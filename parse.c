#include "parse.h"

// Returns whether an arg is empty
int is_arg_empty(char *arg) {
  while(*arg) {
    if (!isspace((unsigned char)*arg)) {
      return 0;
    }
    arg++;
  }
  return 1;
}


// Makin' me re-invent arraylist ova' hea'
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

