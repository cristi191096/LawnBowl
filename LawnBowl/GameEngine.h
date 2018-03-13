#pragma once

#include "GameObject.h"
#include <iostream>
#include <vector>

class GameEngine
{
	static std::vector<GameObject*> gameobjects; ///<Vector of (pointers to) game objects: all the objects in the game.

	static void FixedUpdate();
	static void updateGame(); ///<Function that updates the game state
public:
	static void initEngine(int argc, char **argv, const char* windowTitle = "New Game", bool debugMode = false, int width = 500, int height = 500); ///<Initialises the engine, initilising glut and OpenGL.
	static void displayFunc();
	static void reshapeFunc(int, int);
	static void addGameObject(GameObject* gameobject, bool follow); ///<Adds a GameObject to the game.
	static void startEngine(); ///<Start the engine (and the main game loop).
	static void cleanup(); ///<Function to clean up and delete any pointers and anything else when the game exists to prevent memory leaks.
};

