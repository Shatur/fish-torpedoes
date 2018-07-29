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

#include "Scenes/PauseScene.h"

#include "ui/CocosGUI.h"

#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"
#include "Objects/Background.h"

USING_NS_CC;

bool PauseScene::init()
{
    if (!Scene::init())
        return false;

    // Background
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("PauseBackground.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background);

    // Buttons
    auto resumeButton = ui::Button::create("UI/OrangeButtonNormal.png", "UI/OrangeButtonPressed.png");
    resumeButton->setTitleFontName("Fonts/DSMarkerFelt.ttf");
    resumeButton->setTitleFontSize(22);
    auto mainMenuButton = static_cast<ui::Button*>(resumeButton->clone());
    auto quitButton = static_cast<ui::Button*>(mainMenuButton->clone());

    resumeButton->setTitleText("Resume");
    mainMenuButton->setTitleText("Main menu");
    quitButton->setTitleText("Quit");

    resumeButton->addClickEventListener(CC_CALLBACK_0(PauseScene::resumeGame, this));
    mainMenuButton->addClickEventListener(CC_CALLBACK_0(PauseScene::toMainMenu, this));
    quitButton->addClickEventListener(CC_CALLBACK_0(PauseScene::quitGame, this));

    // Buttons container
    auto menuLayout = ui::VBox::create();
    menuLayout->addChild(resumeButton);
    menuLayout->addChild(mainMenuButton);
    menuLayout->addChild(quitButton);
    menuLayout->setPosition(Vec2(visibleSize.width / 2 - resumeButton->getContentSize().width / 2,
                                     visibleSize.height / 2 + resumeButton->getContentSize().height * 1.5f));
    this->addChild(menuLayout);

    // Title
    auto title = ui::Text::create("Pause", "Fonts/DSMarkerFelt.ttf", 48);
    title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.75f + title->getContentSize().height / 2));
    this->addChild(title);

    // Keyboard listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_1(PauseScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void PauseScene::resumeGame()
{
    Director::getInstance()->popScene();
}

void PauseScene::toMainMenu()
{
    auto mainMenuScene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, mainMenuScene));
}

void PauseScene::quitGame()
{
    Director::getInstance()->end();
}

void PauseScene::onKeyReleased(EventKeyboard::KeyCode keyCode)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        resumeGame();
}
