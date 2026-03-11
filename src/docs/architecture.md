# Game Concept
A player is an hse bachelor first-year student
They walk into the hallway, enter different rooms like home apartment, lecture hall, et cetera. Have several stats: mental health, energy, knoweldge, which change after some actions are done

# Rooms' descriptions
- lecture hall ~ gives 5 knowledge, takes 5 energy (if walked in from home apartment) and 0 otherwise, other parametres are unchanged
- seminar room ~ gives 35 knowledge, takes 25 energy
- home apartment ~ gives 15 mental health, 10 energy
- cafeteria ~ gives 12 energy, takes 1 mental health
- to be updated...

# Student parameters
- mental health (-100 <=> +150) - if it is negative one receives achivement ``depression`` if it reaches 150 then a player is in ``zen`` state
- energy (0 <=> 100) - a player needs energy to perform any tasks
- knoweldge (0 <=> unlimited) - one needs knoweldge to ... to ... ?
- to be updated...

## Textures:
  corridor_background: assets/textures/corridor.png
  student: assets/textures/student.png

## Fonts:
  main: assets/fonts/OpenSans-Light.ttf