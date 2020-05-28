#define AMenu1  "                _____                "
#define AMenu2  "             ,-\"     \"-.             "
#define AMenu3  "            / o       o \\            "
#define AMenu4  "           /   \\     /   \\           "
#define AMenu5  "          /     )-\"-(     \\          "
#define AMenu6  "         /     ( 6 6 )     \\         "
#define AMenu7  "        /       \\ \" /       \\        "
#define AMenu8  "       /         )=(         \\       "
#define AMenu9  "      /   o   .--\"-\"--.   o   \\      "
#define AMenu10 "     /    I  /  -   -  \\  I    \\     "
#define AMenu11 " .--(    (_}y/\\       /\\y{_)    )--. "
#define AMenu12 "(    \".___l\\/__\\_____/__\\/l___,\"    )"
#define AMenu13 " \\                                 / "
#define AMenu14 "  \"-._      o O o O o O o      _,-\"  "
#define AMenu15 "      `--Y--.___________.--Y--'      "
#define AMenu16 "         |==.___________.==| hjw     "
#define AMenu17 "         `==.___________.==' `97     "

#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <vector>

#include "projectile.h"
#include "ship.h"
#include "alien.h"

using namespace std;

typedef vector< Projectile > proj_vec;

class Game{
  public:
    Game( int );
    
    void start();
    void ShowMenu();
    void PrintInitAlien( int );
    float SetDifficulty();
    
    
  private:
    proj_vec project;
    
    WINDOW * menuwin;
    WINDOW * gamewin;
    
    float speed;
    
};

