#ifndef COMMAND_H
#define COMMAND_H

typedef struct Command {
    const char *command;
    int (*handler)(int argc, char** argv);
    const char* description;
} CommandEntry;

int dd_handler(int argc, char** argv);
int help_handler(int argc, char** argv);
int ls_handler(int argc, char** argv);
int cat_handler(int argc, char** argv);

extern CommandEntry commands_table[];

#endif //COMMAND_H
