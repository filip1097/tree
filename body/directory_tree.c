/*> Description ******************************************************************************************************/
/**
* @brief Defines functions to handle the structure Directory_Tree.
* @file directory_tree.c
*/

/*> Includes *********************************************************************************************************/
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "directory_tree.h"
#include "string_util.h"

/*> Defines **********************************************************************************************************/

/*> Type Declarations ************************************************************************************************/

/*> Global Constant Definitions **************************************************************************************/

/*> Global Variable Definitions **************************************************************************************/

/*> Local Constant Definitions ***************************************************************************************/

/*> Local Variable Definitions ***************************************************************************************/

/*> Local Function Declarations **************************************************************************************/
static bool is_directory(char* path_string);

static bool is_symbolic_link(char* path_string);

static bool path_exists(char* path_string);

static void add_directory_tree_child(char* file_name, Directory_Tree* parent);

static void print_node(Directory_Tree* dir_tree, int indentation);

/*> Local Function Definitions ***************************************************************************************/
/**
 * @brief Checks if path is to a directory.
 * @param path_string [in] Path to check.¨
 * @return True if path goes to a directory, false otherwise.
 */
static bool is_directory(char* path_string)
{
  struct stat file_info = {0};
  stat(path_string, &file_info);
  return S_ISDIR(file_info.st_mode);
}

/**
 * @brief Checks if path is a symbolic link.
 * @param path_string [in] Path to check.¨
 * @return True if path goes to a symbolic link, false otherwise.
 */
static bool is_symbolic_link(char* path_string)
{
  struct stat file_info = {0};
  stat(path_string, &file_info);
  return S_ISLNK(file_info.st_mode);
}

/**
 * @brief Checks if the path leads to a real file or directory.
 * @param path_string [in] Path to check.
 * @return True if the path exists, false otherwise.
 */
static bool path_exists(char* path_string)
{
  return access(path_string, F_OK) == 0;
}

/**
 * @brief Creates and add a Directory Tree child to parent.
 * @param file_name [in] The name of the file in the parent directory.
 * @param parent [in/out] The Directory Tree node to add child to
 */
static void add_directory_tree_child(char* file_name, Directory_Tree* parent)
{
  int new_depth = parent->depth - 1;
  char new_path_string[200];
  strcpy(new_path_string, parent->path_string);
  strcat(new_path_string, file_name);

  if (new_depth >= 0 && path_exists(new_path_string))
  {
    Directory_Tree* new_dir_tree = (Directory_Tree*) malloc(sizeof(Directory_Tree));
    new_dir_tree->depth = new_depth;
    new_dir_tree->is_directory = is_directory(new_path_string); 
    new_dir_tree->is_base = false;
    strcpy(new_dir_tree->path_string, new_path_string);
    strcpy(new_dir_tree->file_name, file_name);
    if (new_dir_tree->is_directory)
    {
      strcat(new_dir_tree->path_string, "/");
      strcat(new_dir_tree->file_name, "/");
    }
    new_dir_tree->children_count = 0;

    if (new_dir_tree->is_directory && new_depth > 0)
    {
      /* add children */
      DIR* dir_stream_p = opendir(new_path_string);
      if (dir_stream_p == NULL)
      {
        printf("Could not open the directory: %s\n", new_path_string);
        exit(1);
      }

      struct dirent* directory_entry_p = readdir(dir_stream_p);
      while (directory_entry_p != NULL)
      {
        char* child_name = directory_entry_p->d_name;
        if (!strings_are_equal(child_name, ".") && !strings_are_equal(child_name, ".."))
        {
          add_directory_tree_child(child_name, new_dir_tree);
        }
        directory_entry_p = readdir(dir_stream_p);
      }

      closedir(dir_stream_p);
    }

    parent->children[parent->children_count] = new_dir_tree;
    parent->children_count++;
  }
  else
  {
    printf("Could not find path: %s\n", new_path_string);
    exit(1);
  }
}

/**
 * @brief Prints one node in a Directory_Tree.
 * @param dir_tree [in] The Directory_Tree node to print.
 * @param indentation [in] The number of spaces this node will be printed.
 */
void print_node(Directory_Tree* dir_tree, int indentation)
{
  for (int i = 0; i < indentation; i++)
  {
    printf(" ");
  }

  if (dir_tree->is_base)
  {
    printf("%s\n", dir_tree->path_string);
  }
  else
  {
    printf("|- %s\n", dir_tree->file_name);
  }

  if (dir_tree->depth > 0)
  {
    for (int i = 0; i < dir_tree->children_count; i++)
    {
      print_node(dir_tree->children[i], indentation + 2);
    }
  }
}

/*> Global Function Definitions **************************************************************************************/
/**
 * @brief Creates the directory tree based on the base path provided.
 * @param base_path_string [in] The base path as a string.
 * @param depth [in] How far down relative the base directory to create children directory tree nodes.
 * @return The pointer to the directory tree struct allocated.
 */
Directory_Tree* create_directory_tree(char* base_path_string, int depth)
{
  if (path_exists(base_path_string))
  {
    Directory_Tree* dir_tree = (Directory_Tree*) malloc(sizeof(Directory_Tree));
    dir_tree->depth = depth;
    dir_tree->is_directory = is_directory(base_path_string);
    dir_tree->is_base = true;
    strcpy(dir_tree->path_string, base_path_string);
    strcpy(dir_tree->file_name, base_path_string);
    if (dir_tree->is_directory && last_char(dir_tree->path_string) != '/') {
      strcat(dir_tree->path_string, "/");
      strcat(dir_tree->file_name, "/");
    }
    dir_tree->children_count = 0;

    if (dir_tree->is_directory && depth > 0)
    {
      /* add children */
      DIR* dir_stream_p = opendir(base_path_string);
      if (dir_stream_p == NULL)
      {
        printf("Could not open the directory: %s\n", base_path_string);
        exit(1);
      }

      struct dirent* directory_entry_p = readdir(dir_stream_p);
      while (directory_entry_p != NULL)
      {
        char* child_name = directory_entry_p->d_name;
        if (!strings_are_equal(child_name, ".") && !strings_are_equal(child_name, ".."))
        {
          add_directory_tree_child(child_name, dir_tree);
        }
        directory_entry_p = readdir(dir_stream_p);
      }

      closedir(dir_stream_p);
    }

    return dir_tree;
  }
  else
  {
    printf("Could not find path: %s\n", base_path_string);
    exit(1);
  }

}

/**
 * @brief Frees the allocated memory of the Directory_Tree and all its children recursivly.
 * @param dir_tree [in] Pointer to the Directory_Tree.
 */
void free_directory_tree(Directory_Tree* dir_tree)
{
  for (int i = 0; i < dir_tree->children_count; i++)
  {
    free_directory_tree(dir_tree->children[i]);
  }
  free(dir_tree);
}

/**
 * @brief Prints a directory tree.
 * @param dir_tree [in] The Directory_Tree to print.
 */
void print_directory_tree(Directory_Tree* dir_tree)
{
  print_node(dir_tree, 0);
}