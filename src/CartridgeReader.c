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
 * @file Memory.c
 * @brief Define all functions, variables and defines for memory management.
 * @version 0.1
 * @date December 12, 2010
 * @author Maxime Gaudin
 */

#include "CartridgeReader.h"
#include <stdio.h>

int readCartridge(const char* const filename, unsigned char* data) {
    FILE* cartridge =fopen (filename,"r");
    int i = 0;

    if (cartridge==NULL) return -1;
    else {
        do {
            data[i] = (unsigned char)getc (cartridge);
        } while ((signed char)data[i++] != EOF);
        fclose (cartridge);
    }

    return i;
}
