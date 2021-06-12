#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

class Settings : public Scene {
	public:
		static Scene* createScene();

		virtual bool init();
		
		UserDefault* def;
		SimpleAudioEngine* audio;
		
		std::string lives;
		std::string spawn;
		std::string music;
		std::string sound;
		    
		// implement the "static create()" method manually
		CREATE_FUNC(Settings);
};

#endif // __SETTINGS_SCENE_H__
