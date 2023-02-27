#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"

#include <cassert>

RenderEngine::MeshRenderer::MeshRenderer(Ogre::SceneManager* sceneManager,
                                         std::string meshName)
    : sceneManager_(sceneManager) {
	meshRenderer_ = sceneManager_->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entity = sceneManager_->createEntity(meshName);
	meshRenderer_->attachObject(entity);
}

RenderEngine::MeshRenderer::~MeshRenderer() {
	sceneManager_->destroySceneNode(meshRenderer_);
	meshRenderer_ = nullptr;
	sceneManager_ = nullptr;
}

void RenderEngine::MeshRenderer::render() {
ec:
	Transform* tr = ent_->getComponent<Transform>();

	assert(tr != nullptr);

	meshRenderer_->setPosition(tr->getPosition()[0], tr->getPosition()[1],
	                           tr->getPosition()[2]);

	meshRenderer_->setOrientation(Ogre::Quaternion(
	    tr->getPosition()[0], tr->getPosition()[1], tr->getPosition()[2]));

	meshRenderer_->setScale(tr->getPosition()[0], tr->getPosition()[1],
	                        tr->getPosition()[2]);
}

void RenderEngine::MeshRenderer::setActive(bool set) {
	// ec:Component::setActive(set);
	meshRenderer_->setVisible(set);
}