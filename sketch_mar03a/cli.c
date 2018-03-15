/* module for robot hand cli functionality 
 */
typedef unsigned char COMMAND_STATUS;

//we will have to do all of the functions in a argc/ argv manner
typedef COMMAND_STATUS (*cli_function_pointer)(unsigned char, char *);

//Ass of right now this is staticly set, might want to make it dynamic and use 
//a list at some point if the number of functions grows
#define NUM_FUNCTIONS 0

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

int main()
{
    return 0;
}
