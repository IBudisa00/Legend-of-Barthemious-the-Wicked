#include <iostream>
#include <cstdint>
#include "locations.hh"

location::location(){
    shipAccessibleArea = false;
    playerIsHere = false;
    elem = 0;
    value = 0;
}

void location::setItemAtLocation(uint32_t element, uint32_t inputValue){
    elem = element;
    value = inputValue;
}

void location::setShipAccessibleArea(){
    shipAccessibleArea = true;
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

bool location::checkPlayerPosition(){
    if(playerIsHere)
        return true;
    else
        return false;
}

uint32_t location::itemAtLocation(){
    return elem;
}

uint32_t location::valueOfItemAtLocation(){
    return value;
}

//fix passing map which is 2d 
void areaCoordinatesSetting(location map[MAP1_X_CORD][MAP1_Y_CORD]){
    for(int i = 0; i < MAP1_X_CORD; i++)
    {
        for(int j = 0; j < MAP1_Y_CORD; j++)
        {
            map[i][j].setCoordinates(i,j);
        }
    }
}

void setStartingMap(location startMap[MAP1_X_CORD][MAP1_Y_CORD]){
    //location map1[MAP1_X_CORD][MAP1_Y_CORD];
    startMap[0][4].setShipAccessibleArea();
    startMap[1][1].setItemAtLocation(1,4);
    startMap[1][6].setItemAtLocation(3,3);
    startMap[3][3].setItemAtLocation(5,1);
    startMap[3][6].setItemAtLocation(4,1);
    startMap[4][5].setItemAtLocation(2,1);
    startMap[5][0].setItemAtLocation(2,2);
    startMap[5][5].setItemAtLocation(1,4);
    startMap[6][3].setItemAtLocation(4,1);
    startMap[6][8].setItemAtLocation(2,4);
    startMap[7][7].setItemAtLocation(5,1);
    startMap[8][1].setItemAtLocation(1,3);
    startMap[8][4].setItemAtLocation(3,5);
}