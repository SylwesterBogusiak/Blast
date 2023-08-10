
#include "types.h"

void draw_player(float scale,Tplayer *ptrplayer,BITMAP* buffer);

void draw_fire(float scale, Tfire fires[MAX_FIRE],BITMAP* buffer, Tplayer *ptrplayer);

void draw_explosion(float scale,Tplayer *ptrplayer,Texplosion explosions[MAX_EXPLOSION],BITMAP* buffer);

void move_player(Tplayer *ptrplayer, int demo);

void move_fires(Tfire fires[MAX_FIRE]);

void collision_fire(TElement *ptrelement,Tfire fires[MAX_FIRE],Texplosion explosions[MAX_EXPLOSION],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int collision_miners_fires (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int collision_enemies_fires (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int collision_player(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int player_control(Tplayer *ptrplayer,Tfire fires[MAX_FIRE],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int explosion(TElement *ptrelement,Texplosion explosions[MAX_EXPLOSION],int tmpx,int tmpy);

int check_bomb(TElement *ptrelement,Texplosion explosions[MAX_EXPLOSION],int tmpx,int tmpy,int STAGE);

int check_bomb_other(TElement *ptrelement,Texplosion explosions[MAX_EXPLOSION],int tmpx,int tmpy,int STAGE);

int check_electriclineH(TElement *ptrelement,int tmpx,int tmpy,int STAGE);

int check_electriclineV(TElement *ptrelement,int tmpx,int tmpy, int STAGE);

int explosion2(int x,int y,int STAGE);

int collision_miners_player (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int collision_miners_element (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int tmpx,int tmpy, int STAGE);

int collision_miners_miner (TElement *ptrelement,int tmpy, int tmpx, int index_miner);

int collision_enemies_player (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

int collision_enemies_element (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int tmpx,int tmpy, int STAGE);

int find_path(Tplayer *player, TElement *ptrelement, BITMAP * buffer, int MazeMap[MAX_STAGE][MAP_Y][MAP_X], int stage, int TARGET_START, int TARGET_END);

void get_visited();

int get_maze(int MazeMap[MAX_STAGE][MAP_Y][MAP_X],int stage);

int dfs(TElement *ptrelement, int row, int col, int TARGET_START, int TARGET_END);


