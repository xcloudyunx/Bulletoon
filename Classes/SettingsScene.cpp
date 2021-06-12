#include "SettingsScene.h"
#include "CreditScene.h"

Scene* Settings::createScene() {
	return Settings::create();
}

bool Settings::init() {
	if (!Scene::init()) {
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	def = UserDefault::getInstance();
	audio = SimpleAudioEngine::getInstance();
	
	auto mapBackground = TMXTiledMap::create(def->getStringForKey("mapName", "MAZE")+".tmx");
	mapBackground->setLocalZOrder(-2);
	mapBackground->setAnchorPoint(Vec2(0.5, 0.5));
	mapBackground->setPosition(visibleSize/2);
	this->addChild(mapBackground);
	auto background = Sprite::create("background.png");
	background->setLocalZOrder(-1);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(visibleSize/2);
	this->addChild(background);
	
	auto backButton = Button::create("back.png", "back-s.png");
	backButton->setPosition(Vec2(visibleSize.width/10, visibleSize.height-visibleSize.width/10));
	backButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false, 1.0f, 1.0f, 1.0f);
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
	
	auto settingsLabel = Label::createWithTTF("SETTINGS", "ArialRoundedMTBold.TTF", 70);
	settingsLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*14/15));
	this->addChild(settingsLabel);
	
	lives = def->getStringForKey("lives", "1");
	
	auto livesButton = Button::create("text.png", "text-s.png");
	livesButton->setTitleText("LIVES: " + lives);
	livesButton->setTitleFontSize(50);
	livesButton->setTitleFontName("ArialRoundedMTBold.TTF");	
	livesButton->setTitleColor(Color3B(255, 255, 255));
	livesButton->getTitleRenderer()->enableShadow();
	livesButton->setPosition(Vec2(visibleSize.width/2, visibleSize.height*19/24));
	livesButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				livesButton->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false, 1.0f, 1.0f, 1.0f);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				livesButton->setTitleColor(Color3B(255, 255, 255));
				break;
			case Widget::TouchEventType::ENDED:
				livesButton->setTitleColor(Color3B(255, 255, 255));
				if (lives == "1") {
					lives = "5";
				} else if (lives == "5") {
					lives = "10";
				} else if (lives == "10") {
					lives = "1";
				}
				livesButton->setTitleText("LIVES: " + lives);
				def->setStringForKey("lives", lives);
				def->flush();
				break;
			default:
				break;
		}
	});
	this->addChild(livesButton);
	
	spawn = def->getStringForKey("spawn", "3");
	
	auto spawnButton = Button::create("text.png", "text-s.png");
	spawnButton->setTitleText("SPAWN TIME: " + spawn);
	spawnButton->setTitleFontSize(35);
	spawnButton->setTitleFontName("ArialRoundedMTBold.TTF");	
	spawnButton->setTitleColor(Color3B(255, 255, 255));
	spawnButton->getTitleRenderer()->enableShadow();
	spawnButton->setPosition(Vec2(visibleSize.width/2, visibleSize.height*31/48));
	spawnButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				spawnButton->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false, 1.0f, 1.0f, 1.0f);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				spawnButton->setTitleColor(Color3B(255, 255, 255));
				break;
			case Widget::TouchEventType::ENDED:
				spawnButton->setTitleColor(Color3B(255, 255, 255));
				if (spawn != "5") {
					spawn = std::to_string(std::atoi(spawn.c_str()) + 1);
				} else {
					spawn = "0";
				}
				spawnButton->setTitleText("SPAWN TIME: " + spawn);
				def->setStringForKey("spawn", spawn);
				def->flush();
				break;
			default:
				break;
		}
	});
	this->addChild(spawnButton);
	
	music = def->getStringForKey("music", "ON");

	auto musicButton = Button::create("text.png", "text-s.png", "text-d.png");
	musicButton->setTitleText("MUSIC");
	musicButton->setTitleFontSize(50);
	musicButton->setTitleFontName("ArialRoundedMTBold.TTF");	
	musicButton->getTitleRenderer()->enableShadow();
	musicButton->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	if (music == "ON") {
		musicButton->setTitleColor(Color3B(255, 255, 255));
	} else {
		musicButton->setBright(false);
		musicButton->setTitleColor(Color3B(0, 0, 0));
	}
	musicButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				musicButton->setBrightStyle(BrightStyle::HIGHLIGHT);
				musicButton->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false, 1.0f, 1.0f, 1.0f);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				musicButton->setTitleColor(Color3B(255, 255, 255));
				break;
			case Widget::TouchEventType::ENDED:
				if (music == "ON") {
					musicButton->setBright(false);
					musicButton->setTitleColor(Color3B(0, 0, 0));
					music = "OFF";
					audio->stopBackgroundMusic();
				} else if (music == "OFF") {
					musicButton->setBright(true);
					musicButton->setTitleColor(Color3B(255, 255, 255));
					music = "ON";
					audio->playBackgroundMusic("start.mp3", true);
				}
				def->setStringForKey("music", music);
				def->flush();
				break;
			default:
				break;
		}
	});
	this->addChild(musicButton);
	
	sound = def->getStringForKey("sound", "ON");
	
	auto soundButton = Button::create("text.png", "text-s.png", "text-d.png");
	soundButton->setTitleText("SOUND");
	soundButton->setTitleFontSize(50);
	soundButton->setTitleFontName("ArialRoundedMTBold.TTF");
	soundButton->getTitleRenderer()->enableShadow();
	if (sound == "ON") {
		soundButton->setTitleColor(Color3B(255, 255, 255));
	} else {
		soundButton->setBright(false);
		soundButton->setTitleColor(Color3B(0, 0, 0));
	}
	soundButton->setPosition(Vec2(visibleSize.width/2, visibleSize.height*17/48));
	soundButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				soundButton->setBrightStyle(BrightStyle::HIGHLIGHT);
				soundButton->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "OFF") {
					audio->playEffect("button.mp3", false, 1.0f, 1.0f, 1.0f);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				soundButton->setTitleColor(Color3B(255, 255, 255));
				break;
			case Widget::TouchEventType::ENDED:
				if (sound == "ON") {
					soundButton->setBright(false);
					soundButton->setTitleColor(Color3B(0, 0, 0));
					sound = "OFF";
				} else if (sound == "OFF") {
					soundButton->setBright(true);
					soundButton->setTitleColor(Color3B(255, 255, 255));
					sound = "ON";
				}
				def->setStringForKey("sound", sound);
				def->flush();
				break;
			default:
				break;
		}
	});
	this->addChild(soundButton);
	
	auto creditButton = Button::create("text.png", "text-s.png");
	creditButton->setTitleText("CREDITS");
	creditButton->setTitleFontSize(50);
	creditButton->setTitleFontName("ArialRoundedMTBold.TTF");
	creditButton->getTitleRenderer()->enableShadow();
	creditButton->setPosition(Vec2(visibleSize.width/2, visibleSize.height*5/24));
	creditButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				creditButton->setBrightStyle(BrightStyle::HIGHLIGHT);
				creditButton->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false, 1.0f, 1.0f, 1.0f);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				creditButton->setTitleColor(Color3B(255, 255, 255));
				break;
			case Widget::TouchEventType::ENDED: {
				creditButton->setTitleColor(Color3B(255, 255, 255));
				auto scene = Credit::createScene();
				Director::getInstance()->pushScene(scene);
				break;
			}
			default:
				break;
		}
	});
	this->addChild(creditButton);
	
	return true;
}