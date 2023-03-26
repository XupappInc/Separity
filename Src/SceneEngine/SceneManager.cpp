﻿#include "SceneManager.h"

#include <iostream>

#include <lua.hpp>

#include "Entity.h"

#include "TransformCreator.h"
#include "MeshRendererCreator.h"


template<typename T>
std::unique_ptr<T> Singleton<T>::_INSTANCE_;

Separity::SceneManager* Separity::SceneManager::getInstance() {
	return static_cast<SceneManager*>(instance());
}

void Separity::SceneManager::update() {}

Separity::SceneManager::~SceneManager() {}

bool Separity::SceneManager::loadScene(const std::string& root) { 

	lua_State* L = luaL_newstate();

	int scriptLoadStatus = luaL_dofile(L, root.c_str());

	// define error reporter for any Lua error
	if(scriptLoadStatus != 0) {
		std::cerr << "[LUA ERROR] " << lua_tostring(L, -1) << std::endl;

		// remove error message from Lua state
		lua_pop(L, 1);
	} 
	else {

		std::cout << "Entidades:\n";
		lua_getglobal(L, "Entities");

		lua_pushnil(L); 
		while(lua_next(L, -2)) {

			if(lua_isstring(L, -2)) {
				std::string entity = lua_tostring(L, -2, NULL);
				std::cout << " " << entity << ":\n";
			}

			if(lua_istable(L, -1)) {

				Entity* entity = new Entity(_grp_GENERAL);

				lua_pushnil(L);  // Poner la primera key en la pila
				while(lua_next(L, -2)) {
				
					if(lua_isstring(L, -2)) {
						std::string component = lua_tostring(L, -2, NULL);
						std::cout << "  " << component << "\n";

						factory_.addComponent(component, L, entity);
					}
					lua_pop(L, 1);
				}
			}
			lua_pop(L, 1);
		}		
	}

	lua_close(L);

	return false; 
}

Separity::SceneManager::SceneManager() { 
	factory_ = CCreatorFactory(); 
	factory_.add("transform", new TransformCreator());
	factory_.add("meshRenderer", new MeshRendererCreator());
}
