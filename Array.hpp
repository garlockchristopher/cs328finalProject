/*
File: Array.hpp 
Author: Matt Garlock CS 328 section a
Implementation file for the Array class
*/
#include <stdexcept>
#include <iostream>
using namespace std;

template <class T>
Array<T>:: Array( const unsigned int size )
{
  m_size = 0;
  m_max_size = 0;
  for ( unsigned int i = 0; i < size; i ++ )
  {
    push_back( T() );
  }
}

template <class T>
void Array<T>:: clear()
{
  delete [] m_data; //dealocate memory
  m_data = NULL;
  m_size = 0;
  m_max_size = 0;
  
  return;
}

template <class T>
void Array<T>:: pop_back()
{
  if(m_size == 0)
  {
    throw std::length_error("Array is empty!"); 
  }
  if(m_size ==1)
  {
    delete [] m_data;
    m_size = 0;
    m_max_size = 0;
    m_data = NULL;
  }
  else
  {
    m_size--;
    if(m_size / static_cast<float>(m_max_size) <= .25) //lots of unused space
    {
      T *temp = new T[m_max_size/2]; //make a smaller Array then copy contents
      for (int i = 0; i < m_size; i++)  
        temp[i] = m_data[i];
      delete [] m_data; //delete old Array
      m_data = temp; //make m_data point to new Array
      temp = NULL; //unpoint temp (just to be safe)
      m_max_size /=2;
    }
  }
  
}

template <class T>
void Array<T>:: push_back(const T& x)
{
  if(m_max_size == 0) //no Array yet
  {
    m_data = new T[2];
    m_max_size = 2;
  }
  
  if(m_size +1 == m_max_size)
  {
    T *temp = new T[m_max_size*2];
    for(unsigned int i = 0; i<m_size; i++)
    {
      temp[i] = m_data[i]; //copy conents of old Array into the new one
    }
    delete [] m_data;
    m_data = temp; //point m_data to the new Array
    m_max_size *=2;
    temp = NULL;
  }
  
  m_data[m_size] = x;
  m_size++;
  return;
}

template <class T>
void Array<T>:: remove(const T& x)
{
  bool found = false;
  for(int i = 0; i<m_size && !found; i++)
  {
    if( x == m_data[i])
    {
      found = true;
      for(int j = i; i<m_size-1; i++)
        m_data[i] = m_data[i+1];
      m_size--;
    }
  }  
  if(found && m_size <= m_max_size/4.0)
  {
    m_max_size /= 2;
    T *temp = new T[m_max_size];
    for(int i = 0; i<m_size; i++)
    {
      temp[i] = m_data[i]; //copy conents of old Array into the new one
    }
    delete [] m_data; //delete the old Array
    m_data = temp; //point m_data to the new Array
    temp = NULL;
  }  
}


template <class T>
T& Array<T>:: operator[](unsigned int i)
{
  if( i>= m_size )
    throw std:: out_of_range("i<0 or i>=m_size");
  return m_data[i];
}

template <class T>
const T& Array<T>:: operator[](unsigned int i) const
{
  if( i >= m_size)
    throw std:: out_of_range("i<0 or i>=m_size");
  return m_data[i];
}

template <class T>
Array<T>& Array<T>:: operator=(const Array<T>& rhs)
{
  if(m_data != rhs.m_data) // objects are pointing to two seperate Arrays
  {
    m_size = rhs.m_size;
    m_max_size = rhs.m_max_size;
    T *temp = new T[rhs.m_size];
    for( unsigned int i = 0; i<rhs.m_size; i++)
      temp[i] = rhs[i];
    if (m_data != NULL)
      delete[] m_data;
    m_data = temp;
    temp = NULL;
  }
  return *this;
}

template <typename T>
T Array<T>::operator* (const Array<T>& rhs) const
{
  if (m_size != rhs.m_size)
    throw std::length_error("Arrays are not the same length");
  T dotProduct = 0;
  for ( unsigned int i = 0; i < m_size; i++ )
    dotProduct += m_data[i] * rhs[i];
  return dotProduct;
}

template <typename T>
Array<T> Array<T>::operator* (const T& scalar) const
{
  Array<T> scaled = *this;
  scaled *= scalar;
  return scaled;
}

template <typename T>
Array<T>&Array<T>:: operator*= (const T& scalar)
{
  for ( unsigned int i = 0; i < m_size; i++ )
    m_data[i] *= scalar;
  return *this;
}

template <typename T>
Array<T> Array<T>::operator+ (const Array<T>& rhs) const
{
  Array<T> sum(rhs);
  return sum += *this;
}

template <typename T>
Array<T>& Array<T>::operator+= (const Array<T>& rhs)
{
  if (m_size != rhs.m_size)
    throw std::length_error("Arrays are not the same length");
  for ( unsigned int i = 0 ; i < m_size; i++ )
    m_data[i] += rhs[i];
  return *this;
}

template <typename T>
Array<T> Array<T>::operator- (const Array<T>& rhs) const
{
  Array<T> difference(*this);
  return difference -= rhs;
}

template <typename T>
void Array<T>:: swapElements ( const unsigned int index1, const unsigned int index2 )
{
  if ( index1 > m_size || index2 > m_size )
    throw std:: out_of_range("atleast one index is out of range");
  T temp = m_data[index1];
  m_data[index1] = m_data[index2];
  m_data[index2] = temp;
  return;
}

template <typename T>
Array<T>& Array<T>::operator -=(const Array<T>& rhs)
{
  if (m_size != rhs.m_size)
    throw std::length_error("Arrays are not the same length");
  for ( unsigned int i = 0 ; i < m_size; i++ )
    m_data[i] -= rhs[i];
  return *this;
}
