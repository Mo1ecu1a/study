#include <cmath> 
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define mapWidth 80
#define mapHeight 25


typedef struct GameObject {
	float x, y;
	float width, heigth;
	float vertSpeed;
	bool IsFly;
	char cType;
	float horizSpeed;
}

bool IsCollision(TOobject o1, TOobject o2);
void CreateLevel(int lvl);
TOobject *GetNewMoving();



TOobject *add_brick(GameState *gs);
TOobject *add_moving_object(GameState *gs);
bool check_collision(TOobject o1, TOobject o2);
void clear_map(GameState *gs);
void create_level(GameState *gs, int lvl);
void delete_moving_object(GameState *gs, int i);
int get_key_press(void);
void handle_mario_collision(GameState *gs);
void init_object(TOobject *obj, float xPos, float yPos, float oWidth, float oHeigth, char inType);
void is_player_dead(GameState *gs);
bool is_position_valid(int x, int y);
void move_horizontally(GameState *gs, TOobject *obj);
void move_map_horizontally(GameState *gs, float dx);
void move_vertically(GameState *gs, TOobject *obj);
void put_object_on_map(GameState *gs, TOobject obj);
void put_score_on_map(GameState *gs);
void set_object_position(TOobject *obj, float xPos, float yPos);
void show_map(GameState *gs);


int main() {
	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, TRUE);
	curs_set(0);
	nodelay(stdscr, TRUE);


    char map[mapHeight][mapWidth + 1];
    TOobject mario;
    TOobject *brick = NULL;
    int brickLength;

    TOobject *moving = NULL;
    int movingLength;

    int level = 1;
    int score;
    int maxLvl;


	CreateLevel(level);

	do {
		ClearMap();

		int key = getch();

		if ((mario.IsFly == false) && (key == ' ')) mario.vertSpeed = -1;
		if (key == 'a' || key == 'A') HorizonMoveMap(1);
		if (key == 'd' || key == 'D') HorizonMoveMap(-1);
		if (key == 27) break;

		if (mario.y > mapHeight) PlayerDead();

		VerMoveObject(&mario);
		MarioCollision();

		for (int i = 0; i < brickLength; i++) {
			PutObjectOnMap(brick[i]);
		}
		for (int i = 0; i < movingLength; i++) {
			VerMoveObject(moving + i);
			HorizonMoveObject(moving + i);
			if (moving[i].y > mapHeight) {
				DeleteMoving(i);
				i--;
				continue;
			}
			PutObjectOnMap(moving[i]);
		}
		PutObjectOnMap(mario);
		PutScoreOnMap();

		move(0, 0);
		ShowMap();
		refresh();
		napms(10);

	} while (1);

	endwin();
	return 0;
}



TOobject *add_brick() {
	brickLength++;
	brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
	return brick + brickLength - 1;
}


TOobject *add_moving_object() {
	movingLength++;
	moving = (TOobject*)realloc(moving, sizeof(*moving) * movingLength);
	return moving + movingLength - 1;
}



bool check_collision(TOobject o1, TOobject o2) {
	return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.heigth) > o2.y) && (o1.y < (o2.y + o2.heigth)));
}


void clear_map() {
    for (int j = 0; j < mapHeight; j++) {
        for (int i = 0; i < mapWidth; i++) {
            map[j][i] = ' ';
        }
        map[j][mapWidth] = '\0';
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

	InitObject(&mario, 39, 10, 3, 3, '@');
	score = 0;

	if (lvl == 3) {
		//brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
		InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetNewBrick(), 30, 10, 5, 3, '?');
		InitObject(GetNewBrick(), 50, 10, 5, 3, '?');
		InitObject(GetNewBrick(), 60, 15, 40, 10, '#');
		InitObject(GetNewBrick(), 75, 5, 5, 3, '?');
		InitObject(GetNewBrick(), 80, 5, 5, 3, '-');
		InitObject(GetNewBrick(), 85, 5, 5, 3, '?');
		InitObject(GetNewBrick(), 50, 5, 10, 3, '-');
		InitObject(GetNewBrick(), 95, 5, 3, 5, '+');

		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
	}

	if (lvl == 2) {
		//brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
		//InitObject(TOobject *obj, float xPos, float yPos, float oWidth, 
		// float oHeigth, char inType)
		InitObject(GetNewBrick(), 0, 22, 80, 3, '#');
		InitObject(GetNewBrick(), 60, 19, 20, 3, '#');
		InitObject(GetNewBrick(), 83, 21, 5, 3, '#');

        InitObject(GetNewMoving(), 25, 19, 3, 2, 'o');
        InitObject(GetNewMoving(), 70, 15, 3, 2, 'o');
        
        InitObject(GetNewBrick(), 20, 15, 4, 3, '?');
        InitObject(GetNewBrick(), 60, 10, 4, 3, '?');
        InitObject(GetNewBrick(), 90, 21, 5, 3, '+');
	}
	if (lvl == 1) {
		//brick = (TOobject*)realloc(brick, sizeof(*brick) * brickLength);
		InitObject(GetNewBrick(), 20, 20, 60, 5, '#');
		InitObject(GetNewBrick(), 80, 18, 30, 5, '#');
		InitObject(GetNewBrick(), 112, 15, 42, 10, '#');
		InitObject(GetNewBrick(), 160, 20, 15, 15, '+');

        InitObject(GetNewBrick(), 60, 12, 4, 3, '?');
		
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
	}

	maxLvl = 3;
}


void delete_moving_object(int i) {
	movingLength--;
	moving[i] = moving[movingLength];
	moving = (TOobject*)realloc(moving, sizeof(*moving) * movingLength);
}

int get_key_press() {
    int ch = getch();
    return ch;
}


void handle_mario_collision() {
	for (int i = 0; i < movingLength; i++) {
		if (IsCollision(mario, moving[i])) {

			if (moving[i].cType == 'o') {
				if ((mario.IsFly == true) && (mario.vertSpeed > 0) && (mario.y + mario.heigth < moving[i].y + moving[i].heigth * 0.5)) {
					score += 50;
					DeleteMoving(i);
					i--;
					continue;
				} else {
					PlayerDead();
				}
			}

			if (moving[i].cType == '$') {
				score += 100;
				DeleteMoving(i);
				i--;
				continue;
			}
		}
	}
}






void init_object(TOobject *obj, float xPos, float yPos, float oWidth, float oHeigth, char inType) {
	SetObjectPos(obj, xPos, yPos);
	(*obj).width = oWidth;
	(*obj).heigth = oHeigth;
	(*obj).vertSpeed = 0;
	(*obj).cType = inType;
	(*obj).horizSpeed = 0.2;
}


void is_player_dead() {
	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);
	refresh();
	CreateLevel(level);
}


bool is_position_valid(int x, int y) {
	return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}


void move_horizontally(TOobject *obj) {
	obj[0].x += obj[0].horizSpeed;
	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(obj[0], brick[i])) {
			obj[0].x -= obj[0].horizSpeed;
			obj[0].horizSpeed = -obj[0].horizSpeed;
			return;
		}
	}
	if (obj[0].cType == 'o' || obj[0].cType == '$') {
		TOobject tmp = *obj;
		VerMoveObject(&tmp);
		if (tmp.IsFly == true) {
			obj[0].x -= obj[0].horizSpeed;
			obj[0].horizSpeed = -obj[0].horizSpeed;
		}
	}
}

void move_map_horizontally(float dx) {
	mario.x -= dx;
	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(mario, brick[i])) {
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


void move_vertically(TOobject *obj) {
	(*obj).IsFly = true;
	(*obj).vertSpeed += 0.05;
	SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);

	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(*obj, brick[i])) {
			if (obj[0].vertSpeed > 0) {
				obj[0].IsFly = false;
			}

			if ((brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario)) {
				brick[i].cType = '-';
				InitObject(GetNewMoving(), brick[i].x, brick[i].y-3, 3, 2, '$');
				moving[movingLength - 1].vertSpeed = -0.7;
			}

			(*obj).y -= (*obj).vertSpeed;
			(*obj).vertSpeed = 0;

			if (brick[i].cType == '+') {
				level++;
				if (level > maxLvl) level = 1;
				CreateLevel(level);
				refresh();
			}
			break;
		}

	}
}





void put_object_on_map(TOobject obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iWidth = (int)round(obj.width);
	int iHeight = (int)round(obj.heigth);

	for (int i = ix; i < (ix + iWidth); i++) {
		for (int j = iy; j < (iy + iHeight); j++) {
			if (IsPosInMap(i, j))
				map[j][i] = obj.cType;
		}
	}
}


void put_score_on_map() {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i+5] = c[i];
	}
}



void set_object_position(TOobject *obj, float xPos, float yPos) {
	(*obj).x = xPos;
	(*obj).y = yPos;
}


void show_map() {
	for (int j = 0; j < mapHeight; j++) {
		mvprintw(j, 0, "%s", map[j]);
	}
}