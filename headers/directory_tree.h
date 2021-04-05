/*> Description ******************************************************************************************************/
/**
 * @brief Describes the directory tree structure.
 * @file directory_tree.h
 */

/*> Multiple Inclusion Protection ************************************************************************************/
#ifndef DIRECTORY_TREE_H
#define DIRECTORY_TREE_H

/*> Includes *********************************************************************************************************/
#include <stdbool.h>

/*> Defines **********************************************************************************************************/
#define MAX_NUMBER_CHILDREN 1000

/*> Type Declarations ************************************************************************************************/
/**
 * @brief A stucture repesenting a directory tree. Each node is either a directory or a file.
 * @param depth The depth of the tree from the current node.
 * @param is_directory Indication whether path is a direcory. If false, it is a file.
 * @param is_base True if it is the top node of the tree.
 * @param path_string The string of the path to the directory/file.
 * @param children_count The number of children this node has, i.e. number of files/ directories this directory 
 *                       contains.
 * @param children An array of pointers to the children nodes of this node.
 */
typedef struct Directory_Tree
{
  int depth;
  bool is_directory;
  bool is_base;
  char path_string[200];
  int children_count;
  struct Directory_Tree* children[MAX_NUMBER_CHILDREN];
} Directory_Tree;

/*> Constant Declarations ********************************************************************************************/

/*> Variable Declarations ********************************************************************************************/

/*> Function Declarations ********************************************************************************************/
Directory_Tree* create_directory_tree(char* base_path_string, int depth);

void free_directory_tree(Directory_Tree* dir_tree);

void print_directory_tree(Directory_Tree* dir_tree);

/*> End of Multiple Inclusion Protection *****************************************************************************/
#endif 
