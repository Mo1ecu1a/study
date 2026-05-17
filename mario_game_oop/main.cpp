#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <cstring>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <cmath> 


class GameObject {
    public:
        float x, y;
        float width, height;
        float vertSpeed;
        bool IsFly;
        char cType;
        float horizSpeed;

        GameObject *get_new_brick(GameObject *&brick, int &brickLength) {
            brickLength++;
            brick = (GameObject*)realloc(brick, sizeof(*brick) * brickLength);
            return brick + brickLength - 1;
        }
        GameObject *get_new_moving(GameObject *&moving, int &movingLength) {
            movingLength++;
            moving = (GameObject*)realloc(moving, sizeof(*moving) * movingLength);
            return moving + movingLength - 1;
        }
        void init_object(GameObject *obj, float xPos, float yPos, float oWidth, float oHeigth, char inType) {
            set_object_position(obj, xPos, yPos);
            width = oWidth;
            height = oHeigth;
            vertSpeed = 0;
            cType = inType;
            horizSpeed = 0.2;
        }
        void set_object_position(GameObject *obj, float xPos, float yPos) {
            x = xPos;
            y = yPos;
        }
};


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
        void put_object_on_map(const GameObject &obj) {
            int ix = (int)round(obj.x);
            int iy = (int)round(obj.y);
            int iwidth = (int)round(obj.width);
            int iheight = (int)round(obj.height);

            for (int i = ix; i < (ix + iwidth); i++) {
                for (int j = iy; j < (iy + iheight); j++) {
                    if (is_position_on_map(i, j))
                        map[j][i] = obj.cType;
                }
            }
        }    
        void put_score_on_map(int &score) {
            char c[30];
            sprintf(c, "Score: %d", score);
            int len = strlen(c);
            for (int i = 0; i < len; i++) {
                map[1][i+5] = c[i];
            }
        }
        bool is_position_on_map(int x, int y) {
            return ((x >= 0) && (x < MAP_WIDTH) 
                    && (y >= 0) && (y < MAP_HIGHT));
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