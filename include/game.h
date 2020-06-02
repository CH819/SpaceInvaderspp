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
#include <fstream>
#include <cmath>


#include "projectile.h"
#include "ship.h"
#include "alien.h"

using namespace std;

typedef vector< Projectile > proj_vec;

class Game{
  
  public:
    Game( int );
    
    void Start();
    void start_game_window();
    void Play();
    void ShowMenu();
    void PrintInitAlien( int );
    float SetDifficulty();

    void check_projectile_impact( class Aliens& );
    void check_bomb_impact( class Aliens&, class Ship&, int& w );
    void generate_bomb( class Aliens& );

    
    //High Score related functions
    void show_hiscores();
    void check_score();    
    void init_hiscores();
    void new_hiscore( string * );


    
  private:
    
    string lost, won;
    
    proj_vec project; //Shot by player
    proj_vec bombs; // Shot by aliens
    
    WINDOW * menuwin;
    WINDOW * gamewin;
    WINDOW * infowin;
    WINDOW * hswin;
    
    float speed;
    
    int yMaxSTD,  xMaxSTD;   //Max Coordinates for Std Screen
    int yMaxMenu, xMaxMenu; //For Menu Screen
    int yMaxInfo, xMaxInfo; //For Info Screen
    float yMaxGame, xMaxGame; //For Game Screen
    
    int Score = 0;
    
    string names[5];
    string scores[5];
};

