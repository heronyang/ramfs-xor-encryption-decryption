/* internal.h: ramfs internal definitions
 *
 * Copyright (C) 2005 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */


extern const struct address_space_operations ramfs_aops;
extern const struct inode_operations ramfs_file_inode_operations;
extern int ramfs_flag;
//extern ssize_t my_aio_write(struct kiocb, const struct iovec , unsigned long , loff_t);
//extern ssize_t my_aio_read(struct kiocb, const struct iovec, unsigned long, loff_t);
