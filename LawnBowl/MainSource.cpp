#include "Vector3D.h"
#include "GameEngine.h"
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

	OBJLoader loader;

	loader.LoadFile("Ball_and_Box.obj");

	Vector3D myVec(5, 2, 3);
	Vector3D otherVec(1, 1, 1);
	std::cout << "Dot Product: "<< myVec.DotProduct(otherVec) << std::endl;
	ASSERT(TestVectorClass(myVec, otherVec));
	Vector3D cross = myVec.CrossProduct(otherVec);
	std::cout << "Cross Product: " << cross.x() << " | " << cross.y() << " | " << cross.z() << std::endl;
	myVec -= otherVec;
	std::cout << "MYVEC: " << myVec.x() << " | " << myVec.y() << " | " << myVec.z() << std::endl;
	system("PAUSE");
	return 0;
}