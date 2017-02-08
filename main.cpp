#include <iostream>
#include "Utils/Display.h"
#include "Utils/Camera.h"
#include "Utils/Renderer.h"
#include "Utils/Timer.h"
#include "Utils/Utils.h"

int main() {

	Display mainDisplay = Display(1280, 720, "The Game", false);



	Camera camera;
	Renderer renderer = Renderer(mainDisplay, camera);

	while(!mainDisplay.needsToBeClosed()) {
		renderer.prepare();



		renderer.update();
        mainDisplay.update();
	}

	return 0;
}