#ifndef texture2D_h
#define texture2D_h

#include "texture.h"

class Texture2D : public Texture
{
private:

public:
	void bindTexture() const;
	void texParameteri(GLenum, GLenum);

	/*
	/	load a texture from an array of floats
	*/
	bool loadArrayF(int dimX, int dimY, float* data);

	/*
	/	load a texture from an array of characters (bytes)
	*/
	bool loadArrayC(int dimX, int dimY, char* data);
};

#endif
