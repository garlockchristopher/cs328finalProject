/* Banded.h
   Definition for a templated Banded matrix class
   Christopher Garlock
 */
 
#ifndef BANDED_H
#define BANDED_H

#include "Vector.h"
#include <stdexcept>
#include <iostream>
#include "Matrix.h"

template <class T>
class Banded: public virtual MatrixBase<T>
{
  private:
    Array<T> m_tBand;
    Array<T> m_mBand;
    Array<T> m_bBand;
    const T M_ZERO;
    T m_zero;
  public:
   //constructor
    //pre: size > 2
    Banded(unsigned int size);
    
    //copy constructor
    Banded(const Banded<T>& copy);
    
    //destructor
    virtual ~Banded(){}
    
    //assignment operator
    //pre: size of lhs and rhs are equal
    Banded<T>& operator= (const Banded<T>& rhs);
    
    //parenthesis operator, returns a reference to position (row, col) of the matrix
    //note: if you try to change an element where row > col +1 or col > row +1 
    //         it will actually change m_zero this will have no effect on the matrix 
    //         and will not effect future return values from this function
    T& operator()(const unsigned int row, const unsigned int col);
    
    //const version of above operator
    const T& operator()(const unsigned int row, const unsigned int col)const;
    
    //subtraction operator
    //pre: both Bandeds are of the same size
    //returns the Banded resulting from the subtraction
    Banded<T> operator- (const Banded<T>& rhs) const;
    
    //addition operator
    //pre: both Bandeds are of the same size
    //returns the Banded resulting from the addition
    Banded<T> operator+ (const Banded<T>& rhs) const;
    
    // Purpose: Multiplication operator (with other matrices)
    // Parameters: Calling object, Banded to multiply with the calling object
    // Returns: The updated Banded
    // Preconditions: multiplication, addition and assignment operators defined for type T
    Banded<T> operator* (const Banded<T>& rhs);
    
    // Purpose: Multiplication operator (with a scalar)
    // Parameters: Calling object, scalar to multiply with the calling object
    // Returns: The updated Banded
    // Preconditions: multiplication and assignment operators defined for type T
    Banded<T> operator* (const T& rhs);
    
    // Purpose: Multiplication operator (with a vector)
    // Parameters: Calling object, Vector to multiply with the calling object
    // Returns: The updated Banded
    // Preconditions: multiplication and assignment operators defined for type T
    Vector<T> operator* (const Vector<T>& rhs);
    
    //print function, used by base class MatrixBase to call this classes insertion operator
    virtual ostream& print(ostream& os){return os<<*this;}
    
    //read function, used by base class MatrixBase to call this classes extraction operator
    virtual istream& read(istream& is){return is>>*this;}
    
    //solves the equation Ax=b for x where A is the calling object
    //pre: size of b and calling object are the equal
    virtual Vector<T> solve(Vector<T> b);
    
    // Purpose: To output a banded to an output stream
    // Parameters: lefthand operand should be an output stream and rhs should be a banded
    // Returns: the same stream it was passed  
    // Postconditions: Elements of the array are added to output stream
    friend ostream& operator<< (ostream& os, const Banded<T>& myBand)
    {
      for (unsigned int i=0;i<myBand.MatrixBase<T>::size();i++)
      {
        for (unsigned int j=0;j<myBand.MatrixBase<T>::size();j++)
        {
          os<<myBand(i,j)<<' ';
        }
        os<<endl;
      }
      return os;
    }
    
    // extraction operator: reads in a banded from an input stream
    // pre: banded in input stream is same size as calling object and is a valid banded matrix
    // returns a reference to the input stream
    friend istream& operator>> (istream& is, Banded<T>& myBand)
    {
      T input;
      for (unsigned int i=0;i<myBand.MatrixBase<T>::size();i++)
      {
        for (unsigned int j=0;j<myBand.MatrixBase<T>::size();j++)
        {
          if(i > j + 1 || j > i + 1)
          {
            is>>input;
            if(input!=0)
              throw ios_base::failure ("This input violates the properties of a banded matrix.");
          }
          else
            is>>myBand(i,j);
        }
      }
      return is;
    }
};
#include "Banded.hpp"

#endif
