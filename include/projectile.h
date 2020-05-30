#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

class Projectile{
  
  friend class Game;
  
  public:
    Projectile( int, int, float, WINDOW * );
    void print();
    void move();
  
  private:
    float direction;
    int max_y;
    int y, x;
    WINDOW * gamewin;
};

#endif
