#ifdef WINDOWS
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "Logs.h"
#include "Memory.h"
#include "CartridgeReader.h"
#include "Display.h"

#define IDLE_TIME 16

int main(int argc, char** argv) {
	setupLogs(1, LOW_LEVEL_OPERATION, DEFAULT_OUTPUT_FILENAME);
	setupMemory();
	setupDisplay(argc, argv);

	glutDisplayFunc(render);
	//glutMotionFunc(CPUTick);

	glutMainLoop();

	cleanupDisplay();
	cleanupMemory();
	closeLogs();
	return 0;
}
