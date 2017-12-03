#include "shell.h"

int main() {

  char input[256];
  char prompt[256];

    // Programmer Senses are telling me not to do this 
    while(1) {
 
        make_prompt(prompt);
        printf("%s", prompt);

        fgets(input, sizeof(input),stdin);
        // Remove the newline at the end of our input
        input[strlen(input) - 1] = '\0';

        exec_args(parse_args(input));
        //printf("Result: %s", input);
    }
    return 0;
}
