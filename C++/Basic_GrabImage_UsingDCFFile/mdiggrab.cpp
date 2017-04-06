/********************************************************************************/
/* 
 * File name: MDigGrab.cpp 
 *
 * Synopsis:  This program demonstrates how to grab from a camera in
 *            continuous and monoshot mode.
 */
#include <mil.h> 

int MosMain(void)
{ 
   MIL_ID MilApplication,  /* Application identifier.  */
          MilSystem,       /* System identifier.       */
          MilDisplay,      /* Display identifier.      */
          MilDigitizer,    /* Digitizer identifier.    */ 
          MilImage;        /* Image buffer identifier. */

   /* Allocate defaults. */
   //MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem,&MilDisplay, &MilDigitizer, &MilImage);


   // using DCF 파일
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(MIL_TEXT("M_DEFAULT"), M_DEFAULT, M_DEFAULT, &MilSystem);
   MdigAlloc(MilSystem, M_DEV0,"D:/SC-D500x(2456x2058).dcf", M_DEFAULT, &MilDigitizer);
   // DCF FILE 경로

   MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay);

   MbufAlloc2d(MilSystem, 
	   (MIL_INT)(MdigInquire(MilDigitizer, M_SIZE_X, M_NULL) * 1.0),
	   (MIL_INT)(MdigInquire(MilDigitizer, M_SIZE_Y, M_NULL) * 1.0),
	   8L + M_UNSIGNED,
	   M_IMAGE + M_GRAB + M_DISP, &MilImage);

   MbufClear(MilImage,0x0);

   MdispSelect(MilDisplay, MilImage);
   MdigControl(MilDigitizer, M_GRAB_SCALE, 1.0);

   //////////////////////////////////////////

   /* Grab continuously. */
   MdigGrabContinuous(MilDigitizer, MilImage);

   /* When a key is pressed, halt. */
   MosPrintf(MIL_TEXT("\nDIGITIZER ACQUISITION:\n"));
   MosPrintf(MIL_TEXT("----------------------\n\n"));
   MosPrintf(MIL_TEXT("Continuous image grab in progress.\n"));
   MosPrintf(MIL_TEXT("Press <Enter> to stop.\n\n"));
   MosGetch();

   /* Stop continuous grab. */
   MdigHalt(MilDigitizer);

   /* Pause to show the result. */
   MosPrintf(MIL_TEXT("Continuous grab stopped.\n\n"));
   MosPrintf(MIL_TEXT("Press <Enter> to do a single image grab.\n\n"));
   MosGetch();

   /* Monoshot grab. */
   MdigGrab(MilDigitizer, MilImage);

   /* Pause to show the result. */
   MosPrintf(MIL_TEXT("Displaying the grabbed image.\n"));
   MosPrintf(MIL_TEXT("Press <Enter> to end.\n\n"));
   MosGetch();

   /* Free defaults. */
   MappFreeDefault(MilApplication, MilSystem, MilDisplay, MilDigitizer, MilImage);

   return 0;
}

