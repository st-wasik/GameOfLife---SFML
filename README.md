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
All of these settings can be changed <b>only</b> before compilation. **This will be changed in future.** <br/>
<b>4.1.1</b> To run program in fullscreen you have to use #define fullscreen in GameOfLife.cpp. <br/>
<b>4.1.2</b> To hide cells outlines you have to use #define no_cell_outline in GameOfLife.cpp. <br/>
<b>4.1.3</b> To change the game rule you have to call game.setRule("...") in main.cpp. The basic Conway's Game of Life rule is 23/3. To set this rule simply call game.setRule("23/3"). More rules can be found on: https://pl.wikipedia.org/wiki/Gra_w_%C5%BCycie#Modyfikacje_gry_w_%C5%BCycie<br/>

### 4.2 Key binding
<pre>Esc           - Close program</pre>
<pre>Num+          - Make simulation faster</pre>
<pre>Num-          - Make simulation slower</pre>
<pre>Space         - Full speed of simulation</pre>
<pre>Num*          - Make random cells alive</pre>
<pre>Num/          - Kill all life</pre>
<pre>Num0          - Highlight central cell</pre>
<pre>Enter         - Simulation start/stop</pre>
<pre>Mouse:Left    - Make selected cell alive</pre>
<pre>Mouse:Right   - Kill selected cell</pre>

## 5.License
### GNU GPL v3.0
Refer to **license.md** for more.

## 6.Credits
Stanislaw Wasik, Poznan 2017-2018
