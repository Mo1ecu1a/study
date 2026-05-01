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
} TOobject;

char map[mapHeight][mapWidth + 1];
TOobject mario;
TOobject *brick = NULL;
int brickLength;
int level = 1;

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
}

BOOL IsCollision(TOobject o1, TOobject o2);
void CreateLevel(int lvl);

void VerMoveObject (TOobject *obj) {
	(*obj).IsFly = TRUE;
	(*obj).vertSpeed += 0.05;
	SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
	for (int i = 0; i < brickLength; i++) {
		if (IsCollision(*obj, brick[0])) {
			(*obj).y -= (*obj).vertSpeed;
			(*obj).vertSpeed = 0;
			(*obj).IsFly = FALSE;
			if (brick[i].cType == '+') {
				level++;
				if (level > 2) level = 1;
				CreateLevel(level);
				Sleep(1000);
			}
			break;
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
}



BOOL IsCollision(TOobject o1, TOobject o2) {
	return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.heigth) > o2.y) && (o1.y < (o2.y + o2.heigth)));
}



void CreateLevel(int lvl) {
	InitObject(&mario, 39, 10, 3, 3, '@');

	if (lvl == 1) {
		brickLength = 6;
		brick = realloc(brick, sizeof(*brick) * brickLength);
		InitObject(brick+0, 20, 20, 40, 5, '@');
		InitObject(brick+1, 60, 15, 10, 10, '@');
		InitObject(brick+2, 80, 20, 20, 5, '@');
		InitObject(brick+3, 120, 15, 10, 10, '@');
		InitObject(brick+4, 150, 20, 40, 5, '@');
		InitObject(brick+5, 210, 15, 10, 10, '+');
	}
	if (lvl == 2) {
		brickLength = 4;
		brick = realloc(brick, sizeof(*brick) * brickLength);
		InitObject(brick+0, 20, 20, 40, 5, '@');
		InitObject(brick+1, 80, 20, 15, 5, '@');
		InitObject(brick+2, 120, 15, 15, 10, '@');
		InitObject(brick+3, 160, 10, 15, 15, '+');
	}
}



int main() {
	CreateLevel();
	system("color 9F");

	do {
		ClearMap(level);

		if ((mario.IsFly == FALSE) && (GetKeyState(VK_ESCAPE) < 0)) mario.vertSpeed = -1;
		if (GetKeyState('A') < 0) HorizonMoveMap(1);
		if (GetKeyState('D') < 0) HorizonMoveMap(-1);


		if (mario.y > mapHeight) CreateLevel(level);

		VerMoveObject(&mario);
		for (int i = 0; i < brickLength; i++)
		PutObjectOnMap(brick[i]);
		PutObjectOnMap(mario);

		setCur(0, 0);
		ShowMap();
		Sleep(10);

	}
	while (GetKeyState (VK_ESCAPE) >= 0);
	return 0;`
}