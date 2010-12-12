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
  * @brief Memory.c header : Define all functions, variables and defines for memory management.
  * @version 0.1
  * @date December 12, 2010
  */

///@brief Specifies the memory address where memory starts (0x0, what a surprise isn't it ??)
#define RESERVED_MEMORY_START 0x0
/// @brief ...
#define RESERVED_MEMORY_STOP 0x200

/// @brief ...
#define DATA_SPACE_START 0x200
/// @brief ...
#define DATA_SPACE_STOP 0xFFF

/// @brief ...
#define MAX_REGISTERS 0xF

/* Shared memory ============================================ */
/// @brief Address register
static short I; 

/// @brief Delay register - Decremented every 17 ms (60Hz)
static char delay;

/// @brief Sound register - Decremented every 17 ms (60Hz)
static char sound;

/// @brief General purpose registers
static char* registers; 

static char* memory;
/* ========================================================== */

/**
  * @brief Initialize memory to 0
  */
int setupMemory();

/**
  * @brief write [len] bytes from [data] into memory at adress [addr]
  * @param [in] addr : Address where data will be written
  * @param [in] data : Pointer to data buffer
  * @param [in] len : Number of byte written
  * @return : 0 if success, 1 otherwise.
  */
int write(unsigned short addr, char* const data, unsigned int len);

/**
  * @brief Read [len] bytes of data from address [addr] to buffer
  * @param [in] addr : Address where rea
  * @param [in] len : Number of bytes read
  * @param [out] buffer : Pointer to the data buffer
  */
int read(short addr, unsigned short len, char* const buffer);
