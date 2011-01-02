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

static unsigned char* bitmap;

/**
  * @brief Rendering function : Translation pixel information from meory space to the screen space
  */
static void render();

/**
  * @brief Recomputation  in case of display resizing.
  */
static void reshape(int width, int height);

int setupDisplay(int argc, char** argv) {
    bitmap = (unsigned char*)calloc(SCREEN_WIDTH * SCREEN_HEIGTH, sizeof(unsigned char));
    if(bitmap == NULL) return 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH * SCREEN_RATIO, SCREEN_HEIGTH * SCREEN_RATIO);
    glutCreateWindow("Chip8 emu");

    glutReshapeFunc(reshape);
    glutDisplayFunc(render);

    return 0;
}

int cleanupDisplay() {
    free(bitmap);

    return 0;
}

int clearScreen() {
    return (bitmap == memset(bitmap, 0, SCREEN_WIDTH * SCREEN_HEIGTH)) ? 0 : 1;
}

static void reshape(int width, int height) {
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        45,
        (float)(width)/(float)(height),
        0.1,
        100
    );
    glMatrixMode(GL_MODELVIEW);
}

static void render() {
    int i = 0;

    addEntry(LOW_LEVEL_OPERATION, "Drawing ...");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,-12,0,0,0,0,1,0);

    for(i=0; i<SCREEN_HEIGTH * SCREEN_WIDTH; ++i)
        if(bitmap[i]) {
            glPushMatrix();
            glTranslated(SCREEN_RATIO * (i % SCREEN_WIDTH), SCREEN_RATIO * (i / SCREEN_WIDTH), 0);
            glScaled(2, 1, 0);
            glutSolidCube(SCREEN_RATIO);
            glPopMatrix();
        }

    glutSwapBuffers();
    addEntry(LOW_LEVEL_OPERATION, "Drawing done.");

    glutPostRedisplay();
}
