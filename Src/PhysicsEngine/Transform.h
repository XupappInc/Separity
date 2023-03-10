#pragma once
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include "Component.h"
#include "Vector.h"

class btTransform;

namespace Separity {
	class Transform : public Separity::Component {
		public:
		__CMPTYPE_DECL__(Separity::_PHYSICS)
		__CMPID_DECL__(Separity::_TRANSFORM)
		Transform();
		~Transform();
		/// <summary>
		/// El transform de la clase bullet directamente
		/// </summary>
		/// <returns>el btTransform</returns>
		btTransform* getBulletTransform();
		/// <summary>
		/// Setear la posici?n del componente tranform
		/// </summary>
		/// <param name="other">Vector3 de la posici?n</param>
		void setPosition(Spyutils::Vector3 other);
		/// <summary>
		/// Setear la posici?n del componente tranform
		/// </summary>
		/// <param name="x">posici?n x</param>
		/// <param name="y">posici?n y</param>
		/// <param name="z">posici?n z</param>
		void setPosition(float x, float y, float z);
		/// <summary>
		/// Transladar la posici?n del transform
		/// </summary>
		/// <param name="other">Vector3 para transladar</param>
		void translate(Spyutils::Vector3 other);
		/// <summary>
		/// Coger la posici?n del transform
		/// </summary>
		/// <returns></returns>
		Spyutils::Vector3 getPosition();
		/// <summary>
		/// Setetar l posici?n del transform.
		/// </summary>
		/// <param name="rotationX">grados del eje x</param>
		/// <param name="rotationY">grados eje y</param>
		/// <param name="rotationZ">grados de ejez</param>
		void setRotation(float rotationX, float rotationY, float rotationZ);
		/// <summary>
		/// geter de la rotaci?n en un Vector3
		/// </summary>
		/// <returns></returns>
		Spyutils::Vector3 getRotation();
		/// <summary>
		/// Rotacion en el eje x
		/// </summary>
		/// <param name="degree">grados a girar</param>
		void pitch(float degree);
		/// <summary>
		/// Rotacion en el eje y
		/// </summary>
		/// <param name="degree">grados a girar</param>
		void yaw(float degree);
		/// <summary>
		/// Rotacion en el eje z
		/// </summary>
		/// <param name="degree">grados a girar</param>
		void roll(float degree);
		/// <summary>
		/// setear la escala del transform
		/// </summary>
		/// <param name="scaleX">float para escalar del eje x</param>
		/// <param name="scaleY">float para escalar del eje y</param>
		/// <param name="scaleZ">float para escalar del eje z</param>
		void setScale(float scaleX, float scaleY, float scaleZ);
		/// <summary>
		/// setear la escala del transform
		/// </summary>
		/// <param name="scale">float para escalar el eje x y z</param>
		void setScale(float scale);
		/// <summary>
		/// geter de la escala del transform
		/// </summary>
		/// <returns></returns>
		Spyutils::Vector3 getScale();

		private:
		btTransform* tr_;
		Spyutils::Vector3 positition_;
		Spyutils::Vector3 rotation_;
		Spyutils::Vector3 scale_;
	};
}  // namespace Separity
#endif __TRANSFORM_H__