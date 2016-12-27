#include "vars.h"
#include "zcore.h"
#include "zresm.h"

int main(int argc, char *argv[])
{
zresminit();

zcoreinit();
zcoreloop();

zresmdown();

zcoredown();

return 0;
}
