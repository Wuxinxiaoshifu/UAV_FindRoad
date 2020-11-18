#include <map>
#include <iostream>
#include "grid.h"
class Localmap
{
private:
    /* data */
    // id -> Grid
    std::map<int, Grid> data;
    std::map<int, double> road;

public:
    Localmap(/* args */);
    ~Localmap();
    Update_Map();
    Find_Road();
};