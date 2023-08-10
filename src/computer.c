
#include "player.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// 0 starts animating, 2 stands by and does nothing
void draw_miner(float scale,TElement *ptrelement,BITMAP* buffer)
{

    int x,y;
    int i;


    for(i=0;i<MAX_COMP;i++)
    {

    x=ptrelement->miner[i].x-ptrelement->player.shift_x;
    y=ptrelement->miner[i].y-ptrelement->player.shift_y;




    if (ptrelement->miner[i].hit==0)

    {
    rotate_sprite(buffer,ptrelement->miner[i].bmptab[ptrelement->miner[i].anim_count],x,y,(ptrelement->miner[i].random_direction+1)*64*65635);
    }
    else
    if (ptrelement->miner[i].hit==1)
    {

    // move behind the scene

    ptrelement->miner[i].x=-50;
    ptrelement->miner[i].y=-50;
    ptrelement->miner[i].hit=2;

    }

    }; // from for





 } // draw_miner();



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// move miner
int move_miner(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)
{

int i,tmpx=0,tmpy=0;

    for(i=0;i<MAX_COMP;i++)
    {{


    if (ptrelement->miner[i].wait == 0)
    {{

    if (ptrelement->miner[i].hit==0)

    {
        tmpy =ptrelement->miner[i].y/MAX_Y;
        tmpx =ptrelement->miner[i].x/MAX_X;


            if (ptrelement->miner[i].mine==1)              /// set mine
            {
            ptrelement->miner[i].mine=0;
            (Map[STAGE][tmpy][tmpx]=COMPUTER_MINE);
            }



            if (ptrelement->miner[i].x<(MARGIN_LEFT*MAX_X))
            {
            ptrelement->miner[i].x=(MARGIN_LEFT*MAX_X);
            ptrelement->miner[i].random_direction=(rand() % 4);  // turn in a random direction
            };
            if (ptrelement->miner[i].x>NUMBER_OF_SCREENS_X*SCREEN_w-(MARGIN_RIGHT*MAX_X)-MAX_X)
            {
            ptrelement->miner[i].x=NUMBER_OF_SCREENS_X*SCREEN_w-(MARGIN_RIGHT*MAX_X)-MAX_X;
            ptrelement->miner[i].random_direction=(rand() % 4);  // turn in a random direction
            };
            if (ptrelement->miner[i].y<(MARGIN_TOP*MAX_Y))
            {
            ptrelement->miner[i].y=(MARGIN_TOP*MAX_Y);
            ptrelement->miner[i].random_direction=(rand() % 4);  // turn in a random direction
            };
            if (ptrelement->miner[i].y>NUMBER_OF_SCREENS_Y*SCREEN_h-(MARGIN_BOTTOM*MAX_Y)-MAX_Y)
            {
            ptrelement->miner[i].y=NUMBER_OF_SCREENS_Y*SCREEN_h-(MARGIN_BOTTOM*MAX_Y)-MAX_Y;
            ptrelement->miner[i].random_direction=(rand() % 4);  // turn in a random direction
            };


            if ((ptrelement->miner[i].section<=0))
            {
            ptrelement->miner[i].direction=4;

            }


            if ((ptrelement->miner[i].section>0))

            {

            switch (ptrelement->miner[i].direction)

            {

            case 1: {ptrelement->miner[i].x+=ptrelement->miner[i].step; break;}     // krok right
            case 2: {ptrelement->miner[i].y+=ptrelement->miner[i].step; break;}     // down
            case 3: {ptrelement->miner[i].x-=ptrelement->miner[i].step; break;}     // krok w left
            case 0: {ptrelement->miner[i].y-=ptrelement->miner[i].step; break;}     // up

            }; // od switch

            };

            if ((ptrelement->miner[i].section)>0)
            {
            (ptrelement->miner[i].section)--;
            };

    }; // from if

    }}

    }}  // from for

    return 0;

}; //move miner();


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void move_miner_around(TElement * ptrelement, int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)
{
    int i,tmpx,tmpy;
    int mouse_control=0;

    tmpx = 0;
    tmpy = 0;


    for(i=0;i<MAX_COMP;i++)
    {
    if(ptrelement->miner[i].wait==0)
    {

    // ATTENTION MINER IS SAVED ON THE BOARD AND THE FIRST MOVE AFTER THE START SHOULD DELETE HIS STARTING POINT

    // if there is no remainder from division, that is integer values
    if ((!(ptrelement->miner[i].x%MAX_X)) &&(!(ptrelement->miner[i].y%MAX_Y)))

    {
    tmpx=(ptrelement->miner[i].x)/MAX_X;tmpy=(ptrelement->miner[i].y)/MAX_Y;
    };

//if (ptrwait == 0)

    {
    if (ptrelement->miner[i].section<=0)
    if (mouse_control==0)

    {

    /* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING LEFT */


    if (ptrelement->miner[i].hit==0)
    {

    if (ptrelement->miner[i].direction==4)
    {

    if (ptrelement->miner[i].random_direction==3)
    {

    ptrelement->miner[i].angle=270;

    if(((Map[STAGE][tmpy][tmpx-1]==BACKGROUND) ||
    (Map[STAGE][tmpy][tmpx-1]==MINER) ||
    (Map[STAGE][tmpy][tmpx-1]==COMPUTER_MINE)) &&
    (collision_miners_miner(ptrelement,tmpy,tmpx-1,ptrelement->miner[i].id)==0))

    {
    ptrelement->miner[i].direction = 3;
    ptrelement->miner[i].angle=270;
    ptrelement->miner[i].section=MAX_X/ptrelement->miner[i].step;
    }

    else

    {

    if (!(ptrelement->miner[i].id%ptrelement->miner[1].divider))
    {
    ptrelement->miner[i].random_direction=0;
    }
    else
    {
    ptrelement->miner[i].random_direction=2;
    }
    }
    };

/* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING RIGHT */

    if (ptrelement->miner[i].random_direction==1)
    {
    ptrelement->miner[i].angle=90;

    if (((Map[STAGE][tmpy][tmpx+1]==BACKGROUND) ||
    (Map[STAGE][tmpy][tmpx+1]==MINER) ||
    (Map[STAGE][tmpy][tmpx+1]==COMPUTER_MINE)) &&
    (collision_miners_miner(ptrelement,tmpy,tmpx+1,ptrelement->miner[i].id)==0))

    {
    ptrelement->miner[i].direction = 1;
    ptrelement->miner[i].angle=90;

    ptrelement->miner[i].section=MAX_X/ptrelement->miner[i].step;
    }
    else
    {
    if (!(ptrelement->miner[i].id%ptrelement->miner[1].divider))
    {
    ptrelement->miner[i].random_direction=2;
    }
    else
    {
    ptrelement->miner[i].random_direction=0;
    }
    }
    };

    /* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING DOWN */

    if (ptrelement->miner[i].random_direction==2)
    {

    ptrelement->miner[i].angle=180;

    if (((Map[STAGE][tmpy+1][tmpx]==BACKGROUND) ||
    (Map[STAGE][tmpy+1][tmpx]== MINER) ||
    (Map[STAGE][tmpy+1][tmpx]==COMPUTER_MINE)) &&
    (collision_miners_miner(ptrelement,tmpy+1,tmpx,ptrelement->miner[i].id)==0))

    {
    ptrelement->miner[i].direction = 2;
    ptrelement->miner[i].angle=180;
    ptrelement->miner[i].section=MAX_Y/ptrelement->miner[i].step;
    }
    else
    {

    if (!(ptrelement->miner[i].id%ptrelement->miner[1].divider))
    {
    ptrelement->miner[i].random_direction=3;
    }
    else
    {
    ptrelement->miner[i].random_direction=1;
    }
    }
    };

    /* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING UP */


    if (ptrelement->miner[i].random_direction==0)
    {
    ptrelement->miner[i].angle=0;

    if(((Map[STAGE][tmpy-1][tmpx]==BACKGROUND) ||
    (Map[STAGE][tmpy-1][tmpx]== MINER) ||
    (Map[STAGE][tmpy-1][tmpx]==COMPUTER_MINE)) &&
    (collision_miners_miner(ptrelement,tmpy-1,tmpx,ptrelement->miner[i].id)==0))

    {
    ptrelement->miner[i].direction = 0;
    ptrelement->miner[i].angle=0;
    ptrelement->miner[i].section=MAX_Y/ptrelement->miner[i].step;
    }
    else
    {
    if (!(ptrelement->miner[i].id%ptrelement->miner[1].divider))
    {
    ptrelement->miner[i].random_direction=1;
    }
    else
    {
    ptrelement->miner[i].random_direction=3;
    }
    }
    };


    } // if direction 4
    } // if hit 0

    } // if player section

    } // if wait



    }

    } // for

} // of move_around()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void draw_enemy(float scale,TElement *ptrelement,BITMAP* buffer)
{

    int x,y,angle;
    int i;
    for(i=0;i<MAX_ENEMIES;i++)
    {
    x=ptrelement->enemy[i].x-ptrelement->player.shift_x;
    y=ptrelement->enemy[i].y-ptrelement->player.shift_y;
    angle=ptrelement->enemy[i].angle/90;

    if (ptrelement->enemy[i].hit==0)
    {
    masked_blit(ptrelement->enemy[i].bmptab[angle],buffer,0,0,x,y,MAX_X,MAX_Y);


    }; // if hit


    if (ptrelement->enemy[i].hit==1)
    {

    ptrelement->enemy[i].x=-50;
    ptrelement->enemy[i].y=-50;
    ptrelement->enemy[i].hit=2;



    };

    }; // for


 } // draw_enemy();



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// move enemy
int move_enemy(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)
{

    int i;

    for(i=0;i<MAX_ENEMIES;i++)

    {{

        if(ptrelement->enemy[i].wait==0)
    {{

    if (ptrelement->enemy[i].hit==0)

    {


    if  (ptrelement->enemy[i].x<(MARGIN_LEFT*MAX_X))
    {
    ptrelement->enemy[i].x=(MARGIN_LEFT*MAX_X); ptrelement->enemy[i].random_direction=(rand() % 4);  // zawroc w przypadkowy kierunek
    };

    if  (ptrelement->enemy[i].x>NUMBER_OF_SCREENS_X*SCREEN_w-(MARGIN_RIGHT*MAX_X)-MAX_X)
    {
    ptrelement->enemy[i].x=NUMBER_OF_SCREENS_X*SCREEN_w-(MARGIN_RIGHT*MAX_X)-MAX_X;ptrelement->enemy[i].random_direction=(rand() % 4);  // zawroc w przypadkowy kierunek
    };

    if  (ptrelement->enemy[i].y<(MARGIN_TOP*MAX_Y))
    {
    ptrelement->enemy[i].y=(MARGIN_TOP*MAX_Y);ptrelement->enemy[i].random_direction=(rand() % 4);  // zawroc w przypadkowy kierunek
    };

    if  (ptrelement->enemy[i].y>NUMBER_OF_SCREENS_Y*SCREEN_h-(MARGIN_BOTTOM*MAX_Y)-MAX_Y)
    {
    ptrelement->enemy[i].y=NUMBER_OF_SCREENS_Y*SCREEN_h-(MARGIN_BOTTOM*MAX_Y)-MAX_Y;ptrelement->enemy[i].random_direction=(rand() % 4);  // zawroc w przypadkowy kierunek
    };


    if ((ptrelement->enemy[i].section<=0))  { (ptrelement->enemy[i].direction=4);


    }

    if ((ptrelement->enemy[i].section>0))

    {

    switch (ptrelement->enemy[i].direction)
    {

    case 1: {ptrelement->enemy[i].x+=ptrelement->enemy[i].step; break;}     // step right
    case 2: {ptrelement->enemy[i].y+=ptrelement->enemy[i].step; break;}     // step down
    case 3: {ptrelement->enemy[i].x-=ptrelement->enemy[i].step; break;}     // step left
    case 0: {ptrelement->enemy[i].y-=ptrelement->enemy[i].step; break;}     // step up


    }; // from switch

    };

    if ((ptrelement->enemy[i].section)>0)
    {
    (ptrelement->enemy[i].section)--;
    };

    }; // if

    }};

    }}; // for

    return 0;

}; // move enemy();


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void move_enemy_around(TElement * ptrelement, int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)

{
    int i,tmpx,tmpy;
    int mouse_control=0;
    tmpx = 0;
    tmpy = 0;

    for(i=0;i<MAX_ENEMIES;i++)
    {

    if(ptrelement->enemy[i].wait==0)
    {

    // ATTENTION! ENEMY IS SAVED ON THE BOARD AND THE FIRST MOVE AFTER THE START SHOULD DELETE HIS STARTING POINT

    // if there is no remainder from division, that is integer values
    if  ((!(ptrelement->enemy[i].x%MAX_X)) &&(!(ptrelement->enemy[i].y%MAX_Y)))

    {
    tmpx=(ptrelement->enemy[i].x)/MAX_X;tmpy=(ptrelement->enemy[i].y)/MAX_Y;
    };

//if (ptrwait == 0)

    {
    if (ptrelement->enemy[i].section<=0)
    if (mouse_control==0)
    {

    /* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING LEFT */

    if (ptrelement->enemy[i].hit==0)
    {
    if (ptrelement->enemy[i].direction==4)
    {

    if (ptrelement->enemy[i].random_direction==3)
    {
    ptrelement->enemy[i].angle=270;

    if ((Map[STAGE][tmpy][tmpx-1]==BACKGROUND) ||
    (Map[STAGE][tmpy][tmpx-1]==ENEMY) ||
    (Map[STAGE][tmpy][tmpx-1]==COMPUTER_MINE))
    {
    ptrelement->enemy[i].direction = 3;
    ptrelement->enemy[i].angle=270;
    ptrelement->enemy[i].section=MAX_X/ptrelement->enemy[i].step;
    }
    else
    {

    if (!(ptrelement->enemy[i].id%ptrelement->enemy[1].divider))
    {
    ptrelement->enemy[i].random_direction=0;
    }
    else
    {
    ptrelement->enemy[i].random_direction=2;
    }
    }
    };

    /* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING RIGHT */

    if (ptrelement->enemy[i].random_direction==1)
    {
    ptrelement->enemy[i].angle=90;

    if((Map[STAGE][tmpy][tmpx+1]==BACKGROUND) ||
    (Map[STAGE][tmpy][tmpx+1]==ENEMY) ||
    (Map[STAGE][tmpy][tmpx+1]==COMPUTER_MINE))
    {
    ptrelement->enemy[i].direction = 1;
    ptrelement->enemy[i].angle=90;
    ptrelement->enemy[i].section=MAX_X/ptrelement->enemy[i].step;
    }
    else
    {
    if (!(ptrelement->enemy[i].id%ptrelement->enemy[1].divider))
    {
    ptrelement->enemy[i].random_direction=2;
    }
    else
    {
    ptrelement->enemy[i].random_direction=0;
    }
    }
    };

    /* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING DOWN */

    if (ptrelement->enemy[i].random_direction==2)
    {
    ptrelement->enemy[i].angle=180;

    if((Map[STAGE][tmpy+1][tmpx]==BACKGROUND) ||
    (Map[STAGE][tmpy+1][tmpx]== ENEMY) ||
    (Map[STAGE][tmpy+1][tmpx]==COMPUTER_MINE))
    {
    ptrelement->enemy[i].direction = 2;
    ptrelement->enemy[i].angle=180;
    ptrelement->enemy[i].section=MAX_Y/ptrelement->enemy[i].step;
    }
    else
    {
    if (!(ptrelement->enemy[i].id%ptrelement->enemy[1].divider))
    {
    ptrelement->enemy[i].random_direction=3;
    }
    else
    {
    ptrelement->enemy[i].random_direction=1;
    }
    }
    };
    /* GOES LEFT AND DRAWS A NEW DIRECTION
    GOES RIGHT AND DRAWS A NEW DIRECTION, ETC

    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    MOVING UP */

    if (ptrelement->enemy[i].random_direction==0)
    {
    ptrelement->enemy[i].angle=0;

    if((Map[STAGE][tmpy-1][tmpx]==BACKGROUND) ||
    (Map[STAGE][tmpy-1][tmpx]== ENEMY) ||
    (Map[STAGE][tmpy-1][tmpx]==COMPUTER_MINE))
    {
    ptrelement->enemy[i].direction = 0;
    ptrelement->enemy[i].angle=0;
    ptrelement->enemy[i].section=MAX_Y/ptrelement->enemy[i].step;
    }
    else
    {
    if (!(ptrelement->enemy[i].id%ptrelement->enemy[1].divider))
    {
    ptrelement->enemy[i].random_direction=1;
    }
    else
    {
    ptrelement->enemy[i].random_direction=3;
    }
    }
    };

    } // if direction
    } // ifhit

    } // if player section
    }  // if wait

    } // if(ptrelement->enemy[i].wait==0)

    };     // of for



} // end of move_around()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



