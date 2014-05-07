#ifndef BBUILDER_H
#define BBUILDER_H

#include <cmath>
#include <iostream>//DONT FORGET TO TAKE THIS OUT
#include "Vector.h"
//#include "topFunc.h"
//#include "botFunc.h"
//#include "leftFunc.h"
//#include "rightFunc.h"

template <class T>
class bBuilder
{
  public:
    Vector<T> operator()(unsigned int size/*, topFunc<T> tFunc, botFunc<T> bFunc, leftFunc<T> lFunc, rightFunc<T> rFunc*/);
};

#include "BBuilder.hpp"
#endif