#include "ComponentFactory.h"

#include "CCreator.h"

#include <iostream>

Separity::ComponentFactory::ComponentFactory() {

	creators_ = std::unordered_map<std::string, CCreator*>();
}

Separity::ComponentFactory::~ComponentFactory() {
	for(auto cc : creators_) 
		delete cc.second;
}

bool Separity::ComponentFactory::createComponent(const std::string& CName,
                                             lua_State* L,
                                             Separity::Entity* ent) {

	if(!creators_.count(CName)) {
		std::cerr << "El componente " << CName << " no existe\n";
		return false;

	} else {
		return creators_[CName]->createComponent(L, ent);
	}
}

void Separity::ComponentFactory::addCreator(const std::string& CName,
                                    CCreator* CCreator) {
	creators_[CName] = CCreator;
	CCreator->registerInLua();
}