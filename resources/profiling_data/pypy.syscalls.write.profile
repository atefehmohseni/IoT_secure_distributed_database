% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 28.98    0.009158          38       240           rt_sigaction
  6.57    0.002075          42        49           read
  6.52    0.002060          30        69           mmap
  5.74    0.001813          35        52           pread64
  5.56    0.001756          39        45        18 epoll_ctl
  5.53    0.001748          50        35         2 openat
  5.50    0.001739          53        33        23 newfstatat
  4.10    0.001295          35        37           close
  3.52    0.001113          38        29           mprotect
  3.03    0.000957          30        32           fcntl
  2.47    0.000782          36        22           fstat
  1.97    0.000623          57        11           futex
  1.94    0.000614          23        27           rt_sigprocmask
  1.85    0.000586          37        16           lstat
  1.59    0.000501          50        10           clone
  1.42    0.000450          41        11           readlinkat
  1.28    0.000405          37        11           getsockopt
  1.27    0.000400          57         7           munmap
  1.04    0.000329          55         6           brk
  1.04    0.000328          27        12        12 access
  0.84    0.000266          53         5           write
  0.78    0.000245          25        10         1 recvmsg
  0.68    0.000216          54         4           getpid
  0.51    0.000161          54         3         2 connect
  0.51    0.000160          80         2           epoll_create1
  0.49    0.000154         154         1           getsockname
  0.46    0.000144          48         3           socket
  0.37    0.000118          30         4           getuid
  0.35    0.000112          56         2           set_tid_address
  0.33    0.000105          53         2           lseek
  0.33    0.000104          52         2           prlimit64
  0.31    0.000098          49         2           statfs
  0.30    0.000094          24         4           sigaltstack
  0.25    0.000080          27         3           pipe2
  0.25    0.000079          40         2           getdents64
  0.25    0.000078          78         1           waitid
  0.23    0.000072          36         2           gettid
  0.19    0.000061          61         1           wait4
  0.19    0.000061          61         1           getgid
  0.19    0.000059          59         1           sendmsg
  0.18    0.000057          57         1           rt_sigreturn
  0.18    0.000056          28         2           umask
  0.15    0.000047          47         1           getpeername
  0.15    0.000046          23         2           set_robust_list
  0.14    0.000044          22         2           arch_prctl
  0.13    0.000041          21         2           sched_getaffinity
  0.13    0.000040          20         2           execve
  0.10    0.000032          16         2           uname
  0.10    0.000031          31         1           setsockopt
  0.03    0.000008           2         4         2 ioctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.031601                   828        60 total
