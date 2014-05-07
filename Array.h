/* Array.h
   Definition for a templated Array class
   Christopher Garlock
 */

#ifndef Array_H
#define Array_H

#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

template <class T>
class Array
{
  private:
    unsigned int m_size;      // current # of elements (i.e., data items)
    unsigned int m_max_size;  // current maximum size of Array
    T* m_data;                // data
    
    template <class U> friend class Vector; //so we can resize an Array from within the vector class.

  public:
    // Purpose: default constructor
    // Postconditions: current size and maximum size set to 0,
    // and data set to NULL
    Array(): m_size(0), m_max_size(0), m_data(NULL) {}
    
    // Purpose: constructor
    // Postconditions: creates an array of specified maximum size with no data
    Array(unsigned int size);

    // Purpose: copy constructor
    // Parameters: cpy is Array that is to be copied
    // Postconditions: current size, maximum size, and data set to those of cpy
    Array(const Array<T>& cpy) { *this = cpy; }

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
    
    // Purpose: To output an array to an output stream
    // Parameters: lefthand operand should be an output stream and rhs should be an Array
    // Returns: the same stream it was passed  
    // Postconditions: Elements of the array are added to output stream
    friend ostream& operator<< (ostream& os, const Array<T>& myArray)
    {
       for (unsigned int i=0;i<myArray.size();i++)
          os<<myArray[i]<<endl;
       return os;
    }
    
    // Purpose: To read elements into an array
    // Parameters: lefthand operand should be an input stream and rhs should be an Array
    // Returns: the same stream it was passed  
    // Postconditions: reads in a T and places it into the array
     friend istream& operator>> (istream& is, Array<T>& myArray)
    {
       T input;
       myArray.push_back(input);
       return is;
    }
};

#include "Array.hpp"
#endif
