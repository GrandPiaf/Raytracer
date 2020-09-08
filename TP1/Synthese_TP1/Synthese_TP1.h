#pragma once

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

static const glm::vec3 planeSpeed{ 50, 0, 0 };
static const glm::vec3 airBallonSpeed{ 0, 0, 0 };

static const glm::vec3 planePosition{ 0, 0, 4000 };
static const glm::vec3 airBallonPosition{ 1000, 0, 4000 };

static const float g = 9.8; //m.s-2
static const float deltaTime = 1; //s

static const glm::vec3 z{ 0, 0, 1 };
static const glm::vec3 wind{ -5, 0, 0 };