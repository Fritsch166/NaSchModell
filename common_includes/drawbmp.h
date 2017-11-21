#pragma once

/**************************************
 * dll for printing *.bmp file
 **************************************/

#ifdef DLLFUNKTION_EXPORT
#define _DLL_DECLSPEC_ _declspec(dllexport) 
#else
#define _DLL_DECLSPEC_ _declspec(dllimport)
#endif

_DLL_DECLSPEC_ void drawbmp(
   const char * pcFilename,
   const int iWIDTH,
   const int iHEIGHT,
   const unsigned char ** const ppcRED,
   const unsigned char ** const ppcGREEN,
   const unsigned char ** const ppcBLUE
);