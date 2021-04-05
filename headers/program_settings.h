/*> Description ******************************************************************************************************/
/**
 * @brief Describes the program settings sctructure.
 * @file program_settings.h
 */

/*> Multiple Inclusion Protection ************************************************************************************/
#ifndef PROGRAM_SETTINGS_H
#define PROGRAM_SETTINGS_H

/*> Includes *********************************************************************************************************/
#include <stdbool.h>

/*> Defines **********************************************************************************************************/

/*> Type Declarations ************************************************************************************************/
/**
 * @brief Structure containing the settings of the program execution set by the input arguments.
 * @param path_str The string of the path to open.
 * @param depth The depth of the tree.
 * @param help Boolean value whether help information should be printed or not.
 */
typedef struct Program_Settings
{
  char path_str[200];
  int depth;
  bool help;
} Program_Settings;

/*> Constant Declarations ********************************************************************************************/

/*> Variable Declarations ********************************************************************************************/

/*> Function Declarations ********************************************************************************************/

/*> End of Multiple Inclusion Protection *****************************************************************************/
#endif 
