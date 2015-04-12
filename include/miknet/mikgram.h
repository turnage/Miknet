#ifndef MIKNET_MIKGRAM_H_
#define MIKNET_MIKGRAM_H_

#include <stdint.h>

#define MIKNET_METADATA_SIZE 4
#define MIKNET_GRAM_MAX_SIZE 512
#define MIKNET_GRAM_MIN_SIZE MIKNET_METADATA_SIZE
#define MIKNET_MAX_PAYLOAD_SIZE MIKNET_GRAM_MAX_SIZE - MIKNET_METADATA_SIZE

/**
 *  A mikgram represents the most basic unit of communication between miknodes.
 *  It abbreviates "miknode datagram".
 */
typedef struct mikgram_t {
	void *data;
	size_t len;
	uint8_t peer;
	struct mikgram_t *next;
} mikgram_t;

/**
 *  Creates a complete mikgram for a chunk of data, with its own copy. A mikgram
 *  contains the original data and a serialized header containing its size and
 *  some flags.
 *
 *  mikgrams must be disposed of with mikgram_close.
 */
mikgram_t *mikgram(const void *data, size_t len);

/**
 *  If the data is a complete mikgram, returns the number of octets needed to
 *  extract the payload from it with mikgram_extract (zero-length mikgrams are
 *  not allowed).
 *
 *  Negative values indicate an error or that the gram does not conform to
 *  miknet expectations.
 */
ssize_t mikgram_check(const mikgram_t *gram);

/**
 *  Extracts the data from a packed/serialized mikgram into a buffer.
 */
int mikgram_extract(const mikgram_t *gram, void *buf, size_t len);

/**
 *  Frees the resources used by a mikgram.
 */
void mikgram_close(mikgram_t *gram);

#endif /* MIKNET_MIKGRAM_H_ */
