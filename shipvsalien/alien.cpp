#include "alien.h"

Alien::Alien( int y, int x ){

  XL = x;
  XR = x + LENGHT;

  Y = y;

  Counter = 0;
  direction = 1;
}

void Alien::UpdatePosition( int max_x ){


  int N = 4;
  int M = 2;
  
  mat aliens( M, vec( N ) );

  aliens[1][1] = 1;

  int next_x;

  for ( int j=0; j<M; j++ ){
    for ( int i=0; i<N; i++ ){

      if ( aliens[j][i]==1 && Counter != 0 ){

        PrintWhiteSpace( Y + HEIGHT*j, XL + LENGHT*i );
      }

      else {

        PrintAlien( Y + HEIGHT*j, XL + LENGHT*i );
      }
    }
  }

 // refresh();

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

void Alien::PrintAlien( int y, int x ){

  mvprintw( y+0, x, ALIENH1 );
  mvprintw( y+1, x, ALIENH2 );
  mvprintw( y+2, x, ALIENH3 );
  mvprintw( y+3, x, ALIENH4 );
}

void Alien::PrintWhiteSpace( int y, int x ){

//   mvprintw( y+0, x, DALIEN1 );
//   mvprintw( y+1, x, DALIEN1 );
//   mvprintw( y+2, x, DALIEN1 );
//   mvprintw( y+3, x, DALIEN1 );
// 
//   refresh();

  mvprintw( y+0, x, DALIEN2 );
  mvprintw( y+1, x, DALIEN2 );
  mvprintw( y+2, x, DALIEN2 );
  mvprintw( y+3, x, DALIEN2 );
  
}
