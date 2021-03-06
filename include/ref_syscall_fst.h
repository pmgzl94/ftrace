/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#ifndef REF_SYSCALL_FST_
#define REF_SYSCALL_FST_

#include "ref_syscall.h"

const static struct ref_syscall ref_syscall_fst[435] = {
    {"restart_syscall", {}, 0},
    {"exit", {INT}, 1},
    {"fork", {}, 0},
    {"read", {INT, STRING, INT}, 3},
    {"write", {INT, STRING, INT}, 3},
    {"open", {STRING, FLAG, INT}, 3},
    {"close", {INT}, 1},
    {"waitpid", {INT, ADDR, INT}, 3},
    {"creat", {STRING, INT}, 2},
    {"link", {STRING, STRING}, 2},
    {"unlink", {STRING}, 1},
    {"execve", {STRING, ARRAY | STRING, ARRAY | STRING}, 3},
    {"chdir", {STRING}, 1},
    {"time", {STRUCT}, 1},
    {"mknod", {STRING, INT, INT}, 3},
    {"chmod", {STRING, STRUCT}, 2},
    {"lchownADDR", {STRING, INT, INT}, 3},
    {"undefined", {}, 0},
    {"stat", {STRING, STRUCT}, 2},
    {"lseek", {INT, STRUCT, INT}, 3},
    {"getpid", {}, 0},
    {"mount", {STRING, STRING, STRING, FLAG, ADDR}, 5},
    {"oldumount", {STRING}, 1},
    {"setuidADDR", {INT}, 1},
    {"getuidADDR", {}, 0},
    {"stime", {STRUCT}, 1},
    {"ptrace", {INT, INT, ADDR, ADDR}, 4},
    {"alarm", {INT}, 1},
    {"fstat", {INT, STRUCT}, 2},
    {"pause", {}, 0},
    {"utime", {STRING, STRUCT}, 2},
    {"undefined", {}, 0},
    {"undefined", {}, 0},
    {"access", {STRING, INT}, 2},
    {"nice", {INT}, 1},
    {"undefined", {}, 0},
    {"sync", {}, 0},
    {"kill", {INT, INT}, 2},
    {"rename", {STRING, STRING}, 2},
    {"mkdir", {STRING, INT}, 2},
    {"rmdir", {STRING}, 1},
    {"dup", {INT}, 1},
    {"pipe", {ARRAY | INT}, 1},
    {"times", {STRUCT}, 1},
    {"undefined", {}, 0},
    {"brk", {ADDR}, 1},
    {"setgidADDR", {INT}, 1},
    {"getgidADDR", {}, 0},
    {"signal", {INT, STRUCT}, 2},
    {"geteuidADDR", {}, 0},
    {"getegidADDR", {}, 0},
    {"acct", {STRING}, 1},
    {"umount", {STRING, FLAG}, 2},
    {"undefined", {}, 0},
    {"ioctl", {INT, INT, INT}, 3},
    {"fcntl", {INT, INT, INT}, 3},
    {"undefined", {}, 0},
    {"setpgid", {INT, INT}, 2},
    {"undefined", {}, 0},
    {"olduname", {STRUCT}, 1},
    {"umask", {INT}, 1},
    {"chroot", {STRING}, 1},
    {"ustat", {INT, STRUCT}, 2},
    {"dup2", {INT, INT}, 2},
    {"getppid", {}, 0},
    {"getpgrp", {}, 0},
    {"setsid", {}, 0},
    {"sigaction", {INT, STRUCT, STRUCT}, 3},
    {"sgetmask", {}, 0},
    {"ssetmask", {INT}, 1},
    {"setreuidADDR", {INT, INT}, 2},
    {"setregidADDR", {INT, INT}, 2},
    {"sigsuspend", {INT, INT, STRUCT}, 3},
    {"sigpending", {STRUCT}, 1},
    {"sethostname", {STRING, INT}, 2},
    {"setrlimit", {INT, STRUCT}, 2},
    {"old_getrlimit", {INT, STRUCT}, 2},
    {"getrusage", {INT, STRUCT}, 2},
    {"gettimeofday", {STRUCT, STRUCT}, 2},
    {"settimeofday", {STRUCT, STRUCT}, 2},
    {"getgroupsADDR", {INT, ADDR}, 2},
    {"setgroupsADDR", {INT, ADDR}, 2},
    {"old_select", {STRUCT}, 1},
    {"symlink", {STRING, STRING}, 2},
    {"lstat", {STRING, STRUCT}, 2},
    {"readlink", {STRING, STRING, INT}, 3},
    {"uselib", {STRING}, 1},
    {"swapon", {STRING, FLAG}, 2},
    {"reboot", {INT, INT, INT, ADDR}, 4},
    {"old_readdir", {INT, STRUCT, INT}, 3},
    {"old_mmap", {STRUCT}, 1},
    {"munmap", {ADDR, INT}, 2},
    {"truncate", {STRING, INT}, 2},
    {"ftruncate", {INT, INT}, 2},
    {"fchmod", {INT, STRUCT}, 2},
    {"fchownADDR", {INT, INT, INT}, 3},
    {"getpriority", {INT, INT}, 2},
    {"setpriority", {INT, INT, INT}, 3},
    {"undefined", {}, 0},
    {"statfs", {STRING, STRUCT}, 2},
    {"fstatfs", {INT, STRUCT}, 2},
    {"ioperm", {INT, INT, INT}, 3},
    {"socketcall", {INT, ADDR}, 2},
    {"syslog", {INT, STRING, INT}, 3},
    {"setitimer", {INT, STRUCT, STRUCT}, 3},
    {"getitimer", {INT, STRUCT}, 2},
    {"newstat", {STRING, STRUCT}, 2},
    {"newlstat", {STRING, STRUCT}, 2},
    {"newfstat", {INT, STRUCT}, 2},
    {"uname", {STRUCT}, 1},
    {"iopl", {INT, STRUCT}, 2},
    {"vhangup", {}, 0},
    {"undefined", {}, 0},
    {"vmFLAG6old", {STRUCT, STRUCT}, 2},
    {"wait4", {INT, ADDR, INT, STRUCT}, 4},
    {"swapoff", {STRING}, 1},
    {"sysinfo", {STRUCT}, 1},
    {"ipc", {}, 0},
    {"fsync", {INT}, 1},
    {"sigreturn", {STRUCT}, 1},
    {"clone", {INT, INT, INT, INT, STRUCT}, 5},
    {"setdomainname", {STRING, INT}, 2},
    {"newuname", {STRUCT}, 1},
    {"modify_ldt", {INT, ADDR, INT}, 3},
    {"adjtimex", {STRUCT}, 1},
    {"mprotect", {INT, INT, INT}, 3},
    {"sigprocmask", {FLAG, STRUCT, STRUCT}, 3},
    {"undefined", {}, 0},
    {"init_module", {ADDR, INT, STRING}, 3},
    {"delete_module", {STRING, FLAG}, 2},
    {"undefined", {}, 0},
    {"quotactl", {INT, STRING, STRUCT, ADDR}, 4},
    {"getpgid", {INT}, 1},
    {"fchdir", {INT}, 1},
    {"bdflush", {INT, INT}, 2},
    {"sysfs", {INT, INT, INT}, 3},
    {"personality", {INT}, 1},
    {"undefined", {}, 0},
    {"setfsuidADDR", {INT}, 1},
    {"setfsgidADDR", {INT}, 1},
    {"llseek", {INT, INT, INT, STRUCT, INT}, 5},
    {"getdents", {INT, STRUCT, INT}, 3},
    {"select", {INT, ADDR, ADDR, ADDR, STRUCT}, 5},
    {"flock", {INT, INT}, 2},
    {"msync", {INT, INT, FLAG}, 3},
    {"readv", {INT, STRUCT, INT}, 3},
    {"writev", {INT, STRUCT, INT}, 3},
    {"getsid", {INT}, 1},
    {"fdatasync", {INT}, 1},
    {"sysctl", {STRUCT}, 1},
    {"mlock", {INT, INT}, 2},
    {"munlock", {INT, INT}, 2},
    {"mlockall", {FLAG}, 1},
    {"munlockall", {}, 0},
    {"sched_setparam", {INT, STRUCT}, 2},
    {"sched_getparam", {INT, STRUCT}, 2},
    {"sched_setscheduler", {INT, INT, STRUCT}, 3},
    {"sched_getscheduler", {INT}, 1},
    {"sched_yield", {}, 0},
    {"sched_get_priority_max", {INT}, 1},
    {"sched_get_priority_min", {INT}, 1},
    {"sched_rr_get_interval", {INT, STRUCT}, 2},
    {"nanosleep", {STRUCT, STRUCT}, 2},
    {"mremap", {ADDR, INT, INT, FLAG, ADDR}, 5},
    {"setresuidADDR", {INT, INT, INT}, 3},
    {"getresuidADDR", {ADDR, ADDR, ADDR}, 3},
    {"vmFLAG6", {INT, INT, STRUCT}, 3},
    {"undefined", {}, 0},
    {"poll", {STRUCT, INT, INT}, 3},
    {"nfsservctl", {INT, STRUCT, ADDR}, 3},
    {"setresgidADDR", {INT, INT, INT}, 3},
    {"getresgidADDR", {ADDR, ADDR, ADDR}, 3},
    {"prctl", {INT, INT, INT, INT, INT}, 5},
    {"rt_sigreturn", {STRUCT}, 1},
    {"rt_sigaction", {INT, STRUCT, STRUCT, INT}, 4},
    {"rt_sigprocmask", {FLAG, STRUCT, STRUCT, INT}, 4},
    {"rt_sigpending", {STRUCT, INT}, 2},
    {"rt_sigtimedwait", {STRUCT, STRUCT, STRUCT, INT}, 4},
    {"rt_sigqueueinfo", {INT, INT, STRUCT}, 3},
    {"rt_sigsuspend", {STRUCT, INT}, 2},
    {"pread64", {INT, STRING, INT, STRUCT}, 4},
    {"pwrite64", {INT, STRING, INT, STRUCT}, 4},
    {"chownADDR", {STRING, INT, INT}, 3},
    {"getcwd", {STRING, INT}, 2},
    {"capget", {STRUCT, STRUCT}, 2},
    {"capset", {STRUCT, STRUCT}, 2},
    {"sigaltstack", {STRUCT, STRUCT, STRUCT}, 3},
    {"sendfile", {INT, INT, STRUCT, INT}, 4},
    {"undefined", {}, 0},
    {"undefined", {}, 0},
    {"vfork", {STRUCT}, 1},
    {"getrlimit", {INT, STRUCT}, 2},
    {"mmap_pgoff", {}, 0},
    {"truncate64", {STRING, STRUCT}, 2},
    {"ftruncate64", {INT, STRUCT}, 2},
    {"stat64", {STRING, STRUCT}, 2},
    {"lstat64", {STRING, STRUCT}, 2},
    {"fstat64", {INT, STRUCT}, 2},
    {"lchown", {STRING, INT, INT}, 3},
    {"getuid", {}, 0},
    {"getgid", {}, 0},
    {"geteuid", {}, 0},
    {"getegid", {}, 0},
    {"setreuid", {INT, INT}, 2},
    {"setregid", {INT, INT}, 2},
    {"getgroups", {INT, ADDR}, 2},
    {"setgroups", {INT, ADDR}, 2},
    {"fchown", {INT, INT, INT}, 3},
    {"setresuid", {INT, INT, INT}, 3},
    {"getresuid", {ADDR, ADDR, ADDR}, 3},
    {"setresgid", {INT, INT, INT}, 3},
    {"getresgid", {ADDR, ADDR, ADDR}, 3},
    {"chown", {STRING, INT, INT}, 3},
    {"setuid", {INT}, 1},
    {"setgid", {INT}, 1},
    {"setfsuid", {INT}, 1},
    {"setfsgid", {INT}, 1},
    {"pivot_root", {STRING, STRING}, 2},
    {"mincore", {INT, INT, STRING}, 3},
    {"madvise", {INT, INT, INT}, 3},
    {"getdents64", {INT, STRUCT, INT}, 3},
    {"fcntl64", {INT, INT, INT}, 3},
    {"undefined", {}, 0},
    {"undefined", {}, 0},
    {"gettid", {}, 0},
    {"readahead", {INT, STRUCT, INT}, 3},
    {"setxattr", {STRING, STRING, ADDR, INT, FLAG}, 5},
    {"lsetxattr", {STRING, STRING, ADDR, INT, FLAG}, 5},
    {"fsetxattr", {INT, STRING, ADDR, INT, FLAG}, 5},
    {"getxattr", {STRING, STRING, ADDR, INT}, 4},
    {"lgetxattr", {STRING, STRING, ADDR, INT}, 4},
    {"fgetxattr", {INT, STRING, ADDR, INT}, 4},
    {"listxattr", {STRING, STRING, INT}, 3},
    {"llistxattr", {STRING, STRING, INT}, 3},
    {"flistxattr", {INT, STRING, INT}, 3},
    {"removexattr", {STRING, STRING}, 2},
    {"lremovexattr", {STRING, STRING}, 2},
    {"fremovexattr", {INT, STRING}, 2},
    {"tkill", {INT, INT}, 2},
    {"sendfile64", {INT, INT, STRUCT, INT}, 4},
    {"futex", {}, 0},
    {"sched_setaffinity", {INT, INT, ADDR}, 3},
    {"sched_getaffinity", {INT, INT, ADDR}, 3},
    {"set_thread_area", {STRUCT}, 1},
    {"get_thread_area", {STRUCT}, 1},
    {"io_setup", {INT, STRUCT}, 2},
    {"io_destroy", {STRUCT}, 1},
    {"io_getevents", {STRUCT, INT, INT, STRUCT, STRUCT}, 5},
    {"io_submit", {STRUCT, INT, STRUCT}, 3},
    {"io_cancel", {STRUCT, STRUCT, STRUCT}, 3},
    {"fadvise64", {INT, STRUCT, INT, INT}, 4},
    {"undefined", {}, 0},
    {"exit_group", {INT}, 1},
    {"lookup_dcookie", {UNDEFINED, STRING, INT}, 3},
    {"epoll_create", {INT}, 1},
    {"epoll_ctl", {INT, INT, INT, STRUCT}, 4},
    {"epoll_wait", {INT, STRUCT, INT, INT}, 4},
    {"remap_file_pages", {INT, INT, INT, INT, FLAG}, 5},
    {"set_tid_address", {ADDR}, 1},
    {"timer_create", {STRUCT, STRUCT, STRUCT}, 3},
    {"timer_settime", {STRUCT, FLAG, STRUCT, STRUCT}, 4},
    {"timer_gettime", {STRUCT, STRUCT}, 2},
    {"timer_getoverrun", {STRUCT}, 1},
    {"timer_delete", {STRUCT}, 1},
    {"clock_settime", {STRUCT, STRUCT}, 2},
    {"clock_gettime", {STRUCT, STRUCT}, 2},
    {"clock_getres", {STRUCT, STRUCT}, 2},
    {"clock_nanosleep", {STRUCT, FLAG, STRUCT, STRUCT}, 4},
    {"statfs64", {STRING, INT, STRUCT}, 3},
    {"fstatfs64", {INT, INT, STRUCT}, 3},
    {"tgkill", {INT, INT, INT}, 3},
    {"utimes", {STRING, STRUCT}, 2},
    {"fadvise64_64", {INT, STRUCT, STRUCT, INT}, 4},
    {"undefined", {}, 0},
    {"mbind", {}, 0},
    {"get_mempolicy", {ADDR, ADDR, INT, ADDR, FLAG}, 5},
    {"set_mempolicy", {INT, ADDR, INT}, 3},
    {"mq_open", {STRING, FLAG, STRUCT, STRUCT}, 4},
    {"mq_unlink", {STRING}, 1},
    {"mq_timedsend", {STRUCT, STRING, INT, INT, STRUCT}, 5},
    {"mq_timedreceive", {STRUCT, STRING, INT, ADDR, STRUCT}, 5},
    {"mq_notify", {STRUCT, STRUCT}, 2},
    {"mq_getsetattr", {STRUCT, STRUCT, STRUCT}, 3},
    {"kexec_load", {INT, INT, STRUCT, FLAG}, 4},
    {"waitid", {INT, INT, STRUCT, INT, STRUCT}, 5},
    {"undefined", {}, 0},
    {"add_key", {STRUCT, STRING, ADDR, INT, STRUCT}, 5},
    {"request_key", {STRUCT, STRING, STRING, STRUCT}, 4},
    {"keyctl", {INT, INT, INT, INT, INT}, 5},
    {"ioprio_set", {INT, INT, INT}, 3},
    {"ioprio_get", {INT, INT}, 2},
    {"inotify_init", {}, 0},
    {"inotify_add_watch", {INT, STRING, UNDEFINED}, 3},
    {"inotify_rm_watch", {INT, UNDEFINED}, 2},
    {"migrate_pages", {INT, INT, ADDR, ADDR}, 4},
    {"openat", {INT, STRING, FLAG, INT}, 4},
    {"mkdirat", {INT, STRING, INT}, 3},
    {"mknodat", {INT, STRING, INT, INT}, 4},
    {"fchownat", {INT, STRING, INT, INT, FLAG}, 5},
    {"futimesat", {INT, STRING, STRUCT}, 3},
    {"fstatat64", {INT, STRING, STRUCT, FLAG}, 4},
    {"unlinkat", {INT, STRING, FLAG}, 3},
    {"renameat", {INT, STRING, INT, STRING}, 4},
    {"linkat", {INT, STRING, INT, STRING, FLAG}, 5},
    {"symlinkat", {STRING, INT, STRING}, 3},
    {"readlinkat", {INT, STRING, STRING, INT}, 4},
    {"fchmodat", {INT, STRING, STRUCT}, 3},
    {"faccessat", {INT, STRING, INT}, 3},
    {"pselect6", {}, 0},
    {"ppoll", {STRUCT, INT, STRUCT, STRUCT, INT}, 5},
    {"unshare", {FLAG}, 1},
    {"set_robust_list", {STRUCT, INT}, 2},
    {"get_robust_list", {INT, STRUCT, ADDR}, 3},
    {"splice", {}, 0},
    {"sync_file_range", {INT, STRUCT, STRUCT, FLAG}, 4},
    {"tee", {INT, INT, INT, FLAG}, 4},
    {"vmsplice", {INT, STRUCT, INT, FLAG}, 4},
    {"move_pages", {}, 0},
    {"getcpu", {ADDR, ADDR, STRUCT}, 3},
    {"epoll_pwait", {}, 0},
    {"utimensat", {INT, STRING, STRUCT, FLAG}, 4},
    {"signalfd", {INT, STRUCT, INT}, 3},
    {"timerfd_create", {INT, FLAG}, 2},
    {"eventfd", {INT}, 1},
    {"fallocate", {INT, INT, STRUCT, STRUCT}, 4},
    {"timerfd_settime", {INT, FLAG, STRUCT, STRUCT}, 4},
    {"timerfd_gettime", {INT, STRUCT}, 2},
    {"signalfd4", {INT, STRUCT, INT, FLAG}, 4},
    {"eventfd2", {INT, FLAG}, 2},
    {"epoll_create1", {FLAG}, 1},
    {"dup3", {INT, INT, FLAG}, 3},
    {"pipe2", {ADDR, FLAG}, 2},
    {"inotify_init1", {FLAG}, 1},
    {"preadv", {INT, STRUCT, INT, INT, INT}, 5},
    {"pwritev", {INT, STRUCT, INT, INT, INT}, 5},
    {"rt_tgsigqueueinfo", {INT, INT, INT, STRUCT}, 4},
    {"perf_event_open", {STRUCT, INT, INT, INT, FLAG}, 5},
    {"recvmmsg", {INT, STRUCT, INT, FLAG, STRUCT}, 5}
};

#endif
