#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define GAME_BOARD_W 13
#define GAME_BOARD_H 8

#define MAX_POSSIBLE_TILE_X_INDEX 5

typedef struct {
    int x, y;
    int active;
} tile_t;

int possible_tile_x_locations[MAX_POSSIBLE_TILE_X_INDEX + 1] = {0, 2, 4, 7, 9, 11};
tile_t tiles[255]; 
int tile_amount = 0;

int a_p = 0, s_p = 0, d_p = 0, j_p = 0, k_p = 0, l_p = 0;



void spawn_new_tile()
{
    int random_x_index = rand() % (MAX_POSSIBLE_TILE_X_INDEX + 1);
    int x = possible_tile_x_locations[random_x_index];
    int y = 0;

    for (int i = 0; i < tile_amount; ++i)
    {
        tile_t *tile = tiles + i;

        if (!tile->active)
        {
            tile->x = x;
            tile->y = y;
            tile->active = 1;
            return;
        }
    }

    tiles[tile_amount].x = x;
    tiles[tile_amount].y = y;
    tiles[tile_amount].active = 1;

    tile_amount++;
}

void update_tiles()
{
    for (int i = 0; i < tile_amount; i++)
    { 
        tile_t *tile = tiles + i;

        if (!tile->active) continue;

        int t_x = tile->x;
        int t_y = tile->y;

        ++tile->y;

        if (tile->y >= GAME_BOARD_H - 1)
        {
            tile->active = 0;
        }

        mvaddch(t_y, t_x, '*');
    }
}

void print_game_board(char game_board[GAME_BOARD_H][GAME_BOARD_W])
{
    for (int i = 0; i < GAME_BOARD_H; ++i)
    {
        printw(game_board[i]);
        printw("\n");
    }
}

int main()
{
    char game_board[GAME_BOARD_H][GAME_BOARD_W] = {
        ". . .  . . .",
        ". . .  . . .",
        ". . .  . . .",
        ". . .  . . .",
        ". . .  . . .",
        ". . .  . . .",
        ". . .  . . .",
        "# # #  # # #"};

    // some initialization

    float refresh_rate = 1;

    initscr();
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();

    curs_set(0);

    srand(time(NULL));

    int user_input;

    while (1)
    {
        //print_game_board(game_board);
        //update_tiles();
        //spawn_new_tile();

        //printw("%d, %d, %d, %d, %d, %d", a_p, s_p, d_p, j_p, k_p, l_p);
        //refresh();

        usleep(1000000 * refresh_rate);

        user_input = getch();
        if (user_input != ERR)
        {
            switch (user_input)
            {
            case 'a':
                a_p = 1;
                break;
            case 's':
                s_p = 1;
                printw("s pressed\n");
                break;
            case 'd':
                d_p = 1;
                break;
            case 'j':
                j_p = 1;
                break;
            case 'k':
                k_p = 1;
                break;
            case 'l':
                l_p = 1;
                break;
            default:
                break;
            }
        }
        else
        {
            a_p = 0, s_p = 0, d_p = 0, j_p = 0, k_p = 0, l_p = 0;
        }
        refresh();
        //erase();
    }
    endwin();

    return 0;
}
