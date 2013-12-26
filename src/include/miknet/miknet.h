#ifndef miknet_h
#define miknet_h

#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <poll.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/time.h>

#define MIK_PACK_MAX 1200
#define MIK_PORT_MAX 6

#define MIK_DEBUG 1

struct miknode_t;
typedef const void ref;

enum {
	ERR_MISSING_PTR  = -1,
	ERR_INVALID_MODE = -2,
	ERR_SOCKET       = -4,
	ERR_ADDRESS      = -5,
	ERR_SOCK_OPT     = -6,
	ERR_BIND         = -7,
	ERR_CONNECT      = -8,
	ERR_PEER_MAX     = -9,
	ERR_POLL         = -10,
        ERR_MEMORY       = -11,
	ERR_WOULD_FAULT  = -12,
	ERR_LISTEN       = -13
};

typedef enum {
	MIK_DISC = 0,
	MIK_CONN = 2
} mikstate_t;

typedef enum {
	MIK_IPV4 = 1,
	MIK_IPV6 = 2
} mikip_t;

typedef enum {
	MIK_ERR  = -1,
	MIK_JOIN = 0,
	MIK_QUIT = 1,
	MIK_DATA = 2
} miktype_t;

typedef struct mikpack_t {
	miktype_t type;
	uint32_t channel;
	uint16_t peer;
	uint16_t len;
	void *data;
} mikpack_t;

typedef struct miklist_t {
	struct miklist_t *next;
	mikpack_t pack;
} miklist_t;

typedef struct mikpeer_t {
	int index;
	struct miknode_t *node;
	int tcp;
	void *data;
	mikstate_t state;
	uint32_t sent;
	uint32_t recvd;
} mikpeer_t;

typedef struct miknode_t {
	int tcp;
	int udp;
	mikip_t ip;
	struct pollfd *fds;
	mikpeer_t *peers;
	uint16_t peerc;
	uint16_t peermax;
	miklist_t *packs;
	miklist_t *commands;
	uint32_t upcap;
	uint32_t downcap;
} miknode_t;

int mik_debug (int err);

const char *mik_errstr(int err);

mikpack_t mikpack (miktype_t type, ref *data, uint16_t len, uint32_t channel);

miklist_t *miklist (ref *data);

miklist_t *miklist_add (miklist_t *head, ref *data);

miklist_t *miklist_next (miklist_t *head);

void miklist_close (miklist_t *head);

int miknode (miknode_t *n, mikip_t ip, uint16_t port);

int miknode_config (miknode_t *n, uint16_t peers, uint32_t up, uint32_t down);

int miknode_connect(miknode_t *n, const char *a, uint16_t p);

int miknode_send (mikpeer_t *p, ref *d, size_t len, uint32_t channel);

int miknode_poll (miknode_t *n, int t);

void miknode_close (miknode_t *n);

int mikpeer (miknode_t *n);

int mikpeer_close (mikpeer_t *p);

#endif /* miknet_h */
