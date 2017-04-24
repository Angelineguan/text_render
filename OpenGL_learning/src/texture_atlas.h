#pragma  once
#include "stdafx.h"
#include "object.h"

class TextureAltas
{
public:
	TextureAltas(int width, int height, int depth);

	/**
	*  Allocate a new region in the atlas.
	*
	*  @param self   a texture atlas structure
	*  @param width  width of the region to allocate
	*  @param height height of the region to allocate
	*  @return       Coordinates of the allocated region
	*
	*/
	RectI getRegion(int width, int height);

	/**
	 *  Upload data to the specified atlas region.
	 *
	 *  @param self   a texture atlas structure
	 *  @param x      x coordinate the region
	 *  @param y      y coordinate the region
	 *  @param width  width of the region
	 *  @param height height of the region
	 *  @param data   data to be uploaded into the specified region
	 *  @param stride stride of the data
	 *
	 */
	void setRegion(RectI region, unsigned char* data, int stride);

	/**
	*  Remove all allocated regions from the atlas.
	*
	*  @param self   a texture atlas structure
	*/
	void clear();

private:
	TextureAltas() {};
	~TextureAltas();

    vector<Object*> m_nodes;

    int m_width;

    int m_height;

    int m_depth;

    /**
     * Allocated surface size
     */
    int m_used;

    /**
     * Texture identity (OpenGL)
     */
    unsigned int m_id;

    /**
     * Atlas data
     */
    unsigned char * m_data;
};