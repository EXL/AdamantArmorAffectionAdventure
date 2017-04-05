#include "game.h"
#include "vars.h"
#include "wmapload.h"

#include <stdio.h>
#include <stdlib.h>

void zrmloadtextures(void)
{
    FILE *fp;
    u32 i, ii, x, y;
    u8 c, c0;
#ifndef ANDROID_NDK
    fp = fopen("textures.gfx", "rb");
#else
    fp = fopen("/mnt/sdcard/AAAA-Data/textures.gfx", "rb");
#endif

    ii = 0;

    for (i = 0; i < 256; i++) {
        textureheader[i][0] = fgetc(fp);
        textureheader[i][1] = fgetc(fp);
        textureheader[i][2] = fgetc(fp);
        textureheader[i][3] = fgetc(fp);

        texturepointer[i] = ii;

        if (textureheader[i][0] > 0) {
            for (y = 0; y < textureheader[i][2]; y++) {
                for (x = 0; x < textureheader[i][1]; x++) {
                    c = fgetc(fp);
                    c0 = fgetc(fp);
                    texturedata[ii++] = c * 256 + c0;
                }
            }

            texturereload[i] = 1;
        }
    }

    fclose(fp);
}

void loadconfig(void)
{
    FILE *fp;
    u8 i;
#ifndef ANDROID_NDK
    fp = fopen("donothexedit.me", "rb");
#else
    fp = fopen("/mnt/sdcard/AAAA-Data/donothexedit.me", "rb");
#endif

    for (i = 0; i < 32; i++) {
        configdata[i] = fgetc(fp);
    }

    fclose(fp);
}

void saveconfig(void)
{
    FILE *fp;
    u8 i;
#ifndef ANDROID_NDK
    fp = fopen("donothexedit.me", "rb");
#else
    fp = fopen("/mnt/sdcard/AAAA-Data/donothexedit.me", "wb");
#endif

    for (i = 0; i < 32; i++) {
        fputc(configdata[i], fp);
    }

    fclose(fp);
}

void zrmterraininfo(void)
{
    // top,sides,bottom,material
    terrtexx[1][0] = 64;
    terrtexx[1][1] = 64;
    terrtexx[1][2] = 64;
    terrtexx[1][3] = 0; // dirt
    terrtexx[2][0] = 66;
    terrtexx[2][1] = 65;
    terrtexx[2][2] = 64;
    terrtexx[2][3] = 0; // grass
    terrtexx[3][0] = 67;
    terrtexx[3][1] = 67;
    terrtexx[3][2] = 67;
    terrtexx[3][3] = 0; // sand
    terrtexx[4][0] = 68;
    terrtexx[4][1] = 68;
    terrtexx[4][2] = 68;
    terrtexx[4][3] = 0; // stone
    terrtexx[5][0] = 70;
    terrtexx[5][1] = 69;
    terrtexx[5][2] = 70;
    terrtexx[5][3] = 0; // wood
    terrtexx[6][0] = 71;
    terrtexx[6][1] = 71;
    terrtexx[6][2] = 71;
    terrtexx[6][3] = 0; // leaves
    terrtexx[7][0] = 73;
    terrtexx[7][1] = 73;
    terrtexx[7][2] = 73;
    terrtexx[7][3] = 0; // brick
    terrtexx[8][0] = 72;
    terrtexx[8][1] = 72;
    terrtexx[8][2] = 72;
    terrtexx[8][3] = 0; // brick

    terrtexx[9][0] = 79;
    terrtexx[9][1] = 79;
    terrtexx[9][2] = 79;
    terrtexx[9][3] = 0; // simulator white
    terrtexx[10][0] = 80;
    terrtexx[10][1] = 81;
    terrtexx[10][2] = 82;
    terrtexx[10][3] = 0; // simulator green

    terrtexx[11][0] = 85;
    terrtexx[11][1] = 85;
    terrtexx[11][2] = 85;
    terrtexx[11][3] = 0; // dark rock (!!!)
    terrtexx[12][0] = 86;
    terrtexx[12][1] = 86;
    terrtexx[12][2] = 86;
    terrtexx[12][3] = 0; // dark rock with vines (!!!)
    terrtexx[13][0] = 87;
    terrtexx[13][1] = 87;
    terrtexx[13][2] = 87;
    terrtexx[13][3] = 0; // stones
    terrtexx[14][0] = 88;
    terrtexx[14][1] = 88;
    terrtexx[14][2] = 88;
    terrtexx[14][3] = 0; // dirt solid
    terrtexx[15][0] = 89;
    terrtexx[15][1] = 89;
    terrtexx[15][2] = 89;
    terrtexx[15][3] = 0; // dirt
    terrtexx[16][0] = 90;
    terrtexx[16][1] = 90;
    terrtexx[16][2] = 90;
    terrtexx[16][3] = 0; // grass
    terrtexx[17][0] = 99;
    terrtexx[17][1] = 91;
    terrtexx[17][2] = 91;
    terrtexx[17][3] = 0; // greenstone
    terrtexx[18][0] = 93;
    terrtexx[18][1] = 92;
    terrtexx[18][2] = 92;
    terrtexx[18][3] = 0; // brownwall
    terrtexx[19][0] = 94;
    terrtexx[19][1] = 94;
    terrtexx[19][2] = 94;
    terrtexx[18][3] = 0; // yellow dirt

    terrtexx[20][0] = 95;
    terrtexx[20][1] = 95;
    terrtexx[20][2] = 95;
    terrtexx[20][3] = 0; // stones
    terrtexx[21][0] = 75;
    terrtexx[21][1] = 76;
    terrtexx[21][2] = 74;
    terrtexx[21][3] = 0; // metal0
    terrtexx[22][0] = 77;
    terrtexx[22][1] = 78;
    terrtexx[22][2] = 74;
    terrtexx[22][3] = 0; // metal1

    terrtexx[23][0] = 96;
    terrtexx[23][1] = 97;
    terrtexx[23][2] = 98;
    terrtexx[23][3] = 0; // crate1

    terrtexx[24][0] = 120;
    terrtexx[24][1] = 120;
    terrtexx[24][2] = 120;
    terrtexx[24][3] = 0; // brickwall
    terrtexx[25][0] = 121;
    terrtexx[25][1] = 121;
    terrtexx[25][2] = 121;
    terrtexx[25][3] = 0; // metal
    terrtexx[26][0] = 122;
    terrtexx[26][1] = 122;
    terrtexx[26][2] = 122;
    terrtexx[26][3] = 0; // metal line
    terrtexx[27][0] = 123;
    terrtexx[27][1] = 123;
    terrtexx[27][2] = 123;
    terrtexx[27][3] = 0; // metal plate
    terrtexx[28][0] = 124;
    terrtexx[28][1] = 124;
    terrtexx[28][2] = 124;
    terrtexx[28][3] = 0; // luminiscent plate

    terrtexx[29][0] = 161;
    terrtexx[29][1] = 160;
    terrtexx[29][2] = 160;
    terrtexx[29][3] = 0; // lab wall0

    terrtexx[30][0] = 162;
    terrtexx[30][1] = 163;
    terrtexx[30][2] = 163;
    terrtexx[30][3] = 0; // lab wall1
    terrtexx[31][0] = 164;
    terrtexx[31][1] = 165;
    terrtexx[31][2] = 164;
    terrtexx[31][3] = 0; // lab wall2

    terrtexx[32][0] = 110;
    terrtexx[32][1] = 110;
    terrtexx[32][2] = 110;
    terrtexx[32][3] = 0; // zveryle
    terrtexx[33][0] = 111;
    terrtexx[33][1] = 111;
    terrtexx[33][2] = 111;
    terrtexx[33][3] = 0; // zveryle
    terrtexx[34][0] = 112;
    terrtexx[34][1] = 112;
    terrtexx[34][2] = 112;
    terrtexx[34][3] = 0; // zveryle
    terrtexx[35][0] = 113;
    terrtexx[35][1] = 113;
    terrtexx[35][2] = 113;
    terrtexx[35][3] = 0; // zveryle
    terrtexx[36][0] = 114;
    terrtexx[36][1] = 114;
    terrtexx[36][2] = 114;
    terrtexx[36][3] = 0; // zveryle
    terrtexx[37][0] = 115;
    terrtexx[37][1] = 115;
    terrtexx[37][2] = 115;
    terrtexx[37][3] = 0; // zveryle
    terrtexx[38][0] = 116;
    terrtexx[38][1] = 116;
    terrtexx[38][2] = 116;
    terrtexx[38][3] = 0; // zveryle
    terrtexx[39][0] = 117;
    terrtexx[39][1] = 117;
    terrtexx[39][2] = 117;
    terrtexx[39][3] = 0; // zveryle
}

/*
 * 0  - click
 * 1  - ok
 * 2  - bad
 * 3  - <reserved>
 * 4  - step0
 * 5  - step1
 * 6  - step2
 * 7  - step3
 * 8  - jump
 * 9  - fall
 * 10 - inwater
 * 11 - melee swing
 * 12 - shooting gun
 * 13 - bullet hit
 * 14 - <reserved>
 * 15 - <reserved>
 * 16 - hero idle
 * 17 - hero alarm
 * 18 - hero hit
 * 19 - hero die
 * 20 - neko idle
 * 21 - neko alarm
 * 22 - neko sad
 * 23 - neko hurt and dead
 * 24 - slime idle
 * 25 - slime alarm
 * 26 - slime sad
 * 27 - slime hurt and dead
 * 28 - soldier idle
 * 29 - soldier alarm
 * 30 - soldier sad
 * 31 - solier dead
 * 32 - zombie idle
 * 33 - zombie alarm
 * 34 - zombie sad
 * 35 - zombie hurt and dead
 * 36 - ghast idle
 * 37 - ghast alarm
 * 38 - ghast sad
 * 39 - ghast hurt and dead
 */

void zrmmobsonic(void)
{
    /*
     * 0..3 - steps
     * 4    - waterstep
     * 5    - jump
     * 6    - fall
     * 7    - song
     * 8    - idle
     * 9    - alarm
     * 10   - sad
     * 11   - hurt
     * 12   - die
     * 13   - ...
     * 14   - ...
     * 15   - ...
     */

    mobsonic[0][0] = 4;
    mobsonic[0][1] = 5;
    mobsonic[0][2] = 6;
    mobsonic[0][3] = 7;

    mobsonic[0][4] = 10;
    mobsonic[0][5] = 8;
    mobsonic[0][6] = 9;
    mobsonic[0][7] = 17;

    mobsonic[0][8] = 0;
    mobsonic[0][9] = 0;
    mobsonic[0][10] = 0;
    mobsonic[0][11] = 18;

    mobsonic[0][12] = 19;
    mobsonic[0][13] = 0;
    mobsonic[0][14] = 0;
    mobsonic[0][15] = 0;

    // neko
    mobsonic[1][0] = 4;
    mobsonic[1][1] = 5;
    mobsonic[1][2] = 6;
    mobsonic[1][3] = 7;

    mobsonic[1][4] = 10;
    mobsonic[1][5] = 8;
    mobsonic[1][6] = 9;
    mobsonic[1][7] = 20; // meow

    mobsonic[1][8] = 20;
    mobsonic[1][9] = 21;
    mobsonic[1][10] = 22;
    mobsonic[1][11] = 23;

    mobsonic[1][12] = 23;
    mobsonic[1][13] = 0;
    mobsonic[1][14] = 0;
    mobsonic[1][15] = 0;

    // slime
    mobsonic[2][0] = 10;
    mobsonic[2][1] = 10;
    mobsonic[2][2] = 10;
    mobsonic[2][3] = 10;

    mobsonic[2][4] = 10;
    mobsonic[2][5] = 10;
    mobsonic[2][6] = 10;
    mobsonic[2][7] = 10;

    mobsonic[2][8] = 24;
    mobsonic[2][9] = 25;
    mobsonic[2][10] = 26;
    mobsonic[2][11] = 27;

    mobsonic[2][12] = 27;
    mobsonic[2][13] = 0;
    mobsonic[2][14] = 0;
    mobsonic[2][15] = 0;

    // soldier
    mobsonic[3][0] = 4;
    mobsonic[3][1] = 5;
    mobsonic[3][2] = 6;
    mobsonic[3][3] = 7;

    mobsonic[3][4] = 10;
    mobsonic[3][5] = 8;
    mobsonic[3][6] = 9;
    mobsonic[3][7] = 17;

    mobsonic[3][8] = 28;
    mobsonic[3][9] = 29;
    mobsonic[3][10] = 30;
    mobsonic[3][11] = 31;

    mobsonic[3][12] = 31;
    mobsonic[3][13] = 0;
    mobsonic[3][14] = 0;
    mobsonic[3][15] = 0;

    // zombie
    mobsonic[4][0] = 4;
    mobsonic[4][1] = 5;
    mobsonic[4][2] = 6;
    mobsonic[4][3] = 7;

    mobsonic[4][4] = 10;
    mobsonic[4][5] = 8;
    mobsonic[4][6] = 9;
    mobsonic[4][7] = 17;

    mobsonic[4][8] = 32;
    mobsonic[4][9] = 33;
    mobsonic[4][10] = 34;
    mobsonic[4][11] = 35;

    mobsonic[4][12] = 36;
    mobsonic[4][13] = 0;
    mobsonic[4][14] = 0;
    mobsonic[4][15] = 0;

    // ghoul
    mobsonic[5][0] = 4;
    mobsonic[5][1] = 5;
    mobsonic[5][2] = 6;
    mobsonic[5][3] = 7;

    mobsonic[5][4] = 10;
    mobsonic[5][5] = 8;
    mobsonic[5][6] = 9;
    mobsonic[5][7] = 17;

    mobsonic[5][8] = 37;
    mobsonic[5][9] = 38;
    mobsonic[5][10] = 39;
    mobsonic[5][11] = 40;

    mobsonic[5][12] = 41;
    mobsonic[5][13] = 0;
    mobsonic[5][14] = 0;
    mobsonic[5][15] = 0;

    // scientist
    mobsonic[6][0] = 4;
    mobsonic[6][1] = 5;
    mobsonic[6][2] = 6;
    mobsonic[6][3] = 7;

    mobsonic[6][4] = 10;
    mobsonic[6][5] = 8;
    mobsonic[6][6] = 9;
    mobsonic[6][7] = 17;

    mobsonic[6][8] = 28;
    mobsonic[6][9] = 29;
    mobsonic[6][10] = 30;
    mobsonic[6][11] = 31;

    mobsonic[6][12] = 31;
    mobsonic[6][13] = 0;
    mobsonic[6][14] = 0;
    mobsonic[6][15] = 0;

    // dino
    mobsonic[7][0] = 4;
    mobsonic[7][1] = 5;
    mobsonic[7][2] = 6;
    mobsonic[7][3] = 7;

    mobsonic[7][4] = 10;
    mobsonic[7][5] = 8;
    mobsonic[7][6] = 9;
    mobsonic[7][7] = 17;

    mobsonic[7][8] = 42;
    mobsonic[7][9] = 43;
    mobsonic[7][10] = 44;
    mobsonic[7][11] = 45;

    mobsonic[7][12] = 45;
    mobsonic[7][13] = 0;
    mobsonic[7][14] = 0;
    mobsonic[7][15] = 0;

    // zombie2
    mobsonic[8][0] = 4;
    mobsonic[8][1] = 5;
    mobsonic[8][2] = 6;
    mobsonic[8][3] = 7;

    mobsonic[8][4] = 10;
    mobsonic[8][5] = 8;
    mobsonic[8][6] = 9;
    mobsonic[8][7] = 17;

    mobsonic[8][8] = 32;
    mobsonic[8][9] = 33;
    mobsonic[8][10] = 34;
    mobsonic[8][11] = 35;

    mobsonic[8][12] = 36;
    mobsonic[8][13] = 0;
    mobsonic[8][14] = 0;
    mobsonic[8][15] = 0;
}

void premeshccc(void)
{
    /*
    s32 x,y,celli,i,k;
    for (y=0;y<22;y++) {
        for (x=0;x<22;x++) {
            celli=((x)+(y)*22);
            i=16384+celli*6*2*3;

            //top 0
            meshc[i*4]=255;
            meshc[i*4+1]=255;
            meshc[i*4+2]=255;
            meshc[i*4+3]=255;
            mesh[i*3]=(x-10)*65536;
            mesh[i*3+1]=65536;
            mesh[i*3+2]=(y-10)*65536;
            mesht[(i)*2]=0;
            mesht[(i)*2+1]=0;

            meshc[(i+1)*4]=255;
            meshc[(i+1)*4+1]=255;
            meshc[(i+1)*4+2]=255;
            meshc[(i+1)*4+3]=255;
            mesh[(i+1)*3]=(x+1-10)*65536;
            mesh[(i+1)*3+1]=65536;
            mesh[(i+1)*3+2]=(y-10)*65536;
            mesht[(i+1)*2]=65536;
            mesht[(i+1)*2+1]=0;

            meshc[(i+2)*4]=255;
            meshc[(i+2)*4+1]=255;
            meshc[(i+2)*4+2]=255;
            meshc[(i+2)*4+3]=255;
            mesh[(i+2)*3]=(x-10)*65536;
            mesh[(i+2)*3+1]=65536;
            mesh[(i+2)*3+2]=(y+1-10)*65536;
            mesht[(i+2)*2]=0;
            mesht[(i+2)*2+1]=65536;
            //top 1
            meshc[(i+3)*4]=255;
            meshc[(i+3)*4+1]=255;
            meshc[(i+3)*4+2]=255;
            meshc[(i+3)*4+3]=255;
            mesh[(i+3)*3]=(x+1-10)*65536;
            mesh[(i+3)*3+1]=65536;
            mesh[(i+3)*3+2]=(y-10)*65536;
            mesht[(i+3)*2]=65536;
            mesht[(i+3)*2+1]=0;

            meshc[(i+4)*4]=255;
            meshc[(i+4)*4+1]=255;
            meshc[(i+4)*4+2]=255;
            meshc[(i+4)*4+3]=255;
            mesh[(i+4)*3]=(x-10)*65536;
            mesh[(i+4)*3+1]=65536;
            mesh[(i+4)*3+2]=(y+1-10)*65536;
            mesht[(i+4)*2]=0;
            mesht[(i+4)*2+1]=65536;

            meshc[(i+5)*4]=255;
            meshc[(i+5)*4+1]=255;
            meshc[(i+5)*4+2]=255;
            meshc[(i+5)*4+3]=255;
            mesh[(i+5)*3]=(x+1-10)*65536;
            mesh[(i+5)*3+1]=65536;
            mesh[(i+5)*3+2]=(y+1-10)*65536;
            mesht[(i+5)*2]=65536;
            mesht[(i+5)*2+1]=65536;

            #ifdef PC_GL
            for (k=i;k<i+12;k++) {
                mesh[k*3]=mesh[k*3]/65536.0;
                mesh[k*3+1]=mesh[k*3+1]/65536.0;
                mesh[k*3+2]=mesh[k*3+2]/65536.0;

                mesht[k*2]=mesht[k*2]/65536.0;
                mesht[k*2+1]=mesht[k*2+1]/65536.0;
            }
            #endif
        }
    }
    */
}

void applycheats(void)
{
    int i;

    // 1. Open all disks
    for (i = 1; i <= 5; ++i) {
        configdata[i] = 1;
    }

    // 2. Open all levels
    for (i = 16; i < 32; ++i) {
        configdata[i] = 99;
    }

    // 3. Disable mobs attack
    ai_attack_disable_cheat = 1;
}

void zresminit(void)
{
    loadconfig();
    applycheats();
    zrmterraininfo();
    zrmloadtextures();
    zrmmobsonic();
    gamemode = ZGM_GAMEPLAY;
    newgamemode = ZGM_GAMEPLAY;
    // playmode=ZPM_EDIT;
    // level=255;
    // premeshccc();
    level = 9;
    // newgamemode=ZGM_SELECTOR;
    // level=0;

    // playmode=ZPM_AUTISM;
    // level=11;

    //    gamemode = ZGM_LOGO;
    //    newgamemode = ZGM_LOGO;
    //    level = 0;
}

void zresmstep(void)
{
    gameframe();
}

void zresmdown(void)
{
    saveconfig();
}
