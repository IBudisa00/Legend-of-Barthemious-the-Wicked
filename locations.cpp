#include <locations.hh>

location::location(){
    shipAccesableArea = false;
    elem = 0;
    value = 0;
}

void location::setLocation(int element, int inputValue){
    elem = element;
    value = inputValue;
}

void location::setShipAccesableArea(){
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
        return false;
}

//---- Area 1 setting ------//
area map1[9][9];
map1[0][3].setShipAccesableArea();
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