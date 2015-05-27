/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */
 
int le_init();
int le_loadexpr(char *expr, char **pmsg);
void le_eval(int cookie, char **pmsg);
double le_eval_double(int cookie, char **pmsg);
int    le_eval_integer(int cookie, char **pmsg);
int    le_eval_boolean(int cookie, char **pmsg);
void le_unref(int cookie);
void le_setvar(char *name, double value);
double le_getvar(char *name);
