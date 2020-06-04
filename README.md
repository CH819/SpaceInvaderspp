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
|   ├── hiscores.txt
|   └── logos
└──extras 

```

## About the game

Space Invaders is an arcade game created by Toshihiro Nishikado and released in 1978.

A cluster of aliens moves horizontally and each time it hits the border of the screen it moves down one line. The player moves horizontally and shoots projectiles vertically.

The objective of the game is to kill all the aliens before they reach the player. The player loses if the aliens reach them or if they are hit by a projectile.


## Requirements

This game uses the ncurses library, version 6.3. To install it, run the command that matches the distribution you are using.


* For Ubuntu:

``` apt-get install libncurses5-dev libncursesw5-dev ```

* For Arch:

``` pacman -S ncurses ```

You can also follow the instructions given in [this ncurses documentation](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/intro.html#WHERETOGETIT).


## Installation

1. Clone the original repository.

``` git clone https://github.com/CH819/SpaceInvaderspp.git```

2. Open a terminal in the cloned repository and run

``` make ```

3. Run the compiled file ```play```.

``` ./play```
