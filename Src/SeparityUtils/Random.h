#pragma once
#ifndef __RANDOM_H__
#define __RANDOM_H__

#ifdef _SEPARITY_EXPORT_
#define _SEPARITY_EXPORT_ __declspec(dllexport)
#else
#define _SEPARITY_EXPORT_ __declspec(dllimport)
#endif

namespace Spyutils {
	/// <summary>
	/// Clase para generar n�meros aleatorios
	/// </summary>
	class Random {
		public:
		Random();
		~Random();
		/// <summary>
		/// Devuelve un n�mero entero aleatorio
		/// </summary>
		/// <returns>N�mero entero aleatorio</returns>
		int randInt();
		/// <summary>
		/// Devuelve un n�mero entero aleatorio entre min (inclusive) y max (inclusive)
		/// </summary>
		/// <param name="min">M�nimo n�mero que puede devolver</param>
		/// <param name="max">M�ximo n�mero que puede devolver</param>
		/// <returns>N�mero entero aleatorio</returns>
		int randInt(int min, int max);
		/// <summary>
		/// Devuelve un float aleatorio
		/// </summary>
		/// <returns>Float aleatorio</returns>
		float randFloat();
		/// <summary>
		/// Devuelve un float aleatorio entre min (inclusive) y max
		/// (inclusive)
		/// </summary>
		/// <param name="min">M�nimo n�mero que puede devolver</param>
		/// <param name="max">M�ximo n�mero que puede devolver</param>
		/// <returns>Float aleatorio</returns>
		float randFloat(float min, float max);		
	};
}


#endif  // __RANDOM_H__