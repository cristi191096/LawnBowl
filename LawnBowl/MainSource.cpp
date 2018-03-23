#include "Vector3D.h"
#include "GameEngine.h"
#include "Ball.h"
#include "OBJLoader.h"

#define ASSERT(x) if(!(x)) __debugbreak();

bool TestVectorClass(Vector3D first, Vector3D second) {

	if (first.DotProduct(second) != 10) {
		std::cout << "Dot Product failed!" << std::endl;
		return false;
	}
	

	return true;
}

int main(int argc, char* argv[]) {

	GameEngine::initEngine(argc, argv, "Lawn Bowl");

	std::cout << "Right here, baby!" << std::endl;
	

	GameEngine::startEngine();
	system("PAUSE");
	return 0;
}