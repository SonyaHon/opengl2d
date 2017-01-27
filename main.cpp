#include "Utils/Display.h"
#include "Utils/Camera.h"
#include "Utils/Renderer.h"

int main() {

	Display mainDisplay = Display(1280, 720, "The Game", false);
	Camera camera;
	Renderer renderer = Renderer(mainDisplay, camera);
	renderer.loadFont("/home/sonyahon/workspace/cpp/2ds/assets/fonts/mytype.ttf", 128, 0);


	while(!mainDisplay.needsToBeClosed()) {
		renderer.prepare();


		mainDisplay.update();
	}

	return 0;
}