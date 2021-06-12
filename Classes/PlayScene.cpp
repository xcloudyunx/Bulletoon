#include "PlayScene.h"
		
std::string oneText;
std::string twoText;
std::string threeText;
std::string fourText;

Scene* Play::createScene(std::string one, std::string two, std::string three, std::string four) {
	oneText = one;
	twoText = two;
	threeText = three;
	fourText = four;
	
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setSubsteps(30);
	auto layer = Play::create();
	scene->addChild(layer);
	return scene;
}

bool Play::init() {
	if (!Scene::init()) {
		return false;
	}
	
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	def = UserDefault::getInstance();
	audio = SimpleAudioEngine::getInstance();
	
	int lives = atoi(def->getStringForKey("lives", "1").c_str());
	
	auto mapBackground = TMXTiledMap::create(def->getStringForKey("mapName", "MAZE")+".tmx");
	mapBackground->setName("mapBackground");
	mapBackground->setAnchorPoint(Vec2(0.5, 0.5));
	mapBackground->setPosition(visibleSize/2);
	auto mapPhysics = PhysicsBody::createEdgeBox(Size(mapBackground->getContentSize()), PhysicsMaterial(0, 1, 0), 20);
	mapBackground->addComponent(mapPhysics);
	mapBackground->getPhysicsBody()->setCollisionBitmask(9);
	mapBackground->getPhysicsBody()->setContactTestBitmask(true);
	
	{
		if ((def->getStringForKey("mapName", "MAZE") != "OPEN") && (def->getStringForKey("mapName", "MAZE") != "BOX")) {
			auto mapLayer = mapBackground->getLayer("map");
			Sprite* tiles[990] = {};
			for (int x = 0; x < 33; x++) {
				for (int y = 0; y < 30; y++) {
					auto spriteTile = mapLayer->getTileAt(Vec2(x, y));
					if (spriteTile != nullptr) {
						tiles[30*x+y] = spriteTile;
					}
				}
			}
			int j = 0;
			int k = 0;
			for (int i = 0; i < 990; i++) {
				if (tiles[i] != nullptr) {
					j = i;
					int height = 20;
					while (tiles[j] != nullptr) {
						if (tiles[j+1] != nullptr) {
							height += 20;
						}
						j++;
					}
					if (height != 20) {
						PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(20, height), PhysicsMaterial(0, 1, 0));                 
						tilePhysics->setDynamic(false);
						tilePhysics->setCollisionBitmask(9);
						tilePhysics->setContactTestBitmask(true);
						tiles[(i+j)/2]->addComponent(tilePhysics);
						while (j >= i) {
							if (tiles[j+30] == nullptr) {
								tiles[j] = nullptr;
							}
							j--;
						}
					}
				}
				if (tiles[i] != nullptr) {
					k = i;
					int width = 20;
					while (tiles[k] != nullptr) {
						if (tiles[k+30] != nullptr) {
							width += 20;
						}
						k += 30;
						
					}
					PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, 20), PhysicsMaterial(0, 1, 0));                 
					tilePhysics->setDynamic(false);
					tilePhysics->setCollisionBitmask(9);
					tilePhysics->setContactTestBitmask(true);
					tiles[(i+k-30)/2]->addComponent(tilePhysics);
					while (k >= i) {
						if (tiles[k-1] == nullptr && tiles[k+1] == nullptr) {
							tiles[k] = nullptr;
						}
						k -= 30;
					}
				}
			}
		} else if (def->getStringForKey("mapName", "MAZE") == "BOX") {
			auto mapLayer = mapBackground->getLayer("invisible");
			for (int x = 0; x < 33; x++) {
				for (int y = 0; y < 30; y++) {
					auto spriteTile = mapLayer->getTileAt(Vec2(x, y));
					if (spriteTile != nullptr) {
						PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(60, 60), PhysicsMaterial(0, 1, 0));                 
						tilePhysics->setDynamic(false);
						tilePhysics->setCollisionBitmask(9);
						tilePhysics->setContactTestBitmask(true);
						spriteTile->addComponent(tilePhysics);
					}
				}
			}
		}
	}
	this->addChild(mapBackground);
	
	int playersNumber = 1;
	
	if (oneText == "-") {
		auto one = std::unique_ptr<Player>(new Player(playersNumber, Vec2(40, 40), mapBackground, lives, Vec2(0, 1), Vec2(0, 1), Vec2(visibleSize.width/40, 280-visibleSize.width/40), Vec2(1, 0), Vec2(280-visibleSize.width/40, visibleSize.width/40), "Red", Vec2(0, 0), Vec2(0, 0)));
		players.push_back(std::move(one));
	}
	playersNumber += 1;
	if (twoText == "-") {
		auto two = std::unique_ptr<Player>(new Player(playersNumber, Vec2(40, mapBackground->getContentSize().height-40), mapBackground, lives, Vec2(1, 0), Vec2(1, 1), Vec2(280-visibleSize.width/40, visibleSize.height-visibleSize.width/40), Vec2(1, 1), Vec2(visibleSize.width/40, visibleSize.height-(280-visibleSize.width/40)), "Green", Vec2(0, 1), Vec2(0, visibleSize.height)));
		players.push_back(std::move(two));
	}
	playersNumber += 1;
	if (threeText == "-") {
		auto three = std::unique_ptr<Player>(new Player(playersNumber, Vec2(mapBackground->getContentSize().width-40, mapBackground->getContentSize().height-40), mapBackground, lives, Vec2(0, -1), Vec2(1, 0), Vec2(visibleSize.width-visibleSize.width/40, visibleSize.height-(280-visibleSize.width/40)), Vec2(1, 0), Vec2(visibleSize.width-(280-visibleSize.width/40), visibleSize.height-visibleSize.width/40), "Yellow", Vec2(1, 1), visibleSize));
		players.push_back(std::move(three));
	}
	playersNumber += 1;
	if (fourText == "-") {
		auto four = std::unique_ptr<Player>(new Player(playersNumber, Vec2(mapBackground->getContentSize().width-40, 40), mapBackground, lives, Vec2(-1, 0), Vec2(0, 0), Vec2(visibleSize.width-(280-visibleSize.width/40), visibleSize.width/40), Vec2(1, 1), Vec2(visibleSize.width-visibleSize.width/40, 280-visibleSize.width/40), "Blue", Vec2(1, 0), Vec2(visibleSize.width, 0)));
		players.push_back(std::move(four));
	}
	
	def->setIntegerForKey("numberOfPlayers", players.size());
	def->flush();
	
	touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = [&](const std::vector<Touch*> &touches, Event* event) {
		for(int i = 0; i < touches.size(); ++i){
			auto p = touches[i]->getLocation();
			for (auto &j : players) {
				if ((*j).alive) {
					auto pp = (*j).joy->convertToNodeSpace(p);
					if ((*j).circleContainsPoint(pp)) {
						(*j).movementStart(pp, touches[i]->getID());
						break;
					}
				}
			}
		}
	};
	touchListener->onTouchesMoved = [&](const std::vector<Touch*> &touches, Event* event) {
		for(int i = 0; i < touches.size(); ++i){
			auto p = touches[i]->getLocation();
			for (auto &j : players) {
				if ((*j).alive) {
					if (touches[i]->getID() == (*j).touch) {
						auto pp = (*j).joy->convertToNodeSpace(p);
						(*j).movementMain(pp);
						break;
					}
				}
			}
		}
	};
	touchListener->onTouchesEnded = [&](const std::vector<Touch*> &touches, Event* event) {
		for(int i = 0; i < touches.size(); ++i){
			for (auto &j : players) {
				if ((*j).alive) {
					if (touches[i]->getID() == (*j).touch) {
						(*j).movementEnd();
						break;
					}
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [&](PhysicsContact &contact) {
		int a = contact.getShapeA()->getBody()->getCollisionBitmask();
		int b = contact.getShapeB()->getBody()->getCollisionBitmask();
		
		int c = (a<b ? a:b);
		int d = (a>b ? a:b);
		
		if (c == d/11) {
			for (auto &j : players) {
				if ((*j).playerNumber == c) {
					(*j).collectBullet();
					return false;
				}
			}
		} else {
			for (auto &j : players) {
				if ((*j).playerNumber == c) {
					for (auto &k : players) {
						if ((*k).bulletNumber == d) {
							if (def->getStringForKey("sound", "ON") == "ON") {
								audio->playEffect("dead.mp3", false, 1.0f, 1.0f, 1.0f);
							}
							(*j).die();
							(*k).collectBullet();
							return false;
						}
					}
				}
			}
		}
		
		if ((c == 9) && (d%11 == 0)) {
			if (def->getStringForKey("sound", "ON") == "ON") {
				audio->playEffect("ricochet.mp3", false, 1.0f, 1.0f, 1.0f);
			}
		}
		
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, mapBackground);
	
	pauseButton1 = Button::create("pause.png", "pause-s.png");
	pauseButton1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/10));
	pauseButton1->addTouchEventListener(CC_CALLBACK_2(Play::pause, this));
	pauseButton1->setEnabled(false);
	pauseButton1->setBright(true);
	this->addChild(pauseButton1);
	pauseButton2 = Button::create("pause.png", "pause-s.png");
	pauseButton2->setPosition(Vec2(visibleSize.width/2, visibleSize.height*9/10));
	pauseButton2->setRotation(180);
	pauseButton2->addTouchEventListener(CC_CALLBACK_2(Play::pause, this));
	pauseButton2->setEnabled(false);
	pauseButton2->setBright(true);
	this->addChild(pauseButton2);
	
	this->scheduleUpdate();
	
	time = 3;
	touchListener->setEnabled(false);
	contactListener->setEnabled(false);	
	for (auto &j : players) {
		(*j).shoot->setEnabled(false);
		(*j).shoot->setBright(true);
	}
	auto countdown1 = Label::createWithTTF(std::to_string(time), "ArialRoundedMTBold.TTF", 70);
	countdown1->setName("countdown1");
	countdown1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/3));
	this->addChild(countdown1);
	auto countdown2 = Label::createWithTTF(std::to_string(time), "ArialRoundedMTBold.TTF", 70);
	countdown2->setName("countdown2");
	countdown2->setPosition(Vec2(visibleSize.width/2, visibleSize.height*2/3));
	countdown2->setRotation(180);
	this->addChild(countdown2);
	time -= 1;
	
	this->schedule([&](float dt){
		this->getChildByName("countdown1")->removeFromParentAndCleanup(true);
		this->getChildByName("countdown2")->removeFromParentAndCleanup(true);
		if (time == 0) {
			this->unschedule("start");
			
			pauseButton1->setEnabled(true);
			pauseButton2->setEnabled(true);
			
			auto countdown1 = Label::createWithTTF("GO", "ArialRoundedMTBold.TTF", 70);
			countdown1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/3));
			this->addChild(countdown1);
			countdown1->runAction(FadeOut::create(3.0f));
			auto countdown2 = Label::createWithTTF("GO", "ArialRoundedMTBold.TTF", 70);
			countdown2->setPosition(Vec2(visibleSize.width/2, visibleSize.height*2/3));
			countdown2->setRotation(180);
			this->addChild(countdown2);
			countdown2->runAction(FadeOut::create(3.0f));
			
			touchListener->setEnabled(true);
			contactListener->setEnabled(true);		
			Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);	
			for (auto &j : players) {
				(*j).shoot->setEnabled(true);
			}
			
			if (def->getStringForKey("music", "ON") == "ON") {
				audio->playBackgroundMusic("background.mp3", true);
			}
			
		} else {	
			auto countdown1 = Label::createWithTTF(std::to_string(time), "ArialRoundedMTBold.TTF", 70);
			countdown1->setName("countdown1");
			countdown1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/3));
			this->addChild(countdown1);
			auto countdown2 = Label::createWithTTF(std::to_string(time), "ArialRoundedMTBold.TTF", 70);
			countdown2->setName("countdown2");
			countdown2->setPosition(Vec2(visibleSize.width/2, visibleSize.height*2/3));
			countdown2->setRotation(180);
			this->addChild(countdown2);
			time -= 1;
		}
		
	}, 1.0, "start");
	
	return true;
}

void Play::pause(Ref* sender, Widget::TouchEventType type) {
	switch (type) {
		case Widget::TouchEventType::BEGAN:
			if (def->getStringForKey("sound", "ON") == "ON") {
				audio->playEffect("button.mp3", false);
			}
			break;
		case Widget::TouchEventType::ENDED:
			touchListener->setEnabled(false);
			contactListener->setEnabled(false);
			
			Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
			pausedActions = Director::getInstance()->getActionManager()->pauseAllRunningActions();
			
			for (auto &j : players) {
				if ((*j).shoot->isEnabled()) {
					(*j).shoot->setEnabled(false);
					(*j).shoot->setBright(true);
				}
			}
			
			pauseButton1->setEnabled(false);
			pauseButton1->setBright(true);
			pauseButton2->setEnabled(false);
			pauseButton2->setBright(true);
			
			audio->pauseBackgroundMusic();
			audio->pauseAllEffects();

			paused = true;
			break;
		default:
			break;
	}
}

void Play::resume(Ref* sender, Widget::TouchEventType type) {
	switch (type) {
		case Widget::TouchEventType::BEGAN:
			if (def->getStringForKey("sound", "ON") == "ON") {
				audio->playEffect("button.mp3", false);
			}
			break;
		case Widget::TouchEventType::ENDED:
			touchListener->setEnabled(true);
			contactListener->setEnabled(true);
			Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
			Director::getInstance()->getActionManager()->resumeTargets(pausedActions);
			for (auto &j : players) {
				if ((*j).alive) {
					(*j).shoot->setEnabled(true);
				}
			}
			pauseButton1->setEnabled(true);
			pauseButton2->setEnabled(true);
				
			this->getChildByName("pauseBackground")->removeFromParentAndCleanup(true);
			this->getChildByName("homeButton1")->removeFromParentAndCleanup(true);
			this->getChildByName("homeButton2")->removeFromParentAndCleanup(true);
			this->getChildByName("restartButton1")->removeFromParentAndCleanup(true);
			this->getChildByName("restartButton2")->removeFromParentAndCleanup(true);
			this->getChildByName("resumeButton1")->removeFromParentAndCleanup(true);
			this->getChildByName("resumeButton2")->removeFromParentAndCleanup(true);
				
			audio->resumeBackgroundMusic();
			audio->resumeAllEffects();
			break;
		default:
			break;
	}
}

void Play::home(Ref* sender, Widget::TouchEventType type) {
	audio->stopBackgroundMusic();
	audio->stopAllEffects();

	switch (type) {
		case Widget::TouchEventType::BEGAN:
			if (def->getStringForKey("sound", "ON") == "ON") {
				audio->playEffect("button.mp3", false);
			}
			break;
		case Widget::TouchEventType::ENDED:
			audio->playBackgroundMusic("start.mp3", true);
			Director::getInstance()->popToRootScene();
			break;
		default:
			break;
	}
}

void Play::restart(Ref* sender, Widget::TouchEventType type) {
	audio->stopBackgroundMusic();
	audio->stopAllEffects();

	switch (type) {
		case Widget::TouchEventType::BEGAN:
			if (def->getStringForKey("sound", "ON") == "ON") {
				audio->playEffect("button.mp3", false);
			}
			break;
		case Widget::TouchEventType::ENDED: {
			auto scene = Play::createScene(oneText, twoText, threeText, fourText);
			Director::getInstance()->replaceScene(scene);
			break;
		}
		default:
			break;
	}
}

void Play::update(float dt) {
	if (!finished) {
		for (auto &j : players) {
			if (!(*j).move) {
				(*j).player->getPhysicsBody()->setVelocity(Vec2(0, 0));
				(*j).player->getPhysicsBody()->setAngularVelocity(0);
			} 
		}
		
		if (def->getIntegerForKey("numberOfPlayers") <= 1) {
			std::string one;
			Color4B oneC;
			std::string two;
			Color4B twoC;
			std::string three;
			Color4B threeC;
			std::string four;
			Color4B fourC;
			for (auto &j : players) {
				Color4B c;
				if ((*j).colour == "Red") {
					c = Color4B(255, 0, 0, 255);
				} else if ((*j).colour == "Green") {
					c = Color4B(0, 255, 0, 255);
				} else if ((*j).colour == "Blue") {
					c = Color4B(0, 0, 255, 255);
				} else if ((*j).colour == "Yellow") {
					c = Color4B(255, 255, 0, 255);
				}
				
				if ((*j).placing == 2) {
					two = (*j).colour;
					twoC = c;
				} else if ((*j).placing == 3) {
					three = (*j).colour;
					threeC = c;
				} else if ((*j).placing == 4) {
					four = (*j).colour;
					fourC = c;
				} else {
					(*j).placing = 1;
					one = (*j).colour;
					oneC = c;
				} 
			}
			
			touchListener->setEnabled(false);
			contactListener->setEnabled(false);
			
			Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
			
			for (auto &j : players) {
				(*j).shoot->setEnabled(false);
			}
			
			pauseButton1->removeFromParentAndCleanup(true);
			pauseButton2->removeFromParentAndCleanup(true);
			
			auto background = Sprite::create("background.png");
			background->setPosition(Vec2(visibleSize/2));
			this->addChild(background);
			
			if (def->getStringForKey("music", "ON") == "ON") {
				audio->playBackgroundMusic("finish.mp3", true);
			}
			
			auto finishBackground = Sprite::create("finishBackground.png");
			finishBackground->setAnchorPoint(Vec2(0.5, 0.5));
			finishBackground->setPosition(visibleSize/2);
			this->addChild(finishBackground);
			
			auto width = finishBackground->getContentSize().width;
			auto height = finishBackground->getContentSize().height;
			
			auto first = Label::createWithTTF(one+" was first!", "ArialRoundedMTBold.TTF", 70);
			first->setTextColor(oneC);
			finishBackground->addChild(first);
			
			auto second = Label::createWithTTF(two+" was second!", "ArialRoundedMTBold.TTF", 50);
			second->setTextColor(twoC);
			finishBackground->addChild(second);
			
			if (!three.empty()) {
				auto third = Label::createWithTTF(three+" was third!", "ArialRoundedMTBold.TTF", 50);
				third->setTextColor(threeC);
				finishBackground->addChild(third);
				
				if (!four.empty()) {
					auto fourth = Label::createWithTTF(four+" was fourth!", "ArialRoundedMTBold.TTF", 50);
					fourth->setTextColor(fourC);
					finishBackground->addChild(fourth);

					first->setPosition(Vec2(width/2, height*9/10));
					second->setPosition(Vec2(width/2, height*7/10));
					third->setPosition(Vec2(width/2, height/2));
					fourth->setPosition(Vec2(width/2, height*3/10));
				} else {
					first->setPosition(Vec2(width/2, height*17/20));
					second->setPosition(Vec2(width/2, height*3/5));
					third->setPosition(Vec2(width/2, height*7/20));
				}
			} else {
				first->setPosition(Vec2(width/2, height*4/5));
				second->setPosition(Vec2(width/2, height*9/20));
			}
			
			auto restart = Button::create("restart.png", "restart-s.png");
			restart->setPosition(Vec2(width/3, height/10));
			restart->addTouchEventListener(CC_CALLBACK_2(Play::restart, this));
			finishBackground->addChild(restart);
				
			auto home = Button::create("home.png", "home-s.png");
			home->setPosition(Vec2(width*2/3, height/10));
			home->addTouchEventListener(CC_CALLBACK_2(Play::home, this));
			finishBackground->addChild(home);
			
			finished = true;
		}
		
		if (paused) {
			auto pauseBackground = Sprite::create("background.png");
			pauseBackground->setPosition(Vec2(visibleSize/2));
			pauseBackground->setName("pauseBackground");
			this->addChild(pauseBackground);
			
			auto homeButton1 = Button::create("home.png", "home-s.png");
			homeButton1->setPosition(Vec2(visibleSize.width/4, visibleSize.height/4));
			homeButton1->addTouchEventListener(CC_CALLBACK_2(Play::home, this));
			homeButton1->setName("homeButton1");
			this->addChild(homeButton1);
			auto homeButton2 = Button::create("home.png", "home-s.png");
			homeButton2->setPosition(Vec2(visibleSize.width*3/4, visibleSize.height*3/4));
			homeButton2->setRotation(180);
			homeButton2->addTouchEventListener(CC_CALLBACK_2(Play::home, this));
			homeButton2->setName("homeButton2");
			this->addChild(homeButton2);
			
			auto restartButton1 = Button::create("restart.png", "restart-s.png");
			restartButton1->setPosition(Vec2(visibleSize.width*3/4, visibleSize.height/4));
			restartButton1->addTouchEventListener(CC_CALLBACK_2(Play::restart, this));
			restartButton1->setName("restartButton1");
			this->addChild(restartButton1);
			auto restartButton2 = Button::create("restart.png", "restart-s.png");
			restartButton2->setPosition(Vec2(visibleSize.width/4, visibleSize.height*3/4));
			restartButton2->setRotation(180);
			restartButton2->addTouchEventListener(CC_CALLBACK_2(Play::restart, this));
			restartButton2->setName("restartButton2");
			this->addChild(restartButton2);
			
			auto resumeButton1 = Button::create("resume.png", "resume-s.png");
			resumeButton1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
			resumeButton1->addTouchEventListener(CC_CALLBACK_2(Play::resume, this));
			resumeButton1->setName("resumeButton1");
			this->addChild(resumeButton1);
			auto resumeButton2 = Button::create("resume.png", "resume-s.png");
			resumeButton2->setPosition(Vec2(visibleSize.width/2, visibleSize.height*3/4));
			resumeButton2->setRotation(180);
			resumeButton2->addTouchEventListener(CC_CALLBACK_2(Play::resume, this));
			resumeButton2->setName("resumeButton2");
			this->addChild(resumeButton2);
			
			paused = false;
		}
	}
}