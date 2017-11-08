
#include "..\h-files\drawbmp.h"

#include <stdio.h>


void drawbmp(
   const char * pcFilename,
   const int iWIDTH,
   const int iHEIGHT,
   const unsigned char ** const ppcRED,
   const unsigned char ** const ppcGREEN,
   const unsigned char ** const ppcBLUE
)
{

   unsigned int headers[13];
   FILE * outfile;
   int extrabytes;
   int paddedsize;
   int x; int y; int n;
   int red = 0, green = 0, blue = 0;


   extrabytes = 4 - ((iWIDTH * 3) % 4);                 // How many bytes of padding to add to each
                                                       // horizontal line - the size of which must
                                                       // be a multiple of 4 bytes.
   if (extrabytes == 4)
      extrabytes = 0;

   paddedsize = ((iWIDTH * 3) + extrabytes) * iHEIGHT;

   // Headers...
   // Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

   headers[0] = paddedsize + 54;      // bfSize (whole file size)
   headers[1] = 0;                    // bfReserved (both)
   headers[2] = 54;                   // bfOffbits
   headers[3] = 40;                   // biSize
   headers[4] = iWIDTH;               // biWidth
   headers[5] = iHEIGHT;              // biHeight
   headers[6] = 0x00180001;           // biPlanes and biBitCount in position 6, but they're shorts.
   headers[7] = 0;                    // biCompression
   headers[8] = paddedsize;           // biSizeImage
   headers[9] = 0;                    // biXPelsPerMeter
   headers[10] = 0;                   // biYPelsPerMeter
   headers[11] = 0;                   // biClrUsed
   headers[12] = 0;                   // biClrImportant


   //
   // Open FILE ..
   //

   fopen_s(&outfile, pcFilename, "wb");

   //
   // Headers begin...
   // When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
   //

   fprintf(outfile, "BM");

   for (n = 0; n <= 12; n++)
   {
      fprintf(outfile, "%c", headers[n] & 0x000000FF);
      fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
      fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
      fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
   }

   //
   // Headers done, now write the data...
   //

   for (y = iHEIGHT - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
   {
      for (x = 0; x <= iWIDTH - 1; x++)
      {
         // Also, it's written in (b,g,r) format...

         fprintf(outfile, "%c", ppcBLUE[x][y]);
         fprintf(outfile, "%c", ppcGREEN[x][y]);
         fprintf(outfile, "%c", ppcRED[x][y]);
      }

      if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
      {
         for (n = 1; n <= extrabytes; n++)
         {
            fprintf(outfile, "%c", 0);
         }
      }

   }

   fclose(outfile);
   return;
}