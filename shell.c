#include "shell.h"

// It's green and bold! wwowzers!
// the %d is for shell colors
const char * PROMPT = "\e[1;4;%dm%s@%s:%s$\e[0m ";

// Animation counter for badass animation
int animation_counter = 0;

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

void make_prompt(char *buffer) {
    
    int start = 31, end = 36;
    int animation_color = start + (animation_counter % (end - start + 1));

    uid_t uid = geteuid();

    struct passwd *pw = getpwuid(uid);

    char *uname = pw->pw_name;
    char machine[128];
    gethostname(machine, 128);
 
    char dir[256];
    getcwd(dir, 256);
      
    char *home_dir = pw->pw_dir;
    int home_dir_len = strlen(home_dir);
      
    
    // Find our home dir so we can shorten our directory path
    char *home_dir_buffer = malloc(home_dir_len);
    strncpy(home_dir_buffer, dir, home_dir_len);
    home_dir_buffer[home_dir_len] = '\0';
    
    // If the start of our dir is the same as our home dir,
    // insert a ~ to shorten our home dir
    if (!strcmp(home_dir_buffer, home_dir)) {
        int result_len = strlen(dir) - home_dir_len;
        char *modified_dir = malloc( 1 + result_len);
        memcpy( &modified_dir[1], &dir[home_dir_len], result_len);
        modified_dir[0] = '~';
        modified_dir[1 + result_len] = '\0';
        sprintf(buffer, PROMPT, animation_color, uname, machine, modified_dir);
    }
    else{
        sprintf(buffer, PROMPT, animation_color, uname, machine, dir);
    }
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

void exec_args(char **args){
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
    if (args[0] == 0);
    else if (!strcmp(args[0], "cd")){
        chdir(args[1]);
    }
    else if (!strcmp(args[0], "exit")){
        exit(0);
    }
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

        // Increment animation counter
        animation_counter++;

        exec_args(parse_args(input));
        //printf("Result: %s", input);
    }
    return 0;
}
