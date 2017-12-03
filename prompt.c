#include "prompt.h"

// It's green and bold! wwowzers!
// the %d is for shell colors
const char * promptFormat = "\e[1;4;%dm%s@%s:%s$\e[0m ";

// Animation counter for badass animation
int animation_counter = 0;


void make_prompt(char *buffer) {
   
    // Increment animation counter
    animation_counter++;
   
 
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
        sprintf(buffer, promptFormat, animation_color, uname, machine, modified_dir);
    }
    else{
        sprintf(buffer, promptFormat, animation_color, uname, machine, dir);
    }
}

