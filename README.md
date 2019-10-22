# super-smash-termbox
A very simple 1 vs 1 game in the terminal using termbox.

## How to install:
1. Install termbox development files: 
* Void Linux: xbps-install termbox-devel
* Debian based distros: apt install libtermbox-dev 
* Arch based distros: There is no package for termbox yet on Arch based distros, so you have to build termbox yourself.
2. git clone https://github.com/mathijskr/super-smash-termbox
3. cd super-smash-termbox
4. make

## How to play:
1. cd super-smash-termbox
2. make run

## Dependencies:
* tcc, the tiny c compiler. You can also use gcc, you only have to change tcc to gcc in the Makefile.
* GNU Make.
* Termbox development files.
