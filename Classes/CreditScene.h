#ifndef __CREDIT_SCENE_H__
#define __CREDIT_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

class Credit : public Scene {
	public:
		static Scene* createScene();

		virtual bool init();
    
		// implement the "static create()" method manually
		CREATE_FUNC(Credit);
};

#endif // __CREDIT_SCENE_H__
