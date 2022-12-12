#include "field.h"

ship::ship(field & game,int size, int x, int y, bool vertical, ship_numer num): 
    x(x), y(y), size(size), game(game), vertical(vertical){
        if(vertical){
            for(int i = 0; i< size; i++){
                cells.push_back(std::pair(x, y+i));
                game.fill_cell(x, y + i, num);
            }
        }
        else{
            for(int i = 0; i< size; i++){
                cells.push_back(std::pair(x + i, y));
                game.fill_cell(x + i, y, num);
            }
        }
}
    

void ship::bonk(){
    isdead = true;
    for(int it=0; it<size;it++){
        if(vertical){
            if(!(game.get_cell(std::pair(x, y + it))())) isdead = false;
        }
        else {
            if(!(game.get_cell(std::pair(x + it, y ))())) isdead = false;
        }
    }
    if(isdead){
        game.ships_dead(this);
    }
}
