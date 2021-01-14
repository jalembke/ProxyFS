/*
    Caching file system proxy
    Copyright (C) 2004  Miklos Szeredi <miklos@szeredi.hu>

    This program can be distributed under the terms of the GNU GPL.
    See the file COPYING.
*/

#include "sshfs_op.h"

struct sshfs_operations *cache_wrap(struct sshfs_operations *oper);
int cache_parse_options(struct fuse_args *args);
void cache_add_attr(const char *path, const struct stat *stbuf, uint64_t wrctr);
void cache_invalidate(const char *path);
uint64_t cache_get_write_ctr(void);
