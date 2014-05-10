/* Vector.hpp
   Implementation for a templated Vector class
   Christopher Garlock
*/

// Purpose: Constructor
// Parameters: Size of the vector
// Returns: nothing
// Postconditions: a Vector of the specified size is created
template <class T>
Vector<T>::Vector(unsigned int size)
{
  m_vector.m_data = new T [size];
  m_vector.m_size = size;
  m_vector.m_max_size = size;
}

// Purpose: To swap the values of two indexes in the vector
// Parameters: the rows to swap
// Returns: nothing
// Postconditions: the two specified rows are interchanged.
template <class T>
void Vector<T>::swapRow(unsigned int row1, unsigned int row2)
{
  if(row1>size() || row2>size())
    throw std::out_of_range("One or more of the row numbers specified is too large.");
  T temp;
  temp = m_vector[row1];
  m_vector[row1] = m_vector[row2];
  m_vector[row2] = temp;
  return;
}

// Purpose: To perform a row operation on the vector
// Parameters:  two rows and a multiplier
// Returns: nothing
// Preconditions: multiplication, addition, and assignment operators
//                        defined for type T
// Postconditions: row1 is multiplied by mult and added to row2
template <class T>
void Vector<T>::rowOp (unsigned int row1, T mult, unsigned int row2)
{
  if(size()<2)
    throw std::length_error("Must have at least two rows for a row operation.");
  if(row1 >= size() || row2 >= size())
    throw std::out_of_range("One or more of the specified rows is out of range.");
  m_vector[row2] = m_vector[row2] + (m_vector[row1] * mult);
  return;
}
    
// Purpose: Allow the user to change the value of an index of the vector
// Parameters: The index
// Returns: a reference to the T at the specified index
template <class T>
T& Vector<T>::operator[](unsigned int i)
{
  if(size()==0 || i>=size())
    throw std::out_of_range("The vector is empty or you went past the end");
  return m_vector[i];
}
    
// Purpose: Provide access to an index without allowing it to be changed
// Parameters: The index
// Returns: A read only reference to the index
template <class T>
const T& Vector<T>::operator[](unsigned int i) const
{
  if(size()==0 || i>=size())
    throw std::out_of_range("The vector is empty or you went past the end");
  return m_vector[i];
}

template <typename T>
T Vector<T>::operator* (const Vector<T>& rhs) const
{
  if (m_size != rhs.m_size)
    throw std::length_error("Vectors are not the same length");
  T dotProduct = 0;
  for ( unsigned int i = 0; i < m_size; i++ )
    dotProduct += m_vector[i] * rhs[i];
  return dotProduct;
}

template <typename T>
Vector<T> operator- () const
{
	Vector<T> negated ( m_vector.size() );
	for ( unsigned int i = 0; i < m_vector.size(); i++ )
	{
		negated[i] = -m_vector[i];
	}
	return negated;
}