#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "projectile.h"
#include "ship.h"
#include "alien.h"
#include "game.h"

using namespace std;


int main(){
  
  Game game1(2);
  
  game1.ShowMenu();
  
  
  
  return 0;
}

