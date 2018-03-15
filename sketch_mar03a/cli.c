#include <util.h>

/* module for robot hand cli functionality 
 */
typedef unsigned char COMMAND_STATUS;

//we will have to do all of the functions in a argc/ argv manner
typedef COMMAND_STATUS (*cli_function_pointer)(unsigned char, char *);

//Ass of right now this is staticly set, might want to make it dynamic and use 
//a list at some point if the number of functions grows
#define NUM_FUNCTIONS 0

//TODO: need way to specify expected types of params, maybe enum?
struct {
  char * func_name;
  char num_arguments;
  cli_function_pointer func_ptr;
} Function;

struct Function Functions [NUM_FUNCTIONS];

/* Sting compare function so we don't need std lib
 */
COMMAND_STATUS cli_strcmp(char * str1, char * str2)
{
  int ii = 0;
  if(str1 == 0 || str2 == 0)
    return 0;
  while(*(str1 + ii) == *(str2 + ii)){
    if(*(str1 + ii) == '\0'){
      if(*(str2 + ii) == '\0')
        return 1;
      return 0;//if we reach the end of str1 but not str2 we know they're not same
    }
    ii++;
  }
  return 0;
}

/* Does the specified funtion exist?
 * If it does we return a pointer to the Function struct, it not we return NULL
 */
Function * find_function(char * name)
{
  int i;
  for(i = 0; i < NUM_FUNCTIONS; i++)
    if(cli_strcmp(name, Functions[i].func_name))
      return Functions + i;
  return 0;
}

/* Function to call the supplied function.
 * Needs to parse the line that the user sent in into the function and args
 *
 * Command is expected to be a line that was entered in serial.
 * 	Ex: rotate 0 180
 * The function will call the function 'rotate' with the params 0 and 180
 *
 * TODO: Fix the fundamental problem with this function, it expects that the user
 * is not an idiot.  If more than one space seperates words it won't work
 */
COMMAND_STATUS call_function(char * command)
{
  if(!command)//error if null pointer
    return 1;
  u_i8 split_size = 0; 
  split_size = get_split_size(command);

  //I know you can't do this in c, maybe you can in c++. Otherwise dynamic
  char * argv [split_size - 1];
  char * func_name;

  identify_and_parse(command, func_name, argv, slpit_size - 1);
  //at this point we should have all of the correct things in the correct slots
  
  Function * function = finc_function(func_name);
  if(function == 0)
    return 1;

  //we have the function.  Call it and everything
}

int main()
{
    return 0;
}
