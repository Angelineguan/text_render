#pragma  once 

//////////////////////////////////////////////////////////////////////////
typedef union
{
	int data[4];
	struct {
        int x;
        int y;
        int z;
        int w;
    };
	struct {
        int x_;
        int y_;
        int width;
        int height;
    };
	struct {
        int r;
        int g;
        int b;
        int a;
    };
	struct {
        int red;
        int green;
        int blue;
        int alpha;
    };
	struct {
        int vstart;
        int vcount;
        int istart;
        int icount;
    };
} ivec4;


typedef union
{
	int data[3];
	struct {
        int x;
        int y;
        int z;
    };
	struct {
        int r;
        int g;
        int b;
    };
	struct {
        int red;
        int green;
        int blue;
    };
} ivec3;

typedef union
{
	int data[2];
	struct {
        int x;
        int y;
    };
	struct {
        int s;
        int t;
    };
	struct {
        int start;
        int end;
    };
} ivec2;

//////////////////////////////////////////////////////////////////////////
typedef union
{
	float data[4];
	struct {
        float x;
        float y;
        float z;
        float w;
    };
	struct {
        float left;
        float top;
        float width;
        float height;
    };
	struct {
        float r;
        float g;
        float b;
        float a;
    };
	struct {
        float red;
        float green;
        float blue;
        float alpha;
    };
} vec4;

typedef union
{
	float data[3];
	struct {
        float x;
        float y;
        float z;
    };
	struct {
        float r;
        float g;
        float b;
    };
	struct {
        float red;
        float green;
        float blue;
    };
} vec3;

typedef union
{
	float data[2]; 
	struct {
        float x;
        float y;
	};
	struct {
        float s;
		float t;
	};
} vec2;

//////////////////////////////////////////////////////////////////////////
typedef ivec2  SizeI;
typedef vec2  SizeF;
typedef vec4 Color;
typedef ivec4 RectI;
typedef vec4 RectF;