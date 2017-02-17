#ifndef INC_2DS_SPRITE_H
#define INC_2DS_SPRITE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Image.h"
#include <vector>

#include "../Utils/Enums.h"
#include "../Collisions/Collider.h"

class Sprite {
private: //Fields
	//Mesh size

    GLuint baseHeight;
    GLuint baseWidth;

	GLuint height;
	GLuint width;


	//Mesh transform
	GLfloat rotation;
	glm::vec3 scale;
	glm::vec2 position;
	GLfloat zLevel;

	//Mesh storage
	GLuint VAO_ID;
	std::vector<GLuint> VBOs;
	GLuint vertexCount;

	//Sprite texture
	Image *texture;

	//Sprite origin point
	OriginEnum currOrigin;

	//Mesh`s uv`s and texture`s real size (not visible zeroLayer)
	int img_h;
	int img_w;
	int img_x;
	int img_y;
	float rW;
	float rH;

    Collider collider;

public:
	//<editor-fold desc="Constructors,Destructors">
	Sprite();
	Sprite(const Sprite &sprite);
	Sprite(Image *texture, int img_x, int img_y, int img_w, int img_h);
	Sprite(Image *texture);
	virtual ~Sprite();
	//</editor-fold>

	//<editor-fold desc="Getters">

	GLuint getHeight() const;
	GLuint getWidth() const;
	const glm::vec2 &getPosition() const;
	const float &getPositionX() const;
	const float &getPositionY() const;
	GLfloat getZLevel() const;
	GLuint getVAO_ID() const;
	GLuint getVertexCount() const;
	Image *getTexture() const;
	//</editor-fold>

	//<editor-fold desc="Setters">

    void setCollider(ColliderType type, GLfloat x, GLfloat y, GLuint size1, GLuint size2);
	void setCollider(ColliderType type, GLfloat x, GLfloat y, GLuint size1);
	void setPosition(const glm::vec2 &position);
	void setPosition(GLfloat x, GLfloat y);
	void setZLevel(GLfloat zLevel);
	//</editor-fold>

	//<editor-fold desc="Stuff">

	glm::mat4 genModelMatrix();
	void translate(glm::vec2 vector);
	void translate(GLfloat x, GLfloat y);
	void rotate(float angle, AnglesEn type);
	void setOrigin(OriginEnum origin);
	void setScale(GLfloat);
	void flipHorizontally();
	void flipVertically();
	void setTetxturePosition(int img_x, int img_y, int img_w, int img_h);

    bool simpleCollide(Sprite &target);

	//</editor-fold>

	Sprite operator=(const Sprite& sprite);
};


#endif //INC_2DS_SPRITE_H
