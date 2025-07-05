#include "../../../include/user/command.h"

#include <stddef.h>

#include "../../../include/drivers/ps2.h"

CommandEntry commands_table[] = {
    {"ls", ls_handler, "List files"},
    {"cat", cat_handler, "Show file"},
    {"dd", dd_handler, "Disk operations"},
    {"help", help_handler, "Show commands"},
    {NULL, NULL, NULL}
};

int ls_handler(int argc, char** argv) {
    kprintf("Hello world!\n", 0x07);
    return 0;
}

int cat_handler(int argc, char** argv) {
    kprintf("Hello world!\n", 0x07);
    return 0;
}

int dd_handler(int argc, char** argv) {
    char c;
    while ((c = getchar()) != 'q') {
        kprintf("DD>%c\n", 0x07, c);
        if (c == 'h') {
            kprintf("Disk dump tool\n", 0x07);
        } else {
            putchar(c, 0x07);
        }
    }
    return 0;
}

int help_handler(int argc, char** argv) {
    kprintf("Hello world!\n", 0x07);
    return 0;
}
