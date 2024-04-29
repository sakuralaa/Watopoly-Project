#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <string>
#include <vector>
#include "graphicdisplay.h"
#include "box.h"
#include "observer.h"
#include "Building.h"
#include "gameboard.h"
#include "player.h"
#include "dice.h"
#include "buildingobserver.h"
#include "normal.h"
#include "testingdice.h"
int main(int argc, char* argv[]) {
   Xwindow x = Xwindow();
   x.loadBoxes();
   GameBoard G = GameBoard();
   x.drawBoard();
   BuildingObserver b = BuildingObserver();
   G.attachObserver(&x);
   G.attachObserver(&b);
   G.init();
   G.setObserver1Src();

   bool testingMode = false;
   std::string loadFilename;

   for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      
      if (arg == "-load" && (i + 1) < argc) {
         loadFilename = argv[++i];
      } else if (arg == "-testing") {
         testingMode = true;
      } else {
         std::cerr << "Invalid command: " << arg << std::endl;
         return 1; 
      }
   }

   if (!loadFilename.empty()) {
      G.loadGame(loadFilename);
   }

   if(testingMode){
      G.setDiceStrategy(make_unique<TestingDiceStrategy>());
   }else{
      G.setDiceStrategy(make_unique<NormalDiceStrategy>());
   }

   string s;
   while(true){
      cin >> s;
      if(s == "roll"){
         if(!G.canRoll){
            if(G.playerMove(0)){
               cout << "you have cleared" << endl;
               G.canRoll = true;
               G.nextPlayer();
               auto [a,b] = G.roll();
               int sum = a + b;
               if(G.playerMove(sum)){
                  G.nextPlayer();
               }else{
                  G.canRoll = false;
                  continue;
               }
            }else{
               cout << "please have enough money or drop out" << endl;
               continue;
            }
         }
         auto [a,b] = G.roll();
         int sum = a + b;
         if(G.playerMove(sum)){
            G.nextPlayer();
         }else{
            G.canRoll = false;
            continue;
         }
      }
      else if(s == "bankrupt"){
         G.bankrupt();
         G.canRoll = true;
      }
      else if(s == "q"){
         break;
      }
      else if(s == "next"){
         G.canRoll = true;
         if(!G.nextPlayer()){
            cout << "THE GAME IS END, NOW WE HAVE A WINNER" << endl;
            break;
         }
      }
      else if(s == "all"){
         G.all();
      }else{
         cerr << "invalid command" << endl;
      }
   }
   x.waitForCloseEvent();
}
