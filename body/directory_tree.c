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

static inline char last_char(char* string);

static void add_directory_tree_child(char* file_name, Directory_Tree* parent);

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
 * @brief Gets the last char of a string.
 * @param str [in] The string.
 * @return The last character of the string.
 */
static inline char last_char(char* str)
{
  return str[strlen(str) - 1];
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
    new_dir_tree->is_directory = is_directory(new_path_string) && !is_symbolic_link(new_path_string);
    new_dir_tree->is_base = false;
    strcpy(new_dir_tree->path_string, new_path_string);
    if (new_dir_tree->is_directory)
    {
      strcat(new_dir_tree->path_string, "/");
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

      printf("Opened directory %s\n", new_path_string);
      printf("Is symbolic link: %d\n", is_symbolic_link(new_path_string));

      struct dirent* directory_entry_p = readdir(dir_stream_p);
      while (directory_entry_p != NULL)
      {
        printf("Read %s\n", directory_entry_p->d_name);
        add_directory_tree_child(directory_entry_p->d_name, new_dir_tree);
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

/*> Global Function Definitions **************************************************************************************/
Directory_Tree* create_directory_tree(char* base_path_string, int depth)
{
  if (path_exists(base_path_string))
  {
    Directory_Tree* dir_tree = (Directory_Tree*) malloc(sizeof(Directory_Tree));
    dir_tree->depth = depth;
    dir_tree->is_directory = is_directory(base_path_string);
    dir_tree->is_base = true;
    strcpy(dir_tree->path_string, base_path_string);
    if (dir_tree->is_directory && last_char(dir_tree->path_string) != '/') {
      strcat(dir_tree->path_string, "/");
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
        printf("Read %s\n", directory_entry_p->d_name);
        add_directory_tree_child(directory_entry_p->d_name, dir_tree);
        directory_entry_p = readdir(dir_stream_p);
      }

      closedir(dir_stream_p);
    }
  }
  else
  {
    printf("Could not find path: %s\n", base_path_string);
    exit(1);
  }

}

void free_directory_tree(Directory_Tree* dir_tree)
{
  /* TODO */
}

void print_directory_tree(Directory_Tree* dir_tree)
{
  /* TODO */
}