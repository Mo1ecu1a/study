#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <cmath> 

#define mapWidth 80
#define mapHeight 25


typedef struct SOobject {
	float x, y;
	float width, heigth;
	float vertSpeed;
	bool IsFly;
	char cType;
	float horizSpeed;
} TOobject;

char map[mapHeight][mapWidth + 1];
TOobject mario;
TOobject *brick = NULL;
int brickLength;

TOobject *moving = NULL;
int movingLength;

int level = 1;
int score;
int maxLvl;


void clear_map() {
    for (int j = 0; j < mapHeight; j++) {
        for (int i = 0; i < mapWidth; i++) {
            map[j][i] = ' ';
        }
        map[j][mapWidth] = '\0';
    }
}


void show_map() {
	for (int j = 0; j < mapHeight; j++) {
		mvprintw(j, 0, "%s", map[j]);
	}
}


void set_object_position(TOobject *obj, float xPos, float yPos) {
	(*obj).x = xPos;
	(*obj).y = yPos;
}

void init_object(TOobject *obj, float xPos, float yPos, float oWidth, float oHeigth, char inType) {
	set_object_position(obj, xPos, yPos);
	(*obj).width = oWidth;
	(*obj).heigth = oHeigth;
	(*obj).vertSpeed = 0;
	(*obj).cType = inType;
	(*obj).horizSpeed = 0.2;
}


bool is_collision(TOobject o1, TOobject o2);
void create_level(int lvl);
TOobject *get_new_moving();


void is_player_dead() {
	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);
	refresh();
	create_level(level);
}


int get_key_press() {
    int ch = getch();
    return ch;
}


void vertical_move_object(TOobject *obj) {
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
				init_object(get_new_moving(), brick[i].x, brick[i].y-3, 3, 2, '$');
				moving[movingLength - 1].vertSpeed = -0.7;
			}

			(*obj).y -= (*obj).vertSpeed;
			(*obj).vertSpeed = 0;

			if (brick[i].cType == '+') {
				level++;
				if (level > maxLvl) level = 1;
				create_level(level);
				refresh();
			}
			break;
		}

	}
}


void delete_moving(int i) {
	movingLength--;
	moving[i] = moving[movingLength];
	moving = (TOobject*)realloc(moving, sizeof(*moving) * movingLength);
}


void mario_collision() {
	for (int i = 0; i < movingLength; i++) {
		if (is_collision(mario, moving[i])) {

			if (moving[i].cType == 'o') {
				if ((mario.IsFly == true) && (mario.vertSpeed > 0) && (mario.y + mario.heigth < moving[i].y + moving[i].heigth * 0.5)) {
					score += 50;
					delete_moving(i);
					i--;
					continue;
				} else {
					is_player_dead();
				}
			}

			if (moving[i].cType == '$') {
				score += 100;
				delete_moving(i);
				i--;
				continue;
			}
		}
	}
}


void horizon_move_object (TOobject *obj) {
	obj[0].x += obj[0].horizSpeed;
	for (int i = 0; i < brickLength; i++) {
		if (is_collision(obj[0], brick[i])) {
			obj[0].x -= obj[0].horizSpeed;
			obj[0].horizSpeed = -obj[0].horizSpeed;
			return;
		}
	}
	if (obj[0].cType == 'o' || obj[0].cType == '$') {
		TOobject tmp = *obj;
		vertical_move_object(&tmp);
		if (tmp.IsFly == true) {
			obj[0].x -= obj[0].horizSpeed;
			obj[0].horizSpeed = -obj[0].horizSpeed;
		}
	}
}

bool is_position_on_map (int x, int y) {
	return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}


void put_object_on_map (TOobject obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iWidth = (int)round(obj.width);
	int iHeight = (int)round(obj.heigth);

	for (int i = ix; i < (ix + iWidth); i++) {
		for (int j = iy; j < (iy + iHeight); j++) {
			if (is_position_on_map(i, j))
				map[j][i] = obj.cType;
		}
	}
}


void horizon_move_map(float dx) {
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


bool is_collision(TOobject o1, TOobject o2) {
	return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.heigth) > o2.y) && (o1.y < (o2.y + o2.heigth)));
}


TOobject *get_new_brick() {
	brickLength++;
	brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
	return brick + brickLength - 1;
}


TOobject *get_new_moving() {
	movingLength++;
	moving = (TOobject*)realloc(moving, sizeof(*moving) * movingLength);
	return moving + movingLength - 1;
}


void put_score_on_map() {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i+5] = c[i];
	}
}


void create_level(int lvl) {
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

	if (lvl == 3) {
		//brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
		init_object(get_new_brick(), 20, 20, 40, 5, '#');
		init_object(get_new_brick(), 30, 10, 5, 3, '?');
		init_object(get_new_brick(), 50, 10, 5, 3, '?');
		init_object(get_new_brick(), 60, 15, 40, 10, '#');
		init_object(get_new_brick(), 75, 5, 5, 3, '?');
		init_object(get_new_brick(), 80, 5, 5, 3, '-');
		init_object(get_new_brick(), 85, 5, 5, 3, '?');
		init_object(get_new_brick(), 50, 5, 10, 3, '-');
		init_object(get_new_brick(), 95, 5, 3, 5, '+');

		
		init_object(get_new_moving(), 25, 10, 3, 2, 'o');
		init_object(get_new_moving(), 80, 10, 3, 2, 'o');
	}

	if (lvl == 2) {
		//brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
		//InitObject(TOobject *obj, float xPos, float yPos, float oWidth, 
		// float oHeigth, char inType)
		init_object(get_new_brick(), 0, 22, 80, 3, '#');
		init_object(get_new_brick(), 60, 19, 20, 3, '#');
		init_object(get_new_brick(), 83, 21, 5, 3, '#');

        init_object(get_new_moving(), 25, 19, 3, 2, 'o');
        init_object(get_new_moving(), 70, 15, 3, 2, 'o');
        
        init_object(get_new_brick(), 20, 15, 4, 3, '?');
        init_object(get_new_brick(), 60, 10, 4, 3, '?');
        init_object(get_new_brick(), 90, 21, 5, 3, '+');
	}
	if (lvl == 1) {
		//brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
		init_object(get_new_brick(), 20, 20, 60, 5, '#');
		init_object(get_new_brick(), 80, 18, 30, 5, '#');
		init_object(get_new_brick(), 112, 15, 42, 10, '#');
		init_object(get_new_brick(), 160, 20, 15, 15, '+');

        init_object(get_new_brick(), 60, 12, 4, 3, '?');
		
		init_object(get_new_moving(), 80, 10, 3, 2, 'o');
		init_object(get_new_moving(), 120, 10, 3, 2, 'o');
		init_object(get_new_moving(), 175, 10, 3, 2, 'o');
	}

	maxLvl = 3;
}



int main() {
	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, TRUE);
	curs_set(0);
	nodelay(stdscr, TRUE);


	create_level(level);

	do {
		clear_map();

		int key = getch();

		if ((mario.IsFly == false) && (key == ' ')) mario.vertSpeed = -1;
		if (key == 'a' || key == 'A') horizon_move_map(1);
		if (key == 'd' || key == 'D') horizon_move_map(-1);
		if (key == 27) break;

		if (mario.y > mapHeight) is_player_dead();

		vertical_move_object(&mario);
		mario_collision();

		for (int i = 0; i < brickLength; i++) {
			put_object_on_map(brick[i]);
		}
		for (int i = 0; i < movingLength; i++) {
			vertical_move_object(moving + i);
			horizon_move_object(moving + i);
			if (moving[i].y > mapHeight) {
				delete_moving(i);
				i--;
				continue;
			}
			put_object_on_map(moving[i]);
		}
		put_object_on_map(mario);
		put_score_on_map();

		move(0, 0);
		show_map();
		refresh();
		napms(10);

	} while (1);

	endwin();
	return 0;
}