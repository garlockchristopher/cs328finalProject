/* Vector.hpp
   Implementation for a templated Vector class
   Christopher Garlock
*/

// Purpose: To swap the values of two indexes in the vector
// Parameters: the rows to swap
// Returns: nothing
// Postconditions: the two specified rows are interchanged.
template <class T>
void Vector<T>::swapRow(const unsigned int & row1, const unsigned int & row2)
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
  if (m_vector.size() != rhs.size())
    throw std::length_error("Vectors are not the same length");
  T dotProduct = 0;
  for ( unsigned int i = 0; i < size(); i++ )
    dotProduct += m_vector[i] * rhs[i];
  return dotProduct;
}

template <typename T>
Vector<T> Vector<T>:: operator- () const
{
	Vector<T> negated ( m_vector.size() );
	for ( unsigned int i = 0; i < m_vector.size(); i++ )
	{
		negated[i] = -m_vector[i];
	}
	return negated;
}

template <class T>
T Vector<T>::norm()const
{
  T sum = 0;
  // get the sum of the squared absolute values of all elements
  for(unsigned int i = 0; i<m_vector.size();i++)
    sum += abs(m_vector[i]) * abs(m_vector[i]);
  // return the square root of the sum
  return pow(sum, 0.5);
}

template <class T>
Vector<T> Vector<T>:: operator- ( const Vector<T> & rhs ) const
{
  if (m_vector.size() != rhs.size())
    throw std::length_error("Vectors are not the same length");
  Vector<T> difference ( rhs.size() );
  for ( unsigned int i = 0; i < size(); i++ )
  {
    difference[i] = m_vector[i] - rhs[i];
  }
  return difference;
}