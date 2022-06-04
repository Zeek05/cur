// a commandline plugin that allows you to set the current cursor position as well as enable/disable cursor blink
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct CUR {
    int x;
    int y;
} CUR;

// a function that returns the x/y coordinates of the cursor
CUR getCursor() {
    CUR cur;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cur.x = csbi.dwCursorPosition.X;
    cur.y = csbi.dwCursorPosition.Y;
    return cur;
}

// a function that sets the cursor position
void setCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// a function that enables/disables cursor blink
void setCursorBlink(int enable) {
    // use ansi escape to set the cursor blink state
    printf("\033[?12%c", enable ? 'h' : 'l');
    return;
}

void setCursorSize(int dwSize) {
    // if dwSize is 0 then set the cursor size to the default
    if (dwSize == 0) {
        dwSize = 25;
    }
    // if dwSize is greater than 100 then set the cursor size to 100
    if (dwSize > 100) {
        dwSize = 100;
    }
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = dwSize;
    cci.bVisible = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void showHideCursor(int show) {
    // use ansi escape to set the cursor visibility
    printf("\033[?25%c", show ? 'h' : 'l');
    return;
}

// help function
void doHelp() {
    // enable VIRTUAL_TERMINAL_PROCESSING
    DWORD mode;
    GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode);
    // enable text blink
    printf("\x1b[5m");
    // set the text to blue background and white foreground
    printf("\x1b[44m\x1b[37m");
    // print the program name
    printf("cur.exe by ZeekHalkyr");
    // disable text blink
    printf("\x1b[25m");
    // restore color
    printf("\x1b[0m\n\n");
    // print the description
    printf("\x1b[41m\x1b[37mDescription:\x1b[0m\nGet and set the cursor position, and toggle the cursor blink.\n\n");
    // print the usage
    printf("\x1b[41m\x1b[37mUsage:\x1b[0m cur.exe <command> [arguments]\n");
    // print the commands
    printf("\n\x1b[41m\x1b[37mCommands:\x1b[0m\n\n");
    printf("  get - get the current cursor position\n");
    printf("  set <x> <y> - set the cursor position\n");
    printf("  blink <on/off> <opt. size 0-100> - toggle the cursor blink \n");
    printf("  size <size 0-100> - set the cursor size\n");
    printf("  show <on/off> - toggle the cursor visibility\n");
    printf("  help - print this help message\n\n");
    printf("\x1b[41m\x1b[37mOther notes:\x1b[0m\n");
    printf("When getting the cursor position in the shell, the cursor position will be the position just below the prompt.\n");
    printf("If you specify an invalid number, it will default to 0.\n");
    printf("The console cursor size is not an exact. Some sizes display the same as others.\n");
    printf("Adjusting the cursors size will turn the cursor back on.\n");


}

void enableVT() {
    // enable VIRTUAL_TERMINAL_PROCESSING
    DWORD mode;
    GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode);
}

// main function
// takes in the commandline arguments and calls the appropriate functions
int main(int argc, char *argv[]) {
    // if there is no argument then display the help function
    if (argc < 2) {
        doHelp();
        return 1;
    }

    enableVT(); 

    // if the first argument is /? or -? or help then display the help function
    if (strcmp(argv[1], "/?") == 0 || strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "help") == 0) {
        doHelp();
        return 0;
    }

    // if the first argument is get then get the cursor position and print it to stdout
    if (strcmp(argv[1], "get") == 0) {
        CUR cur = getCursor();
        printf("%d %d\n", cur.x, cur.y);
        return 0;
    }

    // if the first argument is set then set the cursor position
    if (strcmp(argv[1], "set") == 0) {
        // if there is not two arguments then display the help function
        if (argc < 4) {
            doHelp();
            return 1;
        }
        // set the cursor position to the x and y coordinates, if it is not a valid number then the invalid number defaults to 0
        setCursor(atoi(argv[2]), atoi(argv[3]));
        return 0;
    }

    // if the first argument is blink then toggle the cursor blink
    if (strcmp(argv[1], "blink") == 0) {
        // if there is not two arguments then display the help function
        if (argc < 3) {
            doHelp();
            return 1;
        }
        // if the second argument is on then enable the cursor blink
        if (strcmp(argv[2], "on") == 0) {
            setCursorBlink(1);
            return 0;
        }
        // if the second argument is off then disable the cursor blink
        if (strcmp(argv[2], "off") == 0) {
            setCursorBlink(0);
            return 0;
        }
        // if the second argument is not on or off then display the help function
        doHelp();
        return 1;
    }

    // if the first argument is size then set the cursor size
    if (strcmp(argv[1], "size") == 0) {
        // if there is not two arguments then display the help function
        if (argc < 3) {
            doHelp();
            return 1;
        }
        // set the cursor size to the size, if it is not a valid number then the invalid number defaults to 25
        setCursorSize(atoi(argv[2]));
        return 0;
    }

    // if the first argument is show then toggle the cursor visibility
    if (strcmp(argv[1], "show") == 0) {
        // if there is not two arguments then display the help function
        if (argc < 3) {
            doHelp();
            return 1;
        }
        // if the second argument is on then enable the cursor visibility
        if (strcmp(argv[2], "on") == 0) {
            showHideCursor(1);
            return 0;
        }
        // if the second argument is off then disable the cursor visibility
        if (strcmp(argv[2], "off") == 0) {
            showHideCursor(0);
            return 0;
        }
        // if the second argument is not on or off then display the help function
        doHelp();
        return 1;
    }

    // if it is not a recognized command then display the help function
    doHelp();
}