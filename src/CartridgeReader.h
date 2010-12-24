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
 * @file CartridgeReader.h
 * @brief Define all functions, variables and defines for cartridge management.
 * @version 0.1
 * @date December 12, 2010
 * @author Maxime Gaudin
 */

#ifndef CARTRIDGE_READER_HEADER
#define CARTRIDGE_READER_HEADER

/**
  * @brief Provide a pointer to the cardridge data
  * @param [in] filename Point the file to load into memory
  * @param [out] data Buffer that eventually receive the cardridge data. It must be initialized and big enougth.
  * @return The number of bytes read if the file exists, -1 otherwise.
  */
int readCartridge(const char* const filename, unsigned char* data);

#endif /** CARTRIDGE_READER_HEADER **/
