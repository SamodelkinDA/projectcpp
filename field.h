#include "includes.h"

class ship;
class cell;

class field
{

// класс поле. Руководит всем происходящим в партии.
private:
    int counter = 1;
    bool finish = false;
    bool loop_step();
    int size_x, size_y;
    // Размеры поля по х, у. х- горизонталь
    int max_ship = 0;
    // в игре используются корабли: 1х(max_ship), 2х(max_ship-1), ..., (max_ship)х1
    std::vector<ship> ships;
    // вектор кораблей этого поля
    std::vector<std::vector<cell>> cells;
    // Квадратный массив клеток.
    void fill_field();
    // Заполнение поля кораблями.
    bool can_be_placed(int len, int, int, bool);
    friend ship;
    friend cell;
public:
    void ships_dead(ship *);
    cell& get_cell(std::pair<int, int>);

    bool loop();
    // цикл игры 
    cell* fill_cell(int, int, ship_numer);
    // заполнение клетки поля кораблем
    ship_numer shoot(int, int);
    // выстрел игрока
    void visualisation();
    // отбражение на экран. Пока что в терминал
    field(int , int);
    field();
    // конструктор с двумя параметрами
    field(const field &) = delete;
    field(const field &&) = delete;
    field& operator=(const field &) = delete;
    field& operator=(const field &&) = delete;
    // Поле field уникально. Перемещение можно было бы разрешить но зачем?
    ~field();
};

class ship{
private:
    field &game; // ссылка на игровое поле
    int size, x, y; // размер корабля
    std::vector<std::pair<int, int>> cells;
    friend cell;
    friend field;
    bool isdead = false;
    bool vertical;
public:
    void bonk();
    ship(field &, int, int, int, bool, ship_numer);
    /*ship(ship const &)=delete;
    ship(ship const &&)=delete;
    ship& operator=(ship const &)=delete;
    ship& operator=(ship const &&)=delete;
    ~ship(){};*/
};






class cell
{
private:
    bool checked = false;  // возвращает стреляли ли по клетке.
    int x, y; // координаты на поле
    field &game; // поле 
    ship_numer placed_ship; // размещенный корабль
    void fill(ship_numer place_ship);
    // запоминает корабль на этой клетке 

    friend field;
    friend ship;
public:
    void dead_of_ship();
    ship_numer check();
    bool free();
    bool operator()();
    // проверяет стреляли ли по клетке 
    cell(field &, int , int);


    /*cell(ship const &)=delete;
    cell(ship const &&)=delete;
    cell& operator=(cell const &)=delete;
    cell& operator=(cell const &&)=delete;
    ~cell(){};
    */
};


