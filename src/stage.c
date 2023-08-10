///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "stage.h"




int time_of_animation = 200; // okolo 2 s czas wyświetlania się animacji w next stage i game over i draw final

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int calibrate_joypad(BITMAP* bmp_menu)
{

    //AL_CONST char *msg;

    /* before using the joystick, we have to calibrate it. This loop only
    * calibrates joystick number 0, but you could do the same thing for
    * other sticks if they are present (the num_joysticks variable will
    * tell you how many there are).
    */
    while (joy[0].flags & JOYFLAG_CALIBRATE)
    {
    //msg = calibrate_joystick_name(0);
    if (calibrate_joystick(0) != 0)
    {
    if (language == english)
    {
    allegro_message("Error calibrating joypad!\n");
    }
    if (language == polish)

    {
	 allegro_message("Błąd kalibracji joypada!\n");

    }
    return 1;
    }
    }

    return 0;

} // calibrate_joypad()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int new_entry_read_string( char *str_to, int size, TElement * ptrelement)
{
    static int cur_pos = MAX_DIGITS_SCORES; // position of caret
    int the_key = 0;
    int i;

    the_key =' ';

    if (ptrelement->is_cleaned== 0)
    {
    ptrelement->is_cleaned=1;
    clear_keybuf();

    for (i = size-2; i >= MAX_DIGITS_SCORES-1; i--)

    {
    str_to[i] = ' ';                                                                    // 'clean' the string
    }

    cur_pos=MAX_DIGITS_SCORES;

    }

    if (the_key>>8 != KEY_ENTER)
    {
    the_key = readkey();

    if ((the_key & 0xff) > ' ') // get only valid chars
    {
    str_to[cur_pos] = the_key & 0xff;
    cur_pos++;
    if (cur_pos > size-2)
    {
    cur_pos = size-2;
    }

    }

    if (the_key >> 8 == KEY_BACKSPACE)
    {

    str_to[cur_pos] = ' '; // enter space
    cur_pos --;
    if (cur_pos < MAX_DIGITS_SCORES)
    {
    cur_pos = MAX_DIGITS_SCORES;
    }
    }

    }; // if


    static int Enterup=0;

    if (!(key[KEY_ENTER]))
    {
    Enterup=0;
    }

    if (Enterup==0)
    {
    if (key[KEY_ENTER])
    {
    Enterup=1;

    ptrelement->is_cleaned=0;

    cur_pos = MAX_DIGITS_SCORES;

    str_to[MAX_LETTERS-1] = '\n';
    return 2;
    }
    }

    return 1;

} // new_entry_read_string()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int load_scoreboard(char *score_name)

{
    FILE * file;

    if ((file=fopen("data/highscore.bin","rb"))==NULL)
    {

    if (language == english)
    {
    allegro_message("Cant open 'Highscore.bin' file! New file is created.");
    }

    if (language == polish)
    {
    allegro_message("Nie można otworzyć pliku 'highscore.bin'. Został utworzony nowy plik.");
    }

    return 1;
    };

    fseek(file,0,SEEK_SET);

    size_t ret = fread(score_name,1,MAX_ENTRIES*(MAX_LETTERS)*(sizeof(char)),file);
    printf("read %zu bytes from file highscore.bin\n", ret*MAX_ENTRIES*(MAX_LETTERS)*(sizeof(char)));

    fclose(file);

    return 0;

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int save_scoreboard( char *score_name)
{

    FILE * file;


    if ((file=fopen("data/highscore.bin","wb"))==NULL)                                              // "w" text mode, "wb" binary mode, file to write
    {
    if (language == english)
    {
    allegro_message("Can't create 'highscore.bin' file.");
    }

    if (language == polish)
    {
    allegro_message("Nie można utworzyć pliku 'highscore.bin'.");
    }
    allegro_exit();
    }

    fwrite(score_name,1,MAX_ENTRIES*(MAX_LETTERS)*(sizeof(char)),file);

    fclose(file);
    return 0;

} // save_scoreboard()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int hall_of_fame_entry(TElement *ptrelement,BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X],int ptrwait)
{

    char entryPoints[MAX_LETTERS]=     "            ";
    char playerPoints[MAX_LETTERS]=    "            ";
    char playerNamePoints[MAX_LETTERS]="            ";
    char tmpNamePoints[MAX_LETTERS]=   "            ";
    //char entryNamePoints[MAX_LETTERS]= "            ";

    int val=0;
    int val2=0;

    static BITMAP *hall_of_fame_bmp=NULL;

    if (hall_of_fame_bmp==NULL)
    {
    hall_of_fame_bmp=create_bitmap(SCREEN_w,SCREEN_h);
    }

    clear_to_color(hall_of_fame_bmp,makecol(0,0,0));

    static char score_board[MAX_ENTRIES][MAX_LETTERS];
    static char* ptr_score_board, * ptr_new_score_board;
    static char new_score_board[MAX_ENTRIES][MAX_LETTERS] =

    {("930  Ann   \n"),
    ("820  Joe   \n"),
    ("718  Jack  \n"),
    ("617  Ann   \n"),
    ("515  Jackie\n"),
    ("414  Ann   \n"),
    ("313  Hob   \n"),
    ("212  Ann   \n"),
    ("111  George\n"),
    ("50   Ann   \n")};


    ptr_score_board=*score_board;
    ptr_new_score_board =* new_score_board;

    static int highScore_is_loaded=0;
    static int positionHighscore=9;
    static int new_entry =0;


    if( highScore_is_loaded==0)
    {
    highScore_is_loaded=1;

    if (load_scoreboard(ptr_score_board) !=0)
    {
    save_scoreboard(ptr_new_score_board);

    load_scoreboard(ptr_score_board);

    }
    }

    if (option == o_hall_of_fame_new_entry)
    {

    if(ptrelement->player.total_score>0)
    {
    size_t size = sizeof(ptrelement->player.total_score_buffer);

    strncpy(playerPoints,ptrelement->player.total_score_buffer,size);
    strncpy(playerNamePoints,playerPoints,MAX_LETTERS);
    }

    tu_jump :

    strncpy(entryPoints,score_board[positionHighscore],MAX_DIGITS_SCORES);

    val = atoi(playerPoints);
    val2 = atoi(entryPoints);

    if((val>=val2) && (positionHighscore>=0) && (positionHighscore<MAX_ENTRIES))

    {
    new_entry=1;

    strncpy(tmpNamePoints,score_board[positionHighscore],MAX_LETTERS);
    strncpy(score_board[positionHighscore],playerNamePoints,MAX_LETTERS);
    if(positionHighscore<(MAX_ENTRIES-1))
    {
    strncpy(score_board[positionHighscore+1],tmpNamePoints,MAX_LETTERS);
    }

    positionHighscore--;

    goto tu_jump;

    }

    if ((new_entry==1))
    {
    new_entry=new_entry_read_string(score_board[positionHighscore+1], MAX_LETTERS, ptrelement);

    if (new_entry==2)
    {
    save_scoreboard(ptr_score_board);
    }
    }
    else
    {
    highScore_is_loaded=0;
    positionHighscore=9;
    new_entry =0;

    rest(1000);

    return  option=o_draw_menu;

    }

    }; // if

    if (language == english)
    {
    textout_centre_ex(hall_of_fame_bmp,font_menu,"High scores",SCREEN_w/2,30,GREY,-1);
    }

    if (language == polish)
    {
    textout_centre_ex(hall_of_fame_bmp,font_menu,"Najlepsze wyniki",SCREEN_w/2,30,GREY,-1);
    }


    int ii,jj;
    for (ii=0;ii<MAX_ENTRIES;ii++)
    {
    tutu:
    for (jj=0;jj<MAX_LETTERS;jj++)
    {
    if (score_board[ii][jj]=='\n')
    {
    if (ii<(MAX_ENTRIES))
    {
    ii++;
    goto tutu;
    }
    }

    if (ii<(MAX_ENTRIES))
    {
    textprintf_centre_ex(hall_of_fame_bmp,font_menu,(SCREEN_w-MAX_LETTERS*(text_length(font_menu,"A")))/2+jj*(text_length(font_menu,"A")),70+ii*(text_height(font_menu)+2),GREY,-1,"%c",score_board[ii][jj]);

    if((option==o_hall_of_fame_new_entry) && (ii==(positionHighscore+1)))

    {
    textprintf_centre_ex(hall_of_fame_bmp,font_menu,(SCREEN_w-MAX_LETTERS*(text_length(font_menu,"A")))/2+jj*(text_length(font_menu,"A")),70+ii*(text_height(font_menu)+2),WHITE,-1,"%c",score_board[ii][jj]);
    }

    } // if
    }; // for
    }; // for

    if(option==o_hall_of_fame_new_entry)
    {

    if (language == english)
    {
    textout_centre_ex(hall_of_fame_bmp,font_menu, "Enter your name", SCREEN_w/2,SCREEN_h-50, GREY,-1);
    }

    if (language == polish)
    {
    textout_centre_ex(hall_of_fame_bmp,font_menu, "Wprowadź swoje imię", SCREEN_w/2,SCREEN_h-50, GREY,-1);
    }

    }; // if

    if(option==o_hall_of_fame_draw)
    {

    if (language == english)
    {
    textout_centre_ex(hall_of_fame_bmp,font_menu, "Press any key or move the mouse to exit", SCREEN_w/2,SCREEN_h-50, GREY,-1);
    }

    if (language == polish)
    {
    textout_centre_ex(hall_of_fame_bmp,font_menu, "Naciśnij dowolny klawisz lub rusz myszką aby wyjść", SCREEN_w/2,SCREEN_h-50, GREY,-1);
    }

    }; // if

    draw_sprite(buffer,hall_of_fame_bmp,0,0);

    if (option == o_hall_of_fame_new_entry) return option = o_hall_of_fame_new_entry;


    return option = o_hall_of_fame_draw;

} // hall_of_fame_entry()

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//
void draw_title(BITMAP *buffer,BITMAP *bmp_obj,unsigned char TitleMap[MAP_Y_24][MAP_X_32],int element)
{

    static BITMAP *title_bmp=NULL;
    static int t_height;
    int x,y;
    static int delta_x=1;
    static int delta_y=1;

    t_height = text_height(font_menu);

	if (title_bmp==NULL)
	{
	title_bmp=create_bitmap(SCREEN_w,SCREEN_h);
	}

    clear_to_color(title_bmp,makecol(0,0,0));

    for(x=0;x<MAP_X_32;x++)
    {
        for (y=0;y<MAP_Y_24;y++)
        {
        if (TitleMap[y][x]==element)
        {
        stretch_blit(bmp_obj,title_bmp,0,0,bmp_obj->w,bmp_obj->h,2*x*delta_x+MAX_X,2*y*delta_y,delta_x,delta_y);
        };

        if (delta_x<((bmp_obj->w)/2))
        {
        delta_x++;delta_y++;
        } // if
        }; // for
    }; // for
        if (language == english)
        {
        textout_centre_ex(title_bmp,font_menu,"Please press SPACE or left mouse button",SCREEN_w/2,SCREEN_h-4*t_height,GREY,-1);
        }

        if (language == polish)
        {
        textout_centre_ex(title_bmp,font_menu,"Proszę nacisnąć SPACJĘ lub lewy przycisk myszki",SCREEN_w/2,SCREEN_h-4*t_height,GREY,-1);
        }


        draw_sprite(buffer,title_bmp,0,0);

};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//
int draw_game_over(BITMAP *buffer,BITMAP *bmp_obj,unsigned char GameOverMap[MAP_Y_24][MAP_X_32],int element,TElement * ptrelement, int ptrwait)

{

    int x,y;
    static int delta_x=0;
    static int delta_y=0;
    static int ticker=0;

    for(x=0;x<MAP_X_32;x++)
    {
        for (y=0;y<MAP_Y_24;y++)
        {
        if (GameOverMap[y][x]==element)
        {
        masked_stretch_blit(bmp_obj,buffer,0,0,bmp_obj->w,bmp_obj->h,x*delta_x,y*delta_y,delta_x,delta_y);
        }
        }; // for
    }; // for

    if (ptrwait == 0)
    {
    if (delta_x<(bmp_obj->w))
    {
    delta_x++;delta_y++;};
    ticker++;
    }

    if (ticker>(time_of_animation))
    {
    ticker=0;
    delta_x=0;
    delta_y=0;
    clear_bitmap(buffer);

    ptrelement->player.total_score=ptrelement->player.points;
    sprintf(ptrelement->player.total_score_buffer, "%d", ptrelement->player.total_score);

    return (option=o_hall_of_fame_new_entry);


    }; // if

    textprintf_centre_ex(buffer,font_menu,SCREEN_w/2,MAX_Y*2,GREY,-1,"Your Points : %d",ptrelement->player.points);
    return (option=o_draw_game_over);

 } // draw_game_over()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// the function returns 1 is the next stage, if 0 then not yet, if 2 then end the boards and display game_over
int draw_next_stage(BITMAP *buffer,BITMAP *bmp_obj,unsigned char NextStageMap[MAP_Y_24][MAP_X_32],int element, int ptrwait)
{

    int x,y;
    static int delta_x=0;
    static int delta_y=0;
    static int ticker=0;
    for(x=0;x<MAP_X_32;x++)
    {
        for (y=0;y<MAP_Y_24;y++)
        {
        if (NextStageMap[y][x]==element)
        masked_stretch_blit(bmp_obj,buffer,0,0,bmp_obj->w,bmp_obj->h,x*delta_x,y*delta_y,delta_x,delta_y);
        };
    }; // for

    if (ptrwait==0)
    {
    if (delta_x<(bmp_obj->w))
    {
    delta_x++;delta_y++;
    }
    ticker++;
    }; // if

    if (ticker>(time_of_animation))
    {
    ticker=0;
    delta_x=0;
    delta_y=0;
    clear_bitmap(buffer);

    if (option==o_draw_next_stage_demo)

    {
    return option=o_play_game_demo;
    } // if

    return option=o_play_game;
    }; // if

    if (option==o_draw_next_stage_demo)
    {
    return option=o_draw_next_stage_demo;
    }

    return option=o_draw_next_stage;

} // draw_next_stage()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//

void draw_menu(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X], TElement * ptrelement, int ptrwait)
{

    static int i,t_width,t_height;
    static int pos_menu ;
    static  BITMAP *mouse_cursor=NULL;

    static int old_mouse_y = 0;
    static char *column_menu;
    static char *text_menu[MAX_POS_MENU+1];
    static int kdown=0,kup=0;
    static BITMAP *bmp_menu=NULL;

    if (language == english)
    {
    t_width = text_length(font_menu, "PLAY  ");
    }
    if (language == polish)
    {
    t_width = text_length(font_menu, "GRAJ  ");
    }

    t_height = text_height(font_menu);


    if (mouse_cursor==NULL)
    {
    mouse_cursor=create_bitmap(25,25);

    clear_to_color(mouse_cursor,CLEAR);
    circle(mouse_cursor,12,12,12,GREY);
    circle(mouse_cursor,12,12,10,GREY);

    line(mouse_cursor,0,12,25,12,GREY);
    line(mouse_cursor,12,0,12,25,GREY);
    }; // if

    if (bmp_menu==NULL)

    {
    bmp_menu=create_bitmap(SCREEN_w,SCREEN_h);
    column_menu = malloc(MAX_POS_MENU*sizeof(char));

    for (i=1;i<=MAX_POS_MENU;i++)

    {
    text_menu[i]=malloc(6*5*sizeof(char));                                          //reserve 30 characters each
    }

    pos_menu=1;
    }

    if (language == english)
    {
        strcpy(text_menu[1],"PLAY  ");
        strcpy(text_menu[2],"OPTIONS");
        strcpy(text_menu[3],"EDITOR");
        strcpy(text_menu[4],"INFO  ");
        strcpy(text_menu[5],"EXIT  ");
    }
    if (language == polish)
    {
        strcpy(text_menu[1],"GRAJ  ");
        strcpy(text_menu[2],"OPCJE ");
        strcpy(text_menu[3],"EDYTOR");
        strcpy(text_menu[4],"INFO  ");
        strcpy(text_menu[5],"WYJDŹ ");
    }

    clear(bmp_menu);

    for (i=1;i<=MAX_POS_MENU;i++)
    {
    column_menu[i]=200;
    };

    if(!(key[KEY_DOWN]))
    {
    kdown=0;
    }                                                                          // key up

    if (kdown==0)
    {
    if(key[KEY_DOWN])
    {
    kdown=1;                                                                    //key down
    pos_menu++;

    if (pos_menu>MAX_POS_MENU)
    {
    pos_menu=MAX_POS_MENU;
    }

    } // if
    }; // if


    if(!(key[KEY_UP]))
    {
    kup=0;
    }


    if (kup==0)
    {
    if(key[KEY_UP])
    {
    kup=1;
    pos_menu--;
    if (pos_menu<1)
    {
    pos_menu=1;
    }
    } // if
    }; // if

    column_menu[pos_menu]=200;

    // *-  marker next to the text
    textout(bmp_menu,font_menu,"*",(SCREEN_w-t_width)/2-40,2*t_height+pos_menu*t_height+t_height/4,WHITE);
    textout(bmp_menu,font_menu,"*",(SCREEN_w-t_width)/2+100+MAX_Y,2*t_height+pos_menu*t_height+t_height/4,WHITE);
    // -*

    for (i=1;i<=MAX_POS_MENU;i++)
    {
    textout(bmp_menu,font_menu,text_menu[i],(SCREEN_w-t_width)/2,2*t_height+i*t_height,GREY);
    }

    if (language == english)
    {
    textout_centre_ex(bmp_menu,font_menu,"Please select and press ENTER",SCREEN_w/2,SCREEN_h-2*t_height,GREY,-1);
    }

    if (language == polish)
    {
    textout_centre_ex(bmp_menu,font_menu,"Proszę wybrać i wcisnąć ENTER",SCREEN_w/2,SCREEN_h-2*t_height,GREY,-1);
    }

    show_mouse(bmp_menu);
    set_mouse_sprite(mouse_cursor);
    blit(bmp_menu,buffer,0,0,0,0,SCREEN_w,SCREEN_h);

    if (old_mouse_y!=mouse_y)
    {
    old_mouse_y=mouse_y;

        for (i=1;i<=MAX_POS_MENU;i++)
        {
        if ((mouse_y>(2*t_height+i*t_height))&&(mouse_y<(2*t_height+i*t_height+t_height-20)))
        {
        pos_menu=i;
        break;
        }
        }; // for


    }; // if

    static int enterup=0;

    if(!(key[KEY_ENTER]))
    {
    enterup=0;
    }

    if (enterup==0)
    {
    if((key[KEY_ENTER]) || (mouse_b & 1))    //space or left mouse button
    {
    enterup=1;
    rest(1000);

    if (option==o_draw_menu)
    switch(pos_menu)
    {
    case 1:
    {
    option=o_new_game;
    break;
    }

    case 2:
    {
    option=o_draw_menu_options;
    break;
    };

    case 3:
    {
    option=o_editor_load_stages;
    break;
    }

    case 4:
    {
    option=o_draw_info;
    ptrelement->startscroll=1;
    break;
    }

    case 5:
    {
    option=o_exit;
    break;
    }

    } // switch
    } // if
    }; // if

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// function called from draw menu function. It informs about the rules of the game.

void draw_info(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X], TElement * ptrelement, int ptrwait)
{
    static BITMAP *info_bmp=NULL;
    static BITMAP *info_bmp2=NULL;

    static int t_height;


    static int delta_y=1;
    static int vline=380;                                                           // shift
    if (ptrelement->startscroll == 1)
    {
    vline=380;
    }
    ptrelement->startscroll=0;

    if (ptrwait == 0)
    {
    delta_y+=1;
    if (!(delta_y%2))
    {
    vline-=1;
    }
    } // if

    if (vline<(-SCREEN_h-150))
    {
    vline= SCREEN_h-100;
    }


    /*
    if (language == english)
    {
    t_width = text_length(font_menu,"Press any key to exit");
    }

    if (language == polish)
    {
    t_width = text_length(font_menu,"Naciśnij dowolny klawisz aby wyjść");
    }
    */

    t_height = text_height(font_menu);

	if (info_bmp==NULL)
	{
	info_bmp=create_bitmap(SCREEN_w,SCREEN_h*2);
	}

	clear_to_color(info_bmp,makecol(0,0,0));

    if (info_bmp2==NULL)
    {
    info_bmp2=create_bitmap(SCREEN_w,4*t_height);
    }

    clear_to_color(info_bmp2,makecol(0,0,0));


    if (language == english)
    {
    textout_centre_ex(info_bmp,font,"                            BLAST game rules.                           ",SCREEN_w/2,60+vline,GREY,-1);
    textout_centre_ex(info_bmp,font,"                 A spaceship controlled by a player                     ",SCREEN_w/2,75+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                should be carried out thought all stages                ",SCREEN_w/2,90+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                in the shortest possible time. Destroy                  ",SCREEN_w/2,105+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                all 'death stars' encountered and watch                 ",SCREEN_w/2,120+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                out for strangers.                                      ",SCREEN_w/2,135+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,150+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                You have a fleet of three ships at your di-             ",SCREEN_w/2,165+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                sposal. Each of them equipped with a cannon             ",SCREEN_w/2,180+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                with twenty bullets and lasers.                         ",SCREEN_w/2,195+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                When the ship gets stuck on the board, de-              ",SCREEN_w/2,210+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                tonate it using the F1 key. Then you will               ",SCREEN_w/2,225+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                start the next ship journey.                            ",SCREEN_w/2,240+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                There are 3 levels of difficulty in the game.           ",SCREEN_w/2,255+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,270+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                As an addition, there is a stage editor                 ",SCREEN_w/2,285+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                in which you can create any board from the              ",SCREEN_w/2,300+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                available elements.                                     ",SCREEN_w/2,315+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Take the challenge as a ship's pilot.                   ",SCREEN_w/2,330+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Enjoy.                                                  ",SCREEN_w/2,345+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,360+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Controlling:                                            ",SCREEN_w/2,375+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Motility - WSAD buttons, arrows or left Joypad          ",SCREEN_w/2,390+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                           knob.                                        ",SCREEN_w/2,405+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Hull rotation - Left CONTROL and direction,             ",SCREEN_w/2,420+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                right Joypad knob.                      ",SCREEN_w/2,435+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Ammo - SPACE, Joypad button.                            ",SCREEN_w/2,450+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Laser - Right CONTROL, Joypad button.                   ",SCREEN_w/2,465+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,480+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,495+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,510+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                The game is created with use libraries:                 ",SCREEN_w/2,525+vline,GREY,-1);
    textout_centre_ex(info_bmp,font,"                -Allegro 4.2 (by) Shawn Hargreaves.                     ",SCREEN_w/2,540+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                -JGMOD 0.99 (by) Jeffery Guan.                          ",SCREEN_w/2,555+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,570+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Music: X-Ray - Grayscale Project (Atari/PC).            ",SCREEN_w/2,585+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Graphics and programming: Sylvi91 MARTE.BEST            ",SCREEN_w/2,600+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,615+vline,WHITE,-1);

    textout_centre_ex(info_bmp,font_menu,"                                                                            ",SCREEN_w/2,0,WHITE,BLACK);

    textout_centre_ex(info_bmp,font_menu,"                          Blast v 1.2 SE MARTE.BEST                         ",SCREEN_w/2,29,WHITE,BLACK);  // 29 not 30 to not flickering
    textout_centre_ex(info_bmp,font_menu,"                                                                            ",SCREEN_w/2,58,WHITE,BLACK);

    textout_centre_ex(info_bmp2,font_menu,"Press any key or move the mouse to exit",SCREEN_w/2,0,GREY,-1);
    }




    if (language == polish)
    {
    textout_centre_ex(info_bmp,font,"                            Zasady gry BLAST.                           ",SCREEN_w/2,60+vline,GREY,-1);
    textout_centre_ex(info_bmp,font,"                 Statek kosmiczny, którym steruje gracz                 ",SCREEN_w/2,75+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                należy przeprowadzić przez wszystkie et-                ",SCREEN_w/2,90+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                apy, w jak najkrótszym czasie. Zniszczyć                ",SCREEN_w/2,105+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                wszystkie napotkane 'gwiazdy śmierci' i                 ",SCREEN_w/2,120+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                uważać na obcych.                                       ",SCREEN_w/2,135+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,150+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Do dyspozycji masz flotę trzech statków,                ",SCREEN_w/2,165+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                każdy z nich wyposażony w działo z dwu-                 ",SCREEN_w/2,180+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                dziestoma pociskami i laserami.                         ",SCREEN_w/2,195+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                W momencie gdy statek utknie na planszy                 ",SCREEN_w/2,210+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                zdetonuj go używając klawisza F1. Wtedy                 ",SCREEN_w/2,225+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                zaczniesz podróż następnym.                             ",SCREEN_w/2,240+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                W grze są 3 poziomy trudności.                          ",SCREEN_w/2,255+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,270+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Jako dodatek, jest editor etapów, w któ-                ",SCREEN_w/2,285+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                rym można stworzyć dowolną planszę z dos-               ",SCREEN_w/2,300+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                tępnych elementów.                                      ",SCREEN_w/2,315+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Podejmij wyzwanie jako pilot statku.                    ",SCREEN_w/2,330+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Powodzenia.                                             ",SCREEN_w/2,345+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,360+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Sterowanie:                                             ",SCREEN_w/2,375+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Poruszanie się - klawisze WSAD, strzałki                ",SCREEN_w/2,390+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                 lewa gałka Joypada                     ",SCREEN_w/2,405+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Obrót kadłuba - Lewy CONTROL i kierunek lub             ",SCREEN_w/2,420+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                prawa gałka Joypada                     ",SCREEN_w/2,435+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Pociski - SPACJA, przycisk Joypada                      ",SCREEN_w/2,450+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Laser - Prawy CONTROL, przycisk Joypada                 ",SCREEN_w/2,465+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,480+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,495+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,510+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Gra powstała z użyciem bibliotek:                       ",SCREEN_w/2,525+vline,GREY,-1);
    textout_centre_ex(info_bmp,font,"                -Allegro 4.2 (by) Shawn Hargreaves.                     ",SCREEN_w/2,540+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                -JGMOD 0.99 (by) Jeffery Guan.                          ",SCREEN_w/2,555+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,570+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Muzyka: X-Ray - Grayscale Project (Atari/PC).           ",SCREEN_w/2,585+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                Grafika i programowanie: Sylvi91 MARTE.BEST.            ",SCREEN_w/2,600+vline,WHITE,-1);
    textout_centre_ex(info_bmp,font,"                                                                        ",SCREEN_w/2,615+vline,WHITE,-1);

    textout_centre_ex(info_bmp,font_menu,"                                                                            ",SCREEN_w/2,0,WHITE,BLACK);

    textout_centre_ex(info_bmp,font_menu,"                          Blast v 1.2 SE MARTE.BEST                         ",SCREEN_w/2,29,WHITE,BLACK);  // 29 not 30 to not flickering
    textout_centre_ex(info_bmp,font_menu,"                                                                            ",SCREEN_w/2,58,WHITE,BLACK);

    textout_centre_ex(info_bmp2,font_menu,"Naciśnij dowolny klawisz lub rusz myszką aby wyjść",SCREEN_w/2,0,GREY,-1);
    }

    // X-Ray Grayscale Project Atari Scene Screamtracker 3     (Łukasz Sychowicz)

    draw_sprite(buffer,info_bmp,0,0);
    draw_sprite(buffer,info_bmp2,0,SCREEN_h-2*t_height);

} // draw_info()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// function called from draw menu function
int draw_menu_options(BITMAP *buffer,BITMAP *bmp_obj,int Map[MAX_STAGE][MAP_Y][MAP_X],int MUSIC_NUMBER)
{


////////////// START Section CREATE
////////////////////////////////////////////////////

#define MAX_POS_MENU_OPTIONS 6


    static int i,t_width,t_height;
    static int pos_menu=3+1 ;
    static BITMAP *mouse_cursor=NULL;
    static int old_mouse_y;
    static char *column_menu;
    static char *text_menu[MAX_POS_MENU_OPTIONS+1];
    static int kdown=0,kup=0;
    static int kleft=0,kright=0;
    static int enterup=1;

#ifdef jgmod
    static int music_vol_increase_x=50;                                                     // for drawing lines and setting the volume multiplied by 2.5
    static int max_sound_bar_lenght=100;
#endif // jgmod


    static BITMAP *bmp_menu=NULL;
    static BITMAP *bmp_submenu_graphics=NULL;
    static BITMAP *bmp_submenu_music=NULL;
    static BITMAP *bmp_submenu_ctrl=NULL;
    static BITMAP *bmp_submenu_difficulties=NULL;
    static BITMAP *bmp_submenu_lang=NULL;

    if (language == english)
    {
    t_width = text_length(font_menu, "GRAPHICS  ");
    }

    if (language == polish)
    {
    t_width = text_length(font_menu, "GRAFIKA   ");
    }


    t_height = text_height(font_menu);

    if (mouse_cursor==NULL)
    {
    mouse_cursor=create_bitmap(25,25);
    clear_to_color(mouse_cursor,CLEAR);

    circle(mouse_cursor,12,12,12,GREY);
    circle(mouse_cursor,12,12,10,GREY);

    line(mouse_cursor,0,12,25,12,GREY);
    line(mouse_cursor,12,0,12,25,GREY);
    };

    if (bmp_menu==NULL)
    {
    bmp_menu=create_bitmap(SCREEN_w,SCREEN_h);
    column_menu = malloc(MAX_POS_MENU_OPTIONS*sizeof(char));

    for (i=1;i<=MAX_POS_MENU_OPTIONS;i++)
    {
    text_menu[i]=malloc(40*sizeof(char));                                           // reserve 40 characters each
    }

    pos_menu=3;
    };

    if (language == english)
    {
        strcpy(text_menu[1],"GRAPHICS   ");
        strcpy(text_menu[2],"MUSIC      ");
        strcpy(text_menu[3],"CONTROLLERS");
        strcpy(text_menu[4],"LEVEL      ");
        strcpy(text_menu[5],"LANGUAGE   ");
        strcpy(text_menu[6],"BACK       ");
    }

     if (language == polish)
    {
        strcpy(text_menu[1],"GRAFIKA    ");
        strcpy(text_menu[2],"MUZYKA     ");
        strcpy(text_menu[3],"STEROWANIE ");
        strcpy(text_menu[4],"POZIOM     ");
        strcpy(text_menu[5],"JĘZYK      ");
        strcpy(text_menu[6],"POWRÓT     ");
    }

    if (bmp_submenu_graphics==NULL)

    {
    bmp_submenu_graphics=create_bitmap(SCREEN_w,SCREEN_h/10);
    };

    if (bmp_submenu_music==NULL)

    {
    bmp_submenu_music=create_bitmap(SCREEN_w,SCREEN_h/10);
    };

    if (bmp_submenu_ctrl==NULL)

    {
    bmp_submenu_ctrl=create_bitmap(SCREEN_w,SCREEN_h/10);
    };

    if (bmp_submenu_difficulties==NULL)

    {
    bmp_submenu_difficulties=create_bitmap(SCREEN_w,SCREEN_h/10);
    };

    if (bmp_submenu_lang==NULL)

    {
    bmp_submenu_lang=create_bitmap(SCREEN_w,SCREEN_h/10);
    };

////////////// END Section CREATE
////////////////////////////////////////////////////

    clear(bmp_menu);
    clear_to_color(bmp_submenu_graphics,GREY);
    clear_to_color(bmp_submenu_music,GREY);
    clear_to_color(bmp_submenu_ctrl,GREY);
    clear_to_color(bmp_submenu_difficulties,GREY);
    clear_to_color(bmp_submenu_lang,GREY);

    for (i=1;i<=MAX_POS_MENU_OPTIONS;i++)
    {
    column_menu[i]=200;
    };

    if(!(key[KEY_DOWN]))
    {
    kdown=0;                                                                        // key up
    }

    if (kdown==0)
    {
    if(key[KEY_DOWN])
    {
    kdown=1;                                                                        // key down
    pos_menu++;
    if (pos_menu>MAX_POS_MENU_OPTIONS)
    {
    pos_menu=MAX_POS_MENU_OPTIONS;
    }
    } // if
    }; // if

    if(!(key[KEY_UP]))
    {
    kup=0;
    }

    if (kup==0)
    {
    if(key[KEY_UP])
    {
    kup=1;                                                                          // key down
    pos_menu--;
    if (pos_menu<1)
    {
    pos_menu=1;
    }
    } // if
    }; // if


    column_menu[pos_menu]=200;

    /// *-  marker next to the text
    textout(bmp_menu,font_menu,"*",(SCREEN_w-t_width)/2-40,2*t_height+pos_menu*t_height+t_height/4,WHITE);
    textout(bmp_menu,font_menu,"*",(SCREEN_w-t_width)/2+120+MAX_Y,2*t_height+pos_menu*t_height+t_height/4,WHITE);
    /// -*

    for (i=1;i<=MAX_POS_MENU_OPTIONS;i++)
    {
    textout(bmp_menu,font_menu,text_menu[i],(SCREEN_w-t_width)/2,2*t_height+i*t_height,GREY);
    }

    if (language == english)
    {
    textout_centre_ex(bmp_menu,font_menu,"Please use arrows",SCREEN_w/2,SCREEN_h-2*t_height,GREY,-1);
    }

    if (language == polish)
    {
    textout_centre_ex(bmp_menu,font_menu,"Proszę używać strzałek",SCREEN_w/2,SCREEN_h-2*t_height,GREY,-1);
    }

    show_mouse(bmp_menu);

    set_mouse_sprite(mouse_cursor);

    if (old_mouse_y!=mouse_y)
    {
    old_mouse_y=mouse_y;

    for (i=1;i<=MAX_POS_MENU_OPTIONS;i++)
    {
        if ((mouse_y>(2*t_height+i*t_height))&&(mouse_y<(2*t_height+i*t_height+t_height-20)))
        {
        pos_menu=i;break;
        }
    }
    }; // if

////////////// START Section READ KEY
////////////////////////////////////////////////////

    if (option==o_draw_menu_options)
    switch(pos_menu)
    {
    // SUBMENU GRAPHICS
    case 1:
    {
    if(!(key[KEY_ENTER]))
    {
    enterup=0;
    }

    if (enterup==0)
    {
    if(key[KEY_ENTER])
    {
    enterup=1;
    set_mouse_sprite(NULL);
    set_resolution();
    set_palette(*mono_palette);
    set_mouse_sprite(mouse_cursor);
    }
    }; // if


    if (language == english)
    {
    textout_centre_ex(bmp_submenu_graphics,font_menu,"Press ENTER to setup",SCREEN_w/2,(SCREEN_h/10-t_height)/2,BLACK,-1);
    }
    if (language == polish)
    {
    textout_centre_ex(bmp_submenu_graphics,font_menu,"Wciśnij ENTER do zmiany ustawień",SCREEN_w/2,(SCREEN_h/10-t_height)/2,BLACK,-1);
    }


    blit(bmp_submenu_graphics,bmp_menu,0,0,0,SCREEN_h/2+70,SCREEN_w,SCREEN_h);

    break;

    }

    case 2:
    {

#ifdef jgmod

    if (!(key[KEY_ENTER])) enterup=1;
    if (enterup==1)

    if (key[KEY_ENTER])
    {
    enterup=0;
    play_mod(mod[MUSIC_NUMBER],FALSE);
    MUSIC_NUMBER++;
    if (MUSIC_NUMBER>=(MAX_MOD))
    {
    MUSIC_NUMBER=0;
    }

    play_mod(mod[MUSIC_NUMBER],TRUE);

    }


    if(!(key[KEY_LEFT]))
    {
    kleft=0;
    }

    if (kleft==0)
    {
    if(key[KEY_LEFT])
    {
    kleft=1;
    music_vol_increase_x=music_vol_increase_x-1;
    }
    };

    if(!(key[KEY_RIGHT]))
    {
    kright=0;
    }


    if (kright==0)
    {
    if(key[KEY_RIGHT])
    {
    kright=1;
    music_vol_increase_x=music_vol_increase_x+1;
    }
    };


    if (music_vol_increase_x>=max_sound_bar_lenght) music_vol_increase_x=max_sound_bar_lenght;
    if (music_vol_increase_x<=0)
    {
    music_vol_increase_x=0;
    }

    set_mod_volume(music_vol_increase_x*1.25);  // vol (0 - 255) from jgmod manual

    line(bmp_submenu_music,(SCREEN_w-max_sound_bar_lenght)/2,20,(SCREEN_w-max_sound_bar_lenght)/2+(max_sound_bar_lenght),20,BLACK);
    line(bmp_submenu_music,(SCREEN_w-max_sound_bar_lenght)/2,22,(SCREEN_w-max_sound_bar_lenght)/2+(max_sound_bar_lenght),22,BLACK);
    line(bmp_submenu_music,(SCREEN_w-max_sound_bar_lenght)/2,24,(SCREEN_w-max_sound_bar_lenght)/2+(max_sound_bar_lenght),24,BLACK);
    line(bmp_submenu_music,(SCREEN_w-max_sound_bar_lenght)/2,26,(SCREEN_w-max_sound_bar_lenght)/2+(max_sound_bar_lenght),26,BLACK);

    int ay=0;

    for (ay=15;ay<31;ay++)
    {
    line(bmp_submenu_music,(SCREEN_w-max_sound_bar_lenght)/2+(music_vol_increase_x-2),ay,(SCREEN_w-max_sound_bar_lenght)/2+(music_vol_increase_x+2),ay,BLACK);
    }

    if (language == english)
    {
    textout_ex(bmp_submenu_music,font_menu," ENTER - change music",10,(SCREEN_h/10-t_height)/2,BLACK,-1);
    textout_ex(bmp_submenu_music,font_menu,"<-> - change volume",(SCREEN_w-10-text_length(font_menu,"<-> - change volume")),(SCREEN_h/10-t_height)/2,BLACK,-1);
    }

    if (language == polish)
    {
    textout_ex(bmp_submenu_music,font_menu," ENTER - zmiana muzyki",10,(SCREEN_h/10-t_height)/2,BLACK,-1);
    textout_ex(bmp_submenu_music,font_menu,"<-> - zmiana głośności",(SCREEN_w-10-text_length(font_menu,"<-> - zmiana głośności")),(SCREEN_h/10-t_height)/2,BLACK,-1);
    }



#else

    if (language == english)
    {
    textout_ex(bmp_submenu_music,font_menu," Sound not installed!  ",10,(SCREEN_h/10-t_height)/2,BLACK,-1);
    textout_ex(bmp_submenu_music,font_menu," JGMOD is OFF!!!       ",(SCREEN_w-10-text_length(font_menu," JGMOD is OFF!!!       ")),(SCREEN_h/10-t_height)/2,BLACK,-1);
    }

    if (language == polish)
    {
    textout_ex(bmp_submenu_music,font_menu," Brak dźwięku!        ",10,(SCREEN_h/10-t_height)/2,BLACK,-1);
    textout_ex(bmp_submenu_music,font_menu," JGMOD jest wyłączony!",(SCREEN_w-10-text_length(font_menu," JGMOD jest wyłączony!")),(SCREEN_h/10-t_height)/2,BLACK,-1);
    }

#endif





    blit(bmp_submenu_music,bmp_menu,0,0,0,SCREEN_h/2+70,SCREEN_w,SCREEN_h);

    break;
    };

    //////// SUBMENU CONTROLLERS

    case 3:
    {

    int static controller1 =arrows;
    int COLOR_CNTRL[3] = {WHITE,BLACK,BLACK};

    COLOR_CNTRL[0] = BLACK;
    COLOR_CNTRL[1] = BLACK;
    COLOR_CNTRL[2] = BLACK;

    if(!(key[KEY_LEFT]))
    {
    kleft=0;
    }

    if (kleft==0)
    {
    if(key[KEY_LEFT])
    {
    kleft=1;
    controller1--;
    if (controller1<0)
    {
    controller1=2;
    }
    }
    };


    if(!(key[KEY_RIGHT]))
    {
    kright=0;
    }

    if (kright==0)
    {
    if(key[KEY_RIGHT])
    {
    kright=1;
    controller1++;

    if (controller1>2)
    {
    controller1=0;
    }
    }
    };

    COLOR_CNTRL[controller1] = WHITE;

    controller=controller1;           /////  enum Tcontroller {wsad, arrows, joypad};

    static int calibrate = 0;

    if (controller1==joypad)
    {

    if (!num_joysticks)
    {
    remove_joystick();

    if (language == english)
    {
    allegro_message("Error: joypad not found! Please plug in joypad and press Enter.\n");
    }

    if (language == polish)
    {
    allegro_message("Błąd: joypad nie wykryty! Proszę podłączyć joypad i nacisnąć Enter.\n");
    }

    /* the first thing is to initialise the joystick driver */
    if (install_joystick(JOY_TYPE_AUTODETECT) != 0)
    {
    if (language == english)
    {
    allegro_message("Error initialising joypad.\n%s\n", allegro_error);
    }

    if (language == polish)
    {
    allegro_message("Błąd inicjalizacji joypada.\n%s\n", allegro_error);
    }
    }

    else

    {

    if (num_joysticks)

    {
    if (language == english)
    {
    allegro_message("Joypad found! Please press Enter to calibrate!");
    }

    if (language == polish)
    {
    allegro_message("Joypad wykryty! Proszę wcisnąc Enter aby skalibrować!");
    }

    if (calibrate_joypad(bmp_menu)==0)
    {
    calibrate=1;
    controller=joypad;
    }
    } // if

    else

    {
    if (language == english)
    {
    allegro_message("Error: Sorry, but joypad can't be detected!");
    }

    if (language == polish)
    {
    allegro_message("Błąd: Przepraszam, ale Joypad nie może zostać wykryty!");
    }
    controller1=arrows;
    }
    }
    }

    else

    {
    if (calibrate ==0)
    {

    if (language == english)
    {
    allegro_message("Joypad OK! Please press Enter to calibrate!");
    }

    if (language == polish)
    {
    allegro_message("Joypad OK! Proszę nacisnąć Enter aby skalibrować!");
    }

    if (calibrate_joypad(bmp_menu)==0)
    {
    calibrate=1;
    controller=joypad;
    }
    }; // if
    }; // else
    }; // if

    if (language == english)
    {
    textout_ex(bmp_submenu_ctrl,font_menu,"WSAD",(0+text_length(font_menu,"WSAD")),(SCREEN_h/10-t_height)/2,COLOR_CNTRL[0],-1);
    textout_ex(bmp_submenu_ctrl,font_menu,"ARROWS",(SCREEN_w-text_length(font_menu,"ARROWS"))/2,(SCREEN_h/10-t_height)/2,COLOR_CNTRL[1],-1);
    textout_ex(bmp_submenu_ctrl,font_menu,"JOYPAD",(SCREEN_w-2*text_length(font_menu,"JOYPAD")),(SCREEN_h/10-t_height)/2,COLOR_CNTRL[2],-1);
    }

    if (language == polish)
    {
    textout_ex(bmp_submenu_ctrl,font_menu,"WSAD",(0+text_length(font_menu,"WSAD")),(SCREEN_h/10-t_height)/2,COLOR_CNTRL[0],-1);
    textout_ex(bmp_submenu_ctrl,font_menu,"STRZAŁKI",(SCREEN_w-text_length(font_menu,"STRZAŁKI"))/2,(SCREEN_h/10-t_height)/2,COLOR_CNTRL[1],-1);
    textout_ex(bmp_submenu_ctrl,font_menu,"JOYPAD",(SCREEN_w-2*text_length(font_menu,"JOYPAD")),(SCREEN_h/10-t_height)/2,COLOR_CNTRL[2],-1);
    }

    blit(bmp_submenu_ctrl,bmp_menu,0,0,0,SCREEN_h/2+70,SCREEN_w,SCREEN_h); // wyrzuc menu _menu do buffera

    break;
    }

    case 4:
    {
    int static difficulty1 =0;
    int COLOR_DIFF[3] = {WHITE,BLACK,BLACK};
    COLOR_DIFF[0] = BLACK;
    COLOR_DIFF[1] = BLACK;
    COLOR_DIFF[2] = BLACK;

    if(!(key[KEY_LEFT]))
    {
    kleft=0;
    }

    if (kleft==0)
    {
    if(key[KEY_LEFT])
    {
    kleft=1;
    difficulty1--;
    if (difficulty1<0)
    {
    difficulty1=2;
    }
    } // if
    }; // if

    if(!(key[KEY_RIGHT]))
    {
    kright=0;
    }

    if (kright==0)
    {
    if(key[KEY_RIGHT])
    {
    kright=1;
    difficulty1++;
    if (difficulty1>2)
    {
    difficulty1=0;
    }
    } // if
    }; // if

    COLOR_DIFF[difficulty1] = WHITE;

    difficulty=difficulty1;

    if (language == english)
    {
    textout_ex(bmp_submenu_difficulties,font_menu,"EASY",(0+text_length(font_menu,"EASY")),(SCREEN_h/10-t_height)/2,COLOR_DIFF[0],-1);
    textout_ex(bmp_submenu_difficulties,font_menu,"MEDIUM",(SCREEN_w-text_length(font_menu,"MEDIUM"))/2,(SCREEN_h/10-t_height)/2,COLOR_DIFF[1],-1);
    textout_ex(bmp_submenu_difficulties,font_menu,"HARD",(SCREEN_w-2*text_length(font_menu,"HARD")),(SCREEN_h/10-t_height)/2,COLOR_DIFF[2],-1);
    }

    if (language == polish)
    {
    textout_ex(bmp_submenu_difficulties,font_menu,"ŁATWY",(0+text_length(font_menu,"ŁATWY")),(SCREEN_h/10-t_height)/2,COLOR_DIFF[0],-1);
    textout_ex(bmp_submenu_difficulties,font_menu,"ŚREDNI",(SCREEN_w-text_length(font_menu,"ŚREDNI"))/2,(SCREEN_h/10-t_height)/2,COLOR_DIFF[1],-1);
    textout_ex(bmp_submenu_difficulties,font_menu,"TRUDNY",(SCREEN_w-2*text_length(font_menu,"TRUDNY")),(SCREEN_h/10-t_height)/2,COLOR_DIFF[2],-1);
    }

    blit(bmp_submenu_difficulties,bmp_menu,0,0,0,SCREEN_h/2+70,SCREEN_w,SCREEN_h); // wyrzuc menu _menu do buffera

    break;
    }

//////////////////////////// new LANG

    case 5:
    {

    int static lang1 =0;
    int COLOR_LANG[2] = {WHITE,BLACK};
    COLOR_LANG[0] = BLACK;
    COLOR_LANG[1] = BLACK;

    if(!(key[KEY_LEFT]))
    {
    kleft=0;
    }

    if (kleft==0)
    {
    if(key[KEY_LEFT])
    {
    kleft=1;
    lang1--;
    if (lang1<0)
    {
    lang1=1;
    }
    }
    };


    if(!(key[KEY_RIGHT]))
    {kright=0;
    }

    if (kright==0)
    {
    if(key[KEY_RIGHT])
    {
    kright=1;
    lang1++;
    if (lang1>1)
    {
    lang1=0;
    }
    }
    };

    COLOR_LANG[lang1] = WHITE;

    language=lang1;

    if (language == english)
    {
    textout_ex(bmp_submenu_lang,font_menu,"ENGLISH",(0+text_length(font_menu,"ENGLISH")),(SCREEN_h/10-t_height)/2,COLOR_LANG[0],-1);
    textout_ex(bmp_submenu_lang,font_menu,"POLISH",(SCREEN_w-2*text_length(font_menu,"POLISH")),(SCREEN_h/10-t_height)/2,COLOR_LANG[1],-1);
    }

    if (language == polish)
    {
    textout_ex(bmp_submenu_lang,font_menu,"ANGIELSKI",(0+text_length(font_menu,"ANGIELSKI")),(SCREEN_h/10-t_height)/2,COLOR_LANG[0],-1);
    textout_ex(bmp_submenu_lang,font_menu,"POLSKI",(SCREEN_w-2*text_length(font_menu,"POLSKI")),(SCREEN_h/10-t_height)/2,COLOR_LANG[1],-1);
    }

    blit(bmp_submenu_lang,bmp_menu,0,0,0,SCREEN_h/2+70,SCREEN_w,SCREEN_h); // wyrzuc menu _menu do buffera

    break;
    };

    case 6:
    {
    if ((key[KEY_ENTER]) || (mouse_b & 1))
    {
    rest(1000);
    option=o_draw_menu;
    }

    break;
    };

    } // switch


    //}   //od if KEY_SPACE

////////////// END Section READ KEY
////////////////////////////////////////////////////


    blit(bmp_menu,buffer,0,0,0,0,SCREEN_w,SCREEN_h);

    return MUSIC_NUMBER;

} // draw_menu_options()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int draw_time_over(BITMAP *buffer, TElement * ptrelement)
{

    static BITMAP *final_bmp=NULL;
    static BITMAP *final_bmp2=NULL;

    int t_height;
    int vline;                                                                                              //shift
    vline=100;

    /*
    if (language == english)
    {
    t_width = text_length(font_menu,"Press ESC to exit.");
    }

    if (language == polish)
    {
    t_width = text_length(font_menu,"Naciśnij ESC aby wyjść.");
    }

    */

    t_height = text_height(font_menu);

    if (final_bmp==NULL)
    {
    final_bmp=create_bitmap(SCREEN_w,SCREEN_h);
    }

    clear_to_color(final_bmp,BLACK);

    if (final_bmp2==NULL)
    {
    final_bmp2=create_bitmap(SCREEN_w,4*t_height);
    }

    clear_to_color(final_bmp2,makecol(0,0,0));

    ptrelement->player.total_score=ptrelement->player.points+ptrelement->player.my_timer_min*60+ptrelement->player.my_timer_sec;

    sprintf(ptrelement->player.total_score_buffer, "%d", ptrelement->player.total_score);

    if (language == english)
    {
    textout(final_bmp,font,"                                Time has gone!                              ",0,60+vline,GREY);
    textout(final_bmp,font,"                       You have not finished the game.                      ",0,75+vline,WHITE);
    textout(final_bmp,font,"                  'Death Stars' has been exploded, and destroyed            ",0,90+vline,WHITE);
    textout(final_bmp,font,"                    other stages and Your ships and equipment.              ",0,105+vline,WHITE);

    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,120+vline,WHITE,-1,"Your points: %d        ",ptrelement->player.points);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,150+vline,WHITE,-1,"Total score: %d        ",ptrelement->player.total_score);
    textout(final_bmp,font,"                                                                            ",0,165+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,180+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,195+vline,WHITE);
    textout(final_bmp,font,"                    You can try to play on another difficulty               ",0,210+vline,WHITE);
    textout(final_bmp,font,"                    level or use editor to create own stages.               ",0,225+vline,WHITE);
    textout(final_bmp,font,"                    Enjoy!                                                  ",0,240+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,255+vline,WHITE);
    textout(final_bmp,font,"                    Press any key.                                          ",0,270+vline,WHITE);

    }

    if (language == polish)
    {
    textout(final_bmp,font,"                                  Czas minął!                               ",0,60+vline,GREY);
    textout(final_bmp,font,"                            Nie ukończyłeś zadania.                         ",0,75+vline,WHITE);
    textout(final_bmp,font,"                  'Gwiazdy Śmierci' eksplodowały i zniszczyły               ",0,90+vline,WHITE);
    textout(final_bmp,font,"              pozostałe etapy, twoją flotę statków i wyposażenie.          ",0,105+vline,WHITE);

    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,120+vline,WHITE,-1,"Twoje punkty: %d      ",ptrelement->player.points);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,150+vline,WHITE,-1,"Punkty łącznie: %d      ",ptrelement->player.total_score);
    textout(final_bmp,font,"                                                                            ",0,165+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,180+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,195+vline,WHITE);
    textout(final_bmp,font,"                  Spróbuj gry na innym poziomie trudności lub               ",0,210+vline,WHITE);
    textout(final_bmp,font,"                  utwórz w editorze własne etapy.                           ",0,225+vline,WHITE);
    textout(final_bmp,font,"                  Powodzenia!                                               ",0,240+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,255+vline,WHITE);
    textout(final_bmp,font,"                  Wciśnij klawisz.                                          ",0,270+vline,WHITE);

    }


    draw_sprite(buffer,final_bmp,0,0);

    static int ticker=0;

    ticker++;

    if (ticker>(1*time_of_animation))  // 10 sec
    {
    ticker=0;
    keypressed();

    return (option=o_hall_of_fame_new_entry);
    };

    return (option=o_time_over);

} // draw_time_over()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//

int draw_final(BITMAP *buffer, TElement * ptrelement)
{

    static BITMAP *final_bmp=NULL;
    static BITMAP *final_bmp2=NULL;
    int t_height;
    int vline;                                                                                  //shift

    vline=100;
    /*
    if (language == english)
    {
    t_width = text_length(font_menu,"Press ESC to exit");
    }

    if (language == polish)
    {
    t_width = text_length(font_menu,"Naciśnij ESC aby wyjść");
    }
    */

    t_height = text_height(font_menu);


	if (final_bmp==NULL)
	{
	final_bmp=create_bitmap(SCREEN_w,SCREEN_h);
	}

    clear_to_color(final_bmp,BLACK);

    if (final_bmp2==NULL)
    {
    final_bmp2=create_bitmap(SCREEN_w,4*t_height);
    }

    clear_to_color(final_bmp2,makecol(0,0,0));


    ptrelement->player.total_score=ptrelement->player.points+ptrelement->player.my_timer_min*60+ptrelement->player.my_timer_sec+ptrelement->player.ships*500;

    sprintf(ptrelement->player.total_score_buffer, "%d", ptrelement->player.total_score);

    if (language == english)
    {

    textout(final_bmp,font,"                                Congratulations!                            ",0,60+vline,GREY);
    textout(final_bmp,font,"                    All stages on this difficulty level has                 ",0,75+vline,WHITE);
    textout(final_bmp,font,"                    been finished.                                          ",0,90+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,105+vline,WHITE);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,120+vline,WHITE,-1,"Your points: %d",ptrelement->player.points);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,135+vline,WHITE,-1,"Bonus from time left: %d * 60 + %d = %d",ptrelement->player.my_timer_min,ptrelement->player.my_timer_sec,ptrelement->player.my_timer_min*60+ptrelement->player.my_timer_sec);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,150+vline,WHITE,-1,"Bonus from saved ships: %d * %d = %d",ptrelement->player.ships,500,ptrelement->player.ships*500) ;
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,165+vline,WHITE,-1,"Total score: %d",ptrelement->player.total_score);       // for every minute 60 points
    textout(final_bmp,font,"                                                                            ",0,180+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,195+vline,WHITE);
    textout(final_bmp,font,"                    You can try to play on another difficulty               ",0,210+vline,WHITE);
    textout(final_bmp,font,"                    level or use editor to create own stages.               ",0,225+vline,WHITE);
    textout(final_bmp,font,"                    Enjoy!                                                  ",0,240+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,255+vline,WHITE);
    textout(final_bmp,font,"                    Press any key.                                          ",0,270+vline,WHITE);

    }

    if (language == polish)
    {

    textout(final_bmp,font,"                                   Gratulacje!                              ",0,60+vline,GREY);
    textout(final_bmp,font,"                  Wszystkie plansze na tym poziomie trudności               ",0,75+vline,WHITE);
    textout(final_bmp,font,"                  zostały ukończone.                                        ",0,90+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,105+vline,WHITE);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,120+vline,WHITE,-1,"Twoje punkty z gry: %d",ptrelement->player.points);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,135+vline,WHITE,-1,"Bonus za pozostały czas: %d * 60 + %d = %d",ptrelement->player.my_timer_min,ptrelement->player.my_timer_sec,ptrelement->player.my_timer_min*60+ptrelement->player.my_timer_sec);
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,150+vline,WHITE,-1,"Bonus za zachowaną flotę statków: %d * %d = %d",ptrelement->player.ships,500,ptrelement->player.ships*500) ;
    textprintf_centre_ex(final_bmp,font,SCREEN_w/2,165+vline,WHITE,-1,"Punkty łącznie: %d",ptrelement->player.total_score);         // for every minute 60 points
    textout(final_bmp,font,"                                                                            ",0,180+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,195+vline,WHITE);
    textout(final_bmp,font,"                  Spróbuj gry na innym poziomie trudności lub               ",0,210+vline,WHITE);
    textout(final_bmp,font,"                  utwórz w editorze własne etapy.                           ",0,225+vline,WHITE);
    textout(final_bmp,font,"                  Powodzenia!                                               ",0,240+vline,WHITE);
    textout(final_bmp,font,"                                                                            ",0,255+vline,WHITE);
    textout(final_bmp,font,"                  Wciśnij klawisz.                                          ",0,270+vline,WHITE);


    }

    draw_sprite(buffer,final_bmp,0,0);

    static int ticker=0;

    ticker++;
    if (ticker>(1*time_of_animation))  // 10 sec
    {
    ticker=0;
    keypressed();

    return (option=o_hall_of_fame_new_entry);
    };

    return (option=o_draw_final);

};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
int create_Blast_config_file()
{
#define MAX_ROWS    12
#define MAX_COLUMNS 52
    int i;
    FILE * file;
    FILE * inifile;
    //static char * Blast_config;

    // const char *const output[] = {"0123456789", "2"};
    const char *const new_Blast_config[] =
    {
    ("# The ini file consists of blocks                   "),
    ("# which are marked by [ NAME OF BLOCK ]             "),
    ("[graphics]                                          "),
    ("# mode:                                             "),
    ("# width height bits per pixel                       "),
    ("mode= 800 600 24	                                  "),
    ("# Whether or not the program should run windowed    "),
    ("windowed= TRUE                                      "),
    ("# the actual content of the screen                  "),
    ("[content]                                           "),
    ("# the header line                                   "),
    ("headline= Blast 1.2 SE MARTE.BEST                   ")};



    //Blast_config = * new_Blast_config;


    if ((file=fopen("data/Blast_config.ini","r"))==NULL)              // "r" text file, "rb" binary file to read
    {
    //fclose(file);

    rest(300);

    if ((inifile=fopen("data/Blast_config.ini","w+"))==NULL)              // "w+" text file to append, "wb"  binary file to write
    {
    if (language == english)
    {
    allegro_message("Can't create 'Blast_config.ini' file.");
    }

    if (language == polish)
    {
    allegro_message("Nie można utworzyć pliku 'Blast_config.ini'.");
    }
    return 1;
    }
    //fwrite(&new_Blast_config[MAX_ROWS][MAX_COLUMNS],1,MAX_ROWS*(MAX_COLUMNS)*(sizeof(char)),file);

     // write to the text file
    for (i = 0; i < MAX_ROWS; i++)
    {
        fprintf(inifile, "%s\n", new_Blast_config[i]);
    }



    fclose(inifile);
    rest(300);
    return 0;
    }
    else
    {
    fclose(file);
    }

    return 0;

} // create_Blast_config_file();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

