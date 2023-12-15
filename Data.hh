#pragma once
#include <iostream>
#include <cstdint>
#include "locations.hh"
#define MAX_NAME 32
#define MAX_FOOD_AND_THIRST_LEVEL 5
#define INV_SIZE 5

enum consumation{
    eating = 1,
    drinking
};

struct Status {
    uint32_t food = MAX_FOOD_AND_THIRST_LEVEL;
    uint32_t thirst = MAX_FOOD_AND_THIRST_LEVEL;
};

/*item types:
    0 - empty/no elem
    1 - wood
    2 - iron
    3 - rope
    4 - food
    5 - drink
*/

struct Item {
    uint32_t type;
    uint32_t value;
};

struct ShipType {
    uint32_t iron;
    uint32_t wood;
    uint32_t rope;
    ShipType(uint32_t ironValue, uint32_t woodValue, uint32_t ropeValue);
};

class Player {
    private:
        char name[MAX_NAME];
        Status stats;
        Item inventory[INV_SIZE];
        bool playerIsAlive;
    public:
        Player();
        void setName(char* desiredName);
        void eat(int slot);
        void drink(int slot);
        void pickup(location *pos);
        void setInventorySlot(uint32_t element, uint32_t itemValue, int inventoryPosition);
        bool checkInvForItem(uint32_t slot);
        void removeItemFromInv(uint32_t slot);
        uint32_t getItemType(int slot);
        uint32_t getItemValue(int slot);
        void changePlayerStats(uint32_t consumationType);
        uint32_t getPlayerHunger();
        uint32_t getPlayerThirst();
        bool isStorableItem(int slot);
        bool checkIsPlayerAlive();
        char *inventoryItemToString(int slot);
};

class Ship{
    private:
        bool damaged = false;
        uint32_t type;
        uint32_t iron = 2;
        uint32_t wood = 5;
        uint32_t rope = 0;
    public:
        Ship();
        void upgradeShip(ShipType shipRequirements[]);
        bool checkElems(ShipType shipRequirements[]);
        void checkInv();
        const char* typeToClass(int shipType);
        void storeItem(int typeOfItem, int valueOfItem);
        void sail();
        uint32_t getShipType();
};

void consumingItem(Player *playerInfo, uint32_t functionOfConsuming);