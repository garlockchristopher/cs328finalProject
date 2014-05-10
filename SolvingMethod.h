// Matt Garlock
// CS328 Final Project
// SolvingMethod header file


# include "MatrixBase.h"
# include "Vector.h"

# ifndef SOLVINGMETHOD_H
# define SOLVINGMETHOD_H

template <typename T>
class SolvingMethod
{
  private:
    unsigned int iterations;
    double errorTolerance;
  public:
    SolvingMethod ( double error ): errorTolerance(error), iterations(0) {}
    virtual Vector<T> operator() ( const MatrixBase<T> & A, const MatrixBase<T> & X ) = 0;
    unsigned int getIterations () const { return iterations; }
};

# endif