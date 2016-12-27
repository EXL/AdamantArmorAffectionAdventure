#include "vars.h"

#include "gamescene.h"
#include "playcontrol.h"
#include "gamemenu.h"
#include "zeditmode.h"
#include "wmapload.h"

#include "intro.h"
#include "zgui.h"

void gameframe(void)
{

tension[0]=255;
tension[1]=255;
tension[2]=255;
tension[3]=configdata[13]*16;

if (gamemode!=newgamemode)
{
if (gameswitchdelay==0) gameswitchdelay=-100;
else
{
if (gameswitchdelay<0) gameswitchdelay++;
if (gameswitchdelay==0) {gamemode=newgamemode;gameswitchdelay=100;}
}
}
else
if (gameswitchdelay>0) gameswitchdelay--;

switch (gamemode)
{
case ZGM_MENU:gamemenu();break;
case ZGM_CONFIG:gameconfig();break;
case ZGM_SELECTOR:gameselector();break;

case ZGM_LOGO:gamelogo();break;

case ZGM_GAMEPLAY:
if (level!=lastlevel) {LoadNewMap(level);lastlevel=level;}
gamesceneframe();

//if (gameswitchdelay==0)
{
switch (playmode)
{
case ZPM_NONE:procplaycontrol();break;
case ZPM_FLYINTRO:procintro();break;
case ZPM_AAA:procgamecontrol();break;
case ZPM_MOVIE:procmovie();break;

case ZPM_AUTISM:procautism();break;
case ZPM_ZVERYLE:proczveryle();break;


}
//if (playmode!=ZPM_EDIT) procplaycontrol();
}



if (playmode==ZPM_EDIT) proceditmode();

break;//gameplay
}

procnoise();

////
if (button[15]>5) zcoreenabled=0;
////
levelframes++;
}
