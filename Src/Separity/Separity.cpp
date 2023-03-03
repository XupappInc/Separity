// Separity.cpp : Este archivo contiene la función "main". La ejecución del
// programa comienza y termina ahí.
//

#include "RenderEngine.h"
#include "InputManager.h"
#include "MeshRenderer.h"
#include <Ogre.h>

#include <iostream>
using namespace std;
using namespace Separity;
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SeparityRender *s = new SeparityRender();
	s->renderOgre();
	/*MeshRenderer* mr =
	    new MeshRenderer(nullptr, "");*/


	InputManager* inputManger = new InputManager();

	// Bucle principal
	bool quit = false;
	while(!quit) {
		inputManger->update();
		if(inputManger->isKeyDown('q')) {
			quit = true;
		} else {
			if(inputManger->isKeyDown('w')) {
				cout << "Tecla w Pulsada\n";
			}
			if(inputManger->isMouseButtonDown(InputManager::LEFT)) {
				cout << "Click\n";
			}
			if(inputManger->isMouseButtonHeld(InputManager::LEFT)) {
				cout << "Hold\n";
			}
			if(inputManger->isMouseButtonUp(InputManager::LEFT)) {
				cout << "Release\n";
			}
		}
		s->mRoot->renderOneFrame();

	}

	return 0;
}