
#include "field.h"

cell::cell(field &game, int x, int y): game(game), x(x), y(y), placed_ship(0){}

bool cell::operator()(){
    return checked;
}


void cell::fill(ship_numer place_ship){
    placed_ship = place_ship;
}


void cell::dead_of_ship(){
    checked = true;
}

bool cell::free(){return (placed_ship == 0);}

ship_numer cell::check(){
    //assert(checked == false && "cell shouldn't be shooted at");
    checked = true;
    return placed_ship;
}
