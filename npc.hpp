#ifndef __NPC_H__
#define __NPC_H__

#include "player.hpp"
#include <random>
#include <functional>

#include <algorithm>
#include <string>
#include <chrono>

class NPC : public Player
{
public:

    /**
     * Generate random numbers for a computer player.
     * @return Four digit number
     */
    std::string generateRandomNum()
    {
        int counter =0;
        std::string generatedNum;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        generatedNum = "1234567890";

        std::shuffle(generatedNum.begin(), generatedNum.end(), std::default_random_engine(seed));

        return generatedNum.substr(0,4);
    }
};

#endif // __NPC_H__
