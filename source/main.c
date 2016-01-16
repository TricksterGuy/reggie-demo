#include <3ds.h>
#include <string.h>
#include "reggie.h"

int main()
{
	// Initialize services
	srvInit();
	aptInit();
	hidInit();
	gfxInitDefault();
	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		// Your code goes here

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu


		u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		memset(fb, 0, 240*400*3);

		// Example rendering code that displays an image. 
		// The image was converted to C using one of my own tools nin10kit.
		// Image was exported to account for the 3ds's screen being rotated by 90 degrees.
		const unsigned char* ptr = reggie;
		for (int i = 0; i < 240*400; i++)
		{
			fb[3 * i] = ptr[3 * i];
			fb[3 * i + 1] = ptr[3 * i + 1];
			fb[3 * i + 2] = ptr[3 * i + 2];
		}

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	// Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
