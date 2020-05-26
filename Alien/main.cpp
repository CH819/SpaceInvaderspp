
#include "alien.h"

int main(int argc, char *argv[]) {


  int max_y = 0, max_x = 0;

  int next_x = 0;

  Alien A1( 0, 0 );

  initscr();

  noecho();
  curs_set(FALSE);


  // Global var `stdscr` is created by the call to `initscr()`
  getmaxyx(stdscr, max_y, max_x);


  while(1) {
    clear();

    next_x = A1.UpdatePosition( next_x, max_x);
  }

  endwin();
}


