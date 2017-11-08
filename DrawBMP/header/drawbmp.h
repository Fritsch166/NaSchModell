#ifndef _INC_DRAWBMPH
#define _INC_DRAWBMPH


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

#endif // _INC_DRAWBMPH