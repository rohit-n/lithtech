#!/usr/bin/python3

from sys import argv

includes = []
str_table = []
text = []
with open(argv[1], 'r') as f:
    cur_lst = None
    for l in f.readlines():
        if '#include' in l.lower():
            n = l.split('"')
            includes.append(n[1].replace('\\', '/'))
        if 'stringtable' in l.lower():
            cur_lst = str_table
        if 'end' in l.lower():
            cur_lst = None
        if l.startswith(' ') and cur_lst is not None:
            n = l.split('"')
            cur_lst.append((n[0].strip(), n[1]))


with open(argv[1].split('/')[-1] + '.cpp', 'w') as o:
    o.write('''/* 
  my template c++ file which implements the internal resource 
  lookup and storage
*/

#include "dynres.h"
''')
    for i in includes:
        o.write('#include "{0}"'.format(i)+'\n')
    o.write('''
#include <string>
#include <unordered_map>
#include <cinttypes>

static std::unordered_map<uint32_t, std::string> g_string_table;

void Add2StringTable(uint32_t id, const char* str)
{
    g_string_table[id] = std::string{str};
}

extern "C" {
const char* LoadString(uint32_t id)
{
    auto res = g_string_table.find(id);
    if(res != g_string_table.end())
        return res->second.c_str();
    else
        return nullptr;
}
}

void setup_cursors() { }

void setup_string_tables() { // all discardable string table labels here
''')
    for x in str_table:
            o.write('    Add2StringTable({0}, "{1}");\n'.format(x[0], x[1]))
    o.write('}\n')
