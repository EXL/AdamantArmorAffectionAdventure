typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

typedef signed char s8;
typedef signed int s16;
typedef signed long s32;

enum ZLGAME_MODES
{
ZGM_NONE,
ZGM_LOAD,
ZGM_INTRO,
ZGM_MENU,
ZGM_GAMEPLAY,
ZGM_CONFIG,
ZGM_SELECTOR,
ZGM_LOGO
};

enum ZLPLAY_MODES
{
ZPM_NONE,
ZPM_FLYINTRO,
ZPM_EDIT,
ZPM_TUTORIAL,
ZPM_AAA,
ZPM_AUTISM,
ZPM_ZOMBIEH,
ZPM_ZVERYLE,
ZPM_MOVIE
};

enum ZLAI_STATE
{
AI_DISABLED,
AI_PEACE,
AI_ATTACK
};
