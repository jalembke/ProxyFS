# DEFUSE

Source code for Delayed Exploration File Systems in User Space (DEFUSE).  A fully user level interface for user space file systems.  Using LD_PRELOAD, a small kernel driver, and existing kernel interfaces provides high speed access to file systems implemented in user space without context switching to the kernel as is done with FUSE.

White Paper: https://www.cs.purdue.edu/homes/lembkej/papers/DEFUSE.pdf

## Repository Organization

bopfs_module - kernel module implementing bypassed open.  A feature used by DEFUSE to skip all access and lookup calls done by the kernel during the processing of an 'open' syscall.  A file descriptor opened from bopfs cannot be used for any I/O operations.  Meta operations (lseek, fcntl, etc.) are supported.

lddefuse - library to be used with LD_PRELOAD to intercept I/O system calls (open, close, read, write, etc).  When used intercepted system calls are sent directly to the user space file system.  Currently client file systems must be hard coded into lddefuse though an implementation of the FileSystemWrapper class.  Example implementations are given within the lddefuse directory.  Future goal is for lddefuse to dynamically load the user space file system library when needed based on information in exeuction environment or mount points.

usfs_wrap - implementation of loadable libraries to be used when lddefuse supports dynamic user space library loading.

data - test results and gnuplot files

fuse - standard FUSE file system drivers taken from https://github.com/libfuse/libfuse/tree/master/example

test - test scripts used for verification and benchmarking

### Deprecated

defuse_module - an early implementation of the bopfs module.  It is no longer used and included for reference only.
