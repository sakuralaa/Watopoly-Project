#include "gameboard.h"
#include "graphicdisplay.h"

// Now actually define the variables here
std::vector<char> playerList = {'G','B', 'D', 'P', 'S', '$', 'L', 'T'};

std::vector<std::string> names = {
    "GO TO TIMS", "B2", "CIF", "B1", "PHYS", "V1", "EV3", "EV2", "NEEDLES HALL", "EV1",
    "GOOSE NESTING", "PAC", "RCH", "DWE", "CPH", "UWP", "LHI", "SLC", "BMH", "OPT",
    "DC Tims Line", "HH", "PAS", "ECH", "MKV", "TUITION", "ML", "AL", "SLC", "COLLECT OSAP",
    "EIT", "ESC", "SLC", "C2", "REV", "NEEDLES HALL", "MC", "COOP FEE", "DC", "NEEDLES HALL"
};

std::unordered_map<std::string, AcademicBuildingData> academicBuildingInfo = {
    {"AL", {{26, 27}, 40, 50, {2, 10, 30, 90, 160, 250}}},
    {"ML", {{26, 27}, 60, 50, {4, 20, 60, 180, 320, 450}}},
    {"ECH", {{23, 22, 21}, 100, 50, {6, 30, 90, 270, 400, 550}}},
    {"PAS", {{23, 22, 21}, 100, 50, {6, 30, 90, 270, 400, 550}}},
    {"HH", {{23, 22, 21}, 120, 50, {8, 40, 100, 300, 450, 600}}},
    {"RCH", {{12, 13, 14}, 140, 100, {10, 50, 150, 450, 625, 750}}},
    {"DWE", {{12, 13, 14}, 140, 100, {10, 50, 150, 450, 625, 750}}},
    {"CPH", {{12, 13, 14}, 160, 100, {12, 60, 180, 500, 700, 900}}},
    {"LHI", {{18, 19, 16}, 180, 100, {14, 70, 200, 550, 750, 950}}},
    {"BMH", {{18, 19, 16}, 180, 100, {14, 70, 200, 550, 750, 950}}},
    {"OPT", {{18, 19, 16}, 200, 100, {16, 80, 220, 600, 800, 1000}}},
    {"EV1", {{7, 6, 9}, 220, 150, {18, 90, 250, 700, 875, 1050}}},
    {"EV2", {{7, 6, 9}, 220, 150, {18, 90, 250, 700, 875, 1050}}},
    {"EV3", {{7, 6, 9}, 240, 150, {20, 100, 300, 750, 925, 1100}}},
    {"PHYS", {{4, 1, 3}, 260, 150, {22, 110, 330, 800, 975, 1150}}},
    {"B1", {{4, 1, 3}, 260, 150, {22, 110, 330, 800, 975, 1150}}},
    {"B2", {{4, 1, 3}, 280, 150, {24, 120, 360, 850, 1025, 1200}}},
    {"EIT", {{30, 31, 33}, 300, 200, {26, 130, 390, 900, 1100, 1275}}},
    {"ESC", {{30, 31, 33}, 300, 200, {26, 130, 390, 900, 1100, 1275}}},
    {"C2", {{30, 31, 33}, 320, 200, {28, 150, 450, 1000, 1200, 1400}}},
    {"MC", {{38, 36}, 350, 200, {35, 175, 500, 1100, 1300, 1500}}},
    {"DC", {{38, 36}, 400, 200, {50, 200, 600, 1400, 1700, 2000}}}
};

vector<int> nonPropertyIndex = {0,8,10,17,20,25,28,29,32,35,37,39};
vector<int> academicIndex = {1,3,4,5,6,7,9, 12,13,14,15,16, 18,19,21,22,23,26,27,30,31,33,36,38};

vector<int> residenceIndex = {5,15,24,34};
vector<int> gymIndex = {2,11};

GameBoard::GameBoard() : currPlayerIdx(0) {}

void GameBoard::init() {
    // Initialize all buildings as Building objects
    for (int i = 0; i < static_cast<int>(names.size()); ++i) {
        Buildings.push_back(make_shared<Building>(i, names[i]));
    }

    // Convert specified buildings to AcademicBuilding objects
    for (int index : academicIndex) {
        auto& currBuilding = Buildings[index]; 
        auto it = academicBuildingInfo.find(currBuilding->name);
        if (it != academicBuildingInfo.end()) {
            const auto& academicData = it->second;
            Buildings[index] = make_shared<AcademicBuilding>(
                *currBuilding,
                academicData.monopolyBlockIndices,
                academicData.purchaseCost,
                academicData.improvementCost,
                academicData.tuitionWithImprovements
            );
        }
    }

    cout << "Academic init success" << endl;
    const int residencePurchaseCost = 200;
    const vector<int> rentWithMultipleOwned = {25, 50, 100, 200};

    for (int index : residenceIndex) {
        auto currBuilding = Buildings[index]; 
        if (currBuilding) {
            Buildings[index] = make_shared<Residence>(
                *currBuilding,
                residenceIndex,
                residencePurchaseCost,
                rentWithMultipleOwned
            );
        }
    }
    cout << "residence init success" << endl;

    const int gymPurchaseCost = 150;
    for (int index : gymIndex) {
        auto currBuilding = Buildings[index]; 
        if (currBuilding) {
            Buildings[index] = make_shared<Gym>(
                *currBuilding,
                gymIndex,
                this,
                gymPurchaseCost
            );
        }
    }
    cout << "gym init success" << endl;

    
    std::vector<int> noFunctionIndices = {10, 28, 32, 35, 0, 8, 17, 39};
    for (int index : noFunctionIndices) {
        Buildings[index] = std::make_shared<noFunction>(*Buildings[index]);
    }

    // Replace specific buildings with specialized non-property subclass instances
    Buildings[0] = std::make_shared<GoToTims>(*Buildings[0],this);
    Buildings[20] = std::make_shared<DCTimsLine>(*Buildings[20],this);
    Buildings[25] = std::make_shared<Tuition>(*Buildings[25]);
    Buildings[29] = std::make_shared<CollectOSAP>(*Buildings[29]);
    Buildings[37] = std::make_shared<CoopFee>(*Buildings[37]);

    cout << "Non-property initialization success." << endl;
}



void GameBoard::attachObserver(Observer *b) {
    observers.push_back(b);
    cout << "obs success" << endl;
}

bool GameBoard::playerMove(int move) {

    if(currPlayer->isTrapped){
        if(!Buildings[20]->performAction(currPlayer,Players)){
        cout << "you must pay the outstanding balace" << endl;
        return false;
    }else{
        return true;
    }
    }


    int index = currPlayer->getPosition();
    shared_ptr<Building> b = Buildings[index];

    b->currPlayer.erase(remove(b->currPlayer.begin(), b->currPlayer.end(), currPlayer), b->currPlayer.end());


    observers[0]->notify(b);

    currPlayer->move(move);
    index = currPlayer->getPosition();
    Buildings[index]->currPlayer.push_back(currPlayer);
    observers[0]->notify(Buildings[index]);

    if(Buildings[index]->getOwner() == "none" && Buildings[index]->getType() != nonproperty){
        cout << "do you want to purchase this property? y or n" << endl;
        char cmd;
        cin >> cmd;
        while(cmd != 'y' && cmd != 'n'){
            cerr << "please write the valid commnad" << endl;
            cin >> cmd;
        }
        if(cmd == 'y'){
        auto currBuilding = Buildings[index];
        buildingType tp = currBuilding->getType();
        int purchaseCost = 0;

        switch (tp) {
            case academic: {
                auto specificBuilding = std::dynamic_pointer_cast<AcademicBuilding>(currBuilding);
                purchaseCost = specificBuilding ? specificBuilding->purchaseCost : 0;
                break;
            }
            case gym: {
                auto specificBuilding = std::dynamic_pointer_cast<Gym>(currBuilding);
                purchaseCost = specificBuilding ? specificBuilding->purchaseCost : 0;
                break;
            }
            case residence: {
                auto specificBuilding = std::dynamic_pointer_cast<Residence>(currBuilding);
                purchaseCost = specificBuilding ? specificBuilding->purchaseCost : 0;
                break;
            }
            default:
                std::cerr << "Unknown building type." << std::endl;
                return false;
        }
        if (purchaseCost > 0 && currPlayer->charge(purchaseCost)) {
            currBuilding->owner = currPlayer->getName();
            currPlayer->property.push_back(currBuilding->getIdx());
            observers[0] ->notify(currPlayer);
            for (auto& observer : observers) {
                observer->notify(currBuilding);
            }

            cout << "Building " << currBuilding->name << " is now owned by " << currPlayer->getName() << endl;
        } else {
            cout << "You cannot perform this action since you don't have enough money." << std::endl;
        }

        }else {
            cout << "you did not pruchase this property, now goes into the auction" << endl;
            this->auction(Buildings[index]);
        }
    }

    if(!Buildings[index]->performAction(currPlayer,Players)){
        cout << "you must pay the outstanding balace" << endl;
        return false;
    }else{
        observers[0]->notify(currPlayer);
        return true;
    }

}


bool GameBoard::nextPlayer() {
    if(Players.size() > 1){
        currPlayerIdx++;
        if (currPlayerIdx >= Players.size()) {
            currPlayerIdx = 0;
        }
        currPlayer = Players[currPlayerIdx];
        observers[0]->notify(currPlayer);
        cout << "the current player is " << currPlayer->getName() << endl;
        return true;
    }else{
        return false;
    }
}

void GameBoard::loadGame(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file\n";
            return;
        }

        int numPlayers;
        file >> numPlayers;
        file.ignore();

        unordered_map<string, shared_ptr<Player>> playerMap;
        for (int i = 0; i < numPlayers; ++i) {
            std::string line;
            std::getline(file, line);
            std::istringstream iss(line);

            std::string player,character;
            int TimsCups, money, position;
            iss >> player >> character >> TimsCups >> money >> position;

            auto newPlayer = std::make_shared<Player>(character, TimsCups, position, money);
            Players.push_back(newPlayer);
            playerMap[character] = newPlayer;
        }
        std::string line;
        int buildingIdx = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, owner;
            int improvements;
            iss >> name >> owner >> improvements;

            auto newBuilding = Buildings[buildingIdx];
            newBuilding->level = improvements;
            buildingIdx ++;
            if (owner != "BANK") {
                newBuilding->owner = owner;
                if (playerMap.find(owner) != playerMap.end()) {
                    playerMap[owner]->property.push_back(newBuilding->index);
                }
            }
        }
        for(auto i: Players){
            int index = i->getPosition();
            Buildings[index]->currPlayer.push_back(i);
            observers[0]->notify(Buildings[index]);
        }
        for(auto j: Buildings){
            observers[0]->notify(j);
            observers[1]->notify(j);
        }

        file.close();

        currPlayer = Players[0];
        currPlayerIdx = 0;
        cout << "The current player is " << currPlayer->getName() << endl;
    }

void GameBoard::setObserver1Src(){
    BuildingObserver *b = dynamic_cast<BuildingObserver *>(observers[1]);
    b->setSrc(Buildings);
}

void GameBoard::bankrupt() {
    if(currPlayer->isBankrupt) {
        // Remove the player from the current building's player list
        shared_ptr<Building> b = Buildings[currPlayer->getPosition()];
        b->currPlayer.erase(remove(b->currPlayer.begin(), b->currPlayer.end(), currPlayer), b->currPlayer.end());
        observers[0]->notify(b);

        for(int i : currPlayer->property) {
            Buildings[i]->owner = "none";
            for(auto& obs : observers) {
                obs->notify(Buildings[i]);
            }
        }
        Players.erase(Players.begin() + currPlayerIdx);
        if(currPlayerIdx >= Players.size()) {
            currPlayerIdx = 0;
        }else{
            currPlayer = Players[currPlayerIdx];
        }
        cout << "You have now declared bankrupt." << endl;
    } else {
        cout << "You cannot declare bankrupt yet." << endl;
    }
}


void GameBoard::setDiceStrategy(unique_ptr<DiceStrategy> strategy) {
    Dice::initializePRNG();
    diceStrg = std::move(strategy);
}

pair<int,int> GameBoard::roll() {
    return diceStrg->roll();
}

void GameBoard::auction(shared_ptr<Building> building) {
    vector<std::shared_ptr<Player>> copyVec = Players;
    int maxBid = 0;
    shared_ptr<Player> highestBidder = nullptr;
    int bidIndex = 0;

    while (copyVec.size() > 1) {
        if (copyVec[bidIndex] == highestBidder) {
            bidIndex = (bidIndex + 1) % copyVec.size();
            continue;
        }

        cout << "Player " << copyVec[bidIndex]->getName() << ", bid or quit? Current max bid: " << maxBid << std::endl;
        string bOrQ;
        cin >> bOrQ;

        if (bOrQ == "bid") {
            int bid;
            cout << "Enter your bid (must be higher than " << maxBid << "): ";
            cin >> bid;

            if (bid > maxBid) {
                if (copyVec[bidIndex]->asset >= bid) {
                    maxBid = bid;
                    highestBidder = copyVec[bidIndex];
                    cout << copyVec[bidIndex]->getName() << " bids " << bid << "." << endl;
                } else {
                    cout << "Insufficient assets to cover the bid. Please bid within your asset range." << endl;
                }
            } else {
                cout << "Bid must be higher than current max bid. Please try again." << endl;
            }
            bidIndex = (bidIndex + 1) % copyVec.size();
        } else if (bOrQ == "quit") {
            cout << copyVec[bidIndex]->getName() << " quits the auction." << endl;
            copyVec.erase(copyVec.begin() + bidIndex);

            // Adjust bidIndex to account for the removed player
            if (bidIndex >= static_cast<int>(copyVec.size())) {
                bidIndex = 0;
            }
        } else if(bOrQ == "q"){
            break;
            }else {
            cout << "Invalid input. Please type 'bid' to make a bid or 'quit' to exit the auction." << endl;
        }
    }

    // Handle the auction's outcome
    if (!copyVec.empty() && highestBidder) {
        highestBidder->charge(maxBid);
        observers[0] ->notify(highestBidder);
        building->owner= highestBidder->getName();
        highestBidder->property.push_back(building->getIdx());
        for(auto obs: observers){
            obs->notify(building);
        }
        cout << highestBidder->getName() << " wins the auction for " << building->name << " with a bid of " << maxBid << "!" << endl;
    }
}

void GameBoard:: all() const{
    for(auto i:Players){
        cout << "player" << i->getName() << "has $ " << i->asset << endl;
    }
}

string GameBoard::getCurrPlayer(){
    return currPlayer->getName();
}

