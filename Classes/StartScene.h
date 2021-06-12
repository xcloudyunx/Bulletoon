#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"
#include "SettingsScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

class Start : public Scene {
	public:
		static Scene* createScene();

		virtual bool init();
		
		Size visibleSize;
		
		UserDefault* def;
		SimpleAudioEngine * audio;
		
		std::string oneText;
		std::string twoText;
		std::string threeText;
		std::string fourText;
		
		bool begin;
		
		Button* oneplus;
		Button* twoplus;
		Button* threeplus;
		Button* fourplus;
		Button* start;
		Button* settings;
		
		TMXTiledMap* mapBackground;
		std::string mapName;
		Button* map;
    
		// implement the "static create()" method manually
		CREATE_FUNC(Start);
	private:
		virtual void onEnter() override;
};

#endif // __START_SCENE_H__
