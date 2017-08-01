#!/usr/bin/python3

import sys
import smtplib
from email.mime.text import MIMEText

logs = []
with open(sys.argv[1], 'r') as log:
    logs = set(log.readlines())

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
for l in logs:
    if 'EXE_Lithtech' in l:
        client.append(l[:-1])
    for k in counts.keys():
        if k in l:
            counts[k] += 1

fmt = 'Pass:  {Pass}\nFail:  {Fail}\n'
fmt += 'Warn:  {warning}\nUnDef: {undefined reference}'
print(fmt.format(**counts))

mime = MIMEText('\n'.join(client))
mime['Subject'] = 'Lithtech client build - Travis'
mime['From'] = 'no-reply@example.com'
mime['To'] = 'rk.katana.steel@gmail.com'

s = smtplib.SMTP('localhost')
s.send_message(mime)
s.quit()

if mins['Pass'] > counts['Pass']:
    print('component passes has gone down')
    sys.exit(1)

for k in ['Fail', 'warning', 'undefined reference']:
    if mins[k] < counts[k]:
        print('{0} parts have gone above known limits'.format(k))
        sys.exit(1)


