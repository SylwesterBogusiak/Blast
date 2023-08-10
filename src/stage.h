
#include "types.h"

void draw_title(BITMAP *buffer,BITMAP *bmp_obj,unsigned char TitleMap[MAP_Y_24][MAP_X_32],int element);

int draw_game_over(BITMAP *buffer,BITMAP *bmp_obj,unsigned char GameOverMap[MAP_Y_24][MAP_X_32],int elemencik,TElement * element, int ptrwait);

int draw_next_stage(BITMAP *buffer,BITMAP *bmp_obj,unsigned char NextStageMap[MAP_Y_24][MAP_X_32],int element, int ptrwait);

void draw_menu(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X],TElement * ptrelement, int ptrwait);

void draw_info(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X], TElement * ptrelement, int ptrwait);

int draw_menu_options(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X],int MUSIC_NUMBER);

void stage_init(int STAGE);

int draw_time_over(BITMAP *buffer, TElement * ptrelement);

int draw_final(BITMAP *buffer,TElement * ptrelement);

int draw_message(BITMAP *buffer,TElement * ptrelement);

int create_Blast_config_file();

