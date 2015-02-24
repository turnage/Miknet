#ifndef MIKNET_MIKLIST_H_
#define MIKNET_MIKLIST_H_

typedef struct miklist_t {
	struct miklist_t *next;
	void *payload;
} miklist_t;

/**
 *  Enqueues a payload in a miklist; assumes responsibility for the payload
 *  pointer and expects that it is properly allocated to live beyond the caller
 *  scope.
 *
 *  Passing a NULL list returns a new list. Otherwise it will return the passed
 *  list.
 */
miklist_t *miklist_enqueue(miklist_t *list, void *payload);

/**
 *  Removes the first element from the miklist and frees the resources it used
 *  for itself and its payload. Returns the new front of queue. If NULL, the
 *  queue is empty.
 */
miklist_t *miklist_dequeue(miklist_t *list);

#endif /* MIKNET_MIKLIST_H_ */