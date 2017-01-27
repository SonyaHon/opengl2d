/*
 * Class for updating the display context and rendering sprites.
 */

#ifndef INC_2DS_RENDERER_H
#define INC_2DS_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Display.h"
#include "../Sprites/Sprite.h"
#include "../Shaders/ShaderProgram.h"
#include "Camera.h"
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string.h>

class Renderer {
private:
	GLfloat R;
	GLfloat G;
	GLfloat B;
	glm::mat4 projection_matrix;

	Camera* cam;

	ShaderProgram simple_shader_program;
	ShaderProgram textShader;

	bool hasBgImage;
	Image* bg;


	//Text rendering stuff

	FT_Library ft;
	FT_Face font_face;

	GLuint textVAO;
	GLuint textVBO;

public:
	Renderer(Display& display, Camera& cam);
	virtual ~Renderer();

	void render_simple(Sprite& sprite);

	void prepare();
	void setClearColor(GLfloat r, GLfloat g, GLfloat b);
	void setBackgroundImage(Image* image);
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLuint font_id);
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color, GLuint font_id);
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLuint font_id);

	void loadFont(std::string path, unsigned int font_height, GLuint font_id);
};


#endif //INC_2DS_RENDERER_H
