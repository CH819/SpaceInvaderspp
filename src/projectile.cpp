#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "projectile.h"

using namespace std;

Projectile::Projectile( int y_coor, int x_coor, float dir, WINDOW * win ){
  
  x = x_coor;
  y = y_coor - 2;
  direction = dir;
  gamewin = win;
}


void Projectile::print(){
  
  if ( direction > 0 ){
  mvwprintw( gamewin, y, x, "*" );
  mvwprintw( gamewin, y+1, x, "*" );
  }
  
  else {
    mvwprintw( gamewin, y-1, x, "*" );
    mvwprintw( gamewin, y, x, "*" );
  }
  
}


void Projectile::move(){
  y -= direction;
}
