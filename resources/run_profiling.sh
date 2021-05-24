#!/bin/bash

# write profiling
for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./profiling_data/pypy.write.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done
for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./profiling_data/cpython.write.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" python3 client.py); done
for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./profiling_data/cpp.write.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" ../build/client); done

# read profiling
for i in {1..10}; do _=$(cat ../test/read_testcase.txt | /usr/bin/time -o ./profiling_data/pypy.read.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done
for i in {1..10}; do _=$(cat ../test/read_testcase.txt | /usr/bin/time -o ./profiling_data/cpython.read.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" python3 client.py); done
for i in {1..10}; do _=$(cat ../test/read_testcase.txt | /usr/bin/time -o ./profiling_data/cpp.read.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" ../build/client); done

# delete profiling
for i in {1..10}; do _=$(cat ../test/delete_testcase.txt | /usr/bin/time -o ./profiling_data/pypy.delete.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done
for i in {1..10}; do _=$(cat ../test/delete_testcase.txt | /usr/bin/time -o ./profiling_data/cpython.delete.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" python3 client.py); done
for i in {1..10}; do _=$(cat ../test/delete_testcase.txt | /usr/bin/time -o ./profiling_data/cpp.delete.profile --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" ../build/client); done

# syscalls (just for the write, no need to repeat)
cat ../test/write_testcase.txt | strace -c -o ./profiling_data/pypy.syscalls.write.profile pypy3 client.py
cat ../test/write_testcase.txt | strace -c -o ./profiling_data/cpython.syscalls.write.profile python3 client.py
cat ../test/write_testcase.txt | strace -c -o ./profiling_data/cpp.syscalls.write.profile ../build/client

