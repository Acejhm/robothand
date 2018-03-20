#include "util.h"

u_i8 get_split_size(char * function)
{
  u_i8 size = 0, counter = 0;
  while(*(function + counter) != '\0'){
    if(*(function + counter) == ' ')
      size++;
    counter++;
  }
  return size + 1;
}

u_i8 strcpyuntil(char * from, char * to, char split, u_i8 start)
{
  u_i8 ii = 0;
  while(*(from + ii + start) != '\0' && *(from + ii + start) != split){
    to[ii] = from[ii + start];
    ii++;
  }
  to[ii] = '\0';
  return ii;
}

void identify_and_parse(char * command, char * function, 
                        char argv [MAX_NUM_ARGS][MAX_ARG_LEN], u_i8 argc)
{
  //ii is the word index, the function is at index 0, all args are after it
  u_i8 ii = 0, jj = 0, kk = 0;
  ii = strcpyuntil(command, function, ' ', 0) + 1;
  argc--;
  for(jj = 0; jj < argc; jj++){
    kk = strcpyuntil(command, argv[jj], ' ', ii);
    if(kk == 0){
      ii++;
      jj--;
      continue;
    }
    ii += kk + 1;
  }
}

u_i8 find_num_args(char * str)
{
  //we start with found space true to deal with leading whitespace
  u_i8 found_space = 1, num_args = 0, ii = 0;
  while(str[ii] != '\0'){
    if(found_space && str[ii] != ' '){
      found_space = 0;
      num_args++;
    }else if(!found_space && str[ii] == ' ')
      found_space = 1;
    ii++;
  }
  return num_args;
}

/* Sting compare function so we don't need std lib
 */
COMMAND_STATUS cli_strcmp(char * str1, char * str2)
{
  u_i8 ii = 0;
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

void clear_newline(char * str)
{
  u_i8 ii = 0;
  while(*(str + ii) != '\0'){
    if(*(str + ii) == '\n'){
      *(str + ii) = '\0';
      break;
    }
    ii++;
  }
}

