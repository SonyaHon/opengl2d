#ifndef INC_2DS_IMAGE_H
#define INC_2DS_IMAGE_H


#include <GL/glew.h>

class Image {
private:
	GLuint textureID;
	GLuint image_height;
	GLuint image_width;
public:
	Image(const char* path);
	Image();
	virtual ~Image();
	GLuint getTextureID() const;
	GLuint getImage_height() const;
	GLuint getImage_width() const;
};


#endif //INC_2DS_IMAGE_H
