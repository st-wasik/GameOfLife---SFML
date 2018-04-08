# GameOfLife

## 1.Overview
This is The Game Of Life based on SFML library.

## 2.Tools
SFML library

## 3.How to run
Download SFML from https://www.sfml-dev.org/download.php. This project is based on **SFML 2.4.2.** <br/>
Open project using IDE and configure for SFML (https://www.sfml-dev.org/tutorials/2.4/#getting-started). <br/>
Compile project and run. 

## 4.Game
### 4.1 Settings
All of these settings can be changed <u>only</u> before compilation. **This will be changed in future.** <br/>
4.1.1 To run program in fullscreen you have to use #define fullscreen in GameOfLife.cpp. <br/>
4.1.2 To hide cells outlines you have to use #define no_cell_outline in GameOfLife.cpp. <br/>
4.1.3 To change the game rule you have to call game.setRule("...") in main.cpp. The basic Conway's Game of Life rule is 23/3. To set this rule simply call game.setRule("23/3"). More rules can be found on: https://pl.wikipedia.org/wiki/Gra_w_%C5%BCycie#Modyfikacje_gry_w_%C5%BCycie<br/>

### 4.2 Key binding
* Esc - Close program
* Num+ - Make simulation faster
* Num- - Make simulation slower
* Space - Full speed of simulation 
* Num* - Make random cells alive
* Num/ - Kill all life
* Num0 - Highlight central cell
* Enter - Simulation start/stop
* Mouse:Left - Make selected cell alive
* Mouse:Right - Kill selected cell

## 5.License
### GNU GPL v3.0
Refer to **license.md** for more.

## 6.Credits
Stanislaw Wasik, Poznan 2017-2018
