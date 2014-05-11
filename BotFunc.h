// Matt Garlock
// CS 328 Final Project
// BotFunc

# ifndef BOTFUNC_H
# define BOTFUNC_H

template < typename T >
class BotFunc
{
  public:
    // returns the z value for the point ( x , 0 )
    T operator () ( const T & x ) { return 1 - 4 * ( x - .5 ) * ( x - .5 ); }
};

# endif