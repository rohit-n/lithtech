#!/usr/bin/python3

import sys
import os

logs = []
with open(sys.argv[1], 'r') as log:
    for l in log.readlines():
        if l[:-1] in logs:
            continue
        logs.append(l[:-1])

counts = {
    'Pass ': 0,
    'Fail ': 0,
    'warning': 0,
    'undefined reference': 0
}

errs = []
warns = []
comp_fail = []
for l in logs:
    if 'warning:' in l:
        warns.append(l)
    if 'error:' in l:
        errs.append(l)
    if l.startswith('Fail '):
        comp_fail.append(l)
    for k in counts.keys():
        if k in l:
            counts[k] += 1

warns = list(set(warns[:]))
warns.sort()

errs = list(set(errs[:]))
errs.sort()


def summary(counts, warns):
    fmt = 'Pass:  {Pass }\nFail:  {Fail }\n'
    fmt += "Warn:  {warning}\nUnDef: {undefined reference}"
    print(fmt.format(**counts))
    print('warns {0} vs counts {1}'.format(len(warns), counts['warning']))


must_pass = [
    'EXE_',
    'DLL_',
    'Test_',
    'LIB_',
    'NOLF2_'
]
failed = False
for part in must_pass:
    lookup = 'Fail ' + part
    for f in comp_fail:
        if lookup in f:
            failed = True
            break
    if failed:
        break

if failed:
    print('\n'.join(warns))
    print('\n'.join(errs))
    summary(counts, warns)
    p = f.split(' ')[-1]
    print("critical parts didn't build, check build log for: %s" % p)
    os.system('../tests/upload_logs.sh')
    sys.exit(1)

summary(counts, warns)
