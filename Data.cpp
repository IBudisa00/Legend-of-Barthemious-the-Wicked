#include <iostream>
#include <string.h>
#include <cstdint>
#include "Data.hh"

ShipType::ShipType(uint32_t ironValue, uint32_t woodValue, uint32_t ropeValue){
    iron = ironValue;
    wood = woodValue;
    rope = ropeValue;
}

//----------- Start Ship functions ----------------//
Ship::Ship(){
    //setting starting values for raft
    type = 1;
    iron = 2;
    wood = 5;
    rope = 0;
}

void Ship::upgradeShip(ShipType shipRequirements[]){
    if(type != 3)
    {
        if(checkElems(shipRequirements) == 0)
        {
            std::cout << "Cannot upgrade ship, missing requirements!\n";
            std::cout << "Check ship inventory!\n";
        }
        else
        {
            type++;
            std::cout << "Ship upgraded to " << typeToClass(type) <<"\n";
        }
    }
    else
        std::cout << "Ship is already maximally upgraded.\n";
}

bool Ship::checkElems(ShipType shipRequirements[]){
    if((wood < shipRequirements[type-1].wood) || (iron < shipRequirements[type-1].iron) || (rope < shipRequirements[type-1].rope))
        return false;
    return true;
}

void Ship::checkInv(){
    std::cout << "Iron: "<< iron<<"\n";
    std::cout << "Wood: "<< wood<<"\n";
    std::cout << "Rope: "<< rope<<"\n";
}

const char* Ship::typeToClass(int shipType){
    if(shipType == 1)
        return "Raft";
    else if(shipType == 2)
        return "Gally";
    else
        return "Frigate";
}

void Ship::storeItem(int typeOfItem, int valueOfItem){
    if(typeOfItem == 1)
        wood+=valueOfItem;
    else if(typeOfItem == 2)
        iron+=valueOfItem;
    else if(typeOfItem == 3)
        rope+=valueOfItem;
}

void Ship::sail(){
    std::cout<<"Sailing to next land...\n";
}

uint32_t Ship::getShipType(){
    return type;
}

//----------- End Ship functions ----------------//

//----------- Start Player functions ---------------//
Player::Player(){
    strcpy(name,"Unnamed Entity");
    stats.food = MAX_FOOD_AND_THIRST_LEVEL;
    stats.thirst = MAX_FOOD_AND_THIRST_LEVEL;

    for(int i = 0; i<INV_SIZE; i++)
    {
        inventory[i].value = 0;
        inventory[i].type = 0;
    }
}
void Player::setName(char* desiredName){
    strcpy(name, desiredName);
}

void Player::eat(int slot){
    if(inventory[slot-1].type != 4)
        std::cout << "Item at slot "<< slot <<" isn't food!\n";
    else
    {
        std::cout << "OM NOM NOM\n";
        if(stats.food + inventory[slot-1].value > MAX_FOOD_AND_THIRST_LEVEL)
            stats.food = MAX_FOOD_AND_THIRST_LEVEL;
        else
            stats.food += inventory[slot-1].value;

        for(int i = slot-1; i < INV_SIZE; i++){
            inventory[i].type = inventory[i+1].type;
            inventory[i].value = inventory[i+1].value;
        }
        inventory[INV_SIZE-1].type = 0;
        inventory[INV_SIZE-1].value = 0;
    }

}

void Player::drink(int slot){
    if(inventory[slot-1].type != 5)
        std::cout << "Item at slot "<< slot <<" isn't drink!\n";
    else
    {
        std::cout << "GULP GULP GULP\n";
        if(stats.thirst + inventory[slot-1].value > MAX_FOOD_AND_THIRST_LEVEL)
            stats.thirst = MAX_FOOD_AND_THIRST_LEVEL;
        else
            stats.thirst += inventory[slot-1].value;

        for(int i = slot-1; i < INV_SIZE; i++){
            inventory[i].type = inventory[i+1].type;
            inventory[i].value = inventory[i+1].value;
        }
        inventory[INV_SIZE-1].type = 0;
        inventory[INV_SIZE-1].value = 0;
    }

}

void Player::pickup(location *pos){
    for(int i = 0; i < INV_SIZE; i++)
    {
        if(inventory[i].type == 0)
        {
            setInventorySlot(pos->itemAtLocation(), pos->valueOfItemAtLocation(), i);
            pos->deleteElem();
            return;
        }
    }
    std::cout << "All inventory slots taken!\n";
}

void Player::setInventorySlot(uint32_t element, uint32_t itemValue, int inventoryPosition){
    inventory[inventoryPosition].type = element;
    inventory[inventoryPosition].value = itemValue;
}

bool Player::checkInvForItem(uint32_t slot){
    if(inventory[slot].type)
        return true;
    else
        return false;
}

void Player::removeItemFromInv(uint32_t slot){
    setInventorySlot(0, 0, slot);
}

uint32_t Player::getItemType(int slot){
    return inventory[slot].type;
}

uint32_t Player::getItemValue(int slot){
    return inventory[slot].value;
}

void Player::changePlayerStats(uint32_t consumationType){
    if(consumationType == consumation::eat)
        stats.food--;
    else if(consumationType == consumation::drink)
        stats.thirst--;
    else
        std::cout << "Unknown consumationType...\n";
}

uint32_t Player::getPlayerHunger(){
    return stats.food;
}
uint32_t Player::getPlayerThirst(){
    return stats.thirst;
}

bool Player::isStorableItem(int slot){
    if((inventory[slot].type != 4) && (inventory[slot].type != 5))
        return true;
    else
        return false;
}
//----------- End Player functions ---------------//

void consumingItem(Player *playerInfo, uint32_t functionOfConsuming){
    int itemSlot;
    std::cout << "Select item slot to consume: ";
    std::cin >> itemSlot;
    if(itemSlot > INV_SIZE)
    {
        std::cout << "Invalid slot position, maximum position is 5!\n";
    }
    else
    {
        if(functionOfConsuming == eat)
            playerInfo->eat(itemSlot);
        else
            playerInfo->drink(itemSlot);
    }
}