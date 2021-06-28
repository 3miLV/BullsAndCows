#ifndef __FILE_H__
#define __FILE_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include "player.hpp"
#include "game.hpp"
#include "globalVariables.hpp"


class MyFile
{
public:

    /**
     * Read game progress from the saved file.
     * @param filename File where the process is saved.
     * @return class Game object.
     */
    Game readGameProgress(const std::string &filename)
    {
        Player player;
        Game game;

        std::vector<std::string> v;
        std::string pl, sec;
        std::vector<std::string> secret;

        std::ifstream ifile;
        ifile.open(filename.c_str());

        if(!ifile)
        {
            std::cerr << "the file cannot be read" << std::endl;
        }

        std::string line, buffer;
        ifile >> pl >> sec;
        game.setSecret(sec, pl);
        ifile >> pl >> sec;
        game.setSecret(sec, pl);

        while(std::getline(ifile, line))
        {
            std::istringstream ss(line);
            ss >> buffer;
            player.setName(buffer);
            ss >> buffer;
            v.push_back("number: " + buffer + " |");
            ss >> buffer;
            v.push_back("bulls: " + buffer + " |");

            if(buffer == "4"){
                gBulls = 4;
                gIsLoad = 1;
            }

            ss >> buffer;
            v.push_back("cows: " + buffer);
            game.setGameResult(v, player.getName());
            v.clear();
        }

        ifile.close();
        return game;
    }

    /**
     * records the secret number in a save file.
     * @param filename File where to save secret number.
     * @param player Player name.
     * @param num Secret number.
     */
    void writeSecret(const std::string &filename, const std::string player, const std::string num)
    {
        std::ofstream ofile;
        ofile.open(filename.c_str(), std::ofstream::app);

        if(!ofile)
        {
            std::cerr << "Failed to create file" << std::endl;
        }

        ofile << player << " " << num;
        ofile << "\n";
        ofile.close();
    }

    /**
     * Records the current progress of the game in file.
     * @param filename File where to save progress.
     * @param name Player name.
     * @param current curent progress.
     */
    void writeGameProgress(const std::string &filename, const std::string name, const std::vector<std::string> &current)
    {
        std::ofstream ofile;
        ofile.open(filename.c_str(), std::ofstream::app);

        if(!ofile)
        {
            std::cerr << "Failed to create file" << std::endl;
        }

        ofile << name << " ";

        for(auto it : current)
        {
            for(auto i : it)
            {
                if(isdigit(i)){
                    ofile << i;
                }
            }

            ofile << " ";
        }

        ofile << "\n";
        ofile.close();
    }


    /**
     * Prints a history of previous games.
     * @param filename File where the game history is saved.
     */
    void readGameHistory(const std::string &filename)
    {
        int i=1;
        std::ifstream ifile;
        ifile.open(filename.c_str());

        if(!ifile)
        {
            std::cerr << "No game history" << std::endl;
        }

        std::string line;
        std::cout << "***********************************\n";

        while(std::getline(ifile, line))
        {
            if(line == "[]")
            {
                line = "";
            }

            std::cout << line << "\n";
            if(line.substr(0,9) == "Game end!")
                std::cout << "***********************************\n";
        }

        ifile.close();
    }


    /**
     * Save game history after end of game.
     * @param filename File where the game history will be saved.
     * @param stringMap std::map with game data.
     * @param name A player who has won the game or draw.
     */
    void writeGameHistory(const std::string &filename, const std::map<std::string, std::vector<std::vector<std::string>>> &stringMap, std::string name)
    {
        std::ofstream ofile;
        ofile.open(filename.c_str(), std::ofstream::app);

        if(!ofile)
        {
            std::cerr << "history record failed" << std::endl;
        }

        for(auto iter = stringMap.begin(); iter!=stringMap.end(); iter++){
            ofile << iter->first << "\n[";

            for(auto itv : iter->second)
            {
                for(auto it : itv)
                {
                    ofile << it;
                }

                ofile << "]\n[";
            }

            ofile << "]";
            ofile << "\n";
        }

        ofile << "Game end!" << name;
        ofile << "\n";
        ofile.close();
    }
};


#endif // __FILE_H__
