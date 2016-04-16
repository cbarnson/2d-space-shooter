# Call of Shooty

2D side-scrolling shooter inspired by 1980s arcade classics that pioneered the 
genre.  

Call of Shooty features fast-paced arcade-style action with dynamic enemy
waves, 5+ enemy variations, enemy boss battles, a score-based upgrade system,
highscore tracking across local games, 2 game modes, and multiple weapon types.

## Installation

Allegro version 5.0.11 or later http://liballeg.org/old.html
The following addons are required:

* allegro-font
* allegro-ttf
* allegro-primitives
* allegro-image

## Usage

Modify provided Makefile in directory src/ to include necessary headers
and specify locations to runtime libraries. Run <make> from command line
to compile project and produce executable.  

Running exectuable will load game menu.  Pressing '1' will load the standard
single player game mode.  Pressing '2' will load the versus game mode.  At any
time, hitting 'ESC' will exit the game.

## Known Bugs

In the Versus game mode, there seems to be an issue with 
ALLEGRO_KEYBOARD_STATE struct.  When either player holds down the primary
fire key and reduces the health of the opposing player to zero, a segmentation
fault will occur.  A bug fix is in progress.

## History

Originally created as the project for Practical Software Development course
to demonstrate ability to create flexible and reliable software.  

## Credits

Cody Barnson

Josh Mohan

Dawson Meyer

## License

Allegro 5 game programming library

http://liballeg.org/license.html