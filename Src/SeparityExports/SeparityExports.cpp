// SeparityExports.cpp : Define las funciones exportadas del archivo DLL.
//
#include "SeparityExports.h"

#include <iostream>
#include "Entity.h"
#include "Component.h"

#include "Behaviour.h"

// Componentes
#include "Animator.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "Behaviour.h"
#include "Button.h"
#include "Camera.h"
#include "Collider.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "Panel.h"
#include "ParticleSystem.h"
#include "RigidBody.h"
#include "Text.h"
#include "Transform.h"
#include "spyQuaternion.h"
#include "GetComponentWrapper.h"
// Managers
#include "AudioManager.h"
#include "EntityManager.h"
//#include "inputmanager.h"
#include "LuaManager.h"
#include "ManagerManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "UIManager.h"
//// Utils
#include "Random.h"
#include "VirtualTimer.h"

#include <Windows.h>
#include <iostream>
#include <utility>

using namespace Separity;
// Constructor de clase exportada.
CSeparityExports::CSeparityExports() { std::cout << "Hola" << std::endl; }

void CSeparityExports::initMotor() { 
	ManagerManager::init();
	UIManager* uiM = UIManager::getInstance();
	EntityManager* eM = EntityManager::getInstance();
	SceneManager* sM = SceneManager::getInstance();
	PhysicsManager* pM = PhysicsManager::getInstance();
	RenderManager* rM = RenderManager::getInstance();
	AudioManager* aM = AudioManager::getInstance();
	LuaManager* lM = LuaManager::getInstance();
	
}
