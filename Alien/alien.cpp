#include "alien.h"

Alien::Alien( int y, int x ){

  XL = x;
  XR = x + LENGHT;

  Y = y;

  direction = 1;
}

int Alien::UpdatePosition( int next_x, int max_x ){


  PrintAlien( Y, XL );

  usleep( DELAY );

  if ( direction > 0 ){

    next_x = XR + direction;

    if( next_x  >= max_x ){

      direction += 0.3;
      direction *=-1;
      Y++;
    }

    else{

      XR += direction;
      XL += direction;
    }
  }

  else{

    next_x = XL + direction;

    if( next_x < 0 ){

      direction -= 0.7;
      direction *= -1;
      Y++;
    }

    else{

      XR += direction;
      XL += direction;
    }
  }
}

void Alien::PrintAlien( int y, int x ){

  mvprintw( y+0, x, ALIENH1 );
  mvprintw( y+1, x, ALIENH2 );
  mvprintw( y+2, x, ALIENH3 );
  mvprintw( y+3, x, ALIENH4 );

  refresh();
}
