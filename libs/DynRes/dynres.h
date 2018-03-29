#ifndef __lib_dynres_h__
#define __lib_dynres_h__
#include <cinttypes>
uint32_t LoadString(void *h, int id, char* buff, int len);

void setup_string_tables(void);
void setup_cursors(void);
#endif