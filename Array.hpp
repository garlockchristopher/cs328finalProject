/* Array.hpp
   Implementation for a templated Array class
   Christopher Garlock
 */

 // Purpose: constructor
 // Postconditions: creates an array of specified maximum size with no data
template <class T>
Array<T>::Array(unsigned int size)
{
  m_data = new T [size];
  m_size = size;
  m_max_size = size;
}

// Purpose: effectively "empties" the Array
// Postconditions: current size and maximum size set to 0,
// data set to NULL, and all dynamically allocated memory for data is
// deallocated
template <class T>
void Array<T>::clear()
{
  m_size=0;
  m_max_size=0;
  delete [] m_data;
  m_data=NULL;
  return;
}

// Purpose: puts the value x at the "leftmost available" index in Array
// Parameters: x is value to be added to Array
// Postconditions: if current size + 1 == maximum size BEFORE the insertion
// of x, memory for data is doubled; x now at the formerly "leftmost
// available" position in the Array, and current size incremented by 1
template <class T>
void Array<T>::push_back(const T& x)
{
  if(m_size+1>=m_max_size) //array is almost full, we need to double size.
  {
    T* temp;
    if(m_max_size==0)//need this if the array is empty because 0*2=0
      m_max_size=1;
    temp = new T [m_max_size*2];
    for(unsigned int i=0;i<m_size;i++)
    {
      temp[i]=m_data[i];
    }
    m_max_size*=2;  //adjust max size
    delete [] m_data;  //deallocate m_data's memory
    m_data=temp;  //point m_data to the location of temp
  }
  m_size++;
  m_data[m_size-1]=x;
  return;
}


// Purpose: Removes one instance of the value x from the Array if it exists
// Parameters: x is the value to be removed from the Array
// Postconditions: if x is in the Array, m_size is decremented and the
//     first instance of x is removed from the Array. If x is not in the
//     Array, do nothing.
//     If m_size <= m_max_size/4, halve the amount of memory available
template <class T>
void Array<T>::remove(const T& x)
{
  int location=-1;  //locations of x, if it exists
  int i=0;
  while (location == -1 and i < m_size) //find x
  {
    if(x==m_data[i])
    {
      location=i;
    }
    i++;
  }
  if(location!=-1)  //x has been found
  {
    for(int j=location;j<m_size-1;j++) //start at the location, walk up to end
    {
      m_data[j]=m_data[j+1];
    }
    m_size--;  //decrement size
    if(m_size/static_cast<float>(m_max_size)<=0.25)//array size needs to halved
    {
      T* temp;
      temp = new T [m_max_size/2];
      for(int i=0;i<m_size;i++)
      {
        temp[i]=m_data[i];
      }
      m_max_size/=2;  //adjust max size
      delete [] m_data;  //deallocate m_data's memory
      m_data=temp;  //point m_data to the location of temp
    }
  }
  return;
}

// Purpose: removes the "last" element in the Array
// Postconditions: current size decremented by 1, and memory for data is
// halved if current size / maximum size <= 0.25 AFTER the removal of x
// Exceptions: if the Array is empty, then throw std::length_error
template <class T>
void Array<T>::pop_back()
{
  if (m_data==NULL or m_size==0)
    throw std::length_error("Array is empty.");

  m_size--;

  if(m_size/static_cast<float>(m_max_size)<=0.25)//array size needs to halved
  {
    T* temp;
    temp = new T [m_max_size/2];
    for(int i=0;i<m_size;i++)
    {
      temp[i]=m_data[i];
    }
    m_max_size/=2;  //adjust max size
    if(m_max_size==1)  //need to adjust this because 2/2=1 but size should=0
      m_max_size=0;
    delete [] m_data;  //deallocate m_data's memory
    m_data=temp;  //point m_data to the location of temp
  }

  return;
}

// Purpose: return a read-and-write reference to the element at
// the specified position
// Parameters: i is 0-based index into the Array
// Returns: the element at position i in the Array
// Exceptions: if i < 0 or i >= current size, throw
// std::out_of_range("i<0 or i>=m_size")
template <class T>
T& Array<T>::operator[](unsigned int i)
{
  if(i>=m_max_size)
  {
    throw std::out_of_range("i>=m_max_size");
  }
  if(i>=m_size)
    m_size++;
  return m_data[i];
}

// Purpose: return a read-only reference to the element at
// the specified position
// Parameters: i is 0-based index into the Array
// Returns: the element at position i in the Array
// Exceptions: if i < 0 or i >= current size, throw
// std::out_of_range("i<0 or i>=m_size")
template <class T>
const T& Array<T>::operator[](unsigned int i) const
{
  if(i>=m_size)
  {
    throw std::out_of_range("i>=m_size");
  }
  return m_data[i];
}

// Purpose: performs a deep copy of the data from rhs into this Array
// Parameters: rhs is Array to be copied
// Returns: *this
// Postconditions: current size, maximum size, and data set to those of
// rhs
template <class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
  if (m_data==rhs.m_data)  //no need to create a new array and stuff if
  {                        //assigning to the same object.
    return *this;
  }
  m_size=rhs.m_size;
  m_max_size=rhs.m_max_size;
  //delete [] m_data;
  m_data=new T[m_max_size];
  for (unsigned int i=0;i<m_size;i++)
  {
    m_data[i]=rhs.m_data[i];
  }
  return *this;
}







