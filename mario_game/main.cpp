#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25


typedef struct SOobject {
	float x, y;
	float width, heigth;
	float vertSpeed;
	BOOL IsFly;
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




void ClearMap() {
	for (int i = 0; i < mapWidth; i++) {
		map[0][i] = ' ';
	}
	map[0][mapWidth] = '\0'
	for (int j = 1; j < mapHeight; j++) {
		sprintf(map[j], map[0]);
	}
}

void ShowMap() {
	map[mapHeight - 1][mapWidth - 1] = '\0';
	for (int j = 0; j < mapHeight; j++) {
		printf("%s", map[j]);
	}
}


void SetObjectPos(TOobject *obj, float xPos, float yPos) {
	(*obj).x = xPos;
	(*obj).y = yPos;
}

void InitObject(TOobject *obj, float xPos, float yPos, float oWidth, float oHeigth, char inType) {
	SetObjectPos(obj, xPos, yPos);
	(*obj).width = oWidth;
	(*obj).heigth = oHeigth;
	(*obj).vertSpeed = 0;
	(*obj).cType = inType;
	(*obj).horizSpeed = 0.2;
}





void PlayerDead() {
	system("color 4F");
	Sleep(500);
	CreateLevel(level);
}







BOOL IsCollision(TOobject o1, TOobject o2);
void CreateLevel(int lvl);
TOobject *GetMewMoving();

void VerMoveObject(TOobject *obj) {
	(*obj).IsFly = TRUE;
	(*obj).vertSpeed += 0.05;
	SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);

	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(*obj, brick[i])) {
			if (obj[0].vertSpeed > 0) {
				obj[0].IsFly = FALSE;
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

				system("color 2F");
				Sleep(500);
				CreateLevel(level);
			}
			break;
		}

	}
}




void DeleteMoving(int i) {
	movingLength--;
	moving[i] = moving[movingLength];
	moving = realloc(moving, sizeof(*moving) * movingLength);
}



void MarioCollision() {
	for (int i = 0; i < movingLength; i++) {
		if (IsCollision(mario, moving[i])) {

			if (moving[i].cType == 'o') {
				if ((mario.IsFly == TRUE) && (mario.vertSpeed > 0) && (mario.y + mario.heigth < moving[i].y + moving[i].heigth * 0.5)) {
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



void HorizonMoveObject(TOobject *obj) {
	obj[0].x += obj[0].horizSpeed;
	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(obj[0], brick[i])) {
			obj[0].x -= obj[0].horizSpeed;
			obj[0].horizSpeed = -obj[0].horizSpeed;
			return;
		}
	}
	if (obj[0].cType == 'o') {
		TOobject tmp = *obj;
		VerMoveObject(&tmp);
		if (tmp.IsFly == TRUE) {
			obj[0].x -= obj[0].horizSpeed;
			obj[0].horizSpeed = -obj[0].horizSpeed;
		}
	}
}





BOOL IsPosInMap(int x, int y) {
	returb ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}


void PutObjectOnMap (TOobject obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iWidth = (int)round(obj.width);
	int iHeight = (int)round(obj.heigth);

	for (int i = ix; i < (ix + iWidth); i++) {
		for (int j = iy; j < (iy + iHeight); j++) {
			if (IsPosInMap(i, j))
				map[iy][ix] = obj.cType;
		}
	}
}


void setCur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_NANDLE), coord);
}



void HorizonMoveMap(float dx) {
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



BOOL IsCollision(TOobject o1, TOobject o2) {
	return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.heigth) > o2.y) && (o1.y < (o2.y + o2.heigth)));
}




TOobject *GetMewBrick() {
	brickLength++;
	brick = realloc(brick, sizeof(*brick) * brickLength);
	return brick + brickLength - 1;
}


TOobject *GetMewMoving() {
	movingLength++;
	moving = realloc(moving, sizeof(*moving) * movingLength);
	return moving + movingLength - 1;
}




void PutScoreOnMap() {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i+5] = c[i];
	}
}






void CreateLevel(int lvl) {
	system("color 9F");

	brickLength = 0;
	brick = realloc(brick, 0);
	movingLength = 0;
	moving = realloc(moving, 0);

	InitObject(&mario, 39, 10, 3, 3, '@');
	score = 0;

	if (lvl == 1) {
		brick = realloc(brick, sizeof(*brick) * brickLength);
		InitObject(GetMewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetMewBrick(), 30, 10, 5, 3, '?');
		InitObject(GetMewBrick(), 50, 10, 5, 3, '?');
		InitObject(GetMewBrick(), 60, 15, 40, 10, '#');
		InitObject(GetMewBrick(), 70, 5, 10, 3, '-');
		InitObject(GetMewBrick(), 75, 5, 5, 3, '?');
		InitObject(GetMewBrick(), 80, 5, 5, 3, '-');
		InitObject(GetMewBrick(), 85, 5, 5, 3, '?');
		InitObject(GetMewBrick(), 50, 5, 10, 3, '-');
		InitObject(GetMewBrick(), 100, 20, 20, 5, '#');
		InitObject(GetMewBrick(), 120, 15, 10, 10, '#');
		InitObject(GetMewBrick(), 150, 20, 40, 5, '#');
		InitObject(GetMewBrick(), 210, 15, 10, 10, '+');

		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
	}

	if (lvl == 2) {
		brick = realloc(brick, sizeof(*brick) * brickLength);
		InitObject(GetMewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetMewBrick(), 60, 15, 10, 10, '#');
		InitObject(GetMewBrick(), 80, 20, 20, 5, '#');
		InitObject(GetMewBrick(), 120, 15, 10, 10, '#');
		InitObject(GetMewBrick(), 150, 20, 40, 5, '#');
		InitObject(GetMewBrick(), 210, 15, 10, 10, '+');

		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 65, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
	}
	if (lvl == 3) {
		brick = realloc(brick, sizeof(*brick) * brickLength);
		InitObject(GetMewBrick(), 20, 20, 40, 5, '#');
		InitObject(GetMewBrick(), 80, 20, 15, 5, '#');
		InitObject(GetMewBrick(), 120, 15, 15, 10, '#');
		InitObject(GetMewBrick(), 160, 10, 15, 15, '+');
		
		InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 65, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
		InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
	}

	maxLvl = 3;
}



int main() {
	CreateLevel();

	do {
		ClearMap(level);

		if ((mario.IsFly == FALSE) && (GetKeyState(VK_ESCAPE) < 0)) mario.vertSpeed = -1;
		if (GetKeyState('A') < 0) HorizonMoveMap(1);
		if (GetKeyState('D') < 0) HorizonMoveMap(-1);


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

		setCur(0, 0);
		ShowMap();
		Sleep(10);

	}
	while (GetKeyState (VK_ESCAPE) >= 0);
	return 0;`
}