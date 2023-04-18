#include "PathFollow.h"

#include "Entity.h"
#include "RigidBody.h"
#include "Transform.h"

Separity::PathFollow::PathFollow(std::vector<Spyutils::Vector3> const& path)
    : path_(path), pathingTo_(0), velocity_(1.0f), stopped_(false),
      rigidBody_(nullptr), transform_(nullptr), PhysicsComponent() {}

Separity::PathFollow::~PathFollow() {}

void Separity::PathFollow::update(const uint32_t& deltaTime) {
	
	/*	if(stopped_)
			return;
		if(path_.size() == 0)
			return;
		if(pathingTo_ >= path_.size())
			return;
		Spyutils::Vector3 dir = path_[pathingTo_] - transform_->getPosition();
		dir.normalize();
		rigidBody_->setVelocity(dir * velocity_);
		if(Spyutils::Vector3::distance(path_[pathingTo_],
		                               transform_->getPosition()) < 0.1f) {
			pathingTo_++;
		}*/
	
}

void Separity::PathFollow::initComponent() {
	transform_ = ent_->getComponent<Transform>();
	assert(transform_ != nullptr);

	rigidBody_ = ent_->getComponent<RigidBody>();
	assert(rigidBody_ != nullptr);
}

void Separity::PathFollow::setStopped(bool stop) { stopped_ = stop; }

void Separity::PathFollow::setPath(std::vector<Spyutils::Vector3> const& path) {
	path_ = path;
}

void Separity::PathFollow::setVelocity(float vel) { velocity_ = vel; }
