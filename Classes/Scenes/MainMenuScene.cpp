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

#include "Scenes/MainMenuScene.h"

#include "ui/CocosGUI.h"

#include "Scenes/SettingsScene.h"
#include "Scenes/GameScene.h"
#include "Objects/Background.h"

USING_NS_CC;

bool MainMenuScene::init()
{
    if (!Scene::init())
        return false;

    // Background
    auto background = Background::create();
    this->addChild(background);

    // Fish
    for (int i = 0; i < 7; i++) {
        background->spawnDecorFish();
    }

    // Buttons
    auto newGameButton = ui::Button::create("UI/OrangeButtonNormal.png", "UI/OrangeButtonPressed.png");
    newGameButton->setTitleFontName("Fonts/DSMarkerFelt.ttf");
    newGameButton->setTitleFontSize(22);
    auto settingsButton = static_cast<ui::Button*>(newGameButton->clone());
    auto quitButton = static_cast<ui::Button*>(settingsButton->clone());

    newGameButton->setTitleText("New Game");
    settingsButton->setTitleText("Settings");
    quitButton->setTitleText("Quit");

    newGameButton->addClickEventListener(CC_CALLBACK_0(MainMenuScene::toGameScene, this));
    settingsButton->addClickEventListener(CC_CALLBACK_0(MainMenuScene::toSettings, this));
    quitButton->addClickEventListener(CC_CALLBACK_0(MainMenuScene::quit, this));

    // Buttons container
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto menuLayout = ui::VBox::create();
    menuLayout->addChild(newGameButton);
    menuLayout->addChild(settingsButton);
    menuLayout->addChild(quitButton);
    menuLayout->setPosition(Vec2(visibleSize.width / 2 - newGameButton->getContentSize().width / 2,
                                     visibleSize.height / 2 + newGameButton->getContentSize().height * 1.5f));
    this->addChild(menuLayout);

    // Logo
    auto logo = Label::createWithTTF("Fish Torpedoes", "Fonts/DSMarkerFelt.ttf", 48, Size::ZERO, TextHAlignment::CENTER);
    logo->setPosition(visibleSize.width / 2, visibleSize.height * 0.75f + logo->getContentSize().height / 2);
    this->addChild(logo);

    return true;
}

void MainMenuScene::toGameScene()
{
    auto gameScene = GameScene::create();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, gameScene));
}

void MainMenuScene::toSettings()
{
    auto gameScene = SettingsScene::create();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5, gameScene));
}

void MainMenuScene::quit()
{
    Director::getInstance()->end();
}
