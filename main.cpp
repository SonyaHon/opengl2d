#include "engine.h"

int main() {
    Display	mainDisplay = Display(1280, 720, "The Game", false);
    Camera	camera;
    Renderer	renderer(mainDisplay, camera);

	Image img = Image("./assets/imgs/mario.png");
	Sprite sprite = Sprite(&img);

    while (!mainDisplay.needsToBeClosed()) {
	renderer.prepare();

		renderer.render_simple(sprite);

	renderer.update();
	mainDisplay.update();
    }
    return 0;
}
