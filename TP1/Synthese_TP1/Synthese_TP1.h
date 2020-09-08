#pragma once

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

void writeResults(std::ofstream& file, glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position);

void printResults(glm::vec3 acceleration, glm::vec3 speed, glm::vec3 position);

class Foo {
	public:
		Foo() : m_a(5) {
		}

	private:
		int m_a = 5;

		glm::vec3 m_v{1, 0, 0};
};