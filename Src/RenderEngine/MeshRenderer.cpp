#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"
#include "spyMath.h"
#include "RenderManager.h"
#include <Ogre.h>
#include <cassert>
using namespace Separity;

Separity::MeshRenderer::MeshRenderer(std::string meshName) {
	Separity::RenderManager* render = Separity::RenderManager::getInstance();
	// se accede al sceneManager
	sceneManager_ = render->getSceneManager();
	meshRenderer_ = sceneManager_->getRootSceneNode()->createChildSceneNode();
	entity_ = sceneManager_->createEntity(meshName);
	//meshRenderer_->attachObject(entity_);

}
void Separity::MeshRenderer::initComponent() {
	Transform* tr = ent_->getComponent<Transform>();
	auto node = tr->getNode();
	node->attachObject(entity_);

}

Separity::MeshRenderer::~MeshRenderer() {

	sceneManager_->destroyMovableObject(entity_);
	sceneManager_->destroySceneNode(meshRenderer_);
	
	entity_ = nullptr;
	meshRenderer_ = nullptr;
	sceneManager_ = nullptr;
}

void Separity::MeshRenderer::render() {
	/*Transform* tr = ent_->getComponent<Transform>();

	assert(tr != nullptr);

	meshRenderer_->setPosition(tr->getPosition().x, tr->getPosition().y,
	                           tr->getPosition().z);
	Ogre::Matrix3 matrix;
	matrix.FromEulerAnglesYXZ(
	    Ogre::Radian(Spyutils::Math::toRadians(tr->getRotation().y)),
	    Ogre::Radian(Spyutils::Math::toRadians(tr->getRotation().x)),
	    Ogre::Radian(Spyutils::Math::toRadians(tr->getRotation().z)));
	Ogre::Quaternion rot(matrix);
	meshRenderer_->setOrientation(rot);

	meshRenderer_->setScale(tr->getScale().x, tr->getScale().y,
	                        tr->getScale().z);*/
}

void Separity::MeshRenderer::setTexture(const std::string& name) {

	entity_->setMaterialName(name);
}

void Separity::MeshRenderer::setActive(bool set) {
	// ec:Component::setActive(set);
	meshRenderer_->setVisible(set);
}

Ogre::SceneNode* Separity::MeshRenderer::getNode() { return meshRenderer_; }

Ogre::Entity* Separity::MeshRenderer::getOgreEntity() { return entity_; }
