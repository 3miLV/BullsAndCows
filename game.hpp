#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <string>
#include <vector>
#include <iostream>

class Game
{
private:

    std::map<std::string, std::vector<std::vector<std::string>>> gameResult;
    std::map<std::string, std::string> secret;

public:

    Game(){}
    ~Game(){}


    /**
     * Prints the current progress of the game.
     * @param player Player name.
     */
    void printGameResult(std::string player)
    {
        for(auto it : gameResult[player])
        {
            std::cout << "[ ";
            for(auto it1 : it)
            {
                std::cout << it1;
            }
            std::cout << " ]";
            std::cout << '\n';
        }
    }


    /**
     * Тakes the player's progress
     * @return gameResult The player's progress
     */
    std::map<std::string, std::vector<std::vector<std::string>>> getGameResult() const
    {
        return gameResult;
    }



    /**
     * Тakes the player's secret number
     * @return secret The player's secret number
     */
    std::map<std::string, std::string> getSecret() const
    {
        return secret;
    }


    /**
     * Set the secret number of the given player.
     */
    void setSecret(std::string secret, std::string player)
    {
        this->secret.insert(std::pair<std::string, std::string>(player, secret));
    }


    /**
     * Тakes the number of moves the player has made.
     * @param player Player name.
     */
    int getGameResultSize(std::string player) const
    {
        for(auto it : gameResult)
        {
            if (it.first == player)
            {
                return it.second.size();
            }
        }

        return 0;
    }


    /**
     * Аdds the last move made to the list of previous player moves.
     * @param nums Vector with the last guess.
     * @params player Player name.
     */
    void setGameResult(std::vector<std::string> nums, std::string player)
    {
        this->gameResult[player].push_back(nums);
    }


    /**
     * check if the player has saved moves to get the current move.
     * @param player Player name.
     * @return true if player has moves or false if not.
     */
    bool checkGameResult(std::string player)
    {
        if(gameResult.find(player) == gameResult.end())
        {
            return false;
        }

        return true;
    }


    /**
     * Clear Game class objects after the end of the game
     */
    void clear()
    {
        this->gameResult.clear();
        this->secret.clear();
    }
};

#endif // __GAME_H__
