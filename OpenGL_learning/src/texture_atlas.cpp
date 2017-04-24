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

RectI TextureAltas::getRegion(int width, int height)
{

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