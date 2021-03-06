// Matt Garlock
// CS 328 Final Project
// RightFunc

# ifndef RIGHTFUNC_H
# define RIGHTFUNC_H


template < typename T >
class RightFunc
{
  public:
    // returns the z value for the point ( 1 , y )
    T operator () ( const T & y ) { return 0 * y; }
};

# endif