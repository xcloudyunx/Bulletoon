#include "CreditScene.h"

Scene* Credit::createScene() {
	return Credit::create();
}

bool Credit::init() {
	if (!Scene::init()) {
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto mapBackground = TMXTiledMap::create(UserDefault::getInstance()->getStringForKey("mapName", "MAZE")+".tmx");
	mapBackground->setLocalZOrder(-2);
	mapBackground->setAnchorPoint(Vec2(0.5, 0.5));
	mapBackground->setPosition(visibleSize/2);
	this->addChild(mapBackground);
	auto background = Sprite::create("background.png");
	mapBackground->setLocalZOrder(-1);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(visibleSize/2);
	this->addChild(background);
	
	auto backButton = Button::create("back.png", "back-s.png");
	backButton->setPosition(Vec2(visibleSize.width/10, visibleSize.height-visibleSize.width/10));
	backButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				if (UserDefault::getInstance()->getStringForKey("sound", "ON") == "ON") {
					SimpleAudioEngine::getInstance()->playEffect("button.mp3", false, 1.0f, 1.0f, 1.0f);
				}
				break;
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->popScene();
				break;
			default:
				break;
		}
	});
	this->addChild(backButton);
				
	auto creditsLabel = Label::createWithTTF("CREDITS", "ArialRoundedMTBold.TTF", 70);
	creditsLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*13/15));
	this->addChild(creditsLabel);
	
	auto gameTitle = Label::createWithTTF("GAME DESIGN", "ArialRoundedMTBold.TTF", 50);
	gameTitle->setPosition(Vec2(visibleSize.width/2, visibleSize.height*2/3));
	this->addChild(gameTitle);
	
	auto gameLabel1 = Label::createWithTTF("YUNGE YU", "ArialRoundedMTBold.TTF", 35);
	gameLabel1->setPosition(Vec2(visibleSize.width/2, visibleSize.height*11/18));
	this->addChild(gameLabel1);
	/*auto gameLabel3 = Label::createWithTTF("yungeyu.com", "ArialRoundedMTBold.TTF", 35);
	gameLabel3->setPosition(Vec2(visibleSize.width/2, visibleSize.height*10/18));
	this->addChild(gameLabel3);*/
	
	auto musicTitle = Label::createWithTTF("MUSIC & SOUND EFFECTS", "ArialRoundedMTBold.TTF", 50);
	musicTitle->setPosition(Vec2(visibleSize.width/2, visibleSize.height/3));
	this->addChild(musicTitle);
	
	auto musicLabel1 = Label::createWithTTF("ERIC MATYAS", "ArialRoundedMTBold.TTF", 35);
	musicLabel1->setPosition(Vec2(visibleSize.width/2, visibleSize.height*5/18));
	this->addChild(musicLabel1);
	auto musicLabel2 = Label::createWithTTF("soundimage.org", "ArialRoundedMTBold.TTF", 35);
	musicLabel2->setPosition(Vec2(visibleSize.width/2, visibleSize.height*4/18));
	this->addChild(musicLabel2);
	
	return true;
}
