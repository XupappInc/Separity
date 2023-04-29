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
	for(auto m : managers_) {
		m.second->startComponent();
	}
}

void Separity::ManagerManager::start() {
	for(auto m : managers_) {
		m.second->start();
	}
}

void Separity::ManagerManager::update(const uint32_t& deltaTime) {
	for(auto m : managers_) {
		m.second->update(deltaTime);
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
	// close();
}

void Separity::ManagerManager::initManagers() {
	for(auto m : managers_) {
	}
}

bool Separity::ManagerManager::quit() { return quit_; }

void Separity::ManagerManager::shutDown() { quit_ = true; }
