#pragma once
#ifndef __MANAGER_MANAGER_H__
#define __MANAGER_MANAGER_H__

#ifdef _SEPARITY_EXPORT_
#define _SEPARITY_EXPORT_ __declspec(dllexport)
#else
#define _SEPARITY_EXPORT_ __declspec(dllimport)
#endif

#include "Manager.h"

#include <map>
#include <string>

class lua_State;

namespace Separity {

	class CCreator;

	class ManagerManager : public Separity::Manager,
	                       public Singleton<Separity::ManagerManager> {
		friend Singleton<Separity::ManagerManager>;

		public:
		
		void initComponents();

		void update(const uint32_t& deltaTime) override;

		void render() override;

		static ManagerManager* getInstance();

		void addManager(cmpType_type type, Manager* manager);
		Manager* getManager(cmpType_type type);

		int nManagers();

		void clean() override;

		void pseudoClean();

		protected:
		ManagerManager();

		private:
		std::map<cmpType_type, Manager*> managers_;
	};
}  // namespace Separity

#endif __MANAGER_MANAGER_H__