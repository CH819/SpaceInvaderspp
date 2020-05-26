#include "alien.h"

Alien::Alien( float y, float x ){

  XL = x;
  XR = x + LENGHT;

  Y = y;

  Counter = 0;
  direction = 0.3;
}

void Alien::UpdatePosition( float max_x ){


  float N = 4;
  float M = 2;
  
  mat aliens( M, vec( N ) );

  aliens[1][1] = 1;

  float next_x;

  for ( float j=0; j<M; j++ ){
    for ( float i=0; i<N; i++ ){

      if ( aliens[j][i]==1 && Counter != 0 ){

        PrintWhiteSpace( Y + HEIGHT*j, XL + LENGHT*i );
      }

      else {

        PrintAlien( Y + HEIGHT*j, XL + LENGHT*i );
      }
    }
  }

  refresh();

  usleep( DELAY );

  if ( direction > 0 ){

    next_x = XR + direction;

    if( next_x  >= max_x - (N-1)*LENGHT ){

      direction += 0.3;
      direction *=-1;
      Y++;
      Counter++;
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

void Alien::PrintAlien( float y, float x ){

  mvprintw( y+0, x, ALIENH1 );
  mvprintw( y+1, x, ALIENH2 );
  mvprintw( y+2, x, ALIENH3 );
  mvprintw( y+3, x, ALIENH4 );
}

void Alien::PrintWhiteSpace( float y, float x ){

  mvprintw( y+0, x, DALIEN1 );
  mvprintw( y+1, x, DALIEN1 );
  mvprintw( y+2, x, DALIEN1 );
  mvprintw( y+3, x, DALIEN1 );

  refresh();

  mvprintw( y+0, x, DALIEN2 );
  mvprintw( y+1, x, DALIEN2 );
  mvprintw( y+2, x, DALIEN2 );
  mvprintw( y+3, x, DALIEN2 );
  
}
