#include "engine.h"

int main() {
    Display	mainDisplay = Display(1280, 720, "The Game", false);
    Camera	camera;
    Renderer	renderer(mainDisplay, camera);


    while (!mainDisplay.needsToBeClosed()) {
		renderer.prepare();



		renderer.update();
		mainDisplay.update();
	}
    return 0;
}
