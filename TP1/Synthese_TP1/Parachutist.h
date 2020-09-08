 #include <sstream>

#include <glm/glm.hpp>

class Parachutist {

	private:
		std::string m_name;
		glm::vec3 m_speed;
		glm::vec3 m_position;
		float m_mass; //kg
		float m_coefGuillaume;

	public:
		Parachutist(std::string name, glm::vec3 speed, glm::vec3 position, float mass, float coef) : m_name(name), m_speed{speed}, m_position{position}, m_mass(mass), m_coefGuillaume(coef) {};

		void computeCurve();

		void writeResults(std::ofstream& file, glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position);

		void printResults(glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position);

};