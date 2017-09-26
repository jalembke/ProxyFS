#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <dlfcn.h>
#include <strings.h>
#include <string>
#include <sstream>

#include "ldproxyfs.h"
#include "glibc_ops.h"

struct glibc_ops real_ops;

static inline void* 
dlsym_exit_on_error(void* handle, const char* name)
{
	void* sym;
	char* error;

	// Clear any existing error
	dlerror();

	// Search for the symbol
	sym = dlsym(handle, name);

	// Check for error
	if(sym == NULL) {
		std::stringstream err_out;
		err_out << "Warning: Failed to link symbol " << name << ": Symbol not found" << std::endl;
		std::string err_str = err_out.str();
		syscall(SYS_write, STDERR_FILENO, err_str.data(), err_str.length());
	} else if((error = dlerror()) != NULL) {
		std::stringstream err_out;
		err_out << "Error: Failed to link symbol " << name << ": " << error << std::endl;
		std::string err_str = err_out.str();
		syscall(SYS_write, STDERR_FILENO, err_str.data(), err_str.length());
		exit(EXIT_FAILURE);
	}
	
	DEBUG_EXIT(sym);
	return sym;
}

void 
load_glibc_ops(void)
{
	static bool load_glibc_ops_flag = false;

	if(!load_glibc_ops_flag) {

		bzero(&real_ops, sizeof(struct glibc_ops));
		real_ops.open = (int (*)(const char*, int, ...))dlsym_exit_on_error(RTLD_NEXT, "open");
		real_ops.open64 = (int (*)(const char*, int, ...))dlsym_exit_on_error(RTLD_NEXT, "open64");
		real_ops.openat = (int (*)(int, const char*, int, ...))dlsym_exit_on_error(RTLD_NEXT, "openat");
		real_ops.openat64 = (int (*)(int, const char*, int, ...))dlsym_exit_on_error(RTLD_NEXT, "openat64");
		real_ops.creat = (int (*)(const char*, mode_t))dlsym_exit_on_error(RTLD_NEXT, "creat");
		real_ops.creat64 = (int (*)(const char*, mode_t))dlsym_exit_on_error(RTLD_NEXT, "creat64");
		real_ops.unlink = (int (*)(const char*))dlsym_exit_on_error(RTLD_NEXT, "unlink");
		real_ops.unlinkat = (int (*)(int, const char*, int))dlsym_exit_on_error(RTLD_NEXT, "unlinkat");
		real_ops.rename = (int (*)(const char*, const char*))dlsym_exit_on_error(RTLD_NEXT, "rename");
		real_ops.renameat = (int (*)(int, const char*, int, const char*))dlsym_exit_on_error(RTLD_NEXT, "renameat");
		real_ops.read = (ssize_t (*)(int, void*, size_t))dlsym_exit_on_error(RTLD_NEXT, "read");
		real_ops.pread = (ssize_t (*)(int, void*, size_t, off_t))dlsym_exit_on_error(RTLD_NEXT, "pread");
		real_ops.readv = (ssize_t (*)(int, const struct iovec*, int))dlsym_exit_on_error(RTLD_NEXT, "readv");
		real_ops.write = (ssize_t (*)(int, const void*, size_t))dlsym_exit_on_error(RTLD_NEXT, "write");
		real_ops.pwrite = (ssize_t (*)(int, const void*, size_t, off_t))dlsym_exit_on_error(RTLD_NEXT, "pwrite");
		real_ops.writev = (ssize_t (*)(int, const struct iovec*, int))dlsym_exit_on_error(RTLD_NEXT, "writev");
		real_ops.truncate = (int (*)(const char*, off_t))dlsym_exit_on_error(RTLD_NEXT, "truncate");
		real_ops.ftruncate = (int (*)(int, off_t))dlsym_exit_on_error(RTLD_NEXT, "ftruncate");
		real_ops.fallocate = (int (*)(int, off_t, off_t))dlsym_exit_on_error(RTLD_NEXT, "fallocate");
		real_ops.close = (int (*)(int))dlsym_exit_on_error(RTLD_NEXT, "close");
		real_ops.__xstat = (int (*)(int, const char*, struct stat*))dlsym_exit_on_error(RTLD_NEXT, "__xstat");
		real_ops.__xstat64 = (int (*)(int, const char*, struct stat64*))dlsym_exit_on_error(RTLD_NEXT, "__xstat64");
		real_ops.__fxstat = (int (*)(int, int, struct stat*))dlsym_exit_on_error(RTLD_NEXT, "__fxstat");
		real_ops.__fxstat64 = (int (*)(int, int, struct stat64*))dlsym_exit_on_error(RTLD_NEXT, "__fxstat64");
		real_ops.__fxstatat = (int (*)(int, int, const char*, struct stat*, int))dlsym_exit_on_error(RTLD_NEXT, "__fxstatat");
		real_ops.__fxstatat64 = (int (*)(int, int, const char*, struct stat64*, int))dlsym_exit_on_error(RTLD_NEXT, "__fxstatat64");
		real_ops.__lxstat = (int (*)(int, const char*, struct stat*))dlsym_exit_on_error(RTLD_NEXT, "__lxstat");
		real_ops.__lxstat64 = (int (*)(int, const char*, struct stat64*))dlsym_exit_on_error(RTLD_NEXT, "__lxstat64");
		real_ops.futimesat = (int (*)(int, const char*, const struct timeval*))dlsym_exit_on_error(RTLD_NEXT, "futimesat");
		real_ops.utimes = (int (*)(const char*, const struct timeval*))dlsym_exit_on_error(RTLD_NEXT, "utimes");
		real_ops.utime = (int (*)(const char*, const struct utimbuf*))dlsym_exit_on_error(RTLD_NEXT, "utime");
		real_ops.futimes = (int (*)(int, const struct timeval*))dlsym_exit_on_error(RTLD_NEXT, "futimes");
		real_ops.dup = (int (*)(int))dlsym_exit_on_error(RTLD_NEXT, "dup");
		real_ops.dup2 = (int (*)(int, int))dlsym_exit_on_error(RTLD_NEXT, "dup2");
		real_ops.dup3 = (int (*)(int, int, int))dlsym_exit_on_error(RTLD_NEXT, "dup3");
		real_ops.chown = (int (*)(const char*, uid_t, gid_t))dlsym_exit_on_error(RTLD_NEXT, "chown");
		real_ops.fchown = (int (*)(int, uid_t, gid_t))dlsym_exit_on_error(RTLD_NEXT, "fchown");
		real_ops.fchownat = (int (*)(int, const char*, uid_t, gid_t, int))dlsym_exit_on_error(RTLD_NEXT, "fchownat");
		real_ops.lchown = (int (*)(const char*, uid_t, gid_t))dlsym_exit_on_error(RTLD_NEXT, "lchown");
		real_ops.chmod = (int (*)(const char*, mode_t))dlsym_exit_on_error(RTLD_NEXT, "chmod");
		real_ops.fchmod = (int (*)(int, mode_t))dlsym_exit_on_error(RTLD_NEXT, "fchmod");
		real_ops.fchmodat = (int (*)(int, const char*, mode_t, int))dlsym_exit_on_error(RTLD_NEXT, "fchmodat");
		real_ops.lchmod = (int (*)(const char*, mode_t))dlsym_exit_on_error(RTLD_NEXT, "lchmod");
		real_ops.mkdir = (int (*)(const char*, mode_t))dlsym_exit_on_error(RTLD_NEXT, "mkdir");
		real_ops.mkdirat = (int (*)(int, const char*, mode_t))dlsym_exit_on_error(RTLD_NEXT, "mkdirat");
		real_ops.rmdir = (int (*)(const char*))dlsym_exit_on_error(RTLD_NEXT, "rmdir");
		real_ops.readlink = (ssize_t (*)(const char*, char*, size_t))dlsym_exit_on_error(RTLD_NEXT, "readlink");
		real_ops.readlinkat = (ssize_t (*)(int, const char*, char*, size_t))dlsym_exit_on_error(RTLD_NEXT, "readlinkat");
		real_ops.symlink = (int (*)(const char*, const char*))dlsym_exit_on_error(RTLD_NEXT, "symlink");
		real_ops.symlinkat = (int (*)(const char*, int, const char*))dlsym_exit_on_error(RTLD_NEXT, "symlinkat");
		real_ops.link = (int (*)(const char*, const char*))dlsym_exit_on_error(RTLD_NEXT, "link");
		real_ops.linkat = (int (*)(int, const char*, int, const char*, int))dlsym_exit_on_error(RTLD_NEXT, "linkat");
		real_ops.opendir = (DIR* (*)(const char*))dlsym_exit_on_error(RTLD_NEXT, "opendir");
		real_ops.fdopendir = (DIR* (*)(int))dlsym_exit_on_error(RTLD_NEXT, "fdopendir");
		real_ops.readdir = (dirent* (*)(DIR*))dlsym_exit_on_error(RTLD_NEXT, "readdir");
		real_ops.readdir64 = (dirent64* (*)(DIR*))dlsym_exit_on_error(RTLD_NEXT, "readdir64");
		real_ops.readdir_r = (int (*)(DIR*, struct dirent*, struct dirent **))dlsym_exit_on_error(RTLD_NEXT, "readdir_r");
		real_ops.readdir64_r = (int (*)(DIR*, struct dirent*, struct dirent64 **))dlsym_exit_on_error(RTLD_NEXT, "readdir64_r");
		real_ops.closedir = (int (*)(DIR*))dlsym_exit_on_error(RTLD_NEXT, "closedir");
		real_ops.access = (int (*)(const char*, int))dlsym_exit_on_error(RTLD_NEXT, "access");
		real_ops.faccessat = (int (*)(int, const char*, int, int))dlsym_exit_on_error(RTLD_NEXT, "faccessat");
		real_ops.flock = (int (*)(int, int))dlsym_exit_on_error(RTLD_NEXT, "flock");
		real_ops.fcntl = (int (*)(int, int, ...))dlsym_exit_on_error(RTLD_NEXT, "fcntl");
		real_ops.sync = (void (*)())dlsym_exit_on_error(RTLD_NEXT, "sync");
		real_ops.fsync = (int (*)(int))dlsym_exit_on_error(RTLD_NEXT, "fsync");
		real_ops.fdatasync = (int (*)(int))dlsym_exit_on_error(RTLD_NEXT, "fdatasync");
		real_ops.fadvise = (int (*)(int, off_t, off_t, int))dlsym_exit_on_error(RTLD_NEXT, "fadvise");
		real_ops.fadvise64 = (int (*)(int, off64_t, off64_t, int))dlsym_exit_on_error(RTLD_NEXT, "fadvise64");
		real_ops.statfs = (int (*)(const char*, struct statfs*))dlsym_exit_on_error(RTLD_NEXT, "statfs");
		real_ops.statfs64 = (int (*)(const char*, struct statfs64*))dlsym_exit_on_error(RTLD_NEXT, "statfs64");
		real_ops.fstatfs = (int (*)(int, struct statfs*))dlsym_exit_on_error(RTLD_NEXT, "fstatfs");
		real_ops.fstatfs64 = (int (*)(int, struct statfs64*))dlsym_exit_on_error(RTLD_NEXT, "fstatfs64");
		real_ops.statvfs = (int (*)(const char*, struct statvfs*))dlsym_exit_on_error(RTLD_NEXT, "statvfs");
		real_ops.fstatvfs = (int (*)(int, struct statvfs*))dlsym_exit_on_error(RTLD_NEXT, "fstatvfs");
		real_ops.__xmknod = (int (*)(int, const char*, mode_t, dev_t*))dlsym_exit_on_error(RTLD_NEXT, "__xmknod");
		real_ops.__xmknodat = (int (*)(int, int, const char*, mode_t, dev_t))dlsym_exit_on_error(RTLD_NEXT, "__xmknodat");
		real_ops.sendfile = (ssize_t (*)(int, int, off_t*, size_t))dlsym_exit_on_error(RTLD_NEXT, "sendfile");
		real_ops.sendfile64 = (ssize_t (*)(int, int, off64_t*, size_t))dlsym_exit_on_error(RTLD_NEXT, "sendfile64");
		real_ops.setxattr = (int (*)(const char*, const char*, const void*, size_t, int))dlsym_exit_on_error(RTLD_NEXT, "setxattr");
		real_ops.lsetxattr = (int (*)(const char*, const char*, const void*, size_t, int))dlsym_exit_on_error(RTLD_NEXT, "lsetxattr");
		real_ops.fsetxattr = (int (*)(int, const char*, const void*, size_t, int))dlsym_exit_on_error(RTLD_NEXT, "fsetxattr");
		real_ops.getxattr = (ssize_t (*)(const char*, const char*, void*, size_t))dlsym_exit_on_error(RTLD_NEXT, "getxattr");
		real_ops.lgetxattr = (ssize_t (*)(const char*, const char*, void*, size_t))dlsym_exit_on_error(RTLD_NEXT, "lgetxattr");
		real_ops.fgetxattr = (ssize_t (*)(int, const char*, void*, size_t))dlsym_exit_on_error(RTLD_NEXT, "fgetxattr");
		real_ops.listxattr = (ssize_t (*)(const char*, char*, size_t))dlsym_exit_on_error(RTLD_NEXT, "listxattr");
		real_ops.llistxattr = (ssize_t (*)(const char*, char*, size_t))dlsym_exit_on_error(RTLD_NEXT, "llistxattr");
		real_ops.flistxattr = (ssize_t (*)(int, char*, size_t))dlsym_exit_on_error(RTLD_NEXT, "flistxattr");
		real_ops.removexattr = (int (*)(const char*, const char*))dlsym_exit_on_error(RTLD_NEXT, "removexattr");
		real_ops.lremovexattr = (int (*)(const char*, const char*))dlsym_exit_on_error(RTLD_NEXT, "lremovexattr");
		real_ops.fremovexattr = (int (*)(int, const char*))dlsym_exit_on_error(RTLD_NEXT, "fremovexattr");
		real_ops.munmap = (int (*)(void*, size_t))dlsym_exit_on_error(RTLD_NEXT, "munmap");
		real_ops.msync = (int (*)(void*, size_t, int))dlsym_exit_on_error(RTLD_NEXT, "msync");
		/*real_ops.getfscreatecon = (int (*)(security_context_t*))dlsym_exit_on_error(RTLD_NEXT, "getfscreatecon");
		real_ops.getfilecon = (int (*)(const char*, security_context_t*))dlsym_exit_on_error(RTLD_NEXT, "getfilecon");
		real_ops.lgetfilecon = (int (*)(const char*, security_context_t*))dlsym_exit_on_error(RTLD_NEXT, "lgetfilecon");
		real_ops.fgetfilecon = (int (*)(int, security_context_t*))dlsym_exit_on_error(RTLD_NEXT, "fgetfilecon");
		real_ops.setfscreatecon = (int (*)(security_context_t))dlsym_exit_on_error(RTLD_NEXT, "setfscreatecon");
		real_ops.setfilecon = (int (*)(const char*, security_context_t))dlsym_exit_on_error(RTLD_NEXT, "setfilecon");
		real_ops.lsetfilecon = (int (*)(const char*, security_context_t))dlsym_exit_on_error(RTLD_NEXT, "lsetfilecon");
		real_ops.fsetfilecon = (int (*)(int, security_context_t))dlsym_exit_on_error(RTLD_NEXT, "fsetfilecon");*/

		load_glibc_ops_flag = true;
	}
}