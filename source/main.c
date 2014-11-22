#include <3ds.h>
#include "reggie.h"

int main()
{
	// Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
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

		// Example rendering code that displays a white pixel
		// Please note that the 3DS screens are sideways (thus 240x400 and 240x320)
		u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		memset(fb, 0, 240*400*3);
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
