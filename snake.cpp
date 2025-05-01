// Alap C++ és SDL2 fejlécek
#include <SDL2/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>

// Ablak és rácsméret konstansai
const int WIDTH = 640;
const int HEIGHT = 480;
const int CELL_SIZE = 20; // minden "mező" 20x20 pixel

// Irányokat reprezentáló enum
enum Direction { UP, DOWN, LEFT, RIGHT };

// Egyszerű pont struktúra a kígyótagok és alma helyének tárolásához

struct Point {
    int x, y;
};
