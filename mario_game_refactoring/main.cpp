#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <cmath> 


typedef struct GameObject {
    float x, y;
    float width, heigth;
    float vertSpeed;
    bool IsFly;
    char cType;
    float horizSpeed;
} GameObject;




int score;
int maxLvl;




void clear_map(const int MAP_HIGHT, const int MAP_WIDTH, char **map);
void create_level(int lvl, GameObject& mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level);
void delete_moving(int i, GameObject *&moving, int &movingLength);
int get_key_press();
GameObject *get_new_brick(GameObject *&brick, int &brickLength);
GameObject *get_new_moving(GameObject *&moving, int &movingLength);
void horizon_move_map(float dx, GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength);
void horizon_move_object(GameObject *obj, GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level);
void init_object(GameObject *obj, float xPos, float yPos, float oWidth, float oHeigth, char inType);
bool is_collision(GameObject o1, GameObject o2);
void is_player_dead(GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level);
bool is_position_on_map(int x, int y, const int MAP_HIGHT, const int MAP_WIDTH);
void mario_collision(GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level);
void put_object_on_map(GameObject obj, char **map, const int MAP_HIGHT, const int MAP_WIDTH);
void put_score_on_map(char **map);
void set_object_position(GameObject *obj, float xPos, float yPos);
void show_map(char **map, const int MAP_HIGHT);
void vertical_move_object(GameObject *obj, GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level);



int main() {
	const int MAP_WIDTH = 80;
	const int MAP_HIGHT = 25;
	char** map = new char*[MAP_HIGHT];
	for (int i = 0; i < MAP_HIGHT; i++) {
    	map[i] = new char[MAP_WIDTH + 1];
	}
	GameObject mario;
	GameObject *brick = nullptr;
	int brickLength = 0;
	GameObject *moving = nullptr;
	int movingLength = 0;
	int level = 1;

    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    create_level(level, mario, brick, brickLength, moving, movingLength, level);

    do {
        clear_map(MAP_HIGHT, MAP_WIDTH, map);

        int key = getch();

        if ((mario.IsFly == false) && (key == ' ')) mario.vertSpeed = -1;
        if (key == 'a' || key == 'A') horizon_move_map(1, mario, brick, brickLength, moving, movingLength);
        if (key == 'd' || key == 'D') horizon_move_map(-1, mario, brick, brickLength, moving, movingLength);
        if (key == 27) break;

        if (mario.y > MAP_HIGHT) is_player_dead(mario, brick, brickLength, moving, movingLength, level);

        vertical_move_object(&mario, mario, brick, brickLength, moving, movingLength, level);
        mario_collision(mario, brick, brickLength, moving, movingLength, level);

        for (int i = 0; i < brickLength; i++) {
            put_object_on_map(brick[i], map, MAP_HIGHT, MAP_WIDTH);
        }

        for (int i = 0; i < movingLength; i++) {
            vertical_move_object(moving + i, mario, brick, brickLength, moving, movingLength, level);
            horizon_move_object(moving + i, mario, brick, brickLength, moving, movingLength, level);
            if (moving[i].y > MAP_HIGHT) {
                delete_moving(i, moving, movingLength);
                i--;
                continue;
            }
            put_object_on_map(moving[i], map, MAP_HIGHT, MAP_WIDTH);
        }

        put_object_on_map(mario, map, MAP_HIGHT, MAP_WIDTH);
        put_score_on_map(map);

        move(0, 0);
        show_map(map, MAP_HIGHT);
        refresh();
        napms(10);

    } while (1);

    endwin();
    return 0;
}


void clear_map(const int MAP_HIGHT, const int MAP_WIDTH, char **map) {
    for (int j = 0; j < MAP_HIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            map[j][i] = ' ';
        }
        map[j][MAP_WIDTH] = '\0';
    }
}


void create_level(int lvl, GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level) {
    brickLength = 0;
    if (brick != NULL) {
        free(brick);
        brick = NULL;
    }

    movingLength = 0;
    if (moving != NULL) {
        free(moving);
        moving = NULL;
    }

    init_object(&mario, 39, 10, 3, 3, '@');
    score = 0;

    if (lvl == 1) {
		init_object(get_new_brick(brick, brickLength), 20, 20, 60, 5, '#');
        init_object(get_new_brick(brick, brickLength), 80, 18, 30, 5, '#');
        init_object(get_new_brick(brick, brickLength), 112, 15, 42, 10, '#');

        init_object(get_new_brick(brick, brickLength), 160, 20, 15, 15, '+');

        init_object(get_new_brick(brick, brickLength), 60, 12, 4, 3, '?');
        
        init_object(get_new_moving(moving, movingLength), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, movingLength), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, movingLength), 175, 10, 3, 2, 'o');
    }

    if (lvl == 2) {
        init_object(get_new_brick(brick, brickLength), 0, 22, 80, 3, '#');
        init_object(get_new_brick(brick, brickLength), 60, 19, 20, 3, '#');
        init_object(get_new_brick(brick, brickLength), 83, 21, 5, 3, '#');

        init_object(get_new_brick(brick, brickLength), 90, 21, 5, 3, '+');

        init_object(get_new_brick(brick, brickLength), 20, 15, 4, 3, '?');
        init_object(get_new_brick(brick, brickLength), 60, 10, 4, 3, '?');

        init_object(get_new_moving(moving, movingLength), 25, 19, 3, 2, 'o');
        init_object(get_new_moving(moving, movingLength), 70, 15, 3, 2, 'o');
    }
    
    if (lvl == 3) {
        init_object(get_new_brick(brick, brickLength), 20, 20, 40, 5, '#');
        init_object(get_new_brick(brick, brickLength), 60, 15, 40, 10, '#');
        init_object(get_new_brick(brick, brickLength), 80, 5, 5, 3, '-');
        init_object(get_new_brick(brick, brickLength), 50, 5, 10, 3, '-');

        init_object(get_new_brick(brick, brickLength), 95, 5, 3, 5, '+');

        init_object(get_new_brick(brick, brickLength), 30, 10, 5, 3, '?');
        init_object(get_new_brick(brick, brickLength), 50, 10, 5, 3, '?');
        init_object(get_new_brick(brick, brickLength), 75, 5, 5, 3, '?');
        init_object(get_new_brick(brick, brickLength), 85, 5, 5, 3, '?');
        
        init_object(get_new_moving(moving, movingLength), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, movingLength), 80, 10, 3, 2, 'o');
    }

    maxLvl = 3;
}


void delete_moving(int i, GameObject *&moving, int &movingLength) {
    movingLength--;
    moving[i] = moving[movingLength];
    moving = (GameObject*)realloc(moving, sizeof(*moving) * movingLength);
}


int get_key_press() {
    int ch = getch();
    return ch;
}


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


void horizon_move_map(float dx, GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength) {
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++) {
        if (is_collision(mario, brick[i])) {
            mario.x += dx;
            return;
        }
    }

    mario.x += dx;
    for (int i = 0; i < brickLength; i++) {
        brick[i].x += dx;
    }

    for (int i = 0; i < movingLength; i++) {
        moving[i].x += dx;
    }
}


void horizon_move_object(GameObject *obj, GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level) {
    obj[0].x += obj[0].horizSpeed;
    for (int i = 0; i < brickLength; i++) {
        if (is_collision(obj[0], brick[i])) {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }
    }

    if (obj[0].cType == 'o' || obj[0].cType == '$') {
        GameObject tmp = *obj;
        vertical_move_object(&tmp, mario, brick, brickLength, moving, movingLength, level);
        if (tmp.IsFly == true) {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}


void init_object(GameObject *obj, float xPos, float yPos, float oWidth, float oHeigth, char inType) {
    set_object_position(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).heigth = oHeigth;
    (*obj).vertSpeed = 0;
    (*obj).cType = inType;
    (*obj).horizSpeed = 0.2;
}


bool is_collision(GameObject o1, GameObject o2) {
    return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && 
            ((o1.y + o1.heigth) > o2.y) && (o1.y < (o2.y + o2.heigth)));
}


void is_player_dead(GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level) {
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    refresh();
    create_level(level, mario, brick, brickLength, moving, movingLength, level);
}


bool is_position_on_map(int x, int y, const int MAP_HIGHT, const int MAP_WIDTH) {
    return ((x >= 0) && (x < MAP_WIDTH) 
			&& (y >= 0) && (y < MAP_HIGHT));
}


void mario_collision(GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level) {
    for (int i = 0; i < movingLength; i++) {
        if (is_collision(mario, moving[i])) {
            if (moving[i].cType == 'o') {
                if ((mario.IsFly == true) && (mario.vertSpeed > 0) && 
                    (mario.y + mario.heigth < moving[i].y + moving[i].heigth * 0.5)) {
                    score += 50;
                    delete_moving(i, moving, movingLength);
                    i--;
                    continue;
                } else {
                    is_player_dead(mario, brick, brickLength, moving, movingLength, level);
                }
            }

            if (moving[i].cType == '$') {
                score += 100;
                delete_moving(i, moving, movingLength);
                i--;
                continue;
            }
        }
    }
}


void put_object_on_map(GameObject obj, char **map, const int MAP_HIGHT, const int MAP_WIDTH) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.heigth);

    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (is_position_on_map(i, j, MAP_HIGHT, MAP_WIDTH))
                map[j][i] = obj.cType;
        }
    }
}


void put_score_on_map(char **map) {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++) {
        map[1][i+5] = c[i];
    }
}


void set_object_position(GameObject *obj, float xPos, float yPos) {
    (*obj).x = xPos;
    (*obj).y = yPos;
}


void show_map(char **map, const int MAP_HIGHT) {
    for (int j = 0; j < MAP_HIGHT; j++) {
        mvprintw(j, 0, "%s", map[j]);
    }
}


void vertical_move_object(GameObject *obj, GameObject &mario, GameObject *&brick, int &brickLength, GameObject *&moving, int &movingLength, int level) {
    (*obj).IsFly = true;
    (*obj).vertSpeed += 0.05;
    set_object_position(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);

    for (int i = 0; i < brickLength; i++) {
        if (is_collision(*obj, brick[i])) {
            if (obj[0].vertSpeed > 0) {
                obj[0].IsFly = false;
            }
			
            if ((brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario)) {
                brick[i].cType = '-';
                init_object(get_new_moving(moving, movingLength), brick[i].x, brick[i].y-3, 3, 2, '$');
                moving[movingLength - 1].vertSpeed = -0.7;
            }

            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;

            if (brick[i].cType == '+') {
                level++;
                if (level > maxLvl) level = 1;
                create_level(level, mario, brick, brickLength, moving, movingLength, level);
                refresh();
            }
            break;
        }
    }
}