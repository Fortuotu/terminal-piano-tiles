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

int game_quit = 0;

int possible_tile_x_locations[MAX_POSSIBLE_TILE_X_INDEX + 1] = {0, 2, 4, 7, 9, 11};
tile_t tiles[255]; 
int tile_amount = 0;

int user_input;
int a_p = 0, s_p = 0, d_p = 0, j_p = 0, k_p = 0, l_p = 0;

int lives = 3;
char lives_str[255];

void set_lives(int l)
{
    lives = l;
    sprintf(lives_str, "lives: %d", lives);
}

tile_t *get_tile_at_location(int x, int y)
{
    for (int i = 0; i < tile_amount; i++)
    {
        tile_t *tile = tiles + i;

        if (!tile->active) continue;

        if (tile->x == x && tile->y == y)
        {
            return tile;
        }
    }
    return NULL;
}

void get_user_input()
{
    tile_t *tile;
    while (1)
    {
        user_input = getch();
        if (user_input != ERR)
        {
            switch (user_input)
            {
            case 'q':
                game_quit = 1;
                return;
            case 'a':
                tile = get_tile_at_location(0, GAME_BOARD_H - 1);
                if (tile == NULL)
                {
                    set_lives(lives -1);
                }
                else{
                    tile->active = 0;
                }
                break;
            case 's':
                tile = get_tile_at_location(2, GAME_BOARD_H - 1);
                if (tile == NULL)
                {
                    set_lives(lives -1);
                }
                else{
                    tile->active = 0;
                }
                break;
            case 'd':
                tile = get_tile_at_location(4, GAME_BOARD_H - 1);
                if (tile == NULL)
                {
                    set_lives(lives -1);
                }
                else{
                    tile->active = 0;
                }
                break;
            case 'j':
                tile = get_tile_at_location(7, GAME_BOARD_H - 1);
                if (tile == NULL)
                {
                    set_lives(lives -1);
                }
                else{
                    tile->active = 0;
                }
                break;
            case 'k':
                tile = get_tile_at_location(9, GAME_BOARD_H - 1);
                if (tile == NULL)
                {
                    set_lives(lives -1);
                }
                else{
                    tile->active = 0;
                }
                k_p = 1;
                break;
            case 'l':
                tile = get_tile_at_location(11, GAME_BOARD_H - 1);
                if (tile == NULL)
                {
                    set_lives(lives -1);
                }
                else{
                    tile->active = 0;
                }
                break;
            default:
                break;
            }
        }
        else
        {
            a_p = 0, s_p = 0, d_p = 0, j_p = 0, k_p = 0, l_p = 0;
        }
    }
}

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

        if (tile->y >= GAME_BOARD_H)
        {
            tile->active = 0;
            set_lives(lives - 1);
            continue;
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

int main(int argc, char **argv)
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
    int refresh_rate = 1000000;
    if (argc >= 1)
    {
        refresh_rate = atoi(argv[1]);
    }

    initscr();
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();

    curs_set(0);

    srand(time(NULL));
    
    pthread_t input_thread_id;
    pthread_create(&input_thread_id, NULL, get_user_input, NULL);

    set_lives(3);

    while (!game_quit)
    {
        print_game_board(game_board);
        update_tiles();
        spawn_new_tile();
        mvaddstr(GAME_BOARD_H, 0, lives_str);

        usleep(refresh_rate);
        
        erase();
    }
    pthread_join(input_thread_id, NULL);
    endwin();

    return 0;
}
