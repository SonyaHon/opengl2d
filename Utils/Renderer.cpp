#include <iostream>
#include <map>
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

std::map<int, std::map<GLchar, Character> > Characters;

Renderer::Renderer(Display& display, Camera& cam) :
		//ShaderProgramms
		simple_shader_program("/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/simple_vertex.glsl",
							  "/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/simle_fragment.glsl"),
		textShader("/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/textVertex.glsl",
				   "/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/textFragment.glsl"),
		finalFBORender("/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/postProccessing/default_vertex.glsl",
					   "/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/postProccessing/default_fragment.glsl"),
		setContrastProgram("/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/postProccessing/default_vertex.glsl",
						   "/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/postProccessing/contrast_fragment.glsl"),
		flatColorProgram("/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/flatVertex.glsl",
						 "/home/sonyahon/workspace/cpp/opengl2d/Shaders/GLSL/flatFragment.glsl"),

		//FBO`s
		first(display.getMainWindowWidth(), display.getMainWindowHeight()),
		second(display.getMainWindowWidth(), display.getMainWindowHeight())
{
	this->R = 0.0f;
	this->B = 0.0f;
	this->G = 0.0f;
	this->projection_matrix = glm::ortho(0.0f, (float) display.getMainWindowWidth(),
										 (float) display.getMainWindowHeight(), 0.0f, 0.0f, 100.0f);
	this->cam = &cam;
	this->hasBgImage = false;
	this->bg = nullptr;

	this->isUsingFirts = true;

	if(FT_Init_FreeType(&ft)) {
		std::cout << "ASD" << std::endl;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const GLfloat vertexBuffer[] =  {-1.0f, 1.0f,
									 -1.0f, -1.0f,
									 1.0f, -1.0f,
									 1.0f, -1.0f,
									 1.0f, 1.0f,
									 -1.0f, 1.0f};

	const GLfloat uv_buffer[] = {0, 1,
								 0, 0,
								 1, 0,
								 1, 0,
								 1, 1,
								 0, 1};

	glGenVertexArrays(1, &mainSquadVAO);
	glBindVertexArray(mainSquadVAO);
	glGenBuffers(2, mainSquadVBOS);
	glBindBuffer(GL_ARRAY_BUFFER, mainSquadVBOS[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, mainSquadVBOS[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer), uv_buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Renderer::~Renderer() {
	FT_Done_Face(font_face);
	FT_Done_FreeType(ft);
}

void Renderer::prepare() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, isUsingFirts?first.getFbo_id():second.getFbo_id());
	glClearColor(R, G, B, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if(this->hasBgImage) {
		Sprite sprite = Sprite(this->bg);
		render_simple(sprite);
	}
}

void Renderer::setClearColor(GLfloat r, GLfloat g, GLfloat b) {
	this->R = r;
	this->G = g;
	this->B = b;
}

void Renderer::render_simple(Sprite &sprite) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, isUsingFirts?first.getFbo_id():second.getFbo_id());
	simple_shader_program.start();
	simple_shader_program.loadMatrix4(simple_shader_program.getUniformLocation("transformationMatrix"), sprite.genModelMatrix());
	simple_shader_program.loadMatrix4(simple_shader_program.getUniformLocation("viewMatrix"), cam->getViewMatrix());
	simple_shader_program.loadMatrix4(simple_shader_program.getUniformLocation("projectionMatrix"), this->projection_matrix);
	glBindVertexArray(sprite.getVAO_ID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite.getTexture()->getTextureID());
	glDrawElements(GL_TRIANGLES, sprite.getVertexCount(), GL_UNSIGNED_INT, (void *)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
	simple_shader_program.stop();

}

void Renderer::setBackgroundImage(Image *image) {
	hasBgImage = true;
	this->bg = image;
}

void Renderer::loadFont(std::string path, unsigned int font_height, GLuint font_id) {

	FT_New_Face(ft, path.c_str(), 0, &this->font_face);
	FT_Set_Pixel_Sizes(font_face, 0, font_height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for(GLubyte c = 0; c < 128; c++) {
		if(FT_Load_Char(font_face, c, FT_LOAD_RENDER)) {
			std::cout << "Failed to load Glyph " << c << std::endl;
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_RED,
					 font_face->glyph->bitmap.width,
					 font_face->glyph->bitmap.rows,
					 0,
					 GL_RED,
					 GL_UNSIGNED_BYTE,
					 font_face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
				texture,
				glm::ivec2(font_face->glyph->bitmap.width, font_face->glyph->bitmap.rows),
				glm::ivec2(font_face->glyph->bitmap_left, font_face->glyph->bitmap_top),
				font_face->glyph->advance.x
		};
		Characters[font_id].insert(std::pair<GLchar, Character>(c, character));
	}
}

void Renderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color, GLuint font_id) {
	textShader.start();
	textShader.loadVector4(textShader.getUniformLocation("textColor"), color);
	textShader.loadMatrix4(textShader.getUniformLocation("projection"), projection_matrix);
	glBindVertexArray(textVAO);
	glActiveTexture(GL_TEXTURE0);
	glEnableVertexAttribArray(0);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = Characters[font_id][*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - ch.Bearing.y * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;

		GLfloat vertices[6][4] = {
				{xpos,     ypos + h, 0.0, 1.0f - 0.0f},
				{xpos,     ypos,     0.0, 1.0f - 1.0f},
				{xpos + w, ypos,     1.0, 1.0f - 1.0f},

				{xpos,     ypos + h, 0.0, 1.0f - 0.0f},
				{xpos + w, ypos,     1.0, 1.0f - 1.0f},
				{xpos + w, ypos + h, 1.0, 1.0f - 0.0f}
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.Advance >> 6) * scale;
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	textShader.stop();
}

void Renderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLfloat r, GLfloat g, GLfloat b,
						  GLfloat a, GLuint font_id) {
	glm::vec4 color = glm::vec4(r, g, b, a);
	renderText(text, x, y, scale, color, font_id);


}

void Renderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLuint font_id) {
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	renderText(text, x, y, scale, color, font_id);
}

void Renderer::update() {

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	finalFBORender.start();
	glBindVertexArray(this->mainSquadVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, isUsingFirts?first.getTexture_id():second.getTexture_id());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
	finalFBORender.stop();

}

void Renderer::setContrast(float value) {
	isUsingFirts = !isUsingFirts;
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, isUsingFirts?first.getFbo_id():second.getFbo_id());
	setContrastProgram.start();
	setContrastProgram.loadFloat(setContrastProgram.getUniformLocation("contrast"), value);
	glBindVertexArray(this->mainSquadVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, isUsingFirts?second.getTexture_id():first.getTexture_id());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
	setContrastProgram.stop();
}



void Renderer::drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, glm::vec4 color) {
	const GLfloat vertex_buffer[] = {0, 0, 0,
									 0, height, 0,
									 width, 0, 0,
									 width, 0, 0,
									 0, height, 0,
									 width, height, 0};
	glm::mat4 transformation_matrix = glm::mat4(1.0f);
	transformation_matrix = glm::translate(transformation_matrix, glm::vec3(x, y, -1));
	GLuint tempVAO;
	GLuint tempVBO;
	glGenVertexArrays(1, &tempVAO);
	glBindVertexArray(tempVAO);
	glGenBuffers(1, &tempVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	flatColorProgram.start();
	flatColorProgram.loadVector4(flatColorProgram.getUniformLocation("color"), color);
	flatColorProgram.loadMatrix4(simple_shader_program.getUniformLocation("transformationMatrix"), transformation_matrix);
	flatColorProgram.loadMatrix4(simple_shader_program.getUniformLocation("viewMatrix"), cam->getViewMatrix());
	flatColorProgram.loadMatrix4(simple_shader_program.getUniformLocation("projectionMatrix"), this->projection_matrix);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	flatColorProgram.stop();
	glDeleteBuffers(1, &tempVBO);
	glDeleteVertexArrays(1, &tempVAO);
}

void
Renderer::drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glm::vec4 color = glm::vec4(r, g, b, a);
	drawRect(x, y, width, height, color);
}

void Renderer::drawCircle(GLfloat x, GLfloat y, GLfloat radius, glm::vec4 color) {
	//Triangle_fan or check for shader drawing
}

void Renderer::drawCirlce(GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glm::vec4 color = glm::vec4(r, g, b, a);
	drawCircle(x, y, radius, color);
}


//TODO Collision
//TODO Optimize render proses
//TODO DrawRect functions etc. Need to make some new shaders for it.
//TODO Enums of keyboard`s buttons for glfw one`s
//TODO More Post proccessing shit
