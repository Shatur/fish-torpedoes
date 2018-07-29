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

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(GameScene)

private:
    enum Tag {
        NONE,
        BUTTOM,
        FISH,
        KILLER_FISH,
        DEAD_FISH,
        TORPEDO,
        CANNON,
    };
    enum GameStatus {
        LOSE,
        WIN,
    };

    virtual bool init();
    void updateTime(float delta);
    void spawnKillerFish(float delta);
    void explodeCannon();
    void endGame();

    void onMoseMove(cocos2d::Event *event);
    void onMouseUp(cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
    bool onContactPostSolve(cocos2d::PhysicsContact &contact);

    cocos2d::Sprite *cannonTube;
    cocos2d::Sprite *cannonMount;

    cocos2d::Label *timeLabel;
    cocos2d::Label *scoreLabel;

    int fishCount;
    int fishKilled = 0;
    int bulletSpeed;
    unsigned timeLeft;
};

#endif // GAMESCENE_H
