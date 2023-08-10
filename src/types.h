
#ifndef		TYPY_H
#define		TYPY_H

#include <stdio.h>                                                  // for text and binary files
#include "allegro.h"


#define BLACK makecol(0,0,0)
#define GREY makecol(128,128,128)
#define WHITE makecol(255,255,255)
#define CLEAR makecol(255,0,255)

#define textout(a,b,c,d,e,f) textout_ex(a,b,c,d,e,f,makecol(0,0,0))    // macro

/* define only one option below */
#define MiniBlast
//#define MidiBlast
//#define MaxiBlast

#ifdef MiniBlast
//MiniBlast    5 minutes game
#define NUMBER_OF_SCREENS_X 1
#define NUMBER_OF_SCREENS_Y 1
#define MAX_STAGE 5

#endif // MiniBlast

#ifdef MidiBlast
///MidiBlast    15 minutes game
#define NUMBER_OF_SCREENS_X 2
#define NUMBER_OF_SCREENS_Y 2
#define MAX_STAGE 10

#endif // MidiBlast

#ifdef MaxiBlast
///MaxiBlast    60 minutes game
#define NUMBER_OF_SCREENS_X 3 //1
#define NUMBER_OF_SCREENS_Y 3 //2
#define MAX_STAGE 15

#endif // MiniBlast


#define MAP_X 32*NUMBER_OF_SCREENS_X        // stage size x (elements maze)
#define MAP_Y 24*NUMBER_OF_SCREENS_Y        // stage size y (elements maze)

#define MAP_X_32 32                         // for draw title game over etc
#define MAP_Y_24 24



extern int SCREEN_w; //320
extern int SCREEN_h; //240
extern int MAX_X; //10                             // elements size
extern int MAX_Y; // 10


#define SCALE 1                             // 1 is OK for Miner
#define DEGREES(x) ((x)/360.0*0xFFFFFF) //for rotation of Miner


#define MAX_ENTRIES 10                  // number of entries in highscore

// text fields on the game screen
#define FIELD_STAGE 0
#define FIELD_SHIPS 1
#define FIELD_AMMO 2
#define FIELD_LASER 3
#define FIELD_POINTS 4                   // position in table txt_dane
#define FIELD_TIMER 5
#define FIELD_STAR 6


#define MAX_LETTERS 12                  // lnumber of characters in HIGH SCORE line
#define MAX_DIGITS_SCORES 6             // number of digits for highscore entry = 5+terminator

#define FIELD_STAGE_NR 10               // field stage in editor
#define MAX_POS_MENU 5

//////////////////////////////////////////////////////////////// Elements on stage: blocks, walls, quads etc.


 typedef struct TBlock{
int anim_count;
BITMAP *bmp;
//SAMPLE *spl;
} TBlock;

 typedef struct TWall{
int anim_count;
BITMAP *bmp_wall;
//SAMPLE *spl;
} TWall;

 typedef struct TQuad{
int anim_count;
BITMAP *bmp_quad;
//SAMPLE *spl;
} TQuad;

 typedef struct TSlantL{
int anim_count;
BITMAP *bmp_slantL;
//SAMPLE *spl;
} TSlantL;

 typedef struct TSlantR{
int anim_count;
BITMAP *bmp_slantR;
//SAMPLE *spl;
} TSlantR;

typedef struct TBomb{
int anim_count;
BITMAP *bitmap;
//SAMPLE *spl;
} TBomb;

typedef struct TWeaponRecharger{
int anim_count;
BITMAP *bmp_weaponrecharger;
//SAMPLE *spl;
} TWeaponRecharger;


#define MAX_ANIM_ELECTRIC 4

typedef struct TElectricLine{
int anim_count;
BITMAP *bmp;
BITMAP *bmptab[MAX_ANIM_ELECTRIC];
//SAMPLE *spl;
} TElectricLine;

typedef struct TWallSwitchOFF{
int anim_count;
BITMAP *bmp;
//SAMPLE *spl;
} TWallSwitchOFF;


//****************
#define MAX_ANIM_STARS 6
#define MAX_STAR 1000                       /// 24x32 = 768 elements on small stage size

typedef struct TStar{
int anim_count;
BITMAP *bmp_stars;
BITMAP *bmptab[MAX_ANIM_STARS];
int x;
int y;
//SAMPLE *spl;
} TStar;

#define MAX_FIRE 80
#define MAX_ANIM_FIRES 4
typedef struct {
int direction;                              // direction of ammo or laser: 0 = up, 1 = right, 2 = down, 3 = left
int step;                                   // step for ammo
int step2;                                  // step for laser
int x;                                      // pozsition y
int y;                                      // position x
int type_of_weapon;                         // 0 = ammo, 1 = laser
int wait;                                   // 0 = on move, 1 = idle.
BITMAP *bmp;
BITMAP *bmptab[MAX_ANIM_FIRES];
//SAMPLE *spl;
}Tfire ;


#define MAX_EXPLOSION 300
#define MAX_ANIM_EXPLOSION_X 8
#define MAX_ANIM_EXPLOSION_Y 4

  typedef struct
 {

 int x;                                     //position
 int y;
 int animate;                               // 1 = animate, 0 = idle
 char anim_count_x;
 char anim_count_y;                         // frames of animation
 BITMAP * bmp;                              // bitmab image
 //SAMPLE *spl;
 } Texplosion;

//****************
#define MAX_COMP 1000
#define MAX_ANIM_COMP 4
#define MAX_ENEMIES 1000

//****************
typedef  struct Tplayer
{
int x  ;                                    // pozycja x playera
int y  ;                                    // pozycja y playera
int id;                                     // index dla minera
int divider;                                // for miner move_around
int mine;                                   // for miner to set mines
int shift_y;                                // for doubled or tripled stage size
int shift_x;
int random_shot;                            // for demo_game
int step;                                   // step for move
int direction ;                             // direction of player or enemy or miner - 0 = up, 1 = right  2 = down 3 = left
int section ;                               // section to move
int angle ;                                 // only for miner
int field ;                                 // free field around player - not in use
int random_direction;                       // for miner
int change_direction;                       // used by player controlled by follow_patch in demo mode
int find_object;                            // find patch to target/object
int follow_object;                          // follow patch to object
int hit;                                    // for draw miner
int wait;                                   // for sync with timer
int type_of_weapon;                         // 0 = ammo, 1 = laser
int anim_count;                             // for animation of miner
int my_timer_sec;
int my_timer_min;
int my_timer_hrs;
int ships;
int ammo;
int laser;
int points;
int stars_left;
int total_score;
char total_score_buffer[MAX_DIGITS_SCORES];

BITMAP *bmp ;                               //full bitmap with frames
BITMAP *bmptab[MAX_ANIM_COMP];              //bitamps from frames of sprite

Tfire fires[MAX_FIRE];
Texplosion explosions[MAX_EXPLOSION];

} Tplayer;

typedef  struct {
    int x;
    int y;

 int source_y;
 int source_x;
} Teditor;

typedef struct TCamera

{
    int x_left;
    int x_right;
    int y_top;
    int y_bottom;
} TCamera;

extern TCamera camera;


// for maze dfs algorithm
extern int CRUMB;
extern int crumb;
extern int wall;                                       // for player in demo game mode
extern int was_here;                                   // for player in demo game mode



// definitions for Allegro GRABBER software [.dat files]
#define FONT_NUMBER_DAT 1 // 1 mala font 8x8 w plku font.dat   0 to duza font 29 px
// GRABBER FILES LIST IN DAT COMPRESSED FILE
#define MAX_ELEMENTS 18

#define BACKGROUND 0
#define BLOCK 1                                 // to destroy
#define BOMB 2                                  // explosive box
#define EXPLOSIONS 3                            // not an element
#define WEAPONRECHARGER 4                       // load ammo and laser
#define MINER 5                                 //
#define PLAYER 6
#define AMMO 7                                  // ammo - weapon for player
#define QUAD 8                                  // when there is a hit, the quad is shifting
#define SLANTL 9                                // when there is a hit, the bullets are deflected
#define SLANTR 10                               // when there is a hit, the bullets are deflected
#define STAR 11                                 // to destroy by ammo
#define WALL 12                                 // not to destroy
#define ELECTRICLINEV 13                        // electric line to shock player
#define ELECTRICLINEH 14                        // electric line to shock player
#define WALLOFFV 15                             // when there is a hit, it turn off electric line
#define WALLOFFH 16                             // when there is a hit, it turn off electric line
#define SLANTLROTATE 17                         // rotated slant
#define SLANTRROTATE 18                         // rotated slant
#define ENEMY 19                                // enemy ship - aka ufo
#define MONO_PAL 20
#define COLOR_PAL 21
//#define COMPUTER_PATH MINER+100               // ufo_path
#define COMPUTER_MINE MINER+101                 // mine is set

#define MARGIN_RIGHT 0
#define MARGIN_LEFT 0
#define MARGIN_TOP 0
#define MARGIN_BOTTOM 0

// all alements in one struct

typedef struct TElement
{

TBlock block;
TWall wall;
TQuad quad;
TStar stars[MAX_STAR];
TSlantL slantL;
TSlantR slantR;
TBomb bomb;
Tplayer player;
Tfire fires[MAX_FIRE];
Tplayer miner[MAX_COMP];
Tplayer enemy[MAX_ENEMIES];
TWeaponRecharger weaponrecharger;
TElectricLine electriclineH;
TElectricLine electriclineV;
TWallSwitchOFF switchOFFH;
TWallSwitchOFF switchOFFV;
TSlantL slantLrotate;
TSlantR slantRrotate;
Teditor editor;

int startscroll;                                // for draw_info
int is_cleaned;                                 // new_entry_read
int uTimer_menu;
int uTimer_hall_of_fame;
int uTimer_info;
int uTimer_play_demo;
int target_row;                                 // for player target
int target_col;

} TElement;

#ifdef jgmod

#define MAX_MOD 9                               // 9 titles in an array from 0 - 8

extern JGMOD *mod[MAX_MOD];

#endif // jgmod

extern FONT *font;
extern FONT *font_menu;                                // 0 from file font.dat
extern PALETTE *mono_palette;                          // from file blast_img.dat
extern PALLETE *the_pallete;
extern PALLETE *color_palette;
extern PALLETE mono2_pallete;
extern PALLETE title_pallete;

enum menu {o_draw_title,o_draw_next_stage,o_draw_game_over,o_play_game,o_stop,o_new_game,o_editor_load_stages,o_editor,o_previous,o_next,o_sound,o_exit,
o_draw_menu,o_draw_info,o_draw_menu_options,o_hall_of_fame_new_entry,o_hall_of_fame_draw,o_draw_final,o_time_over,o_play_game_demo,o_new_game_demo,o_draw_next_stage_demo};

extern enum menu option;
extern enum menu tmp_option;                           //auxiliary key for menu options like (sound on/off) to return to the previous value

enum Tdifficulty {easy, medium, hard};
extern enum Tdifficulty difficulty;

enum Tcontroller {wsad, arrows, joypad};
extern enum Tcontroller controller;

enum Tlang {english, polish};
extern enum Tlang language;

enum Tdir {up,right,down,left};
extern enum Tdir dir;

extern BITMAP *screen_buffer[2];                        // main game screen

//extern BITMAP *bmp_background = NULL;

extern int next_page;

extern DATAFILE *data;
extern DATAFILE *images;                                // images in file blast_img.dat

//extern int MAX_STAGES=0;                             // max number of stages

//extern int STAGE= 0;                                    // number of stage
extern unsigned char TitleMap[MAP_Y_24][MAP_X_32];
extern unsigned char GameOverMap[MAP_Y_24][MAP_X_32];
extern unsigned char NextStageMap[MAP_Y_24][MAP_X_32];
extern int Map[MAX_STAGE][MAP_Y][MAP_X];               //stage



extern int** maze;
extern int** visited;
extern int rows;
extern int cols;
extern int start_row;
extern int start_col;


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////////////       **************                        DECLARATIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


extern void timer();

extern void next_lives(BITMAP* screen_buffer);
extern void stage_init(int STAGE);
extern void draw_text(BITMAP* buffer);
extern void play_game(BITMAP *buffer);
extern void play_game_demo(BITMAP *buffer);
extern int set_resolution();
extern void new_game();
extern int check_game_end();
extern int install_game();
extern void deinstall_game();
extern int load_data();
extern void free_data();
extern int editor(BITMAP *buffer,int E_Map[MAX_STAGE][MAP_Y][MAP_X],TElement *ptrelement,int ptrwait);
extern void draw_player(float scale,Tplayer *ptrplayer,BITMAP* buffer);
extern void draw_fire(float scale, Tfire fires[MAX_FIRE],BITMAP* buffer, Tplayer *ptrplayer);
extern void draw_explosion(float scale,Tplayer *ptrplayer,Texplosion explosions[MAX_EXPLOSION],BITMAP* buffer);
extern void move_player(Tplayer *ptrplayer, int demo);
extern void collision_fire(TElement *ptrelement,Tfire fires[MAX_FIRE],Texplosion explosions[MAX_EXPLOSION],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);

extern void move_fires(Tfire fires[MAX_FIRE]);
extern int player_control(Tplayer *ptrplayer,Tfire fires[MAX_FIRE],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern void draw_elements(TElement * ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],BITMAP *buffer,int STAGE, int option);   // 1-bmp_block ,2-bmp_wall ,3-bmp_quad ,4- bmp_stars
extern void random_move(TElement * ptrelement,int ptrwait,int *Map ,int STAGE);
extern void play();
extern int collision_computer_player (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int collision_computer_fires (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int new_collision_fires (TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int load_level(int sizeMap,int E_Map[MAX_STAGE][MAP_Y][MAP_X], char * path, enum Tdifficulty difficulty_level);
extern void save_level(int sizeMap,int E_Map[MAX_STAGE][MAP_Y][MAP_X], char * path, enum Tdifficulty difficulty_level);
extern int center_player(TElement *ptrelement);
extern int find_path(Tplayer *player, TElement *ptrelement, BITMAP * buffer, int MazeMap[MAX_STAGE][MAP_Y][MAP_X], int stage, int TARGET_START, int TARGET_END);
extern int collision_miners_player (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int collision_miners_element (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int tmpx,int tmpy, int STAGE);
extern int collision_miners_fires (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int collision_enemies_fires (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int collision_player(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int collision_miners_miner (TElement *ptrelement,int tmpy, int tmpx, int index_miner);
extern int collision_enemies_player (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int collision_enemies_element (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int tmpx,int tmpy, int STAGE);
extern void draw_title(BITMAP *buffer,BITMAP *bmp_obj,unsigned char TitleMap[MAP_Y_24][MAP_X_32],int element);
extern int draw_game_over(BITMAP *buffer,BITMAP *bmp_obj,unsigned char GameOverMap[MAP_Y_24][MAP_X_32],int elemencik,TElement * element, int ptrwait);
int draw_next_stage(BITMAP *buffer,BITMAP *bmp_obj,unsigned char NextStageMap[MAP_Y_24][MAP_X_32],int element, int ptrwait);
extern void draw_menu(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X],TElement * ptrelement, int ptrwait);
extern void draw_info(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X], TElement * ptrelement, int ptrwait);
extern int draw_menu_options(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X],int MUSIC_NUMBER);
extern void stage_init(int STAGE);
extern int draw_time_over(BITMAP *buffer, TElement * ptrelement);
extern int draw_final(BITMAP *buffer,TElement * ptrelement);
extern int draw_message(BITMAP *buffer,TElement * ptrelement);
extern int hall_of_fame_entry(TElement *ptrelement,BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X],int ptrwait);
extern int move_miner(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);     // kierunki   kolizje itp
extern void draw_miner(float scale,TElement *ptrelement,BITMAP* buffer);
extern void move_miner_around(TElement * ptrelement, int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern int move_enemy(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);     // kierunki   kolizje itp
extern void draw_enemy(float scale,TElement *ptrelement,BITMAP* buffer);
extern void move_enemy_around(TElement * ptrelement, int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE);
extern void get_visited();
extern int get_maze(int MazeMap[MAX_STAGE][MAP_Y][MAP_X],int stage);
extern int dfs(TElement *ptrelement, int row, int col, int TARGET_START, int TARGET_END);
extern int follow_path_to_target(Tplayer *ptrplayer,Tfire fires[MAX_FIRE],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE, int TARGET);
extern int create_Blast_config_file();
#endif// TYPY_H


