/*> Description ******************************************************************************************************/
/**
 * @brief Declares the string helper functions.
 * @file string_util.h
 */

/*> Multiple Inclusion Protection ************************************************************************************/
#ifndef STRING_UTIL_H
#define STRING_UTIL_H

/*> Includes *********************************************************************************************************/
#include <stdbool.h>

/*> Defines **********************************************************************************************************/

/*> Type Declarations ************************************************************************************************/

/*> Constant Declarations ********************************************************************************************/

/*> Variable Declarations ********************************************************************************************/

/*> Function Declarations ********************************************************************************************/
bool is_numeric_string(char* str);

/*> Inline Function Definitions **************************************************************************************/
/**
 * @brief Gets the last char of a string.
 * @param str [in] The string.
 * @return The last character of the string.
 */
static inline char last_char(char* str)
{
  return str[strlen(str) - 1];
}

/**
 * @brief Checks if two are equals.
 * @param str1 [in] First string.
 * @param str2 [in] Second string.
 * @return True if str1 and str2 are equal, false otherwise.
 */
static inline bool strings_are_equal(char* str1, char* str2)
{
  return strcmp(str1, str2) == 0;
}

/*> End of Multiple Inclusion Protection *****************************************************************************/
#endif 
