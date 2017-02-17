#include "FBO.h"

FBO::FBO(GLuint width, GLuint height) : width(width), height(height) {
	glGenFramebuffers(1, &fbo_id);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FBO::getWidth() const {
	return width;
}

GLuint FBO::getHeight() const {
	return height;
}

GLuint FBO::getFbo_id() const {
	return fbo_id;
}

GLuint FBO::getTexture_id() const {
	return texture_id;
}

void FBO::cleanUp() {
	glDeleteTextures(1, &texture_id);
	glDeleteFramebuffers(1, &fbo_id);
}
