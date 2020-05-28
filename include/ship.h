#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>

#include "projectile.h"

using namespace std;

typedef vector< Projectile > proj_vec;

class Ship{
  
  public:
    Ship( float, float, WINDOW * );
    void print();
    void action( int, proj_vec& );
  
  private:
    int direction = 1;
    int max_y;
    int max_x;
    int y, x;
    
    WINDOW * gamewin;
};

#endif
