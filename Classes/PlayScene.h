#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include <string>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player.h"

using namespace cocos2d;
using namespace CocosDenshion;

class Play : public Scene {
	public:
		static Scene* createScene(std::string, std::string, std::string, std::string);

		virtual bool init();
		
		Size visibleSize;
				
		UserDefault* def;
		SimpleAudioEngine* audio;
		
		std::vector<std::unique_ptr<Player>> players;
		
		EventListenerTouchAllAtOnce* touchListener;
		EventListenerPhysicsContact* contactListener;
		
		int time;
		
		bool paused = false;
		
		Button* pauseButton1;
		Button* pauseButton2;
		
		Vector<Node*> pausedActions;
		
		void pause(Ref*, Widget::TouchEventType);
		void resume(Ref*, Widget::TouchEventType);
		void home(Ref*, Widget::TouchEventType);
		void restart(Ref*, Widget::TouchEventType);
		void update(float);
		
		bool finished = false;
    
		// implement the "static create()" method manually
		CREATE_FUNC(Play);
};

#endif // __PLAY_SCENE_H__
