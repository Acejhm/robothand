
typedef unsigned char u_i8; //probably could be named better

/* Helper function that will tell us the number of elements to
 * expect from our split. Simply number of spaces + 1
 */
u_i8 get_split_size(char * function);

/* This function will take in the entire string command that the user entered into the cli
 * in the command variable, put the first space seperated word into function, and all remaning
 * words into the elements of argv sequentially.
 */
void identify_and_parse(char * command, char * function, char * argv [], u_i8 argc);
