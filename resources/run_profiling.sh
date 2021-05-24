#!/bin/bash

# write profiling
for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./profiling_data/pypy.write.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done
for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./profiling_data/cpython.write.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" python3 client.py); done
for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./profiling_data/cpp.write.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" ../build/client); done

# read profiling
for i in {1..10}; do _=$(cat ../test/read_testcase.txt | /usr/bin/time -o ./profiling_data/pypy.read.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done
for i in {1..10}; do _=$(cat ../test/read_testcase.txt | /usr/bin/time -o ./profiling_data/cpython.read.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" python3 client.py); done
for i in {1..10}; do _=$(cat ../test/read_testcase.txt | /usr/bin/time -o ./profiling_data/cpp.write.read.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" ../build/client); done

# delete profiling
for i in {1..10}; do _=$(cat ../test/delete_testcase.txt | /usr/bin/time -o ./profiling_data/pypy.delete.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done
for i in {1..10}; do _=$(cat ../test/delete_testcase.txt | /usr/bin/time -o ./profiling_data/cpython.delete.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" python3 client.py); done
for i in {1..10}; do _=$(cat ../test/delete_testcase.txt | /usr/bin/time -o ./profiling_data/cpp.delete.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" ../build/client); done

# syscalls (just for the write, no need to repeat)
cat ../test/write_testcase.txt | strace -c -o ./profiling_data/pypy.syscalls.write.profiling.txt pypy3 client.py
cat ../test/write_testcase.txt | strace -c -o ./profiling_data/cpython.syscalls.write.profiling.txt python3 client.py
cat ../test/write_testcase.txt | strace -c -o ./profiling_data/cpp.syscalls.write.profiling.txt ../build/client

