#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <SFML/Graphics.hpp>

#include "Ray.h"
#include "Light.h"
#include "SceneObject.h"
#include "Sphere.h"

template <typename T>
T changeRange(T const& OldValue, T const& OldMin, T const& OldMax, T const& NewMin, T const& NewMax);