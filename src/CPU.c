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

/**
  * @brief Clear screen, i.e. put every pixel to low state (black)
  *
  */
inline static void opCLS() {

}

/**
  * @brief Return from sub routine.
  * Thus, the CPU set the pc to the address contained in stack[sp] and decrement sp by 1.
  * Mnemonic = RET
  * Opcode : 0x00EE
  */
inline static void opRET() {
	addEntry(DISASSEMBLY, "RET");
	pc = stack[sp--];
}

/**
  * @brief Jump unconditionnaly to [addr], 
  * i.e. set pc to addr - 2 (because it will be incremented before the next CPU cycle )
  * Mnemonic = JP
  * opCode : 0x1NNN
  * param [in] addr Address of the nezt intruction to execute.
  */
inline static void opJP(unsigned short addr) {
	pc = addr - 2;	
}

/**
  * @brief Call the subroutine at [addr].
  * i.e. pc is stored in the stack, set to [addr] - 2 and the stack pointer is incremented.
  * Mnemonic = CALL
  * opCode = 0x2NNN
  * param [in] address Address of the subroutine to call.
  */
inline static void opCALL(unsigned short addr) {
	
}

/**
  * @brief Skip if equal : Skip next instruction if V[X] == kk
  * Mnemonic = SE
  * opCode = 0x3Xkk
  * param [in] X Index of the register to compare
  * param [in] kk Value to compare with
*/
inline static void opSE(unsigned char X, unsigned char kk) {
	if(registers[X] == kk) pc += 2;
}

/**
  * @brief Skip if equal : Skip next instruction if V[X] == V[Y]
  * Mnemonic = SE
  * opCode = 0x5XY0
  * param [in] X Index of the first register to compare
  * param [in] Y Index of the second register to compare
  */
inline static void opSE2(unsigned char X, unsigned char Y) {
	if(registers[X] == registers[Y]) pc += 2;
}

/**
  * @brief Skip if not equal : Skip next instruction if V[X] != kk
  * Mnemonic = SNE
  * opCode = 0x4Xkk
  * param [in] X Index of the register to compare
  * param [in] kk value Value to compare with
*/
inline static void opSNE(unsigned char X, unsigned char kk) {
	if(registers[X] =! kk) pc += 2;
}

/**
  * Move value : Put value kk into register X.
  * Mnemonic = MOV
  * opCode = 0x6Xkk
  * param [in] X Index of the storage register
  * param [in] kk Value to store
  */
inline static void opMOV(unsigned char X, unsigned char kk) {
	registers[X] = kk;
}

/**
  * Move value : Put value from register Y into register X.
  * Mnemonic = MOV
  * opCode = 0x8XY0
  * param [in] X Index of the destination register
  * param [in] Y Index of the source register
  */
inline static void opMOV2(unsigned char X, unsigned char Y) {
	registers[X] = registers[Y];
}

/**
  * Add value : Put value kk + V[X] into register X.
  * Mnemonic = ADD
  * opCode = 0x7Xkk
  * param [in] X Index of the storage register
  * param [in] kk Value to add
  */
inline static void opADD(unsigned char X, unsigned char kk) {
	registers[X] += kk;
}


/**
  * Add operator : Put value V[X] + V[Y] into register X.
  * If an overflow happens, V[0xF] = 1, v[0xF] = 0 Otherwise. 
  * Mnemonic = ADD
  * opCode = 0x8XY4
  * param [in] X Index of the destination register
  * param [in] Y Index of the source register
  */
inline static void opADD2(unsigned char X, unsigned char Y) {
	registers[0xF] = ((int)registers[X] + (int)registers[Y] > 255) ? 1 : 0;
	registers[X] += registers[Y];
}

/**
  * Sub operator : Put value V[X] - V[Y] into register X.
  * If V[X] > V[Y], V[0xF] = 1, v[0xF] = 0 Otherwise. 
  * Mnemonic = SUB
  * opCode = 0x8XY5
  * param [in] X Index of the destination register
  * param [in] Y Index of the source register
  */
inline static void opSUB(unsigned char X, unsigned char Y) {
	registers[0xF] = (registers[X] > registers[Y]) ? 1 : 0;
	registers[X] -= registers[Y];
}

/**
  * Opposite Sub operator : Put value V[Y] - V[X] into register X.
  * If V[Y] > V[X], V[0xF] = 1, v[0xF] = 0 Otherwise. 
  * Mnemonic = SUBN
  * opCode = 0x8XY7
  * param [in] X Index of the destination register
  * param [in] Y Index of the source register
  */
inline static void opSUBN(unsigned char X, unsigned char Y) {
	registers[0xF] = (registers[Y] > registers[X]) ? 1 : 0;
	registers[X] = registers[Y] - registers[X];
}

/**
  * SHR operator : Shift register X by 1 to the right.
  * If the least significant bit of V[X] is 1, V[0xF] = 1. 0 otherwise.
  * In other words, if V[X] is odd, V[0xF] = 1.
  * Mnemonic = SHR
  * opCode = 0x8XY6
  * param [in] X Index of the destination register
  */
inline static void opSHR(unsigned char X) {
	registers[0xF] = (registers[X] % 2);
	registers[X] >> 1;
}

/**
  * SHR operator : Shift register X by 1 to the left.
  * If the most significant bit of V[X] is 1, V[0xF] = 1. 0 otherwise.
  * In other words, if V[X] >= 128, V[0xF] = 1.
  * Mnemonic = SHL
  * opCode = 0x8XYE
  * param [in] X Index of the destination register
  */
inline static void opSHL(unsigned char X) {
	registers[0xF] = (registers[X] >= 128) ? 1 : 0;
	registers[X] << 1;
}

/**
  * Or binary operator : Put value V[X] | V[Y] into register X.
  * Mnemonic = OR
  * opCode = 0x8XY1
  * param [in] X Index of the destination register
  * param [in] Y Index of the source register
  */
inline static void opOR(unsigned char X, unsigned char Y) {
	registers[X] |= registers[Y];
}


/**
  * And binary operator : Put value V[X] & V[Y] into register X.
  * Mnemonic = AND
  * opCode = 0x8XY2
  * param [in] X Index of the destination register
  * param [in] Y Index of the source register
  */
inline static void opAND(unsigned char X, unsigned char Y) {
	registers[X] &= registers[Y];
}

/**
  * Xor binary operator : Put value V[X] ^ V[Y] into register X.
  * Mnemonic = XOR
  * opCode = 0x8XY3
  * param [in] X Index of the destination register
  * param [in] Y Index of the source register
  */
inline static void opXOR(unsigned char X, unsigned char Y) {
	registers[X] ^= registers[Y];
}


void tick() {
	// WHILE SMTH
	handleOpCode();
}

void handleOpCode() {
	unsigned short opCode; read(pc, 2, (char*)(&opCode));
	unsigned char byte1, byte2; 
	byte1 = 0x01 & opCode; byte2 = 0x10 & opCode;

	if(opCode == 0x00E0) { opCLS(); }
	else if(opCode == 0x00EE) { opRET(); }

	else if(opCode & 0x1000 == 0x1000) { opJP(opCode & 0x0111); }
	else if(opCode & 0x1000 == 0x2000) { opCALL(opCode  & 0x0111); }
	else if(opCode & 0x1000 == 0x3000) { opSE(opCode & 0x0100, opCode & 0x0011); }
	else if(opCode & 0x1000 == 0x4000) { opSNE(opCode & 0x0100, opCode & 0x0011); }
	else if(opCode & 0x1001 == 0x5000) { opSE2(opCode & 0x0100, opCode & 0x0010); }

	
}

