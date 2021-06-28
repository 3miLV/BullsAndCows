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
