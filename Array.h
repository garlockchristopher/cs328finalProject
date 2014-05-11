/*
File: Array.h
Author: Matt Garlock CS 153 section a
header file for the Array class
*/

#ifndef Array_H
#define Array_H

# include <cstdlib>
# include <ostream>
# include <fstream>

template <class T>
class Array
{
  private:  
    unsigned int m_size;      // current # of elements (i.e., data items)
    unsigned int m_max_size;  // current maximum size of Array
    T* m_data;                // data
    
  public:
    // Purpose: default constructor
    // Postconditions: current size and maximum size set to 0, 
    // and data set to NULL
    Array(): m_size(0), m_max_size(0), m_data(NULL) {}
    
    // Purpose: sized constructor
    // Parameters: size is the size the Array will be
    // Postconditions: Array initialized with the requested size
    Array( const unsigned int size );

    // Purpose: copy constructor
    // Parameters: cpy is Array that is to be copied
    // Postconditions: current size, maximum size, and data set to those of cpy
    Array(const Array<T>& cpy) {m_data = NULL;  *this = cpy; }

    // Purpose: destructor
    // Postconditions: current size and maximum size set to 0, 
    // and data set to NULL (via clear())
    ~Array() { clear(); }

    // Purpose: effectively "empties" the Array
    // Postconditions: current size and maximum size set to 0, 
    // data set to NULL, and all dynamically allocated memory for data is
    // deallocated
    void clear();
    
    // Purpose: puts the value x at the "leftmost available" index in Array
    // Parameters: x is value to be added to Array
    // Postconditions: if current size + 1 == maximum size BEFORE the insertion
    // of x, memory for data is doubled; x now at the formerly "leftmost 
    // available" position in the Array, and current size incremented by 1
    void push_back(const T& x);

    // Purpose: Removes one instance of the value x from the Array if it exists
    // Parameters: x is the value to be removed from the Array
    // Postconditions: if x is in the Array, m_size is decremented and the
    //     first instance of x is removed from the Array. If x is not in the
    //     Array, do nothing.
    //     If m_size <= m_max_size/4, halve the amount of memory available
    void remove(const T& x);

    // Purpose: removes the "last" element in the Array
    // Postconditions: current size decremented by 1, and memory for data is
    // halved if current size / maximum size <= 0.25 AFTER the removal of x
    // Exceptions: if the Array is empty, then throw std::length_error
    void pop_back();

    // Purpose: accessor function for the current # data values in the Array
    // Returns: current size of the Array 
    unsigned int size() const {return m_size;}

    // Purpose: accessor function for the maximum size of the Array
    // Returns: current maximum size of the Array 
    unsigned int max_size() const { return m_max_size; }

    // Purpose: swaps two elements in the Array
    // Pre: both incidences are on the Array
    // Post: elements at index1 and index2 have been swapped
    void swapElements ( const unsigned int index1, const unsigned int index2 );
    
    // Purpose: return a read-and-write reference to the element at 
    // the specified position
    // Parameters: i is 0-based index into the Array
    // Returns: the element at position i in the Array
    // Exceptions: if i < 0 or i >= current size, throw 
    // std::out_of_range("i<0 or i>=m_size")
    T& operator[](unsigned int i);

    // Purpose: return a read-only reference to the element at 
    // the specified position
    // Parameters: i is 0-based index into the Array
    // Returns: the element at position i in the Array
    // Exceptions: if i < 0 or i >= current size, throw 
    // std::out_of_range("i<0 or i>=m_size")
    const T& operator[](unsigned int i) const;

    // Purpose: performs a deep copy of the data from rhs into this Array
    // Parameters: rhs is Array to be copied
    // Returns: *this
    // Postconditions: current size, maximum size, and data set to those of
    // rhs
    Array<T>& operator=(const Array<T>& rhs);
    
    // Purpose: calculates the dot product between two Arrays
    // Parameters: rhs is the second Array in the dot product
    // Pre: Arrays are of the same length T can be assigned 0
    // Returns: the dot product of the calling object and rhs
    T operator* (const Array<T>& rhs) const;
    
    // Purpose: performs scalar multiplication on the calling object
    // Parameters: Scalar is the object each entry in the Array will be multiplied by
    // Pre: T * T is defined
    // Returns: a Array representing the scalar multiplication of the calling object
    Array<T> operator* (const T& scalar) const;
    Array<T>& operator*= (const T& scalar);
    
    // Purpose: adds the two Arrays
    // Parameters: rhs is the right had side of the operation
    // Pre: the + and = operators are defined for type T with T as the parameter
    //         and both Arrays are the same length
    // Returns: a Array equal to the calling object + rhs
    Array<T> operator+ (const Array<T>& rhs) const;
    Array<T>& operator+= (const Array<T>& rhs);
    
    // Purpose: subtracts the two Arrays
    // Parameters: rhs is the right had side of the operation
    // Pre: the - and = operators are defined for type T with T as the parameter
    //         and both Arrays are the same length
    // Returns: a Array equal to the calling object - rhs
    Array<T> operator- (const Array<T>& rhs) const;
    Array<T>& operator-=(const Array<T>& rhs);
    


    // Purpose: outputs the data in m_data seperated by spaces
    // Pre:  << operator is defined for type T
    // Parameters: lhs is the output stream, rhs is the Array to be output
    // Returns: the calling ostream
    friend std::ostream& operator << ( std::ostream& os, const Array<T>& rhs )
    {
      for ( unsigned int i = 0; i < rhs.size(); i++ )
      {
        os << rhs[ i ] <<  ' ';
      }
      return os;
    }
    friend std::ifstream& operator >> ( std::ifstream& is, Array<T>& rhs )
    {
      for ( unsigned int i = 0; i < rhs.size(); i++ )
      {
        T temp;
        is >> temp;
        rhs[ i ] = temp;
      }
      return is;
    }
};

#include "Array.hpp"
#endif
