#include "alien.h"

Aliens::Aliens( float y, float x, int n, int m ){

  XL = x;
  XR = x + LENGHT;

  Y = y;

  direction = 0.3;
  
  N = n; //Number of columns
  M = m; //Number of rows
  
  mat AliensStatus( M, vec( N ) );
  
}

void Aliens::UpdatePosition( float max_x ){



  float next_x;

  for ( float j=0; j<M; j++ ){
    for ( float i=0; i<N; i++ ){

        PrintAlien( Y + HEIGHT*j, XL + LENGHT*i );
    
    }
  }


  usleep( DELAY );

  if ( direction > 0 ){

    next_x = XR + direction;

    if( next_x  >= max_x - (N-1)*LENGHT ){

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

      direction *= -1;
      Y++;
    }

    else{

      XR += direction;
      XL += direction;
    }
  }
}

void Aliens::PrintAlien( float y, float x ){

  mvprintw( y+0, x, ALIENH1 );
  mvprintw( y+1, x, ALIENH2 );
  mvprintw( y+2, x, ALIENH3 );
  mvprintw( y+3, x, ALIENH4 );
}

void Aliens::PrintWhiteSpace( float y, float x ){

  mvprintw( y+0, x, DALIEN1 );
  mvprintw( y+1, x, DALIEN1 );
  mvprintw( y+2, x, DALIEN1 );
  mvprintw( y+3, x, DALIEN1 );
}
