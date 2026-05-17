#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <cstring>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <cmath> 



class Map {
    private:
	    static const int MAP_HIGHT = 25;
        static const int MAP_WIDTH = 80;
        char map[MAP_HIGHT][MAP_WIDTH];

    public:
        void clear_map() {
            for (int j = 0; j < MAP_HIGHT; j++) {
                for (int i = 0; i < MAP_WIDTH; i++) {
                    map[j][i] = ' ';
                }
                map[j][MAP_WIDTH] = '\0';
            }
        }
        void show_map() {
            for (int j = 0; j < MAP_HIGHT; j++) {
                mvprintw(j, 0, "%s", map[j]);
            }
        }       

};

int main() {
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    Map map;
	map.clear_map();
	map.show_map();

    getch();
    endwin();
	return 0;
}