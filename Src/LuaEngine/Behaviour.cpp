#include "Behaviour.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

Separity::Behaviour::Behaviour() : behaviourLua_(nullptr) {}

Separity::Behaviour::Behaviour(luabridge::LuaRef behaviourLua)
    : behaviourLua_(&behaviourLua) {}

Separity::Behaviour::~Behaviour() {}

void Separity::Behaviour::update() {

    luabridge::LuaRef updateLua = (*behaviourLua_)["update"];
	if(updateLua.isFunction()) {
		updateLua();
	}
}

void Separity::Behaviour::start() {}

void Separity::Behaviour::awake() {}

void Separity::Behaviour::onCollisionEnter(Entity* other) {}

void Separity::Behaviour::onCollisionExit(Entity* other) {}

void Separity::Behaviour::onCollisionStay(Entity* other) {}