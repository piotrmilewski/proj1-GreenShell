#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

void make_prompt(char *);
char **parse_args(char *);
void exec_args(char **);
int main();

#endif
