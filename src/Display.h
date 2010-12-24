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

#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

/**
  * @brief Setup all display related memory buffer and glut framework.
  */
int setupDisplay(int argc, char** argv);

int cleanupDisplay();

/**
  * @brief Display a [len] byte sprite contained into [spriteData] at ([X], [Y]).
  * TECHNICAL DESCRIPTION TODO
  * @return 1 if any pixel has been erase, 0 Otherwise.
  */
int drawSprite(unsigned char X, unsigned char Y,const char* const spriteData, unsigned char len);

void render();

/**
  * @brief Clear screen
  * @return 1 if any pixel has been erase, 0 Otherwise.
  */
int clearScreen();

#endif /** DISPLAY_HEADER **/
