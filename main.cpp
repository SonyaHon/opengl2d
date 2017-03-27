#include "engine.h"
#include "GAME/Character.h"
#include "GAME/Tile.h"

int main() {
    Display	mainDisplay = Display(1280, 720, "The Game", false);
    Camera	camera;
    Renderer	renderer(mainDisplay, camera);
	renderer.loadFont("assets/fonts/mytype.ttf", 64, 0);
	renderer.setClearColor(0.2, 0.2, 0.5);

	Image playerSpriteSheet("/home/sonyahon/workspace/cpp/opengl2d/assets/imgs/Player.png");
	Image tileset("/home/sonyahon/workspace/cpp/opengl2d/assets/imgs/tileset.png");

	Character player = Character(&playerSpriteSheet);
	player.setAction(FALL);
	player.getSprite().setCollider(COLLIDER_RECTANGLE, 0, 12*5 - 20, 12 * 5, 20);

	Tile map[64];

	for(int i = 0; i < 30; i++) {
		Tile tile = Tile(&tileset, i * 16*5, 720 - 16 * 5, rand()%10>=8?16*5*6:16*5, 0);
		map[i] = tile;
	}
	for(int i = 30; i < 60; i++) {
		Tile tile = Tile(&tileset, (i - 30) * 16*5, 720 - 16 * 5 * 2, 16*5*2, 0);
		map[i] = tile;
	}

	map[60] = Tile(&tileset, 700, 720-16*5 - 30 * 5, 16*5, 16*5);
	map[60].getSprite().setCollider(COLLIDER_RECTANGLE, 0, 0, 16*5, 3);

	map[61] = Tile(&tileset, 700 + 16 * 5 + 20, 720-16*5 - 30 * 5 - 40, 16*5, 16*5);
	map[61].getSprite().setCollider(COLLIDER_RECTANGLE, 0, 0, 16*5, 3);

	map[62] = Tile(&tileset, 500, 720-16*5 - 30 * 10, 16*5, 16*5);
	map[62].getSprite().setCollider(COLLIDER_RECTANGLE, 0, 0, 16*5, 3);

	map[63] = Tile(&tileset, (10) * 16 * 5, 720-16*5*3, 16*5*2, 0);

	while (!mainDisplay.needsToBeClosed()) {
	renderer.prepare();
		for(int i = 0; i < 64; i++) {
			map[i].update();
			renderer.render_simple(map[i].getSprite());
		}

		renderer.renderText(std::to_string((int)player.getSprite().getPositionY()), 20, 100, 0.5, 0);

	renderer.render_simple(player.getSprite());
	player.update();
		player.checkForGround(map);
		if(mainDisplay.keyPressed(GLFW_KEY_A)) {
			player.applyForce(glm::vec2(-5, 0));
			player.setDir(LEFT);
			if(player.isIsOnGround()) {
				player.setAction(RUN);
			}
			if(player.getSprite().getPositionX() <= camera.getPositionX() + 400) {
				camera.translate(-5, 0);
			}
		}
		else if(mainDisplay.keyPressed(GLFW_KEY_D)) {
			player.applyForce(glm::vec2(5, 0));
			player.setDir(RIGHT);
			if(player.isIsOnGround()) {
				player.setAction(RUN);
			}
			if(player.getSprite().getPositionX() >= camera.getPositionX() + mainDisplay.getMainWindowWidth() - 400) {
				camera.translate(5, 0);
			}
		}
		else if(player.isIsOnGround()){
			player.setAction(IDLE);
		}
		if(mainDisplay.keyPressed(GLFW_KEY_SPACE) && player.isIsOnGround()) {
			player.setSpeed(glm::vec2(player.getSpeed().x, 0));
			player.applyForce(glm::vec2(0, -9));
			player.setAction(JUMP);
			player.setIsOnGround(false);
		}

		camera.setPosition(camera.getPositionX(), player.getSprite().getPositionY() - mainDisplay.getMainWindowHeight() / 2);

	renderer.update();
	mainDisplay.update();
    }
    return 0;
}
