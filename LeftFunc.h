// Matt Garlock
// CS 328 Final Project
// LeftFunc

# ifndef LEFTFUNC_H
# define LEFTFUNC_H

template < typename T >
class LeftFunc
{
  public:
    // returns the z value for the point ( 0 , y )
    T operator () ( const T & y ) { return 0 * y; }
};

# endif