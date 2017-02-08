#include <iostream>
#include "Display.h"


Display::Display(int width, int height, const char* tittle, bool fullScreen) : height(height), width(width) {

	if(!glfwInit()) {
		fprintf(stderr, "Error: %s\n", "Failed to initialize glfw.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->isFullscreen = fullScreen;
	win_tittle = tittle;

	if(!fullScreen) {
		this->main_win = glfwCreateWindow(this->width, this->height, tittle, nullptr, nullptr);
	}
	else{
		GLFWmonitor* mainMonitor = glfwGetPrimaryMonitor();
		this->main_win = glfwCreateWindow(this->width, this->height, tittle, mainMonitor, nullptr);
	}

	glfwMakeContextCurrent(main_win);

	glewExperimental = GL_TRUE;
	GLenum glewInitErr = glewInit();

	if(GLEW_OK != glewInitErr) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glewInitErr));
		exit(1);
	}

	glfwGetFramebufferSize(main_win, &real_width, &real_height);
	glViewport(0, 0, real_width, real_height);

	glfwSetInputMode (main_win, GLFW_STICKY_KEYS, 1);
	elTime = 0;

}

int Display::getMainWindowHeight() const {
	return real_height;
}

int Display::getMainWindowWidth() const {
	return real_width;
}

GLFWwindow *Display::getMainWindow() const {
	return main_win;
}

Display::~Display() {
	glfwTerminate();
}

int Display::needsToBeClosed() {
	return glfwWindowShouldClose(this->main_win);
}

void Display::update() {
	glfwPollEvents();
	glfwSwapBuffers(main_win);
	glfwSetTime(0);
}

bool Display::keyPressed(int key) {
	return glfwGetKey(main_win, key) == GLFW_PRESS;
}

bool Display::keyReleased(int key) {
	return glfwGetKey(main_win, key) == GLFW_RELEASE;
}

void Display::setFullscreen(bool state) {
	if(this->isFullscreen != state) {
		if(state) {
			GLFWmonitor *mainMonitor = glfwGetPrimaryMonitor();
			glfwSetWindowMonitor(this->main_win, mainMonitor, 0, 0, this->width, this->height, GLFW_DONT_CARE);
			glfwGetFramebufferSize(main_win, &real_width, &real_height);
			glfwSetWindowSize(this->main_win, real_width, real_height);
			glViewport(0, 0, real_width, real_height);
			this->isFullscreen = true;
		}
		else {
			glfwSetWindowMonitor(this->main_win, nullptr, 100, 100, this->width, this->height, GLFW_DONT_CARE);
			glfwGetFramebufferSize(main_win, &real_width, &real_height);
			glViewport(0, 0, this->width, this->height);
			this->isFullscreen = false;
		}
	}
}

glm::vec2 Display::getMousePosition() {
	double x, y;
	glfwGetCursorPos(main_win, &x, &y);
	glm::vec2 pos = glm::vec2(x, y);
	return pos;
}

void Display::setCursorMode(CursorStateEnum mode) {
	glfwSetInputMode(main_win, GLFW_CURSOR, mode);
}

double Display::ellapsedTime() {
	return glfwGetTime();
}
