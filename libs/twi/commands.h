/*
 * Copyright 2009 Anton Staaf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __twi_commands_h__
#define __twi_commands_h__

#include "libs/shell/shell.h"

extern const ShellCommand	shell_command_release   PROGMEM;
extern const ShellCommand	shell_command_master    PROGMEM;
extern const ShellCommand	shell_command_message   PROGMEM;
extern const ShellCommand	shell_command_twi       PROGMEM;

#endif //__twi_commands_h__
