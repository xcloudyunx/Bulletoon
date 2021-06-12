#include "StartScene.h"

Scene* Start::createScene() {
    return Start::create();
}

bool Start::init() {
	if (!Scene::init()) {
        return false;
    }
	
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	def = UserDefault::getInstance();
	audio = SimpleAudioEngine::getInstance();
	audio->setEffectsVolume(1.0);
	
	oneText = "+";
	auto one = Sprite::create("p1.png");
	one->setAnchorPoint(Vec2(0, 0));
	one->setPosition(Vec2(0, 0));
	oneplus = Button::create("button.png", "button-s.png");
	oneplus->setPosition(one->getBoundingBox().size*7/15);
	oneplus->setTitleText(oneText);
	oneplus->setTitleFontSize(40);
	oneplus->setTitleFontName("ArialRoundedMTBold.TTF");
	oneplus->setTitleColor(Color3B(255, 255, 255));
	oneplus->getTitleRenderer()->enableShadow();
	oneplus->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				oneplus->setBrightStyle(BrightStyle::HIGHLIGHT);
				oneplus->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				oneplus->setTitleColor(Color3B(255, 255, 255));\
				break;
			case Widget::TouchEventType::ENDED:
				if (oneText == "+") {
					oneText = "-";
				} else {
					oneText = "+";
				}
				oneplus->setTitleText(oneText);
				oneplus->setTitleColor(Color3B(255, 255, 255));
				break;
			default:
				break;
		}
	});
	this->addChild(one);
	one->addChild(oneplus);
	
	twoText = "+";
	auto two = Sprite::create("p2.png");
	two->setAnchorPoint(Vec2(0, 1));
	two->setPosition(Vec2(0, visibleSize.height));
	twoplus = Button::create("button.png", "button-s.png");
	twoplus->setPosition(Vec2(two->getBoundingBox().size.width*7/15, two->getBoundingBox().size.height*8/15));
	twoplus->setRotation(180);
	twoplus->setTitleText(twoText);
	twoplus->setTitleFontSize(40);
	twoplus->setTitleFontName("ArialRoundedMTBold.TTF");
	twoplus->setTitleColor(Color3B(255, 255, 255));
	twoplus->getTitleRenderer()->enableShadow();
	twoplus->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				twoplus->setBrightStyle(BrightStyle::HIGHLIGHT);
				twoplus->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				twoplus->setTitleColor(Color3B(255, 255, 255));\
				break;
			case Widget::TouchEventType::ENDED:
				if (twoText == "+") {
					twoText = "-";
				} else {
					twoText = "+";
				}
				twoplus->setTitleText(twoText);
				twoplus->setTitleColor(Color3B(255, 255, 255));
				break;
			default:
				break;
		}
	});
	this->addChild(two);
	two->addChild(twoplus);
	
	threeText = "+";
	auto three = Sprite::create("p3.png");
	three->setAnchorPoint(Vec2(1, 1));
	three->setPosition(visibleSize);
	threeplus = Button::create("button.png", "button-s.png");
	threeplus->setPosition(three->getBoundingBox().size*8/15);
	threeplus->setRotation(180);
	threeplus->setTitleText(threeText);
	threeplus->setTitleFontSize(40);
	threeplus->setTitleFontName("ArialRoundedMTBold.TTF");
	threeplus->setTitleColor(Color3B(255, 255, 255));
	threeplus->getTitleRenderer()->enableShadow();
	threeplus->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				threeplus->setBrightStyle(BrightStyle::HIGHLIGHT);
				threeplus->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				threeplus->setTitleColor(Color3B(255, 255, 255));\
				break;
			case Widget::TouchEventType::ENDED:
				if (threeText == "+") {
					threeText = "-";
				} else {
					threeText = "+";
				}
				threeplus->setTitleText(threeText);
				threeplus->setTitleColor(Color3B(255, 255, 255));
				break;
			default:
				break;
		}
	});
	this->addChild(three);
	three->addChild(threeplus);
	
	fourText = "+";
	auto four = Sprite::create("p4.png");
	four->setAnchorPoint(Vec2(1, 0));
	four->setPosition(Vec2(visibleSize.width, 0));
	fourplus = Button::create("button.png", "button-s.png");
	fourplus->setPosition(Vec2(four->getBoundingBox().size.width*8/15, four->getBoundingBox().size.height*7/15));
	fourplus->setTitleText(fourText);
	fourplus->setTitleFontSize(40);
	fourplus->setTitleFontName("ArialRoundedMTBold.TTF");
	fourplus->setTitleColor(Color3B(255, 255, 255));
	fourplus->getTitleRenderer()->enableShadow();
	fourplus->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				fourplus->setBrightStyle(BrightStyle::HIGHLIGHT);
				fourplus->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				fourplus->setTitleColor(Color3B(255, 255, 255));\
				break;
			case Widget::TouchEventType::ENDED:
				if (fourText == "+") {
					fourText = "-";
				} else {
					fourText = "+";
				}
				fourplus->setTitleText(fourText);
				fourplus->setTitleColor(Color3B(255, 255, 255));
				break;
			default:
				break;
		}
	});
	this->addChild(four);
	four->addChild(fourplus);
		
	start = Button::create("text.png", "text-s.png", "text-d.png");
	start->setTitleText("START");
	start->setTitleFontSize(50);
	start->setTitleFontName("ArialRoundedMTBold.TTF");	
	start->setTitleColor(Color3B(255, 255, 255));
	start->getTitleRenderer()->enableShadow();
	start->setPosition(Vec2(visibleSize.width/2, visibleSize.height*5/8));
	start->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				start->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				start->setTitleColor(Color3B(255, 255, 255));
				break;
			case Widget::TouchEventType::ENDED: {
				start->setTitleColor(Color3B(255, 255, 255));
				if ((oneText == "-" && (twoText == "-" || threeText == "-" || fourText == "-")) || (twoText == "-" && (threeText == "-" || fourText == "-")) || (threeText == "-" && fourText=="-")){
					audio->stopBackgroundMusic();
					auto scene = Play::createScene(oneText, twoText, threeText, fourText);
					Director::getInstance()->pushScene(scene);
				} else {
					auto errorPlayer1 = Label::createWithTTF("YOU NEED AT LEAST 2 PLAYERS", "ArialRoundedMTBold.TTF", 20);
					errorPlayer1->setPosition(Vec2(visibleSize.width/20, visibleSize.height/2));
					errorPlayer1->setRotation(90);
					this->addChild(errorPlayer1);
					auto errorPlayer2 = Label::createWithTTF("YOU NEED AT LEAST 2 PLAYERS", "ArialRoundedMTBold.TTF", 20);
					errorPlayer2->setPosition(Vec2(visibleSize.width*19/20, visibleSize.height/2));
					errorPlayer2->setRotation(270);
					this->addChild(errorPlayer2);
					
					errorPlayer1->runAction(FadeOut::create(1));
					errorPlayer2->runAction(FadeOut::create(1));
				}
				break;
			}
			default:
				break;
		}
	});
	this->addChild(start);
	
	settings = Button::create("text.png", "text-s.png");
	settings->setTitleText("SETTINGS");
	settings->setTitleFontSize(50);
	settings->setTitleFontName("ArialRoundedMTBold.TTF");	
	settings->setTitleColor(Color3B(255, 255, 255));
	settings->getTitleRenderer()->enableShadow();
	settings->setPosition(Vec2(visibleSize/2));
	settings->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				settings->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				settings->setTitleColor(Color3B(255, 255, 255));\
				break;
			case Widget::TouchEventType::ENDED: {
				settings->setTitleColor(Color3B(255, 255, 255));
				auto scene = Settings::createScene();
				Director::getInstance()->pushScene(scene);
				break;
			}
			default:
				break;
		}
	});
	this->addChild(settings);
	
	mapName = def->getStringForKey("mapName", "MAZE");
	
	mapBackground = TMXTiledMap::create(mapName+".tmx");
	mapBackground->setLocalZOrder(-1);
	mapBackground->setAnchorPoint(Vec2(0.5, 0.5));
	mapBackground->setPosition(visibleSize/2);
	this->addChild(mapBackground);
	auto background = Sprite::create("background.png");
	background->setLocalZOrder(-2);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(visibleSize/2);
	this->addChild(background);
	
	
	map = Button::create("text.png", "text-s.png");
	map->setTitleText(mapName);
	map->setTitleFontSize(50);
	map->setTitleFontName("ArialRoundedMTBold.TTF");	
	map->setTitleColor(Color3B(255, 255, 255));
	map->getTitleRenderer()->enableShadow();
	map->setPosition(Vec2(visibleSize.width/2, visibleSize.height*3/8));
	map->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				map->setTitleColor(Color3B(0, 62, 110));
				if (def->getStringForKey("sound", "ON") == "ON") {
					audio->playEffect("button.mp3", false);
				}
				break;
			case Widget::TouchEventType::CANCELED:
				map->setTitleColor(Color3B(255, 255, 255));\
				break;
			case Widget::TouchEventType::ENDED:
				map->setTitleColor(Color3B(255, 255, 255));
				if (mapName == "MAZE") {
					mapName = "BOX";
				} else if (mapName == "BOX") {
					mapName = "FORTRESS";
				} else if (mapName == "FORTRESS") {
					mapName = "CORNER";
				} else if (mapName == "CORNER") {
					mapName = "OPEN";
				} else if (mapName == "OPEN") {
					mapName = "MAZE";
				}
				mapBackground->removeFromParentAndCleanup(true);
				mapBackground = TMXTiledMap::create(mapName+".tmx");
				mapBackground->setLocalZOrder(-1);
				mapBackground->setAnchorPoint(Vec2(0.5, 0.5));
				mapBackground->setPosition(visibleSize/2);
				this->addChild(mapBackground);
				
				map->setTitleText(mapName);
				def->setStringForKey("mapName", mapName);
				def->flush();
				
				break;
			default:
				break;
		}
	});
	this->addChild(map);
	
	return true;
}

void Start::onEnter() {
	if (def->getBoolForKey("new")) {
		auto loadScreen = Sprite::create("load.png");
		loadScreen->setPosition(visibleSize/2);
		loadScreen->setName("loadScreen");
		this->addChild(loadScreen);
		def->setBoolForKey("new", false);
		def->flush();
		
		oneplus->setEnabled(false);
		twoplus->setEnabled(false);
		threeplus->setEnabled(false);
		fourplus->setEnabled(false);
		start->setEnabled(false);
		settings->setEnabled(false);
		map->setEnabled(false);
		
		this->scheduleOnce([&](float dt) {
			oneplus->setEnabled(true);
			twoplus->setEnabled(true);
			threeplus->setEnabled(true);
			fourplus->setEnabled(true);
			start->setEnabled(true);
			settings->setEnabled(true);
			map->setEnabled(true);
			this->getChildByName("loadScreen")->removeFromParentAndCleanup(true);
			if (def->getStringForKey("music", "ON") == "ON") {
				audio->playBackgroundMusic("start.mp3", true);
			}
		}, 2, "loading");
	} else {
		if (def->getStringForKey("music", "ON") == "ON") {
			audio->playBackgroundMusic("start.mp3", true);
		}
	}
	
	Node::onEnter();
}