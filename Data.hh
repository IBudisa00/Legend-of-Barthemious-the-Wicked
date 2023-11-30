#include <iostream>
#define MAX_NAME 32
#define MAX_FOOD_AND_THIRST_LEVEL 5
#define INV_SIZE 5

struct Status {
    uint32_t food = MAX_FOOD_AND_THIRST_LEVEL;
    uint32_t thirst = MAX_FOOD_AND_THIRST_LEVEL;
};

/*
  type of items:
    0 - EMPTY SLOT
    1 - building
    2 - food
    3 - drink

  itemName list:
    1 - Wood
    2 - Iron
    3 - Rope
    4 - Rum
    5 - Crab
*/
struct Item {
    uint32_t type;
    int itemName;
    uint32_t value;
}

struct ShipType {
    uint32_t iron;
    uint32_t wood;
    uint32_t rope;
};

class Player {
    private:
        char name[MAX_NAME];
        uint32_t health_point = 100;
        Status stats;
        Item inventory[INV_SIZE]; 
    public:
        void SetName(char* desiredName);
        void Eat(int slot);
        void Drink(int slot);
        void Pickup();
};

class Ship{
    private:
        bool damaged == false;
        uint32_t type;
        uint32_t iron = 2;
        uint32_t wood = 5;
        uint32_t rope = 0;
    public:
        Ship();
        void UpgradeShip();
        bool CheckElems();
        void CheckInv();
        char* typeToClass(int shipType);
        void StoreItem(int typeOfItem, int nameOfItem, int valueOfItem);
        void Sail();
};