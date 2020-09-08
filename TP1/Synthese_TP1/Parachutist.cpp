#include "Parachutist.h"
#include "Synthese_TP1.h"

void Parachutist::computeCurve() {

	glm::vec3 nextSpeed;
	glm::vec3 nextPosition;

	std::ofstream dataFile;
	dataFile.open("..\\..\\..\\results\\" + m_name + "-" + std::to_string(m_coefGuillaume) + ".dat"); //Current directory is x64-Debug

	while (m_position.z > 0.0f) {

		//Compute acceleration
		glm::vec3 acceleration = (-m_mass * g * z - m_speed * m_coefGuillaume * glm::length(m_speed)) / m_mass;

		//Compute next speed & position
		glm::vec3 nextSpeed = m_speed + acceleration * deltaTime;
		glm::vec3 nextPosition = m_position + m_speed * deltaTime + wind * deltaTime;

		m_speed = nextSpeed;
		m_position = nextPosition;

		writeResults(dataFile, acceleration, m_speed, m_position);
		printResults(acceleration, m_speed, m_position);

	}

	dataFile.close();

}


inline void Parachutist::writeResults(std::ofstream& file, glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position) {
	file << position.x << " " << /*position.y << " " <<*/ position.z << std::endl;
}

void Parachutist::printResults(glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position) {

	std::cout << std::endl;
	std::cout << "Acceleration : (" << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << ")" << std::endl;
	std::cout << "Speed        : (" << speed.x << ", " << speed.y << ", " << speed.z << ")" << std::endl;
	std::cout << "Position     : (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

}