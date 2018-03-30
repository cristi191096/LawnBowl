#include "GameEngine.h"
#include "Camera.h"
#include "Ball.h"
#include "Rect.h"


Renderer* GameEngine::renderer = new Renderer();
Shader* GameEngine::currentShader = new Shader();
std::vector<GameObject*> GameEngine::gameobjects;
glm::mat4 GameEngine::projectionMat = glm::mat4();
glm::mat4 GameEngine::modelView = glm::mat4();
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;


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
		if (key == 'a') {
			Camera::instance->position.x -= 0.1;
			std::cout << "CamPos: " << Camera::instance->position.x << " | " << Camera::instance->position.y << " | " << Camera::instance->position.z << std::endl;
		}
		if (key == 'd') {
			Camera::instance->position.x += 0.1;
			std::cout << "CamPos: " << Camera::instance->position.x << " | " << Camera::instance->position.y << " | " << Camera::instance->position.z << std::endl;
		}
		if (key == 'w') {
			Camera::instance->position.z += 0.1;
			std::cout << "CamPos: " << Camera::instance->position.x << " | " << Camera::instance->position.y << " | " << Camera::instance->position.z << std::endl;
		}
		if (key == 's') {
			Camera::instance->position.z -= 0.1;
			std::cout << "CamPos: " << Camera::instance->position.x << " | " << Camera::instance->position.y << " | " << Camera::instance->position.z << std::endl;
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

	Camera::instance->LookAt( glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	currentShader->SetUniformMat4("u_ModelViewMat", Camera::instance->GetModelView());
	//Material::shader->SetUniformMat4("u_ModelViewMat", modelView);
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

	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTimeSinceStart - oldTimeSinceStart;

	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		gameobjects[i]->update(deltaTime);
	}

	glutPostRedisplay();
}
#pragma endregion update the game status every frame

#pragma region START_ENGINE
void GameEngine::startEngine() {
	glClearColor(0.5, 0.1, 0.12, 1.0);
	
	//GameEngine::addGameObject(new Rectangle(5, 5, Vector3D(0, 0, 0), "Rect", glm::vec4(0, 0, 1, 1)));
	
	Rect* rect = new Rect(1, 0.5, Vector3D(0, 0, 0), "Rect", glm::vec4(0, 0, 1, 1));
	GameEngine::addGameObject(rect);

	Ball* myBall = new Ball(0.5, Vector3D(0, 0, 0), "BlueBall", glm::vec4(0,0,1,1));
	//Rectangle* rectangle = new Rectangle(5, 5, "Rect", glm::vec4(0, 0, 1, 1));
	GameEngine::addGameObject(myBall);


	Camera::instance->Perspective(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	currentShader->SetUniformMat4("u_ProjectionMat", projectionMat);
	//Send this to the shader
	
	//Material::shader->SetUniformMat4("u_ProjectionMat", projectionMat);

	glutMainLoop();
}
void GameEngine::cleanup()
{
}
#pragma endregion aka setup()