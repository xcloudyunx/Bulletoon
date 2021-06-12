#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#define DEGREES (180/3.14159265359)
#define BULLETSPEED 250
#define PLAYERSPEED 180

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

class Player : public Ref{
		Sprite* stick;
		int lives;
		float angle = 0;
		Vec2 startPosition;
		Vec2 startVelocity;
		
	public:
		bool alive = true;
		int touch = 999;
		Sprite* joy;
		Button* shoot;
		Sprite* bullet;
		Sprite* player;
		TMXTiledMap* mapBackground;
		int playerNumber;
		int bulletNumber;
		Vec2 velocity;
		int ammo = 1;
		int placing;
		std::string colour;
		bool move = false;
	
		Player();
		
		Player(int a, Vec2 b, TMXTiledMap* c, int d, Vec2 e, Vec2 f, Vec2 g, Vec2 h, Vec2 i, std::string j, Vec2 k, Vec2 l) {
			playerNumber = a;
			bulletNumber = a*11;
			startPosition = b;
			mapBackground = c;
			lives = d;
			startVelocity = e;
			velocity = e;
			colour = j;
			
			player = Sprite::create("player"+std::to_string(playerNumber)+".png");
			player->setPosition(b);
			auto playerPhysics = PhysicsBody::createBox(Size(29, 29), PhysicsMaterial(0, 0, 0));
			player->addComponent(playerPhysics);
			player->getPhysicsBody()->setCollisionBitmask(playerNumber);
			player->getPhysicsBody()->setContactTestBitmask(true);
			mapBackground->addChild(player);
			
			auto back = Sprite::create("p" + std::to_string(playerNumber) + ".png");
			back->setAnchorPoint(k);
			back->setPosition(l);
			mapBackground->getParent()->addChild(back);
			
			
			joy = Sprite::create("joy.png");
			joy->setAnchorPoint(f);
			joy->setPosition(g);
			mapBackground->getParent()->addChild(joy);
			
			stick = Sprite::create("stick" + std::to_string(playerNumber) + ".png");
			stick->setPosition(joy->getContentSize()/2);
			joy->addChild(stick);
			
			shoot = Button::create("shoot.png", "shoot-s.png", "shoot-d.png");
			shoot->setAnchorPoint(h);
			shoot->setPosition(i);
			if (shoot->getPosition().y > Director::getInstance()->getVisibleSize().height/2) {
				shoot->setRotation(180);
			}
			shoot->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
				switch (type) {
					case Widget::TouchEventType::ENDED:
						if (ammo && alive) {
							if (UserDefault::getInstance()->getStringForKey("sound", "ON") == "ON") {
								SimpleAudioEngine::getInstance()->playEffect("shoot.mp3", false, 1.0f, 1.0f, 1.0f);
							}
							auto bulletPhysics = PhysicsBody::createCircle(8.5, PhysicsMaterial(0, 1, 0));
							bullet = Sprite::create("bullet"+std::to_string(playerNumber)+".png");
							bullet->setName("bullet"+std::to_string(playerNumber));
							bullet->setPosition(player->getPosition()+velocity*25);
							bullet->setPhysicsBody(bulletPhysics);
							bullet->getPhysicsBody()->setVelocity(velocity*BULLETSPEED);
							bullet->getPhysicsBody()->setCollisionBitmask(bulletNumber);
							bullet->getPhysicsBody()->setContactTestBitmask(true);
							mapBackground->addChild(bullet);
							ammo = 0;
						}
						break;
					default:
						break;
				}
			});
			mapBackground->getParent()->addChild(shoot);
		};
		
		bool circleContainsPoint(Point p) {
			auto x = p.x-joy->getContentSize().width/2;
			auto y = p.y-joy->getContentSize().height/2;
			auto hype = sqrt(x*x + y*y);
			if (hype < 0) {
				hype = -hype;
			}
			float radius = joy->getContentSize().width/2;
			return hype <= radius;
		};
		
		void movementStart(Point p, int t) {
			move = true;
			
			stick->setPosition(p);
			
			auto x = p.x-joy->getContentSize().width/2;
			auto y = p.y-joy->getContentSize().height/2;
			
			if (x >= 0 && y >= 0) {
				angle = atan2(x, y) * DEGREES;
			} else if (x >= 0 && y < 0) {
				angle = atan2(-y, x) * DEGREES + 90;
			} else if (x < 0 && y < 0) {
				angle = atan2(-x, -y) * DEGREES + 180;
			} else if (x < 0 && y >= 0) {
				angle = atan2(y, -x) * DEGREES + 270;
			}
			player->setRotation(angle);
			
			if (angle < 90) {
				x = sin(angle / DEGREES);
				y = cos(angle / DEGREES);
			} else if (angle < 180) {
				x = cos((angle-90) / DEGREES);
				y = -(sin((angle-90) / DEGREES));
			} else if (angle < 270) {
				x = -(sin((angle-180) / DEGREES));
				y = -(cos((angle-180) / DEGREES));
			} else if (angle < 360) {
				x = -(cos((angle-270) / DEGREES));
				y = sin((angle-270) / DEGREES);
			}
			velocity = Vec2(x, y);
							
			player->getPhysicsBody()->setVelocity(velocity*PLAYERSPEED);
			player->getPhysicsBody()->setAngularVelocity(0);
			
			touch = t;
		};
		
		void movementMain(Point p) {
			auto radius = joy->getContentSize().width/2;
			auto x = p.x - radius;
			auto y = p.y - radius;
			if (x > 0 && y > 0) {
				angle = atan2(x, y);
				angle *= DEGREES;
			} else if (x > 0 && y < 0) {
				angle = atan2(-y, x);
				angle = angle * DEGREES + 90;
			} else if (x < 0 && y < 0) {
				angle = atan2(-x, -y);
				angle = angle * DEGREES + 180;
			} else if (x < 0 && y > 0) {
				angle = atan2(y, -x);
				angle = angle * DEGREES + 270;
			}
			player->setRotation(angle);
			
			if (x >= 0 && y >= 0) {
				x = sin(angle / DEGREES);
				y = cos(angle / DEGREES);
			} else if (x >= 0 && y < 0) {
				y = -(sin((angle-90) / DEGREES));
				x = cos((angle-90) / DEGREES);
			} else if (x < 0 && y < 0) {
				x = -(sin((angle-180) / DEGREES));
				y = -(cos((angle-180) / DEGREES));
			} else if (x < 0 && y >= 0) {
				y = sin((angle-270) / DEGREES);
				x = -(cos((angle-270) / DEGREES));
			}
			velocity = Vec2(x, y);
			
			if (!circleContainsPoint(p)) {
				p.x = x*radius+radius;
				p.y = y*radius+radius;
			}
			stick->setPosition(p);
			
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
			player->getPhysicsBody()->setVelocity(velocity*PLAYERSPEED);
			player->getPhysicsBody()->setAngularVelocity(0);
		};

		void movementEnd() {
			move = false;
			
			stick->setPosition(joy->getContentSize()/2);
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
			player->getPhysicsBody()->setAngularVelocity(0);
			touch = 999;
		};
		
		void collectBullet() {
			bullet->removeFromParentAndCleanup(true);
			ammo = 1;
		};
		
		void die() {
			alive = false;
			lives -= 1;
			player->setVisible(false);
			player->getPhysicsBody()->setEnabled(false);
			player->getPhysicsBody()->setVelocity(Vec2(0,0));
			player->getPhysicsBody()->setAngularVelocity(0);
			stick->setPosition(joy->getContentSize()/2);
			shoot->setEnabled(false);
			
			auto liveCount = Label::createWithTTF(std::to_string(lives), "ArialRoundedMTBold.TTF", 20);
			liveCount->setPosition(player->getPosition());
			mapBackground->addChild(liveCount);
			liveCount->runAction(FadeOut::create(1.0f));
			
			if (lives > 0) {
				mapBackground->getParent()->scheduleOnce([&](float dt){
					player->setPosition(startPosition);
					player->setRotation(0);
					angle = 0;
					velocity = startVelocity;
					touch = 999;
					player->getPhysicsBody()->setEnabled(true);
					player->setVisible(true);
					alive = true;
					shoot->setEnabled(true);
				}, UserDefault::getInstance()->getIntegerForKey("spawn", 3), "respawn"+std::to_string(playerNumber));
			} else {
				if (mapBackground->getChildByName("bullet"+std::to_string(playerNumber))) {
					bullet->setVisible(false);
					bullet->getPhysicsBody()->setEnabled(false);
				}
				UserDefault* def = UserDefault::getInstance();
				placing = def->getIntegerForKey("numberOfPlayers");
				def->setIntegerForKey("numberOfPlayers", placing-1);
				def->flush();
			}
		};
};