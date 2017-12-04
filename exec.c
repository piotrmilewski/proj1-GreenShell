#include "exec.h"

void run_execvp(char **args) {
    int pid = fork();
    if (!pid) {
        if (execvp(args[0], args) < 0) {
            printf("execvp failed!\n");
        }
        exit(0);
    } else {
        wait(0);
    }
}

void copy_args(char **src_args, char *dest_args[], int to_where) {
    int i;
    for(i = 0; i < to_where; i++) {
        dest_args[i] = src_args[i];
    }
    // Damn null terminators
    dest_args[to_where] = NULL;
}

void exec_args(char **args){
    //if multiple commands separated by ';'
    int i = 0;
    while (args[i]){

        if (!strcmp(args[i], ">")) {
        // If we redirect stdout 
            // Overrite stdout
            int file_to_write = open(args[i+1], O_CREAT | O_WRONLY, 0644);
            int stdout_copy = dup(STDOUT_FILENO);
            dup2(file_to_write, STDOUT_FILENO);

            // Make duplicate that excludes everything after the <
            char **copied_args = (char**)malloc( (i+1) * sizeof(*args));
            copy_args(args, copied_args, i);
            run_execvp(copied_args);

            // Free memory and reset stdout
            free(copied_args);
            close(file_to_write); // should this be moved down?
            dup2(stdout_copy, STDOUT_FILENO);
            return;
        } else if (!strcmp(args[i], "<")) {
        // If we redirect stdin
            //TODO: Figure out how stdin works actually
            // Overrite stdin
            printf("File: %s\n", args[i+1]);
            int file_to_write = open(args[i+1], O_WRONLY, 0644);
            int stdin_copy = dup(STDIN_FILENO);
            dup2(file_to_write, STDIN_FILENO);

            // Make duplicate that excludes everything after the <
            char **copied_args = (char**)malloc( (i+1) * sizeof(*args));
            copy_args(args, copied_args, i);
            run_execvp(copied_args);

            // Free memory and reset stdin
            free(copied_args);
            dup2(stdin_copy, STDIN_FILENO);
            close(file_to_write); // should this be moved down?
            return;
        }
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
        run_execvp(args);
    }
}

