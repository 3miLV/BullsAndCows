// This file is part of BullsAndCows.

// BullsAndCows is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// BullsAndCows is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with BullsAndCows.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>


/**
 * Implementation of players in the game.
 */
class Player
{
protected:

    std::string playerName, secretNum;

public:

    Player(){}
    Player(std::string name, std::string num):playerName(name), secretNum(num){}
    ~Player(){}


    /**
     * Gets player name.
     * @return Player name.
    */
    std::string getName() const
    {
        return this->playerName;
    }


    /**
     * Set player name.
     * @param name Player name
     */
    void setName(std::string name)
    {
        this->playerName = name;
    }


    /**
     * Gets player secret number
     * @return Player secret number
     */
    std::string getSecretNum() const
    {
        return this->secretNum;
    }


    /**
     * Set player secret number.
     * @param num Player secret number.
     */
    void setSecretNum(std::string num)
    {
        this->secretNum = num;
    }
};

#endif // __PLAYER_H__
