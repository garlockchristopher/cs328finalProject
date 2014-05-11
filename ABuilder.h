// Matt Garlock
// CS 328 Final Project
// Header file for the ABuilder class

# include "MatrixBase.h"
# include "Symmetric.h"
# include "Diagonal.h"
# include "Banded.h"
# include <math.h>

# ifndef ABUILDER_H
# define ABUILDER_H

template <typename T>
class ABuilder
{
  public:
    Symmetric<T> operator() ( unsigned int n );
};

# include "ABuilder.hpp"
# endif