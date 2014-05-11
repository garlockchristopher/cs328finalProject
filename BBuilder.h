// Chris Garlock
// CS 328 Final Project
// Header file for the BBuilder class
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
    //purpose: given a size n, this function will generate the b vector for the equation Ax=b to be used when solving
    //         Laplace's equation
    Vector<T> operator()(unsigned int n, TopFunc<T> tFunc, BotFunc<T> bFunc, LeftFunc<T> lFunc, RightFunc<T> rFunc);
};

#include "BBuilder.hpp"
#endif