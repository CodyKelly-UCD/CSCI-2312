#ifndef submarine_hpp
#define submarine_hpp

#include "watervehicle.hpp"

class Submarine : public WaterVehicle
{
private:
    int diveDepth;
    
public:
    inline void setDiveDepth(float depth) { diveDepth = depth; }
    inline int getDiveDepth() { return diveDepth; }
    inline bool surfaced() { return diveDepth == 0; }
};

#endif /* submarine_hpp */
