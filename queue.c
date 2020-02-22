#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q == NULL) {
        // printf("memory is not enough!\n");
        // exit(-1);
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->q_size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }

    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *now = q->head;

    if (now == NULL) {
    } else {
        while (now) {
            list_ele_t *next = now->next;

            free(now->value);
            free(now);

            now = next;
        }
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */

    if (q == NULL) {
        return false;
    }

    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    if (newh == NULL) {
        // printf("malloc returns NULL!\n");
        return false;
    }

    newh->value = (char *) malloc(sizeof(char) * strlen(s) + 1);

    if (newh->value == NULL) {
        // printf("malloc returns NULL!\n");
        free(newh);
        return false;
    }

    newh->next = NULL;
    strncpy(newh->value, s, strlen(s));
    newh->value[strlen(s)] = 0;

    // printf("size of s :%zu\n", strlen(s));
    //學到一課了，format string可以用%zu
    // printf("string : %s\n", newh->value);

    if (q->head == NULL) {
        q->tail = newh;
    }

    newh->next = q->head;
    q->head = newh;

    q->q_size++;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newt;

    if (q == NULL) {
        return false;
    }

    newt = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    if (newt == NULL) {
        // printf("malloc returns NULL!\n");
        return false;
    }

    newt->value = (char *) malloc(sizeof(char) * strlen(s) + 1);

    if (newt->value == NULL) {
        // printf("malloc returns NULL!\n");
        free(newt);
        return false;
    }

    newt->next = NULL;
    strncpy(newt->value, s, strlen(s));
    newt->value[strlen(s)] = 0;

    // printf("size of s :%zu\n", strlen(s));
    // printf("string : %s\n", newt->value);

    if (q->tail == NULL) {
        q->head = newt;
        q->tail = newt;

    } else {
        q->tail->next = newt;
        q->tail = newt;
    }

    q->q_size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL) {
        return false;
    }

    if (sp != NULL && bufsize != 0) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = 0;
    }

    list_ele_t *deleted;

    deleted = q->head;

    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    q->head = q->head->next;

    free(deleted->value);
    free(deleted);

    if (q->head == NULL) {
        q->tail = NULL;
    }

    q->q_size--;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->head == NULL) {
        return 0;
    }
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return q->q_size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL || q->head == NULL || q->head->next == NULL) {
        return;
    }

    list_ele_t *last = NULL;
    list_ele_t *now = q->head;
    list_ele_t *next = now->next;

    q->tail = q->head;

    while (now) {
        now->next = last;

        last = now;
        now = next;

        if (next != NULL) {
            next = next->next;
        }
    }

    q->head = last;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
//改成merge sort

void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL || q->head == NULL || q->head->next == NULL) {
        return;
    }



    list_ele_t *sorted = q->head;
    list_ele_t *unsorted_head = q->head->next;

    sorted->next = NULL;

    while (unsorted_head) {
        list_ele_t *last = NULL;
        list_ele_t *i;
        for (i = sorted; i != NULL; last = i, i = i->next) {
            if (strcmp(unsorted_head->value, i->value) <= 0) {
                // printf("unsorted_head->value : %s\n", unsorted_head->value);
                // printf("i->value : %s\n", i->value);

                if (last == NULL) {
                    list_ele_t *temp;
                    temp = unsorted_head->next;

                    unsorted_head->next = sorted;
                    sorted = unsorted_head;
                    unsorted_head = temp;

                } else {
                    list_ele_t *temp;
                    temp = unsorted_head->next;

                    last->next = unsorted_head;
                    unsorted_head->next = i;

                    unsorted_head = temp;
                }
                break;
            }
        }
        if (i == NULL) {
            list_ele_t *temp;
            temp = unsorted_head->next;

            last->next = unsorted_head;
            unsorted_head->next = NULL;
            unsorted_head = temp;
        }
    }

    q->head = sorted;
}
