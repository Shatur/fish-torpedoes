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

#include "Scenes/SplashScene.h"

#include "Scenes/MainMenuScene.h"

USING_NS_CC;

bool SplashScene::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto label = Label::createWithTTF("<Awesome logo>", "Fonts/DSMarkerFelt.ttf", 78, Size::ZERO, TextHAlignment::CENTER);
    auto noteLabel = Label::createWithTTF("(that does not exist)", "Fonts/DSMarkerFelt.ttf", 48, Size::ZERO, TextHAlignment::CENTER);
    label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    noteLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - label->getContentSize().height);
    this->addChild(label);
    this->addChild(noteLabel);
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::toMainMenuScene), 1.5f);

    return true;
}

void SplashScene::toMainMenuScene(float delta)
{
    auto mainMenuScene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(2, mainMenuScene));
}


