#include "dynres.h"

void __attribute__((constructor)) InitializeResourceSystem() {
    setup_string_tables();
    setup_cursors();
    return;
}
