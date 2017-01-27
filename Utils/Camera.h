#ifndef INC_2DS_CAMERA_H
#define INC_2DS_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class Camera {
private:
	glm::vec2 position;
	glm::mat4 viewMatrix;

public:
	Camera();
	virtual ~Camera();

	const glm::vec2 &getPosition() const;
	const GLfloat getPositionX() const;
	const GLfloat getPositionY() const;

	void setPosition(const glm::vec2 &position);
	void setPosition(GLfloat x, GLfloat y);

	void translate(glm::vec2 vector);
	void translate(GLfloat x, GLfloat y);

	glm::mat4 getViewMatrix();
};


#endif //INC_2DS_CAMERA_H
