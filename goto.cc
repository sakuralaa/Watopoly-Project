#include "goto.h"

GoToTims::GoToTims(const Building &building,GameBoard *game): Building(building),game(game){}

bool GoToTims::performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) {
    const int dcTimsLineIndex = 20;
    int currentPlayerIndex = player->getPosition();
    game->Buildings[currentPlayerIndex]->currPlayer.erase(
        std::remove(game->Buildings[currentPlayerIndex]->currPlayer.begin(), 
                    game->Buildings[currentPlayerIndex]->currPlayer.end(), 
                    player),
        game->Buildings[currentPlayerIndex]->currPlayer.end());
    
    game->observers[0]->notify(game->Buildings[currentPlayerIndex]);

    player->currPosition = dcTimsLineIndex;
    game->Buildings[dcTimsLineIndex]->currPlayer.push_back(player);
    
    game->observers[0]->notify(game->Buildings[dcTimsLineIndex]);

    player->setTrap();
    std::cout << player->getName() << " has been sent to the DC Tims Line." << std::endl; 
    return true;
}

DCTimsLine::DCTimsLine(const Building &building, GameBoard *game)
    : Building(building), game(game) {}

bool DCTimsLine::performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) {
    if (!player->isTrapped) {
        return true;
    } else {
        player->turnsTrap++;
        if(player->turnsTrap == 3){
            if(player->timCups >= 1){
                    player->timCups -= 1;
                    player->isTrapped = false;
                    player->turnsTrap = 0;
                    return true;
            }else if(player->charge(50)){
                    player->isTrapped = false;
                    player->turnsTrap = 0;
                    return true;
            }else{
                player->setBankrupt();
                player->setOweMoeny(currTuition);
                return false;
            }
        }
        cout << "do you want to pay or roll? or cup?" << endl;
        string cmd;
        while(true){
            cin >> cmd;
            if(cmd == "pay"){
                if(player->charge(50)){
                    player->isTrapped = false;
                    player->turnsTrap = 0;
                    break;
                    return true;
                }else{
                    player->setBankrupt();
                    player->setOweMoeny(currTuition);
                    break;
                    return false;  
                }
            }
            else if(cmd == "roll"){
                auto [die1, die2] = game->roll();
                if(die1 == die2){
                    player->isTrapped = false;
                    player->turnsTrap = 0;
                    break;
                    return true;
                }else{
                    cout << "you did not roll double , try again" << endl;
                    game->nextPlayer();
                    break;
                    return true;
                }
            }
            else if(cmd == "cup"){
                if(player->timCups >= 1){
                    player->timCups -= 1;
                    player->isTrapped = false;
                    player->turnsTrap = 0;
                    break;
                    return true;
                }else{
                    cout << "you did not have enough cup, try other way" << endl;
                    continue;
                }
            }else{
                cout <<"invalid command, retype" << endl;
                continue;
            }
        }

    }
    return true;
}