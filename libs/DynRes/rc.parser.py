#!/usr/bin/python3

from sys import argv

includes = []
v=[]
with open(argv[1], 'r') as f:
    v = f.read().replace('\\', '/').split('\n')

for x in v[:]:
    if 'include' in x:
        includes.append(x)
        v.remove(x)

with open(argv[1].split('/')[-1] + '.cpp', 'w') as o:
    o.write('''/* 
  my template c++ file which implements the internal resource 
  lookup and storage
*/

#include "dynres.h"
''')
    for i in includes:
        o.write(i+'\n')
    o.write('''
#include <string>
#include <unordered_map>
#include <cinttypes>

static std::unordered_map<uint32_t, std::string> g_string_table;

void Add2StringTable(uint32_t id, const char* str)
{
    g_string_table[id] = std::string{str};
}


const char* LoadString(uint32_t id)
{
    auto res = g_string_table.find(id);
    if(res != g_string_table.end())
        return res->second.c_str();
    else
        return nullptr;
}

void setup_cursors() { }

void setup_string_tables() { // all discardable string table labels here
''')
    for l in v:
        if 'IDS' in l:
            x = l.split()
            o.write('    Add2StringTable({0}, {1});\n'.format(x[0], ' '.join(x[1:])))
    o.write('}\n')
