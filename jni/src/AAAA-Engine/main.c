#include "vars.h"
#include "zcore.h"
#include "zresm.h"

// For replacing main() to SDL_main()
#ifdef ANDROID_NDK
#include <SDL.h>
#endif

int main(int argc, char* argv[])
{
    zresminit();

    zcoreinit();
    zcoreloop();

    zresmdown();

    zcoredown();

    return 0;
}
