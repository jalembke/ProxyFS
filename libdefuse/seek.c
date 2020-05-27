#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "libdefuse.h"

#define SEEK_DATA 3
#define SEEK_HOLE 4

int defuse_lseek(const struct file_handle_data* fhd, int fd, off_t offset, int whence)
{
	DEBUG_ENTER;
	int rv = 0;
	if(whence == SEEK_CUR || whence == SEEK_SET) {
		rv = real_lseek(fd, offset, whence);
		goto out;
	}

	struct stat statbuf;
	rv = fhd->mount->fgetattr(fhd->file_handle, &statbuf);
	if(rv != 0) {
		errno = rv;
		rv = -1;
		goto out;
	}
	switch(whence) {
		case SEEK_HOLE:
			if(offset >= statbuf.st_size) {
				errno = ENXIO;
				rv = -1;
				goto out;
			}
			offset = statbuf.st_size;
			break;
		case SEEK_DATA:
			if(offset >= statbuf.st_size) {
				errno = ENXIO;
				rv = -1;
				goto out;
			}
			break;
		case SEEK_END:
			offset += statbuf.st_size;
			break;
	}
	rv = real_lseek(fd, offset, SEEK_SET);
out:
	DEBUG_EXIT(rv);
	return rv;
}

#undef SEEK_DATA
#undef SEEK_HOLE
