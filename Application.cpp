#include <iostream>
#include <cstring>
#include <conio.h>
#include "locations.hh"
#include "Data.hh"

#define MAX_COMMANDS_SIZE 16

void StoryLine();
void StartCommands();
void listOfCommands();
void PlayGame();
void StartGame();
uint32_t commandToInt(char *command);
void printMap(location gameMap[MAP1_X_CORD][MAP1_Y_CORD]);
bool checkRequirementsForSailing(Ship ship);

int main(){
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
                  /exit - Exit game\n";
};

void listOfCommands(){
    std::cout << "/eat - Open inventory to eat\n \
                  /drink - Open inventory to drink\n \
                  /pickup - Picks item up from current location\n \
                  /upgrade - Upgrade ship\n \
                  /shipinv - Check ship's inventory (building materials)\n \
                  /sail - Sail to next island\n \
                  /store - Store items from inventory to ship (only wood, iron and rope can be stored)\n \
                  /commands - List of commands\n \
                  /exit - Exit game\n";
};

void PlayGame(){
    bool acceptableCommand = true;
    char command[MAX_COMMANDS_SIZE];

    StartCommands();
    while(acceptableCommand)
    {
        std::cin >> command;
        switch(commandToInt(command))
        {
            case 1:
                StartGame();
                acceptableCommand = false;
                break;
            case 2:
                listOfCommands();
                break;
            case 3:
                std::cout << "Exiting game...\n";
                acceptableCommand = false;
                break;
            case 0:
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
    char desiredName[MAX_NAME];
    location map1[MAP1_X_CORD][MAP1_Y_CORD];
    location *position = &map1[0][4];
    Player player;
    Player *playerPointer = &player;
    Ship ship;
    ShipType shipRequirements[2] = {ShipType(8, 12, 6), ShipType(16, 24, 12)};

    areaCoordinatesSetting(map1);
    setStartingMap(map1);
    StoryLine();
    std::cout <<"Enter your name: ";
    std::cin >> desiredName;
    playerPointer->SetName(desiredName);
    while(gameOngoing)
    {
        std::cin >> command;
        switch(commandToInt(command))
        {
            case 2:
                listOfCommands();
                break;
            case 4:
                if(position->checkExistence())
                {
                    playerPointer->Pickup(position);
                }
                break;
            case 5:
                consumingItem(playerPointer, eat);
                break;
            case 6:
                consumingItem(playerPointer, drink);
                break;
            case 7:
                if(position->getx() == 0)
                {
                    std::cout << "Cannot go there...\n";
                }
                else
                {
                    position->setPlayerIsHere(false);
                    position = &map1[position->getx() - 1][position->gety()];
                    position->setPlayerIsHere(true);
                    printMap(map1);
                }
                break;
            case 8:
                if(position->getx() == 8)
                {
                    std::cout << "Cannot go there...\n";
                }
                else
                {
                    position->setPlayerIsHere(false);
                    position = &map1[position->getx() + 1][position->gety()];
                    position->setPlayerIsHere(true);
                    printMap(map1);
                }
                break;
            case 9:
                if(position->gety() == 0)
                {
                    std::cout << "Cannot go there...\n";
                }
                else
                {
                    position->setPlayerIsHere(false);
                    position = &map1[position->getx()][position->gety() - 1];
                    position->setPlayerIsHere(true);
                    printMap(map1);
                }
                break;
            case 10:
                if(position->gety() == 8)
                {
                    std::cout << "Cannot go there...\n";
                }
                else
                {
                    position->setPlayerIsHere(false);
                    position = &map1[position->getx()][position->gety() + 1];
                    position->setPlayerIsHere(true);
                    printMap(map1);
                }
                break;
            case 11:
                if(position->checkShipAccessibleArea())
                {
                    if(checkRequirementsForSailing(ship))
                        ship.Sail();
                    else
                        std::cout << "Ship must be upgraded before it can be sailed through murky waters.\n";
                }
                else
                {
                    std::cout << "Cannot sail from here, go back to the ship to sail.\n";
                }
            case 12:
                if(position->checkShipAccessibleArea())
                {
                    for(int i = 0; i < INV_SIZE; i++)
                    {
                        if(playerPointer->checkInvForItem(i))
                            ship.StoreItem(playerPointer->getItemType(i),playerPointer->getItemValue(i));
                    }
                }
                else
                {
                    std::cout << "Cannot access ship from here, go back to the ship to store items.\n";
                }
            case 3:
                std::cout << "Exiting game...\n";
                gameOngoing = false;
                break;
            case 0:
                std::cout << "Unknown command\n";
                break;
        }
        if(gameEnds)
            gameOngoing = false;
    }
}

uint32_t commandToInt(char *command){
    if(strcmp(command, "/start") == 0)
        return 1;
    else if(strcmp(command, "/commands") == 0)
        return 2;
    else if(strcmp(command, "/exit") == 0)
        return 3;
    else if(strcmp(command, "/pickup") == 0)
        return 4;
    else if(strcmp(command, "/eat") == 0)
        return 5;
    else if(strcmp(command, "/drink") == 0)
        return 6;
    else if(strcmp(command, "/up") == 0)
        return 7;
    else if(strcmp(command, "/down") == 0)
        return 8;
    else if(strcmp(command, "/left") == 0)
        return 9;
    else if(strcmp(command, "/right") == 0)
        return 10;
    else if(strcmp(command, "/sail") == 0)
        return 11;
    else if(strcmp(command, "/store") == 0)
        return 12;
    else
        return 0;
}

void printMap(location gameMap[MAP1_X_CORD][MAP1_Y_CORD]){
    //clrscr();
    for(int i = 0; i < MAP1_X_CORD; i++)
    {
        for(int j = 0; j < MAP1_Y_CORD; j++)
        {
            if(gameMap[i][j].checkPlayerPosition())
                std::cout << "| P |";
            else
            {
                if(gameMap[i][j].itemAtLocation() == 1)
                    std::cout << "| W |";
                else if(gameMap[i][j].itemAtLocation() == 2)
                    std::cout << "| I |";
                else if(gameMap[i][j].itemAtLocation() == 3)
                    std::cout << "| R |";
                else if(gameMap[i][j].itemAtLocation() == 4)
                    std::cout << "| F |";
                else if(gameMap[i][j].itemAtLocation() == 5)
                    std::cout << "| D |";
                else
                    std::cout << "|   |";
            }
        }
        std::cout <<"\n";
    }
}

bool checkRequirementsForSailing(Ship ship){
    if(ship.getShipType() > 1)
        return true;
    else
        return false;
}