#include<stdio.h>


const char * PROMPT = "%s@%s:%s$ ";


int main() {
    
    char input[128];

    // Programmer Senses are telling me not to do this 
    while(1) {
        // TODO: Replace me!
        printf(PROMPT, "machine", "user", "dir");
        fgets(input, sizeof(input),stdin);
        //printf("Result: %s", input);
    }
    return 0;
}
