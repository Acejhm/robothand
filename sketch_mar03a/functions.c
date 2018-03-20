#include "util.h"
#include "functions.h"

Function Functions [NUM_FUNCTIONS] = {
  {
    .func_ptr = test_func,
    .func_name = "test",
    .num_arguments = 0
  },
  {
    .func_ptr = arg_test_function,
    .func_name = "arg_test",
    .num_arguments = 10//not sure how to do 'n' arguments
  },
};

COMMAND_STATUS test_func(unsigned char argc, char argv [MAX_NUM_ARGS][MAX_ARG_LEN])
{
  if(argc != 0){
    printf("Incorrect number of arguments!\n");
    return 2;
  }
  printf("Test function\n");
  return 0;
}

COMMAND_STATUS arg_test_function(unsigned char argc, char argv [MAX_NUM_ARGS][MAX_ARG_LEN])
{
  u_i8 ii;
  printf("Arg test function!\n");
  for(ii = 0; ii < argc; ii++)
    printf("arg%d: '%s'\n", ii + 1, argv[ii]);
  return 0;
}

