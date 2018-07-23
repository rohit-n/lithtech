#ifndef __lib_dynres_h__
#define __lib_dynres_h__
#include <cinttypes>
uint32_t LoadString(void *h, int id, char* buff, int len);
uint32_t GetStringSize(void *h, int id);

void setup_string_tables(void);
void setup_cursors(void);
#endif
