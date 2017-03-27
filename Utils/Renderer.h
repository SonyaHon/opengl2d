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
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string.h>
#include "FBO.h"

class Renderer {
private:
	//Clear color
	GLfloat R;
	GLfloat G;
	GLfloat B;

	//Render projection matrix
	glm::mat4 projection_matrix;

	//Camera to get the view matrix from
	Camera* cam;


	//Shader programs to use for rendering to the fbo`s
	ShaderProgram simple_shader_program;
	ShaderProgram textShader;
	ShaderProgram finalFBORender;
	ShaderProgram setContrastProgram;
	ShaderProgram flatColorProgram;
	ShaderProgram circleColorProgram;
	ShaderProgram blurProgramHorizontal;
	ShaderProgram blurProgramVertical;

	//Background image vars
	bool hasBgImage;
	Image* bg;

	//Text rendering stuff
	FT_Library ft;
	FT_Face font_face;
	GLuint textVAO;
	GLuint textVBO;

	//Post Proccessing stuff
	GLuint mainSquadVAO;
	GLuint mainSquadVBOS[2];

	Display display;
	std::map<std::string, std::pair<FBO, int> > fbos;
	FBO zeroLayer;

	std::string currentFBO;

	int max_layer;

public:

	Renderer(Display& display, Camera& cam);
	virtual ~Renderer();

	void render_simple(Sprite& sprite); // Rendering sprite to the current FBO

	void prepare(); // Clear the screen and render bg image if this is the case

	void setClearColor(GLfloat r, GLfloat g, GLfloat b); // Set the clear color

	void setBackgroundImage(Image* image); // Set the background image if u want

	// Print text
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLuint font_id);
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color, GLuint font_id);
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLuint font_id);

	//Load font to memory, with special id. font height will be the bitmap size, so font_height is the height of font with scale of 1
	void loadFont(std::string path, unsigned int font_height, GLuint font_id);


	//FBO stuff
	void update(); // update draw to the deafult fbo to the rectangle.
	void createLayer(std::string layer_name, int layer_num);
	void bindLayer(std::string layer_name);

	//Post Procces
	void setContrast(float value);

	void setHorizontalBlur(float strength);
	void setVerticalBlur(float strength);
	void setBlur(float strength);


	void drawCircle(GLfloat x, GLfloat y, GLfloat radius, glm::vec4 color);
	void drawCirlce(GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, glm::vec4 color);
	void drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	glm::mat4 &getProjection_matrix();

	void render();
	void render(Sprite &sprite);
};


#endif //INC_2DS_RENDERER_H
