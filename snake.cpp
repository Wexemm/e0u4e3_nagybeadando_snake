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

// Snake játék osztálya
class SnakeGame {
    public:
        SnakeGame() : dir(RIGHT), grow(false), running(true) {
            SDL_Init(SDL_INIT_VIDEO);  // SDL inicializálás
            // Ablak létrehozása
            window = SDL_CreateWindow("🐍 SDL2 Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
            // Renderer létrehozása
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            // Kígyó inicializálása középre
            snake.push_back({WIDTH / 2 / CELL_SIZE, HEIGHT / 2 / CELL_SIZE});
            spawnApple();  // első alma elhelyezése
        }
    
        ~SnakeGame() {
            // SDL erőforrások felszabadítása
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    
        // Fő játékhurok
    void run() {
        Uint32 last = SDL_GetTicks();  // utolsó frissítés ideje
        while (running) {
            handleInput();  // billentyűkezelés
            Uint32 now = SDL_GetTicks();
            if (now - last > 100) {  // kb. 10 FPS frissítés
                update();    // játékmenet frissítése
                render();    // kirajzolás
                last = now;
            }
        }
    }

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<Point> snake;  // a kígyó teste
    Point apple;               // alma pozíciója
    Direction dir;             // jelenlegi irány
    bool grow;                 // kell-e nőni?
    bool running;              // játék fut-e

    // Billentyűesemények kezelése
    void handleInput() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    // Irányváltás, de nem lehet ellentétes irányba fordulni
                    case SDLK_UP:    if (dir != DOWN) dir = UP; break;
                    case SDLK_DOWN:  if (dir != UP) dir = DOWN; break;
                    case SDLK_LEFT:  if (dir != RIGHT) dir = LEFT; break;
                    case SDLK_RIGHT: if (dir != LEFT) dir = RIGHT; break;
                }
            }
        }
    }

    // Kígyó mozgatása, növekedés, ütközésellenőrzés
    void update() {
        Point head = snake.front();  // aktuális fej
        // Elmozdítás irány alapján
        switch (dir) {
            case UP:    head.y--; break;
            case DOWN:  head.y++; break;
            case LEFT:  head.x--; break;
            case RIGHT: head.x++; break;
        }
