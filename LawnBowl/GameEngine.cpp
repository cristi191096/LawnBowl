#include "GameEngine.h"

Renderer* GameEngine::renderer = new Renderer();
std::vector<GameObject*> GameEngine::gameobjects;
glm::mat4 GameEngine::projectionMat = glm::mat4();
glm::mat4 *GameEngine::modelView = new glm::mat4();


#pragma region INIT
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

	glutKeyboardFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = true;

		if (key == 27) {
			
			exit(0);
		}
	});
	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = false;
	});

	glutSpecialFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = true;
	});

	glutSpecialUpFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = false;
	});


	glutIdleFunc(updateGame);
}
#pragma endregion Initialise glut, glew and some variables
void GameEngine::displayFunc() 
{
	for (int i = 0; i < gameobjects.size(); i++) {
		renderer->Draw(gameobjects[i], DrawType::ARRAYS);
	}

	glutSwapBuffers();
}

void GameEngine::reshapeFunc(int w, int h) 
{
	glViewport(0, 0, w, h);
}

void GameEngine::addGameObject(GameObject * gameobject, bool follow)
{
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
void GameEngine::cleanup()
{
}
#pragma endregion aka setup()