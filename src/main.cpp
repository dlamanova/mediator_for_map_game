#include "../include/include.hpp"
#include "../include/mediator.hpp"

int main()
{
    Player player1("rozkazy.txt", "program_gracza1");
    Player player2("rozkazy1.txt", "program_gracza2");
    Mediator mediator("map.txt", "status.txt", player1, player2);
    while(mediator.rounds>0){
        mediator.round();
    }
    if(player1.mobs.size()>player2.mobs.size()){
        cout<<"Player 1 won!"<<endl;
    }
    else if(player1.mobs.size()<player2.mobs.size()){
        cout<<"Player 2 won!"<<endl;
    }
    else{
        cout<<"Remis!" <<endl;
    }
}

