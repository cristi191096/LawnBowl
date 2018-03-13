#include "GameEngine.h"

std::vector<GameObject*> GameEngine::gameobjects;

void GameEngine::initEngine(int argc, char **argv, const char* windowTitle, bool debug, int width, int height) {

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(windowTitle);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_RGBA);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(displayFunc);

	glutReshapeFunc(reshapeFunc);

	//glutKeyboardFunc();
	/*glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = false;
	});

	glutSpecialFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = true;
	});

	glutSpecialUpFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = false;
	});*/


	glutIdleFunc(updateGame);
}

void GameEngine::displayFunc() 
{

}

void GameEngine::reshapeFunc(int w, int h) 
{
	glViewport(0, 0, w, h);
}

#pragma region COLISION_DETECTION
void GameEngine::FixedUpdate() {


}
#pragma endregion check for colision every X frames


#pragma region UPDATE
void GameEngine::updateGame() {

}
#pragma endregion update the game status every frame

#pragma region START_ENGINE
void GameEngine::startEngine() {


}
#pragma endregion aka setup()