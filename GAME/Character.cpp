//
// Created by sonyahon on 15.03.17.
//

#include "Character.h"

Character::Character(Image * image) {
	sprite = Sprite(image, 0, 0, 12 * 5, 12 * 5);
	position = glm::vec2(500, -50);
	speed = glm::vec2(0);
	acceleration = glm::vec2(0);

	lastGroundPos = position;

	timer.start();
	posX = 0.0f;
	posY = 0.0f;

	dir = RIGHT;
	dirToggle = false;
	isOnGround = false;

	isNearWall = std::pair<bool, Direction >(false, LEFT);
	lastSidePos = position;

}

void Character::update() {
	speed += acceleration;
	position += speed;
	acceleration = glm::vec2(0);

	if(!isOnGround) applyForce(glm::vec2(0, 0.3));
	if(!isOnGround && action != JUMP) action = FALL;

	if(isNearWall.first) {
		if(dir == isNearWall.second) {
			if(dir == RIGHT) {
				position.x = lastSidePos.x - 12*5 + 4;
			}
			else {
				position.x  = lastSidePos.x + 16*5;
			}
		}
	}

	if(isOnGround) position.y = lastGroundPos.y;

	if(isOnGround) speed.y = 0;

	speed.x /= 20;
	if(speed.x <= 0.001) speed.x = 0;

	posY = action * 12 * 5;


	if(timer.getTime(TIME_M_SECS) >= 200) {
		posX += 12 * 5;
		float mult;
		switch(action) {
			case IDLE:
				mult = 3;
				break;
			case RUN:
				mult = 4;
				break;
			case JUMP:
				mult = 4;
				break;
			case FALL:
				mult = 2;
				break;
		}
 		if (posX >= 12 * 5 * mult && action == JUMP) {
			action = FALL;
			posX = 0;
		}
		else if(posX >= 12 * 5 * mult ) {
			posX = 0;
		}
		timer.reset();
	}



	sprite.setTetxturePosition(posX, posY,12 * 5, 12 * 5);
	if(dir == LEFT)
		sprite.flipHorizontally();
	sprite.setPosition(position);
}

bool Character::isIsOnGround() const {
	return isOnGround;
}

void Character::applyForce(glm::vec2 newForce) {
	acceleration += newForce;

}

Sprite& Character::getSprite() {
	return sprite;
}

void Character::setAction(Action act) {
	action = act;
}

void Character::setIsOnGround(bool isOnGround) {
	Character::isOnGround = isOnGround;
}

void Character::setDir(Direction dir) {
	Character::dir = dir;
}

void Character::checkForGround(Tile *map) {
	isOnGround = false;
	isNearWall = std::pair<bool, Direction >(false, LEFT);
	for (int i = 0; i < 64; i++) {
		if (sprite.simpleCollide(map[i].getSprite())) {
			if(sprite.getColliderPosition().y < map[i].getSprite().getColliderPosition().y && speed.y >= 0) {
				lastGroundPos = map[i].getSprite().getPosition();
				lastGroundPos.y -= 12 * 5;
				isOnGround = true;
			}
			if(sprite.getColliderPosition().y >= map[i].getSprite().getColliderPosition().y) {
				isNearWall = std::pair<bool, Direction >(true, sprite.getColliderPosition().x >=
																	   map[i].getSprite().getColliderPosition().x ? LEFT : RIGHT);
				lastSidePos = map[i].getSprite().getPosition();
			}
		}
	}

}

void Character::setPosition(const glm::vec2 &position) {
	Character::position = position;
}

void Character::setSpeed(const glm::vec2 &speed) {
	Character::speed = speed;
}

const glm::vec2 &Character::getSpeed() const {
	return speed;
}
