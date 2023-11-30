#include <iostream>
#include <cstring>
#include <Data.hh>
#include <Data.cpp>

#define MAX_COMMANDS_SIZE 16

void StoryLine();
void StartCommands();
void listOfCommands();
void PlayGame();
void StartGame();

int main(){
    //Initialize data --> done
    PlayGame();
    //Release data

    return 0;
}

void StoryLine(){
    std::cout << "Arrrrg mattey!\n\t \
                Welcome to the Legend of Barthemious the Wicked, most cruel and gold driven pirate of them all.\n\t \
                He was so keen to becoming the richest pirate that he sacrificed his whole crew to gain mountains of gold.\n\t \
                Legend says that in his madness he hid his gold somewhere in Sea of Desires and that madness drowe him to his death.\n\t \
                It's up to you to find it and break curse which captain Barthemious called upon all pirates when he thought\n\t \
                that they had stolen his gold. You have to save all other pirates from it by lighting torch which captain left at location,\n\t \
                curse brings clouds and bad luck to everybody sailing this waters. This adventure won't be easy, you will have\n\t \
                to find clues and break down captain's markings about location of gold. Be careful, your decision chooses fate\n\t \
                of all other pirates which sail this waters!\n \
                Good luck mattey!\n";
}

void StartCommands(){
    std::cout << "/commands - List of commands\n \
                  /start - Start game\n \
                  /exit - Exit game\n"
}

void listOfCommands(){
    std::cout << "/eat_<x> - Eat item at inventory slot x, e.g. /eat_4  <--- eats item at slot 4\n \
                  /drink_<x> - Drink item at inventory slot x, e.g. /drink_4  <--- drinks item at slot 4\n \
                  /pickup - Picks item up from current location\n \
                  /upgrade - Upgrade ship\n \
                  /shipinv - Check ship's inventory (building materials)\n \
                  /commands - List of commands\n \
                  /exit - Exit game\n"
}

void PlayGame(){
    bool acceptableCommand = true;
    char command[MAX_COMMANDS_SIZE];

    StartCommands();
    while(acceptableCommand)
    {
        std::cin >> command;
        switch(command)
        {
            case "/start":
                StartGame();
                acceptableCommand = false;
                break;
            case "/commands":
                listOfCommands();
                break;
            case "/exit":
                std::cout << "Exiting game...\n";
                acceptableCommand = false;
                break;
            default:
                std::cout << "Unknown command\n";
                break;
        }
    }
}

void StartGame()
{
    bool gameOngoing = true;
    bool gameEnds = false;
    char command[MAX_COMMANDS_SIZE];

    StoryLine();
    while(gameOngoing)
    {
        std::cin >> command;
        switch(command)
        {
            case "/commands":
                listOfCommands();
                break;
            case "/pickup":
                //check map if anything can be picked up
                break;
            case "/exit":
                std::cout << "Exiting game...\n";
                gameOngoing = false;
                break;
            default:
                std::cout << "Unknown command\n";
                break;
        }
        if(gameEnds)
            gameOngoing = false;
    }
}