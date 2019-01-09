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

#include "KillerFish.h"

USING_NS_CC;

bool KillerFish::init()
{
    if (!Node::init())
        return false;

    sprite = Sprite::create("Fish/KillerFish.png");
    this->addChild(sprite);

    auto *body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(100, 1.0f, 0));
    body->setGravityEnable(false);
    this->addComponent(body);

    return true;
}

void KillerFish::kill()
{
    auto *explosion = ParticleSystemQuad::create("Particles/KillerFishExplosion.plist");
    explosion->setPosition(this->getPosition());
    this->getParent()->addChild(explosion);
    this->removeFromParentAndCleanup(true);
}

void KillerFish::setFlippedX(bool flippedX)
{
    sprite->setFlippedX(flippedX);
}

void KillerFish::setVelocity(float x, float y)
{
    this->getPhysicsBody()->setVelocity(Vec2(x, y));
}

void KillerFish::setVelocity(const Vec2 &velocity)
{
    this->getPhysicsBody()->setVelocity(velocity);
}

void KillerFish::setContactTestBitmask(int bitmask)
{
    this->getPhysicsBody()->setContactTestBitmask(bitmask);
}

Vec2 KillerFish::getVelocity()
{
    return this->getPhysicsBody()->getVelocity();
}
