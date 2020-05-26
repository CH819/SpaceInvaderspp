
#include "alien.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

  vector< class Alien > VA;

  float max_x = 0, max_y = 0;

  float N = 2; //Number of aliens

  Alien A1( 0, 0 );
  Alien A2( 0, LENGHT );

  VA.push_back( A1 );
  VA.push_back( A2 );

  initscr();

  noecho();
  curs_set(FALSE);


  // Global var `stdscr` is created by the call to `initscr()`
  getmaxyx(stdscr, max_y, max_x);


  while(1) {
    clear();

    A1.UpdatePosition( max_x );
    //getch();
  }

  endwin();
}









