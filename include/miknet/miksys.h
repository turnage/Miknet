#ifndef MIKNET_MIKSYS_H_
#define MIKNET_MIKSYS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/**
 *  miksys provides wrappers for functions provided by the kernel or C language
 *  that parts of miknet might otherwise call directly.
 *
 *  This layer of misdirection allows the functions to be easily switched out
 *  with other dependencies at runtime, for testing.
 */

typedef struct posix_t {
	int (*bind)(	const struct posix_t *,
			int,
			const struct sockaddr *,
			socklen_t);
	void (*freeaddrinfo)(const struct posix_t *, struct addrinfo *);
	int (*getaddrinfo)(	const struct posix_t *,
				const char *,
				const char *,
				const struct addrinfo *,
				struct addrinfo **);
	ssize_t (*sendto)(	const struct posix_t *,
				int,
				const void *,
				size_t,
				int,
				const struct sockaddr *,
				socklen_t);
	int (*setsockopt)(	const struct posix_t *,
				int,
				int,
				int,
				const void *,
				socklen_t);
	int (*socket)(const struct posix_t *, int, int, int);
	ssize_t (*recvfrom)(	const struct posix_t *,
				int,
				void *,
				size_t,
				int,
				struct sockaddr *,
				socklen_t *);
} posix_t;

/**
 *  Returns the default posix wrapper.
 */
posix_t *mikposix();

#endif /* MIKNET_MIKSYS_H_ */
