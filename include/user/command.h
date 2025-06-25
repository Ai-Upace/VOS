#ifndef COMMAND_H
#define COMMAND_H

struct Command {
    const char *command;
    void (*handler)(int argc, char** argv);
    const char* description;
};

extern struct Command commands_table[] = {
    {"help", help_handler},
    {"dd", dd_handler},
};

#endif //COMMAND_H
