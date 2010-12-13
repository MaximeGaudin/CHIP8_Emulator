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

#include "Memory.h"

#include <stdlib.h>
#include <string.h>

/// @brief Array representing the RAM.
static unsigned char* memory;

int setupMemory() {
	memory = (unsigned char*)calloc(DATA_SPACE_STOP, sizeof(unsigned char));	
	if(memory == NULL) return 1;

	return 0;
}


void cleanupMemory() {
	free(memory);
}

int write(unsigned short addr, char* const data, unsigned int len) {
	if(addr + len < DATA_SPACE_STOP) {
		memcpy(memory + addr, data, len);
		return 0;
	}

	return 1;
}

int read(short addr, unsigned short len, char* const buffer) {
	if(addr + len < DATA_SPACE_STOP) {
		memcpy(buffer, memory + addr, len);
		return 0;
	}

	return 1;
}
