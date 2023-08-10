
#include  "types.h"

char txt_data_editor[4][65];

int load_level(int sizeMap,int E_Map[MAX_STAGE][MAP_Y][MAP_X], char * path, enum Tdifficulty difficulty_level);

void save_level(int sizeMap,int E_Map[MAX_STAGE][MAP_Y][MAP_X], char * path, enum Tdifficulty difficulty_level);

int editor(BITMAP *buffer,int E_Map[MAX_STAGE][MAP_Y][MAP_X],TElement *ptrelement,int ptrwait);

int center_player(TElement *ptrelement);

void draw_text_ed(BITMAP *buffer);

