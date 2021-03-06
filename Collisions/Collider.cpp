#include "Collider.h"
#include "../Utils/Utils.h"


Collider::Collider() {
    type = COLLIDER_RECTANGLE;
    position = glm::vec2(0);
    height = 0;
    width = 0;
    radius1 = 0;
}

Collider::Collider(ColliderType type, GLfloat x, GLfloat y, GLfloat size1, GLfloat size2) : type(type), position(glm::vec2(x, y)) {
    if(type == COLLIDER_RECTANGLE) {
        width = size1;
        height = size2;
    }
    else {
        radius1 = size1;
    }
}

void Collider::setColliderSize(GLfloat size1, GLfloat size2) {
    if(type == COLLIDER_RECTANGLE) {
        width = size1;
        height = size2;
    }
    else {
        radius1 = size1;
    }
}

bool Collider::collisionSimple(GLfloat myX, GLfloat myY, Collider &target, GLfloat targetX, GLfloat targetY) {
    bool collide = false;
    if(this->type == COLLIDER_RECTANGLE && target.type == COLLIDER_RECTANGLE) {
        if((this->position.x + myX >= target.position.x + targetX && this->position.x + myX <= target.position.x + targetX + target.width) ||
            (target.position.x + targetX >= this->position.x + myX && target.position.x + targetX <= this->position.x + myX + this->width)){
            if((this->position.y + myY >= target.position.y + targetY && this->position.y + myY <= target.position.y + targetY + target.height) ||
               (target.position.y + targetY >= this->position.y + myY && target.position.y + targetY <= this->position.y + myY + this->height)) {
                    collide = true;
            }
        }
    }
    else if(this->type == COLLIDER_CIRCLE && target.type == COLLIDER_CIRCLE) {
		GLfloat radSum = this->radius1 + target.radius1;
		GLfloat distance = square_distance(myX, myY, targetX, targetY);
		if(radSum >= distance) collide = true;
	}
    return collide;
}

Collider::Collider(ColliderType type, GLfloat x, GLfloat y, GLfloat size1) : type(type), position(glm::vec2(x, y)) {
	if(type == COLLIDER_CIRCLE) {
		radius1 = size1;
	}
	else {
		height = size1;
		width = size1;
	}
}

const glm::vec2 &Collider::getPosition() const {
	return position;
}
