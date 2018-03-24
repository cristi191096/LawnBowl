#include "GameEngine.h"
#include "Ball.h"

Renderer* GameEngine::renderer = new Renderer();
std::vector<GameObject*> GameEngine::gameobjects;
glm::mat4 GameEngine::projectionMat = glm::mat4();
glm::mat4 GameEngine::modelView = glm::mat4();


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

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_RGBA);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
#pragma endregion Initialise glut, glew and some variables

void GameEngine::displayFunc() 
{
	renderer->Clear();
	

	for (int i = 0; i < gameobjects.size(); i++) {
		gameobjects[i]->draw();
		renderer->Draw(gameobjects[i], DrawType::ELEMENTS);
	}

	glutSwapBuffers();
}

void GameEngine::reshapeFunc(int w, int h) 
{
	glViewport(0, 0, w, h);
}

void GameEngine::addGameObject(GameObject * gameobject)
{
	
	gameobjects.push_back(gameobject);
	gameobject->start();
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
	glClearColor(0.5, 0.1, 0.12, 1.0);
	Material::shader = new Shader("GameShaders.shader");
	Material::shader->Bind();

	Ball* myBall = new Ball(10, Vector3D(0, 0, 0), "BlueBall");
	GameEngine::addGameObject(myBall);

	//Send this to the shader
	projectionMat = glm::frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	Material::shader->SetUniformMat4("u_ProjectionMat", projectionMat);

	glutMainLoop();
}
void GameEngine::cleanup()
{
}
#pragma endregion aka setup()