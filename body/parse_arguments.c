/*> Description ******************************************************************************************************/
/**
* @brief Methods for parsing the arguments of the program.
* @file parse_arguments.c
*/

/*> Includes *********************************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program_settings.h"
#include "string_util.h"

/*> Defines **********************************************************************************************************/

/*> Type Declarations ************************************************************************************************/

/*> Global Constant Definitions **************************************************************************************/

/*> Global Variable Definitions **************************************************************************************/

/*> Local Constant Definitions ***************************************************************************************/

/*> Local Variable Definitions ***************************************************************************************/

/*> Local Function Declarations **************************************************************************************/
static void initatalize_settings(Program_Settings* settings_p);

static bool check_for_help_argument(char* argument_array[], int* argument_index_p, Program_Settings* settings_p);

static bool parse_option_arguments(int argument_count, 
                                   char* argument_array[], 
                                   int* argument_index_p, 
                                   Program_Settings* settings_p);

/*> Local Function Definitions ***************************************************************************************/
/**
 * @brief Initalizes the settings struct with default values.
 * @param settings_p [out] Pointer to the settings structure for the execution of the program.
 */
void initatalize_settings(Program_Settings* settings_p)
{
  settings_p->depth = 1;
  settings_p->help = false;
  strcpy(settings_p->path_str, "./");
}

/**
 * @brief Checks for the '--help' argument, and if present updates execution settings.
 * @param argument_array [in] The array containing the arguments.
 * @param argument_index_p [in/out] Pointer to the current argument index.
 * @param settings_p [out] Pointer to the settings structure for the execution of the program.
 * @return True if '--help' argument is present, false otherwise.
 */
static bool check_for_help_argument(char* argument_array[], int* argument_index_p, Program_Settings* settings_p)
{
  if (strings_are_equal(argument_array[*argument_index_p], "--help"))
  {
    settings_p->help = true;
    (*argument_index_p)++;
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Parses the option arguments and sets the program settings accordingly.
 * @param argument_count [in] The number of arguments.
 * @param argument_array [in] The array containing the arguments.
 * @param argument_index_p [in/out] Pointer to the current argument index.
 * @param settings_p [out] Pointer to the settings structure for the execution of the program.
 * @return True if method successfully parses all option arguments, false otherwise.
 */
static bool parse_option_arguments(int argument_count, 
                                   char* argument_array[], 
                                   int* argument_index_p, 
                                   Program_Settings* settings_p)
{
  if (strings_are_equal(argument_array[*argument_index_p], "-d") ||
      strings_are_equal(argument_array[*argument_index_p], "--depth"))
  {
    (*argument_index_p)++;
    if (*argument_index_p < argument_count && 
        is_numeric_string(argument_array[*argument_index_p]))
    {
      int depth = atoi(argument_array[*argument_index_p]);
      (*argument_index_p)++;
      settings_p->depth = depth;
    }
    else
    {
      return false;
    }
  }

  return true;
}

/*> Global Function Definitions **************************************************************************************/
/**
 * @brief Parses arguments and set the execution settings.
 * @param argument_count [in] The number of arguments.
 * @param argument_array [in] The array containg the arguments.
 * @param settings_p [out] Pointer to the settings structure for the execution of the program.
 * @return True if the arguments could be parsed successfully, false otherwise.
 */
bool parse_arguments(int argument_count, char* argument_array[], Program_Settings* settings_p)
{
  /* The usage order is: tree [--help] [<options>] [<path>] 
     Thus this method checks for help, options and path in that order. */

  int argument_index = 1;

  initatalize_settings(settings_p);
  
  /* Check for the '--help' argument*/
  if (argument_index < argument_count)
  {
    bool will_print_help = check_for_help_argument(argument_array, &argument_index, settings_p);

    /* Do not check remaining arguments if help should be printed. */
    if (will_print_help)
    {
      return true;
    }
  }
  else
  {
    return true;
  }

  /* check for options arguments */
  if (argument_index < argument_count)
  {
    bool successful_parse = parse_option_arguments(argument_count, argument_array, &argument_index, settings_p);

    if (!successful_parse)
    {
      return false;
    }
  }
  else 
  {
    return true;
  }

  /* check for path argument */
  if (argument_index < argument_count)
  {
    stpcpy(settings_p->path_str, argument_array[argument_index]);
    argument_index++;
  }
  else
  {
    return true;
  }

  if (argument_index < argument_count) 
  {
    /* More arguments than expected return false */
    return false;
  }

  return true;
}


