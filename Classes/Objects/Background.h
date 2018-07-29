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

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "cocos2d.h"

class Background : public cocos2d::Node
{
public:
    CREATE_FUNC(Background)

    cocos2d::Sprite *getButtom() const;
    void spawnDecorFish();

private:
    virtual bool init();
    void spawnBackgroundFish();
    void spawnBubles(float delta);

    cocos2d::Sprite* buttom;
};

#endif // BACKGROUND_H
