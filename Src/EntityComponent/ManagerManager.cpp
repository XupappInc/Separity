#include "ManagerManager.h"

std::unique_ptr<Separity::ManagerManager>
    Singleton<Separity::ManagerManager>::_INSTANCE_;

Separity::ManagerManager* Separity::ManagerManager::getInstance() {
	return static_cast<ManagerManager*>(instance());
}

void Separity::ManagerManager::initComponents() {
	for(auto m : managers_) {
		m.second->initComponents();
	}
}

void Separity::ManagerManager::update(const uint32_t& deltaTime) {
	for(auto m : managers_) {
		m.second->update(deltaTime);
	}
}

void Separity::ManagerManager::render() {
	for(auto m : managers_) {
		m.second->render();
	}
}

Separity::ManagerManager::ManagerManager() : quit_(false) {
	managers_ = std::map<cmpType_type, Manager*>();
}

void Separity::ManagerManager::addManager(cmpType_type type, Manager* manager) {
	managers_[type] = manager;
}

Separity::Manager* Separity::ManagerManager::getManager(cmpType_type type) {
	return managers_[type];
}

void Separity::ManagerManager::clean() {
	for(auto m : managers_) {
		m.second->clean();
	}
	close();
}

void Separity::ManagerManager::initManagers() {
	for(auto m : managers_) {
		
	}
}

bool Separity::ManagerManager::quit() { return quit_; }

void Separity::ManagerManager::shutDown() { quit_ = true; }

void Separity::ManagerManager::pseudoClean() {
	for(auto m = managers_.begin(); m != managers_.end();) {
		if(m->first != _SCENE && m->first != _INPUT && m->first != _RENDER) {
			auto aux = m;
			aux++;
			m->second->clean();
			managers_.erase(m);
			m = aux;
		} else {
			m++;
		}
	}
	//for(auto m = managers_.begin(); m != managers_.end();) {
	//	m->second->reset();
	//	m++;
	//}
}
