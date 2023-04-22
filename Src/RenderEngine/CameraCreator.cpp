#include "CameraCreator.h"

#include "Camera.h"
#include "Entity.h"
#include "LuaManager.h"
#include "RenderManager.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

Separity::CameraCreator::CameraCreator() {}

void Separity::CameraCreator::registerInLua() {
	lua_State* L = Separity::LuaManager::getInstance()->getLuaState();
	luabridge::getGlobalNamespace(L)
	    .beginClass<Camera>("camera")
	    .endClass();
}

bool Separity::CameraCreator::createComponent(lua_State* L,
                                              Separity::Entity* ent) {

	if(RenderManager::getInstance()->getCamera() != nullptr)
		return false;

	ent->addComponent<Camera>();
	return true;
}