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

#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "ConfigParser.h"

USING_NS_CC;

class SettingsScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(SettingsScene)

private:
    virtual bool init();

    void applySettings();
    void cancelSettings();

    void setCountSlider();
    void setSpeedSlider();
    void setTimeSlider();
    void setCountField();
    void setSpeedField();
    void setTimeField();

    ui::VBox* menuLayout;
    ui::Slider* countSlider;
    ui::Slider* speedSlider;
    ui::Slider* timeSlider;
    ui::TextField* countField;
    ui::TextField* speedField;
    ui::TextField* timeField;
    ConfigParser config;
};

#endif // SETTINGSSCENE_H
