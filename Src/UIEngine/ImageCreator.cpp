#include "ImageCreator.h"
#include "Entity.h"
#include"Image.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "LuaManager.h"
Separity::ImageCreator::ImageCreator() {}

void Separity::ImageCreator::registerInLua() {
	lua_State* L = Separity::LuaManager::getInstance()->getLuaState();
	luabridge::getGlobalNamespace(L).beginClass<Image>("image").endClass();
}

bool Separity::ImageCreator::createComponent(lua_State* L,
                                              Separity::Entity* ent) {
	int x, y, width, height;
	std::string texture, overlayName;

	if(readParam("overlay", L, overlayName) && readParam("x", L, x) &&
	   readParam("y", L, y) && readParam("width", L, width) &&
	   readParam("height", L, height) && readParam("texture", L, texture)) {
		
		ent->addComponent<Image>(overlayName, x, y, width, height, texture);
		return true;
	}

	return false;
}
