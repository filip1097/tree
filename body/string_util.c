/*> Description ******************************************************************************************************/
/**
* @brief Defines functions to help manage strings.
* @file string_util.c
*/

/*> Includes *********************************************************************************************************/
#include <stdbool.h>

/*> Defines **********************************************************************************************************/

/*> Type Declarations ************************************************************************************************/

/*> Global Constant Definitions **************************************************************************************/

/*> Global Variable Definitions **************************************************************************************/

/*> Local Constant Definitions ***************************************************************************************/

/*> Local Variable Definitions ***************************************************************************************/

/*> Local Function Declarations **************************************************************************************/

/*> Local Function Definitions ***************************************************************************************/

/*> Global Function Definitions **************************************************************************************/
/**
 * @brief Checks if the input string is made of only numeric characters.
 * @param str [in] The string.
 * @return True if the string only contain digit characters.
 */
bool is_numeric_string(char* str)
{
  int i = 0;

  while (str[i] != '\0')
  {
    /* numeric chars '0'-'9' are  48-57 in ascii. */
    if (str[i] < 48 || str[i] > 57)
    {
      return false;
    }
    i++;
  }

  return true;
}