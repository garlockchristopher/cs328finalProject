/* Vector.h
   Definition for a templated Vector class
   Christopher Garlock
 */
#ifndef VECTOR_H
#define VECTOR_H

#include "Array.h"
#include <stdexcept>

template <class T>
class Vector
{
  private:
    Array<T> m_vector;
    
    
  public:
  
    // Purpose: Constructor
    // Parameters: Size of the vector
    // Returns: nothing
    // Postconditions: a Vector of the specified size is created
    Vector(unsigned int size);
    
    // Purpose: Destructor
    // Parameters: none
    // Returns: nothing
    // Postconditions: Memory is deallocated and the object is destroyed
    ~Vector() {}
    
    // Purpose: accessor function for the size of the vector
    // Parameters: none
    // Returns: an unsigned integer representing the size of the vector
    unsigned int size() const {return m_vector.m_size;}
    
    // Purpose: To swap the values of two indexes in the vector
    // Parameters: the rows to swap
    // Returns: nothing
    // Postconditions: the two specified rows are interchanged.
    void swapRow(unsigned int row1, unsigned int row2);
    
    // Purpose: To perform a row operation on the vector
    // Parameters:  two rows and a multiplier
    // Returns: nothing
    // Preconditions: multiplication, addition, and assignment operators
    //                        defined for type T
    // Postconditions: row1 is multiplied by mult and added to row2
    void rowOp(unsigned int row1, T mult, unsigned int row2);
    
    // Purpose: Allow the user to change the value of an index of the vector
    // Parameters: The index
    // Returns: a reference to the T at the specified index
    T& operator[](unsigned int i);
    
    // Purpose: Provide access to an index without allowing it to be changed
    // Parameters: The index
    // Returns: A read only reference to the index
    const T& operator[](unsigned int i) const;
    
    // Purpose: Set a vector to be equal to another vector
    // Parameters: The calling object and a vector to be copied
    // Returns: a reference to the updated vector
    Vector<T>& operator=(const Vector<T>& rhs){m_vector = rhs.m_vector; return *this;}
	
	// Purpose: calculates the dot product between two vectors
    // Parameters: rhs is the second vector in the dot product
    // Pre: Vectors are of the same length T can be assigned 0
    // Returns: the dot product of the calling object and rhs
    T operator* (const Vector<T>& rhs) const;
	
    // Purpose: negates every element of the Vector
    // Pre:  negation ( unary - ) operator is defined for type T.
    // Returns: the vector with elm = -elm assigned for every element in the vector
    Vector<T> operator- () const;
    
   // Pre: The +=, *, abs() and pow() functions are all defined for type T
   // Returns: the square root of the sum of the squares of the elements in the vector
   T Vector<T>::norm()const;
    
    // Purpose: Insertion operator
    // Parameters: An ostream and a vector
    // Returns: the ostream with the vector inserted into it
    friend ostream& operator<< (ostream& os, const Vector<T>& myVector)
    {
       for (unsigned int i=0;i<myVector.size();i++)
       {
         os<<myVector[i]<<' ';
       }
       return os;
    }
    
    // Purpose: Extraction operator
    // Pre: the number of elements in the stream = m_size
    // Parameters: An istream and a vector
    // Returns: The input stream with the vector removed
    friend istream& operator>> (istream& is, Vector<T>& myVector)
    {
       for (unsigned int i=0;i<myVector.size();i++)
       {
         is>>myVector[i];
       }
       return is;
    }
};

#include "Vector.hpp"
#endif
