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
