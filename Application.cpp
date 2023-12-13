#include <iostream>
#include <cstring>
#include <conio.h>
#include "locations.hh"
#include "Data.hh"

#define MAX_COMMANDS_SIZE 16

void storyLine();
void startCommands();
void listOfCommands();
void playGame();
void startGame();
uint32_t commandToInt(char *command);
void printMap(location gameMap[MAP1_X_CORD][MAP1_Y_CORD]);
bool checkRequirementsForSailing(Ship ship);
void updatePlayerNeeds(Player *playerPointer, uint32_t needsCounter, bool counterUpdated);
void printInventory(Player *playerPointer);

int main(){
    playGame();
    //Release data

    return 0;
}

void storyLine(){
    std::cout << "\tArrrrg mattey!\n\t \
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

void startCommands(){
    std::cout << "/commands - List of commands\n \
                  /start - Start game\n \
                  /exit - Exit game\n";
};

void listOfCommands(){
    std::cout << "/up - Go up\n \
                  /down - Go down\n \
                  /left - Go left\n \
                  /right - Go right\n \
                  /eat - Open inventory to eat\n \
                  /drink - Open inventory to drink\n \
                  /pickup - Picks item up from current location\n \
                  /upgrade - Upgrade ship\n \
                  /shipinv - Check ship's inventory (building materials)\n \
                  /sail - Sail to next island\n \
                  /store - Store items from inventory to ship (only wood, iron and rope can be stored)\n \
                  /commands - List of commands\n \
                  /exit - Exit game\n";
};

void playGame(){
    bool acceptableCommand = true;
    char command[MAX_COMMANDS_SIZE];

    startCommands();
    while(acceptableCommand)
    {
        std::cin >> command;
        switch(commandToInt(command))
        {
            case 1:
                startGame();
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

void startGame()
{
    bool gameOngoing = true;
    char command[MAX_COMMANDS_SIZE];
    char desiredName[MAX_NAME];
    location map1[MAP1_X_CORD][MAP1_Y_CORD];
    location *position = &map1[0][4];
    Player player;
    Player *playerPointer = &player;
    Ship ship;
    ShipType shipRequirements[2] = {ShipType(8, 12, 6), ShipType(16, 24, 12)};
    uint32_t needsCounter = 0;

    areaCoordinatesSetting(map1);
    setStartingMap(map1);
    storyLine();
    std::cout <<"Enter your name: ";
    std::cin >> desiredName;
    playerPointer->setName(desiredName);
    position->setPlayerIsHere(true);
    printMap(map1);

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
                    playerPointer->pickup(position);
                    updatePlayerNeeds(playerPointer, needsCounter, false);
                    printInventory(playerPointer);
                    printMap(map1);
                }
                break;
            case 5:
                consumingItem(playerPointer, eat);
                updatePlayerNeeds(playerPointer, needsCounter, false);
                printInventory(playerPointer);
                printMap(map1);
                break;
            case 6:
                consumingItem(playerPointer, drink);
                updatePlayerNeeds(playerPointer, needsCounter, false);
                printInventory(playerPointer);
                printMap(map1);
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
                    needsCounter++;
                    updatePlayerNeeds(playerPointer, needsCounter, true);
                    printInventory(playerPointer);
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
                    needsCounter++;
                    updatePlayerNeeds(playerPointer, needsCounter, true);
                    printInventory(playerPointer);
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
                    needsCounter++;
                    updatePlayerNeeds(playerPointer, needsCounter, true);
                    printInventory(playerPointer);
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
                    needsCounter++;
                    updatePlayerNeeds(playerPointer, needsCounter, true);
                    printInventory(playerPointer);
                    printMap(map1);
                }
                break;
            case 11:
                if(position->checkShipAccessibleArea())
                {
                    if(checkRequirementsForSailing(ship))
                    {
                        ship.sail();
                        std::cout << "Congrats you escaped to calm waters, continue your life in hapiness and enjoy paradise islands.\n";
                        gameOngoing = false;
                    }
                    else
                        std::cout << "Ship must be upgraded before it can be sailed through murky waters.\n";
                }
                else
                {
                    std::cout << "Cannot sail from here, go back to the ship to sail.\n";
                }
                break;
            case 12:
                if(position->checkShipAccessibleArea())
                {
                    for(int i = 0; i < INV_SIZE; i++)
                    {
                        if(playerPointer->checkInvForItem(i))
                        {
                            ship.storeItem(playerPointer->getItemType(i),playerPointer->getItemValue(i));
                            playerPointer->removeItemFromInv(i);
                        }
                    }
                }
                else
                {
                    std::cout << "Cannot access ship from here, go back to the ship to store items.\n";
                }
                updatePlayerNeeds(playerPointer, needsCounter, false);
                printInventory(playerPointer);
                printMap(map1);
                break;
            case 13:
                if(position->checkShipAccessibleArea())
                {
                    ship.checkInv();
                }
                else
                {
                    std::cout << "Cannot access ship from here, go back to the ship to check inventory.\n";
                }
                updatePlayerNeeds(playerPointer, needsCounter, false);
                printInventory(playerPointer);
                printMap(map1);
                break;
            case 14:
                if(position->checkShipAccessibleArea())
                {
                    ship.upgradeShip(shipRequirements);
                }
                else
                {
                    std::cout << "Cannot upgrade ship from here, go back to the ship.\n";
                }
                updatePlayerNeeds(playerPointer, needsCounter, false);
                printInventory(playerPointer);
                printMap(map1);
                break;
            case 3:
                std::cout << "Exiting game...\n";
                gameOngoing = false;
                break;
            case 0:
                std::cout << "Unknown command\n";
                break;
        }
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
    else if(strcmp(command, "/shipinv") == 0)
        return 13;
    else if(strcmp(command, "/upgrade") == 0)
        return 14;
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

void updatePlayerNeeds(Player *playerPointer, uint32_t needsCounter, bool counterUpdated){
    if(counterUpdated)
    {
        if(needsCounter % 8 == 0)
            playerPointer->changePlayerStats(drink);
        if(needsCounter % 12 == 0)
            playerPointer->changePlayerStats(eat);
    }

    std::cout << "Hunger: "<< playerPointer->getPlayerHunger();
    std::cout << "\tThirst: "<< playerPointer->getPlayerThirst() <<std::endl;
}

void printInventory(Player *playerPointer){
    for(int i = 0; i <INV_SIZE; i++){
        std::cout << "|Slot " << i+1 <<": ";

        if(playerPointer->getItemType(i) == 0)
            std::cout << " \t";
        else
            std::cout << playerPointer->getItemType(i)<< "\t";
    }
    std::cout << "\n";
}