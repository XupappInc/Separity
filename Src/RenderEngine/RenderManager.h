#pragma once
#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__
#include "Manager.h"
class RenderManager/* : Manager*/ {
	public:
	inline RenderManager();
	virtual ~RenderManager();

	/// <summary>
	/// M�todo encargado de renderizar todos los componentes
	/// dentro de la lista de componentes
	/// </summary>
	void render();
};
#endif __RENDER_MANAGER_H__
