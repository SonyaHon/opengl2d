//
// Created by sonyahon on 18.03.17.
//

#ifndef INC_2DS_TILE_H
#define INC_2DS_TILE_H


#include "../engine.h"

class Tile {
private:
	Sprite sprite;
	glm::vec2 position;
	float posx;
	float posy;

public:
	Tile(){};
	Tile(Image *image, float x, float y, float posx, float posy);
	Sprite &getSprite();
	void update();
};


#endif //INC_2DS_TILE_H
