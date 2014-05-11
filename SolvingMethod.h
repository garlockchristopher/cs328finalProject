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
  protected:
    double errorTolerance;
    string name;
    unsigned int iterations;
    
  public:
    SolvingMethod ( double error, string name ): errorTolerance(error), name(name), iterations(0) {}
    virtual Vector<T> operator() ( const MatrixBase<T> & A, const Vector<T> & X ) = 0;
    string getName() const { return name; }
    unsigned int getIterations () const { return iterations; }
};

# endif