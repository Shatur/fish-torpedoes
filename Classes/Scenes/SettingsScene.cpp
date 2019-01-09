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

#include "Scenes/SettingsScene.h"

#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#include "Scenes/MainMenuScene.h"
#include "Objects/Background.h"

using namespace CocosDenshion;

bool SettingsScene::init()
{
    if (!Scene::init())
        return false;

    // Background
    auto *background = Background::create();
    this->addChild(background);

    // Fish
    for (int i = 0; i < 7; ++i)
        background->spawnDecorFish();

    // Title
    const Size visibleSize = Director::getInstance()->getVisibleSize();
    auto *title = ui::Text::create("Settings", "Fonts/DSMarkerFelt.ttf", 48);
    title->setAnchorPoint(Vec2(0.5f, 0));
    title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.75f - title->getContentSize().height));
    this->addChild(title);

    // Labels
    auto *countText = ui::Text::create();
    countText->setFontName("Fonts/DSMarkerFelt.ttf");
    countText->setFontSize(24);
    countText->setAnchorPoint(Vec2(0.5f, 0));
    auto *speedText = static_cast<ui::Text*>(countText->clone());
    auto *timeText = static_cast<ui::Text*>(speedText->clone());

    countText->setString("Number of fish");
    speedText->setString("Torpedo speed");
    timeText->setString("Game time");

    // Sliders
    countSlider = ui::Slider::create("UI/SliderBarHorizontal.png", "UI/OrangeSlider.png");
    countSlider->setAnchorPoint(Vec2(0.5, 0));
    speedSlider = static_cast<ui::Slider*>(countSlider->clone());
    timeSlider = static_cast<ui::Slider*>(countSlider->clone());

    countSlider->setMaxPercent(50);
    speedSlider->setMaxPercent(1000);

    countSlider->setPercent(config.getCount());
    speedSlider->setPercent(config.getSpeed());
    timeSlider->setPercent(config.getTime());

    countSlider->addEventListener(CC_CALLBACK_0(SettingsScene::setCountField, this));
    speedSlider->addEventListener(CC_CALLBACK_0(SettingsScene::setSpeedField, this));
    timeSlider->addEventListener(CC_CALLBACK_0(SettingsScene::setTimeField, this));

    // Text fields
    countField = ui::TextField::create("40", "Fonts/DSMarkerFelt.ttf", 24);
    speedField = static_cast<ui::TextField*>(countField->clone());
    timeField = static_cast<ui::TextField*>(speedField->clone());

    countField->setString(std::to_string(config.getCount()));
    speedField->setString(std::to_string(config.getSpeed()));
    timeField->setString(std::to_string(config.getTime()));

    countField->addEventListener(CC_CALLBACK_0(SettingsScene::setCountSlider, this));
    speedField->addEventListener(CC_CALLBACK_0(SettingsScene::setSpeedSlider, this));
    timeField->addEventListener(CC_CALLBACK_0(SettingsScene::setTimeSlider, this));

    // Positions
    countText->setPosition(Vec2(visibleSize.width / 2, title->getPosition().y - countText->getContentSize().height - 25));
    countSlider->setPosition(Vec2(visibleSize.width / 2, countText->getPosition().y - countSlider->getContentSize().height - 25));
    countField->setPosition(Vec2(visibleSize.width / 2 + countSlider->getContentSize().width / 2 + 25, countSlider->getPosition().y));

    speedText->setPosition(Vec2(visibleSize.width / 2, countSlider->getPosition().y - speedText->getContentSize().height - 25));
    speedSlider->setPosition(Vec2(visibleSize.width / 2, speedText->getPosition().y - speedSlider->getContentSize().height - 25));
    speedField->setPosition(Vec2(visibleSize.width / 2 + speedSlider->getContentSize().width / 2 + 25, speedSlider->getPosition().y));

    timeText->setPosition(Vec2(visibleSize.width / 2, speedSlider->getPosition().y - timeText->getContentSize().height - 25));
    timeSlider->setPosition(Vec2(visibleSize.width / 2, timeText->getPosition().y - timeSlider->getContentSize().height - 25));
    timeField->setPosition(Vec2(visibleSize.width / 2 + timeSlider->getContentSize().width / 2 + 25, timeSlider->getPosition().y));

    this->addChild(countText);
    this->addChild(speedText);
    this->addChild(timeText);

    this->addChild(countField);
    this->addChild(speedField);
    this->addChild(timeField);

    this->addChild(countSlider);
    this->addChild(speedSlider);
    this->addChild(timeSlider);

    // Cancel and confirm buttons
    auto *cancelButton = ui::Button::create("UI/OrangeButtonNormal.png", "UI/OrangeButtonPressed.png");
    cancelButton->setTitleFontName("Fonts/DSMarkerFelt.ttf");
    cancelButton->setTitleFontSize(22);
    auto *applyButton = ui::Button::create("UI/BlueButtonNormal.png", "UI/BlueButtonPressed.png");
    applyButton->setTitleFontName("Fonts/DSMarkerFelt.ttf");
    applyButton->setTitleFontSize(22);

    cancelButton->setTitleText("Cancel");
    applyButton->setTitleText("Apply");

    cancelButton->addClickEventListener(CC_CALLBACK_0(SettingsScene::cancelSettings, this));
    applyButton->addClickEventListener(CC_CALLBACK_0(SettingsScene::applySettings, this));

    // Buttons container
    auto *menuLayout = ui::HBox::create();
    menuLayout->addChild(cancelButton);
    menuLayout->addChild(applyButton);
    menuLayout->setPosition(Vec2(visibleSize.width / 2 - cancelButton->getContentSize().width, visibleSize.height * 0.25f));
    this->addChild(menuLayout);

    return true;
}

void SettingsScene::applySettings()
{
    SimpleAudioEngine::getInstance()->playEffect("Sounds/Click.ogg");

    config.setCount(countSlider->getPercent());
    config.setSpeed(speedSlider->getPercent());
    config.setTime(timeSlider->getPercent());
    config.writeConfig();

    auto *mainMenuScene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, mainMenuScene));
}

void SettingsScene::cancelSettings()
{
    SimpleAudioEngine::getInstance()->playEffect("Sounds/Click.ogg");

    auto *mainMenuScene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, mainMenuScene));
}

void SettingsScene::setCountSlider()
{
    int value;
    try {
        value = std::stoi(countField->getString());
    } catch (...) {
        value = 0;
    }

    countSlider->setPercent(value);
}

void SettingsScene::setSpeedSlider()
{
    int value;
    try {
        value = std::stoi(speedField->getString());
    } catch (...) {
        value = 0;
    }

    speedSlider->setPercent(value);
}

void SettingsScene::setTimeSlider()
{
    int value;
    try {
        value = std::stoi(timeField->getString());
    } catch (...) {
        value = 0;
    }

    timeSlider->setPercent(value);
}

void SettingsScene::setCountField()
{
    countField->setString(std::to_string(countSlider->getPercent()));
}

void SettingsScene::setSpeedField()
{
    speedField->setString(std::to_string(speedSlider->getPercent()));
}

void SettingsScene::setTimeField()
{
    timeField->setString(std::to_string(timeSlider->getPercent()));
}
