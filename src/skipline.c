#include "os/shell/shell_command_utils.h"
#include "os/system_time.h"

/* ************************************************************************** */

void SkipLine(uint16_t n) {
    for (uint16_t i = 1; i <= n; i++) {
        if (i % 4 == 0) {
            printf("Skip");
        }
        if (i % 9 == 0) {
            printf("Line");
        }
        if ((i % 4) && (i % 9)) {
            printf("%u", i);
        }
        printf("\r\n");
    }
}

const char code[] = "void SkipLine(uint16_t n) {\r\n\
    for (uint16_t i = 1; i <= n; i++) {\r\n\
        if (i % 4 == 0) {\r\n\
            printf(\"Skip\");\r\n\
        }\r\n\
        if (i % 9 == 0) {\r\n\
            printf(\"Line\");\r\n\
        }\r\n\
        if ((i % 4) && (i % 9)) {\r\n\
            printf(\"%u\", i);\r\n\
        }\r\n\
        printf(\"\r\n\");\r\n\
    }\r\n\
}";

void sh_skipline(int argc, char **argv) {
    switch (argc) {
    case 1:
        println("usage: \tskipline <n>");
        println("\tskipline --code");
        return;
    case 2:
        if (!strcmp(argv[1], "--code")) {
            println(code);
        } else {
            // if (is)
            SkipLine(atoi(argv[1]));
        }
        return;
    }
    println("invalid arguments");
}

void skipline_init(void) {
    shell_register_command(sh_skipline, "skipline"); //
}