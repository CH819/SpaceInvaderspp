#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "ship.h"
#include "alien.h"

using namespace std;


int main(){
  
  float max_y = 0, max_x = 0;
  int ch;
  
  initscr();
  noecho();
  curs_set(FALSE);
  //raw();
  cbreak();
  keypad( stdscr, true );
  nodelay(stdscr, 1);  
  
  getmaxyx(stdscr, max_y, max_x);
  
  Aliens A1( 0., 0., 3, 4 );
  Ship ship( max_y, max_x );
  
  while(1) {
    
    //getmaxyx(stdscr, max_y, max_x);
    clear();
    
    A1.UpdatePosition( max_x );
    ship.print();
    
    ch = getch();
    ship.move( ch );
    
    refresh();
    
    if ( ch == KEY_F(1) ) break;
    
  }
  
  endwin();
  
  return 0;
}

