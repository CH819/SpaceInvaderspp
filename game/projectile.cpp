#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "projectile.h"

using namespace std;

Projectile::Projectile( int y_coor, int x_coor, WINDOW * win ){
  
  x = x_coor;
  y = y_coor - 2;
  gamewin = win;
}


void Projectile::print(){
  
  mvwprintw( gamewin, y, x, "*" );
  mvwprintw( gamewin, y+1, x, "*" );
  
  //refresh();
}


void Projectile::move(){
  y -= direction;
}
