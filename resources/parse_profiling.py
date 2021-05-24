import ast
import re

REGEX = '^(?P<real>\d+\.\d+) real,	(?P<user>\d+\.\d+) user,	(?P<sys>\d+\.\d+) sys,	(?P<cpu>\d+)% CPU,	(?P<maxmem>\d+)k max mem,	(?P<Mpagefaults>\d+) major pagefaults,	(?P<mpagefaults>\d+) minor pagefaults'
regex = re.compile(REGEX)
groups = list(regex.groupindex)

print('-'*20+'\ncpython profiling\n'+'-'*20)
with open('cpython.profiling.txt') as f:
    total = {group:0 for group in groups}
    lines = f.readlines()
    for line in lines:
        match = regex.match(line)
        for group in groups:
            total[group] += ast.literal_eval(match.group(group))

    print({k:round(v/len(lines),2) for k,v in total.items()})

print('-'*20+'\ncpp profiling\n'+'-'*20)
with open('cpp.profiling.txt') as f:
    total = {group:0 for group in groups}
    lines = f.readlines()
    for line in lines:
        match = regex.match(line)
        for group in groups:
            total[group] += ast.literal_eval(match.group(group))

    print({k:round(v/len(lines),2) for k,v in total.items()})