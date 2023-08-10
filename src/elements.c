
#include "elements.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// drawing elements on the scene
void draw_elements(TElement * ptrelement,int Map[MAX_STAGE][MAP_Y][MAP_X],BITMAP *buffer,int STAGE, int option)     // 1-bmp_block ,2-bmp_wall ,3-bmp_quad ,4- bmp_stars etc.
{

    static int x,y;

    static int index_star;


    static int shift_x=0;
    static int shift_y=0;
    static int edge_visibility=0;
    int x_on_map=0;
    int y_on_map=0;

    index_star=0;


    if (option==o_play_game)
    {
    x_on_map=ptrelement->player.shift_x/MAX_X;
    y_on_map=ptrelement->player.shift_y/MAX_Y;
    shift_x = ptrelement->player.shift_x;
    shift_y = ptrelement->player.shift_y;
    edge_visibility=1;

    } else
    if (option==o_editor)
    {
    x_on_map=ptrelement->editor.x/MAX_X;
    y_on_map=ptrelement->editor.y/MAX_Y;

    shift_x = ptrelement->editor.x;
    shift_y = ptrelement->editor.y;
    edge_visibility=1;

    }




    for(x=x_on_map;x<x_on_map+MAP_X_32+edge_visibility;x++)
    for (y=y_on_map;y<y_on_map+MAP_Y_24+edge_visibility;y++)

    {
    // this must be as a constraint for the board field

    if (x<=0) x=0;
    if (y<=0) y=0;
    if (x>MAP_X) x= MAP_X-1;
    if (y>MAP_Y) y= MAP_Y-1;

    if (Map[STAGE][y][x]==COMPUTER_MINE)         // COMPUTER_MINE
    {
    circlefill(buffer,x*MAX_X-shift_x+MAX_X/2,y*MAX_Y-shift_y+MAX_Y/2,2,GREY);
    };


    if (Map[STAGE][y][x]==SLANTLROTATE)
    {
    // ok draw_sprite(buffer,ptrelement->wall.bmp_wall,x*MAX_Y,y*MAX_Y);
    masked_blit(ptrelement->slantLrotate.bmp_slantL,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_Y,MAX_Y);
	};

    if (Map[STAGE][y][x]==SLANTRROTATE)
    {
    masked_blit(ptrelement->slantRrotate.bmp_slantR,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_Y,MAX_Y);
    };

    if (Map[STAGE][y][x]==BLOCK)
    {
    masked_blit(ptrelement->block.bmp,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);   // all1
    };

    if (Map[STAGE][y][x]==WALL)
    {
    masked_blit(ptrelement->wall.bmp_wall,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    //circle(buffer,x*MAX_Y,y*MAX_Y,5,20);
    };

    if (Map[STAGE][y][x]==QUAD)
    {
    masked_blit(ptrelement->quad.bmp_quad,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    if (Map[STAGE][y][x]==WEAPONRECHARGER)
    {
    masked_blit(ptrelement->weaponrecharger.bmp_weaponrecharger,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    if (Map[STAGE][y][x]==ELECTRICLINEV)
    {
    masked_blit(ptrelement->electriclineV.bmptab[ptrelement->electriclineV.anim_count],buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    if (Map[STAGE][y][x]==ELECTRICLINEH)
    {
    masked_blit(ptrelement->electriclineH.bmptab[ptrelement->electriclineH.anim_count],buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };


    if (Map[STAGE][y][x]==WALLOFFH)
    {
    masked_blit(ptrelement->switchOFFH.bmp,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    if (Map[STAGE][y][x]==WALLOFFV)
    {
    masked_blit(ptrelement->switchOFFV.bmp,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
	};



    if (Map[STAGE][y][x]==STAR)
    {
    index_star++;
    if (index_star>MAX_STAR)
    {
    index_star=0;
    }

    masked_stretch_blit(ptrelement->stars[index_star].bmp_stars,buffer,0,
    ptrelement->stars[index_star].anim_count*(ptrelement->stars[index_star].bmp_stars->h/6),
    ptrelement->stars[index_star].bmp_stars->w,ptrelement->stars[index_star].bmp_stars->h/6,
    x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);

    // ok all1 blit(ptrelement->stars[index_star].bmp_stars,buffer,0,ptrelement->stars[index_star].anim_count*(ptrelement->stars[index_star].bmp_stars->h/6),x*MAX_Y,y*MAX_Y,MAX_Y,MAX_Y);

    };

    if (Map[STAGE][y][x]==SLANTL)
    {
    // ok all1 blit(ptrelement->slantL.bmp_slantL,buffer,0,0,x*MAX_Y,y*MAX_Y,MAX_Y,MAX_Y);
    masked_blit(ptrelement->slantL.bmp_slantL,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    if (Map[STAGE][y][x]==SLANTR)
    {
    // ok all1 blit(ptrelement->slantR.bmp_slantR,buffer,0,0,x*MAX_Y,y*MAX_Y,MAX_Y,MAX_Y);
    masked_blit(ptrelement->slantR.bmp_slantR,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    }

    if (Map[STAGE][y][x]==BOMB)
    {
    // all1 blit(ptrelement->bomb.bitmap,buffer,0,0,x*MAX_Y,y*MAX_Y,MAX_Y,MAX_Y);
    masked_blit(ptrelement->bomb.bitmap,buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    }

    if (option==o_play_game)
    {


    if (Map[STAGE][y][x]==MINER)  // erase miner

    {
    Map[STAGE][y][x]=BACKGROUND;
    }


    if (Map[STAGE][y][x]==ENEMY)  // erase enemy

    {
    Map[STAGE][y][x]=BACKGROUND;
    }

    }

    if (option==o_editor)

    {

    if (Map[STAGE][y][x]==MINER)
    {
    masked_blit(ptrelement->miner[1].bmptab[0],buffer,0,0,x*MAX_Y-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    if (Map[STAGE][y][x]==PLAYER)
    {
    masked_blit(ptrelement->player.bmptab[0],buffer,0,0,x*MAX_X-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    if (Map[STAGE][y][x]==ENEMY)
    {
    masked_blit(ptrelement->enemy[1].bmptab[0],buffer,0,0,x*MAX_Y-shift_x,y*MAX_Y-shift_y,MAX_X,MAX_Y);
    };

    };




    }; // for




} // draw_elements()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
