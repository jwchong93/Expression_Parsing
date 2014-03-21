#ifndef Iterator_H
#define Iterator_H

typedef struct {
	void *head;
	void *tail;
} LinkedList;

typedef struct {
	LinkedList *list;
	void *current;
	void *(*next)(void);
} Iterator;

//Element that Ee pak use to store identifier value.
typedef struct DefineElement_t{
	struct DefineElement_t *next;
	char *id;
	int value;
}DefineElement;

void *getIterator(LinkedList *list);
void *getNext(void);

#endif // Iterator_H

