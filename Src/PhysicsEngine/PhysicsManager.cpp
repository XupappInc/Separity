#include "PhysicsManager.h"

#include <btBulletDynamicsCommon.h>
template<typename T>
std::unique_ptr<T> Singleton<T>::_INSTANCE_;
PhysicsManager::PhysicsManager() {}

PhysicsManager::~PhysicsManager() {}

void PhysicsManager::initWorld() {
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration =
	    new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher =
	    new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver =
	    new btSequentialImpulseConstraintSolver;
	world_ = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
	                                     collisionConfiguration);
}

void PhysicsManager::update() { world_->stepSimulation(0.02); }

 btDiscreteDynamicsWorld* PhysicsManager::getWorld() { return world_; }

PhysicsManager* PhysicsManager::getInstance() {
	return static_cast<PhysicsManager*>(instance());
 }
