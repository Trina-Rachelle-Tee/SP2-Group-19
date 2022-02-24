
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "Camera3.h"
#include "SceneMainMenu.h"
#include "SceneInvestigation.h"
#include "SceneMinigame1.h"
#include "SceneHouse.h"
#include "SceneHouseGame.h"
#include "SceneMinigame2.h"
#include "SceneStalk.h"
#include "SceneGameEnd.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
unsigned Application::m_width;
unsigned Application::m_height;
int scenecheck = 1;

void resize_callback(GLFWwindow* window, int w, int h)
{
	Application::m_width = w;
	Application::m_height = h;
	glViewport(0, 0, w, h);
}

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}

void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}

int Application::GetWindowWidth()
{
	return m_width;
}

int Application::GetWindowHeight()
{
	return m_height;
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{

}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		glfwSetWindowSizeCallback(m_window, resize_callback);
		exit(EXIT_FAILURE);
	}
	
	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_width = 800;
	m_height = 600;
	m_window = glfwCreateWindow(m_width, m_height, "Test Window", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	//Main Loop
	Scene* scene1 = new SceneMainMenu();
	Scene* scene2 = new SceneHouse();
	Scene* scene3 = new SceneInvestigation();
	Scene* scene4 = new SceneMinigame1();
	Scene* scene5 = new SceneMinigame2;
	Scene* scene6 = new SceneStalk();
	Scene* scene7 = new SceneHouseGame();
	Scene* scene8 = new SceneGameEnd();
	Scene* scene = scene1;

	scene1->Init();
	scene2->Init();
	scene3->Init();
	scene4->Init();
	scene5->Init();
	scene6->Init();
	scene7->Init();
	scene8->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		/*if (IsKeyPressed(VK_F1))
			scene = scene1;
		if (IsKeyPressed(VK_F2))
			scene = scene2;
		if (IsKeyPressed(VK_F3))
			scene = scene3;
		if (IsKeyPressed(VK_F4))
			scene = scene4;
		if (IsKeyPressed(VK_F5))
			scene = scene5;
		if (IsKeyPressed(VK_F6))
			scene = scene6;
		if (IsKeyPressed(VK_F7))
			scene = scene7;
		if (IsKeyPressed(VK_F8))
			scene = scene8;*/

		int sceneNo = scene->NextScene();
		if (sceneNo == 1)
			scene = scene1;
		if (sceneNo == 2)
			scene = scene2;
		if (sceneNo == 3)
			scene = scene3;
		if (sceneNo == 4)
			scene = scene4;
		if (sceneNo == 5)
			scene = scene5;
		if (sceneNo == 6)
			scene = scene6;
		if (sceneNo == 7)
			scene = scene7;
		if (sceneNo == 8)
			scene = scene8;


		if (scene == scene8) 
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		if (glfwRawMouseMotionSupported())
		{
			glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}

		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed

	scene->Exit();

	delete scene1;
	delete scene2;
	delete scene3;
	delete scene4;
	delete scene5;
	delete scene6;
	delete scene7;
	delete scene8;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}


