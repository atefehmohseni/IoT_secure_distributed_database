import ast
import re

# to actually run the profiling, use something like:
# for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./pypy.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done

REGEX = '^(?P<real>\d+\.\d+) real,	(?P<user>\d+\.\d+) user,	(?P<sys>\d+\.\d+) sys,	(?P<cpu>\d+)% CPU,	(?P<maxmem>\d+)k max mem,	(?P<Mpagefaults>\d+) major pagefaults,	(?P<mpagefaults>\d+) minor pagefaults'
regex = re.compile(REGEX)
groups = list(regex.groupindex)

def parse_profile(filename):
    print('-'*20+f'\n{filename}\n'+'-'*20)
    with open(filename, 'r') as f:
        total = {group:0 for group in groups}
        lines = f.readlines()
        for line in lines:
            match = regex.match(line)
            for group in groups:
                total[group] += ast.literal_eval(match.group(group))

        print({k:round(v/len(lines),2) for k,v in total.items()})

for filename in ['profiling_data/cpp.write.profile', 'profiling_data/cpython.write.profile', 'profiling_data/pypy.write.profile',
                 'profiling_data/cpp.read.profile', 'profiling_data/cpython.read.profile', 'profiling_data/pypy.read.profile',
                 'profiling_data/cpp.delete.profile', 'profiling_data/cpython.delete.profile', 'profiling_data/pypy.delete.profile']:
    parse_profile(filename)