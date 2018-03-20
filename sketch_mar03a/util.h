#ifndef UTIL_HEADER
    #define UTIL_HEADER
//I think that stdio is the only module we actually need
#include <stdio.h>
#include <unistd.h>

#define MAX_NUM_ARGS 5
#define MAX_ARG_LEN 20

typedef unsigned char COMMAND_STATUS;
typedef unsigned char u_i8; //probably could be named better

/* Helper function that will tell us the number of elements to
 * expect from our split. Simply number of spaces + 1
 */
u_i8 get_split_size(char * function);

/* This function will take in the entire string command that the user entered into the cli
 * in the command variable, put the first space seperated word into function, and all remaning
 * words into the elements of argv sequentially.
 */
void identify_and_parse(char * command, char * function, 
                        char argv [MAX_NUM_ARGS][MAX_ARG_LEN], u_i8 argc);

/* Returns the total number of arguments passed in, counting the function name
 * itself as a parameter
 */
u_i8 find_num_args(char * str);

/* Sting compare function so we don't need std lib
 */
COMMAND_STATUS cli_strcmp(char * str1, char * str2);

/* Removes the first newline from a string and replaces with NULL byte
 */
void clear_newline(char * str);

#endif
