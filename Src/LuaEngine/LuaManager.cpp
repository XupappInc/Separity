#include "LuaManager.h"

#include "Behaviour.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "Entity.h"
#include "Transform.h"
//#include "RigidBody.h"

#include <iostream>

template<typename T>
std::unique_ptr<T> Singleton<T>::_INSTANCE_;

void Separity::LuaManager::initLua() {
	// Creamos el estado de Lua y registramos las clases
	L_ = luaL_newstate();
	if(!L_) {
		// Error: no se pudo crear el estado de Lua
		std::cout << "error al crear el estado de lua" << std::endl;
	}

	luaL_openlibs(L_);

	// Registramos la clase base y sus funciones miembro
	luabridge::getGlobalNamespace(L_)
	    .beginClass<Behaviour>("Behaviour")
	    .addFunction("update", &Behaviour::update)
	    .addProperty("transform_", &Behaviour::transform_)
	    //.addProperty("rigidbody", &Behaviour::rigidBody_)
	    .endClass();

	registerClasses();
}

void Separity::LuaManager::registerClasses() {
	/*luabridge::getGlobalNamespace(L_)
	    .beginClass<Entity>("Entity")
	    .addFunction("getComponent", &Entity::getComponent)
	    .endClass();*/
	luabridge::getGlobalNamespace(L_)
	    .beginClass<Transform>("Transform")
	    .addFunction("translate", &Transform::translate)
	    .addFunction("print", &Transform::print)
	    .addFunction("pitch", &Transform::pitch)
	    .addFunction("yaw", &Transform::yaw)
	    .addFunction("roll", &Transform::roll)
	    .endClass();

	//luabridge::getGlobalNamespace(L_)
	//    .beginClass<RigidBody>("RigidBody")
	//    .addFunction("addForce", &RigidBody::addForce)
	//    .addFunction("clearForces", &RigidBody::clearForces)
	//    .addFunction("setLinearVelocity", &RigidBody::setLinearVelocity)
	//    .endClass();
}

void Separity::LuaManager::loadScript(std::string name, Entity* ent) {
	// Cargamos el script de Lua desde un archivo
	std::string path = "Assets/Scripts/" + name + ".lua";
	luaL_dofile(L_, path.c_str());

	// Creamos una instancia de Behaviour y la pasamos al script
	Behaviour* behaviourScript = ent->addComponent<Behaviour>();

	behaviourScript->initComponent();

	luabridge::push(L_, behaviourScript);
	lua_setglobal(L_, name.c_str());

	// Obtenemos el objeto behaviour desde Lua
	auto behaviourLua =
	    new luabridge::LuaRef(luabridge::getGlobal(L_, (name + "Lua").c_str()));

	behaviourScript->setLuaScript(behaviourLua);

	cmps_.push_back(behaviourScript);
}

Separity::LuaManager* Separity::LuaManager::getInstance() {
	return static_cast<LuaManager*>(instance());
}

Separity::LuaManager::LuaManager() : L_(nullptr) {}

Separity::LuaManager::~LuaManager() {
	for(auto c : cmps_) delete c;

	cmps_.clear();
	
	// Liberamos el estado de Lua
	lua_close(L_);
}
