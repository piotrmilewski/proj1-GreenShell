#include "shell.h"

// It's green and bold! wwowzers!
const char * PROMPT = "\e[1;4;32m%s@%s:%s$\e[0m ";

void make_prompt(char *buffer) {
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
        sprintf(buffer, PROMPT, uname, machine, modified_dir);
    }
}

// Makin' me re-invent arraylist ova' hea'
void parse_args(char *args) {
    char *found;
    char **arglist = malloc(sizeof(*arglist)); 

    int index = 0;
    while( (found = strsep( &args, " ")) != NULL) {
        // Realloc based on where we are in the array
        arglist = realloc(arglist, (index + 1) * sizeof(*arglist));
        arglist[index] = found;
        
        //printf("%s, ", arglist[index]);
        index++;
    }
    printf("\n");

    // A newline is inserted at the end of the last argument. We can't have that
    int len = strlen(arglist[index - 1]);
    arglist[index - 1][len - 1] = '\0';

    arglist = realloc(arglist, (index + 1) * sizeof(*arglist));
    arglist[index] = '\0';

    int pid = fork();
    // If we're the child
    if (!pid) {
        //printf("arglist: %s, %s, %s\n", arglist[0], arglist[1], arglist[2]);
        if (execvp(arglist[0], arglist) < 0) {
            printf("execvp failed!\n");
        }
        exit(0);
    } else {
        int status;
        wait(status);
    }
}

int main() {

    char input[128];
    char prompt[256];

    // Programmer Senses are telling me not to do this 
    while(1) {
        // TODO: Replace me!
        make_prompt(prompt);
        printf("%s", prompt);
        //printf(PROMPT, "machine", "user", "dir");
        fgets(input, sizeof(input),stdin);
        parse_args(input);
        //printf("Result: %s", input);
    }
    return 0;
}
