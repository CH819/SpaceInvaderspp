# SpaceInvaderspp

## Contributors:
Carolina Herrera Segura, David Silva Sánchez

## Project structure
```
. SpaceInvaderspp
├── Makefile
├── include
│  └── headers
├── src
|   └── Space Invaders game
├── data
|   └── hiscores.txt
└──extras  
    └── images
```

## About the game

Space Invader is an arcade game created by Toshihiro Nishikado and released in 1978.

A cluter of aliens moves horizontally and each time it hits the border of the screen it moves down one line. The player moves horizontally and shoots projectiles vertically.

The objective of the game is to kill all the aliens before they reach the player.


## Requirements

This game uses the ncurses library, version 6.3. To install it, run the command that matches the distribution you are using.


* For Ubuntu:

``` apt-get install libncurses6-dev libncursesw6-dev ```

* For Arch:

``` pacman -S ncurses ```

You can also follow the instructions given in [the official ncurses documentation](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/intro.html#WHERETOGETIT).


## Installation

1. Clone the original repository.

``` git clone https://github.com/CH819/SpaceInvaderspp.git```

2. Open a terminal in the cloned repository and run

``` make ```

3. Run the compiled file ```play```.

``` ./play```
