#include "texture_atlas.h"

TextureAltas::TextureAltas(int width, int height, int depth):
m_width(width), m_height(height), m_depth(depth)
{
	m_data = (unsigned char*)malloc(sizeof(unsigned char) * m_width * m_height * m_depth);
	m_nodes.clear();
	m_used = 0;
	m_id = SIZE_MAX;
}

TextureAltas::~TextureAltas()
{
	free(m_data);
}

void TextureAltas::setRegion(RectI region, unsigned char* data, int stride)
{
	int depth;
	int charsize;
	assert( region.x_ > 0);
	assert( region.y_ > 0);
	assert( region.x_ < (m_width-1));
	assert( ( region.x_ + region.width) <= (m_width-1));
	assert( region.y_ < (m_height-1));
	assert( (region.y_ + region.height) <= (m_height-1));

	//prevent copying data from undefined position 
	//and prevent memcpy's undefined behavior when count is zero
	assert(region.height == 0 || (data != NULL && region.width> 0));

	depth = m_depth;
	charsize = sizeof(char);
	for( int i=0; i<region.height; ++i )
	{
		memcpy( m_data+((region.y_+i)*m_width+ region.x_ ) * charsize * depth,
			data + (i*stride) * charsize, region.width * charsize * depth  );
	}
}

void TextureAltas::clear()
{
	
}

int TextureAltas::fit(int index, int width, int height)
{
	SkylineNode *node;
	int x, y, width_left;
	size_t i;

	node = &m_nodes.at(index);
	x = node->x;
	y = node->y;
	width_left = width;
	i = index;

	if ((x + width) > (m_width - 1))
	{
		return -1;
	}
	y = node->y;
	while (width_left > 0)
	{
		node = &m_nodes.at(index);
		if (node->y > y)
		{
			y = node->y;
		}
		if ((y + height) > (m_height - 1))
		{
			return -1;
		}
		width_left -= node->z;
		++i;
	}
	return y;
}


void TextureAltas::merge()
{
	vector<SkylineNode>::iterator iter = m_nodes.begin();
	vector<SkylineNode>::iterator curIter, nextIter;
	for (; iter != m_nodes.end(); ++iter)
	{
		curIter = iter;
		nextIter = iter + 1;
		if (curIter->y == nextIter->y)
		{
			curIter->z += nextIter->z;
			m_nodes.erase(nextIter);
			--iter;
		}
	}
}

RectI TextureAltas::getRegion(int width, int height)
{
	int y, best_index;
	int best_height, best_width;
	SkylineNode *node, *prev;
	ivec4 region = { { 0, 0, width, height } };
	unsigned int i;

	best_height = UINT_MAX;
	best_index = -1;
	best_width = UINT_MAX;

	for (i = 0; i < m_nodes.size(); ++i)
	{
		y = fit(i, width, height);
		if (y >= 0)
		{
			node = &m_nodes.at(i);
			if (((y + height) < best_height) ||
				(((y + height) == best_height) && (node->z > 0 && node->z < best_width)))
			{
				best_height = y + height;
				best_index = i;
				best_width = node->z;
				region.x = node->x;
				region.y = y;
			}
		}
	}

	if (best_index == -1)
	{
		region.x = -1;
		region.y = -1;
		region.width = 0;
		region.height = 0;
		return region;
	}

	node = (SkylineNode *)malloc(sizeof(SkylineNode));
	if (node == NULL)
	{
		fprintf(stderr,
			"line %d: No more memory for allocating data\n", __LINE__);
		exit(EXIT_FAILURE);
	}
	node->x = region.x;
	node->y = region.y + height;
	node->z = width;
	//vector_insert(self->nodes, best_index, node);
	vector<SkylineNode>::iterator iter = m_nodes.begin();
	m_nodes.insert(iter,best_index+1, *node);
	free(node);

	iter = m_nodes.begin();
	iter = m_nodes.begin();
	iter += best_index + 1;
	for (i = best_index + 1; i < m_nodes.size() && iter != m_nodes.end(); ++i, iter++)
	{
		node = &m_nodes.at(i);
		prev = &m_nodes.at(i - 1);

		if (node->x < (prev->x + prev->z))
		{
			int shrink = prev->x + prev->z - node->x;
			node->x += shrink;
			node->z -= shrink;
			if (node->z <= 0)
			{
				m_nodes.erase(iter);
				--i;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	merge();
	m_used += width * height;
	return region;
}

