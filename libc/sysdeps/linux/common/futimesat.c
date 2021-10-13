/*
 * futimesat() for uClibc
 *
 * Copyright (C) 2009 Analog Devices Inc.
 * Copyright (C) 2021 Technology Innovation Institute
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/stat.h>

#if defined __NR_futimesat && defined __NR_utimensat
/*
 * Approach below modified from:
 * libc/sysdeps/linux/common/futimens.c
 * libc/sysdeps/linux/common/lutimes.c
 */
int futimesat (int fd, const char *file, const struct timeval tvp[2])
{
	struct timespec ts[2];

	if (tvp != NULL)
	{
		TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
		TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
		return utimensat(fd, file, ts, 0);
	}
	__set_errno(EINVAL);
	return -1;
}
#endif
