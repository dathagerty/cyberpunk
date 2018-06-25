# Cyberpunk Roguelike

I have always been interested in making a roguelike, and I think this will be
a good opporuntity to learn libtcod and C++.
I am following [this](http://www.roguebasin.com/index.php?title=Complete_roguelike_tutorial_using_C%2B%2B_and_libtcod_-_part_1:_setting_up) RogueBasin tutorial, and will be adding some cyberpunk themes to the setting and items in the tutorial.

# About this project

## Dependencies

This project depends on libtcod. Headers are included in this repository, but the libraries are not. Currently, to compile this project, the libraries must be added to the `lib/` directory or be on your compiler's search path.

## Compiling

To compile, invoke your compiler of choice on a command line and inform it of the location of source files, includes, libraries, and set a name for the executable output. On my Mac, this command looks like: `g++ src/*.cpp -o cyberpunk -Iinclude -L. -ltcod -ltcodxx -Wall`.
