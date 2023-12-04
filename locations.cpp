#include <iostream>
#include <stdint>
#include <locations.hh>

location::location(){
    shipAccessibleArea = false;
    playerIsHere = false;
    elem = 0;
    value = 0;
}

void location::setLocation(uint32_t element, uint32_t inputValue){
    elem = element;
    value = inputValue;
}

void location::setShipAccessibleArea(){
    shipAccesableArea = true;
}

void location::deleteElem(){
    elem = 0;
    value = 0;
}

bool location::checkExistence(){
    if(elem != 0)
        return true;
    else
    {
        std::cout << "Nothing to be picked up.\n";
        return false;
    }
}

void location::setCoordinates(uint32_t x_cord, uint32_t y_cord){
    x = x_cord;
    y = y_cord;
}

uint32_t location::getx(){
    return x;
}

uint32_t location::gety(){
    return y;
}

void location::setPlayerIsHere(bool value){
    playerIsHere = value;
}

void location::checkPlayerPosition(){
    if(playerIsHere)
        return true;
    else
        return false;
}

void location::itemAtLocation(){
    return elem;
}

//fix passing map which is 2d 
void areaCoordinatesSetting(location *mapPointer){
    for(int i = 0; i < MAP1_X_CORD; i++)
    {
        for(int j = 0; j < MAP1_Y_CORD; j++)
        {
            mapPointer->setCoordinates(i,j);
        }
    }
}

//---- Area 1 setting ------//
location map1[MAP1_X_CORD][MAP1_Y_CORD];
map1[0][4].setShipAccessibleArea();
map1[1][1].setLocation(1,4);
map1[1][6].setLocation(3,3);
map1[3][3].setLocation(5,1);
map1[3][6].setLocation(4,1);
map1[4][5].setLocation(2,1);
map1[5][0].setLocation(2,2);
map1[5][5].setLocation(1,4);
map1[6][3].setLocation(4,1);
map1[6][8].setLocation(2,4);
map1[7][7].setLocation(5,1);
map1[8][1].setLocation(1,3);
map1[8][4].setLocation(3,5);
//------Area 1 setting finished ------//