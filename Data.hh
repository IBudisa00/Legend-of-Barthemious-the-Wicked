#include <iostream>
#define MAX_NAME 32
#define MAX_FOOD_AND_THIRST_LEVEL 5
#define INV_SIZE 5

struct Status {
    uint32_t food = MAX_FOOD_AND_THIRST_LEVEL;
    uint32_t thirst = MAX_FOOD_AND_THIRST_LEVEL;
};

/*type of items:
    0 - EMPTY SLOT
    1 - building
    2 - food
    3 - drink
*/
struct Item {
    uint32_t type;
    uint32_t value;
}

struct ShipType {
    uint32_t iron;
    uint32_t wood;
    uint32_t rope;
} shipRequirements[2];

shipRequirements[0].iron = 8;
shipRequirements[0].wood = 12;
shipRequirements[0].rope = 6;

shipRequirements[1].iron = 16;
shipRequirements[1].wood = 24;
shipRequirements[1].rope = 12;

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
        void UpgradeShip();
        bool CheckElems();
        void CheckInv();
        char* typeToClass(int shipType);
        void StoreItems();
        void Sail();
};