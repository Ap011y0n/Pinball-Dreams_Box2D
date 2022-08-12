# Pinball-Dreams_Box2D
Pinball Dreams is a pinball simulation video game developed by Digital Illusions and originally released for the Amiga in 1992.
It strenghts are it's great gameplay mechanics, the incredible audio effects and the physics system and smooth gameplay, which resulted in this game being a great succes.

## Original game:
* Play online:
https://arcadespot.com/game/pinball-dreams/
* Download emulator:
https://gamesnostalgia.com/download/pinball-dreams/3269

## Creators of this project:
* Albert Garcia Belerda
https://github.com/Ap011y0n

* Pol de la Torre Solé
https://github.com/polf780

## Github source
* https://github.com/Ap011y0n/Pinball-Dreams_Box2D

## Compile

```c
cmake --install-prefix=<PREFIX> . && make install

```

## Controls and gameplay
* Press left arrow to use left flipper <--
* Press right arrow to use right flipper -->
* Press down arrow to charge up the kicker
* Press 1 to start the match, or repeat the match if you already lost
* Press 2 to display your balls left
* Press 3 to display your current score
* Press 4 to display your previous score
* Press 5 to display your highscore

* F1, to enter DEBUG mode, here you can see colliders, and click and drag bodies affected by gravity, like the ball, to test map interactions

### Gameplay mechanics:

* "WARP" ROLL OVERS               
Light all letters to  collect 2, 3, 4, 6 + 8 times bonus multiplier. To light a letter permanently, you must go through it 2 times without lightening any other letter.

* "LIGHT" TARGETS                     
Light  all letters to enable  EXTRA BALL, 5 and 10 MILLION points  in turn.

* TOP-LEFT PASSAGE                 
Collect and raise the current RAMP VALUE. Also awards  PLANET WARP, 5 and 10 MILLION  points when enabled.

* RIGHT PASSAGE                 
Scores  one BOOST  (10,000 points) and  lights the next SUN letter. Repeat this to score DOUBLE BOOST (20,000 points) and TRIPLE BOOST(30,000 points).

* BALL TRAP             
Collect  and cycle  the current  points value  and collect EXTRA BALL when enabled.

* "RED" TARGETS          
Add an IGNITION letter when all 3 are lit.

* "IGNITION" LETTERS     
Collect when all letters lit. Awards whit 1,000,000 points

* "FUEL" TARGETS     
Light them up and collect your fuel at the left passage to receive 500,000 points

## Differences with the original
To decrease difficulty, we didnt apply some concepts like the left passage putnuation, that decreased it's rewards every 20 seconds.
Some other interactions are missing, like planet travelling after collecting fuel, so we added a ponts reward. 
There is no bonus and jackpot score in our game.
Few sounds are missing or different from the original game
