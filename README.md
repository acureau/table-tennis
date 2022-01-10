# Table Tennis
This is a clone of the game 'Table Tennis' from the very first home video game console, the Magnavox Odyssey. I wrote this to learn the basics of game development with SDL.

I tried my best to make this as accurate as possible to the source, based on the few videos I could find online. The size of each object was calculated in relation to the size of the paddle in promotional videos. The gameplay mechanics are taken from [this](https://www.youtube.com/watch?v=scaLx1l_j5w) video demonstration.
<br><br>

## How to Play
Table Tennis can only be played by two people. There are no bounds or score keeping. Each player has a reset button to serve the ball.

Table Tennis has many more quirks than Pong. The net's horizontal position and the ball's speed can be adjusted. When a player hits the ball, they are able to control its vertical movement to avoid the second player's paddle. This makes for a much more competitive game!

The paddle also does not move at the same rate constantly. Its speed is controlled by the extent to which the knobs on the controller are rotated. Because of this the paddle also slides to a stop as if it were on ice.

Unfortunately these controls do not transfer well to directional keys with only two states. To simulate this aspect of the game, paddles pick up speed the longer you hold down a directional key and slide when it's released.
<br><br>

## Controls
```
Player One
==========
Directional: W, A, S, D
Ball Up: R
Ball Down: F
Reset Ball: E

Player Two
==========
Directional: Up, Left, Down, Right (Arrows)
Ball Up: Apostrophe
Ball Down: Forward Slash
Reset Ball: Semi-Colon

Ball
==========
Speed Up: +
Speed Down: -

Net
==========
Move Left: 9
Move Right: 0
```
<br>


## How to Build
First, download the SDL Development Library from [here](https://www.libsdl.org/download-2.0.php). Extract the folder, and rename it SDL2. Put this folder in the 'src' directory. You can now build the solution in Visual Studio, or from the command line with MSBuild.