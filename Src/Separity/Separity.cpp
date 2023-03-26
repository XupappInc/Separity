// Separity.cpp : Este archivo contiene la función "main". La ejecución del
// programa comienza y termina ahí.
//

#include "Animator.h"
#include "AudioListener.h"
#include "AudioManager.h"
#include "Camera.h"
#include "Entity.h"
#include "InputManager.h"
#include "Light.h"
#include "LuaManager.h"
#include "ParticleSystem.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "UIManager.h"
// #include "checkML.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "VirtualTimer.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#include <AudioSource.h>
#include <Behaviour.h>
#include <Collider.h>
#include <MeshRenderer.h>
#include <Ogre.h>
#include <RigidBody.h>
#include <Transform.h>
#include <Windows.h>
#include <iostream>

const uint32_t FRAMERATE = 60;
const uint32_t FRAMETIME = 1000 / FRAMERATE;

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
	UIManager* uiManager = Separity::UIManager::getInstance();
	uiManager->initUi();
	InputManager* inputManager = Separity::InputManager::getInstance();
	/*LuaManager* luaManager = Separity::LuaManager::getInstance();
	luaManager->initLua();*/
	SceneManager* sceneMenager = Separity::SceneManager::getInstance();
	sceneMenager->loadScene("Assets/Scenes/scene.lua");


	Entity* MusicInstance = new Entity(_grp_GENERAL,Spyutils::Vector3(10, 0, 0));
	//auto tr2 = MusicInstance->addComponent<Transform>();
	//tr2->setPosition();
	//auto musica = MusicInstance->addComponent<AudioSource>(
	//    "Assets//theme.mp3", string("codigoLyoko"), true);
	//audManager->playAudio(string("codigoLyoko"), 1.0f, 100.0f);

	
	//luaManager->loadScript("prueba", cube);

	/*tr->setScale(0.03);
	tr->pitch(30);
	tr->translate(Spyutils::Vector3(0, 0, 0));*/
	// Entity* plano = new Entity(_grp_GENERAL);
	// auto tr1 = plano->addComponent<Transform>();
	// tr1->translate(Spyutils::Vector3(0, -3, 0));
	// tr1->setScale(0.2, 0.005, 0.2);

	////  mesh renderer
	// plano->addComponent<MeshRenderer>(renderManager->getSceneManager(),
	//                                   "cube.mesh");

	///* collider (antes de rigidbody siempre)*/
	// colliderParams params1;
	// params1.colShape = CUBE;
	// params1.height = .5f;
	// params1.width = 20;
	// params1.depth = 20;
	// params1.offsetY = 0;
	// params1.isTrigger = false;

	// plano->addComponent<Collider>(params1);

	//// rigidbody
	// auto rb1 = plano->addComponent<RigidBody>(STATIC, 10);
	///*rb1->setGravity(Spyutils::Vector3(0, -1, 0));
	// rb1->addForce(Spyutils::Vector3(0, 2, 0));*/

	

	Entity* camera = new Entity(_grp_GENERAL);
	Transform* cam_tr = camera->getEntTransform();  // addComponent<Transform>();
	cam_tr->translate(Spyutils::Vector3(0, 0, 15));
	Camera* cam_cam = camera->addComponent<Camera>();
	camera->addComponent<AudioListener>();

	Spyutils::VirtualTimer* timer = new Spyutils::VirtualTimer();
	uint32_t deltaTime = 0;

	//
	// Entity* sinbad = new Entity(_grp_GENERAL);
	// auto tr4 = sinbad->addComponent<Transform>();
	// tr4->setScale(2, 2, 2);
	////  mesh renderer
	// sinbad->addComponent<MeshRenderer>(renderManager->getSceneManager(),
	//                                   "Sinbad.mesh");
	// auto anim = sinbad->addComponent<Animator>();
	// anim->setUpAnims();

	bool quit = false;
	renderManager->initComponent();
	physManager->initComponent();
	uiManager->initComponent();
	inputManager->initComponent();
	audManager->initComponent();
	while(!quit) {
		timer->reset();

		inputManager->update();
		if(inputManager->isKeyDown('q') || inputManager->closeWindowEvent()) {
			quit = true;
		} else {
			if(inputManager->isKeyDown('a')) {
				cam_tr->translate(Spyutils::Vector3(-5, 0, 0));
			}
			if(inputManager->isKeyDown('d')) {
				cam_tr->translate(Spyutils::Vector3(5, 0, 0));
			}
			if(inputManager->isKeyDown('w')) {
				cam_tr->translate(Spyutils::Vector3(0, 5, 0));
			}
			if(inputManager->isKeyDown('s')) {
				cam_tr->translate(Spyutils::Vector3(0, -5, 0));
			}
			if(inputManager->isKeyDown(InputManager::ARROW_LEFT)) {
				cam_tr->yaw(0.1f);
			}
			if(inputManager->isKeyDown(InputManager::ARROW_RIGHT)) {
				cam_tr->yaw(-0.1f);
			}
			if(inputManager->isKeyDown(InputManager::ARROW_UP)) {
				cam_tr->translate(Spyutils::Vector3(0, 0, -5));
			}
			if(inputManager->isKeyDown(InputManager::ARROW_DOWN)) {
				cam_tr->translate(Spyutils::Vector3(0, 0, 5));
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

		//luaManager->update();
		physManager->update(deltaTime);
		renderManager->update();
		renderManager->render();
		audManager->update();
		uiManager->update();

		deltaTime = timer->currTime();
		int waitTime = FRAMETIME - deltaTime;

		if(waitTime > 0)
			Sleep(waitTime);
	}
	delete MusicInstance;
	//	delete plano;
	delete camera;
	delete timer;

	renderManager->saveConfiguration();
	renderManager->closedown();

	renderManager->close();
	uiManager->close();
	inputManager->close();
	audManager->close();
	physManager->close();
	//luaManager->close();

	return 0;
}