#include "exec.h"

void exec_args(char **args){
    //if multiple commands separated by ';'
    int i = 0;
    while (args[i]){
        if (strchr(args[i], ';')){
            args[i] = 0;
            exec_args(args);
            args = args + i + 1;
            i = 0;
        }
        i++;
    }
    //if no arguments
    if (args[0] == 0);
    //cd call
    else if (!strcmp(args[0], "cd")){
        chdir(args[1]);
    }
    //exit call
    else if (!strcmp(args[0], "exit")){
        exit(0);
    }
    //execute everything else
    else{
        int pid = fork();
        // If we're the child
        if (!pid) {
            //printf("arglist: %s, %s, %s\n", arglist[0], arglist[1], arglist[2]);
            if (execvp(args[0], args) < 0) {
                printf("execvp failed!\n");
            }
            exit(0);
        } else {
            wait(0);
        }
    }
}

