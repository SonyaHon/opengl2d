//
// Created by sonyahon on 18.03.17.
//

#include "Tile.h"

Tile::Tile(Image *image, float x, float y, float posx, float posy) {
	position = glm::vec2(x, y);
	this->posx = posx;
	this->posy = posy;
	sprite = Sprite(image, posx, posy, 16*5, 16*5);
	sprite.setPosition(position);
}

Sprite &Tile::getSprite() {
	return sprite;
}

void Tile::update() {
	sprite.setPosition(position);
}
