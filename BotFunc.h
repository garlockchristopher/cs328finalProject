// Matt Garlock
// CS 328 Final Project
// BotFunc

template < typename T >
class BotFunc
{
  public:
    T operator () ( const T & x ) { return 1 - 4 * ( x - .5 ) * ( x - .5 ); }
}
