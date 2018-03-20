/* module for robot hand cli functionality 
 */
#include "util.h"
#include "functions.h"

/* Does the specified funtion exist?
 * If it does we return a pointer to the Function struct, it not we return NULL
 */
Function * find_function(char * name)
{
  u_i8 ii;
  for(ii = 0; ii < NUM_FUNCTIONS; ii++){
    if(cli_strcmp(name, Functions[ii].func_name))
      return Functions + ii;
  }
  return 0;
}

/* Function to call the supplied function.
 * Needs to parse the line that the user sent in into the function and args
 *
 * Command is expected to be a line that was entered in serial.
 * 	Ex: rotate 0 180
 * The function will call the function 'rotate' with the params 0 and 180
 *
 */
COMMAND_STATUS call_function(char * command)
{
  u_i8 ii = 0;
  if(!command)
    return 1;

  u_i8 num_args = 0;
  //note that the command itself is counted as an argument
  num_args = find_num_args(command);

  char func_name[256];
  char argv [MAX_NUM_ARGS][MAX_ARG_LEN];

  //this will populate func_name and argv both
  identify_and_parse(command, func_name, argv, num_args);
 
  //if the function exists in defined functions it will show up here
  Function * function = find_function(func_name);
  if(function == 0){
    printf("Function '%s' not found\n", func_name);
    return 1;
  }
  //simply invoke the function with the parameters
  //the function expects only the number of actual arguments, so we subtract 1
  function->func_ptr(num_args - 1, argv);
}

int main(int argc, char * argv[])
{
    COMMAND_STATUS st;
    char buf [256];
    printf("Enter a command: ");
    fgets(buf, 256, stdin);
    clear_newline(buf);

    st = call_function(buf);

    return 0;
}
