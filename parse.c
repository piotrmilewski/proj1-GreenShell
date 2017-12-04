#include "parse.h"

/*
    Determines whether an array is empty
    Arguments:
        arg: array to be checked
    Return:
        0 if false
        1 if true
*/
int is_arg_empty(char *arg) {
  while(*arg) {
    if (!isspace((unsigned char)*arg)) {
      return 0;
    }
    arg++;
  }
  return 1;
}


/*
    Parses an array into a multi-dimensional array utilizing strsep
    Uses blank spaces as delimeters
    Arguments:
        args: 1D array to be converted
    Return:
        char *: 2D array after being parsed by blank spaces
*/
char **parse_args(char *args) {
    char *found; 
    char **arglist;
    
    int index = 0;
    while( (found = strsep( &args, " ")) != NULL) {
        // Realloc based on where we are in the array
        if (is_arg_empty(found))
            continue;

        arglist[index] = found;

        index++;
    }

    arglist[index] = '\0';

    return arglist;
}

