#include "Logs.h"
#include "Memory.h"
#include "CartridgeReader.h"

#ifdef WINDOWS
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#define IDLE_TIME 16

#define SCREEN_WIDTH 64
#define SCREEN_HEIGTH 32

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	for(int X=0; X<SCREEN_WIDTH; ++X)
		for(int Y=0; Y< SCREEN_HEIGTH; ++Y)
			if(screen[i][j] == 1)
			{   
				glPushMatrix();
				glTranslated(j,i,0);
				glutSolidCube(1);
				glPopMatrix();
			}   
*/
	glutSwapBuffers();
}

void CPUTick(int) {
	addEntry(LOW_LEVEL_OPERATION, "CPU tick ****");


	glutTimerFunc(IDLE_TIME, CPUTick, 0);
}

void setupGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Chip8 emu");

}

int main(int argc, char** argv) {
	setupLogs(1, LOW_LEVEL_OPERATION, DEFAULT_OUTPUT_FILENAME);
	setupMemory();
	setupGlut(argc, argv);


	glutMainLoop();

	cleanupMemory();
	closeLogs();
	return 0;
}
