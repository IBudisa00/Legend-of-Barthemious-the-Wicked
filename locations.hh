/*elem types:
    0 - empty/no elem
    1 - wood
    2 - iron
    3 - rope
    4 - food
    5 - drink
*/

class area{
    private:
        bool shipAccesableArea;
        int elem;
        int value;
    public:
        area();
        void setLocation(int element, int inputValue);
        void setShipAccesableArea();
        void deleteElem();
        bool checkExistence();
};
