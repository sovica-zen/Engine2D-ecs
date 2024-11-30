#include "Physics.h"

vec2 Physics::getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
	vec2 a_ = a->getComponent<CTransform>().pos;
	vec2 b_ = b->getComponent<CTransform>().pos;

	vec2 ha = a->getComponent<CBBox>().half_size;
	vec2 hb = b->getComponent<CBBox>().half_size;

	float x_overlap = ha.x + hb.x - fabs(a_.x - b_.x);
	float y_overlap = ha.y + hb.y - fabs(a_.y - b_.y);

	return vec2(x_overlap, y_overlap);
}

 vec2 Physics::getPrevOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
	vec2 a_ = a->getComponent<CTransform>().previous_pos;
	vec2 b_ = b->getComponent<CTransform>().previous_pos;

	vec2 ha = a->getComponent<CBBox>().half_size;
	vec2 hb = b->getComponent<CBBox>().half_size;

	float x_overlap = ha.x + hb.x - fabs(a_.x - b_.x);
	float y_overlap = ha.y + hb.y - fabs(a_.y - b_.y);

	return vec2(x_overlap, y_overlap);
}

bool Physics::isCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
	return getOverlap(a, b).x > 0.0 && getOverlap(a, b).y > 0.0;
}
