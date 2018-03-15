#include <util.h>

u_i8 get_split_size(char * function)
{
  u_i8 size = 0, counter = 0;
  while(*(function + counter) != '\0')
    if(*(function + counter) == ' ')
      size++;
    counter++;
  return size + 1;
}

void identify_and_parse(char * command, char * function, char * argv [], u_i8 argc)
{
  //ii is the word index, the function is at index 0, all args are after it
  u_i8 ii = 0, jj = 0;

  function = command;
  while(*(command + jj) != '\0'){
    if(*(command + jj) == ' '){
      if(ii == 0){
        //set the space to null byte so its seperated
        command[jj] = '\0';
	//the next character is expected to be the command
	argv[ii] = *(command + jj + 1);
      }else{
        command[jj] = '\0';
	if(ii < argc)
          argv[ii] = *(command + jj + 1);
      }
      ii++;
    }
  jj++;;
  }
}
