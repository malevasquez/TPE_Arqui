#include<stdc.h>
#include<commands.h>
#include<shell.h>

#define MAX 20
#define COMMANDS 8
// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

// Greeting shell during startup
int initShell() {
    //consoleSize(1016, 0, 760, 0);
    clear();
    openHelp();
    printf("Enter command: \n");
    int index;
    char cmd[MAX];
    char ch;
    while(1) {
        index = 0;
        printf(">>> ");
        //ver si esto funciona con scanf
        while(ch != '\n') {
            if(getChar(&ch) == 1)
            if(ch == '\b') {
                putChar(ch);
                if(index > 0) {
                    index--;
                }
                else {
                    putChar(ch);
                    cmd[index++] = ch;
                }
            }
        }
        cmd[index] = 0;
        ch = 0;
        if(cmdHandler(cmd)) {
            return 0;
        }
    }
    clear();
}


// Function to execute builtin commands
int cmdHandler(char *command) {
    char *cmds[COMMANDS];
    cmds[0] = "exit";
    cmds[1] = "help";
    cmds[2] = "divzero";
    cmds[3] = "opcode";
    cmds[4] = "inforeg";
    cmds[5] = "printmem";
    cmds[6] = "datetime";
    cmds[7] = "4in1";

    int argNum = -1;
    for(int i = 0; i < COMMANDS; i++) {
        if(strcmp(command, cmds[i]) == 0) {
            argNum = i;
        }
    }

    switch(argNum) {
    case 1:
        //exit(0);
        return 1;
    case 2:
        openHelp();
        return 1;
    case 3:
        throwDivZero();
        return 1;
    case 4:
        throwOpcode();
        return 1;
    case 5:
        //infoReg();
        return 1;
    case 6:
        //printMem();
        return 1;
    case 7:
        //dateTime();
        return 1;
    case 8:
        //4in1();
        return 1;
    default:
        printf("Command not found. (Refer to help for a list of available options)");
        break;
    }
    return 0;
}
