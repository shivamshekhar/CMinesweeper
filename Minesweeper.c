/*C Minesweeper
Written by: Shivam Shekhar
*/
#include"alphabet2.h"
#include"Minesweeper.h"
int main()
{
    int maingridheight=21,maingridwidth=21,flags,arenaposx=30,arenaposy=2;
    int minefieldheight=maingridheight/2,minefieldwidth=maingridwidth/2;
    int i,j,x,y,tempx,tempy,isfirstturn=TRUE,tempgridsize=0,difficulty=0;
    flags=(minefieldheight*minefieldwidth)/4;
    system("cls");
    printstr(10,5,"minesweeper",219,_YELLOW);
    setcursorposition(50,24);
    printf("Written by: Shivam Shekhar");
    setcursorposition(25,14);
    system("pause");
    while(1)
    {
        system("cls");
        setcursorposition(10,11);
        printf("(Eg: to get 4x4 grid, enter 4 and 5 for 5x5 grid and so on...)");
        setcursorposition(30,10);
        printf("Enter the grid size: ");
        scanf("%d", &tempgridsize);
        if(tempgridsize < 11 && tempgridsize>2)
            break;
    }
    while(1)
    {
        system("cls");
        setcursorposition(30,9);
        printf("1. Easy");
        setcursorposition(30,10);
        printf("2. Medium");
        setcursorposition(30,11);
        printf("3. Hard");
        setcursorposition(30,8);
        printf("Select the difficulty: ");
        scanf("%d", &difficulty);
        if(difficulty>0 && difficulty<4)
            break;
    }
    system("cls");
    maingridheight = 2*tempgridsize + 1;
    maingridwidth = 2*tempgridsize + 1;
    minefieldheight = maingridheight/2;
    minefieldwidth = maingridwidth/2;
    flags=(minefieldheight*minefieldwidth)/(7-difficulty);
    srand(time(NULL));
    initmaingrid(maingridwidth,maingridheight);
    updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
    while(1)
    {
        if(mouseclick(&x,&y) == 1)
        {
            if(isfirstturn==TRUE)
            {
                if(x>arenaposx && x<arenaposx + 2*minefieldwidth && y>arenaposy && y<arenaposy+2*minefieldheight && (x-arenaposx)%2!=0 && (y-arenaposy)%2!=0 && maingridmap[y-arenaposy][x-arenaposx]==219)
                {
                    initminefield(minefieldwidth,minefieldheight,(x-arenaposx)/2, (y-arenaposy)/2,difficulty);
                    openmine((x-arenaposx)/2,(y-arenaposy)/2,minefieldheight,minefieldwidth,isfirstturn);
                    updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                    isfirstturn=FALSE;
                }
            }
            else
            {
                if(isflagpicked==FALSE) //if user hasn't picked the flag
                {
                    /*if a box is opened*/
                    if(x>arenaposx && x<arenaposx + 2*minefieldwidth && y>arenaposy && y<arenaposy+2*minefieldheight && (x-arenaposx)%2!=0 && (y-arenaposy)%2!=0 && maingridmap[y-arenaposy][x-arenaposx]==219)
                    {
                        openmine((x-arenaposx)/2,(y-arenaposy)/2,minefieldheight,minefieldwidth,isfirstturn);
                        updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                        if(minefield[(y-arenaposy)/2][(x-arenaposx)/2] == MINE)
                        {
                            for(i=0;i<minefieldheight;i++)
                            {
                                for(j=0;j<minefieldwidth;j++)
                                {
                                    if(minefield[i][j]==MINE)
                                    {
                                        maingridmap[MINEFIELD(i)][MINEFIELD(j)]=minefield[i][j];
                                    }
                                }
                            }
                            updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                            gameover();
                        }
                    }
                    if(x>arenaposx && x<arenaposx + 2*minefieldwidth && y>arenaposy && y<arenaposy+2*minefieldheight && (x-arenaposx)%2!=0 && (y-arenaposy)%2!=0 && maingridmap[y-arenaposy][x-arenaposx]==FLAG)
                    {
                        flags++;
                        maingridmap[y-arenaposy][x-arenaposx] = 219;
                        updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                    }
                    else if(x>59 && x<63 && y>9 && y<13) //flag button pressed
                    {
                        isflagpicked=TRUE;
                        updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                    }
                }
                else //if user has picked the flag
                {
                    if(x>59 && x<63 && y>9 && y<13) //flag button pressed
                    {
                        isflagpicked=FALSE;
                        updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                    }
                    /*if a box is selected, then place the flag*/
                    else if(x>arenaposx && x<arenaposx + 2*minefieldwidth && y>arenaposy && y<arenaposy+2*minefieldheight && (x-arenaposx)%2!=0 && (y-arenaposy)%2!=0 && maingridmap[y-arenaposy][x-arenaposx]==219)
                    {
                        isflagpicked=FALSE;
                        if(flags>0)
                        {
                            flags--;
                            maingridmap[y-arenaposy][x-arenaposx] = FLAG;
                        }
                        updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                        if(diduserwin(maingridwidth,maingridheight,difficulty)==1)
                        {
                            setcursorposition(30,23);
                            printf("Congratulations!, You win");
                            getch();
                            system("Minesweeper.exe");
                        }
                    }
                    else //clicked anywhere else on the screen
                    {
                        isflagpicked=FALSE;
                        updatescreen(arenaposx,arenaposy,maingridheight,maingridwidth,flags);
                    }
                }
            }
        }
    }
    getch();
    return 0;
}
