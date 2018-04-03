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
#include <cinttypes>
#include <utility>
#include <algorithm>
#include <vector>
''')
    for i in defs:
        o.write('{0}'.format(i)+'\n')
    o.write('''

std::vector<std::pair<uint32_t,const char*>> str_tab {
''')
    for x in str_table:
        o.write('   std::make_pair({0},"{1}"),'.format(x[0], x[1]))
    o.write('''
    std::make_pair(0,"LithTech")
};

extern "C" {
  const char* LoadString(uint32_t id)
  {
    auto res = std::find_if(str_tab.begin(),
                            str_tab.end(),
                            [id](std::pair<uint32_t, const char*> x){
                                return (x.first == id);
                            });
    if(res != str_tab.end())
        return res->second;
    else
        return nullptr;
  }
}

void setup_cursors() { }

void setup_string_tables() {
    bool c = false;
    for(auto&& p : str_tab)
        c = (LoadString(p.first) == p.second);
}
''')
