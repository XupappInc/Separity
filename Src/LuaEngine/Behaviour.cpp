#include "Behaviour.h"

#include "Entity.h"
#include "LuaManager.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <iostream>

Separity::Behaviour::Behaviour() : behaviourLua_(nullptr) {
	mngr_ = Separity::LuaManager::getInstance();
}

Separity::Behaviour::Behaviour(luabridge::LuaRef* behaviourLua)
    : behaviourLua_(behaviourLua) {
	mngr_ = Separity::LuaManager::getInstance();
}

Separity::Behaviour::~Behaviour() { delete behaviourLua_; }

void Separity::Behaviour::setLuaScript(luabridge::LuaRef* behaviourLua) {
	behaviourLua_ = behaviourLua;
}

void Separity::Behaviour::update(const uint32_t& deltaTime) {
	luabridge::LuaRef updateLua = (*behaviourLua_)["update"];
	if(updateLua.isFunction()) {
		try {
			updateLua();
		} catch(luabridge::LuaException e) {
			std::cout << e.what() << "\n";
		}
	}
}

void Separity::Behaviour::start() {
	luabridge::LuaRef startLua = (*behaviourLua_)["start"];
	if(startLua.isFunction()) {
		startLua();
	}
}

void Separity::Behaviour::awake() {
	luabridge::LuaRef awakeLua = (*behaviourLua_)["awake"];
	if(awakeLua.isFunction()) {
		awakeLua();
	}
}

void Separity::Behaviour::onCollisionEnter(Entity* other) {
	luabridge::LuaRef collisionEnterLua = (*behaviourLua_)["onCollisionEnter"];
	if(collisionEnterLua.isFunction()) {
		auto L = Separity::LuaManager::getInstance()->getLuaState();

		// crea la variable global other de forma temporal, para que lo pueda
		// utilizar el script
		luabridge::setGlobal(L, other, "other");
		collisionEnterLua();
		// quita la variable global de la pila de Lua
		luabridge::getGlobal(L, "other");
	}
}

void Separity::Behaviour::onCollisionExit(Entity* other) {
	luabridge::LuaRef collisionExitLua = (*behaviourLua_)["onCollisionExit"];
	if(collisionExitLua.isFunction()) {
		auto L = Separity::LuaManager::getInstance()->getLuaState();

		// crea la variable global other de forma temporal, para que lo pueda
		// utilizar el script
		luabridge::setGlobal(L, other, "other");
		collisionExitLua(other);
		// quita la variable global de la pila de Lua
		luabridge::getGlobal(L, "other");
	}
}

void Separity::Behaviour::onCollisionStay(Entity* other) {
	luabridge::LuaRef collisionStayLua = (*behaviourLua_)["onCollisionStay"];
	if(collisionStayLua.isFunction()) {
		auto L = Separity::LuaManager::getInstance()->getLuaState();

		// crea la variable global other de forma temporal, para que lo pueda
		// utilizar el script
		luabridge::setGlobal(L, other, "other");
		collisionStayLua(other);
		// quita la variable global de la pila de Lua
		luabridge::getGlobal(L, "other");
	}
}

void Separity::Behaviour::onButtonClick() {
	luabridge::LuaRef onButtonClickLua = (*behaviourLua_)["onButtonClick"];
	if(onButtonClickLua.isFunction()) {
		onButtonClickLua();
	}
}

void Separity::Behaviour::onButtonReleased() {
	luabridge::LuaRef onButtonReleasedLua = (*behaviourLua_)["onButtonReleased"];
	if(onButtonReleasedLua.isFunction()) {
		onButtonReleasedLua();
	}
}

void Separity::Behaviour::onButtonHover() {
	luabridge::LuaRef onButtonHoverLua = (*behaviourLua_)["onButtonHover"];
	if(onButtonHoverLua.isFunction()) {
		onButtonHoverLua();
	}
}

void Separity::Behaviour::onButtonUnhover() {
	luabridge::LuaRef onButtonUnhoverLua = (*behaviourLua_)["onButtonUnhover"];
	if(onButtonUnhoverLua.isFunction()) {
		onButtonUnhoverLua();
	}
}
