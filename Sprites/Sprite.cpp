#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Sprite::Sprite(const Sprite &sprite) { // Magic, don`t change

}

Sprite::Sprite() {
	glGenVertexArrays(1, &this->VAO_ID);
	glBindVertexArray(this->VAO_ID);

	this->height = 0;
	this->width = 0;
    this->baseHeight = 0;
    this->baseWidth = 0;
	this->rotation = 0;

    collider = Collider();

	this->img_h = 0;
	this->img_w = 0;
	this->img_x = 0;
	this->img_y = 0;

	this->rW = 0;
	this->rH = 0;

	this->scale = glm::vec3(1, 1, 1);

	this->position = glm::vec2(0.0f, 0.0f);
	this->zLevel = 0;

	this->vertexCount = 6;
	this->currOrigin = ORIGIN_TOP_LEFT;

	static const GLuint indices_buffer[] = {0, 1, 3, 3, 1, 2};

	GLuint vertexVBO;
	glGenBuffers(1, &vertexVBO);
	this->VBOs.push_back(vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 4, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint uvVBO;
	glGenBuffers(1, &uvVBO);
	this->VBOs.push_back(uvVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 4, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint indicesVBO;
	glGenBuffers(1, &indicesVBO);
	this->VBOs.push_back(indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices_buffer, GL_STATIC_DRAW);

	glBindVertexArray(0);

}

Sprite::Sprite(Image *texture): texture(texture) {
	glGenVertexArrays(1, &this->VAO_ID);
	glBindVertexArray(this->VAO_ID);

	this->height = texture->getImage_height();
	this->width = texture->getImage_width();
    this->baseHeight = this->height;
    this->baseWidth = this->width;
	this->rotation = 0;

    collider = Collider(COLLIDER_RECTANGLE, 0, 0, width, height);

	this->img_h = texture->getImage_height();
	this->img_w = texture->getImage_height();
	this->img_x = 0;
	this->img_y = 0;

	this->rW = texture->getImage_width();
	this->rH = texture->getImage_height();

	this->scale = glm::vec3(1, 1, 1);

	this->position = glm::vec2(0.0f, 0.0f);
	this->zLevel = 0;

	this->vertexCount = 6;
	this->currOrigin = ORIGIN_TOP_LEFT;

	float h = (float)this->height;
	float w = (float)this->width;

	const GLfloat vertex_buffer[] = { 0.0f, h, 0.0f,
											 0.0f, 0.0f, 0.0f,
											 w, 0.0f, 0.0f,
											 w, h, 0.0f};

	const GLfloat uv_buffer[] = {0, 0,
								 0, 1,
								 1, 1,
								 1, 0};

	static const GLuint indices_buffer[] = {0, 1, 3, 3, 1, 2};

	GLuint vertexVBO;
	glGenBuffers(1, &vertexVBO);
	this->VBOs.push_back(vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint uvVBO;
	glGenBuffers(1, &uvVBO);
	this->VBOs.push_back(uvVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer), uv_buffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint indicesVBO;
	glGenBuffers(1, &indicesVBO);
	this->VBOs.push_back(indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices_buffer, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Sprite::Sprite(Image *texture, int img_x, int img_y, int img_w, int img_h) : texture(texture) {
	glGenVertexArrays(1, &this->VAO_ID);
	glBindVertexArray(this->VAO_ID);

	this->height = img_h;
	this->width = img_w;
    this->baseHeight = this->height;
    this->baseWidth = this->width;

    collider = Collider(COLLIDER_RECTANGLE, 0, 0, width, height);

	this->img_h = img_h;
	this->img_w = img_w;
	this->img_x = img_x;
	this->img_y = img_y;

	this->rotation = 0;

	this->scale = glm::vec3(1, 1, 1);

	this->position = glm::vec2(0.0f, 0.0f);
	this->zLevel = 0;

	this->vertexCount = 6;

	this->currOrigin = ORIGIN_TOP_LEFT;

	float h = (float)this->height;
	float w = (float)this->width;

	const GLfloat vertex_buffer[] = { 0.0f, h, 0.0f,
											 0.0f, 0.0f, 0.0f,
											 w, 0.0f, 0.0f,
											 w, h, 0.0f};

	this->rW = texture->getImage_width();
	this->rH = texture->getImage_height();

	const GLfloat uv_buffer[] = {img_x / rW, (rH - img_h - img_y) / rH,
										img_x / rW, (rH - img_y) / rH,
										(img_x + img_w) / rW, (rH - img_y) / rH,
										(img_x + img_w) / rW, (rH - img_h - img_y) / rH};

	static const GLuint indices_buffer[] = {0, 1, 3, 3, 1, 2};

	GLuint vertexVBO;
	glGenBuffers(1, &vertexVBO);
	this->VBOs.push_back(vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint uvVBO;
	glGenBuffers(1, &uvVBO);
	this->VBOs.push_back(uvVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer), uv_buffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint indicesVBO;
	glGenBuffers(1, &indicesVBO);
	this->VBOs.push_back(indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices_buffer, GL_STATIC_DRAW);

	glBindVertexArray(0);
}



Sprite::~Sprite() {
	/*glDeleteVertexArrays(1, &this->VAO_ID);
	for(size_t i = 0; i < this->VBOs.size(); i++) {
		glDeleteBuffers(1, &this->VBOs[i]);
	}*/
}

GLuint Sprite::getHeight() const {
	return height;
}

GLuint Sprite::getWidth() const {
	return width;
}

const glm::vec2 &Sprite::getPosition() const {
	return position;
}

GLfloat Sprite::getZLevel() const {
	return zLevel;
}

GLuint Sprite::getVAO_ID() const {
	return VAO_ID;
}

GLuint Sprite::getVertexCount() const {
	return vertexCount;
}

Image *Sprite::getTexture() const {
	return texture;
}

void Sprite::setPosition(const glm::vec2 &position) {
	Sprite::position = position;
}

void Sprite::setZLevel(GLfloat zLevel) {
	Sprite::zLevel = zLevel;
}

const float &Sprite::getPositionX() const {
	return this->position.x;
}

const float &Sprite::getPositionY() const {
	return this->position.y;
}

void Sprite::setPosition(GLfloat x, GLfloat y) {
	this->setPosition(glm::vec2(x, y));
}

glm::mat4 Sprite::genModelMatrix() {
	glm::mat4 transformationMatrix(1.0f);
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(this->position.x, this->position.y, zLevel));
	transformationMatrix = glm::rotate(transformationMatrix, this->rotation, glm::vec3(0, 0, 1));
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(this->scale.x, this->scale.y, this->scale.z));

	return transformationMatrix;
}

void Sprite::translate(glm::vec2 vector) {
	this->position += vector;
}

void Sprite::translate(GLfloat x, GLfloat y) {
	this->position.x += x;
	this->position.y += y;
}

void Sprite::rotate(float angle, AnglesEn type) {
	this->rotation += type == ANGLE_DEGREE ? glm::radians(angle) : angle;
}

void Sprite::setOrigin(OriginEnum origin) {
	if(this->currOrigin == origin) return;

	float h = (float)this->height;
	float w = (float)this->width;

	glBindVertexArray(this->VAO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOs[0]);
	this->currOrigin = origin;

	switch(origin) {
		case ORIGIN_TOP_LEFT: {
			const GLfloat vertex_buffer0[] = {0.0f, h, 0.0f,
											  0.0f, 0.0f, 0.0f,
											  w, 0.0f, 0.0f,
											  w, h, 0.0f};
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer0), vertex_buffer0, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
			break;
		}
		case ORIGIN_TOP_RIGHT: {
			const GLfloat vertex_buffer1[] = {-w, h, 0.0f,
											  -w, 0.0f, 0.0f,
											  0.0f, 0.0f, 0.0f,
											  0.0f, h, 0.0f};
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer1), vertex_buffer1, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
			break;
		}
		case ORIGIN_CENTER: {
			const GLfloat vertex_buffer2[] = {-w / 2.0f, h / 2.0f, 0.0f,
											  -w / 2.0f, -h / 2.0f, 0.0f,
											  w / 2.0f, -h / 2.0f, 0.0f,
											  w / 2.0f, h / 2.0f, 0.0f};
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer2), vertex_buffer2, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
			break;
		}
		case ORIGIN_BOTTOM_LEFT: {
			const GLfloat vertex_buffer3[] = {0.0f, 0.0f, 0.0f,
											  0.0f, -h, 0.0f,
											  w, -h, 0.0f,
											  w, 0.0f, 0.0f};
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer3), vertex_buffer3, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
			break;
		}
		case ORIGIN_BOTTOM_RIGHT: {
			const GLfloat vertex_buffer4[] = {-w, 0.0f, 0.0f,
											  -w, -h, 0.0f,
											  0.0f, -h, 0.0f,
											  0.0f, 0.0f, 0.0f};
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer4), vertex_buffer4, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
			break;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::setScale(GLfloat scFac) {
	this->scale = glm::vec3(scFac, scFac, scFac);
    this->height = baseHeight * scFac;
    this->width = baseWidth * scFac;
    this->collider.setColliderSize(width, height);
}

void Sprite::flipHorizontally() {
	glBindVertexArray(this->VAO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOs[1]);
	const GLfloat uv_buffer[] = {(img_x + img_w) / rW, (rH - img_h - img_y) / rH,
								 (img_x + img_w) / rW, (rH - img_y) / rH,
								 img_x / rW, (rH - img_y) / rH,
								 img_x / rW, (rH - img_h - img_y) / rH};
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer), uv_buffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::flipVertically() {
	glBindVertexArray(this->VAO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOs[1]);
	const GLfloat uv_buffer[] = {img_x / rW, (rH - img_y) / rH,
								 img_x / rW, (rH - img_h - img_y) / rH,
								 (img_x + img_w) / rW, (rH - img_h - img_y) / rH,
								 (img_x + img_w) / rW, (rH - img_y) / rH};
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer), uv_buffer, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::setTetxturePosition(int img_x, int img_y, int img_w, int img_h) {
	this->img_h = img_h;
	this->img_w = img_w;
	this->img_x = img_x;
	this->img_y = img_y;
	const GLfloat uv_buffer[] = {img_x / rW, (rH - img_h - img_y) / rH,
								 img_x / rW, (rH - img_y) / rH,
								 (img_x + img_w) / rW, (rH - img_y) / rH,
								 (img_x + img_w) / rW, (rH - img_h - img_y) / rH};
	glBindVertexArray(VAO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(uv_buffer), uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Sprite Sprite::operator=(const Sprite &sprite) {
	glBindVertexArray(this->VAO_ID);

	this->height = sprite.img_h;
	this->width = sprite.img_w;
    this->baseHeight = this->height;
    this->baseWidth = this->width;

    this->collider = Collider(COLLIDER_RECTANGLE, 0, 0, width, height);

	this->img_h = sprite.img_h;
	this->img_w = sprite.img_w;
	this->img_x = sprite.img_x;
	this->img_y = sprite.img_y;

	this->rW = sprite.texture->getImage_width();
	this->rH = sprite.texture->getImage_height();

	this->texture = sprite.texture;

	float h = (float)this->height;
	float w = (float)this->width;

	const GLfloat vertex_buffer[] = { 0.0f, h, 0.0f,
									  0.0f, 0.0f, 0.0f,
									  w, 0.0f, 0.0f,
									  w, h, 0.0f};

	const GLfloat uv_buffer[] = {img_x / rW, (rH - img_h - img_y) / rH,
								 img_x / rW, (rH - img_y) / rH,
								 (img_x + img_w) / rW, (rH - img_y) / rH,
								 (img_x + img_w) / rW, (rH - img_h - img_y) / rH};

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_buffer), vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOs[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(uv_buffer), uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return *this;
}

void Sprite::setCollider(ColliderType type, GLfloat x, GLfloat y, GLuint size1, GLuint size2) {
    collider = Collider(type, x, y, size1, size2);
}

bool Sprite::simpleCollide(Sprite &target) {
    return this->collider.collisionSimple(position.x, position.y, target.collider, target.position.x, target.position.y);
}

void Sprite::setCollider(ColliderType type, GLfloat x, GLfloat y, GLuint size1) {
	collider = Collider(type, x, y, size1);
}

glm::vec2 Sprite::getColliderPosition() {
	return glm::vec2(this->position + collider.getPosition());
}


