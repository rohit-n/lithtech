#!/usr/bin/python3

import sys

logs = []
with open(sys.argv[1], 'r') as log:
    for l in log.readlines():
        if l[:-1] in logs:
            continue
        logs.append(l[:-1])

counts = {
    'Pass': 0,
    'Fail': 0,
    'warning': 0,
    'undefined reference': 0
}
mins = {
    'Pass': int(sys.argv[2]),
    'Fail': int(sys.argv[3]),
    'warning': int(sys.argv[4]),
    'undefined reference': int(sys.argv[5])
}
client = []
not_seen = True
for l in logs:
    if not_seen and ('EXE_Lithtech' in l or 'error:' in l):
        client.append(l)
    if l.startswith('make:') and 'EXE_Lithtech' in l:
        not_seen = False
    for k in counts.keys():
        if k in l:
            counts[k] += 1

if 'Fail EXE_Lithtech' in logs:
    print('\n'.join(client))

fmt = 'Pass:  {Pass}\nFail:  {Fail}\n'
fmt += 'Warn:  {warning}\nUnDef: {undefined reference}'
print(fmt.format(**counts))

if mins['Pass'] > counts['Pass']:
    print('component passes has gone down')
    sys.exit(1)

for k in ['Fail', 'warning', 'undefined reference']:
    if mins[k] < counts[k]:
        print('{0} parts have gone above known limits'.format(k))
        sys.exit(1)


