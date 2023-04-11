#pragma once
#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__
#include "Manager.h"
// #include <array>
#include "Entity.h"

#include <vector>
namespace Separity {

	class EntityManager : public Separity::Manager,
	                      public Singleton<Separity::EntityManager> {
		friend Singleton<Separity::EntityManager>;

		public:
		/// <summary>
		/// Contructor por defecto de la clase
		/// </summary>
		inline EntityManager();
		/// <summary>
		/// Destructor por defecto de la clase
		/// </summary>
		virtual ~EntityManager();
		/// <summary>
		/// M�todo que devuelve una instancia de si mismo, es decir
		/// EntityManager, si ya existiera devuelve dicha instancia, si no
		/// existiera a�n devuelve una nueva instancia
		/// </summary>
		/// <returns>Instancia de EntityManager</returns>
		static EntityManager* getInstance();
		/// <summary>
		/// A�ade una entidad al registro del manager
		/// </summary>
		/// <params>Acepta una lista de argumentos (si hay) para ser pasados al
		/// constructor (Id del grupo).</params>
		Entity* addEntity(grpId_type gID) {
			// constexpr
			grpId_type gId = gID;
			// constexpr hdlrId hdlrId = T::;
			assert(gId < Separity::maxGroupId);
			// crea, inicializa y a�ade la entidad
			Entity* e = new Entity(gId);
			e->setContext(this);
			allEntities_.push_back(e);
			// entsByGroup_[gId] = e;
			return e;
		}
		/// <summary>
		/// Usado por el singleton. Actualmente no inicaliza nada
		/// </summary>
		void init();
		/// <summary>
		/// Borra todas las entidades que hay guardadas en el vector llamando a
		/// su destructor
		/// </summary>
		void deleteEntities();

		std::vector<Entity*> allEntities_;
	};
}  // namespace Separity
#endif __ENTITY_MANAGER_H__