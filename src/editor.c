

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "editor.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// the function called in the editor immediately saves the MAX_STAGE of the boards
void save_level(int sizeMap,int E_Map[MAX_STAGE][MAP_Y][MAP_X],char * path, enum Tdifficulty difficulty_level)
{
    FILE * file;
    char * filename;

#ifdef MiniBlast

    if (difficulty_level==easy) filename = "1p_mini_easy.map";
    if (difficulty_level==medium) filename = "1p_mini_medium.map";
    if (difficulty_level==hard) filename = "1p_mini_hard.map";
#endif // MiniBlast

#ifdef MidiBlast

    if (difficulty_level==easy) filename = "1p_midi_easy.map";
    if (difficulty_level==medium) filename = "1p_midi_medium.map";
    if (difficulty_level==hard) filename = "1p_midi_hard.map";
#endif // MidiBlast

#ifdef MaxiBlast

    if (difficulty_level==easy) filename = "1p_maxi_easy.map";
    if (difficulty_level==medium) filename = "1p_maxi_medium.map";
    if (difficulty_level==hard) filename = "1p_maxi_hard.map";
#endif // MaxiBlast

    char *result = malloc(strlen(path)+strlen(filename)+1);//+1 for the zero-terminator

    result = malloc(strlen(path)+strlen(filename)+1);//+1 for the zero-terminator

    strcpy(result, path);
    strcat(result, filename);

    if ((file=fopen(result,"wb"))==NULL)
    {

    free(result);


    if (language == english)
    {
    allegro_message("Can't open file to save levels.");
    }

    if (language == polish)
    {
    allegro_message("Nie można otworzyc pliku aby zapisać plansze.");
    }

    allegro_exit();


    };

    fwrite(E_Map,1,sizeMap,file);
    free(result);
    fclose(file);

}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// function called from the main loop via new_game() and through the editor immediately loads the MAX_STAGE of the boards

int load_level(int sizeMap,int E_Map[MAX_STAGE][MAP_Y][MAP_X], char * path, enum Tdifficulty difficulty_level)
{
    FILE * file;
    int x,y,stars;
    int stage;
    char * filename;
    stars=0;


#ifdef MiniBlast

    if (difficulty_level==easy) filename = "1p_mini_easy.map";
    if (difficulty_level==medium) filename = "1p_mini_medium.map";
    if (difficulty_level==hard) filename = "1p_mini_hard.map";
#endif // MiniBlast

#ifdef MidiBlast

    if (difficulty_level==easy) filename = "1p_midi_easy.map";
    if (difficulty_level==medium) filename = "1p_midi_medium.map";
    if (difficulty_level==hard) filename = "1p_midi_hard.map";
#endif // MidiBlast

#ifdef MaxiBlast

    if (difficulty_level==easy) filename = "1p_maxi_easy.map";
    if (difficulty_level==medium) filename = "1p_maxi_medium.map";
    if (difficulty_level==hard) filename = "1p_maxi_hard.map";
#endif // MaxiBlast

    char *result = malloc(strlen(path)+strlen(filename)+1);//+1 for the zero-terminator
    result = malloc(strlen(path)+strlen(filename)+1);//+1 for the zero-terminator

    strcpy(result, path);
    strcat(result, filename);

    if ((file=fopen(result,"rb"))==NULL)
    {
    if (language == english)
    {
    allegro_message("Can't open %s file.", filename );
    }
    if (language == polish)
    {
    allegro_message("Nie można otworzyć pliku %s", filename );
    }

    free(result);
    return -1;         // return -1 for file missing
    }

    free(result);

    fseek(file,0,SEEK_SET);

    size_t ret = fread(E_Map,1,sizeMap,file);
    printf("read %zu bytes from file %s \n", ret*sizeMap, filename);
    fclose(file);

    // set the MAX_STAGE variable to see if there are stars

    stage=0;                                                                                // local

    while(1)
    {
    stars=0;

    for(x=0;x<MAP_X;x++)
    {
        for (y=0;y<MAP_Y;y++)
        {
        if (E_Map[stage][y][x]==STAR)                                                       // stars
        {
        stars++;
        }
        }
    }

    if (stars>MAX_STAR)
    {
    break;
    };

    if (stars==0)
    {
    break;
    };

    stage++;


    };


    return stage;


} // load_level(




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// editor read all stages and return stage number
int editor(BITMAP *screen_buffer,int E_Map[MAX_STAGE][MAP_Y][MAP_X],TElement *ptrelement, int ptrwait)
{
    static  BITMAP *mouse_pointer=NULL;
    static BITMAP *bmp_element=NULL;

    ptrelement->player.shift_x=0;
    ptrelement->player.shift_y=0;


    if (mouse_pointer==NULL)
    {
    mouse_pointer=create_bitmap(25,25);

    clear_to_color(mouse_pointer,CLEAR);

    circle(mouse_pointer,12,12,12,GREY);
    circle(mouse_pointer,12,12,10,GREY);

    line(mouse_pointer,0,12,25,12,GREY);
    line(mouse_pointer,12,0,12,25,GREY);

    };

    static  BITMAP *buffer=NULL;


     if (buffer==NULL)
    {
    buffer=create_bitmap(SCREEN_w,SCREEN_h);

    clear_to_color(buffer,CLEAR);

    };

#ifndef MiniBlast

     if (language == english)
    {
    strcpy(txt_data_editor[0],("Stage :     'Space'- change element to draw 'C'- center    "));
    strcpy(txt_data_editor[1],("            'Arrows'- scroll stage 'PG Dn/Up'- change stage"));
    strcpy(txt_data_editor[2],("Element:    'Left/Right mouse click'- draw/erase element   "));
    strcpy(txt_data_editor[3],("            'S'- save levels 'F10'- clear stage            "));

    }

    if (language == polish)
    {
    strcpy(txt_data_editor[0],("Etap  :     'Spacja'- zmień element rysowany 'C'- centruj  "));
    strcpy(txt_data_editor[1],("            'Strzałki'- przesuń 'PG Dn/Up'- zmień etap     "));
    strcpy(txt_data_editor[2],("Element:    'Lewy/Prawy przycisk myszy'- rysuj/wymaż       "));
    strcpy(txt_data_editor[3],("            'S'- zapisz plansze 'F10'- wyczyść planszę     "));

    }

#else
    if (language == english)
    {
    strcpy(txt_data_editor[0],("Stage :     'Space'- change element to draw                "));
    strcpy(txt_data_editor[1],("            'PG Dn/Up'- change stage                       "));
    strcpy(txt_data_editor[2],("Element:    'Left/Right mouse click'- draw/erase element   "));
    strcpy(txt_data_editor[3],("            'S'- save levels 'F10'- clear stage            "));

    }

    if (language == polish)
    {
    strcpy(txt_data_editor[0],("Stage :     'Spacja'- zmień element rysowany               "));
    strcpy(txt_data_editor[1],("            'PG Dn/Up'- zmień etap                         "));
    strcpy(txt_data_editor[2],("Element:    'Lewy/Prawy przycisk myszy'- rysuj/wymaż       "));
    strcpy(txt_data_editor[3],("            'S'- zapisz plansze 'F10'- wyczyść planszę     "));

    }

#endif



    static char obiekt[MAX_ELEMENTS-1]={
    //BACKGROUND,
    BLOCK,
    BOMB,
    //EXPLOSIONS,
    WEAPONRECHARGER,
    MINER,
    PLAYER,
    //AMMO,
    QUAD,
    SLANTL,
    SLANTR,
    STAR,
    WALL,
    ELECTRICLINEV,
    ELECTRICLINEH,
    WALLOFFV,
    WALLOFFH,
    SLANTLROTATE,
    SLANTRROTATE,
    ENEMY
    };

    static int stage=0;

    static int nr_element=0;                                                                // current item (1-BLOCK,2-QUAD etc)

    static int x, y;

    static int space=0, l_control;

    static int kleft=0,kright=0;

    clear_to_color(buffer,CLEAR);

    if (bmp_element==NULL)
    {

    if(!(bmp_element=create_bitmap(ptrelement->block.bmp->w,ptrelement->block.bmp->h)))
    {

    if (language == english)
    {
    allegro_message("Not enough memory to create sprites.");
    }

    if (language == polish)
    {
    allegro_message("Za mało pamięci do utworzenia sprajtów.");
    }

    allegro_exit();



    }

    };



#ifndef MiniBlast
    if((key[KEY_C]))
    {

    for(x=0;x<MAP_X;x++)
    {
        for (y=0;y<MAP_Y;y++)
        {
        if (E_Map[stage][y][x]==PLAYER)
        {
        ptrelement->editor.x = x*MAX_X-MAP_X_32/2*MAX_X;
        ptrelement->editor.y = y*MAX_Y-MAP_Y_24/2*MAX_Y;

        if (ptrelement->editor.y<(0*MAX_Y))
        {
        (ptrelement->editor.y=(0*MAX_Y));
        }

        if (ptrelement->editor.y>(SCREEN_h*NUMBER_OF_SCREENS_Y)-(MAP_Y_24*MAX_Y))
        {
        (ptrelement->editor.y=(SCREEN_h*NUMBER_OF_SCREENS_Y)-(MAP_Y_24*MAX_Y));
        }

        if (ptrelement->editor.x<(0*MAX_X))
        {
        (ptrelement->editor.x=(0*MAX_X));
        }

        if (ptrelement->editor.x>(SCREEN_w*NUMBER_OF_SCREENS_X)-(MAP_X_32*MAX_X))
        {
        (ptrelement->editor.x=(SCREEN_w*NUMBER_OF_SCREENS_X)-(MAP_X_32*MAX_X));
        }

        }

        }
    };


    };
#endif // MiniBlast


    if ((key[KEY_F10]))
    {
    if (language == english)
    {
    allegro_message("CLEARING OF THE STAGE!!!");
    }

    if (language == polish)
    {
    allegro_message("CZYSZCZENIE PLANSZY!!!");
    }

    for (x=0;x<MAP_X;x++)
    {
    for (y=0;y<MAP_Y;y++)
    {
    E_Map[stage][y][x]=BACKGROUND;
    }
    }

    };

    if (!(key[KEY_SPACE]))
    {
    space=0;
    }

    if(space==0)

    if((key[KEY_SPACE]))

    {
    nr_element ++;space=1;

    if (nr_element>=MAX_ELEMENTS-1)
    {
    nr_element=0;
    }

    }





    if(!(key[KEY_LCONTROL]))
    {
    l_control=0;
    }

    if(l_control==0)
    {
    if((key[KEY_LCONTROL]))    //space z sziftem

    {
    nr_element --;
    l_control=1;

    if (nr_element<0 )
    {
    nr_element=MAX_ELEMENTS-2;                                                      // minus AMMO, EXPLOSIONS and PLAYER
    }

    }
    }

#ifndef MiniBlast

    if (ptrwait == 0)
    {

    if(key[KEY_DOWN])
    {
    ptrelement->editor.y+=5;
    if (ptrelement->editor.y > (SCREEN_h*(NUMBER_OF_SCREENS_Y-1)))
    {
    ptrelement->editor.y = (SCREEN_h*(NUMBER_OF_SCREENS_Y-1));
    }
    };


    if(key[KEY_UP])
    {
    ptrelement->editor.y-=5;

    if (ptrelement->editor.y< 0)
    {
    ptrelement->editor.y = 0;
    }
    };

    if(key[KEY_RIGHT])
    {
    ptrelement->editor.x+=5;

    if (ptrelement->editor.x > (SCREEN_w*(NUMBER_OF_SCREENS_X-1)))
    {
    ptrelement->editor.x = (SCREEN_w*(NUMBER_OF_SCREENS_X-1));
    }
    };


    if(key[KEY_LEFT])
    {
    ptrelement->editor.x-=5;
    if (ptrelement->editor.x < 0)
    {
    ptrelement->editor.x = 0;
    }
    };

    };

#endif // MiniBlast


    if( !(key[KEY_PGUP]))
    {
    kright=0;
    }

    if (kright==0)
    {
    if(key[KEY_PGUP])
    {
    kright=1;

    if (stage>=MAX_STAGE-1)
    {
    stage=MAX_STAGE-1;
    }
    else
    {
    stage++;
    }
    }
    };


    if(!(key[KEY_PGDN]))
    {
    kleft=0;
    }

    if (kleft==0)
    {
    if(key[KEY_PGDN])
    {
    kleft=1;

    if ((stage<=0) || (stage>MAX_STAGE))
    {
    stage=0;
    }
    else
    {
    stage--;
    }
    }
    };

    clear_bitmap(bmp_element);

    switch(obiekt[nr_element])

    {

    case BLOCK :
    {
    draw_sprite(bmp_element,ptrelement->block.bmp,0,0);

    break;
    };

    case BOMB :
    {
    draw_sprite(bmp_element,ptrelement->bomb.bitmap,0,0);

    break;
    };

    case WEAPONRECHARGER :
    {
    draw_sprite(bmp_element,ptrelement->weaponrecharger.bmp_weaponrecharger,0,0);

    break;
    };

    case MINER :
    {
    draw_sprite(bmp_element,ptrelement->miner[1].bmptab[0],0,0);

    break;
    };

    case PLAYER :
    {
    draw_sprite(bmp_element,ptrelement->player.bmptab[0],0,0);

    break;
    };

    case QUAD :
    {
    draw_sprite(bmp_element,ptrelement->quad.bmp_quad,0,0);

    break;
    };

    case SLANTL :
    {
    draw_sprite(bmp_element,ptrelement->slantL.bmp_slantL,0,0);

    break;
    };

    case SLANTR :

    {
    draw_sprite(bmp_element,ptrelement->slantR.bmp_slantR,0,0);

    break;
    };

    case STAR :
    {
    draw_sprite(bmp_element,ptrelement->stars[1].bmp_stars,0,0);

    break;
    };

    case WALL :
    {
    draw_sprite(bmp_element,ptrelement->wall.bmp_wall,0,0);

    break;
    };

    case ELECTRICLINEV :
    {
    draw_sprite(bmp_element,ptrelement->electriclineV.bmptab[1],0,0);

    break;
    };

    case ELECTRICLINEH :
    {
    draw_sprite(bmp_element,ptrelement->electriclineH.bmptab[1],0,0);

    break;
    };

    case WALLOFFV :
    {
    draw_sprite(bmp_element,ptrelement->switchOFFV.bmp,0,0);

    break;
    };

    case WALLOFFH :
    {
    draw_sprite(bmp_element,ptrelement->switchOFFH.bmp,0,0);

    break;
    };

    case SLANTLROTATE :
    {
    draw_sprite(bmp_element,ptrelement->slantLrotate.bmp_slantL,0,0);

    break;
    };

    case SLANTRROTATE :
    {
    draw_sprite(bmp_element,ptrelement->slantRrotate.bmp_slantR,0,0);

    break;
    };

    case ENEMY :
    { //for (i=0;i<MAX_COMP;i++)

    draw_sprite(bmp_element,ptrelement->enemy[1].bmptab[0],0,0);

    break;
    };

    draw_sprite(buffer,bmp_element,x*MAX_Y,y*MAX_Y);


    }; // from switch(obiekt[nr_element])



    x = mouse_x;
    y = mouse_y;
    // left right borders for board construction
    if (x<0+MARGIN_LEFT*MAX_X)
    {
    x=0+MARGIN_LEFT*MAX_X;
    };

    if (x>SCREEN_w-MARGIN_RIGHT*MAX_X)
    {
    x=SCREEN_w-MARGIN_RIGHT*MAX_X;
    };

    // up down borders for board construction
    if (y<0+MARGIN_TOP*MAX_Y)
    {
    y=0+MARGIN_TOP*MAX_Y-MAX_Y;
    };

    if (y>(SCREEN_h-MARGIN_BOTTOM*MAX_Y))
    {
    y=SCREEN_h-MARGIN_BOTTOM*MAX_X-MAX_X;
    };


    {{

    int ix,iy;

    // store the current element on the coordinates in the map array
    if (mouse_b & 1)
    {

    // check if there is already a player, if so, change it
    if ((obiekt[nr_element])==PLAYER)
    {
    for(ix=0;ix<MAP_X;ix++)
    {
        for (iy=0;iy<MAP_Y;iy++)
        {
        if (E_Map[stage][iy][ix]==PLAYER)  E_Map[stage][iy][ix]=0;

        }
    };
    };


    int index_miner;
    index_miner=0;

    // check if it exceeded MAX_COMP
    if ((obiekt[nr_element])==MINER)
    {

    for(ix=0;ix<MAP_X;ix++)
    {
        for (iy=0;iy<MAP_Y;iy++)
        {
        if (E_Map[stage][iy][ix]==MINER)
        {
        index_miner++;

        if (index_miner>=MAX_COMP)
        {
        index_miner=0;
        nr_element=BACKGROUND;
        }
        }
        }
    };
    };

    int index_enemy=0;
    index_enemy=0;

    // check if it exceeded MAX_ENEMIES
    if ((obiekt[nr_element])==ENEMY)
    {
    for(ix=0;ix<MAP_X;ix++)
    {
        for (iy=0;iy<MAP_Y;iy++)
        {
        if (E_Map[stage][iy][ix]==ENEMY)
        {
        index_enemy++;
        if (index_miner>=MAX_ENEMIES)
        {
        index_miner=0;
        nr_element=BACKGROUND;

        }

        }

        }
    };
    };

    int index_star=0;
    index_star=0;

    // check if it exceeded MAX_STARS
    if ((obiekt[nr_element])==STAR)
    {

    for(ix=0;ix<MAP_X;ix++)
    {
        for (iy=0;iy<MAP_Y;iy++)
        {
        if (E_Map[stage][iy][ix]==STAR)
        {
        index_star++;

        if (index_star>=MAX_STAR)
        {
        nr_element=BACKGROUND;
        index_star=0;
        }
        }
        }
    };
    };


    if(((y+ptrelement->editor.y)/MAX_Y>=0) &&
    ((y+ptrelement->editor.y)/MAX_Y<MAP_Y) &&
    ((x+ptrelement->editor.x)/MAX_X>=0) &&
    ((x+ptrelement->editor.x)/MAX_X<MAP_X))

    {
    E_Map[stage][(y+ptrelement->editor.y)/MAX_Y][(x+ptrelement->editor.x)/MAX_X]=obiekt[nr_element];
    };


    }; // mouse_b


    // save to coordinates in map table empty field (BACKGROUND)
    if (mouse_b & 2)
    {
    if(((y+ptrelement->editor.y)/MAX_Y>=0) &&
    ((y+ptrelement->editor.y)/MAX_Y<MAP_Y) &&
    ((x+ptrelement->editor.x)/MAX_X>=0) &&
    ((x+ptrelement->editor.x)/MAX_X<MAP_X))
    {
    E_Map[stage][(y+ptrelement->editor.y)/MAX_Y][(x+ptrelement->editor.x)/MAX_X]=BACKGROUND;
    }

    }; // mouse_b


    }}


    option=o_editor;

    draw_elements(ptrelement,E_Map,buffer,stage,option);

     x = mouse_x;                                                           // mouse pointer position
     y = mouse_y;

    draw_sprite(buffer,mouse_pointer,x-MAX_X/2,y-MAX_Y/2);

    masked_blit(buffer,screen_buffer,0,0,0,0,0+SCREEN_w,0+SCREEN_h);

    textprintf_centre_ex(screen_buffer,font,SCREEN_w/2,10,WHITE,-1,"Pos x: %d",(ptrelement->editor.x+mouse_x)/MAX_X+1);
    textprintf_centre_ex(screen_buffer,font,SCREEN_w/2,20,WHITE,-1,"Pos y: %d",(ptrelement->editor.y+mouse_y)/MAX_Y+1);
    textprintf_ex(screen_buffer,font,165,SCREEN_h-54,WHITE,0,"%d",stage+1);

    draw_sprite(screen_buffer,bmp_element,165,SCREEN_h-42);   // idealnie dopasowany do napisu Element

    draw_text_ed(screen_buffer);

    return stage;

}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//

void   draw_text_ed(BITMAP *buffer)
{

    static  BITMAP *text_buffer_ed=NULL;

    if (text_buffer_ed==NULL)
    {

    if (!(text_buffer_ed=create_bitmap(SCREEN_w,SCREEN_h/8)))

    {

    if (language == english)
    {
    allegro_message("Not enough memory to create screen buffer.");
    }

    if (language == polish)
    {
    allegro_message("Za malo pamieci do utworzenia buffera ekranu.");
    }

    allegro_exit();


    }

    }

    clear_to_color(text_buffer_ed,CLEAR);

    textout_ex(text_buffer_ed,font,txt_data_editor[0],0,5,WHITE,-1);       // STAGE SPACE

    textout_ex(text_buffer_ed,font,txt_data_editor[1],0,15,WHITE,-1);      // ARROWS Left Right
    textout_ex(text_buffer_ed,font,txt_data_editor[2],0,25,WHITE,-1);      // MOUSE CLICK R
    textout_ex(text_buffer_ed,font,txt_data_editor[3],0,35,WHITE,-1);      // S - stage save

    draw_sprite(buffer,text_buffer_ed,100,(SCREEN_h-3*MAX_Y));



};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
