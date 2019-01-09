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

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

class ConfigParser
{
public:
    ConfigParser();

    int getCount() const;
    int getSpeed() const;
    int getTime() const;

    void setCount(int value);
    void setSpeed(int value);
    void setTime(int value);

    void writeConfig();

private:
    int count;
    int speed;
    int time;
};

#endif // CONFIGPARSER_H
