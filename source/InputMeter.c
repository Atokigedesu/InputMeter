#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "DiffChecker.h"
#include "SDIChecker.h"

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

void Initialize();

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

  Initialize();

  // The console understands VT terminal escape codes
  // This positions the cursor on row 2, column 0
  // we can use variables for this with format codes too
  // e.g. printf ("\x1b[%d;%dH", row, column );
  // printf("\x1b[1;1H");

  while(1) {

    PAD_ScanPads();

    update_diff_checker();
    update_sdi_checker();

    // Wait for the next frame
    VIDEO_WaitVSync();
  }

  return 0;
}

void Initialize(void) {

  // Initialise the video system
  VIDEO_Init();

  // This function initialises the attached controllers
  PAD_Init();

  // Obtain the preferred video mode from the system
  // This will correspond to the settings in the Wii menu
  rmode = VIDEO_GetPreferredMode(NULL);

  // Allocate memory for the display in the uncached region
  xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

  // Initialise the console, required for printf
  console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

  // Set up the video registers with the chosen mode
  VIDEO_Configure(rmode);

  // Tell the video hardware where our display memory is
  VIDEO_SetNextFramebuffer(xfb);

  // Make the display visible
  VIDEO_SetBlack(FALSE);

  // Flush the video register changes to the hardware
  VIDEO_Flush();

  // Wait for Video setup to complete
  VIDEO_WaitVSync();
  if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();


  initialize_diff_checker();
  initialize_sdi_checker();
}
