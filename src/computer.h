
#include "types.h"

int move_miner(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

void draw_miner(float scale,TElement *ptrelement,BITMAP* buffer);

void move_miner_around(TElement * ptrelement, int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int move_enemy(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

void draw_enemy(float scale,TElement *ptrelement,BITMAP* buffer);

void move_enemy_around(TElement * ptrelement, int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

