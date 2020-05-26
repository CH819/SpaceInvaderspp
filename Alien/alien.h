#include <unistd.h>
#include <ncurses.h>

#define ALIENH1 "     ___      "
#define ALIENH2 " ___/   \\___ "
#define ALIENH3 "/   '---'   \\"
#define ALIENH4 "'--_______--' "

#define LENGHT 14
#define HEIGHT 4

#define DELAY 30000


class Alien{

 public:

  //Initialize alient with uppper y and left x
  Alien( int, int );

  void GetXPosition( int * );
  int UpdatePosition( int, int );

  void PrintAlien( int, int );

 private:

  int XL, XR; //Horizontal positions: Left and Right
  int Y; //Vertical position of upper part
  int direction;

};
