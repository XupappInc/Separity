#include "RigidBody.h"

#include "Entity.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "Vector.h"

#include <btBulletDynamicsCommon.h>

RigidBody::RigidBody() {}

RigidBody::RigidBody(typeRb tipo, float mass) : mass_(mass), tipo_(tipo) {
	tr_ = ent_->getComponent<Transform>();

	btTransform nuevoTr;
	nuevoTr.setIdentity();
	nuevoTr.setOrigin(tr_->getBulletTransform()->getOrigin());
	nuevoTr.setRotation(tr_->getBulletTransform()->getRotation());

	btDefaultMotionState* motionState = new btDefaultMotionState(nuevoTr);

	spyutils::Vector3 escala = tr_->getScale();
	btCollisionShape* collisionShape =
	    new btBoxShape(btVector3(escala.x, escala.y, escala.z));

	btVector3 localInertia(0, 0, 0);  // Tensor de inercia local
	collisionShape->calculateLocalInertia(
	    mass_, localInertia);  // Calcula el tensor de inercia local
	btRigidBody::btRigidBodyConstructionInfo rbInfo(
	    mass_, motionState, collisionShape, localInertia);
	rb_ = new btRigidBody(rbInfo);

	// auto dynamicsWorld = PhysicsManager::getWorld;
	// dynamicsWorld->addRigidBody(rigidBody);
}

RigidBody::~RigidBody() { delete rb_; }

void RigidBody::addForce(spyutils::Vector3 force) {
	btVector3 fuerza(force.x, force.y, force.z);
	btVector3 posicion(0, 0, 0);
	rb_->applyForce(fuerza, posicion);
}

void RigidBody::clearForces() { rb_->clearForces(); }

void RigidBody::setLinearVelocity(spyutils::Vector3 vel) {
	btVector3 velocidad(vel.x, vel.y, vel.z);
	rb_->setLinearVelocity(velocidad);
}

void RigidBody::setAngularVelocity(spyutils::Vector3 vel) {
	btVector3 velocidad(vel.x, vel.y, vel.z);
	rb_->setAngularVelocity(velocidad);
}

void RigidBody::applyTorque(spyutils::Vector3 torq) {
	btVector3 torque(torq.x, torq.y, torq.z);
	rb_->applyTorque(torque);
}
void RigidBody::setGravity(spyutils::Vector3 g) {
	btVector3 fuerza(g.x, g.y, g.z);
	rb_->setGravity(fuerza);
}