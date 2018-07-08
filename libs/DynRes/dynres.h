#ifndef __lib_dynres_h__
#define __lib_dynres_h__
/*
    2018 (c) Rene 'Katana Steel' Kjellerup, distributed under the terms of
    the GNU General Public Licenses version 3 or later for details see:
    http://www.gnu.org/licenses/gpl.html
*/
#include <cinttypes>
uint32_t LoadString(void *h, int id, char* buff, int len);
uint32_t GetStringSize(void *h, int id);

void setup_string_tables(void);
void setup_cursors(void);
#endif
