/*	This file is part of C8E.
 *       
 *       C8E is free software: you can redistribute it and/or modify
 *       it under the terms of the GNU General Public License as published by
 *       the Free Software Foundation, either version 3 of the License, or
 *       (at your option) any later version.
 *       
 *       C8E is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *              GNU General Public License for more details.
 *       
 *              You should have received a copy of the GNU General Public License
 *              along with C8E.  If not, see <http://www.gnu.org/licenses/>. 
 *
 *		Author : Maxime Gaudin
 */

/**
 * @file Display.h
 * @brief Define all functions, variables and defines for display management.
 * @version 0.1
 * @date December 12, 2010
 * @author Maxime Gaudin
 */

#include "Display.h"

#include <string.h>
#include <stdlib.h>
#ifdef WINDOWS
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "Logs.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGTH 32

#define DISPLAY_IDLE_TIME 16

static bool* bitmap;

int setupDisplay(int argc, char** argv) {
	bitmap = (bool*)calloc(SCREEN_WIDTH * SCREEN_HEIGTH, sizeof(bool));
	if(bitmap == NULL) return 1;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Chip8 emu");

	return 0;
}

int cleanupDisplay() {
	free(bitmap);

	return 0;
}

void render(int) {
	addEntry(LOW_LEVEL_OPERATION, "Dessin !");
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i=0; i<SCREEN_HEIGTH * SCREEN_WIDTH; ++i)
			if(bitmap[i])
			{   
				glPushMatrix();
				glTranslated(i % SCREEN_WIDTH,i / SCREEN_WIDTH, 0);
				glutSolidCube(1);
				glPopMatrix();
			}

	glutSwapBuffers();
	glutTimerFunc(DISPLAY_IDLE_TIME, render, 0);
}

int clearScreen() {
	return (bitmap == memset(bitmap, false, SCREEN_WIDTH * SCREEN_HEIGTH)) ? 0 : 1;
}
