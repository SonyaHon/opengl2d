#ifndef INC_2DS_CHARACTER_H
#define INC_2DS_CHARACTER_H

#include "../engine.h"
#include "Tile.h"

enum Direction {
	LEFT,
	RIGHT
};

enum Action {
	IDLE,
	RUN,
	JUMP,
	FALL
};

class Character {
private:

	Sprite sprite;

	glm::vec2 position;
	glm::vec2 speed;
	glm::vec2 acceleration;

	Timer timer;

	float posX;
	float posY;

	std::pair<bool, Direction> isNearWall;
	glm::vec2 lastSidePos;

public:
	void setIsOnGround(bool isOnGround);

private:
	bool dirToggle;
	Direction dir;

	bool isOnGround;
	Action action;

	glm::vec2 lastGroundPos;

public:
	Character(Image *image);
	Sprite &getSprite();
	void update();
	void applyForce(glm::vec2 newForce);
	void setAction(Action act);
	bool isIsOnGround() const;
	void setDir(Direction dir);
	void checkForGround(Tile*);

	void setSpeed(const glm::vec2 &speed);

	void setPosition(const glm::vec2 &position);

	const glm::vec2 &getSpeed() const;
};


#endif //INC_2DS_CHARACTER_H
