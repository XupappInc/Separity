#pragma once
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include "Component.h"
#include "Vector.h"
#include <vector>
namespace Ogre {
	class SceneManager;
	class SceneNode;
}  // namespace Ogre

namespace Separity {
	class Transform : public Separity::Component {
		public:
		__CMPTYPE_DECL__(Separity::_TRANSFORM_COMPONENT)
		__CMPID_DECL__(Separity::_TRANSFORM)
		Transform();
		std::vector<std::vector<float>>calculateRotationMatrix(Spyutils::Vector3 rotation);
		
		~Transform();
		/// <summary>
		/// Setear la posici�n del componente tranform
		/// </summary>
		/// <param name="other">Vector3 de la posici�n</param>
		void setPosition(Spyutils::Vector3 other);
		/// <summary>
		/// Setear la posici�n del componente tranform
		/// </summary>
		/// <param name="x">posici�n x</param>
		/// <param name="y">posici�n y</param>
		/// <param name="z">posici�n z</param>
		void setPosition(float x, float y, float z);
		/// <summary>
		/// Transladar la posici�n del transform
		/// </summary>
		/// <param name="other">Vector3 para transladar</param>
		void translate(Spyutils::Vector3 other);
		/// <summary>
		/// Coger la posici�n del transform
		/// </summary>
		/// <returns></returns>
		Spyutils::Vector3 getPosition();
		/// <summary>
		/// Setetar l posici�n del transform.
		/// </summary>
		/// <param name="rotationX">grados del eje x</param>
		/// <param name="rotationY">grados eje y</param>
		/// <param name="rotationZ">grados de ejez</param>
		void setRotation(float rotationX, float rotationY, float rotationZ);
		/// <summary>
		/// geter de la rotaci�n en un Vector3
		/// </summary>
		/// <returns></returns>
		Spyutils::Vector3 getRotation();
		/// <summary>
		/// geter de la rotaci�n en un Vector3 globales
		/// </summary>
		/// <returns></returns>
		Spyutils::Vector3 getRotationGlobal();
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
		Spyutils::Vector3 rotar(Spyutils::Vector3 posicion,
		                        Spyutils::Vector3 anclaje,
		           Spyutils::Vector3 rotacion);
		Spyutils::Vector3 position_;
		Spyutils::Vector3 rotation_;
		Spyutils::Vector3 scale_;
		void getEulerAngles(float R[3][3], float& pitch, float& yaw,
		                    float& roll);
		
	};

}  // namespace Separity
#endif __TRANSFORM_H__