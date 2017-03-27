#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <vector>

void ShaderProgram::CleanUp() {
	this->stop();
	glDetachShader(programID, vShader);
	if(geom) glDetachShader(programID, gShader);
	glDetachShader(programID, fShader);
	glDeleteShader(vShader);
	if(geom) glDeleteShader(gShader);
	glDeleteShader(fShader);
	glDeleteProgram(programID);
}

ShaderProgram::ShaderProgram(std::string vShad, std::string gShad, std::string fShad) {
	geom = true;
	vShader = this->loadShader(vShad, GL_VERTEX_SHADER);
	gShader = this->loadShader(gShad, GL_GEOMETRY_SHADER);
	fShader = this->loadShader(fShad, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vShader);
	glAttachShader(programID, gShader);
	glAttachShader(programID, fShader);
	glLinkProgram(programID);
	glValidateProgram(programID);
}

ShaderProgram::ShaderProgram(std::string vShad, std::string fShad) {
	geom = false;
	vShader = this->loadShader(vShad, GL_VERTEX_SHADER);
	fShader = this->loadShader(fShad, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vShader);
	glAttachShader(programID, fShader);
	glLinkProgram(programID);
	glValidateProgram(programID);
}



GLuint ShaderProgram::loadShader(std::string filename, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	// Reading shader code from file
	std::string shaderCode;
	std::ifstream shaderStream(filename.c_str(), std::ios::in);

	if(shaderStream.is_open()) {
		std::string Line = "";
		while(getline(shaderStream, Line)) {
			shaderCode += "\n" + Line;
		}
		shaderStream.close();
	} else {
		std::cout << "Error opening shader " + filename << std::endl;
	}

	GLint Result = GL_FALSE;
	int InfoLogLenth;

	// Compile shader
	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shader, 1, &sourcePointer, NULL);
	glCompileShader(shader);

	//Test shader

	glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLenth);
	if(InfoLogLenth > 1) {
		std::vector<char> shaderErrorMsg(InfoLogLenth + 1);
		glGetShaderInfoLog(shader, InfoLogLenth, NULL, &shaderErrorMsg[0]);
		std::cout << filename + " info: ";
		fprintf(stdout, "%s", &shaderErrorMsg[0]);
	}
	return shader;
}

void ShaderProgram::start() {
	glUseProgram(programID);
}

void ShaderProgram::stop() {
	glUseProgram(0);
}

GLint ShaderProgram::getUniformLocation(std::string uniformName) {
	return glGetUniformLocation(this->programID, uniformName.c_str());
}

void ShaderProgram::loadFloat(GLint location, GLfloat f) {
	glUniform1f(location, f);
}

void ShaderProgram::loadVector3(GLint location, glm::vec3 v) {
	glUniform3f(location, v.x, v.y, v.z);
}
void ShaderProgram::loadBool(GLint location, bool b) {
	GLfloat b1 = 0.0f;
	if(b) b1 = 1.0f;
	glUniform1f(location, b1);
}

void ShaderProgram::loadMatrix4(GLint location, glm::mat4 matrix) {
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::loadVector4(GLint location, glm::vec4 vector) {
	glUniform4f(location, vector.x, vector.y, vector.z, vector.a);
}

void ShaderProgram::loadVector2(GLint location, glm::vec2 vector) {
	glUniform2f(location, vector.x, vector.y);
}

