#pragma once
#include "vec2.h"
#include "Entity.h"
#include <math.h>

class Physics {
public:
	static vec2 getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
	static vec2 getPrevOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
	static bool isCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};