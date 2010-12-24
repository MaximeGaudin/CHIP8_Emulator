#ifdef WINDOWS
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <stdlib.h>

#include "Logs.h"
#include "Memory.h"
#include "CartridgeReader.h"
#include "Display.h"
#include "CPU.h"

void printUsage() {
    printf("C8E - Chip8 Emulator ***********\n");
    printf("***** Usage :\n");
    printf("***** ./C8E ROM_PATH\n");
    printf("********************************\n");

    exit(0);
}

int main(int argc, char** argv) {
    unsigned char programBuffer[512];
    int len;
    if(argc != 2) printUsage();

    setupLogs(1, LOW_LEVEL_OPERATION, DEFAULT_OUTPUT_FILENAME);
    setupMemory();
    setupDisplay(argc, argv);

    len = readCartridge(argv[1], programBuffer);
    write(DATA_SPACE_START, programBuffer, len);

    /* CPUTick(0); */

	setupCPU();

    glutMainLoop();

	cleanupCPU();
    cleanupDisplay();
    cleanupMemory();
    closeLogs();
    return 0;
}
