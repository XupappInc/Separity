#include "MeshRendererCreator.h"

#include "Entity.h"
#include "MeshRenderer.h"

#include "RenderManager.h"

#include <lua.hpp>
#include <iostream>

Separity::MeshRendererCreator::MeshRendererCreator() {}

void Separity::MeshRendererCreator::registerInLua() {}

void Separity::MeshRendererCreator::createComponent(lua_State* L,
                                                 Separity::Entity* ent) {


	lua_getfield(L, -1, "meshName");
	std::string s = lua_tostring(L, -1);
	s += ".mesh";
	lua_pop(L, 1);

	MeshRenderer* mesh = ent->addComponent<MeshRenderer>(
	    Separity::RenderManager::getInstance()->getSceneManager(), s);

	lua_getfield(L, -1, "textureName");
	s = lua_tostring(L, -1);
	lua_pop(L, 1);

	mesh->setTexture(s);
}
