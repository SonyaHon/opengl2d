#ifndef INC_2DS_FBO_H
#define INC_2DS_FBO_H

#include <GL/glew.h>

class FBO {
private:
	GLuint width;
	GLuint height;

	GLuint fbo_id;
	GLuint texture_id;

public:
	FBO(GLuint width, GLuint height);

	virtual ~FBO();

	GLuint getFbo_id() const;

	GLuint getTexture_id() const;

	GLuint getWidth() const;

	GLuint getHeight() const;
};


#endif //INC_2DS_FBO_H
