/*
 *  Copyright © 2018 Gennady Chernyshchuk <genaloner@gmail.com>
 *
 *  This file is part of Fish Torpedoes
 *
 *  Crow Translate is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a get of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Scenes/GameScene.h"

#include "SimpleAudioEngine.h"

#include "ConfigParser.h"
#include "Scenes/PauseScene.h"
#include "Scenes/EndScene.h"
#include "Objects/Background.h"
#include "Objects/Fish.h"
#include "Objects/KillerFish.h"
#include "Objects/Torpedo.h"

USING_NS_CC;

bool GameScene::init()
{
    if (!Scene::initWithPhysics())
        return false;

    // Parse config
    ConfigParser config;
    fishCount = config.getCount();
    bulletSpeed = config.getSpeed();
    timeLeft = static_cast<unsigned>(config.getTime());

    // Background
    auto background = Background::create();
    auto buttomBody = PhysicsBody::createBox(background->getButtom()->getContentSize());
    buttomBody->setDynamic(false);
    buttomBody->setContactTestBitmask(0x01);
    background->getButtom()->setPhysicsBody(buttomBody);
    background->getButtom()->setTag(Tag::BUTTOM);
    this->addChild(background);

    // Labels
    auto visibleSize = Director::getInstance()->getVisibleSize();
    timeLabel = Label::createWithTTF("Time left: " + std::to_string(timeLeft), "Fonts/DSMarkerFelt.ttf", 24, Size::ZERO, TextHAlignment::RIGHT);
    timeLabel->setPosition(visibleSize.width - timeLabel->getContentSize().width / 2 - 10, visibleSize.height - timeLabel->getContentSize().height / 2 - 10);
    schedule(CC_SCHEDULE_SELECTOR(GameScene::updateTime), 1.0f, timeLeft - 1, 1.0f);
    addChild(timeLabel);

    scoreLabel = Label::createWithTTF("Fish killed: " + std::to_string(fishKilled) + "/" + std::to_string(fishCount), "Fonts/DSMarkerFelt.ttf", 24);
    scoreLabel->setPosition(scoreLabel->getContentSize().width / 2 + 10, visibleSize.height - scoreLabel->getContentSize().height / 2 - 10);
    addChild(scoreLabel);

    // Collision event listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactPostSolve = CC_CALLBACK_1(GameScene::onContactPostSolve, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // World boundaries
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(edgeNode);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    edgeBody->setDynamic(false);
    edgeBody->setContactTestBitmask(0x01);
    edgeNode->setPhysicsBody(edgeBody);

    // Cannon
    cannonMount = Sprite::create("Cannon/Mount.png");
    cannonTube = Sprite::create("Cannon/Tube.png");

    cannonMount->setTag(Tag::CANNON);
    cannonTube->setTag(Tag::CANNON);

    cannonMount->setPosition(visibleSize.width / 2, cannonMount->getContentSize().height / 2 + 52);
    cannonTube->setPosition(cannonMount->getPosition().x, cannonMount->getPosition().y - 10);

    auto mountBody = PhysicsBody::createBox(cannonMount->getContentSize());
    auto tubeBody = PhysicsBody::createBox(cannonTube->getContentSize());

    mountBody->setContactTestBitmask(0x01);
    tubeBody->setContactTestBitmask(0x01);

    mountBody->setDynamic(false);
    tubeBody->setDynamic(false);

    cannonMount->setPhysicsBody(mountBody);
    cannonTube->setPhysicsBody(tubeBody);
    cannonTube->setAnchorPoint(Vec2(0.5f, 0));

    this->addChild(cannonTube);
    this->addChild(cannonMount);

    // Fish
    for (auto i = 0; i < fishCount; i++) {
        auto fish = Fish::create();
        fish->setPosition(random<float>(0, visibleSize.width), random<float>(visibleSize.height / 2, visibleSize.height));
        fish->getPhysicsBody()->setContactTestBitmask(0x01);
        fish->setTag(Tag::FISH);

        // Rotate to proper direction
        if (fish->getVelocity().getAngle() > 1.57f || fish->getVelocity().getAngle() < -1.57f) // 1.57 ~ PI / 2
            fish->setFlippedX(true);
        else
            fish->setFlippedX(false);

        this->addChild(fish);
    }

    // Killer fish
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::spawnKillerFish), random(4, 7));

    // Mouse listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(GameScene::onMoseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Keyboard listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_1(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void GameScene::updateTime(float delta)
{
    timeLeft -= delta;
       if(timeLeft <= 0){
           this->endGame();
       }
       timeLabel->setString("Time left: " + std::to_string(timeLeft));
}

void GameScene::spawnKillerFish(float delta)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto killerFish = KillerFish::create();
    killerFish->getPhysicsBody()->setContactTestBitmask(0x01);
    killerFish->setTag(Tag::KILLER_FISH);

    // Spawn left or right with random height
    if (random<int>(0, 1))
        killerFish->setPosition(killerFish->getContentSize().width / 2, random<float>(visibleSize.height / 2, visibleSize.height));
    else
        killerFish->setPosition(visibleSize.width + killerFish->getContentSize().width / 2, random<float>(visibleSize.height / 2, visibleSize.height));

    // Rotate to proper direction
    if (killerFish->getVelocity().getAngle() > 1.57f || killerFish->getVelocity().getAngle() < -1.57f) // 1.57 ~ PI / 2
        killerFish->setFlippedX(true);
    else
        killerFish->setFlippedX(false);

    killerFish->runAction(MoveTo::create(delta, cannonMount->getPosition()));
    this->addChild(killerFish);

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::spawnKillerFish), random(4, 7)); // Run again
}

void GameScene::explodeCannon()
{
    this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::spawnKillerFish));
    _eventDispatcher->removeEventListenersForType(EventListener::Type::MOUSE);
    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);

    auto explosion = ParticleSystemQuad::create("Particles/CannonExplosion.plist");
    explosion->setPosition(cannonTube->getPosition());
    this->addChild(explosion);

    cannonTube->removeFromParent();
    cannonMount->removeFromParent();

    this->endGame();
}

void GameScene::endGame()
{
    auto endScene = EndScene::create();
    endScene->setScore(fishCount, fishKilled, timeLeft);
    Director::getInstance()->pushScene(TransitionSlideInB::create(0.5, endScene));
}

void GameScene::onMoseMove(Event *event)
{
    auto mousePosition = static_cast<EventMouse*>(event)->getLocationInView();
    float cathete1 = mousePosition.y - cannonTube->getPosition().y;
    float cathete2 = mousePosition.x - cannonTube->getPosition().x;
    auto angle = atan(cathete2 / cathete1) * 57.295f; // 57.295 = 180 / PI
    if (angle > -60 && angle < 60)
        cannonTube->setRotation(angle);

}

void GameScene::onMouseUp(Event *event)
{
    auto torpedo = Torpedo::create();
    torpedo->setRotation(cannonTube->getRotation());
    torpedo->getPhysicsBody()->setContactTestBitmask(0x01);
    torpedo->setTag(Tag::TORPEDO);

    // Calculate velocity
    auto velocity = static_cast<EventMouse*>(event)->getLocationInView() - cannonTube->getPosition(); // Calculate velocity vector from cursor position
    velocity.normalize(); // Make speed independent of the cursor distance
    torpedo->setVelocity(velocity.x * bulletSpeed, velocity.y * bulletSpeed);

    // Calculate position
    auto position = Vec2(cannonTube->getPosition().x, cannonTube->getPosition().y + cannonTube->getContentSize().height + 10);
    position.rotate(cannonTube->getPosition(), -cannonTube->getRotation() * 0.017f); // 0.017 ~ PI / 180 (convert degree to radians)
    torpedo->setPosition(position);
    this->addChild(torpedo);

    // Add effect
    auto muzzleFlash = ParticleSystemQuad::create("Particles/MuzzleFlash.plist");
    muzzleFlash->setPosition(position);
    this->addChild(muzzleFlash);

}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        auto pauseScene = PauseScene::create();
        Director::getInstance()->pushScene(TransitionSlideInB::create(0.5, pauseScene));
    }
}

bool GameScene::onContactPostSolve(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB) {

        // Torpedo and fish
        if ((nodeA->getTag() == Tag::FISH && nodeB->getTag() == Tag::TORPEDO) ||
                (nodeB->getTag() == Tag::FISH && nodeA->getTag() == Tag::TORPEDO)) {

            if (nodeA->getTag() == Tag::FISH) {
                static_cast<Fish*>(nodeA)->kill();
                nodeA->setTag(Tag::DEAD_FISH);
                static_cast<Torpedo*>(nodeB)->explodeNormal();
            }
            else {
                static_cast<Fish*>(nodeB)->kill();
                nodeB->setTag(Tag::DEAD_FISH);
                static_cast<Torpedo*>(nodeA)->explodeNormal();
            }

            // Add score
            fishKilled++;
            scoreLabel->setString("Fish killed: " + std::to_string(fishKilled) +"/" + std::to_string(fishCount));
            if (fishKilled == fishCount)
                this->endGame();

            return true;

        }

        // Torpedo and killer fish
        if ((nodeA->getTag() == Tag::KILLER_FISH && nodeB->getTag() == Tag::TORPEDO) ||
                (nodeB->getTag() == Tag::KILLER_FISH && nodeA->getTag() == Tag::TORPEDO)){

            if (nodeA->getTag() == Tag::KILLER_FISH) {
                static_cast<KillerFish*>(nodeA)->kill();
                static_cast<Torpedo*>(nodeB)->explodeNormal();
            }
            else {
                static_cast<KillerFish*>(nodeB)->kill();
                static_cast<Torpedo*>(nodeA)->explodeNormal();
            }

            return true;
        }

        // Torpedo and sea buttom
        if ((nodeA->getTag() == Tag::BUTTOM && nodeB->getTag() == Tag::TORPEDO) ||
                (nodeB->getTag() == Tag::BUTTOM && nodeA->getTag() == Tag::TORPEDO)) {

            if (nodeA->getTag() == Tag::TORPEDO)
                static_cast<Torpedo*>(nodeA)->explodeSand();
            else
                static_cast<Torpedo*>(nodeB)->explodeSand();

            return true;
        }

        // Two torpedoes
        if (nodeA->getTag() == Tag::TORPEDO && nodeB->getTag() == Tag::TORPEDO) {
            static_cast<Torpedo*>(nodeA)->explodeNormal();
            static_cast<Torpedo*>(nodeB)->explodeNormal();

            return true;
        }

        // Killer fish and cannon
        if ((nodeA->getTag() == Tag::KILLER_FISH && nodeB->getTag() == Tag::CANNON) ||
                (nodeB->getTag() == Tag::KILLER_FISH && nodeA->getTag() == Tag::CANNON)) {

            if (nodeA->getTag() == Tag::KILLER_FISH) {
                static_cast<KillerFish*>(nodeA)->kill();
                explodeCannon();
            }
            else {
                static_cast<KillerFish*>(nodeB)->kill();
                explodeCannon();
            }

            return true;
        }

        // Rotate fish
        if (nodeA->getTag() == Tag::FISH) {
            if (nodeA->getPhysicsBody()->getVelocity().getAngle() > 1.57f || nodeA->getPhysicsBody()->getVelocity().getAngle() < -1.57f) // 1.57 ~ PI / 2
                static_cast<Fish*>(nodeA)->setFlippedX(true);
            else
                static_cast<Fish*>(nodeA)->setFlippedX(false);
        }
        if (nodeB->getTag() == Tag::FISH) {
            if (nodeB->getPhysicsBody()->getVelocity().getAngle() > 1.57f || nodeB->getPhysicsBody()->getVelocity().getAngle() < -1.57f) // 1.57 ~ PI / 2
                static_cast<Fish*>(nodeB)->setFlippedX(true);
            else
                static_cast<Fish*>(nodeB)->setFlippedX(false);
        }

        return true;
    }

    return false;
}
