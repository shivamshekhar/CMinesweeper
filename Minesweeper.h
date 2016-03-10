#define MAINGRIDHEIGHT 21
#define MAINGRIDWIDTH 21
#define MINEFIELD(x) (2*x + 1)
#define MINE 15
#define FLAG 247
#define MINECOL 132
#define GRIDCOL 143
#define GRIDNUMCOL 121
#define EMPTYAREACOL 120
#define FLAGCOL 126
COORD zerozero={0,0};
int maingridmap[MAINGRIDHEIGHT][MAINGRIDWIDTH]=
                        {
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                        };
int minefield[MAINGRIDHEIGHT/2][MAINGRIDWIDTH/2]={0};
int isflagpicked=FALSE,showsoln=FALSE;
///
int mouseclick(int*,int*);
void updatescreen(int,int,int,int,int);
void initmaingrid(int,int);
void initminefield(int,int,int,int,int);
void openmine(int,int,int,int,int);
void printflagbutton(void);
void setcursorposition(int,int);
int diduserwin(int,int,int);
void gameover(void);
///
int mouseclick(int *x, int *y) //checks whether user pressed a button and return the coordinates of the place where user pressed
{
    HANDLE in;
    DWORD info;
    INPUT_RECORD input;
    int ret=0;
    in=GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(in,ENABLE_PROCESSED_INPUT|ENABLE_MOUSE_INPUT);
    ReadConsoleInput(in,&input,1,&info);
    if(input.EventType==MOUSE_EVENT)
    {
        if(input.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            *x = input.Event.MouseEvent.dwMousePosition.X;
            *y = input.Event.MouseEvent.dwMousePosition.Y;
            //printf("%d,%d ",*x,*y);
            ret = 1;
        }
    }
    return ret;
}
//
void updatescreen(int x,int y,int maingridheight, int maingridwidth,int numberofflags) //updates the screen
{
    int i,j;
    CHAR_INFO maingrid[maingridheight*maingridwidth];
    COORD maingridsz={maingridheight,maingridwidth};
    SMALL_RECT maingridrect={x,y,x+maingridwidth,y+maingridheight};
    for(i=0;i<maingridheight;i++)
    {
        for(j=0;j<maingridwidth;j++)
        {
            maingrid[j+maingridwidth*i].Char.AsciiChar=maingridmap[i][j];
            if(maingridmap[i][j]==MINE)
            {
                maingrid[j+maingridwidth*i].Attributes=MINECOL;
            }
            else if(maingridmap[i][j]==177)
            {
                maingrid[j+maingridwidth*i].Attributes=EMPTYAREACOL;
            }
            else if(maingridmap[i][j]==FLAG)
            {
                maingrid[j+maingridwidth*i].Attributes=FLAGCOL;
            }
            else if(maingridmap[i][j]>48 && maingridmap[i][j]<58)
            {
                maingrid[j+maingridwidth*i].Attributes=GRIDNUMCOL;
            }
            else
            {
                maingrid[j+maingridwidth*i].Attributes=GRIDCOL;
            }
        }
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),maingrid,maingridsz,zerozero,&maingridrect);
    printflagbutton();
    setcursorposition(15,24);
    printf("Minesweeper");
    setcursorposition(50,24);
    printf("Written by: Shivam Shekhar");
    setcursorposition(55,8);
    printf("                     ");
    setcursorposition(55,8);
    printf("Number of flags = %d",numberofflags);
    setcursorposition(0,0);
}
//
void initmaingrid(int sizex,int sizey) //initiates the maingrid.
{
    int i,j;
    for(i=0;i<sizey;i++)
    {
        for(j=0;j<sizex;j++)
        {
            if(i==0)
            {
                if(j%2==0)
                    maingridmap[i][j]=194;
                else
                    maingridmap[i][j]=196;
            }
            else if(i==sizey-1)
            {
                if(j%2==0)
                    maingridmap[i][j]=193;
                else
                    maingridmap[i][j]=196;
            }
            else
            {
                if(i%2==0)
                {
                    if(j==0)
                        maingridmap[i][j]=195;
                    else if(j==sizex-1)
                        maingridmap[i][j]=180;

                    else
                    {
                        if(j%2==0)
                            maingridmap[i][j]=197;
                        else
                            maingridmap[i][j]=196;
                    }
                }
                else
                {
                    if(j%2==0)
                    {
                        maingridmap[i][j]=179;
                    }
                    else
                    {
                        maingridmap[i][j]=219;
                    }
                }
            }
        }
    }
    maingridmap[0][0]=218;
    maingridmap[0][sizex - 1]=191;
    maingridmap[sizey - 1][0]=192;
    maingridmap[sizey - 1][sizex - 1]=217;
    if(showsoln==TRUE)
    {
        for(i=0;i<sizey/2;i++)
        {
            for(j=0;j<sizex/2;j++)
            {
                maingridmap[MINEFIELD(i)][MINEFIELD(j)]=minefield[i][j];
            }
        }
    }///displays the solution
}
//
void initminefield(int sizex, int sizey, int openx, int openy,int difficulty) //initiates the minefield
{
    int x,y,i,j,I,J,nofmines=(sizex*sizey)/(7-difficulty),countmines=0;
    while(nofmines>0)
    {
        x=rand()%sizex;
        y=rand()%sizey;
        if(minefield[y][x]!=MINE && x!=openx && y!=openy)
        {
            minefield[y][x]=MINE;
            nofmines--;
        }
    }
    for(i=0;i<sizey;i++)
    {
        for(j=0;j<sizex;j++)
        {
            if(minefield[i][j]!=MINE)
            {
                for(I=i-1;I<=i+1;I++)
                {
                    for(J=j-1;J<=j+1;J++)
                    {
                        if(minefield[I][J]==MINE && I>-1 && I<sizey && J>-1 && J<sizex)
                            countmines++;
                    }
                }
                if(countmines>0)
                    minefield[i][j]=countmines + 48;
                else
                    minefield[i][j]=0;
                countmines=0;
            }
        }
    }
}
void openmine(int x, int y, int sizey, int sizex,int isfirstturn) // opens a selected mine
{
    int I,J;
    if(minefield[y][x] == MINE)
    {
        //printf("Game over\n");
        maingridmap[MINEFIELD(y)][MINEFIELD(x)]=minefield[y][x];//219;//minefield[I][J];
    }
    else if(minefield[y][x]==0)
    {
        //printf("1\n");
        minefield[y][x]=177;
        for(I=y-1;I<=y+1;I++)
        {
            for(J=x-1;J<=x+1;J++)
            {
                if(I>-1 && I<sizey && J>-1 && J<sizex)
                {
                    if(minefield[I][J]==0)
                    {
                        maingridmap[MINEFIELD(I)][MINEFIELD(J)]=minefield[y][x];//219; //minefield[I][J];
                        openmine(J,I,sizey,sizex,FALSE);
                    }
                    else if(minefield[I][J]==MINE)
                        continue;
                    else
                        maingridmap[MINEFIELD(I)][MINEFIELD(J)]=minefield[I][J];//219;
                }
            }
        }
    }
    else
    {
        //printf("2\n");
        if(isfirstturn==TRUE)
        {
            for(I=y-1;I<=y+1;I++)
            {
                for(J=x-1;J<=x+1;J++)
                {
                    if(minefield[I][J]!=MINE && I>-1 && I<sizey && J>-1 && J<sizex)
                    {
                        if(minefield[I][J]!=0)
                        {
                            maingridmap[MINEFIELD(I)][MINEFIELD(J)]=minefield[I][J];
                        }
                        else
                        {
                            maingridmap[MINEFIELD(I)][MINEFIELD(J)]=177;
                        }
                    }
                }
            }
        }
        else
        {
            maingridmap[MINEFIELD(y)][MINEFIELD(x)]=minefield[y][x];
        }
    }
}
//
void printflagbutton() // prints the flag button
{
    int i,x=60,y=10,buttonsize=3;
    CHAR_INFO button[buttonsize*buttonsize];
    SMALL_RECT buttonrect = {x,y,x+buttonsize,y+buttonsize};
    COORD buttoncoord = {buttonsize,buttonsize};
    if(isflagpicked==FALSE)
    {
        for(i=0;i<buttonsize*buttonsize;i++)
        {
            button[i].Char.AsciiChar=219;
            button[i].Attributes=14;
        }
        button[4].Char.AsciiChar=FLAG;
        button[4].Attributes=236;
    }
    else
    {
        for(i=0;i<buttonsize*buttonsize;i++)
        {
            button[i].Char.AsciiChar=219;
            button[i].Attributes=12;
        }
        button[4].Char.AsciiChar=FLAG;
        button[4].Attributes=206;
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),button,buttoncoord,zerozero,&buttonrect);
}
//
void setcursorposition(int x,int y) // sets the cursor's position
{
    COORD cursorpos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cursorpos);
}
//
int diduserwin(int maingridwidth, int maingridheight,int difficulty)
{
    int i,j;
    int minefieldheight=maingridheight/2;
    int minefieldwidth = maingridwidth/2;
    int maxflags = (minefieldheight*minefieldwidth)/(7-difficulty);
    for(i=0;i<minefieldheight;i++)
    {
        for(j=0;j<minefieldwidth;j++)
        {
            if(minefield[i][j]==MINE && maingridmap[MINEFIELD(i)][MINEFIELD(j)]==FLAG)
                maxflags--;
        }
    }
    if(maxflags==0)
    {
        return 1;
    }
    else
        return 0;
}
//
void gameover()
{
    setcursorposition(30,23);
    printf("You lose!");
    getch();
    system("Minesweeper.exe");
}
