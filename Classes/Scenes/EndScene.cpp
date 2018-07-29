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

#include "Scenes/EndScene.h"

#include "ui/CocosGUI.h"

#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"
#include "Objects/Background.h"

USING_NS_CC;

bool EndScene::init()
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

    resumeButton->setTitleText("Retry");
    mainMenuButton->setTitleText("Main menu");
    quitButton->setTitleText("Quit");

    resumeButton->addClickEventListener(CC_CALLBACK_0(EndScene::retry, this));
    mainMenuButton->addClickEventListener(CC_CALLBACK_0(EndScene::toMainMenu, this));
    quitButton->addClickEventListener(CC_CALLBACK_0(EndScene::quitGame, this));

    // Buttons container
    auto menuLayout = ui::VBox::create();
    menuLayout->addChild(resumeButton);
    menuLayout->addChild(mainMenuButton);
    menuLayout->addChild(quitButton);
    menuLayout->setPosition(Vec2(visibleSize.width / 2 - resumeButton->getContentSize().width / 2,
                                     visibleSize.height / 2 + resumeButton->getContentSize().height * 1.5f));
    this->addChild(menuLayout);

    return true;
}

void EndScene::setScore(int fishCount, int fishKilled, unsigned timeLeft)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto title = ui::Text::create();
    title->setFontName("Fonts/DSMarkerFelt.ttf");
    title->setFontSize(48);
    title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.75f));

    if (fishKilled < fishCount)
        title->setString("You lose!");
    else
        title->setString("You win");

    // Fish killed label
    auto fishKilleText = ui::Text::create();
    fishKilleText->setFontName("Fonts/DSMarkerFelt.ttf");
    fishKilleText->setFontSize(24);
    auto timeLeftText = static_cast<ui::Text*>(fishKilleText->clone());

    fishKilleText->setString("Fish killed: " + std::to_string(fishKilled) +"/" + std::to_string(fishCount));
    if (timeLeft > 0)
        timeLeftText->setString("Time left: " + std::to_string(timeLeft));
    else
        timeLeftText->setString("Time is over!");

    fishKilleText->setPosition(Vec2(title->getPosition().x - fishKilleText->getContentSize().width - 10,
                                    title->getPosition().y - fishKilleText->getContentSize().height - 20));
    timeLeftText->setPosition(Vec2(title->getPosition().x + timeLeftText->getContentSize().width + 10,
                                   fishKilleText->getPosition().y));

    this->addChild(title);
    this->addChild(fishKilleText);
    this->addChild(timeLeftText);
}

void EndScene::retry()
{
    auto gameScene = GameScene::create();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, gameScene));
}

void EndScene::toMainMenu()
{
    auto mainMenuScene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, mainMenuScene));
}

void EndScene::quitGame()
{
    Director::getInstance()->end();
}
