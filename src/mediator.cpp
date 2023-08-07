#include "../include/mediator.hpp"
#include "../include/structures.hpp"



Mediator::Mediator(std::string mapFile, std::string statusFile, Player player1, Player player2): curObjId(0), rounds(2000), playerTurn(0) {
	this->mapFile = mapFile;
    readMap();
;	this->statusFile = statusFile;
	this->players[0] = player1;
	this->players[1] = player2;
    findBases();
    findWalls();
    findMines();
}


void Mediator::readMap() {
    std::ifstream map(this->mapFile);
    if (!map.good()) {
        cerr << "Error opening file mapa.txt " << "\t";
        map.ignore();
        map.clear();
        map.close();
        exit(-1);
    }

    map >> this->map;

    setY(countY(this->map));
    setX(countX(this->map, this->Y));
}

coordinates Mediator::find(char ch) {
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[i].size(); j++) {
            if (this->map[i][j] == ch) {
                coordinates coord;
                coord.x = j;
                coord.y = i;
                return coord;
                
            }
        }
    }
    coordinates coord = { -1 };
    coord.y = -1;
    return coord;
}

std::shared_ptr<Mob> Mediator::findMobOnCoordinates(int x, int y) {
    std::shared_ptr<Mob> mob;
    mob = this->players[0].findPlayerMobOnCoordinates(x, y);
    if (mob->hitPoint > 0) {
        return mob;
    }

    mob = this->players[1].findPlayerMobOnCoordinates(x, y);
    mob->isEnemy = 1;
    return mob;
};

void Mediator::findBases() {
    coordinates coord1 = this->find('1');
    coordinates coord2 = this->find('2');
    if(coord1.x == -1 || coord2.x == -1){
        cerr << "Error in map.txt " << "\t";
        exit(-1);
    }
    Base * base1 = new Base(this->getObjId(), coord1.x, coord1.y);
    Base* base2 = new Base(this->getObjId(), coord2.x, coord2.y);
    std::shared_ptr<Mob> base1Ptr(base1);
    std::shared_ptr<Mob> base2Ptr(base2);

    this->players[0].mobs[base1Ptr->getID()] = base1Ptr;
    this->players[0].base = base1Ptr;
    this->players[1].mobs[base2Ptr->getID()] = base2Ptr;
    this->players[1].base = base2Ptr;

}

void Mediator::findWalls() {
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[i].size(); j++) {
            if (this->map[i][j] == '9') {
                coordinates coord;
                coord.x = j;
                coord.y = i;
                this->walls.push_back(coord);

            }
        }
    }
}

void Mediator::findMines() {
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[i].size(); j++) {
            if (this->map[i][j] == '6') {
                coordinates coord;
                coord.x = j;
                coord.y = i;
                this->mines.push_back(coord);

            }
        }
    }
}


bool Mediator::isWallOnCoordinates(int x, int y) {
    for (coordinates& wall : this->walls)
    {
        if (wall.x == x && wall.y == y) {
            return 1;
        }
    }
    return 0;
}

void Mediator::round() {
   bool hasAttacked = 0;
   Player *player = &this->players[int(this->playerTurn)];
   Player *enemy = &this->players[int(!this->playerTurn)];

   
//status
   std::ofstream status(this->statusFile);
   if (!status.good()) {
       fileNotOk(status, "Error opening file status.txt ");
   }

   status << player->money << endl;
   for (auto &pair : player->mobs) {
       std::shared_ptr<Mob> mob = pair.second;
       mob->isEnemy = 0;
       status << "P " << std::string(*mob) <<endl;
   }
   
   for (auto& pair : enemy->mobs) {
       std::shared_ptr<Mob> mob = pair.second;
       mob->isEnemy = 1;
       status << "E " << std::string(*mob) << endl;
   }

   status.clear();
   status.close();
   // run

   std::system(("./" + player->file + " " + this->mapFile + " " + this->statusFile + " " + player->rozkazyfile + " 5").c_str());
   //do
   std::fstream testfile(player->rozkazyfile);
   if (!testfile.good()) {
       fileNotOk(testfile, "Error opening file rozkazy.txt ");
   }
   
   std::string line;

   while (std::getline(testfile, line))
   {
       int id = 9;
       char akcja = 'a';
       std::shared_ptr<Mob> mob;
       std::istringstream iss(line);
       
       if (!(iss >> id)) {
           fileNotOk(testfile, "Error parsing rozkazy.txt. Disqualification of player " + (int(this->playerTurn)+1));
       }
       
       if (player->mobs.find(id) == player->mobs.end()) {
           fileNotOk(testfile, "No such id. Disqualification of player " + (int(this->playerTurn) + 1));
       }

       mob = player->mobs.at(id);


       if (!(iss >> akcja)) {
           fileNotOk(testfile, "Error parsing rozkazy.txt. Disqualification of player " + (int(this->playerTurn) + 1));
       }

       switch (akcja)
       {
       case 'M': {
           if (mob->type == B) {
               fileNotOk(testfile, "Illegal action. Disqualification of player " + (int(this->playerTurn) + 1));
           }
           int x = 0, y =0 ;

           if (!(iss >> x >> y)) {
               fileNotOk(testfile, "Error parsing rozkazy.txt. Disqualification of player " + (int(this->playerTurn) + 1));
           }
           if (0 > x || x > this->X || 0 > y  || y > this->Y) {
               fileNotOk(testfile, "Out of bounadries. Disqualification of player " + (int(this->playerTurn) + 1));
           }

           std::shared_ptr<Mob> neighbour = this->findMobOnCoordinates(x, y);
           if (neighbour->hitPoint> 0 && neighbour->isEnemy) {
               fileNotOk(testfile, "Space is occupied. Disqualification of player " + (int(this->playerTurn) + 1));
           }

           if (this->isWallOnCoordinates(x, y)) {
               fileNotOk(testfile, "Player hit the wall! Disqualification of player " + (int(this->playerTurn) + 1));
           }
           mob->move(x, y, this->map);
           break;
       }
       case 'A': {
           if (hasAttacked) {
               fileNotOk(testfile, "Player too weak to attack twice!. Disqualification of player " + (int(this->playerTurn) + 1));
           }
           hasAttacked = 1;

           if (mob->type == B) {
               fileNotOk(testfile, "Illegal action. Disqualification of player " + (int(this->playerTurn) + 1));
           }

           int enemyId = 0;
           if (!(iss >> enemyId)) {
               fileNotOk(testfile, "Error parsing rozkazy.txt. Disqualification of player " + (int(this->playerTurn) + 1));
           }

           if(enemy->mobs.find(enemyId) == enemy->mobs.end()) {
               fileNotOk(testfile, "Stop fighting your imagination! Disqualification of player " + (int(this->playerTurn) + 1));
           }
           std::shared_ptr<Mob> enemyMob = enemy->mobs[enemyId];
           mob->attack(enemyMob);
           if (enemyMob->hitPoint <= 0) {
               if (enemyMob->type == B) {
                   cout << "Win player " << int(playerTurn) << "!";
                   testfile.clear();
                   testfile.close();
                   exit(1);
                   
               }
               enemy->mobs.erase(enemyId);
           }
           

           break;
       }
       case 'B': {
           if (mob->type != B) {
               fileNotOk(testfile, "Illegal action. Disqualification of player " + (int(this->playerTurn) + 1));
           }
           if (player->buildedMob != nullptr) {
               if (player->buildedMob->buildTime > 0) {
                   fileNotOk(testfile, "We don't have enough hands D:. Disqualification of player " + (int(this->playerTurn) + 1));
               }
           }

           char type = B;
           if (!(iss >> type)) {
               fileNotOk(testfile, "Illegal action. Disqualification of player " + (int(this->playerTurn) + 1));
           }


           switch (type)
           {
           case A:
               player->buildedMob = new Archer(this->getObjId(), player->base->x, player->base->y);
               break;
           case C:
               player->buildedMob = new Catapult(this->getObjId(), player->base->x, player->base->y);
               break;
           case K:
               player->buildedMob = new Knight(this->getObjId(), player->base->x, player->base->y);
               break;
           case P:
               player->buildedMob = new Pikeman(this->getObjId(), player->base->x, player->base->y);
               break;
           case R:
               player->buildedMob = new Ram(this->getObjId(), player->base->x, player->base->y);
               break;
           case S:
               player->buildedMob = new Swordsman(this->getObjId(), player->base->x, player->base->y);
               break;
           case W:
               player->buildedMob = new Worker(this->getObjId(), player->base->x, player->base->y);
               break;
           default:
               player->buildedMob = new Base(this->getObjId(), player->base->x, player->base->y);
           }

           player->money -= player->buildedMob->cost;
           if (player->money < 0) {
               fileNotOk(testfile, "Take a loan or find a job maybe... Whatever... Disqualification of player " + (int(this->playerTurn) + 1));
           }
           player->base->product = type;
           break;
       }
       default:
           fileNotOk(testfile, "Dancing isn't legal move!. Disqualification of player " + (int(this->playerTurn) + 1));
       }
   }

   this->swapTurn();
   testfile.clear();
   testfile.close();

}

int Mediator::getObjId() {
    int id = this->curObjId;
    this->curObjId++;
    return id;
}


void Mediator::swapTurn() {
    this->players[int(!playerTurn)].reload();
    this->players[int(!playerTurn)].dig(this->mines);
    this->rounds = this->rounds - 1;
    this->playerTurn = !this->playerTurn;
}


template<typename T>
int Mediator::countX(const std::vector<std::vector<T> >& v, int numY) {
    int numX;
    if (numY > 0) {
        numX = v[0].size(); // Number of columns is the size of the first inner vector
    }
    else {
        numX = 0; // Empty map, so no columns
    }
    return numX;
}

template<typename T>
int Mediator::countY(std::vector<T>& v) {
    return v.size();
}

void Mediator::setX(int x) {
    this->X = x;
}

void Mediator::setY(int y) {
    this->Y = y;
}

