#ifndef FUNCTIONS_HEADER
    #define FUNCTIONS_HEADER
#include "util.h"

//we will have to do all of the functions in a argc/ argv manner
typedef COMMAND_STATUS (*cli_function_pointer)(unsigned char, 
                                               char [MAX_NUM_ARGS][MAX_ARG_LEN]);
//Ass of right now this is staticly set, might want to make it dynamic and use 
//a list at some point if the number of functions grows
#define NUM_FUNCTIONS 2

typedef struct {
  char * func_name;
  char num_arguments;
  cli_function_pointer func_ptr;
} Function;

//Defined functions
COMMAND_STATUS test_func(unsigned char argc, char argv [MAX_NUM_ARGS][MAX_ARG_LEN]);
COMMAND_STATUS arg_test_function(unsigned char argc, char argv [MAX_NUM_ARGS][MAX_ARG_LEN]);

Function Functions [NUM_FUNCTIONS];
#endif
