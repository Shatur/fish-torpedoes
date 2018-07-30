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

#include "Torpedo.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool Torpedo::init()
{
    if (!Node::init())
        return false;

    sprite = Sprite::create("Cannon/Torpedo.png");
    this->addChild(sprite);

    auto body = PhysicsBody::createBox(sprite->getContentSize());
    body->setGravityEnable(false);
    this->addComponent(body);

    auto trace = ParticleSystemQuad::create("Particles/TorpedoTrace.plist");
    trace->setPosition(sprite->getPosition().x, sprite->getPosition().y - sprite->getContentSize().height / 2);
    this->addChild(trace);

    return true;
}

void Torpedo::explodeNormal()
{
    std::string soundFile = "Sounds/TorpedoExplosions/" + std::to_string(random(1,9)) + ".wav";
    SimpleAudioEngine::getInstance()->playEffect(soundFile.c_str());

    // Check if torpedo exploded before
    if (this->getParent()) {
        // Explode and remove from memory
        auto explosion = ParticleSystemQuad::create("Particles/TorpedoExplosion.plist");
        explosion->setPosition(this->getPosition());
        this->getParent()->addChild(explosion);
        this->removeFromParent();
    }
}

void Torpedo::explodeSand()
{
    std::string soundFile = "Sounds/TorpedoExplosions/" + std::to_string(random(1,9)) + ".wav";
    SimpleAudioEngine::getInstance()->playEffect(soundFile.c_str());

    auto explosion = ParticleSystemQuad::create("Particles/SandExplosion.plist");
    explosion->setPosition(this->getPosition());
    this->getParent()->addChild(explosion);
    this->removeFromParentAndCleanup(true);
}

void Torpedo::setVelocity(float x, float y)
{
    this->getPhysicsBody()->setVelocity(Vec2(x, y));
}

void Torpedo::setVelocity(const Vec2 &velocity)
{
    this->getPhysicsBody()->setVelocity(velocity);
}

void Torpedo::setContactTestBitmask(int bitmask)
{
    this->getPhysicsBody()->setContactTestBitmask(bitmask);
}

Vec2 Torpedo::getVelocity()
{
    return this->getPhysicsBody()->getVelocity();
}
