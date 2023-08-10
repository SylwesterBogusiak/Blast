
/*
//-------------- Blast Game - ver 1.2.xx      10.08.2023 --------------------
// ------------- written in C 99 LANGUAGE in CODE BLOCKS --------------------
// ------------- VERSION OF CB 20.03 OS UBUNTU 22.04     --------------------
// ------------- USE:                                    --------------------
// ------------- ALLEGRO LIBRARY                         --------------------
// ------------- JGMOD LIBRARY [ON/OFF POSSIBLE IN CODE] --------------------
// -------------                                         --------------------
// ------------- author: MARTE.BEST - Sylwester Bogusiak --------------------
// ------------- allegro ver 4.4 - Shawn Hargreaves      --------------------
// ------------- jgmod ver 0.99 - Jeffery Guan           --------------------
// ------------- coding - Sylwester Bogusiak [Sylvi91]   --------------------
// ------------- graphics - Sylwester Bogusiak [Sylvi91] --------------------
// ------------- music - Łukasz Sychowicz [X-Ray]        --------------------
// -------------                                         --------------------
// ------------- Program distributed on GPL-2.0 license  --------------------
// --- https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html  ---
// ------------- Source code available on my GitHub      --------------------
// ---------- https://github.com/SylwesterBogusiak/Blast --------------------
// -------------                                         --------------------
// cleaned code v3
// OK!
// NO ERRORS OR WARNINGS IN DEBUG MODE
// NO ERRORS AND JUST 1 WARNING IN RELEASE MODE
// warning: ‘__builtin_strncpy’ specified bound 12 equals destination size [-Wstringop-truncation]|
// OK!
*/

#include "main.h"


TElement element;

int** maze;
int** visited;
int rows;
int cols;
int start_row;
int start_col;

#ifdef jgmod

///// X-Ray Grayscale Project Atari Scene Screamtracker 3     (Łukasz Sychowicz)
char *filename[MAX_MOD]= {"snd/three.s3m",
"snd/menu.s3m",
"snd/fayatrn.s3m",
"snd/g_b_atar.s3m",
"snd/intfour.s3m",
"snd/kobuzz.s3m",
"snd/boatdog.s3m",
"snd/coqlush.s3m",
"snd/time.s3m"};
#endif // jgmod

int MUSIC_FILE_NUMBER=0;

volatile int close_button_pressed = FALSE;
int wait=0;                                                                         // for timer and drawing functions draw_title, draw_game_over etc



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////////////       **************                        DEFINITIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
void close_button_handler(void)

{
    close_button_pressed=TRUE;

}
END_OF_FUNCTION(close_button_handler)


void timer()
{

    static int uTimer=0;                        // local variable
    int i;
    int index;

    if (option!= o_stop)                        // animate unless pause is pressed
    {


    uTimer++;


    if (option==o_draw_menu)
    {
    element.uTimer_menu++;


    if ((element.uTimer_menu>60*10))
    {

    element.uTimer_menu=0;

    option=o_hall_of_fame_draw;


    }
    }

    if (option==o_hall_of_fame_draw)
    {

    element.uTimer_hall_of_fame++;

    if ((element.uTimer_hall_of_fame>60*10))
    {

    element.uTimer_hall_of_fame=0;

    option=o_new_game_demo;


    }
    }





    if (option==o_play_game_demo)
    {

    element.uTimer_play_demo++;

    if ((element.uTimer_play_demo>60*300))                              // play for 300 second
    {

    element.uTimer_play_demo=0;
    option=o_draw_menu;

    }


                                                                        // this is where control happens
    element.player.change_direction = 5;                                // 5 - off changes the direction on the follow path

    if (!(uTimer%(60*2)))                                               // every 2 seconds

    {
    element.player.change_direction = 4;                                //
    }

    if (!(uTimer%(60*3)))                                              // every 3 seconds


    {
    element.player.random_shot=element.player.type_of_weapon=(rand() % 3);      // 0 = ammo or 1 = laser
    }


    }






    if (!(uTimer%1))
    {
    wait = 0;
    }
    else
    {
    wait = 1;
    };                                                                                                      // slow to timer

    if (!(uTimer%1)) {element.player.wait=0;}
    else
    { element.player.wait=1;}


    if ((option==o_play_game) || (option==o_play_game_demo))
    {
    if (!(uTimer%60))
    {
    element.player.my_timer_sec--;

    if (element.player.my_timer_sec<0)
    {
    element.player.my_timer_sec=59;
    element.player.my_timer_min--;
    }

    if (element.player.my_timer_min<0)
    {
    element.player.my_timer_min=59;
    element.player.my_timer_sec=0;
    }




    }

    }


    if(!(uTimer%10))
    {

    element.electriclineV.anim_count++;

    if (element.electriclineV.anim_count>=MAX_ANIM_ELECTRIC)
    {
    element.electriclineV.anim_count=0;

    //rand() % MAX_ANIM_ELECTRIC
    }
    }

    if(!(uTimer%10))
    {

    if (element.electriclineH.anim_count>=MAX_ANIM_ELECTRIC)
    {
    element.electriclineH.anim_count=0;

    //rand() % MAX_ANIM_ELECTRIC;
    }
    }






    if(!(uTimer%10))
    {
    for (i=0;i<MAX_STAR;i++)                            // animation of death stars
    {

    element.stars[i].anim_count++;                      // animation of frames

    if(element.stars[i].anim_count >= MAX_ANIM_STARS)
    {
    element.stars[i].anim_count = 0;
    }
    }
    }

    for (i=0;i<MAX_COMP;i++)
    {
    element.miner[i].wait=1;                            // slow
    }


    if(!(uTimer%1))
    {
    for (i=0;i<MAX_COMP;i++)
    {
    element.miner[i].wait=0;                            // go
    }
    }



    for (i=0;i<MAX_FIRE;i++)
    {
    element.player.fires[i].wait=1;                     // slow
    }


    if(!(uTimer%1))
    {
    for (i=0;i<MAX_FIRE;i++)
    {
    element.player.fires[i].wait=0;                     // go
    }
    }


    if(!(uTimer%9))
    {
    for (i=0;i<MAX_COMP;i++)
    {
    element.miner[i].anim_count++;                      // animation
    if(element.miner[i].anim_count >= MAX_ANIM_COMP)
    {
    element.miner[i].anim_count = 0;
    }
    }
    }

    if(!(uTimer%9))
    {
    for (i=0;i<MAX_ENEMIES;i++)
    {
    element.enemy[i].anim_count++;                      // animation

    if(element.enemy[i].anim_count >= MAX_ANIM_COMP)
    {
    element.enemy[i].anim_count = 0;
    }
    }
    }


    for (i=0;i<MAX_ENEMIES;i++)
    {
    element.enemy[i].wait=1;                            // slow
    }


    if(!(uTimer%1)) for (i=0;i<MAX_ENEMIES;i++)
    {
    element.enemy[i].wait=0;                            // go
    }



    for (i=0;i<MAX_EXPLOSION;i++)
    {
    if (element.player.explosions[i].animate==1)
    {

    element.player.explosions[i].anim_count_x++;         // animation
    if (element.player.explosions[i].anim_count_x>(MAX_ANIM_EXPLOSION_X-1))
    {
    element.player.explosions[i].anim_count_x=0;
    element.player.explosions[i].anim_count_y++;         // animation

    if (element.player.explosions[i].anim_count_y>(MAX_ANIM_EXPLOSION_Y-1))
    {
    element.player.explosions[i].anim_count_y=0;
    }
    }
    }

    if ((element.player.explosions[i].anim_count_x>=MAX_ANIM_EXPLOSION_X-1)&&
    (element.player.explosions[i].anim_count_y>=MAX_ANIM_EXPLOSION_Y-1))
    {
    element.player.explosions[i].x=-100;                // when animation finished send behind screen
    element.player.explosions[i].y=0;
    element.player.explosions[i].animate=0;
    }


    }





    if (!(uTimer%60))
    {
    element.miner[1].divider = (rand() % 4)+1;          // for miner, can't be 0
    }

    if (!(uTimer%600))
    {
    for (i=0;i<MAX_COMP;i++)
    {
    element.miner[i].random_direction = (rand() % 4);   // set new direction
    }
    }


    index=0;

    index = (rand() % MAX_COMP);

    if (element.miner[index].id>0)
    {
    element.miner[index].mine=1;                        // set mine by random miner
    }




}
}


END_OF_FUNCTION(timer)



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// start new stage on position, etc.

void stage_init(int STAGE)
{
int i,j,x,y;
int index_miner,index_enemy;
int index_player=0;
int randx;
int randy;

CRUMB= 0;

crumb = 0;
wall = 99;                                              // aby pokazal miejsce ktore odwiedzil
was_here = 66;                                          // dla porusznia sie statkiem


element.player.follow_object = 0;                       // 0 - no follow, > 0 follow
element.player.find_object=STAR;                        // 0 - no finding, > 0 finding


camera.x_left=5*MAX_X;
camera.y_top=5*MAX_Y;
camera.x_right=5*MAX_X;
camera.y_bottom=5*MAX_Y;


element.miner[1].divider=2;                             // for move around

element.player.shift_y=0;                               // shift on the stage
element.player.shift_x=0;


element.editor.source_x=0;                              // for editor
element.editor.source_y=0;
element.editor.x=0;                                     //
element.editor.y=0;


/////////////////////////////////////////////////////////////////////////////////////////////


    // PLAYER

index_player=0;                                         // is there a player placed on the board, if not, draw him a position

    for(x=0;x<MAP_X;x++)
    {
    for (y=0;y<MAP_Y;y++)
    {
    if (Map[STAGE][y][x]==PLAYER)
    index_player=1;
    }
    }




    if (index_player==0)                                // only if no placed player
    {

    jumptodrawagain:

    randx= (rand() % MAP_X);                            //position x of the player
    randy= (rand() % MAP_Y);

    if ((Map[STAGE][randy][randx])==BACKGROUND)
    {
    Map[STAGE][randy][randx]=PLAYER;
    }
    else
    {
    goto jumptodrawagain;
    }


    element.player.x =randx*MAX_X;
    element.player.y = randy*MAX_Y;

    }

    //

    for(x=0;x<MAP_X;x++)
    {
        for (y=0;y<MAP_Y;y++)
        {
        if (Map[STAGE][y][x]==PLAYER)                           // element
        {
        Map[STAGE][y][x]=BACKGROUND;                            // enter 0 erase 6 so that it does not interfere with movement because I gave up writing with the player on the board
        element.player.direction = 4;                           // direction of the move - 0 = up, 1 = right, 2 = down, 3 = left
        element.player.step = 2;                                // step in pixels
        element.player.x = x*MAX_X;                             // position x of the player
        element.player.y = y*MAX_Y;
        element.player.type_of_weapon=0;                        // 0 = ammo, 1 = laser


#ifndef MiniBlast

        center_player(&element);

#endif // MiniBlast

        element.player.field=0;                                 // free space, not in use
        element.player.wait=0;                                  // wait for move_player

        if (option==o_new_game)
        {
        element.player.ammo=20;                                 // ammo weapon
        element.player.laser=20;                                // laser weapon
        element.player.ships=3;                                 // number of ships to start the journey
        }

        }

        }
    };


    for(i=0;i<MAX_FIRE;i++)
    {
    element.player.fires[i].direction= 4;
    element.player.fires[i].type_of_weapon=0;                   // 0 = ammo, 1 = laser [shoot with SPACE or RIGHT CONTROL]
    element.player.fires[i].step=2;                             // step in pixels for ammo
    element.player.fires[i].step2=4;                            // step in pixels for laser
    element.player.fires[i].x=-100;                             // set behind the board
    element.player.fires[i].y=-100;
    element.player.fires[i].wait=1;                             // slow with timer

    }



    for (i=0;i<MAX_EXPLOSION;i++)

    {
    element.player.explosions[i].animate=0;
    }


    // end player

    // MINER
    // reset all variables
    for(i=0;i<MAX_COMP;i++)
    {
    element.miner[i].x = -150;                                  // position x of the miner
    element.miner[i].y = -150;
    element.miner[i].hit=2;                                     // for draw miner, 2 = not animate
    element.miner[i].field=0;                                   // free field not in use
    element.miner[i].direction = 4;                             // direction of the move - 0 = up, 1 = right, 2 = down, 3 = left
    element.miner[i].random_direction = 4;                      // random direction for the move - 0 = up, 1 = right, 2 = down, 3 = left
    element.miner[i].step = 0;                                  // step in pixels
    element.miner[i].id=0;                                      // 0
    element.miner[i].mine=0;                                    // 0 = not set mine, 1 = set mine

    };

   // place on the stage

    index_miner=0;                                              // auxiliary variable

    for(x=0;x<MAP_X;x++)
    {
        for (y=0;y<MAP_Y;y++)
        {
        if (Map[STAGE][y][x]==MINER)                            // initiate miners
        {

        index_miner++;

        element.miner[index_miner].x = x*MAX_X;                 // position x of miner
        element.miner[index_miner].y = y*MAX_Y;
        element.miner[index_miner].hit=0;                       // 0 = can animate
        element.miner[index_miner].field=0;                     // free field not in use
        element.miner[index_miner].direction = 4;               // direction of the move - 0 = up, 1 = right, 2 = down, 3 = left
        element.miner[index_miner].random_direction = rand()%4; // random direction for the move - 0 = up, 1 = right, 2 = down, 3 = left
        element.miner[index_miner].step = 1;                    // step in pixels
        element.miner[index_miner].id=index_miner;              //


        for(i=0;i<MAX_FIRE;i++)
        {
        element.miner[index_miner].fires[i].direction= 4;
        //fires[i].anim_count=0;
        element.miner[index_miner].fires[i].step=2;
        element.miner[index_miner].fires[i].x=-200;
        element.miner[index_miner].fires[i].y=-200;


        };

        };
        };
    };
   // end miner


   // ENEMY
   // reset all variables

   for(i=0;i<MAX_ENEMIES;i++)
   {
    element.enemy[i].x = -150;                                  // position x of the miner
    element.enemy[i].y = -150;
    element.enemy[i].hit=2;                                     // for draw miner, 2 = not animate
    element.enemy[i].field=0;                                   // free field not in use
    element.enemy[i].direction = 4;                             // direction of the move - 0 = up, 1 = right, 2 = down, 3 = left
    element.enemy[i].random_direction = 4;                      // random direction for the move - 0 = up, 1 = right, 2 = down, 3 = left
    element.enemy[i].step = 0;                                  // step in pixels
    element.enemy[i].id=0;                                      // 0
    element.enemy[i].mine=0;                                    // 0 = not set mine, 1 = set mine
    element.enemy[i].divider=2;
    element.enemy[i].wait=1;


    };

   // ustaw na planszy

    index_enemy=0;                                              // auxiliary variable


    for(x=0;x<MAP_X;x++)
    {
        for (y=0;y<MAP_Y;y++)
        {
        if (Map[STAGE][y][x]==ENEMY)                            // initialize the board and delete the object from the map after it is dynamic and does not save on the board
        {

        index_enemy++;                                          // auxiliary variable

        element.enemy[index_enemy].x = x*MAX_X;                 // position x of miner
        element.enemy[index_enemy].y = y*MAX_Y;
        element.enemy[index_enemy].hit=0;                       // 0 = can animate
        element.enemy[index_enemy].field=0;                     // free field not in use
        element.enemy[index_enemy].direction = 4;               // direction of the move - 0 = up, 1 = right, 2 = down, 3 = left
        element.enemy[index_enemy].random_direction = rand()%4; // random direction for the move - 0 = up, 1 = right, 2 = down, 3 = left
        element.enemy[index_enemy].step = 1;                    // step in pixels
        element.enemy[index_enemy].id=index_enemy;

        for(i=0;i<MAX_FIRE;i++)
        {
        element.enemy[index_enemy].fires[i].direction= 4;
        //fires[i].anim_count=0;
        element.enemy[index_enemy].fires[i].step=2;
        element.enemy[index_enemy].fires[i].x=-200;
        element.enemy[index_enemy].fires[i].y=-200;

        }


        }
        }
    };

    // end enemy








    for (i=0;i<MAX_STAR;i++)
    {
    element.stars[i].anim_count=rand()%MAX_ANIM_STARS;

    };

    j=0;                                                                // auxiliary variable - number of stars

    for(x=0;x<MAP_X;x++)
    {
        for (y=0;y<MAP_Y;y++)
        {
        if (Map[STAGE][y][x]==STAR)                                     // element
        {
        j++;    //tutaj ilosc gwiazdek
        element.stars[j].x=x*MAX_X;
        element.stars[j].y=y*MAX_Y;
        }

        }
    };

    element.player.stars_left=j;                                        // how many stars left on the stage



 }  //stage_init()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int center_player(TElement *ptrelement)


{
     ptrelement->player.shift_y=(ptrelement->player.y)-(MAP_Y_24/2*MAX_Y); // centered


    if (ptrelement->player.shift_y<(0*MAX_Y))
    {
    (ptrelement->player.shift_y=(0*MAX_Y));
    }


    if (ptrelement->player.shift_y>(SCREEN_h*NUMBER_OF_SCREENS_Y)-(MAP_Y_24*MAX_Y))
    {
    (ptrelement->player.shift_y=(SCREEN_h*NUMBER_OF_SCREENS_Y)-(MAP_Y_24*MAX_Y));
    }

    ptrelement->player.shift_x=(ptrelement->player.x)-(MAP_X_32/2*MAX_X); // centered


    if (ptrelement->player.shift_x<(0*MAX_X))
    {
    (ptrelement->player.shift_x=(0*MAX_X));
    }

    if (ptrelement->player.shift_x>(SCREEN_w*NUMBER_OF_SCREENS_X)-(MAP_X_32*MAX_X))
    {
    (ptrelement->player.shift_x=(SCREEN_w*NUMBER_OF_SCREENS_X)-(MAP_X_32*MAX_X));
    }


return 0;

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// drawing info during the game

void draw_text(BITMAP *buffer)
{

    static  BITMAP *text_buffer=NULL;       //buffer tekstu wyswietlanych informacji o stanie gry


    if (text_buffer==NULL)


    {
    if (!(text_buffer=create_bitmap(SCREEN_w/5,text_height(font)*16+50 )))

    {

    if (language == polish)
    {
    allegro_message("Za malo pamieci do utworzenia bitmapy dla textu");
    }
    else

    {
    allegro_message("Not enough memory to create bitmap for texts");
    }

    }

    }


    clear_to_color(text_buffer,CLEAR);                                      // clear changed numbers and set transparent background


    textout_ex(text_buffer,font_menu,"Blast 1.2",10,10,WHITE,-1);           // TITLE version 1.2

    if (language == english)
    {


    textprintf_ex(text_buffer,font,0+10,FIELD_STAGE*MAX_Y+50,WHITE,-1,"STAGE : %d",STAGE+1);
    textprintf_ex(text_buffer,font,0+10,FIELD_SHIPS*MAX_Y+50,WHITE,-1,"SHIPS : %d",element.player.ships);
    textprintf_ex(text_buffer,font,0+10,FIELD_AMMO*MAX_Y+50,WHITE,-1,"AMMO  : %d",element.player.ammo);
    textprintf_ex(text_buffer,font,0+10,FIELD_LASER*MAX_Y+50,WHITE,-1,"LASER : %d",element.player.laser);
    textprintf_ex(text_buffer,font,0+10,FIELD_POINTS*MAX_Y+50,WHITE,-1,"POINTS: %d",element.player.points);
    textprintf_ex(text_buffer,font,0+10,FIELD_TIMER*MAX_Y+50,WHITE,-1,"TIMER : %d:%d",element.player.my_timer_min,element.player.my_timer_sec);
    textprintf_ex(text_buffer,font,0+10,FIELD_STAR*MAX_Y+50,WHITE,-1,"STARS : %d",element.player.stars_left);
    }

    if (language == polish)
    {
    textprintf_ex(text_buffer,font,0+10,FIELD_STAGE*MAX_Y+50,WHITE,-1,"ETAP  : %d",STAGE+1);
    textprintf_ex(text_buffer,font,0+10,FIELD_SHIPS*MAX_Y+50,WHITE,-1,"STATKI: %d",element.player.ships);
    textprintf_ex(text_buffer,font,0+10,FIELD_AMMO*MAX_Y+50,WHITE,-1,"BROŃ  : %d",element.player.ammo);
    textprintf_ex(text_buffer,font,0+10,FIELD_LASER*MAX_Y+50,WHITE,-1,"LASER : %d",element.player.laser);
    textprintf_ex(text_buffer,font,0+10,FIELD_POINTS*MAX_Y+50,WHITE,-1,"PUNKTY: %d",element.player.points);
    textprintf_ex(text_buffer,font,0+10,FIELD_TIMER*MAX_Y+50,WHITE,-1,"CZAS  : %d:%d",element.player.my_timer_min,element.player.my_timer_sec);
    textprintf_ex(text_buffer,font,0+10,FIELD_STAR*MAX_Y+50,WHITE,-1,"GWIAZD: %d",element.player.stars_left);
    }



    draw_sprite(buffer,text_buffer,0,0);                             // display bitmap with text with 0,0 coords


}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void play_game(BITMAP *screen_buffer)
{
    static  BITMAP *buffer=NULL;

    if (buffer==NULL)
    {
    buffer=create_bitmap(SCREEN_w*1,SCREEN_h*1);
    clear_to_color(buffer,CLEAR);                                        // clear to color and set clear background
    };


    clear_to_color(buffer,CLEAR);                                        // clear to color and set clear background


    // collisions with dynamic elements

    if (collision_miners_player (&element,Map,STAGE)==1)
    {
    next_lives(screen_buffer);
    };

    if (collision_enemies_player (&element,Map,STAGE)==1)
    {
    next_lives(screen_buffer);
    };

    // collisions with static elements

    if (collision_player(&element,Map,STAGE)==1)
    {
    next_lives(screen_buffer);
    };

    // draw elements
    draw_fire(SCALE,element.player.fires,buffer,&element.player);

    // move elements
    move_miner_around(&element, Map,STAGE);

    move_miner(&element,Map,STAGE);



    move_enemy_around(&element, Map,STAGE);

    move_enemy(&element,Map,STAGE);


    collision_fire(&element,element.player.fires,element.player.explosions,Map,STAGE);

    // order important

    // draw elements


    draw_elements(&element,Map,buffer,STAGE,o_play_game);

    draw_miner(SCALE,&element,buffer);

    draw_enemy(SCALE,&element,buffer);




    player_control(&element.player,element.player.fires,Map,STAGE);


    move_player(&element.player,0);
    draw_player(SCALE,&element.player,buffer);

    draw_explosion(SCALE,&element.player,element.player.explosions,buffer);


    collision_miners_fires(&element,Map,STAGE);
    collision_enemies_fires(&element,Map,STAGE);
    move_fires(element.player.fires);

    masked_blit(buffer,screen_buffer,0,0,0,0,0+SCREEN_w,0+SCREEN_h);

    draw_text(screen_buffer);  // draw text above all therefore at the end

/*
    static int lctrl=0;
    if (!key[KEY_LCONTROL])
    {
    lctrl=0;
    }


    if (lctrl==0)
    if (key[KEY_LCONTROL])
    {
    lctrl=1;

    find_path(&element.player,&element, buffer, Map, STAGE, STAR, PLAYER);

    }
*/

}




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void play_game_demo(BITMAP *screen_buffer)
{

    static  BITMAP *buffer=NULL;
    if (buffer==NULL)
    {

    buffer=create_bitmap(SCREEN_w*1,SCREEN_h*1);
    clear_to_color(buffer,CLEAR);

    };

    clear_to_color(buffer,CLEAR);

    if (collision_miners_player (&element,Map,STAGE)==1)
    {
    next_lives(screen_buffer);
    };


    if (collision_enemies_player (&element,Map,STAGE)==1)
    {
    next_lives(screen_buffer);
    };

   // Collision with static elements

    if (collision_player(&element,Map,STAGE)==1)
    {
    next_lives(screen_buffer);
    };

    draw_fire(SCALE,element.player.fires,buffer,&element.player);

    move_miner_around(&element, Map,STAGE);

    move_miner(&element,Map,STAGE);

    move_enemy_around(&element, Map,STAGE);

    move_enemy(&element,Map,STAGE);

    collision_fire(&element,element.player.fires,element.player.explosions,Map,STAGE);  //przenioslem tu

    // order important

    draw_elements(&element,Map,buffer,STAGE,o_play_game);

    draw_miner(SCALE,&element,buffer);

    draw_enemy(SCALE,&element,buffer);




    // order important


    if (element.player.ammo == 1)                                                   // 1 => 0 [exception]

    {
    element.player.ammo = 0;
    element.player.find_object = WEAPONRECHARGER;                                          // 0 = not find OK
    }


    if(element.player.find_object == WEAPONRECHARGER)  /////  0 - not find

    {

    if (find_path(&element.player, &element, buffer, Map, STAGE, WEAPONRECHARGER, PLAYER) == 1)

    {
    element.player.follow_object = WEAPONRECHARGER;                                        // follow
    element.player.find_object = 0;                                                 // it must be so that it does not search the route a second time
    CRUMB=crumb+1;
    }

    else

    {

    element.player.find_object = STAR;

    }

    }

    else
    if (element.player.find_object == STAR)                                     //  0 - not find

    {

    if (find_path(&element.player, &element, buffer, Map, STAGE, STAR, PLAYER) == 1)

    {
    element.player.follow_object = STAR;                                        // follow
    element.player.find_object = 0;                                             // it must be so that it does not search the route a second time
    CRUMB=crumb+1;
    }


    }



    if((element.player.follow_object==STAR))

    {

    follow_path_to_target(&element.player,element.player.fires,Map,STAGE,STAR);

    }

    if((element.player.follow_object==WEAPONRECHARGER))

    {

    follow_path_to_target(&element.player,element.player.fires,Map,STAGE,WEAPONRECHARGER);

    }

    move_player(&element.player,1);                                                             // 1 draw random direction
    draw_player(SCALE,&element.player,buffer);

    draw_explosion(SCALE,&element.player,element.player.explosions,buffer);


    collision_miners_fires(&element,Map,STAGE);
    collision_enemies_fires(&element,Map,STAGE);

    move_fires(element.player.fires);

    masked_blit(buffer,screen_buffer,0,0,0,0,0+SCREEN_w,0+SCREEN_h);



    draw_text(screen_buffer);                                                                   // draw text above all therefore at the end



}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int set_resolution()
{


    int c,w,h;

    MAX_X = 20;     //elements size
    MAX_Y = 20;
    SCREEN_w = 640;
    SCREEN_h = 480;


    set_gfx_mode(GFX_AUTODETECT, SCREEN_w, SCREEN_h, 0, 0);

    if (!gfx_mode_select(&c, &w, &h))
    {
	allegro_exit();

    }


    if (set_gfx_mode(c, w, h, 0, 0) != 0)
	{
	if (language == english)
	{
	allegro_message("Can't set this resolution!");
	} else
    if (language == polish)
	{
	allegro_message("Nie można ustawić tej rozdzielczości!");
	}

    allegro_exit();
    }

    return 0;
 }; //set_resolution

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

 void new_game()
 {

    element.player.ships=3;

    element.player.ammo=20;
    element.player.laser=20;
    element.player.points=0;

    element.player.my_timer_sec=60;

#ifdef MiniBlast
element.player.my_timer_min=4;                                              // MiniBlast 5 min MidiBlast 15 min MaxiBlast 60 min

#endif // MiniBlast

#ifdef MidiBlast
element.player.my_timer_min=14;                                             // MidiBlast

#endif // MiniBlast

#ifdef MaxiBlast

element.player.my_timer_min=59;                                             // MaxiBlast

#endif // MiniBlast


    element.player.my_timer_hrs=0;                                           // not in use
    element.player.stars_left=0;

    MAX_STAGES=load_level(sizeof(Map),Map,"stages/", difficulty);

    STAGE=0;            // must be 0

    stage_init(STAGE);

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
 void next_lives(BITMAP* screen_buffer)
 {

    if(element.player.ships>1) // 3,2,1 is last ship
    {

   textout_ex(screen,font_menu,"Your ship is destroyed.",(SCREEN_W/2-text_length(font_menu,"Your ship is destroyed.")/2),SCREEN_H/2,WHITE,-1);

   rest(1500);

    MAX_STAGES=load_level(sizeof(Map),Map,"stages/",difficulty);

    element.player.ammo=20;       /// chyba musi byc

    element.player.laser=20;       /// chyba musi byc

    element.player.ships--;

    stage_init(STAGE);

    }

    else

    {

    if (language == english)
    {
     textout_ex(screen,font_menu,"Your lost all ships.",(SCREEN_W/2-text_length(font_menu,"Your lost all ships.")/2),SCREEN_H/2,WHITE,-1);
    }

      if (language == polish)
    {
     textout_ex(screen,font_menu,"Straciłeś wszystkie statki.",(SCREEN_W/2-text_length(font_menu,"Straciłeś wszystkie statki.")/2),SCREEN_H/2,WHITE,-1);
    }

    rest(1500);

    option=o_draw_game_over;

    }


} // next_lives(BITMAP* screen_buffer)


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int install_game()
{

// the order is important

   /* initialize the library */
    if (allegro_init() != 0)
    {
        return 0;
    }

    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);
    install_timer();      //before install_mod
    install_mouse();
    install_keyboard();

    if (install_joystick(JOY_TYPE_AUTODETECT) != 0)
    {
    if (language == english)
    {
      allegro_message("Error initialising joypad\n%s\n", allegro_error);
    }
     if (language == polish)
    {
      allegro_message("Błąd inicjalizacji joypada\n%s\n", allegro_error);
    }

    };


#ifdef jgmod
	set_volume_per_voice(0);
    reserve_voices (MAX_MOD, -1);                                   // call this before install_sound if needed
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL))
	{

    if (language == english)
    {
        allegro_message("Error of audio drivers!");
    }

    if (language == polish)
    {
		allegro_message("Błąd instalacji sterowników dzwięku!");
    }
		return 1;
	}


    if (install_mod (MAX_MOD) < 0)
    {
    if (language == english)
    {
        allegro_message ("Error : Can't install and set the sound!");
    }
    if (language == polish)
    {
    allegro_message ("Błąd : Nie można zainstalować i ustawić dzwięku!");

    }
    return 1;
    }

    set_mod_volume(50*1.25);                                                // volume level in accordance with set_mod_volume(music_vol_increase_x*1.25);

#endif // jgmod

    controller = arrows;

    install_int_ex(timer, BPS_TO_TIMER(60));

    return 0;
} // install_game()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void deinstall_game()
{

    destroy_bitmap(screen_buffer[0]);
    destroy_bitmap(screen_buffer[1]);

#ifdef jgmod
    stop_mod();
    destroy_mod (*mod);
#endif // jgmod

    remove_int(timer);                                                      // after destroy_mod
    allegro_exit();

} // deinstall_game()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int load_data()
{

    FILE * file;
    int i,ii = 0;

    if (!(data = load_datafile("images/font.dat")))

    {

    if (language == english)
    {
     allegro_message("Can't open 'font.dat' file.");
    }

    if (language == polish)
    {
     allegro_message("Nie można otworzyć pliku 'font.dat'.");
    }
    allegro_exit();

    }


    if (!(images = load_datafile("images/blast_img20x20_RGB.dat")))
    {

    if (language == english)
    {
    allegro_message("Can't open 'blast_img20x20_grayscale.dat' file.");
    }

    if (language == polish)

    {
    allegro_message("Nie można otworzyć pliku 'blast_img20x20_grayscale.dat'.");
    }
    allegro_exit();

    }


    // read from .dat grabber file
    font = (FONT *)data[FONT_NUMBER_DAT].dat;                               // 1 = smaller font 8x8 pixels
    font_menu = (FONT *)data[FONT_NUMBER_DAT-1].dat;                        // 0 = bigger font 29px height
    mono_palette = (PALETTE*)images[MONO_PAL].dat;
    // read from .dat grabber file
#ifdef jgmod

    for (i=0;i<MAX_MOD;i++)
    {

    mod[i] = load_mod (filename[i]);
    if (mod[i] == NULL)
    {
    if (language == english)
    {
    allegro_message ("Error when reading %s '.s3m' type sound file.", filename[i]);
    }

    if (language == polish)
    {
    allegro_message("Błąd odczytu pliku dźwiękowego typu '.s3m' o tytule %s.", filename[i]);
    }

    allegro_exit();
    }

    };

#endif

    // load bitmaps
    AL_CONST char * message;


    if (language == english)
    {
    message = "Can't create bitmap!";
    }
    else

    if (language == english)
    {
    message = "Nie można utworzyć bitmapy!";
    }

    //load_pcx("../img10x10/ufo10_16.pcx",the_palette)))

    if(!(element.electriclineV.bmp = create_bitmap(MAX_X,MAX_Y*MAX_ANIM_ELECTRIC)))
    allegro_message("%s", message);

    if(!(element.electriclineH.bmp = create_bitmap(MAX_X*MAX_ANIM_ELECTRIC,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.switchOFFV.bmp = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.switchOFFH.bmp = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.slantLrotate.bmp_slantL = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.slantRrotate.bmp_slantR = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.block.bmp = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.wall.bmp_wall = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.quad.bmp_quad = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.weaponrecharger.bmp_weaponrecharger = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.slantL.bmp_slantL = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.slantR.bmp_slantR = create_bitmap(MAX_X,MAX_Y)))
    allegro_message("%s", message);

    if(!(element.bomb.bitmap = create_bitmap(MAX_X,MAX_Y)))
	allegro_message("%s", message);

    if(!(element.player.bmp = create_bitmap(MAX_X,MAX_Y*MAX_ANIM_COMP)))
    allegro_message("%s", message);

    // stars
    for ( i=0;i<MAX_STAR;i++)
    {
    if(!(element.stars[i].bmp_stars =  create_bitmap(MAX_X,MAX_Y*MAX_ANIM_STARS)))
    allegro_message("%s", message);
    }
    // ammo and laser
    for (i=0;i<MAX_FIRE;i++)
    {
    if(!(element.player.fires[i].bmp = create_bitmap(MAX_X,MAX_Y*MAX_ANIM_FIRES)))
    allegro_message("%s", message);
    }

    // explo

    for (i=0;i<MAX_EXPLOSION;i++)
    {

     if(!(element.player.explosions[i].bmp = create_bitmap(MAX_X*MAX_ANIM_EXPLOSION_X,MAX_Y*MAX_ANIM_EXPLOSION_Y)))


    {
    allegro_message("%s", message);}
    }

    // komp
    for (ii=0;ii<MAX_COMP;ii++)
    {
    if(!(element.miner[ii].bmp = create_bitmap(MAX_X,MAX_Y*MAX_ANIM_COMP)))
    {
    allegro_message("%s", message);
    }
    }

    // enemy
    for (ii=0;ii<MAX_ENEMIES;ii++)

    {
    if(!(element.enemy[ii].bmp = create_bitmap(MAX_X,MAX_Y*MAX_ANIM_COMP)))
    {

    allegro_message("%s", message);
    }
    }


    // reading the bitmaps from grabber 4.2 allegro .dat file


    element.block.bmp = (BITMAP*)images[BLOCK].dat;
    element.wall.bmp_wall = (BITMAP*)images[WALL].dat;
    element.quad.bmp_quad = (BITMAP*)images[QUAD].dat;
    element.weaponrecharger.bmp_weaponrecharger =(BITMAP*)images[WEAPONRECHARGER].dat;
    element.slantL.bmp_slantL = (BITMAP*)images[SLANTL].dat;
    element.slantR.bmp_slantR = (BITMAP*)images[SLANTR].dat;
    element.player.bmp = (BITMAP*)images[PLAYER].dat;
    element.bomb.bitmap = (BITMAP*)images[BOMB].dat;
    element.electriclineV.bmp = (BITMAP*) images[ELECTRICLINEV].dat;
    element.electriclineH.bmp = (BITMAP*) images[ELECTRICLINEH].dat;
    element.switchOFFV.bmp = (BITMAP*) images[WALLOFFV].dat;
    element.switchOFFH.bmp = (BITMAP*) images[WALLOFFH].dat;
    element.slantLrotate.bmp_slantL = (BITMAP*)images[SLANTLROTATE].dat;
    element.slantRrotate.bmp_slantR = (BITMAP*)images[SLANTRROTATE].dat;


    // star
    for ( i=0;i<MAX_STAR;i++)
    {
    element.stars[i].bmp_stars = (BITMAP*)images[STAR].dat;
    }


    // ammo and laser
    for (i=0;i<MAX_FIRE;i++)
    {
    element.player.fires[i].bmp = (BITMAP*)images[AMMO].dat;
    }


    // explo
    for (i=0;i<MAX_EXPLOSION;i++)
    {
    element.player.explosions[i].bmp = (BITMAP*)images[EXPLOSIONS].dat;
    }


    for (ii=0;ii<MAX_COMP;ii++)
    {
    element.miner[ii].bmp = (BITMAP*)images[MINER].dat;
    }


    for (ii=0;ii<MAX_ENEMIES;ii++)
    {
    element.enemy[ii].bmp = (BITMAP*)images[ENEMY].dat;
    }
    // reading from .dat grabber file end

    // COPYING BITMAPS TO ARRAYS FOR ANIMATED OBJECTS

    // stars

    for (i=0;i<MAX_STAR;i++)
    {

    for(ii = 0; ii < MAX_ANIM_STARS; ii++)
    {
    if(!(element.stars[i].bmptab[ii] = create_bitmap(MAX_X,MAX_Y)))

    {
             if (language == english)
    {
         allegro_message("Not enough memory to create sprites!");
    }

          if (language == polish)
    {
         allegro_message("Za mało pamięci do utworzenia sprajtów!");
    }
    allegro_exit();

    }


    blit(element.stars[i].bmp_stars,element.stars[i].bmptab[ii],0,i*MAX_X,0,0,element.stars[i].bmptab[ii]->w,element.stars[i].bmptab[ii]->h);

    }

    };

    // ammo



    for (i=0;i<MAX_FIRE;i++)
    {

    for(ii = 0; ii < MAX_ANIM_FIRES; ii++)
    {

    if(!(element.player.fires[i].bmptab[ii] = create_bitmap(MAX_X,MAX_Y)))
    {

    if (language == english)
    {
    allegro_message("Not enough memory to create sprites!");
    }

    if (language == polish)
    {
    allegro_message("Za mało pamięci do utworzenia sprajtów!");
    }

    allegro_exit();

    }


   blit(element.player.fires[i].bmp,element.player.fires[i].bmptab[ii],0,ii*MAX_X,0,0,element.player.fires[i].bmptab[ii]->w,element.player.fires[i].bmptab[ii]->h);

    }

    };

    // player

    for(i = 0; i < 4; i++)
    {
    if(!(element.player.bmptab[i] = create_bitmap(MAX_X,MAX_Y)))
    {

    if (language == english)
    {
    allegro_message("Not enough memory to create sprites!");
    }

    if (language == polish)
    {
    allegro_message("Za mało pamięci do utworzenia sprajtów!");
    }

    allegro_exit();

    }


    blit(element.player.bmp,element.player.bmptab[i],0,i*MAX_X,0,0,MAX_X,MAX_Y);


    }

    destroy_bitmap(element.player.bmp);                                 //


    for(i = 0; i < MAX_ANIM_ELECTRIC; i++)
    {

    if(!(element.electriclineV.bmptab[i] = create_bitmap(MAX_X,MAX_Y)))
    {

    if (language == english)
    {
    allegro_message("Not enough memory to create sprites!");
    }

    if (language == polish)
    {
    allegro_message("Za mało pamięci do utworzenia sprajtów!");
    }

    allegro_exit();

    }

    else

    {

    blit(element.electriclineV.bmp,element.electriclineV.bmptab[i],0,i*MAX_Y,0,0,MAX_X,MAX_Y);}

    }

    destroy_bitmap(element.electriclineV.bmp);


    for(i = 0; i < MAX_ANIM_ELECTRIC; i++)
    {

    if(!(element.electriclineH.bmptab[i] = create_bitmap(MAX_X,MAX_Y)))
    {

    if (language == english)
    {
    allegro_message("Not enough memory to create sprites!");
    }

    if (language == polish)
    {
    allegro_message("Za mało pamięci do utworzenia sprajtów!");
    }

    allegro_exit();

    };

    blit(element.electriclineH.bmp,element.electriclineH.bmptab[i],i*MAX_X,0,0,0,MAX_X,MAX_Y);

    }

    destroy_bitmap(element.electriclineH.bmp);


    // comp

    for (ii=0;ii<MAX_COMP;ii++)
    {
        for(i = 0; i < MAX_ANIM_COMP; i++)
        {
        if(!(element.miner[ii].bmptab[i] = create_bitmap(MAX_X,MAX_Y)))
        {
        if (language == english)
        {
        allegro_message("Not enough memory to create sprites!");
        }

        if (language == polish)
        {
        allegro_message("Za mało pamięci do utworzenia sprajtów!");
        }
        allegro_exit();

        }

        blit(element.miner[ii].bmp,element.miner[ii].bmptab[i],0,i*MAX_X,0,0,element.miner[ii].bmptab[i]->w,element.miner[ii].bmptab[i]->h);

        }
    };



    for (ii=0;ii<MAX_ENEMIES;ii++)
    {
        for(i = 0; i < MAX_ANIM_COMP; i++)
        {
        if(!(element.enemy[ii].bmptab[i] = create_bitmap(MAX_X,MAX_Y)))
        {

        if (language == english)
        {
        allegro_message("Not enough memory to create sprites!");
        }

        if (language == polish)
        {
         allegro_message("Za mało pamięci do utworzenia sprajtów!");
        }

        allegro_exit();
        }

        blit(element.enemy[ii].bmp,element.enemy[ii].bmptab[i],0,i*MAX_X,0,0,element.enemy[ii].bmptab[i]->w,element.enemy[ii].bmptab[i]->h);

        }
    }



// background
    bmp_background =create_bitmap(SCREEN_w, SCREEN_h);

    bmp_background = (BITMAP*)images[BACKGROUND].dat;

    if ((file=fopen("stages/NextStage","rb"))==NULL)                            //"r" text file  "rb" binary file

    {
    if (language == english)
    {
    allegro_message("Can't open 'NextStage' file.");
    }
    if (language == polish)
    {
    allegro_message("Nie można otworzyć pliku 'NextStage'.");
    }

    allegro_exit();

    }


    fseek(file,0,SEEK_SET);

    size_t ret_1 = fread(NextStageMap,1,sizeof(NextStageMap),file);
    printf("read %zu bytes from file NextStage\n", ret_1*sizeof(NextStageMap));

    fclose(file);


    if ((file=fopen("stages/Title","rb"))==NULL)                                //"r" text file  "rb" binary file
    {
    if (language == english)
    {
    allegro_message("Can't open 'Title' file.");
    }

    if (language == polish)
    {
    allegro_message("Nie można zotworzyć pliku 'Title'.");
    }
    allegro_exit();
    }

    fseek(file,0,SEEK_SET);

    size_t ret_2 = fread(TitleMap,1,sizeof(TitleMap),file);
    printf("read %zu bytes from file TitleMap\n", ret_2*sizeof(TitleMap));

    fclose(file);


    if ((file=fopen("stages/GameOver","rb"))==NULL)                             //"r" text file  "rb" binary file
    {
     if (language == english)
    {
    allegro_message("Can't open 'GameOver' file.");
    }

    if (language == polish)
    {
    allegro_message("Nie można otworzyć pliku 'GameOver'.");
    }
    allegro_exit();
    }

    fseek(file,0,SEEK_SET);

    size_t ret_3 = fread(GameOverMap,1, sizeof(GameOverMap),file);
    printf("read %zu bytes from file GameOverMap\n", ret_3*sizeof(GameOverMap));

    fclose(file);

    ////////////////////////////////////////////


return 0;

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void free_data()
{

  // DESTROY ALL OBJECTS


    int i = 0, ii=0;

    //destroy_bitmap(player.bmp);  already destroyed

    for(i = 0; i < 4; i++)
    {
    destroy_bitmap(element.player.bmptab[i]);
    };

    destroy_bitmap(element.switchOFFH.bmp);
    destroy_bitmap(element.switchOFFV.bmp);

    for(i = 0; i < MAX_ANIM_ELECTRIC; i++)
    {
    destroy_bitmap(element.electriclineH.bmptab[i]);
    destroy_bitmap(element.electriclineV.bmptab[i]);
    };



    destroy_bitmap(bmp_background);

    destroy_bitmap(element.block.bmp);

    destroy_bitmap(element.wall.bmp_wall);
    destroy_bitmap(element.quad.bmp_quad);
    for (i=0;i<MAX_STAR;i++)
    {
    destroy_bitmap(element.stars[i].bmp_stars);
    };


    for (i=0;i<MAX_COMP;i++)
    {
    destroy_bitmap(element.miner[i].bmp);

    for (ii=0;ii<MAX_ANIM_COMP;ii++)
    {
    destroy_bitmap(element.miner[i].bmptab[ii]);
    }
    };

    for (i=0;i<MAX_ENEMIES;i++)
    {
    destroy_bitmap(element.enemy[i].bmp);

    for (ii=0;ii<MAX_ANIM_COMP;ii++)
    {
    destroy_bitmap(element.enemy[i].bmptab[ii]);
    }
    };



    destroy_bitmap(element.slantL.bmp_slantL);
    destroy_bitmap(element.slantR.bmp_slantR);
    // destroy_bitmap(bmp_explosion);


} //free_data()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//this function checks the end condition, i.e. (no death stars)
int check_game_end()
{
     int x,y,end;
        end=0;

        for(x=0;x<MAP_X;x++)
        for (y=0;y<MAP_Y;y++)
        {
        if (Map[STAGE][y][x]==STAR)                                     // stars
        end++;
         };
     if (end==0) return 0;                                              // end = 0; yes, stage game end


     return 1;

} // check_game_end()

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// window procedure

int Wndproc(TElement *ptrelement, BITMAP * screen_buffer)
{


    static int val;
    int pos_x, pos_y;

    static int val_y,val_x;

    if ((option==o_draw_info) || (option==o_hall_of_fame_draw) || (option==o_draw_menu) || (option==o_play_game_demo))

    {
    val = keypressed();


    pos_x = mouse_x;
    pos_y = mouse_y;

    if((val_y!=pos_y) || (val_x!=pos_x) || (val!=0))
    {
    element.uTimer_menu=0;
    element.uTimer_hall_of_fame=0;
    element.uTimer_info=0;
    element.uTimer_play_demo=0;


    if ((option==o_draw_info) || (option==o_hall_of_fame_draw) || (option==o_play_game_demo))
    {

        option=o_draw_menu;
    }

    }


    clear_keybuf();
    val_y=mouse_y;
    val_x=mouse_x;

    };

    if (option==o_draw_title)
    {
    if ((key[KEY_SPACE]) || (mouse_b & 1))
    {
    rest(1000);                                                             // 1 sec
    option=o_draw_menu;
    }
    };

    if (key[KEY_ESC])
    {
    element.uTimer_menu=0;
    element.uTimer_hall_of_fame=0;
    element.uTimer_info=0;
    element.uTimer_play_demo=0;
    option=o_draw_menu;
    }

    if(option==o_editor)
    {
    if (key[KEY_S])
    {
    save_level(sizeof(Map),Map,"stages/",difficulty);

    if (language == english)
    {
    allegro_message("All stages are saved.");
    }

     if (language == polish)
    {
    allegro_message("Wszystkie plansze zapisano.");
    }
    }
    };



    static int f1up=0;

    if (!(key[KEY_F1]))
    {
    f1up=0;
    };
                                              // restart the board reducing lives
    if (f1up==0)
    {
    if (key[KEY_F1])
    {
    f1up=1;

    if(option==o_play_game)         // tylko jezeli jest gra wcisniecie F1 restartuje plansze i odejmuje zycia
    {
    next_lives(screen_buffer);
    }

    }
    }


#ifdef jgmod
    static int f5up=0;

    if (!(key[KEY_F5]))
    {
    f5up=0;
    };

    if (f5up==0)
    {
    if (key[KEY_F5])
    {
    f5up=1;

    play_mod(mod[MUSIC_FILE_NUMBER],FALSE);

    MUSIC_FILE_NUMBER++;

    if (MUSIC_FILE_NUMBER>=(MAX_MOD))
    {
    MUSIC_FILE_NUMBER=0;
    };

    play_mod(mod[MUSIC_FILE_NUMBER],TRUE);

    }
    }

#endif // jgmod

    // pause and continue game
    static int keyPup=0;

    if(option==o_stop)
    {
    if ((key[KEY_P]) && (keyPup==1))
    {
    option= o_play_game;
    keyPup = 0;
    return 0;
    }
    }

    if(option==o_play_game)
    {
    if ((key[KEY_P]) && (keyPup==1))
    {
    option= o_stop;
    keyPup=0;
    return 0;
    }
    }

    if (!key[KEY_P]) keyPup=1;



    return 0;
} // Wndproc(TElement *ptrelement, BITMAP * screen_buffer)

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/* works lik strcmp, but ignores case */
int strcmp_no_case(const char*lhs, const char*rhs)
{
    char v;
    while (*lhs && *rhs)
    {
        v = utolower(*lhs) - utolower(*rhs);

        if (v)
        {
        return v;
        }

        ++lhs;
        ++rhs;
    }

    if (*lhs)
    {
    return 1;
    }

    if (*rhs)
    {
    return -1;
    }

    return 0;

} // strcmp_no_case


int load_config()
{
    int w = 800,h = 600,bpp = 24;
    int windowed = GFX_AUTODETECT_WINDOWED;
    int count;
    char **data;

    char *title;

    /* save the current ini file, then set the program specific one */

    push_config_state();

    if (create_Blast_config_file() !=0)
    {

    windowed = GFX_AUTODETECT_WINDOWED;
    title = "Blast 1.2 SE MARTE.BEST";
    w = 800;
    h = 600;
    bpp = 24;
    }
    else
    {

    set_config_file("data/Blast_config.ini");

    /* the gfx mode is stored like this:
    *    640  480 16
    * the get_config_argv() function returns a pointer to a char
    * array, and stores the size of the char array in an int
    */

    data = get_config_argv("graphics", "mode", &count);
    if (count != 3)
    {
    /* We expect only 3 parameters */
    if (language == english)
    {
    allegro_message("Found %i parameters in graphics mode instead of the 3 expected.", count);
    }

    if (language == polish)
    {
    allegro_message("Znaleziono %i parametrów dla trybu graficznego zamiast oczekiwanych 3.", count);
    }

    allegro_exit();
    }
    else
    {
    w = atoi(data[0]);
    h = atoi(data[1]);
    bpp = atoi(data[2]);
    }

    /* Should we use a windowed mode?
    * In the config file this is stored as either FALSE or TRUE.
    * So we need to read a string and see what it contains.
    * If the entry is not found, we use "FALSE" by default
    */

    windowed = GFX_AUTODETECT_WINDOWED;
    if (strcmp_no_case(get_config_string("graphics", "windowed", "FALSE"), "FALSE") == 0)
    {
    windowed = GFX_AUTODETECT_FULLSCREEN;
    }

    else
    {
    windowed = GFX_AUTODETECT_WINDOWED;
    }

    /* the title string
    * The string returned is stored inside of the config system
    * and would be lost if we call pop_config_state(), so we create
    * a copy of it.
    */
    title = ustrdup(get_config_string("content", "headline", "<no headline>"));

    /* restore the old config file */
    pop_config_state();
    };


    set_color_depth(bpp);


    if (set_gfx_mode(windowed, w, h, 0, 0) != 0)
	{

    if (language == english)
    {
	allegro_message("Can't set this graphics mode!");
    }

    if (language == polish)
    {
	allegro_message("Nie można ustawić tego trybu graficznego!");
    }

	allegro_exit();

    }

    if (set_display_switch_mode(SWITCH_BACKGROUND)==-1)
    {
    set_display_switch_mode(SWITCH_PAUSE);
    }


    set_window_title(title);

    /* mandatory for screen_buffer resize and elements size */

    SCREEN_w = 640;
    SCREEN_h = 480;
    MAX_X = 20;
    MAX_Y = 20;

    return 0;

} // load_config()



//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////MAIN////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{


    BITMAP *screen_buffer[2];
    MAX_STAGES=0;                                           // max number of stages
    STAGE = 0;
    srand(time(0));                                         /* seed set */

    install_game();
    load_config();                                          // from file
    load_data();

    stage_init(STAGE);


#ifdef jgmod

    MUSIC_FILE_NUMBER = rand() % (MAX_MOD - 1);

    play_mod(mod[MUSIC_FILE_NUMBER],TRUE);

#endif


    set_palette(*mono_palette);   //dla alleg211 tylko to dziala

    next_page=1;

    if (!(screen_buffer[0]=create_bitmap(SCREEN_w, SCREEN_h)))
    {
    if (language == english)
    {
    allegro_message("Not enough memory to create screen buffer!");
    }

    if (language == polish)
    {
    allegro_message("Za mało pamięci do utworzenia buffera ekranu!");
    }

    allegro_exit();

    }


    if (!(screen_buffer[1]=create_bitmap(SCREEN_w, SCREEN_h)))
    {
    if (language == english)
    {
    allegro_message("Not enough memory to create screen buffer!");
    }
    if (language == polish)
    {
    allegro_message("Za mało pamięci do utworzenia buffera ekranu!");
    }

    allegro_exit();

    }

    difficulty = easy;                                                  // set difficulty level
    language = english;                                                 // set default language
    element.startscroll=1;                                              // for draw info
    element.is_cleaned=0;                                               // ok
    strcpy(element.player.total_score_buffer,"     ");

    element.uTimer_menu=0;
    element.uTimer_hall_of_fame=0;
    element.uTimer_info=0;
    element.uTimer_play_demo=0;

    option=o_draw_title;

    new_game();                                                         // (load level, reset elements and player, miners, enemies etc.)

    /* main loop */
    while (!close_button_pressed)
    {

    if (controller == joypad) poll_joystick();                          /* we HAVE to do this to read the joystick */

    clear(screen_buffer[next_page]);                                        // paleta kolorow  grayscale 0 -black ,255- white

    Wndproc(&element, screen_buffer[next_page]);


    switch(option)
    {

    case o_draw_title:
    {
    draw_title(screen_buffer[next_page],element.wall.bmp_wall,TitleMap,BLOCK); break;
    }

    case o_play_game:
    {



    if (MAX_STAGES<=0)
    {

    if (language == english)
    {
    allegro_message("Ther is no files with stages. You are transferred to the Game Editor.");
    }
    if (language == polish)
    {
    allegro_message("Brak pliku z planszami. Jesteś przeniesiony do edytora plansz.");
    }

    option=o_editor;

    }
    else

    if (check_game_end()==0)
    {

    if (MAX_STAGES>0)
    {

    if (STAGE>=(MAX_STAGES-1))
    {

    if (language == english)
    {
    textout_ex(screen,font_menu,"All 'death stars' succesfully neutralised!",(SCREEN_W/2-text_length(font_menu,"All 'death stars' succesfully neutralised!")/2),SCREEN_H/2,WHITE,-1);
    }

    if (language == polish)
    {
    textout_ex(screen,font_menu,"Wszystkie 'gwiazdy śmierci' zosatały zneutralizowane!",(SCREEN_W/2-text_length(font_menu,"Wszystkie 'gwiazdy śmierci' zosatały zneutralizowane!")/2),SCREEN_H/2,WHITE,-1);
    }

    rest(6000);

    option =o_draw_final;

    }

    else
    {

    if (language == english)
    {
    textout_ex(screen,font_menu,"All 'death stars' on this stage succesfully neutralised!",(SCREEN_W/2-text_length(font_menu,"All 'death stars' on this stage succesfully neutralised!")/2),SCREEN_H/2,WHITE,-1);
    }
    if (language == polish)
    {
    textout_ex(screen,font_menu,"Wszystkie 'gwiazdy śmierci' na tym etapie zostały zneutralizowane!",(SCREEN_W/2-text_length(font_menu,"Wszystkie 'gwiazdy śmierci' na tym etapie zostały zneutralizowane!")/2),SCREEN_H/2,WHITE,-1);
    }

    rest(3000);                                                             // 3 seconds

    option =o_draw_next_stage;}

    }
    };


    if ((element.player.my_timer_sec<=0) && (element.player.my_timer_min<=0))             /// end gry jesli czas sie skonczyl
    {

    if (language == english)
    {
    textout_ex(screen,font_menu,"The time is over!",(SCREEN_W/2-text_length(font_menu,"The time is over!")/2),SCREEN_H/2,WHITE,-1);
    }

    if (language == polish)
    {
    textout_ex(screen,font_menu,"Czas się skończył!",(SCREEN_W/2-text_length(font_menu,"Czas się skończył!")/2),SCREEN_H/2,WHITE,-1);
    }

    rest(6000);                                                                 // 6 seconds

    option = o_time_over;
    }


    play_game(screen_buffer[next_page]);



    break;
    };

    case o_stop:
    {
    if (language == english)
    {
    textout_ex(screen_buffer[next_page],font,"Paused" ,(SCREEN_w-text_length(font,"Paused"))/2, (SCREEN_h-text_height(font))/2,WHITE,-1);
    }

    if (language == english)
    {
    textout_ex(screen_buffer[next_page],font,"Pauza" ,(SCREEN_w-text_length(font,"Pauza"))/2, (SCREEN_h-text_height(font))/2,WHITE,-1);
    }

    break;
    };

    case o_draw_next_stage:
    {
    option=draw_next_stage(screen_buffer[next_page],element.wall.bmp_wall,NextStageMap,BLOCK,wait);

    if (option==o_play_game)
    {
    STAGE++;
    };

    stage_init(STAGE);

    break;
    };


    case o_draw_game_over:
    {

     // hall_of fame
    option =draw_game_over(screen_buffer[next_page],element.wall.bmp_wall,GameOverMap,BLOCK,&element,wait);
    break;
    }


    case o_new_game:
    {
    new_game();
    option=o_play_game;
    break;
    }

    case o_editor_load_stages:
    {
    if (load_level(sizeof(Map),Map,"stages/",difficulty)==-1)
    { // the function returns -1 when there is no file or returns max_stage(max level after checking if there are stars on the board

    save_level(sizeof(Map),Map,"stages/", difficulty);

    if (language == english)
    {
    allegro_message("New clear levels set is created.");
    }

    if (language == polish)
    {
    allegro_message("Nowy czysty zestaw plansz został utworzony.");
    }

    }

    option=o_editor;
    break;
    };

    case o_editor:
    {

    editor(screen_buffer[next_page],Map,&element,wait);
    break;
    };

    case o_previous:
    {


#ifdef jgmod
    //stop_mod();
    play_mod(mod[MUSIC_FILE_NUMBER],FALSE);
    MUSIC_FILE_NUMBER--;

    if (MUSIC_FILE_NUMBER<0)
    {
    MUSIC_FILE_NUMBER=MAX_MOD-1;
    }
    play_mod(mod[MUSIC_FILE_NUMBER],TRUE);

#endif // jgmod

    option=tmp_option;

    break;
    };

    case o_next :
    {
#ifdef jgmod
    //stop_mod();
    play_mod(mod[MUSIC_FILE_NUMBER],FALSE);
    MUSIC_FILE_NUMBER++;

    if (MUSIC_FILE_NUMBER>MAX_MOD)
    {
    MUSIC_FILE_NUMBER=0;
    }
    play_mod(mod[MUSIC_FILE_NUMBER],TRUE);
#endif // jgmod

    option=tmp_option;

    break;
    }

    case o_sound:
    {
    option=tmp_option;

    break;
    }

    case o_exit:
    {
    goto End ;

    break;
    };

    case o_draw_menu:
    {
    draw_menu(screen_buffer[next_page],0,Map,&element, wait);

    break;
    }


    case o_draw_info:
    {
    draw_info(screen_buffer[next_page],0,Map,&element,wait);

    break;
    };

    case o_draw_menu_options:
    {

    MUSIC_FILE_NUMBER=draw_menu_options(screen_buffer[next_page],0,Map,MUSIC_FILE_NUMBER);

    break;
    };

    case o_hall_of_fame_new_entry:
    {
    option= hall_of_fame_entry(&element,screen_buffer[next_page],0,Map,&wait);

    break;
    };

    case o_hall_of_fame_draw:
    {
    option= hall_of_fame_entry(&element,screen_buffer[next_page],0,Map,&wait);

    break;
    };

    case o_draw_final:
    {
    option= draw_final(screen_buffer[next_page],&element);

    break;
    };

    case o_time_over:
    {
    option= draw_time_over(screen_buffer[next_page],&element);

    break;
    }

    case o_new_game_demo:
    {
    new_game();
    option=o_play_game_demo;

    break;
    };

    case o_play_game_demo:
    {

    if (MAX_STAGES<=0)          /// bylo <=0 i przy jednym levelu przenosilo do editora dlatego dodalem 1 do tej zmiemnnej przy ladowaniu load level2
    {

    if (language == english)
    {
    allegro_message("Ther is no files with stages. You are transferred to the Game Editor.");
    }

    if (language == polish)
    {
    allegro_message("Brak pliku z planszami. Jesteś przeniesiony do Edytora plansz.");
    }

    option=o_editor;
    };


    if (check_game_end()==0)
    {

    if (MAX_STAGES>0)
    {

    if (STAGE>=(MAX_STAGES-1))
    {

    if (language == english)
    {
    textout_ex(screen,font_menu,"All 'death stars' succesfully neutralised!",(SCREEN_W/2-text_length(font_menu,"All 'death stars' succesfully neutralised!")/2),SCREEN_H/2,WHITE,-1);
    }

    if (language == polish)
    {
    textout_ex(screen,font_menu,"Wszystkie 'gwiazdy śmierci' zosatały zneutralizowane!",(SCREEN_W/2-text_length(font_menu,"Wszystkie 'gwiazdy śmierci' zosatały zneutralizowane!")/2),SCREEN_H/2,WHITE,-1);
    }

    rest(1500);

    option =o_draw_menu;                                                            // when game end back to menu

    }

    else
    {

    if (language == english)
    {
    textout_ex(screen,font_menu,"All 'death stars' on this stage succesfully neutralised!",(SCREEN_W/2-text_length(font_menu,"All 'death stars' on this stage succesfully neutralised!")/2),SCREEN_H/2,WHITE,-1);
    }

    if (language == polish)
    {
    textout_ex(screen,font_menu,"Wszystkie 'gwiazdy śmierci' na tym etapie zostały zneutralizowane!",(SCREEN_W/2-text_length(font_menu,"Wszystkie 'gwiazdy śmierci' na tym etapie zostały zneutralizowane!")/2),SCREEN_H/2,WHITE,-1);
    }

    rest(1500);


    option =o_draw_next_stage_demo;
    };

    }

    }

    play_game_demo(screen_buffer[next_page]);


    if (language == english)
    {
    textout_centre_ex(screen_buffer[next_page],font_menu,"Demo Game!",SCREEN_w/2,MAX_Y*2,WHITE,-1);
    textout_centre_ex(screen_buffer[next_page],font_menu,"Press any key to back to menu.",SCREEN_w/2,MAX_Y*3,WHITE,-1);
    }

    if (language == polish)
    {
    textout_centre_ex(screen_buffer[next_page],font_menu,"Gra Demo!",SCREEN_w/2,MAX_Y*2,WHITE,-1);
    textout_centre_ex(screen_buffer[next_page],font_menu,"Naciśnij dowolny klawisz aby wrócić do menu.",SCREEN_w/2,MAX_Y*3,WHITE,-1);
    }

    break;
    };

    case o_draw_next_stage_demo:
    {
    option=draw_next_stage(screen_buffer[next_page],element.wall.bmp_wall,NextStageMap,BLOCK, wait);

    if (option==o_play_game_demo)
    {
    STAGE++;
    };

    stage_init(STAGE);

    break;
    };



    }; // from switch(option)

    vsync();
    acquire_screen();
    stretch_blit(screen_buffer[next_page], screen, 0, 0, SCREEN_w, SCREEN_h,0, 0, SCREEN_W, SCREEN_H);   // scale 640x320 32x24 elements map by 20 px to present resolution
    release_screen();

    next_page = 1 - next_page;

     } //while (TRUE)    close_button_pressed

    End:

    deinstall_game();

    allegro_exit();

}
#ifdef END_OF_MAIN

END_OF_MAIN()
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
