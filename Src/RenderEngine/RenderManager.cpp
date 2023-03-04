#include "RenderManager.h"

#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreFileSystemLayer.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <OgreConfigFile.h>


template<typename T>
std::unique_ptr<T> Singleton<T>::_INSTANCE_;

Separity::RenderManager::RenderManager() {}

Separity::RenderManager::~RenderManager() {}

void Separity::RenderManager::init() {
	// Tama�o ventana
	screenW_ = 1024;
	screenH_ = 768;

	// Crear raiz de ogre
	ogreRoot_ = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

	// Inicializar SDL
	if(!SDL_WasInit(SDL_INIT_EVERYTHING))
	SDL_InitSubSystem(SDL_INIT_EVERYTHING);


	// Si hay una configuraci�n de antes se utiliza esa y si no se muestra un
	// di�logo para configuraci�n
	// if(!(ogreRoot_->restoreConfig() || ogreRoot_->showConfigDialog(nullptr)))

	
}

void Separity::RenderManager::loadResources() {
	
	Ogre::ConfigFile configFile;
	configFile.load("resources.cfg");
	Ogre::String sec, type, arch;
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;

	// Cargar los recursos

	for(seci = configFile.getSettingsBySection().begin();
	    seci != configFile.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for(i = settings.begin(); i != settings.end(); i++) {
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			    arch, type, sec);
		}
	}

	
	
}

void Separity::RenderManager::render() {}

void Separity::RenderManager::createTestScene() {
	init();
	createSDLWindow();
	loadResources();

	sceneMgr_ = ogreRoot_->createSceneManager();

	// A�adimos la c�mara
	Ogre::Camera* mCamera = sceneMgr_->createCamera("Cam");

	// Configuramos propiedades de la c�mara

	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(10000);
	mCamera->setAutoAspectRatio(true);

	// A�adimos dicha c�mara a un nodo
	Ogre::SceneNode* mCamNode =
	    sceneMgr_->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(mCamera);

	// Posicionamos el nodo
	mCamNode->setPosition(0, 0, 15);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	// Creamos viewport que muestre aquello que ve la c�mara
	Ogre::Viewport* vp = ogreWindow_->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	// A�adimos luz para que no se vea en negro
	Ogre::Light* luz = sceneMgr_->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	// Metemos la luz en un nodo
	Ogre::SceneNode* mLightNode =
	    sceneMgr_->getRootSceneNode()->createChildSceneNode("nLuz");

	mLightNode->attachObject(luz);
	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  // vec3.normalise();
	mLightNode->setPosition(0, 0, 2000);

	// Creamos entidad con mesh de sinbad
	Ogre::SceneNode* nSinbad =
	    sceneMgr_->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* sinbad = sceneMgr_->createEntity("Sinbad.mesh");
	nSinbad->attachObject(sinbad);
}

Separity::RenderManager* Separity::RenderManager::getInstance() {
	return static_cast<Separity::RenderManager*>(instance());
}

void Separity::RenderManager::createSDLWindow() {

	// Crear ventana de SDL	
	sdlWindow_ = SDL_CreateWindow("Separity", SDL_WINDOWPOS_UNDEFINED,
	                              SDL_WINDOWPOS_UNDEFINED, screenW_, screenH_,
	                              SDL_WINDOW_SHOWN);

	// Queremos asignar a la ventana de renderizado la ventana que hemos creado
	// con SDL
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(sdlWindow_, &wmInfo);

	Ogre::NameValuePairList misc;
	misc["externalWindowHandle"] =
	    Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	// Creamos un render system cogiendo el primer renderer de los que hay
	// disponibles
	Ogre::RenderSystem* sys = ogreRoot_->getAvailableRenderers().front();
	ogreRoot_->setRenderSystem(sys);

	// Crear render window de ogre
	ogreWindow_ = ogreRoot_->initialise(false, "Ogre Render");
	ogreWindow_ = ogreRoot_->createRenderWindow("Ogre Render", screenW_,
	                                            screenH_, false, &misc);
}

SDL_Window* Separity::RenderManager::getSDLWindow() { return sdlWindow_; }

Ogre::Root* Separity::RenderManager::getOgreRoot() { return ogreRoot_; }

Ogre::SceneManager* Separity::RenderManager::getSceneManager() {
	return sceneMgr_;
}
