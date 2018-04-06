#include "GameEngine.h"
#include "Camera.h"
#include "Ball.h"
#include "Rect.h"

Shader* GameEngine::currentShader = nullptr;
std::vector<GameObject*> GameEngine::gameobjects;
glm::mat4 GameEngine::projectionMat = glm::mat4();
glm::mat4 GameEngine::modelView = glm::mat4();
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;
int GameEngine::deltaTime;
int GameEngine::SCREEN_WIDTH;
int GameEngine::SCREEN_HEIGHT;

Model GameEngine::nanoSuit;



#pragma region INIT
void GameEngine::initEngine(int argc, char **argv, const char* windowTitle, bool debug, int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
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
			Camera::instance->ProcessKeyboardInput(LEFT, deltaTime);
			std::cout << "CamPos: " << Camera::instance->Position.x << " | " << Camera::instance->Position.y << " | " << Camera::instance->Position.z << std::endl;
		}
		if (key == 'd') {
			Camera::instance->ProcessKeyboardInput(RIGHT, deltaTime);
			std::cout << "CamPos: " << Camera::instance->Position.x << " | " << Camera::instance->Position.y << " | " << Camera::instance->Position.z << std::endl;
		}
		if (key == 'w') {
			Camera::instance->ProcessKeyboardInput(FORWARD, deltaTime);
			std::cout << "CamPos: " << Camera::instance->Position.x << " | " << Camera::instance->Position.y << " | " << Camera::instance->Position.z << std::endl;
		}
		if (key == 's') {
			Camera::instance->ProcessKeyboardInput(BACKWARD, deltaTime);
			std::cout << "CamPos: " << Camera::instance->Position.x << " | " << Camera::instance->Position.y << " | " << Camera::instance->Position.z << std::endl;
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
	Renderer::Clear();

	currentShader->Bind();
	currentShader->SetUniformMat4("view", Camera::instance->GetView());
	//Material::shader->SetUniformMat4("u_ModelViewMat", modelView);
	for (int i = 0; i < gameobjects.size(); i++) {
		gameobjects[i]->draw();
		//renderer->Draw(gameobjects[i], DrawType::ELEMENTS);
	}

	glm::mat4 model(1.0);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, -70.0f)); // translate it down so it's at the center of the scene
	//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	currentShader->SetUniformMat4("model", model);

	
	nanoSuit.Draw();

	glutSwapBuffers();
}

void GameEngine::reshapeFunc(int w, int h) 
{
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
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
	deltaTime = newTimeSinceStart - oldTimeSinceStart;

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
	
	
	//GameEngine::addGameObject(new Rectangle(5, 5, Vector3D(0, 0, 0), "Rect", glm::vec4(0, 0, 1, 1)));
	
	//Rectangle* rectangle = new Rectangle(5, 5, "Rect", glm::vec4(0, 0, 1, 1));
//	Rect* rect = new Rect(700, 700, Vector3D(0, 0, 0), "Rect", glm::vec4(0, 0, 1, 1));
	//Ball* myBall = new Ball(0.5, Vector3D(0, 0, 1), "BlueBall", glm::vec4(0,1,0,1));
	
	//GameEngine::addGameObject(rect);
	//GameEngine::addGameObject(myBall);

	nanoSuit = Model("Resources/Models/nanosuit/nanosuit.obj");

	currentShader->Bind();
	Camera::instance->Perspective(-SCREEN_WIDTH/2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 0.2f, 100.0f);
	currentShader->SetUniformMat4("projection", Camera::instance->GetProjection());
	//Send this to the shader
	
	//Material::shader->SetUniformMat4("u_ProjectionMat", projectionMat);

	glutMainLoop();
}
void GameEngine::cleanup()
{
}
#pragma endregion aka setup()