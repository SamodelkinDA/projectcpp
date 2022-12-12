#include "field.h"

field::field(int x=10, int y=10):size_x(x), size_y(y)
{
    while(max_ship*(max_ship*max_ship- 1) < x*y) max_ship++;
    max_ship--;
    // вычисление максимального размера корабля.

    cells.reserve(x+2);
    // х - первая координата по горизонтали 
    for(int i =0; i<x+2; i++){
        cells.push_back(std::vector<cell>());
        cells[i].reserve(y);
        for(int j=0; j< y+2; j++){
            cells[i].push_back(cell(*this, i, j));
        }
        
    }
    
    ships.reserve(max_ship * (max_ship + 1) / 2);
    fill_field();

}




field::field():size_x(10), size_y(10)
{
    max_ship = 4;
    // вычисление максимального размера корабля.

    cells.reserve(12);
    // х - первая координата по горизонтали 
    for(int i =0; i<12; i++){
        cells.push_back(std::vector<cell>());
        cells[i].reserve(12);
        for(int j=0; j< 12; j++){
            cells[i].push_back(cell(*this, i, j));
        }
        
    }
    ships.reserve(10);
    fill_field();
}

bool field::can_be_placed(int len, int x, int y, bool vertical){
    bool ans = true;
    if(vertical){
        if(y - 1 > size_y - len || y<1) ans = false;
        else{
        for(int i = -1; i< len+1; i++){
            if(!(cells[x][y+i].free())) ans = false;
            if(!(cells[x-1][y+i].free())) ans = false;
            if(!(cells[x+1][y+i].free())) ans = false;
        }
        }
    }
    else{
        if(x + len > size_x + 1 || x<1) ans = false;
        else{
        for(int i = -1; i< len+1; i++){
            if(!(cells[x+i][y].free())) ans = false;
            if(!(cells[x+i][y+1].free())) ans = false;
            if(!(cells[x+i][y-1].free())) ans = false;
        }
        }
    }
    return ans;
}


/*void field::fill_field(){
    ships.push_back(ship(*this, 4, 1, 1, false, 1));
    ships.push_back(ship(*this, 3, 1, 3, false, 2));
    ships.push_back(ship(*this, 3, 1, 5, false, 3));
    ships.push_back(ship(*this, 2, 1, 7, false, 4));
    ships.push_back(ship(*this, 2, 1, 9, false, 5));
    ships.push_back(ship(*this, 2, 9, 1, false, 6));
    ships.push_back(ship(*this, 1, 10, 3, false, 7));
    ships.push_back(ship(*this, 1, 10, 5, false, 8));
    ships.push_back(ship(*this, 1, 10, 7, false, 9));
    ships.push_back(ship(*this, 1, 10, 9, false, 10));

}*/

cell* field::fill_cell(int x, int y, ship_numer pl){
    assert(cells[x][y].free() && "cell in not free field::fill_cell");
    cells[x][y].fill(pl);
    return &cells[x][y];
}


void field::fill_field(){
    int numerator = 1;
    std::default_random_engine reng(clock() % 16523);
    std::uniform_int_distribution<int> dstrx(1, size_x);
    std::uniform_int_distribution<int> dstry(1, size_y);
    std::uniform_int_distribution<int> dstro(0, 1);
    for(int i = 0; i< max_ship; i++){
        for(int j = 0; j<i+1;j++){
            // len = max_ship - i, num = i+1
            bool success = false;
            while(!success){
                int x = dstrx(reng);
                int y = dstry(reng);
                bool o = dstro(reng);
                if(can_be_placed(max_ship - i, x, y, o)){
                    ships.push_back(ship(*this, max_ship - i, x, y, o, numerator));
                    numerator++;
                    success = true;
                }
            } 
        }
    }


}

ship_numer field::shoot(int x, int y){
    assert(cells[x][y]() == false && "cell shouldn't be shooted at");

    return cells[x][y].placed_ship;
}




void field::visualisation(){
    //system("cls");
    std::cout << " ";
    char a='a'-1, A = 'A';
    for(int j=1; j<= size_x; j++){
        std::cout << " " << (char)(A+j-1);
        if(j%5 == 0) std::cout << " |";
    }
    std::cout <<'\n';
    for(int i =1; i<=size_y; i++){
        std::cout << (char)(a+i) ;
        for(int j=1; j<= size_x; j++){
            if(cells[j][i]()){
                if(cells[j][i].free()) std::cout << " ."; //" o"
                else std::cout << " X";
            }
            else{
                std::cout << "  "; //" ."
            }
            if(j%5 == 0) std::cout << " |";
        }
        if(i%5==0){
            std::cout << "\n-";
            for(int j=1; j<= size_x; j++){
                std::cout << "--";
                if(j%5 == 0) std::cout << "-+";
            }
        }
        std::cout << "\n";
    }
}
field::~field()
{
    ships.clear();
    cells.clear();

}

bool field::loop_step(){
    visualisation();
    char A, a; 
    std::cout << "Turn " << counter <<  "\n";
    while(!finish){
        if(GetAsyncKeyState(VK_ESCAPE)) {
            finish = true;
            break;
        }
        std::cout << "please enter coordinates \n";
        std::cin >> A >> a;
        if ((A >= 'A' && A<'A'+size_x && a>='a' && a< 'a'+size_y)){
            cell &shooted = cells[1+A-'A'][1+a-'a'];
            if(!shooted()){
                ship_numer it = shooted.check();
                //shoot(1+A-'A',1+a-'a');
                if(it != 0){
                    std::cout << "Nice Shot! \n";
                    (ships[it - 1]).bonk();
                    std::cout << ships[it - 1].isdead;
                    finish = true;
                    for(auto it = ships.begin(); it!= ships.end(); it++){
                        if(!(*it).isdead) finish = false; 
                    }
                    return true;
                }
                return false;
            }
            else{
                std::cout << "Choose another cell\n";
            }
        }
        
        
    }
    return false;
}

bool field::loop(){
    // Основной цикл
    while(!finish){
        if(!loop_step()) counter++;
    }

    // Определяем результат игры
    bool win = true;
    for(auto it = ships.begin(); it!= ships.end(); it++)
        if(!(*it).isdead) win = false; 
    if(win) std::cout << "CONGRATULATIONS! \n" << counter << "Turns!\n";
    else std::cout << "DEFEAT \n";
    for(int j = 0; j < size_y+2;j++){
    for(int i = 0; i< size_x + 2; i++){
            get_cell(std::pair(i,j)).dead_of_ship();
    }
    }
    visualisation();
    system("pause");
    return false;
}

void field::ships_dead(ship* s){
    // Уничтожение клеточек вокруг корабля
    auto len = s->size;
    int x = s->x;
    int y = s->y;
    if(s->vertical){
        for(int i = -1; i< len+1; i++){
            get_cell(std::pair(x,y+i)).dead_of_ship();
            cells[x-1][y+i].dead_of_ship();
            cells[x+1][y+i].dead_of_ship();
        }
    }
    else{
        for(int i = -1; i< len+1; i++){
            cells[x+i][y].dead_of_ship();
            cells[x+i][y-1].dead_of_ship();
            cells[x+i][y+1].dead_of_ship();
        }
    }

}

cell& field::get_cell(std::pair<int, int> p){
    // Заготовка, которая могла бы быть использована для рефакторинга
    return cells[p.first][p.second];
}