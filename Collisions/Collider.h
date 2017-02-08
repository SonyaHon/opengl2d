#ifndef INC_2DS_COLLIDER_H
#define INC_2DS_COLLIDER_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Utils/Enums.h"

class Collider {
private:
    ColliderType type;
    glm::vec2 position;
    GLfloat width;
    GLfloat height;
    GLfloat radius1;
    GLfloat radius2;
public:
    Collider();
    Collider(ColliderType type, GLfloat x, GLfloat y, GLfloat size1, GLfloat size2);
    void setColliderSize(GLfloat size1, GLfloat size2);
    bool collisionSimple(GLfloat myX, GLfloat myY, Collider &target, GLfloat targetX, GLfloat targetY);
};


#endif //INC_2DS_COLLIDER_H
