/*!
 *  @file deleteArea.c
 *  @brief Deletes a given area at the window
 *  @author Daniel W. Fritsch
 *  @date 23.12.2012
 */

#include "..\h-files\naschmodell.h"

 /*!
  * @fn void deleteArea(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight)
  * @brief Deletes a given area at the window
  * @param siXStart - First value - X-Coord from left
  * @param siYStart - Fecond value - Y-Coord from top
  * @param siLength - Third value - Length of the area
  * @param siHeight - Fourth value - Height of the area
  * @author Daniel W. Fritsch
  * @date 23.12.2012
  */
void deleteArea(const short int siXStart, const short int siYStart, const short int siLength, const short int siHeight)
{

   //Delete Area
   for (short int siY = 0; siY < siHeight; siY++)
   {
      _gotoxy(siXStart, siYStart + siY);

      for (short int siX = 0; siX < siLength; siX++)
      {
         printf(" ");
      }
   }

   //Standard position of the cursor
   _gotoxy(0, 0);
}