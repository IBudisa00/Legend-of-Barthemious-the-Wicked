#define MAP1_X_CORD 9
#define MAP1_Y_CORD 9

/*elem types:
    0 - empty/no elem
    1 - wood
    2 - iron
    3 - rope
    4 - food
    5 - drink
*/

class location{
    private:
        bool shipAccessibleArea;
        bool playerIsHere;
        uint32_t x;
        uint32_t y;
        uint32_t elem;
        uint32_t value;
    public:
        location();
        void setLocation(uint32_t element, uint32_t inputValue);
        void setShipAccessibleArea();
        void deleteElem();
        bool checkExistence();
        void setCoordinates(uint32_t x_cord, uint32_t y_cord);
        uint32_t getx();
        uint32_t gety();
        void setPlayerIsHere(bool value);
        bool checkPlayerPosition();
        uint32_t itemAtLocation();
};

void areaCoordinatesSetting();
