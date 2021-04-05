/*> Description ******************************************************************************************************/
/**
* @brief Describes the basic functionality for the tree program.
* @file tree.c
*/

/*> Includes *********************************************************************************************************/
#include <stdio.h>

#include "directory_tree.h"
#include "parse_arguments.h"
#include "program_settings.h"

/*> Defines **********************************************************************************************************/

/*> Type Declarations ************************************************************************************************/

/*> Global Constant Definitions **************************************************************************************/

/*> Global Variable Definitions **************************************************************************************/

/*> Local Constant Definitions ***************************************************************************************/
const char* HELP_STRING = 
  "usage: tree [--help] [<option> ...] [<path>]\n"
  "\n"
  "These are the available options:\n"
  "  -d or --depth     The depth of the tree (default: 1). Useage: -d 2.\n"
  "\n"
  "If no path provided, \"./\" is used\n";

const char* BAD_FORMAT_STRING =
  "The command was badly formatted, so arguments could not be parsed. Please use 'tree --help' for help.\n";

/*> Local Variable Definitions ***************************************************************************************/

/*> Local Function Declarations **************************************************************************************/
int main(int argument_count, char* argument_array[]);

void execute_program(Program_Settings* settings_p);

/*> Local Function Definitions ***************************************************************************************/
/**
* @brief Main function for tree program.
* @param argument_count [in] Number of input arguments.
* @param argument_array [in] Array containing input arguments. 
* @return The return code of the program. 0 means the program finished correctly.
*/
int main(int argument_count, char* argument_array[])
{
  Program_Settings settings = {0};

  bool successfully_parsed_arguments = parse_arguments(argument_count, argument_array, &settings);
  if (!successfully_parsed_arguments)
  {
    printf("%s", BAD_FORMAT_STRING);
    return 1;
  }

  execute_program(&settings);

  return 0;
}

/**
 * @brief Executes the tree program based on the program settings.
 * @param settings_p [in] Pointer to the program settings for this run.
 */
void execute_program(Program_Settings* settings_p)
{
  if (settings_p->help)
  {
    printf("%s", HELP_STRING);
    return;
  }

  Directory_Tree* dir_tree = create_directory_tree(settings_p->path_str, settings_p->depth);
  print_directory_tree(dir_tree);
  free_directory_tree(dir_tree);
}

/*> Global Function Definitions **************************************************************************************/
