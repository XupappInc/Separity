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
#include "SoundEngine.h"
//#include "checkML.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "Camera.h"

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

	/*SoundEngine* soundEngine_ = new SoundEngine();
	soundEngine_->initSoundSystem();
	soundEngine_->createSound("Assets//theme.mp3");
	soundEngine_->playSound();*/

	RenderManager* renderManager = Separity::RenderManager::getInstance();
	renderManager->createTestScene();
	PhysicsManager* physManager = Separity::PhysicsManager::getInstance();
	physManager->initWorld();
	AudioManager* audManager = Separity::AudioManager::getInstance();
	audManager->initAudioSystem();
	Entity* mono2 = new Entity(_grp_GENERAL);
	auto musica = mono2->addComponent<AudioSource>("Assets//theme.mp3",
	                                               string("codigoLyoko"), true);
	audManager->playAudio(string("codigoLyoko"));

	InputManager* inputManager = Separity::InputManager::getInstance();
	Entity* mono = new Entity(_grp_GENERAL);
	auto tr = mono->addComponent<Transform>();
	 tr->translate(Spyutils::Vector3(0, 2, 0));
	 tr->setScale(0.5);
	//tr->roll(90);
	// mesh renderer
	mono->addComponent<MeshRenderer>(renderManager->getSceneManager(),
	                                 "Sinbad.mesh");
	auto luz = mono->addComponent<Light>(DIRECTIONAL_LIGHT);
	luz->setDiffuse(Spyutils::Vector3(1, 1, 1));
	luz->setDirection(Spyutils::Vector3(1, 0, 0));
	/* collider (antes de rigidbody siempre)*/
	 colliderParams params;
	 params.colShape = CUBE;
	 params.height = 1;
	 params.width = 1;
	 params.depth = 1;
	 params.isTrigger = false;

	 mono->addComponent<Collider>(params);

	//rigidbody
	 auto rb=mono->addComponent<RigidBody>(DYNAMIC, 10);
	 rb->setGravity(Spyutils::Vector3(0, -1, 0));
	rb->addForce(Spyutils::Vector3(1000, 1000, 0));
	////  Bucle principal










	 	Entity* mono1 = new Entity(_grp_GENERAL);
	 auto tr1 = mono1->addComponent<Transform>();
	 tr1->translate(Spyutils::Vector3(0, -10, -20));
	 tr1->setScale(2);
	 tr1->roll(90);
	 //  mesh renderer
	 mono1->addComponent<MeshRenderer>(renderManager->getSceneManager(),
	                                  "Sinbad.mesh");
	
	 /* collider (antes de rigidbody siempre)*/
	 colliderParams params1;
	 params1.colShape = CUBE;
	 params1.height = 1;
	 params1.width = 1;
	 params1.depth = 1;
	 params1.isTrigger = false;

	 mono1->addComponent<Collider>(params1);

	 // rigidbody
	 auto rb1 = mono1->addComponent<RigidBody>(STATIC, 10);
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
				//cam_tr->translate(Spyutils::Vector3(0, 1, 0));
				cam_cam->zoom(-3);
				std::cout << cam_cam->getZoom() << "\n";
			}
			if(inputManager->isKeyDown('s')) {
				//cam_tr->translate(Spyutils::Vector3(0, -1, 0));
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
	
		}

		physManager->update();
		renderManager->update();
		renderManager->render();
		audManager->update();
	}

	return 0;
}