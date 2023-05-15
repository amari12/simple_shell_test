#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 1024
#define ARGS_SIZE 50

/*file: main.c*/
/*void prompt();*/

/*file: process_input.c*/
/*char **get_input();*/
/*void separate_input(char **input, char **arguments, char *command);*/
/*int exe_command(char *command, char **arguments);*/
/*int forking(char *command, char **arguments);*/

/*global variables -> builtin functions */
/*char *bi_cmds[] = {"cd", "help", "exit"};*/
/*int (*bi_functions[])(char *, char **) = {&ss_cd, &ss_help, &ss_exit};*/
/*ss = simple shell*/
/*bi = builtin*/

/*file: builtins.c*/
/*int get_nr_bi();*/
/*int ss_cd(char *command, char **arguments);*/
/*int ss_help(char *command, char **arguments);*/
/*int ss_exit(char *command, char **arguments);*/

/*global variables -> builtin functions */
/*extern char *bi_cmds[] = {"cd", "help", "exit"};*/
/*extern int (*bi_functions[])(char *, char **) = {&ss_cd, &ss_help, &ss_exit};*/
/*extern char *bi_cmds[];*/
/*extern int (*bi_functions[])(char *, char **);*/
/*ss = simple shell*/
/*bi = builtin*/

/*=====================*/
/*file: process_input2.c*/
void get_input(char *input);
void split_input(char *input, char *args[]);

/*file: handle_bi.c*/
int handle_builtins(char *args[]);

#endif
