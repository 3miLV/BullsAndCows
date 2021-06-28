#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"
#include "game.hpp"
#include "file.hpp"
#include "npc.hpp"
#include "globalVariables.hpp"

#ifdef _WIN32
#include <io.h>
#include <Windows.h>
#define access    _access_s
#else
#include <unistd.h>
#endif

void gameMenu(std::vector<Player> player, Game currentState, MyFile file);


/*Adds time to wait before the npc responds*/
void mySleep()
{
#if defined _WIN32
    Sleep(1);
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
    sleep(1);
#endif
}


/**
* Checks if a saved game file exists.
* @param filename  The name of the file where it is saved.
* @return true if file exists or false if not.
*/
bool fileExists(const std::string& filename)
{
    return access(filename.c_str(), 0) == 0;
}


/*clears the console*/
void clearConsole()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
    system("clear");
#endif
}


/**
* Checks if the number entered by the player is correct.
* @param guess Player guess number.
* @return true if correct or false if not and prints the error message.
*/
bool checkNums(std::string guess)
{
    if (guess.size() != 4)
    {
        std::cout << "you must enter a 4 digit number!" << "\n";
        std::cout << "enter number: ";
        return false;
    }

    for (auto ch : guess)
    {
        if (!isdigit(ch))
        {
            std::cout << "The input must contain only numbers!" << "\n";
            std::cout << "enter number: ";
            return false;
        }
    }

    for (int i = 0; i < guess.size() - 1; i++)
    {
        for (int j = i + 1; j < guess.size(); j++)
        {
            if (guess[i] == guess[j])
            {
                std::cout << "there must be no duplicate digits in the number!" << "\n";
                std::cout << "enter number: ";
                return false;
            }
        }
    }
    return true;
}


/**
* Checks the result of the player's guess number.
* @param secret The secret number of the opposing player.
* @param guess Player guess number.
* @param playerName The name of the player who guesses.
* @return std::vector with three string elements:
    the assumed number, the number of bulls, the numbers of cows
*/
std::vector<std::string> findBullsCows(std::string secret, std::string guess, std::string playerName)
{
    int bulls = 0, cows = 0;
    std::vector<std::string> guesses;

    for (int i = 0; i < secret.size(); i++)
    {
        if (secret[i] == guess[i])
        {
            bulls++;
        }

        for (int j = 0; j < secret.size(); j++)
        {
            if ((guess[j] == secret[i]) && (guess[i] != secret[i]))
            {
                cows++;
            }
        }
    }

    // Sets the global variable gBulls to the number of current bulls.
    gBulls = bulls;

    guesses.push_back("number: " + guess + " |");
    guesses.push_back("bulls: " + std::to_string(bulls) + " |");
    guesses.push_back("cows: " + std::to_string(cows));
    return guesses;
}


/**
 * Returns std::vector with Player object elements.
 * @param pls Numbers of human players.
 * @param file File to save the name and secret number of the players.
 * @return std::vector with class Player object elements.
 */
std::vector<Player> addPlayers(int pls, MyFile file)
{
    std::string name, secret;
    std::vector<Player> player;
    NPC npc;

    for (int i = 0; i < pls; i++)
    {
        std::cout << "add name for player " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "enter  number for " << name << ": ";
        std::cin >> secret;

        // Check if secret number is correct.
        while (checkNums(secret) != true)
        {
            std::cin >> secret;
        }

        player.push_back(Player(name, secret));
        file.writeSecret("progress.txt", player[i].getName(), player[i].getSecretNum());

        // Checks if the player is the one to add computer player
        if (pls == 1)
        {
            npc.setName("glupcho");
            mySleep();
            npc.setSecretNum(npc.generateRandomNum());
            name = npc.getName();
            secret = npc.getSecretNum();
            player.push_back(Player(name, secret));
            file.writeSecret("progress.txt", name, secret);
            gCheckNpc = 1;
        }
        clearConsole();
    }
    return player;
}


/**
 * Returns std::vector with Player object elements restored from the saved file.
 * @param pls Numbers of human players.
 * @param playersMap std::map with the name and secret number of the players.
 * @return std::vector with class Player object elements.
 */
std::vector<Player> recoveryPlayers(int pls, std::map<std::string, std::string> playersMap)
{
    std::vector<Player> player;

    for (auto it : playersMap)
    {
        player.push_back(Player(it.first, it.second));
    }
    return player;
}


/**
 * Initialization and update of the game process.
 * @param state class Game object for processing the instant progress of the game.
 * @param player std::vector with class Player object elements.
 * @param file class File object for writing and reading game progress.
 */
void gameLoop(Game state, std::vector<Player> player, MyFile file)
{
    NPC npc;    // Computer player object

    int turn = 1, end = 1, temp = 0;
    std::string guess;
    std::vector<std::string> currentGuess;

    if(state.checkGameResult(player[0].getName()))
    {
        turn = state.getGameResultSize(player[0].getName()) + 1;
    }

    if (state.getGameResultSize(player[0].getName()) > state.getGameResultSize(player[1].getName()))
    {
        temp = 1;
        turn = state.getGameResultSize(player[1].getName()) + 1;
    }

    while (end != 0)
    {
        for (int i = temp; i < 2; i++)
        {
            std::cout << "**" << gBulls << "**";
            if(gBulls == 4){ // Checks if the player has known a number after loading the interrupted game.
                goto jump;
            }

            mySleep();
            clearConsole();
            std::cout << "\n";
            std::cout << player[i].getName() << " turn " << turn << ": " << std::endl;
            std::cout << "---------------------\n";

            if (gCheckNpc != 1)
            {
                state.printGameResult(player[i].getName());
                std::cout << "enter number: ";
                std::cin >> guess;

                while (checkNums(guess) != true)
                {
                    std::cin >> guess;
                }
            }
            else
            {
                if (i == 1)
                {
                    state.printGameResult(player[i].getName());
                    mySleep();
                    guess = npc.generateRandomNum();
                }
                else
                {
                    state.printGameResult(player[i].getName());
                    std::cout << "enter number: ";
                    std::cin >> guess;
                    while (checkNums(guess) != true)
                    {
                        std::cin >> guess;
                    }
                }
            }

            if (i == 0)
            {
                currentGuess = findBullsCows(player[i + 1].getSecretNum(), guess, player[i].getName());
            }
            else if (i == 1)
            {
                currentGuess = findBullsCows(player[i - 1].getSecretNum(), guess, player[i].getName());
            }

            state.setGameResult(currentGuess, player[i].getName());
            file.writeGameProgress("progress.txt", player[i].getName(), currentGuess);
            currentGuess.clear();
        jump:
            if (gBulls == 4)
            {
                if (i == 0 || gIsLoad == 1)
                {
                    i = 0;
                    std::cout << "*" << gBulls << "*";
                    clearConsole();
                    std::cout << player[i].getName() << " guessed " << player[i + 1].getName() << " the secret number" << std::endl;
                    std::cout << "last chance for " << player[i + 1].getName() << ": " << std::endl;
                    std::cout << "---------------------\n";

                    if (gCheckNpc != 1)
                    {
                        state.printGameResult(player[i + 1].getName());
                        std::cout << "enter number: ";
                        std::cin >> guess;

                        while (checkNums(guess) != true)
                        {
                            std::cin >> guess;
                        }
                    }
                    else
                    {
                        state.printGameResult(player[i + 1].getName());
                        mySleep();
                        guess = npc.generateRandomNum();
                    }

                    currentGuess = findBullsCows(player[i].getSecretNum(), guess, player[i].getName());
                    state.setGameResult(currentGuess, player[i + 1].getName());
                    currentGuess.clear();

                    if (gBulls == 4)
                    {
                        state.printGameResult(player[i + 1].getName());
                        clearConsole();
                        std::cout << "*****************************\n";
                        std::cout << "Game end with draw. " << std::endl;
                        std::cout << "*****************************\n";
                        file.writeGameHistory("gamehistory.txt", state.getGameResult(), " draw");
                        std::remove("progress.txt");
                        state.clear();
                        gBulls = 0;
                        gCheckNpc = 0;
                        gIsLoad = 0;
                        gameMenu(player, state, file);
                    }
                }

                state.printGameResult(player[i].getName());
                clearConsole();
                std::cout << "*****************************\n";
                std::cout << "congratulations " << player[i].getName() << " won the game." << std::endl;
                std::cout << "*****************************\n";
                file.writeGameHistory("gamehistory.txt", state.getGameResult(), (" winer: " + player[i].getName()));
                std::remove("progress.txt");
                state.clear();
                gBulls = 0;
                gCheckNpc = 0;
                gIsLoad = 0;
                gameMenu(player, state, file);
            }
        }
        temp = 0;
        turn++;
    }
}


/**
 * Main menu of the game.
 * @param player std::vector with class Player object elements.
 * @param curentState class Game object for processing the instant progress of the game.
 * @param file class File object for writing and reading game progress
 */
void gameMenu(std::vector<Player> player, Game currentState, MyFile file)
{
    int end = 1, pls;
    std::string choice;

    while (end)
    {
        std::cout << "-----------------------------\n";
        std::cout << "WELCOME TO BULLS AND COWS" << std::endl;
        std::cout << "-----------------------------\n";
        std::cout << "To play with computer press 1." << std::endl;
        std::cout << "To play with friend press 2." << std::endl;
        std::cout << "For games history press 3." << std::endl;
        std::cout << "For exit from game press 4." << std::endl;
        std::cout << "-----------------------------\n";

        std::cin >> choice;

        if (choice == "1")
        {
            clearConsole();
            std::cout << "-----------------------------\n";
            std::cout << "Starting game vs computer." << std::endl;
            std::cout << "-----------------------------\n";
            std::remove("progress.txt");
            pls = 1;
            player = addPlayers(pls, file);
            gameLoop(currentState, player, file);
        }
        else if (choice == "2")
        {
            clearConsole();
            std::cout << "-----------------------------\n";
            std::cout << "Starting game vs friend." << std::endl;
            std::cout << "-----------------------------\n";
            std::remove("progress.txt");
            pls = 2;
            player = addPlayers(pls, file);
            gameLoop(currentState, player, file);
        }
        else if (choice == "3")
        {
            clearConsole();
            file.readGameHistory("gamehistory.txt");
        }
        else if (choice == "4")
        {
            clearConsole();
            std::cout << "Exit from game!" << std::endl;
            exit(0);
        }
        else
        {
            clearConsole();
            std::cout << "-----------------------------\n";
            std::cout << "Invalid selection." << std::endl;
            std::cout << "Please select the correct option from the main menu." << std::endl;
            std::cout << "-----------------------------\n";
            gameMenu(player, currentState, file);
        }
    }
}


int main()
{
    int pls=0, choice;
    std::vector<Player> player;
    Game currentState;
    MyFile file;

    clearConsole();

    if (fileExists("progress.txt"))
    {
        std::cout << "-----------------------------\n";
        std::cout << "An unfinished game was found!" << std::endl;
        std::cout << "If you want to restore it press 1." << std::endl;
        std::cout << "To return to the main menu press 2." << std::endl;
        std::cout << "-----------------------------\n";
        std::cin >> choice;

        if (choice == 1)
        {
            clearConsole();
            std::cout << "-----------------------------\n";
            std::cout << "Recover previous game data!" << std::endl;
            std::cout << "-----------------------------\n";
            currentState = file.readGameProgress("progress.txt");
            pls = 2;
            player = recoveryPlayers(pls, currentState.getSecret());

            try
            {
                player[1].getName();
            }
            catch(std::logic_error){
                std::remove("progress.txt");
                std::cout << "-----------------------------\n";
                std::cout << "The previous game cannot be restored." << "\n";
                std::cout << "Return to the main menu!" << "\n";
                std::cout << "-----------------------------\n";
                gameMenu(player, currentState, file);
            }

            if (player[1].getName() == "glupcho")
            {
                gCheckNpc = 1;
            }

            std::cout << "\n";
            gameLoop(currentState, player, file);
        }
        else if (choice == 2)
        {
            std::remove("progress.txt");
            clearConsole();
            gameMenu(player, currentState, file);
        }
    }
    gameMenu(player, currentState, file);

    return 0;
}
