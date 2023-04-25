#pragma once
#ifndef __VEHICLE_MOVEMENT_H__
#define __VEHICLE_MOVEMENT_H__
#include "PhysicsComponent.h"
#include "SeparityApi.h"

namespace Spyutils {
	class Vector3;
}

class btDynamicsWorld;
class btRaycastVehicle;
class btVehicleRaycaster;
namespace Separity {
	class RigidBody;
	/// <summary>
	/// Componente rigidbody
	/// </summary>
	class _SEPARITY_API_ VehicleMovement : public Separity::PhysicsComponent {
		public:
		__CMPTYPE_DECL__(Separity::_PHYSICS)
		__CMPID_DECL__(Separity::_VEHICLE_MOVEMENT)

		VehicleMovement();
		~VehicleMovement();

		void initComponent() override;
		/// <summary>
		/// A�ade giro al volante
		/// </summary>
		/// <param name="dir">Entre -1 y 1, siendo -1 izquierda y 1
		/// derecha</param>
		void girar(int dir);
		/// <summary>
		/// Acelera hacia delante o hacia atr�s
		/// <param name="dir">Entre -1 y 1, siendo -1 atr�s y 1 adelante</param>
		/// </summary>
		void acelerar(int dir);
		/// <summary>
		/// Gestiona el freno del veh�culo
		/// </summary>
		void frenar();
		/// <summary>
		/// M�todo update heredado de Component
		/// </summary>
		void update(const uint32_t& deltaTime) override;

		private:
		float mass_;
		btDynamicsWorld* world_;
		RigidBody* rb_;
		btRaycastVehicle* vehicle_;
		btVehicleRaycaster* vehicleRayCaster_;
	
		bool rotando_ = false;
	};
}  // namespace Separity
#endif __VEHICLE_MOVEMENT_H__