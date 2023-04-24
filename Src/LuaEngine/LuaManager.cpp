#include "LuaManager.h"

#include "ManagerManager.h"

#include "Transform.h"
#include "Entity.h"
#include "Behaviour.h"


#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <iostream>

template<typename T>
std::unique_ptr<T> Singleton<T>::_INSTANCE_;

Separity::LuaManager* Separity::LuaManager::getInstance() {
	return static_cast<LuaManager*>(instance());
}

void Separity::LuaManager::clean() {

	cmps_.clear();
	// Liberamos el estado de Lua
	lua_close(L_);

	close();
}

Separity::LuaManager::LuaManager() : L_(nullptr) {
	ManagerManager::getInstance()->addManager(_SCRIPT, this);

	initLua();
}

void Separity::LuaManager::initLua() {
	// Creamos el estado de Lua y registramos las clases
	L_ = luaL_newstate();
	if(!L_) {
		// Error: no se pudo crear el estado de Lua
		std::cout << "error al crear el estado de lua" << std::endl;
	}

	luaL_openlibs(L_);

	registerClasses();
}

void Separity::LuaManager::registerClasses() {
	// Registramos la clase base y sus funciones miembro
	luabridge::getGlobalNamespace(L_)
	    .beginClass<Behaviour>("Behaviour")
	    .addFunction("update", &Behaviour::update)
	    .addFunction("start", &Behaviour::start)
	    .addFunction("awake", &Behaviour::awake)
	    .addFunction("onCollisionEnter", &Behaviour::onCollisionEnter)
	    .addFunction("onCollisionExit", &Behaviour::onCollisionExit)
	    .addFunction("onCollisionStay", &Behaviour::onCollisionStay)
	    .addFunction("onButtonClick", &Behaviour::onButtonClick)
	    .addFunction("onButtonReleased", &Behaviour::onButtonReleased)
	    .addFunction("onButtonHover", &Behaviour::onButtonHover)
	    .addFunction("onButtonUnhover", &Behaviour::onButtonUnhover)
	    .addProperty("entity", &Behaviour::ent_)
	    .addProperty("name", &Behaviour::name_)
	    .endClass();
}

bool Separity::LuaManager::loadScript(std::string name, Entity* ent) {
	// Cargamos el script de Lua desde un archivo
	std::string path = "Assets/Scripts/" + name + ".lua";
	if(luaL_dofile(L_, path.c_str()))
		return false;

	// Creamos una instancia de Behaviour y la pasamos al script
	Behaviour* behaviourScript = ent->addComponent<Behaviour>(name);

	//luabridge::push(L_, behaviourScript);
	//lua_setglobal(L_, name.c_str());
	luabridge::setGlobal(L_, behaviourScript, name.c_str());

	// Obtenemos el objeto behaviour desde Lua
	auto behaviourLua =
	    new luabridge::LuaRef(luabridge::getGlobal(L_, (name + "Lua").c_str()));

	behaviourScript->setLuaScript(behaviourLua);

	return true;
}

lua_State* Separity::LuaManager::getLuaState() { return L_; }


