/*
Filename: MatrixBase.h
Author: Chris Garlock
Purpose: An abstract base class designed to be the parent of several different types of matrices
*/

# include <istream>
# include <ostream>
# include <iostream>
# include "Vector.h"

#ifndef MATRIXBASE_H
#define MATRIXBASE_H

template <class T>
class MatrixBase
{
  protected:
    unsigned int m_size;
    
  public:
    //virtual accessor function for size
    virtual unsigned int size() const{return m_size;}
    
    virtual T& operator()(const unsigned int row, const unsigned int col) = 0;
    
    virtual const T& operator()(const unsigned int row, const unsigned int col)const = 0;
    
    //pure virtual print function - should be used to call the insertion operator
    virtual ostream& print(ostream& os) = 0;
    
     //pure virtual read function - should be used to call the extraction operator
    virtual istream& read(istream& is) = 0;
    
    //pure virtual function that gives x for the equation Ax=b when provided b.
    virtual Vector<T> solve(Vector<T> b) = 0;
    
    //virtual destructor
    virtual ~MatrixBase(){}
    
    virtual bool diagonallyDominant(){return false;}
};

template <class T>
std::ostream& operator<<(std::ostream& os, MatrixBase<T>& base)
{
  return base.print(os);
}

template <class T>
std::istream& operator>>(std::istream& is, MatrixBase<T>& base)
{
  return base.read(is);
}
#endif