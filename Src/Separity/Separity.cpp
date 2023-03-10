// Separity.cpp : Este archivo contiene la función "main". La ejecución del
// programa comienza y termina ahí.
//

// #include "RenderEngine.h"
#include "AudioManager.h"
#include "Entity.h"
#include "InputManager.h"
#include "Light.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
// #include "checkML.h"
#include "Camera.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#include <AudioSource.h>
#include <Collider.h>
#include <MeshRenderer.h>
#include <Ogre.h>
#include <RigidBody.h>
#include <Transform.h>
#include <iostream>

using namespace std;
using namespace Separity;
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	RenderManager* renderManager = Separity::RenderManager::getInstance();
	renderManager->init();
	PhysicsManager* physManager = Separity::PhysicsManager::getInstance();
	physManager->initWorld();
	AudioManager* audManager = Separity::AudioManager::getInstance();
	audManager->initAudioSystem();
	Entity* mono2 = new Entity(_grp_GENERAL);
	auto musica = mono2->addComponent<AudioSource>("Assets//theme.mp3",
	                                               string("codigoLyoko"), true);
	audManager->playAudio(string("codigoLyoko"));

	InputManager* inputManager = Separity::InputManager::getInstance();
	Entity* sphere = new Entity(_grp_GENERAL);
	auto tr = sphere->addComponent<Transform>();
	//tr->pitch(60);
	tr->setPosition(Spyutils::Vector3(0, 4, 0));
	tr->setScale(0.03);
	 
	//  mesh renderer
	sphere->addComponent<MeshRenderer>(renderManager->getSceneManager(),
	                                 "cube.mesh");
	auto luz = sphere->addComponent<Light>(DIRECTIONAL_LIGHT);
	luz->setDiffuse(Spyutils::Vector3(1, 0, 1));
	luz->setDirection(Spyutils::Vector3(-1, -1, -1));
	/* collider (antes de rigidbody siempre)*/
	colliderParams params;
	params.colShape = CUBE;
	params.height = 1;
	params.width = 1;
	params.depth = 1;
	params.isTrigger = false;

	sphere->addComponent<Collider>(params);

	// rigidbody
	auto rb = sphere->addComponent<RigidBody>(DYNAMIC, 10);
	rb->setGravity(Spyutils::Vector3(0, 0, 0));
	//rb->addForce(Spyutils::Vector3(1000, 0, 0));
	//rb->addForce(Spyutils::Vector3(1000, 1000, 0));
	rb->applyTorque(Spyutils::Vector3(10, 0,0));
	//rb->setAngularVelocity(Spyutils::Vector3(0.1, 0, 0));
	////  Bucle principal

	Entity* plano = new Entity(_grp_GENERAL);
	auto tr1 = plano->addComponent<Transform>();
	tr1->translate(Spyutils::Vector3(0, -3, 0));
	tr1->setScale(0.2,0.005,0.2);

	//  mesh renderer
	plano->addComponent<MeshRenderer>(renderManager->getSceneManager(),
	                                  "cube.mesh");

	/* collider (antes de rigidbody siempre)*/
	colliderParams params1;
	params1.colShape = CUBE;
	params1.height = 1;
	params1.width = 1;
	params1.depth = 1;
	params1.isTrigger = false;

	plano->addComponent<Collider>(params1);

	// rigidbody
	auto rb1 = plano->addComponent<RigidBody>(STATIC, 10);
	rb1->setGravity(Spyutils::Vector3(0, -1, 0));

	Entity* camera = new Entity(_grp_GENERAL);
	Transform* cam_tr = camera->addComponent<Transform>();
	cam_tr->translate(Spyutils::Vector3(0, 0, 15));
	Camera* cam_cam = camera->addComponent<Camera>();

	bool quit = false;
	while(!quit) {
		inputManager->update();
		if(inputManager->isKeyDown('q') || inputManager->closeWindowEvent()) {
			quit = true;
		} else {
			if(inputManager->isKeyDown('a')) {
				cam_tr->translate(Spyutils::Vector3(-1, 0, 0));
			}
			if(inputManager->isKeyDown('d')) {
				cam_tr->translate(Spyutils::Vector3(1, 0, 0));
			}
			if(inputManager->isKeyDown('w')) {
				// cam_tr->translate(Spyutils::Vector3(0, 1, 0));
				cam_cam->zoom(-3);
				std::cout << cam_cam->getZoom() << "\n";
			}
			if(inputManager->isKeyDown('s')) {
				// cam_tr->translate(Spyutils::Vector3(0, -1, 0));
				cam_cam->zoom(3);
				std::cout << cam_cam->getZoom() << "\n";
			}
			if(inputManager->isKeyDown(InputManager::ARROW_LEFT)) {
				cam_tr->yaw(0.1);
			}
			if(inputManager->isKeyDown(InputManager::ARROW_RIGHT)) {
				cam_tr->yaw(-0.1);
			}
			if(inputManager->isKeyDown(InputManager::ARROW_UP)) {
				cam_tr->pitch(0.1);
			}
			if(inputManager->isKeyDown(InputManager::ARROW_DOWN)) {
				cam_tr->pitch(-0.1);
			}
			if(inputManager->isKeyDown('c')) {
				RenderManager::getInstance()->resizeWindow(1920, 1080);
			}
			if(inputManager->isKeyDown('x')) {
				RenderManager::getInstance()->fullScreen(true);
			}
			if(inputManager->isKeyDown('z')) {
				RenderManager::getInstance()->fullScreen(false);
			}
	
		}

		physManager->update();
		renderManager->update();
		renderManager->render();
		audManager->update();
	}

	renderManager->saveConfiguration();

	return 0;
}