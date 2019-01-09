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

#include "Fish.h"

USING_NS_CC;

bool Fish::init()
{
    if (!Node::init())
        return false;

    sprite = Sprite::create();
    sprite->setTag(random(1, 5));
    sprite->setTexture("Fish/Fish" + std::to_string(sprite->getTag()) + ".png");
    this->addChild(sprite);

    auto *body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0.1f, 1, 0));
    body->setVelocity(Vec2(random(-150, 150), random(-150, 150)));
    body->setGravityEnable(false);
    this->addComponent(body);

    return true;
}

void Fish::kill()
{
    sprite->setTexture("Fish/DeadFish" + std::to_string(sprite->getTag()) + ".png");
    this->getPhysicsBody()->setGravityEnable(true);
    this->getPhysicsBody()->setResting(0);
    this->getPhysicsBody()->setLinearDamping(0.1f);
}

void Fish::setFlippedX(bool flippedX)
{
    sprite->setFlippedX(flippedX);
}

void Fish::setVelocity(float x, float y)
{
    this->getPhysicsBody()->setVelocity(Vec2(x, y));
}

void Fish::setVelocity(const Vec2 &velocity)
{
    this->getPhysicsBody()->setVelocity(velocity);
}

void Fish::setContactTestBitmask(int bitmask)
{
    this->getPhysicsBody()->setContactTestBitmask(bitmask);
}

Vec2 Fish::getVelocity()
{
    return this->getPhysicsBody()->getVelocity();
}
