/*
 *  Display is the class for all windows of the program.
 */

#ifndef INC_2DS_DISPLAYMANAGER_H
#define INC_2DS_DISPLAYMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "Enums.h"

class Display {
private:
	int height;
	int width;

	int real_height;
	int real_width;

	GLFWwindow* main_win;

	bool isFullscreen;

	const char* win_tittle;

	double elTime;

public:
	Display(int width, int height, const char* tittle, bool fullScreen);
	int needsToBeClosed();
	void update();
	int getMainWindowHeight() const;
	int getMainWindowWidth() const;
	GLFWwindow *getMainWindow() const;
	bool keyPressed(int key);
	bool keyReleased(int key);
	void setFullscreen(bool state);
	glm::vec2 getMousePosition();
	void setCursorMode(CursorStateEnum mode);
	double  ellapsedTime();
	virtual ~Display();
};


#endif //INC_2DS_DISPLAYMANAGER_H
