#include "Synthese_TP1.h"


/*
	TP1 context values
*/
static const float m = 80; //kg
static const float g = 9.8; //m.s-2
static const float coefGuillaume = 0.25;

static const glm::vec3 V0{0, 0, 0};
static const glm::vec3 P0{0, 0, 4000};
static const float deltaTime = 1; //s

static const glm::vec3 z{0, 0, 1};
static const glm::vec3 wind{-5, 0, 0};


int main(){

	std::cout << "BEGIN COMPUTING VALUES AT EACH TICK (delatTime " << deltaTime << "ms)" << std::endl;

	printResults(glm::vec3(), V0, P0);

	glm::vec3 speed{V0};
	glm::vec3 position{P0};

	glm::vec3 nextSpeed;
	glm::vec3 nextPosition;

	//File
	std::ofstream dataFile;
	dataFile.open("..\\..\\..\\results\\coef-0_25-wind-MG.data"); //Current directory is x64-Debug

	while(position.z > 0.0f){

		//Compute acceleration
		glm::vec3 acceleration = (-m * g * z - speed * coefGuillaume * glm::length(speed)) / m;

		//Compute next speed & position
		glm::vec3 nextSpeed = speed + acceleration * deltaTime;
		glm::vec3 nextPosition = position + speed * deltaTime + wind * deltaTime;

		speed = nextSpeed;
		position = nextPosition;

		writeResults(dataFile, acceleration, speed, position);
		printResults(acceleration, speed, position);

	}

	dataFile.close();

	return 0;
}

inline void writeResults(std::ofstream& file, glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position) {
	file << position.x << " " << /*position.y << " " <<*/ position.z << std::endl;
}

void printResults(glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position) {

	std::cout << std::endl;
	std::cout << "Acceleration : (" << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << ")" << std::endl;
	std::cout << "Speed        : (" << speed.x << ", " << speed.y << ", " << speed.z << ")" << std::endl;
	std::cout << "Position     : (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

}