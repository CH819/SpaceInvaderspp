#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "projectile.h"

using namespace std;

Projectile::Projectile( int y_coor, int x_coor ){
  
  x = x_coor;
  y = y_coor - 4;
}


void Projectile::print(){
  
  mvprintw(y, x, "*");
  mvprintw(y+1, x, "*");
  mvprintw(y+2, x, "*");
  
  //refresh();
}


void Projectile::move(){
  y -= direction;
}
