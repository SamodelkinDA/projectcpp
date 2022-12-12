#include "field.h"




int main(){
    int x, y;
    while(!GetAsyncKeyState(VK_TAB)){
        
        std::cout << "Welcome to seabattle \n - TAB ---> quit \n  - ESC ---> leave current game \n";
        std::cout << "Please enter size of field x and y (10 <= x, y <= 26) \n";
        try{
            std::cin >> x >> y;
            if(std::cin.fail() || x < 10 || y < 10 || x > 26 || y > 26){
                
                throw x;
            }
            field Game(x , y);
            Game.loop();
        }
        catch(int){
            std::cout << "Not correct numbers!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    
    return 0;
}

