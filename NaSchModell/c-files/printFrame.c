/*!
 *  @file printFrame.c
 *  @brief This function prints a Frame
 *  @author Daniel W. Fritsch
 *  @date 23.12.2012
 */

#include "..\h-files\naschmodell.h"


 /*!
  * @fn void printFrame(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight)
  * @brief Prints a frame with the FILLCHAR -> look at NDame.h define
  * @param siXStart - First value - X-Coord from the left
  * @param siYStart - Fecond value - Y-Coord from the top
  * @param siLength - Third value - Length of the frame
  * @param siHeight - Fourth value - Height of the frame
  * @author Daniel W. Fritsch
  * @date 23.12.2012
  */
void printFrame(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight)
{
   //Prints horizontal
   for (short int siX = 0; siX < siLength; siX++)
   {
      //top
      _gotoxy(siXStart + siX, siYStart);
      printf("%c", FILLCHAR);

      //bottom
      _gotoxy(siXStart + siX, siYStart + siHeight - 1);
      printf("%c", FILLCHAR);
   }

   //Prints vertical
   for (short int siY = 0; siY < siHeight; siY++)
   {
      //left
      _gotoxy(siXStart, siYStart + siY);
      printf("%c", FILLCHAR);

      //right
      _gotoxy(siXStart + siLength - 1, siYStart + siY);
      printf("%c", FILLCHAR);
   }

   //Standard position of the cursor
   _gotoxy(0, 0);
}

