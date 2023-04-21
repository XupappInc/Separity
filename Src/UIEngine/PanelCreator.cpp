#include "PanelCreator.h"

#include "Panel.h"
#include "Entity.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "LuaManager.h"

Separity::PanelCreator::PanelCreator() {}

void Separity::PanelCreator::registerInLua() {
	lua_State* L = Separity::LuaManager::getInstance()->getLuaState();
	luabridge::getGlobalNamespace(L).beginClass<Panel>("panel").endClass();
}

void Separity::PanelCreator::createComponent(lua_State* L,
                                             Separity::Entity* ent) {
	int x, y, width, height;
	std::string material, name;

	readParam("name", L, name);
	readParam("x", L, x);
	readParam("y", L, y);
	readParam("width", L, width);
	readParam("height", L, height);
	readParam("material", L, material);

	ent->addComponent<Panel>(name, x, y, width, height, material);
}
