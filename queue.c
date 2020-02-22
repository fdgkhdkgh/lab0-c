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

list_ele_t *merge(list_ele_t *lefthead,
                  list_ele_t *righthead,
                  int leftsize,
                  int rightsize)
{
    int headsize = 0;
    list_ele_t *temphead = NULL;
    list_ele_t *now = NULL;
    while (leftsize != 0 && rightsize != 0) {
        if (strcmp(lefthead->value, righthead->value) <= 0) {
            if (headsize == 0) {
                temphead = lefthead;
                lefthead = lefthead->next;
                temphead->next = NULL;

                now = temphead;

            } else {
                now->next = lefthead;
                lefthead = lefthead->next;
                now = now->next;
                now->next = NULL;
            }
            leftsize--;
        } else {
            if (headsize == 0) {
                temphead = righthead;
                righthead = righthead->next;
                temphead->next = NULL;

                now = temphead;
            } else {
                now->next = righthead;
                righthead = righthead->next;
                now = now->next;
                now->next = NULL;
            }
            rightsize--;
        }
        headsize++;
    }

    while (leftsize != 0) {
        if (headsize == 0) {
            temphead = lefthead;
            lefthead = lefthead->next;
            temphead->next = NULL;

            now = temphead;
        } else {
            now->next = lefthead;
            lefthead = lefthead->next;
            now = now->next;
            now->next = NULL;
        }
        leftsize--;
        headsize++;
    }

    while (rightsize != 0) {
        if (headsize == 0) {
            temphead = righthead;
            righthead = righthead->next;
            temphead->next = NULL;

            now = temphead;
        } else {
            now->next = righthead;
            righthead = righthead->next;
            now = now->next;
            now->next = NULL;
        }
        rightsize--;
        headsize++;
    }
    return temphead;
}

list_ele_t *mergeSort(list_ele_t *lefthead,
                      list_ele_t *righthead,
                      int leftsize,
                      int rightsize)
{
    if (leftsize == 0 || rightsize == 0) {
        return NULL;
    }
    int i;

    int lhalf_qsize = leftsize / 2;
    list_ele_t *llhead = lefthead;
    list_ele_t *lrhead = lefthead;
    int llsize = lhalf_qsize;
    int lrsize = leftsize - llsize;
    for (i = 0; i < lhalf_qsize; i++) {
        lrhead = lrhead->next;
    }
    llhead = mergeSort(llhead, lrhead, llsize, lrsize);
    if (llsize == 0 && lrsize == 1) {
        llhead = lrhead;
        llhead->next = NULL;
    }

    int rhalf_qsize = rightsize / 2;
    list_ele_t *rlhead = righthead;
    list_ele_t *rrhead = righthead;
    int rlsize = rhalf_qsize;
    int rrsize = rightsize - rhalf_qsize;
    for (i = 0; i < rhalf_qsize; i++) {
        rrhead = rrhead->next;
    }
    rlhead = mergeSort(rlhead, rrhead, rlsize, rrsize);
    if (rlsize == 0 && rrsize == 1) {
        rlhead = rrhead;
        rlhead->next = NULL;
    }
    return merge(llhead, rlhead, leftsize, rightsize);
}

void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL || q->head == NULL || q->head->next == NULL) {
        return;
    }
    int half_qsize = q->q_size / 2;
    int i = 0;
    list_ele_t *lefthead = q->head;
    list_ele_t *righthead = q->head;
    int leftsize = q->q_size / 2;
    int rightsize = q->q_size - leftsize;
    for (i = 0; i < half_qsize; i++) {
        righthead = righthead->next;
    }
    q->head = mergeSort(lefthead, righthead, leftsize, rightsize);
}
