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

#include "ConfigParser.h"

#include "cocos2d.h"

USING_NS_CC;

ConfigParser::ConfigParser()
{
    constexpr int DEFAULT_FISH_COUNT = 13;
    constexpr int DEFAULT_FISH_SPEED = 666;
    constexpr int DEFAULT_FISH_TIME = 13;

    std::string config;

    // Read data from input.txt
    if (FileUtils::getInstance()->getContents("input.txt", &config) != FileUtils::Status::OK) {
        log("Unable to open input.txt");
        count = DEFAULT_FISH_COUNT;
        speed = DEFAULT_FISH_SPEED;
        time = DEFAULT_FISH_TIME;
        return;
    }

    // Parse config
    unsigned long keyPosition = config.find("CountTarget=");
    unsigned long valuePosition = config.find("\n", keyPosition);
    try {
        count = stoi(config.substr(keyPosition + 12, valuePosition));
    } catch (...) {
        log("Unable to read 'CountTarget=' from 'input.txt'");
        count = DEFAULT_FISH_COUNT;
    }

    keyPosition = config.find("Speed=");
    valuePosition = config.find("\n", keyPosition);
    try {
        speed = stoi(config.substr(keyPosition + 6, valuePosition));
    } catch (...) {
        log("Unable to read 'Speed=' from 'input.txt'");
        count = DEFAULT_FISH_SPEED;
    }

    keyPosition = config.find("Time=");
    valuePosition = config.find("\n", keyPosition);
    try {
        time = stoi(config.substr(keyPosition + 5, valuePosition));
    } catch (...) {
        log("Unable to read 'Time=' from 'input.txt'");
        count = DEFAULT_FISH_TIME;
    }
}

int ConfigParser::getCount() const
{
    return count;
}

int ConfigParser::getSpeed() const
{
    return speed;
}

int ConfigParser::getTime() const
{
    return time;
}

void ConfigParser::setCount(int value)
{
    count = value;
}

void ConfigParser::setSpeed(int value)
{
    speed = value;
}

void ConfigParser::setTime(int value)
{
    time = value;
}

void ConfigParser::writeConfig()
{
    std::string config = "CountTarget=" + std::to_string(count) + "\n";
    config.append("Speed=" + std::to_string(speed) + "\n");
    config.append("Time=" + std::to_string(time) + "\n");

    const auto *fileUtils  = FileUtils::getInstance();
    if (fileUtils->writeStringToFile(config, fileUtils->fullPathForFilename("input.txt")))
        log("Unable to write 'input.txt'");
}
