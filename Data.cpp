#include <iostream>
#include <string.h>
#include <Data.hh>

//----------- Start Ship functions ----------------
void Ship::UpgradeShip(){
    if(CheckElems() == 0)
    {
        std::cout << "Cannot upgrade ship, missing requirements!\n";
        std::cout << "Check ship inventory!\n";
    }
    else
    {
        type++;
        std::cout << "Ship upgraded to class " << typeToClass() <<"\n";
    }
}

bool Ship::CheckElems(){
    if((wood < shipRequirements[type-1].wood) || (iron < shipRequirements[type-1].iron) || (rope < shipRequirements[type-1].rope))
        return false;
    return true;
}

void Ship::CheckInv(){
    std::cout << "Iron: "<< iron<<"\n";
    std::cout << "Wood: "<< wood<<"\n";
    std::cout << "Rope: "<< rope<<"\n";
}

char* Ship::typeToClass(int shipType){
    if(shipType == 1)
        return "Raft";
    else if(shipType == 2)
        return "Gally";
    else
        return "Frigate";
}

void Ship::StoreItems(){

}

//----------- End Ship functions ----------------

//----------- Start Player functions ---------------
void Player::SetName(char* desiredName){
    strcpy(desiredName, name);
}

void Player::Eat(int slot){
    if(slot > 5)
    {
        std::cout << "Invalid slot position, maximum position is 5!\n";
        return;
    }

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
    if(slot > 5)
    {
        std::cout << "Invalid slot position, maximum position is 5!\n";
        return;
    }

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

void Player::Pickup(){
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
        inventory[position].type = //nesto sa mape sto je proslijednjeo u fju
        inventory[position].value = //nesto sa mape sto je proslijednjeo u fju
        //obrisat elem sa mape
    }
}
//----------- End Player functions ---------------