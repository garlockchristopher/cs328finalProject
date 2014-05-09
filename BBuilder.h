#ifndef BBUILDER_H
#define BBUILDER_H

#include <cmath>
#include "Vector.h"
#include "TopFunc.h"
#include "BotFunc.h"
#include "LeftFunc.h"
#include "RightFunc.h"

template <class T>
class BBuilder
{
  public:
    Vector<T> operator()(unsigned int size, TopFunc<T> tFunc, BotFunc<T> bFunc, LeftFunc<T> lFunc, RightFunc<T> rFunc);
};

#include "BBuilder.hpp"
#endif