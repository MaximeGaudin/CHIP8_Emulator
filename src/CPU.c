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
 * @file CPU.c
 * @brief
 * @version 0.1
 * @date December 13, 2010
 * @author Maxime Gaudin
 */

#include "CPU.h"
#include "Memory.h"
#include "Logs.h"

/// @brief Address register
static unsigned short I; 

/// @brief Delay register - Decremented every 17 ms (60Hz)
static unsigned char delay;

/// @brief Sound register - Decremented every 17 ms (60Hz)
static unsigned char sound;

/// @brief General purpose registers
static unsigned char* registers; 

/// @brief The program counter register : Specifies the currently executing address
static unsigned short pc;

/// @brief The stack pointer : Point the upmost level of stack
static unsigned char sp;

/// @brief Contains return address of subroutines
static unsigned short* stack;

int setupCPU() {
	addEntry(LOW_LEVEL_OPERATION, "CPU initialization ...");
	
	I = delay = sound = sp = 0;
	pc = DATA_SPACE_START;

	registers = (unsigned char*)calloc(MAX_REGISTERS, sizeof(unsigned char));
	if(registers == NULL) return 1;

	stack = (unsigned char*)calloc(MAX_STACK_SIZE, sizeof(unsigned char));
	if(stack == NULL) return 1;

	addEntry(LOW_LEVEL_OPERATION, "CPU initialized.");

	return 0;
}

void cleanupCPU() {
	addEntry(LOW_LEVEL_OPERATION, "CPU  cleanup.");

	free(registers);
	free(stack);
}
