# python-playdate
Python on the Playdate using pocketpy

Currently WIP and could use help

How it works
parser.py goes through the Playdate c docs and generates function bindings from it that pocketpy uses. Then game.c binds the functions to a playdate module and then runs main.py.

Todo
* .pyi generation
* upload generator and incorperate handmand changes into it
* fix issue with header being seperate
* incorperate missing functions/fix crashes
* more testing
* pythonic classes
* fix importing

![image](https://github.com/user-attachments/assets/f00fbb8e-4b8b-401b-8aa4-0f28c104af07)
Running in simulator
