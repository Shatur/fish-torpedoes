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

#ifndef TORPEDO_H
#define TORPEDO_H

#include "cocos2d.h"

class Torpedo: public cocos2d::Node
{
public:
    CREATE_FUNC(Torpedo)

    void explodeNormal();
    void explodeSand();
    void setVelocity(float x, float y);
    void setVelocity(const cocos2d::Vec2 &velocity);
    void setContactTestBitmask(int bitmask);
    cocos2d::Vec2 getVelocity();

private:
    virtual bool init();

    cocos2d::Sprite* sprite;
};

#endif // TORPEDO_H
