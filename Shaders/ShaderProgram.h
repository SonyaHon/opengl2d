#ifndef TESTING_SHADERPROGRAMM_H
#define TESTING_SHADERPROGRAMM_H

#include <GL/glew.h>
#include <string>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ShaderProgram {
private:
	GLuint vShader;
	GLuint gShader;
	GLuint fShader;
	GLuint programID;

	bool geom;

	GLuint loadShader(std::string, GLenum);

public:
	ShaderProgram(std::string, std::string);
	ShaderProgram(std::string, std::string, std::string);
	virtual ~ShaderProgram();

	void start();
	void stop();
	GLint getUniformLocation(std::string);
	void loadFloat(GLint, GLfloat);
	void loadVector3(GLint, glm::vec3);
	void loadVector4(GLint, glm::vec4);
	void loadBool(GLint, bool);
	void loadMatrix4(GLint, glm::mat4);

};

#endif //TESTING_SHADERPROGRAMM_H