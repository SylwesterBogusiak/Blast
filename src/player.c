
#include "player.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int find_path(Tplayer *ptrplayer, TElement *ptrelement, BITMAP * buffer, int MazeMap[MAX_STAGE][MAP_Y][MAP_X], int stage, int TARGET_START, int TARGET_END)
{

    int x;
    int y;

    x = ptrplayer->x/MAX_X;
    y = ptrplayer->y/MAX_Y;

    get_maze(MazeMap,stage);
    get_visited();

    crumb = 0;
    if (dfs(ptrelement, y,x,TARGET_START,TARGET_END) == 1)

    {
     return 1;
    }

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void alloc_maze()
{

    int i;
	maze = malloc(MAP_Y * sizeof(int*));
	for (i = 0; i < MAP_Y; i++)
	{
    maze[i]=malloc(MAP_X * sizeof(int*));
    };
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void alloc_visited()
{
    int i;
	visited = malloc(MAP_Y * sizeof(int*));

	for (i = 0; i < MAP_Y; i++)
	{
    visited[i]=malloc(MAP_X * sizeof(int*));
    };
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int get_maze(int MazeMap[MAX_STAGE][MAP_Y][MAP_X],int stage)
{   int ax,ay;

    alloc_maze();

    for (ay=0;ay<MAP_Y;ay++)
    {
    for (ax=0;ax<MAP_X;ax++)
    {

    maze[ay][ax]=MazeMap[stage][ay][ax];

    }
    };

return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void get_visited()
{
    int i,j;

    alloc_visited();

    for ( i = 0; i < MAP_Y; i++)
    {
    for ( j = 0; j < MAP_X; j++)
    {
    visited[i][j] = maze[i][j];
    }
    };

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void print_maze(BITMAP *buffer)
{
    int i, j;


	for (i = 0; i < MAP_Y; i++)
	{
    for (j=0; j <MAP_X; j++)
    {

    textprintf_ex(buffer,font,j*MAX_X,i*MAX_Y,WHITE,-1,"%d  ",(maze[i][j]));

    }
    printf("\n");
	};
	printf("\n");
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void print_visited(BITMAP *buffer)
{
    int i, j;

	for (i = 0; i < MAP_Y; i++)
	{
    for (j=0; j <MAP_X; j++)
    {

    textprintf_ex(buffer,font,j*MAX_X,i*MAX_Y,WHITE,-1,"%d  ",(visited[i][j]));

    }
		printf("\n");
	};
	printf("\n");
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int dfs(TElement *ptrelement, int row, int col, int TARGET_START, int TARGET_END)
{

	int * current = &visited[row][col];

    if ((row>0) && (row<MAP_Y-1) && (col>0) && (col<MAP_X-1))
    {

    if (*current == TARGET_START)
    {
    ptrelement->target_row=row;
    ptrelement->target_col=col;

    return 1;
	}

    //if ((*current == BACKGROUND) )

    if ((ptrelement->player.ammo > 0 ) && (ptrelement->player.laser > 0 ))

    {

    if ((*current == BACKGROUND) || (*current == BLOCK) || (*current == BOMB) || (*current == MINER)
    || (*current == ENEMY) || (*current == ELECTRICLINEV) || (*current == ELECTRICLINEH))
    {
    //*current = crumb;
    *current = TARGET_END;

    if (dfs(ptrelement,row,col -1,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }

    if (dfs(ptrelement,row+1,col,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }

    if (dfs(ptrelement,row,col +1,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }

    if (dfs(ptrelement, row-1,col,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }
    }

    }

    else

    {

    if ((*current == BACKGROUND))
    {
    //*current = crumb;
    *current = TARGET_END;

    if (dfs(ptrelement,row,col -1,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }

    if (dfs(ptrelement,row+1,col,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }

    if (dfs(ptrelement,row,col +1,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }

    if (dfs(ptrelement, row-1,col,TARGET_START, TARGET_END))
    {
    crumb--;
    *current = crumb;
    return 1;
    }

	}

    } /// else no ammo nor laser

	}


    return 0;

} // dfs()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void draw_player(float scale,Tplayer *ptrplayer,BITMAP* buffer)
{

    static int x,y,angle=0;

    x=ptrplayer->x-ptrplayer->shift_x;
    y=ptrplayer->y-ptrplayer->shift_y;

    angle=ptrplayer->angle/90;     //angle (0-360)

    masked_blit(ptrplayer->bmptab[angle],buffer,0,0,x,y,MAX_X,MAX_Y);

    textprintf_ex(buffer,font,10,200,WHITE,-1,"Pos X : %d",(ptrplayer->x/MAX_X+1));
    textprintf_ex(buffer,font,10,220,WHITE,-1,"Pos Y : %d",(ptrplayer->y/MAX_Y+1));

} // draw_player()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void draw_fire(float scale, Tfire fires[MAX_FIRE],BITMAP* buffer, Tplayer *ptrplayer)
{


    int i;

    for (i=0;i<MAX_FIRE;i++)
    {
    if (fires[i].direction!=4 )
    {
    if(fires[i].type_of_weapon==1)                                  // laser
    {

    if ((fires[i].direction==0) || (fires[i].direction==2))
    {

    vline(buffer,fires[i].x-ptrplayer->shift_x+MAX_X/2,fires[i].y-ptrplayer->shift_y,fires[i].y-ptrplayer->shift_y+20,GREY);
    vline(buffer,fires[i].x-ptrplayer->shift_x+MAX_X/2-1,fires[i].y-ptrplayer->shift_y,fires[i].y-ptrplayer->shift_y+20,GREY);

    }

    if ((fires[i].direction==1) || (fires[i].direction==3))
    {
    hline(buffer,fires[i].x-ptrplayer->shift_x,fires[i].y-ptrplayer->shift_y+MAX_Y/2,fires[i].x-ptrplayer->shift_x+20,GREY);
    hline(buffer,fires[i].x-ptrplayer->shift_x,fires[i].y-ptrplayer->shift_y+MAX_Y/2+1,fires[i].x-ptrplayer->shift_x+20,GREY);
    }
    }

    else

    {

    masked_blit(fires[i].bmptab[fires[i].direction],buffer,0,0,fires[i].x-ptrplayer->shift_x,fires[i].y-ptrplayer->shift_y,MAX_Y,MAX_Y);

    };

    } // if
    }; // for

} // draw_fire()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void draw_explosion(float scale,Tplayer *ptrplayer,Texplosion explosions[MAX_EXPLOSION],BITMAP* buffer)
{
    int i;

    for (i=0;i<MAX_EXPLOSION;i++)
    {

    if (explosions[i].animate==1)
    {
    masked_blit(explosions[i].bmp,buffer,
    ((explosions[i].anim_count_x))*(explosions[i].bmp->w/8),
    ((explosions[i].anim_count_y))*(explosions[i].bmp->h/4),
    (explosions[i].x)-ptrplayer->shift_x,
    (explosions[i].y)-ptrplayer->shift_y,MAX_X,MAX_Y);
    }

    };

} // draw_explosion()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void collision_fire(TElement *ptrelement,Tfire fires[MAX_FIRE],Texplosion explosions[MAX_EXPLOSION],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE) //plansza

{

    int i,tmpx,tmpy;

    for (i=0;i<MAX_FIRE;i++)
    {

    if (fires[i].direction!=4)
    {

    if ((fires[i].x)<(MARGIN_LEFT*MAX_X) || (fires[i].x)>(NUMBER_OF_SCREENS_X)*SCREEN_w-(MARGIN_RIGHT*MAX_X)-MAX_X)
    {
    fires[i].direction=4;
    }
    if ((fires[i].y)<(MARGIN_TOP*MAX_Y) || (fires[i].y)>(NUMBER_OF_SCREENS_Y)*SCREEN_h-(MARGIN_BOTTOM*MAX_Y)-MAX_Y)
    {
    fires[i].direction=4;
    }
    }



    if (fires[i].direction!=4)

    if  ((!(fires[i].x%MAX_X)) &&(!(fires[i].y%MAX_Y)))
    {{

    tmpx=(fires[i].x)/MAX_X;tmpy=(fires[i].y)/MAX_Y;

    if (Map[STAGE][tmpy][tmpx]==SLANTLROTATE)
    {
    Map[STAGE][tmpy][tmpx]=SLANTRROTATE;

    if (fires[i].direction==0)
    {fires[i].direction=3;goto tu4; }

    if (fires[i].direction==1)
    {fires[i].direction=2;goto tu4; }

    if (fires[i].direction==2)
    {fires[i].direction=1;goto tu4; }

    if (fires[i].direction==3)
    {fires[i].direction=0;goto tu4; }

    };

    // tu3:

    if (Map[STAGE][tmpy][tmpx]==SLANTRROTATE)
    {
    Map[STAGE][tmpy][tmpx]=SLANTLROTATE;

    if (fires[i].direction==0)
    {fires[i].direction=1;goto tu4; }

    if (fires[i].direction==1)
    {fires[i].direction=0;goto tu4; }

    if (fires[i].direction==2)
    {fires[i].direction=3;goto tu4; }

    if (fires[i].direction==3)
    {fires[i].direction=2;goto tu4; }
    };

    tu4 :

    if (Map[STAGE][tmpy][tmpx]==SLANTL)

    {

    if (fires[i].direction==0)
    {fires[i].direction=3;goto tu; }

    if (fires[i].direction==1)
    {fires[i].direction=2;goto tu; }

    if (fires[i].direction==2)
    {fires[i].direction=1;goto tu; }

    if (fires[i].direction==3)
    {fires[i].direction=0;goto tu; }

    };

    tu:

    if (Map[STAGE][tmpy][tmpx]==SLANTR)
    {
    if (fires[i].direction==0)
    {fires[i].direction=1;goto tu2; }

    if (fires[i].direction==1)
    {fires[i].direction=0;goto tu2; }

    if (fires[i].direction==2)
    {fires[i].direction=3;goto tu2; }

    if (fires[i].direction==3)
    {fires[i].direction=2;goto tu2; }

    };

    tu2 :

    if (Map[STAGE][tmpy][tmpx]==STAR)
    {
    if (fires[i].type_of_weapon==0)
    {
    explosion(ptrelement,ptrelement->player.explosions,tmpx*MAX_X,tmpy*MAX_Y);
    Map[STAGE][tmpy][tmpx]=0;
    if (ptrelement->player.ammo>0)
    {
    ptrelement->player.find_object=STAR;                            // 0 - not find, > 0 find
    }
    else
    {
    ptrelement->player.find_object=WEAPONRECHARGER;                 // 0 - not find, > 0 find
    }

    ptrelement->player.stars_left--;
    ptrelement->player.points+=5;
    }

    fires[i].direction=4;

    };


    if (Map[STAGE][tmpy][tmpx]==BLOCK)
    {

    explosion(ptrelement,ptrelement->player.explosions,tmpx*MAX_X,tmpy*MAX_Y);

    Map[STAGE][tmpy][tmpx]=0;

    fires[i].direction=4;
    ptrelement->player.points+=1;
    //play_sample(explosions[index_explozji].spl,100,127,1000,0);

    };

    if (Map[STAGE][tmpy][tmpx]==WALL)

    {
    fires[i].direction=4;
    };

    if (Map[STAGE][tmpy][tmpx]==QUAD)

    {
    switch(fires[i].direction)
    {

    case 0 :
    {
    fires[i].direction=4;

    if((tmpy-1)>=0)
    {

    if(Map[STAGE][tmpy-1][tmpx]==0)

    if ((collision_miners_element (ptrelement,Map,tmpx,tmpy-1,STAGE)==0) &&(!collision_enemies_element(ptrelement,Map,tmpx,tmpy-1,STAGE)))
    {
    Map[STAGE][tmpy][tmpx]=0; Map[STAGE][tmpy-1][tmpx]=QUAD;
    }
    };

    break;
    };

    case 1 :
    {
    fires[i].direction=4;

    if((tmpx+1)<MAP_X)
    {
    if(Map[STAGE][tmpy][tmpx+1]==0)
    {
    if ((collision_miners_element (ptrelement,Map,tmpx+1,tmpy,STAGE)==0) &&(!collision_enemies_element(ptrelement,Map,tmpx+1,tmpy,STAGE)))         // kolizja miner_element sprawdza sie
    {
    Map[STAGE][tmpy][tmpx]=0; Map[STAGE][tmpy][tmpx+1]=QUAD;
    }
    }
    };
    break;
    };

    case 3 :
    {
    fires[i].direction=4;

    if((tmpx-1)>=0)
    {
    if(Map[STAGE][tmpy][tmpx-1]==0)
    {
    if ((collision_miners_element (ptrelement,Map,tmpx-1,tmpy,STAGE)==0) &&(!collision_enemies_element(ptrelement,Map,tmpx-1,tmpy,STAGE)))         // kolizja miner_element sprawdza sie
    {
    Map[STAGE][tmpy][tmpx]=0; Map[STAGE][tmpy][tmpx-1]=QUAD;
    }
    }
    };
    break;
    };

    case 2 :
    {
    fires[i].direction=4;

    if((tmpy+1)<MAP_Y)
    {
    if(Map[STAGE][tmpy+1][tmpx]==0)
    {
    if ((collision_miners_element (ptrelement,Map,tmpx,tmpy+1,STAGE)==0) &&(!collision_enemies_element(ptrelement,Map,tmpx,tmpy+1,STAGE)))         // kolizja miner_element sprawdza sie
    {
    Map[STAGE][tmpy][tmpx]=0; Map[STAGE][tmpy+1][tmpx]=QUAD;
    }
    }
    };
    break;
    };


    }; // switch

    fires[i].direction=4;

    }; // if


    if (Map[STAGE][tmpy][tmpx]==BOMB)
    {
    if (fires[i].type_of_weapon==1)
    {check_bomb(ptrelement,ptrelement->player.explosions,tmpx,tmpy,STAGE);
    }

    fires[i].direction=4;

    }; // if


    if (Map[STAGE][tmpy][tmpx]==WALLOFFH)                   // break the switch, only destroys laser 1
    {
    if (fires[i].type_of_weapon==1)
    {
    Map[STAGE][tmpy][tmpx]=WALL;                            // view wall
    check_electriclineH(ptrelement,tmpx,tmpy,STAGE);        // check if there is an electric line
    }
    fires[i].direction=4;

    }; // if

    if (Map[STAGE][tmpy][tmpx]==WALLOFFV)                   // break the switch, only destroys laser 1
    {
    if (fires[i].type_of_weapon==1)
    {
    Map[STAGE][tmpy][tmpx]=WALL;                            // view wall
    check_electriclineV(ptrelement,tmpx,tmpy,STAGE);        // check if there is an electric line
    }
    fires[i].direction=4;

    }; // if


    if (fires[i].type_of_weapon==1) if (Map[STAGE][tmpy][tmpx]==COMPUTER_MINE)
    {

    explosion(ptrelement,ptrelement->player.explosions,tmpx*MAX_X,tmpy*MAX_Y);

    Map[STAGE][tmpy][tmpx]=0;
    fires[i].direction=4;
    ptrelement->player.points+=1;

    };




    }} //




    }; // for


}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int check_electriclineV(TElement *ptrelement,int tmpx,int tmpy,int STAGE)
{
    int i;

    for (i=-1;i<2;i++)
    {
    if (Map[STAGE][tmpy+i][tmpx]==ELECTRICLINEV)                        // LINE works - turn it off
    {
    Map[STAGE][tmpy+i][tmpx]=BACKGROUND;
    check_electriclineV(ptrelement,tmpx,tmpy+i,STAGE);
    }
    };

    return 0;
} // check_electriclineV()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//

int check_electriclineH(TElement *ptrelement,int tmpx,int tmpy,int STAGE)
{

    int i=0;


    for (i=-1;i<2;i++)
    {
    if (Map[STAGE][tmpy][tmpx+i]==ELECTRICLINEH)                        // LINE works - turn it off
    {
    Map[STAGE][tmpy][tmpx+i]=BACKGROUND;
    check_electriclineH(ptrelement,tmpx+i,tmpy,STAGE);
    }
    };

    return 0;
} // check_electriclineH()



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int check_bomb(TElement *ptrelement,Texplosion explosions[MAX_EXPLOSION],int tmpx,int tmpy,int STAGE)
{
    int i,j;

    for (i=-1;i<2;i++)
    {

    if((tmpy+i>=0) && (tmpy+i<MAP_Y))
    {
    if (Map[STAGE][tmpy+i][tmpx]==BOMB)
    {
    explosion(ptrelement,ptrelement->player.explosions,tmpx*MAX_X,(tmpy+i)*MAX_Y);
    Map[STAGE][tmpy+i][tmpx]=0;
    check_bomb(ptrelement,ptrelement->player.explosions,tmpx,tmpy+i,STAGE);

    };

    if (Map[STAGE][tmpy+i][tmpx]==QUAD)
    {

    explosion(ptrelement,ptrelement->player.explosions,tmpx*MAX_X,(tmpy+i)*MAX_Y);
    Map[STAGE][tmpy+i][tmpx]=0;

    };

    } // if
    }; // for


    for (j=-1;j<2;j++)
    {

    if((tmpx+j>=0) && (tmpx+j<MAP_Y))
    {
    if (Map[STAGE][tmpy][tmpx+j]==BOMB)
    {
    explosion(ptrelement,ptrelement->player.explosions,(tmpx+j)*MAX_X,tmpy*MAX_Y);
    Map[STAGE][tmpy][tmpx+j]=0;
    check_bomb(ptrelement,ptrelement->player.explosions,tmpx+j,tmpy,STAGE);
    };

    if (Map[STAGE][tmpy][tmpx+j]==QUAD)
    {
    explosion(ptrelement,ptrelement->player.explosions,(tmpx+j)*MAX_X,tmpy*MAX_Y);
    Map[STAGE][tmpy][tmpx+j]=0;
    };
    } // if
    }; // for

    return 1;
} // check_bomb()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void move_player(Tplayer *ptrplayer, int demo)
{

    if (ptrplayer->wait==0)
    {
    if ((demo==2))
    {
    if (ptrplayer->change_direction == 1)
    if ((ptrplayer->direction==4))
    {
    ptrplayer->direction = (rand() % 4);
    ptrplayer->angle = ptrplayer->direction * 90;
    ptrplayer->section=MAX_X/ptrplayer->step;
    }
    }

    {

    if ((ptrplayer->section<=0))
    {
    (ptrplayer->direction=4);
    }


    if ((ptrplayer->section>0))

    switch (ptrplayer->direction)
    {
    case 1:
    {
    ptrplayer->x+=ptrplayer->step;

    if (ptrplayer->x>SCREEN_w*NUMBER_OF_SCREENS_X-MAX_X)
    {
    ptrplayer->x=SCREEN_w*NUMBER_OF_SCREENS_X-MAX_X;
    ptrplayer->section=0;
    }
    else
    if (ptrplayer->x > (ptrplayer->shift_x+SCREEN_w-MAX_X-camera.x_right))
    {
    if (ptrplayer->shift_x < ((SCREEN_w*(NUMBER_OF_SCREENS_X)-SCREEN_w)))
    {
    ptrplayer->shift_x+=ptrplayer->step;
    }
    }

    break;
    };

    case 2:
    {
    ptrplayer->y+=ptrplayer->step;

    if (ptrplayer->y>SCREEN_h*NUMBER_OF_SCREENS_Y-MAX_Y)
    {ptrplayer->y=SCREEN_h*NUMBER_OF_SCREENS_Y-MAX_Y;
    ptrplayer->section=0;
    }

    else
    if (ptrplayer->y > (ptrplayer->shift_y+SCREEN_h-MAX_Y-camera.y_bottom))
    {
    if (ptrplayer->shift_y <((SCREEN_h*(NUMBER_OF_SCREENS_Y))-SCREEN_h))
    {
    ptrplayer->shift_y+=ptrplayer->step;
    }

    }
    break;
    };

   case 3:
   {
   ptrplayer->x-=ptrplayer->step;

    if  (ptrplayer->x<(MARGIN_LEFT*MAX_X))
    {
    ptrplayer->x=(MARGIN_LEFT*MAX_X);
    ptrplayer->section=0;
    }
    else
    if (ptrplayer->x < ptrplayer->shift_x+(MARGIN_LEFT*MAX_X)+camera.x_left)
    {

    if (ptrplayer->shift_x >(MARGIN_LEFT*MAX_X))
    {
    ptrplayer->shift_x-=ptrplayer->step;
    }

    }

    break;
    };

   // up
   case 0:
   {
    ptrplayer->y-=ptrplayer->step;

    if  (ptrplayer->y<(MARGIN_TOP*MAX_Y))
    {
    ptrplayer->y=(MARGIN_TOP*MAX_Y);
    ptrplayer->section=0;
    }
    else
    if (ptrplayer->y < ptrplayer->shift_y+(MARGIN_TOP*MAX_Y)+camera.y_top)
    {
    if (ptrplayer->shift_y >(MARGIN_TOP*MAX_Y))
    {
    ptrplayer->shift_y-=ptrplayer->step;
    }
    }

    break;
    };

    }; // switch

    if ((ptrplayer->section)>0)
    {
    (ptrplayer->section)--;
    }


    }

    }
    ptrplayer->wait=1;


} // move_player()



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int collision_player(TElement *ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)

{
    // ONLY STATIC ELEMENTS
    int tmpx,tmpy;

    if  ((!(ptrelement->player.x%MAX_X)) &&(!(ptrelement->player.y%MAX_Y)))
    {{
    tmpx=(ptrelement->player.x)/MAX_X;tmpy=(ptrelement->player.y)/MAX_Y;



    if (Map[STAGE][tmpy][tmpx]==WEAPONRECHARGER)
    {
    Map[STAGE][tmpy][tmpx]=0;
    ptrelement->player.ammo+=20;
    ptrelement->player.laser+=10;
    ptrelement->player.find_object=WEAPONRECHARGER;

    return WEAPONRECHARGER;
    };  //weaponrecharger



    if ((Map[STAGE][tmpy][tmpx]==ELECTRICLINEH) || (Map[STAGE][tmpy][tmpx]==ELECTRICLINEV))
    {
    return 1;
    };  //electricline

    if ((Map[STAGE][tmpy][tmpx]==COMPUTER_MINE))
    {
    return 1;   //chyba dziala
    }; // mine


    }};


    return 0;

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int explosion(TElement *ptrelement,Texplosion explosions[MAX_EXPLOSION],int tmpx,int tmpy)
{
    static int index_explozji;

    index_explozji++;
    if (index_explozji>=MAX_EXPLOSION)
    {
    index_explozji=0;
    }
    explosions[index_explozji].anim_count_x=0;
    explosions[index_explozji].anim_count_y=0;
    explosions[index_explozji].x=tmpx;
    explosions[index_explozji].y=tmpy;
    explosions[index_explozji].animate=1;

return 0;

} // explosion()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int player_control(Tplayer *ptrplayer,Tfire fires[MAX_FIRE],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)

{

// ultimately make a record on the board by summing up the characters
// and handle all collision events in one function
// player eg number 200, objects with which it can overlap
// numbers above 50 - if the field is >250, handle collisions accordingly

    static int tmpx,tmpy;
    static int space=0;                                         // space marker: 1 = pressed, 0 = not
    static int enter=0;                                         // enter marker: 1 = pressed, 0 = not
    int mouse_control=0;
    static int index_fire=0;

    if ((!(ptrplayer->x%MAX_X)) &&(!(ptrplayer->y%MAX_Y)))
    {
    tmpx=(ptrplayer->x)/MAX_X;tmpy=(ptrplayer->y)/MAX_Y;
    }

    if (ptrplayer->section<=0)
    {
    if (mouse_control==0)
    {

    if (controller==wsad)
    {
    if(key[KEY_LCONTROL] && key[KEY_A])
    {
    ptrplayer->angle=270;
    }

    if(key[KEY_LCONTROL] && key[KEY_D])
    {
    ptrplayer->angle=90;
    }

    if(key[KEY_LCONTROL] && key[KEY_W])
    {
    ptrplayer->angle=0;
    }

    if(key[KEY_LCONTROL] && key[KEY_S])
    {
    ptrplayer->angle=180;
    }
    }; // if


    if (controller==arrows)
    {
    if(key[KEY_LCONTROL] && key[KEY_LEFT])
    {
    ptrplayer->angle=270;
    }

    if(key[KEY_LCONTROL] && key[KEY_RIGHT])
    {
    ptrplayer->angle=90;
    }

    if (key[KEY_LCONTROL] && key[KEY_UP])
    {
    ptrplayer->angle=0;
    }

    if(key[KEY_LCONTROL] && key[KEY_DOWN])
    {
    ptrplayer->angle=180;
    }
    }; // if


    if (controller==joypad)
    {
    if (joy[0].stick[1].axis[0].d1)
    {
    ptrplayer->angle=270;
    }

    if (joy[0].stick[1].axis[0].d2)
    {
    ptrplayer->angle=90;
    }

    if (joy[0].stick[1].axis[1].d1)
    {
    ptrplayer->angle=0;
    }

    if (joy[0].stick[1].axis[1].d2)
    {
    ptrplayer->angle=180;
    }

    // if (joy[0].button[1].b)

    }; // if
    // end

    // moves on empty background or steps on weapon recharge, computer mine or weapon recharger

    if (!key[KEY_LCONTROL])
    {
    if (((!key[KEY_D]) && (controller==wsad)) ||
    ((!key[KEY_RIGHT]) && (controller==arrows)) ||
    (controller==joypad)
    )
    {
    if (ptrplayer->direction==4)
    {
    if (((( key[KEY_A]) && (controller==wsad)) ||
    ((key[KEY_LEFT]) && (controller==arrows))) ||
    (joy[0].stick[0].axis[0].d1))
    {

    ptrplayer->angle=270;
    if((Map[STAGE][tmpy][tmpx-1]==BACKGROUND
    || Map[STAGE][tmpy][tmpx-1]==WEAPONRECHARGER
    || Map[STAGE][tmpy][tmpx-1]==ELECTRICLINEH
    || Map[STAGE][tmpy][tmpx-1]==ELECTRICLINEV
    || Map[STAGE][tmpy][tmpx-1]==COMPUTER_MINE
    ))
    {
    ptrplayer->direction = 3;
    ptrplayer->angle=270;
    ptrplayer->section=MAX_X/ptrplayer->step;

    } // if
    } // if
    } // if
    } // if
    }; // if








    if(!key[KEY_LCONTROL])
    {
    if(((!key[KEY_A]) && (controller==wsad)) ||
    ((!key[KEY_LEFT]) && (controller==arrows)) ||
    (controller==joypad)
    )
    {
    if (ptrplayer->direction==4)
    {
    if ((((key[KEY_D]) && (controller==wsad)) ||
    ((key[KEY_RIGHT]) && (controller==arrows))) ||
    (joy[0].stick[0].axis[0].d2))
    {
    ptrplayer->angle=90;
    if((Map[STAGE][tmpy][tmpx+1]==BACKGROUND
    || Map[STAGE][tmpy][tmpx+1]==WEAPONRECHARGER
    || Map[STAGE][tmpy][tmpx+1]==ELECTRICLINEV
    || Map[STAGE][tmpy][tmpx+1]==ELECTRICLINEH
    || Map[STAGE][tmpy][tmpx+1]==COMPUTER_MINE
    ))
    {
    ptrplayer->direction = 1;
    ptrplayer->angle=90;
    ptrplayer->section=MAX_X/ptrplayer->step;
    } // if
    } // if
    } // if
    } // if
    }; // if


    if(!key[KEY_LCONTROL])
    {
    if(((!key[KEY_W]) && (controller==wsad)) ||
    ((!key[KEY_UP]) && (controller==arrows)) ||
    (controller==joypad)
    )
    {
    if (ptrplayer->direction==4)
    {
    if((((key[KEY_S]) && (controller==wsad)) ||
    ((key[KEY_DOWN]) && (controller==arrows))) ||
    (joy[0].stick[0].axis[1].d2))
    {
    ptrplayer->angle=180;

    if((Map[STAGE][tmpy+1][tmpx]==BACKGROUND
    || Map[STAGE][tmpy+1][tmpx]==WEAPONRECHARGER
    || Map[STAGE][tmpy+1][tmpx]==ELECTRICLINEH
    || Map[STAGE][tmpy+1][tmpx]==ELECTRICLINEV
    || Map[STAGE][tmpy+1][tmpx]==COMPUTER_MINE
    ))

    {
    ptrplayer->direction = 2;
    ptrplayer->angle=180;
    ptrplayer->section=MAX_Y/ptrplayer->step;
    } // if
    } // if
    } // if
    } // if
    }; // if


    if(!key[KEY_LCONTROL])
    {
    if(((!key[KEY_S]) && (controller==wsad)) ||
    ((!key[KEY_DOWN]) && (controller==arrows)) ||
    (controller==joypad)
    )
    {
    if (ptrplayer->direction==4)
    {
    if ((((key[KEY_W]) && (controller==wsad)) ||
    ((key[KEY_UP]) && (controller==arrows))) ||
    (joy[0].stick[0].axis[1].d1))
    {
    ptrplayer->angle=0;

    if((Map[STAGE][tmpy-1][tmpx]==BACKGROUND
    || Map[STAGE][tmpy-1][tmpx]==WEAPONRECHARGER
    || Map[STAGE][tmpy-1][tmpx]==ELECTRICLINEH
    || Map[STAGE][tmpy-1][tmpx]==ELECTRICLINEV
    || Map[STAGE][tmpy-1][tmpx]==COMPUTER_MINE
    ))
    {
    ptrplayer->direction = 0;
    ptrplayer->angle=0;
    ptrplayer->section=MAX_Y/ptrplayer->step;
    } // if
    } // if
    } // if
    } // if
    }; // if

    if (controller==wsad)
    {
    if(!(key[KEY_SPACE]))
    {
    if (space>0)
    {
    space--;
    }
    }
    };

    if (controller==arrows)
    {
    if(!(key[KEY_SPACE]))
    {
    if (space>0)
    {
    space--;
    }
    }
    };


    if (controller==joypad)
    {
    if (!(joy[0].button[1].b))
    {
    if (space>0)
    {
    space--;
    }
    }
    };

    if(space<=0)
    {
    if(((controller==wsad)&&(key[KEY_SPACE])) ||
    ((controller==arrows)&&(key[KEY_SPACE])) ||
    ((controller==joypad)&&(joy[0].button[1].b)))
    {
    if (ptrplayer->ammo>0)
    {
    space=5;                                                                                // timing for next shoot
    ptrplayer->ammo--;
    index_fire++;
    if (index_fire>=MAX_FIRE)
    {
    index_fire=0;
    }

    fires[index_fire].direction=ptrplayer->angle/90;
    fires[index_fire].x=ptrplayer->x;
    fires[index_fire].y=ptrplayer->y;
    fires[index_fire].type_of_weapon=0;                                                     // 0 ammo , 1 laser

    }
    }
    }; // if space



    if (controller==wsad)
    {
    if(!(key[KEY_RCONTROL]))
    {
    if (enter>0)
    {
    enter--;
    }
    }
    }; // if

    if (controller==arrows)
    {
    if(!(key[KEY_RCONTROL]))
    {
    if (enter>0)
    {
    enter--;
    }
    }
    }; // if


    if (controller==joypad)
    {
    if (!(joy[0].button[2].b))
    {
    if (enter>0)
    {
    enter--;
    }
    }
    }; // if

    if(enter<=0)
    {
    if(((controller==wsad)&&(key[KEY_RCONTROL])) ||
    ((controller==arrows)&&(key[KEY_RCONTROL])) ||
    ((controller==joypad)&&(joy[0].button[2].b)))
    {
    if (ptrplayer->laser>0)
    {
    enter=20;                                                                                   // timing for next shoot
    // play_sample(spl_gunfire,127,127,1000,0);
    ptrplayer->laser--;

    index_fire++;
    if (index_fire>=MAX_FIRE)
    {
    index_fire=0;
    }

    fires[index_fire].direction=ptrplayer->angle/90;
    fires[index_fire].x=ptrplayer->x;
    fires[index_fire].y=ptrplayer->y;
    fires[index_fire].type_of_weapon=1;                                                         // 0 ammo, 1 laser
    }
    }
    }; // if enter


    }
    } // if player section

    return 0;
} // player_control()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int collision_miners_fires (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)
{
    static int x1,y1,x2,y2,i,j;

    int centrX=10,centrY=10; // polowa MAX_X

#define FIRST 0


    for (j=0;j<MAX_FIRE;j++)
    {

    if(ptrelement->player.fires[j].direction!=4)    //WAZNE !!! inaczej problemy z kolizjami
    {
    x1=ptrelement->player.fires[j].x;
    y1=ptrelement->player.fires[j].y;

    for (i=FIRST;i<MAX_COMP;i++)
    {
    x2=ptrelement->miner[i].x;
    y2=ptrelement->miner[i].y;

    // IMPORTANT X2,Y2 IN THE MIDDLE (i.e. PLAYER)

    for(centrX=-5;centrX<5;centrX++)
    for(centrY=-5;centrY<5;centrY++)

    if ((x2+MAX_X/2+centrX>=x1) && (x2+MAX_X/2+centrX<=x1+MAX_X)
    &&(y2+MAX_Y/2+centrY>=y1)&&(y2+MAX_Y/2+centrY<=(y1+MAX_Y)))

    {
    ptrelement->miner[i].direction=4;
    ptrelement->miner[i].hit=1;
    ptrelement->player.fires[j].x=-100;
    ptrelement->player.fires[j].y=-100;
    ptrelement->player.fires[j].direction=4;
    ptrelement->player.points+=5;

    explosion(ptrelement,ptrelement->player.explosions,x2,y2);
    return 1;
                                          }
    }; // for

    }
    }; // for



    return 0;
} // collision_miners_fires()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
void move_fires(Tfire fires[MAX_FIRE])
{
    int i;
    for (i=0;i<MAX_FIRE;i++)
    {
    if (fires[i].direction!=4)
    {
    if (fires[i].wait == 0)
    {
    if(fires[i].type_of_weapon==0)
    {
    switch (fires[i].direction)                                                                 // laser speed
    {
    case 1: {fires[i].x+=fires[i].step; break;}     // right
    case 2: {fires[i].y+=fires[i].step; break;}     // down
    case 3: {fires[i].x-=fires[i].step; break;}     // left
    case 0: {fires[i].y-=fires[i].step; break;}     // up

    }; // switch

    } // if

    if(fires[i].type_of_weapon==1)                                                              // laser speed
    {
    switch (fires[i].direction)
    {
    case 1: {fires[i].x+=fires[i].step2; break;}     // right
    case 2: {fires[i].y+=fires[i].step2; break;}     // down
    case 3: {fires[i].x-=fires[i].step2; break;}     // left
    case 0: {fires[i].y-=fires[i].step2; break;}     // up

    }; // switch

    } // if

    } // if

    }; // if

    }; // for

} // move_fires()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int collision_miners_player (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)
{
    static int x1,y1,x2,y2,i;
    static int centrX=3,centrY=3;


    x1=ptrelement->player.x;
    y1=ptrelement->player.y;

    for (i=0;i<MAX_COMP;i++)
    {
    x2=ptrelement->miner[i].x;
    y2=ptrelement->miner[i].y;

    for(centrX=-5;centrX<5;centrX++)
    {
    for(centrY=-5;centrY<5;centrY++)
    {
    if ((x2+MAX_X/2+centrX>=x1) && (x2+MAX_X/2+centrX<=x1+MAX_X)
    &&(y2+MAX_Y/2+centrY>=y1)&&(y2+MAX_Y/2+centrY<=(y1+MAX_Y)))
    {
    ptrelement->miner[i].direction=4;
    return 1;
    }
    }; // for
    }; // for
    }; // for

    return 0;
} // collision_miners_player()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int collision_miners_element (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int tmpx,int tmpy, int STAGE)
{

    static int x1,y1,x2,y2,i;
    static int centrX=3,centrY=3;

    x1=tmpx*MAX_X;
    y1=tmpy*MAX_Y;

    for (i=0;i<MAX_COMP;i++)
    {
    x2=ptrelement->miner[i].x;
    y2=ptrelement->miner[i].y;


    for(centrX=-5;centrX<5;centrX++)
    {
    for(centrY=-5;centrY<5;centrY++)
    {
    if ((x2+MAX_X/2+centrX>=x1) && (x2+MAX_X/2+centrX<=x1+MAX_X)
    &&(y2+MAX_Y/2+centrY>=y1)&&(y2+MAX_Y/2+centrY<=(y1+MAX_Y)))
    {
    return 1;
    }
    }; // for
    }; // for
    }; // for

    return 0;
} // collision_miners_element()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// function OFF

int collision_miners_miner (TElement *ptrelement,int tmpy, int tmpx, int index_miner)

{
    static int x1,y1,x2,y2,i;
    static int centrX=3,centrY=3;

    return 0;


    //for (j=0;j<MAX_COMP;j++)
    {

    // if ((ptrelement->miner[j].id>0))
    {
    x1=tmpx*MAX_X;
    y1=tmpy*MAX_Y;
    }

    for (i=0;i<MAX_COMP;i++)
    {
    x2=ptrelement->miner[i].x;
    y2=ptrelement->miner[i].y;


    for(centrX=-5;centrX<5;centrX++)
    {
    for(centrY=-5;centrY<5;centrY++)
    {
    if ((x2+MAX_X/2+centrX>=x1) && (x2+MAX_X/2+centrX<=x1+MAX_X)
    &&(y2+MAX_Y/2+centrY>=y1)&&(y2+MAX_Y/2+centrY<=(y1+MAX_Y)))
    {
    return 1;
    }; // if
    }; // for
    }; // for
    }; // for
    };


    return 0;
} // collision_miners_miner ()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int collision_enemies_fires (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)
{
    static int x1,y1,x2,y2,i,j;

    int centrX=10,centrY=10;

#define FIRST 0


    for (j=0;j<MAX_FIRE;j++)
    {

    if(ptrelement->player.fires[j].direction!=4)
    {
    x1=ptrelement->player.fires[j].x;
    y1=ptrelement->player.fires[j].y;

    for (i=FIRST;i<MAX_ENEMIES;i++)
    {
    x2=ptrelement->enemy[i].x;
    y2=ptrelement->enemy[i].y;


    for(centrX=-5;centrX<5;centrX++)
    {
    for(centrY=-5;centrY<5;centrY++)
    {
    if ((x2+MAX_X/2+centrX>=x1) && (x2+MAX_X/2+centrX<=x1+MAX_X)
    &&(y2+MAX_Y/2+centrY>=y1)&&(y2+MAX_Y/2+centrY<=(y1+MAX_Y)))

    {
    ptrelement->enemy[i].direction=4;
    ptrelement->enemy[i].hit=1;
    ptrelement->player.fires[j].x=-100;
    ptrelement->player.fires[j].y=-100;
    ptrelement->player.fires[j].direction=4;
    ptrelement->player.points+=5;

    explosion(ptrelement,ptrelement->player.explosions,x2,y2);


    return 1;
    } // if
    }; // for
    }; // for
    }; // for

    }; // if

    }; // for

    return 0;
} // collision_enemies_fires()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//

int collision_enemies_player (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE)
{
    static int x1,y1,x2,y2,i;
    static int centrX=3,centrY=3;




    x1=ptrelement->player.x;
    y1=ptrelement->player.y;

    for (i=0;i<MAX_ENEMIES;i++)
    {
    x2=ptrelement->enemy[i].x;
    y2=ptrelement->enemy[i].y;




    for(centrX=-5;centrX<5;centrX++)
    {
    for(centrY=-5;centrY<5;centrY++)
    {
    if ((x2+MAX_X/2+centrX>=x1) && (x2+MAX_X/2+centrX<=x1+MAX_X)
    &&(y2+MAX_Y/2+centrY>=y1)&&(y2+MAX_Y/2+centrY<=(y1+MAX_Y)))

    {
    ptrelement->enemy[i].direction=4;
    return 1;
    }
    }; // for
    }; // for
    }; // for

   return 0;
} // collision_enemies_player()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int collision_enemies_element (TElement *ptrelement,int E_Map[MAX_STAGE][MAP_Y][MAP_X],int tmpx,int tmpy, int STAGE)
{
    static int x1,y1,x2,y2,i;
    static int centrX=3,centrY=3;

    x1=tmpx*MAX_X;
    y1=tmpy*MAX_Y;

    for (i=0;i<MAX_ENEMIES;i++)
    {
    x2=ptrelement->enemy[i].x;
    y2=ptrelement->enemy[i].y;
    {

    for(centrX=-5;centrX<5;centrX++)
    {
    for(centrY=-5;centrY<5;centrY++)
    {
    if ((x2+MAX_X/2+centrX>=x1) && (x2+MAX_X/2+centrX<=x1+MAX_X)
    &&(y2+MAX_Y/2+centrY>=y1)&&(y2+MAX_Y/2+centrY<=(y1+MAX_Y)))
    {
    return 1;
    } // if
    }; // for
    };
    };
    };
    return 0;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//

int follow_path_to_target(Tplayer *ptrplayer,Tfire fires[MAX_FIRE],int Map[MAX_STAGE][MAP_Y][MAP_X],int STAGE, int TARGET)
{
    static int tmpx,tmpy;
    static int space=0;
    static int r_control=0;


    static int index_fire=0;


    if ((!(ptrplayer->x%MAX_X)) &&(!(ptrplayer->y%MAX_Y)))
    {
    tmpx=(ptrplayer->x)/MAX_X;tmpy=(ptrplayer->y)/MAX_Y;
    }

    if (ptrplayer->section<=0)


    {

    if (CRUMB<0)
    {
    // up
    if (ptrplayer->direction==4)
    {
    if((visited[tmpy-1][tmpx]==CRUMB)
    &&( Map[STAGE][tmpy-1][tmpx]==BACKGROUND
    || Map[STAGE][tmpy-1][tmpx]==WEAPONRECHARGER
    //|| Map[STAGE][tmpy-1][tmpx]==ELECTRICLINEH
    //|| Map[STAGE][tmpy-1][tmpx]==ELECTRICLINEV
    || Map[STAGE][tmpy-1][tmpx]==COMPUTER_MINE
    ))
    {
    CRUMB++;
    ptrplayer->direction = 0;
    ptrplayer->angle=0;
    ptrplayer->section=MAX_Y/ptrplayer->step;
    }
    }

    // right
    if (ptrplayer->direction==4)
    {
    if((visited[tmpy][tmpx+1]==CRUMB)
    &&( Map[STAGE][tmpy][tmpx+1]==BACKGROUND
    || Map[STAGE][tmpy][tmpx+1]==WEAPONRECHARGER
    //|| Map[STAGE][tmpy][tmpx+1]==ELECTRICLINEH
    //|| Map[STAGE][tmpy][tmpx+1]==ELECTRICLINEV
    || Map[STAGE][tmpy][tmpx+1]==COMPUTER_MINE
    ))
    {
    CRUMB++;

    ptrplayer->direction = 1;
    ptrplayer->angle=90;
    ptrplayer->section=MAX_X/ptrplayer->step;

    }
    };


    // down

   if (ptrplayer->direction==4)
    {
    if((visited[tmpy+1][tmpx]==CRUMB)
    &&( Map[STAGE][tmpy+1][tmpx]==BACKGROUND
    || Map[STAGE][tmpy+1][tmpx]==WEAPONRECHARGER
    //|| Map[STAGE][tmpy+1][tmpx]==ELECTRICLINEH
    //|| Map[STAGE][tmpy+1][tmpx]==ELECTRICLINEV
    || Map[STAGE][tmpy+1][tmpx]==COMPUTER_MINE
    ))
    {
    CRUMB++;
    ptrplayer->direction = 2;
    ptrplayer->angle=180;
    ptrplayer->section=MAX_Y/ptrplayer->step;
    }
    };

    // left
    if (ptrplayer->direction==4)
    {
    if((visited[tmpy][tmpx-1]==CRUMB)
    &&( Map[STAGE][tmpy][tmpx-1]==BACKGROUND
    || Map[STAGE][tmpy][tmpx-1]==WEAPONRECHARGER
    || Map[STAGE][tmpy][tmpx-1]==ELECTRICLINEH
    || Map[STAGE][tmpy][tmpx-1]==ELECTRICLINEV
    || Map[STAGE][tmpy][tmpx-1]==COMPUTER_MINE
    ))
    {
    CRUMB++;
    ptrplayer->direction = 3;
    ptrplayer->angle=270;
    ptrplayer->section=MAX_X/ptrplayer->step;
    }
    };


    if (ptrplayer->change_direction == 4)                                                               // 5 = off
    {
    if ((ptrplayer->direction==4))
    {

    if ((visited[tmpy][tmpx-1]==CRUMB)
    && ((Map[STAGE][tmpy][tmpx-1]==BLOCK)
    || (Map[STAGE][tmpy][tmpx-1]==QUAD)))
    {
    ptrplayer->change_direction = 3;
    ptrplayer->angle = ptrplayer->change_direction * 90;
    ptrplayer->direction = ptrplayer->change_direction;
    }

    if((visited[tmpy][tmpx+1]==CRUMB)
    &&((Map[STAGE][tmpy][tmpx+1]==BLOCK)
    || (Map[STAGE][tmpy][tmpx+1]==QUAD)))
    {
    ptrplayer->change_direction = 1;
    ptrplayer->angle = ptrplayer->change_direction * 90;
    ptrplayer->direction = ptrplayer->change_direction;
    }

    if((visited[tmpy-1][tmpx]==CRUMB)
    &&((Map[STAGE][tmpy-1][tmpx]==BLOCK)
    || (Map[STAGE][tmpy-1][tmpx]==QUAD)))
    {
    ptrplayer->change_direction = 0;
    ptrplayer->angle = ptrplayer->change_direction * 90;
    ptrplayer->direction = ptrplayer->change_direction;
    }

    if((visited[tmpy+1][tmpx]==CRUMB)
    &&((Map[STAGE][tmpy+1][tmpx]==BLOCK)
    || (Map[STAGE][tmpy+1][tmpx]==QUAD)))
    {
    ptrplayer->change_direction = 2;
    ptrplayer->angle = ptrplayer->change_direction * 90;
    ptrplayer->direction = ptrplayer->change_direction;
    }

    } // if
    }; // if

    }; // if CRUMB < 0

    ///////////////////////////////////////////////////////

    if (CRUMB==0)
    {
    if (TARGET==STAR)
    {
    ptrplayer->type_of_weapon=0;         // switch to AMMO for star destroy

    if((Map[STAGE][tmpy][tmpx-1]==STAR))
    {
    ptrplayer->angle=270;
    }

    if((Map[STAGE][tmpy][tmpx+1]==STAR))
    {
    ptrplayer->angle=90;
    }

    if((Map[STAGE][tmpy-1][tmpx]==STAR))
    {
    ptrplayer->angle=0;
    }

    if((Map[STAGE][tmpy+1][tmpx]==STAR))
    {
    ptrplayer->angle=180;
    }

    };


    if (TARGET==WEAPONRECHARGER)
    {

    if((Map[STAGE][tmpy][tmpx-1]==WEAPONRECHARGER))
    {
    ptrplayer->angle=270;
    ptrplayer->direction = 3;
    ptrplayer->section=MAX_X/ptrplayer->step;
    }

    if((Map[STAGE][tmpy][tmpx+1]==WEAPONRECHARGER))
    {
    ptrplayer->angle=90;
    ptrplayer->direction = 1;
    ptrplayer->section=MAX_X/ptrplayer->step;
    }

    if((Map[STAGE][tmpy-1][tmpx]==WEAPONRECHARGER))
    {
    ptrplayer->angle=0;
    ptrplayer->direction = 0;
    ptrplayer->section=MAX_X/ptrplayer->step;
    }

    if((Map[STAGE][tmpy+1][tmpx]==WEAPONRECHARGER))
    {
    ptrplayer->angle=180;
    ptrplayer->direction = 2;
    ptrplayer->section=MAX_X/ptrplayer->step;
    }

    }; // if TARGET


    } // if CRUMB == 0


    // shooting with ammo

    if (ptrplayer->random_shot==0)
    {
    if (space>0)
    {
    space--;
    }
    };

    if(space<=0)
    {

    if (ptrplayer->type_of_weapon==0)                                                               // AMMO 0 , LASER 1
    {

    if (ptrplayer->ammo>0)
    {

    space=60;                                                                                       // timing for next shoot

    ptrplayer->ammo--;
    index_fire++;

    if (index_fire>=MAX_FIRE)
    {
    index_fire=0;
    }



    fires[index_fire].direction=ptrplayer->angle/90;



    fires[index_fire].x=ptrplayer->x;
    fires[index_fire].y=ptrplayer->y;
    fires[index_fire].type_of_weapon=0;                                     /// 0 ammo , 1 laser


    } // if
    } // if
    }; // if


    // shooting with laser

    if (ptrplayer->random_shot==1)
    {
    if (r_control>0)
    {
    r_control--;
    }
    };

    if(r_control<=0)
    {
    if (ptrplayer->type_of_weapon==1)
    {
    if (ptrplayer->laser>0)
    {
    r_control=60;                                                                       // timing for next shoot
    ptrplayer->laser--;
    index_fire++;

    if (index_fire>=MAX_FIRE)
    {
    index_fire=0;
    }

    fires[index_fire].direction=ptrplayer->angle/90;
    fires[index_fire].x=ptrplayer->x;
    fires[index_fire].y=ptrplayer->y;
    fires[index_fire].type_of_weapon=1;                                                 // 0 ammo, 1 laser
    } // if
    } // if
    }; // if


    }; // if


    if (ptrplayer->change_direction == -11)                                     // ????
    {
    if ((TARGET==STAR) || (TARGET==WEAPONRECHARGER))
    {
    ptrplayer->type_of_weapon=0;                                                // switch weapon

    if((Map[STAGE][tmpy][tmpx-1]==BLOCK))
    {
    ptrplayer->angle=270;
    }

    if((Map[STAGE][tmpy][tmpx+1]==BLOCK))
    {
    ptrplayer->angle=90;
    }

    if((Map[STAGE][tmpy-1][tmpx]==BLOCK))
    {
    ptrplayer->angle=0;
    }

    if((Map[STAGE][tmpy+1][tmpx]==BLOCK))
    {
    ptrplayer->angle=180;
    }

    } // if
    }; // if



    return 0;


} // follow_path_to_target()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


