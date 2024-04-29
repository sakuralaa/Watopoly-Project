# Watopoly-Project
Game Project
To compile using Makefile, please compile in the enviroment that support X11 lib, e.g. install Xquatz
GCC Compiler: GCC version 11 or higher is required
You will need GNU Make to run the makefile.

After compilation, you can run the game by executing:
./watopoly



This game is played using terminal command, please see the avaliable command:

•roll (used if the player can roll): the player rolls two dice, moves the sum of the two dice and takes action on the square
they landed on.
• next (used if the player cannot roll): give control to the next player.
• improve <property>buy/sell: attempts to buy or sell an improvement for property.
• bankrupt: player declares bankruptcy. This command is only available when a player must pay more money then they
currently have.
• assets: displays the assets of the current player. Does not work if the player is deciding how to pay Tuition.
• all: displays the assets of every player. For verifying the correctness of your transactions. Does not work if a player is
deciding how to pay Tuition.


In addition, you need to load the game with -load (the GameName.txt) e.g. -load game1.txt

you can also have the -testing flag, which switch the dice to a manual roll mode:
by using:
roll x y: x and y are integer, you can control the result of the rolling

This project is being constantly updated and more features are being added, please see the update
