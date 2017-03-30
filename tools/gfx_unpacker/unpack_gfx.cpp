/************************************************************************************
** Unpacker for textures.gfx file by EXL, 30-MAR-2017
**
** Requirements:
**  - git
**  - imagemagick
**  - g++ w/ c++1z
**
** Build instructions:
**  $ cd tools/gfx_unpacker/
**  $ git clone --depth 1 https://github.com/lvandeve/lodepng
**  $ g++ unpack_gfx.cpp lodepng/lodepng.cpp -o unpack_gfx -lstdc++fs
**  $ ./unpack_gfx ../../assets_obb/AAAA-Data/textures.gfx
**  $ montage unpacked/*.png -background none tex_collage.png
**
** Get PNG-textures from "unpacked/" folder or collage in the pwd
************************************************************************************/

#include <experimental/filesystem>

#include "lodepng/lodepng.h"

typedef unsigned char  uc;
typedef unsigned short us;
typedef unsigned int   ui;
typedef unsigned long  ul;

// RGBA4444 to RGBA8888 table by Frankinshtein
// http://www.gamedev.ru/code/forum/?id=160094#m13
const uc lookupTable4to8[] = {0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255};

uc textureheader[256][4], texturereload[256];
ui texturedata[1048576 * 5 / 2];
ul texturepointer[256];
us texturedata4444[65536];
ui texturedata8888[65536];

namespace fs = std::experimental::filesystem;

void convertsavetexture(uc index, ui w, ui h) {
	ui ii = texturepointer[index], i = 0, x, y;
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			texturedata4444[i++] = texturedata[ii++];
		}
	}
	i = 0; ii = 0;
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			us color4444 = texturedata4444[i++];
			uc red = lookupTable4to8[(color4444 & 0xFFFF) >> 12];
			uc green = lookupTable4to8[(color4444 & 0xFFF) >> 8];
			uc blue = lookupTable4to8[(color4444 & 0xFF) >> 4];
			uc alpha = lookupTable4to8[color4444 & 0xF];
			ui color8888 = (alpha << 24) + (blue << 16) + (green << 8) + red;
			texturedata8888[ii++] = color8888;
			// std::bitset<32> v(rval);
		}
	}
	if (w > 0 && h > 0) {
		char fname[256] = {'\0'};
		sprintf(fname, "unpacked/%03d.png", index);
		lodepng_encode32_file(fname, (uc *) texturedata8888, w, h);
		fprintf(stderr, "Unpacked texture #%03d, size: %dx%d\n", index + 1, w, h);
	}
}

int main(int argc, char *argv[]) {
	const char *dirname = "unpacked";
	if (!fs::exists(dirname)) {
		fs::create_directory(dirname);
	}
	FILE *fp = fopen(argv[1], "rb");
	ui i, ii = 0, x, y, w, h;
	uc c, c0;
	for (i = 0; i < 256; i++) {
		textureheader[i][0] = fgetc(fp);
		textureheader[i][1] = fgetc(fp);
		textureheader[i][2] = fgetc(fp);
		textureheader[i][3] = fgetc(fp);
		texturepointer[i] = ii;
		w = textureheader[i][1], h = textureheader[i][2];
		if (textureheader[i][0] > 0) {
			for (y = 0; y < h; y++) {
				for (x = 0; x < w; x++) {
					c = fgetc(fp);
					c0 = fgetc(fp);
					texturedata[ii++] = c * 256 + c0;
				}
			}
			texturereload[i] = 1;
		}
		convertsavetexture(i, w, h);
	}
	fclose(fp);
	return 0;
}
