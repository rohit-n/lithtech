#!/usr/bin/python3

from sys import argv

includes = []
str_table = []
text = []
defs = []


def parseRC(rcFile):
    with open(argv[1], 'r') as f:
        cur_lst = None
        str_id = None
        txt = None
        for l in f.readlines():
            if l.lower().startswith('#include'):
                n = l.split('"')
                includes.append(n[1].replace('\\', '/'))
            if 'stringtable' in l.lower():
                cur_lst = str_table
            if 'end' in l.lower():
                cur_lst = None
            if l.startswith(' ') and cur_lst is not None:
                n = l.strip('\n').split('"')
                if str_id is None:
                    str_id = n[0].strip()
                if len(n) is 1:
                    continue
                txt = '"'.join(n[1:-1])
                cur_lst.append((str_id, txt))
                str_id = None
                txt = None


def parseH(hFile):
    try:
        with open(hFile, 'r') as h:
            for l in h.readlines():
                defs.append(l.strip('\n'))
    except Exception:
        pass


parseRC(argv[1])

base = '/'.join(argv[1].split('/')[:-1])
# fetching includes and dropping them directly into the generated file
for i in includes[:]:
    if '.h' in i:
        print('including: {0}'.format(base + '/' + i))
        parseH(base + '/' + i)
    if '.rc' in i.lower():
        print('including: {0}'.format(base + '/' + i))
        parseRC(base + '/' + i)


with open(argv[1].split('/')[-1] + '.cpp', 'w') as o:
    o.write('''/*
  my template c++ file which implements the internal resource
  lookup and storage
*/

#include "dynres.h"
#include <string>
#include <unordered_map>
#include <cinttypes>
''')
    for i in defs:
        o.write('{0}'.format(i)+'\n')
    o.write('''

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
