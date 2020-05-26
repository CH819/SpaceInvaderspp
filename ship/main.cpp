#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "ship.h"

using namespace std;

#define DELAY 300

int main(){
  
  int max_y = 0, max_x = 0;
  int ch;
  
  
  initscr();
  noecho();
  curs_set(FALSE);
  
  getmaxyx(stdscr, max_y, max_x);
  
  Ship ship( max_y, max_x );
  
  initscr();
  raw();
  keypad( stdscr, true );
  noecho();
  
  while(1) {
    
    //getmaxyx(stdscr, max_y, max_x);
    clear();
    
    ship.print();
    
    ch = getch();
    ship.move( ch );
    
    if ( ch == KEY_F(1) ) break;
    
  }
  
  endwin();
  
  return 0;
}

