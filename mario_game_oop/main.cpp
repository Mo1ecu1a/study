#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <cmath> 



class GameObject {
    public:
        float x, y;
        float width, height;
        float vertSpeed;
        bool isFly;
        char cType;
        float horizSpeed;


        void init(float xPos, float yPos, float w, float h, char type) {
            x = xPos; 
            y = yPos;
            width = w; 
            height = h;
            vertSpeed = 0;
            isFly = false;
            cType = type;
            horizSpeed = 0.2;
        }


        void set_position(float xPos, float yPos) {
            x = xPos;
            y = yPos;
        }


        bool is_collision(const GameObject& other) const {
            return ((x + width) > other.x && x < (other.x + other.width) &&
                    (y + height) > other.y && y < (other.y + other.height));
        }
};


class GameMap {
    private:
        int h, w;
        char** map;

    public:
        GameMap(int height, int width) : h(height), w(width) {
            map = new char*[h];

            for (int i = 0; i < h; i++) {
                map[i] = new char[w + 1];
            }
        }


        ~GameMap() {
            for (int i = 0; i < h; i++) {
                delete[] map[i];
            }
            delete[] map;
        }


        void clear() {
            for (int j = 0; j < h; j++) {
                for (int i = 0; i < w; i++) {
                    map[j][i] = ' ';
                }

                map[j][w] = '\0';
            }
        }


        bool is_object_on_map(int x, int y) const {
            return (x >= 0 && x < w && y >= 0 && y < h);
        }


        void put_object_on_map(const GameObject& obj) {
            int ix = (int)round(obj.x);
            int iy = (int)round(obj.y);
            int iw = (int)round(obj.width);
            int ih = (int)round(obj.height);

            for (int i = ix; i < ix + iw; i++) {
                for (int j = iy; j < iy + ih; j++) {
                    if (is_object_on_map(i, j)) {
                        map[j][i] = obj.cType;
                    }
                }
            }
        }


        void put_score_on_map(int score) {
            char buf[30];
            sprintf(buf, "Score: %d", score);
            int len = strlen(buf);
            for (int i = 0; i < len && i + 5 < w; i++) {
                map[1][i + 5] = buf[i];
            }
        }


        void show_map() {
            for (int j = 0; j < h; j++) {
                mvprintw(j, 0, "%s", map[j]);
            }
        }
};


class GameLevel {
    public:
        GameObject mario;
        GameObject* brick;
        int brickLength;
        GameObject* moving;
        int movingLength;
        int level;
        int maxLvl;
        int score;

        GameLevel() : brick(nullptr), brickLength(0), moving(nullptr), movingLength(0), level(1), maxLvl(3), score(0) {}


        ~GameLevel() {
            if (brick) free(brick);
            if (moving) free(moving);
        }


        void create_level(int lvl) {
            level = lvl;
            brickLength = 0;
            if (brick) { 
                free(brick); brick = nullptr; 
            }
            movingLength = 0;
            if (moving) {
                free(moving); moving = nullptr; 
            }

            mario.init(39, 10, 3, 3, '@');
            score = 0;

            auto add_brick = [&](float x, float y, float w, float h, char t) {
                brickLength++;
                brick = (GameObject*)realloc(brick, sizeof(GameObject) * brickLength);
                brick[brickLength - 1].init(x, y, w, h, t);
            };

            auto add_moving = [&](float x, float y, float w, float h, char t) {
                movingLength++;
                moving = (GameObject*)realloc(moving, sizeof(GameObject) * movingLength);
                moving[movingLength - 1].init(x, y, w, h, t);
            };

            
            if (lvl == 1) {
                add_brick(20, 20, 60, 5, '#'); 
                add_brick(80, 18, 30, 5, '#'); 
                add_brick(112, 15, 42, 10, '#');

                add_brick(155, 20, 15, 15, '+'); 

                add_brick(60, 12, 4, 3, '?');

                add_moving(80, 10, 3, 2, 'o'); 
                add_moving(120, 10, 3, 2, 'o'); 
                add_moving(175, 10, 3, 2, 'o');
            } else if (lvl == 2) {
                add_brick(0, 22, 80, 3, '#'); 
                add_brick(60, 19, 20, 3, '#'); 
                add_brick(83, 21, 5, 3, '#');

                add_brick(90, 21, 5, 3, '+'); 

                add_brick(20, 15, 4, 3, '?'); 
                add_brick(60, 10, 4, 3, '?');

                add_moving(25, 19, 3, 2, 'o'); 
                add_moving(70, 15, 3, 2, 'o');
            } else if (lvl == 3) {
                add_brick(20, 20, 40, 5, '#');
                add_brick(60, 15, 40, 10, '#'); 

                add_brick(80, 5, 5, 3, '-');
                add_brick(50, 5, 10, 3, '-'); 

                add_brick(95, 5, 3, 5, '+');

                add_brick(30, 10, 5, 3, '?'); 
                add_brick(50, 10, 5, 3, '?'); 
                add_brick(75, 5, 5, 3, '?'); 
                add_brick(85, 5, 5, 3, '?');

                add_moving(25, 10, 3, 2, 'o'); 
                add_moving(80, 10, 3, 2, 'o');
            }
        }


        void remove_moving(int i) {
            movingLength--;
            moving[i] = moving[movingLength];
            moving = (GameObject*)realloc(moving, sizeof(GameObject) * movingLength);
        }


        void vertical_move(GameObject* obj) {
            obj->isFly = true;
            obj->vertSpeed += 0.05;
            obj->y += obj->vertSpeed;

            for (int i = 0; i < brickLength; i++) {
                if (obj->is_collision(brick[i])) {
                    if (obj->vertSpeed > 0) {
                        obj->isFly = false;
                    }

                    if ((brick[i].cType == '?') && (obj->vertSpeed < 0) && (obj == &mario)) {
                        brick[i].cType = '-';
                        movingLength++;
                        moving = (GameObject*)realloc(moving, sizeof(GameObject) * movingLength);
                        moving[movingLength - 1].init(brick[i].x, brick[i].y - 3, 3, 2, '$');
                        moving[movingLength - 1].vertSpeed = -0.7;
                    }

                    obj->y -= obj->vertSpeed;
                    obj->vertSpeed = 0;
                    if (brick[i].cType == '+' && obj == &mario) {
                        level++;
                        if (level > maxLvl) {
                            level = 1;
                        }
                        create_level(level);
                    }
                    break;
                }
            }
        }


        void horizon_move_map(float dx) {
            mario.x -= dx;
            for (int i = 0; i < brickLength; i++) {
                if (mario.is_collision(brick[i])) {
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


        void horizon_move_object(GameObject* obj) {
            obj->x += obj->horizSpeed;
            for (int i = 0; i < brickLength; i++) {
                if (obj->is_collision(brick[i])) {
                    obj->x -= obj->horizSpeed;
                    obj->horizSpeed = -obj->horizSpeed;
                    return;
                }
            }
            if (obj->cType == 'o' || obj->cType == '$') {
                GameObject tmp = *obj;
                tmp.isFly = true;
                tmp.vertSpeed += 0.05;
                tmp.y += tmp.vertSpeed;
                for (int i = 0; i < brickLength; i++) {
                    if (tmp.is_collision(brick[i])) { 
                        tmp.isFly = false; 
                        break; 
                    }
                }
                if (tmp.isFly == true) {
                    obj->x -= obj->horizSpeed;
                    obj->horizSpeed = -obj->horizSpeed;
                }
            }
        }


        void check_mario_collisions() {
            for (int i = 0; i < movingLength; i++) {
                if (mario.is_collision(moving[i])) {
                    if (moving[i].cType == 'o') {
                        if (mario.isFly && mario.vertSpeed > 0 && 
                            (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)) {
                            score += 50;
                            remove_moving(i);
                            i--;
                            continue;
                        } else {
                            create_level(level);
                        }
                    } else if (moving[i].cType == '$') {
                        score += 100;
                        remove_moving(i);
                        i--;
                        continue;
                    }
                }
            }
        }


        bool is_player_out_of_the_map() const {
            return mario.y > 25;
        }
};





int main() {
    const int MAP_HIGHT = 25;
    const int MAP_WIDTH = 80;

    GameMap gameMap(MAP_HIGHT, MAP_WIDTH);
    GameLevel level;

    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    level.create_level(level.level);

    do {
        gameMap.clear();
        int key = getch();
        if (key == 27) break;

        if (!level.mario.isFly && (key == ' ' || key == 32)) level.mario.vertSpeed = -1;
        if (key == 'a' || key == 'A') level.horizon_move_map(1);
        if (key == 'd' || key == 'D') level.horizon_move_map(-1);

        if (level.is_player_out_of_the_map()) level.create_level(level.level);

        level.vertical_move(&level.mario);
        level.check_mario_collisions();

        for (int i = 0; i < level.brickLength; i++) gameMap.put_object_on_map(level.brick[i]);
        for (int i = 0; i < level.movingLength; i++) {
            level.vertical_move(&level.moving[i]);
            level.horizon_move_object(&level.moving[i]);
            if (level.moving[i].y > MAP_HIGHT) {
                level.remove_moving(i); 
                i--; 
                continue;
            }
            gameMap.put_object_on_map(level.moving[i]);
        }

        gameMap.put_object_on_map(level.mario);
        gameMap.put_score_on_map(level.score);
        gameMap.show_map();
        napms(10);
    } while (1);

    endwin();
    return 0;
}