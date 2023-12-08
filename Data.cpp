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

void Ship::UpgradeShip(ShipType shipRequirements[]){
    if(type != 3)
    {
        if(CheckElems(shipRequirements) == 0)
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

bool Ship::CheckElems(ShipType shipRequirements[]){
    if((wood < shipRequirements[type-1].wood) || (iron < shipRequirements[type-1].iron) || (rope < shipRequirements[type-1].rope))
        return false;
    return true;
}

void Ship::CheckInv(){
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

void Ship::StoreItem(int typeOfItem, int valueOfItem){
    if(typeOfItem == 1)
        wood+=valueOfItem;
    else if(typeOfItem == 2)
        iron+=valueOfItem;
    else if(typeOfItem == 3)
        rope+=valueOfItem;
}

void Ship::Sail(){
    std::cout<<"Sailing to next land...\n";
}

uint32_t Ship::getShipType(){
    return type;
}

//----------- End Ship functions ----------------//

//----------- Start Player functions ---------------//
void Player::SetName(char* desiredName){
    strcpy(desiredName, name);
}

void Player::Eat(int slot){
    if(inventory[slot-1].type != 2)
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

void Player::Drink(int slot){
    if(inventory[slot-1].type != 3)
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

void Player::Pickup(location *pos){
    int position;

    if(inventory[INV_SIZE-1].value != 0)
    {
        std::cout << "All inventory slots taken!\n";
        return;
    }
    else
    {
        for(int i = 0; i < INV_SIZE; i++)
        {
            if(inventory[i].value == 0)
            {
                position = i;
                break;
            }
        }
        SetInventorySlot(pos->itemAtLocation(), pos->valueOfItemAtLocation(), position);
        pos->deleteElem();
    }
}

void Player::SetInventorySlot(uint32_t element, uint32_t itemValue, int inventoryPosition){
    inventory[inventoryPosition].type = element;
    inventory[inventoryPosition].value = itemValue;
}

bool Player::checkInvForItem(uint32_t slot){
    if(inventory[slot-1].value)
        return true;
    else
        return false;
}

void Player::removeItemFromInv(uint32_t slot){
    SetInventorySlot(0, 0, slot-1);
}

uint32_t Player::getItemType(int slot){
    return inventory[slot-1].type;
}

uint32_t Player::getItemValue(int slot){
    return inventory[slot-1].value;
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
            playerInfo->Eat(itemSlot);
        else
            playerInfo->Drink(itemSlot);
    }
}