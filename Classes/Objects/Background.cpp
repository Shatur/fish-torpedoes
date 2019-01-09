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

#include "Background.h"

USING_NS_CC;

bool Background::init()
{
    if (!Node::init())
        return false;

    const Size visibleSize = Director::getInstance()->getVisibleSize();

    // Background
    auto *background = Sprite::create("Background.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background);

    // Buttom
    buttom = Sprite::create("Buttom.png");
    buttom->setPosition(visibleSize.width / 2, buttom->getContentSize().height / 2);
    for (int i = 0; i < random(7, 13); ++i) {
        // Generate random buttom ibjects
        auto *buttomObject = Sprite::create("ButtomObjects/" + std::to_string(random(1, 28)) + ".png");
        buttomObject->setPosition(random<float>(0, visibleSize.width), buttom->getContentSize().height + buttomObject->getContentSize().height / 2 - 8);
        addChild(buttomObject);
    }
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(Background::spawnBubles), random(4, 8));
    this->addChild(buttom, 1);

    // Background fish
    for (int i = 0; i < 7; ++i)
        this->spawnBackgroundFish();

    return true;
}

void Background::spawnDecorFish()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto *fish = Sprite::create();
    fish->setTexture("Fish/Fish" + std::to_string(random(1, 5)) + ".png");
    this->addChild(fish, 1);

    MoveTo* moveAction;
    if (random(0, 1)) {
        fish->setPosition(visibleSize.width, random<float>(visibleSize.height / 5, visibleSize.height - 50));
        moveAction = MoveTo::create(random(5, 9), Vec2(-fish->getContentSize().width / 2, fish->getPosition().y));
        fish->setFlippedX(true); // Rotate to proper direction
    } else {
        fish->setPosition(0, random<float>(visibleSize.height / 5, visibleSize.height - 50));
        moveAction = MoveTo::create(random(5, 9), Vec2(visibleSize.width + fish->getContentSize().width / 2, fish->getPosition().y));
    }

    fish->runAction(Sequence::create(moveAction,
                                     CallFunc::create(CC_CALLBACK_0(Background::spawnDecorFish, this)),
                                     CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, fish)),
                                     NULL));
}

Sprite *Background::getButtom() const
{
    return buttom;
}

void Background::spawnBackgroundFish()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto *fish = Sprite::create();
    fish->setTexture("Fish/BackgroundFish" + std::to_string(random(1, 5)) + ".png");
    fish->setScale(random(0.1f, 0.7f));
    this->addChild(fish);

    MoveTo* moveAction;
    if (random(0, 1)) {
        fish->setPosition(visibleSize.width, random<float>(visibleSize.height / 5, visibleSize.height - 50));
        moveAction = MoveTo::create(random(9, 13), Vec2(-fish->getContentSize().width / 2, fish->getPosition().y));
        fish->setFlippedX(true); // Rotate to proper direction
    } else {
        fish->setPosition(0, random<float>(visibleSize.height / 5, visibleSize.height - 50));
        moveAction = MoveTo::create(random(9, 13), Vec2(visibleSize.width + fish->getContentSize().width / 2, fish->getPosition().y));
    }

    fish->runAction(Sequence::create(moveAction,
                                     CallFunc::create(CC_CALLBACK_0(Background::spawnBackgroundFish, this)),
                                     CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, fish)),
                                     NULL));
}

void Background::spawnBubles(float)
{
    auto *bubbles = ParticleSystemQuad::create("Particles/Bubbles.plist");
    const Size visibleSize = Director::getInstance()->getVisibleSize();
    bubbles->setPosition(random<float>(0, visibleSize.width), 64);
    this->addChild(bubbles);
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(Background::spawnBubles), random(4, 8));
}
