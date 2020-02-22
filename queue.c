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
void merge(int left, int right, list_ele_t **array)
{
    // list_ele_t *temparray[right-left+1];
    // list_ele_t **temparray = (list_ele_t**)malloc(sizeof(list_ele_t*) *
    // (right-left+1));

    list_ele_t *temphead = NULL;
    list_ele_t *now = NULL;

    // printf("temp array size : %d\n", right-left+1);

    // int tempindex = 0;

    int mid = (left + right) / 2;

    int leftindex = left;
    int rightindex = mid + 1;

    while (leftindex <= mid && rightindex <= right) {
        if (strcmp(array[leftindex]->value, array[rightindex]->value) <= 0) {
            // temparray[tempindex] = array[leftindex];
            if (temphead == NULL) {
                temphead = array[leftindex];
                now = temphead;
            } else {
                now->next = array[leftindex];
                now = now->next;
            }
            leftindex++;
        } else {
            // temparray[tempindex] = array[rightindex];
            if (temphead == NULL) {
                temphead = array[rightindex];
                now = temphead;
            } else {
                now->next = array[rightindex];
                now = now->next;
            }
            rightindex++;
        }
        // tempindex++;
    }

    while (leftindex <= mid) {
        // temparray[tempindex] = array[leftindex];
        now->next = array[leftindex];
        now = now->next;

        leftindex++;
        // tempindex++;
    }

    while (rightindex <= right) {
        // temparray[tempindex] = array[rightindex];
        now->next = array[rightindex];
        now = now->next;

        rightindex++;
        // tempindex++;
    }

    now->next = NULL;

    /*tempindex = 0;
    for(int i = left;i <= right;i++){
        array[i] = temparray[tempindex];
    tempindex++;
    }*/
    int index = left;
    for (list_ele_t *i = temphead; i != NULL; i = i->next) {
        array[index] = i;
        index++;
    }
}

void mergeSort(int left, int right, list_ele_t **array)
{
    if (left >= right) {
        return;
    }

    // printf("left : %d\n", left);
    // printf("right : %d\n", right);

    int mid = (left + right) / 2;

    mergeSort(left, mid, array);
    mergeSort(mid + 1, right, array);

    merge(left, right, array);
}

void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL || q->head == NULL || q->head->next == NULL) {
        return;
    }

    list_ele_t *pointer_array[q->q_size];
    //要想辦法把這個array精簡掉...
    //想到一個辦法，因為我們已知q->q_size，所以我們可以在O(N)時間內把一個linked
    // list拆成兩半 mergeSort改成mergeSort(list_ele_t *lefthead, list_ele_t
    // *righthead, int element_size) merge改成merge(list_ele_t *lefthead,
    // list_ele_t *righthead, int element_size)
    //
    // pointer_array = (list_ele_t**)malloc(sizeof(list_ele_t*) * q->q_size);

    int index = 0;
    for (list_ele_t *i = q->head; i != NULL; i = i->next, index++) {
        pointer_array[index] = i;
    }

    mergeSort(0, q->q_size - 1, pointer_array);

    list_ele_t *newhead = NULL;
    list_ele_t *last = NULL;
    for (int i = 0; i < q->q_size; i++) {
        if (i == 0) {
            newhead = pointer_array[i];
            last = newhead;
        } else {
            last->next = pointer_array[i];
            last = pointer_array[i];
        }
    }
    last->next = NULL;

    q->head = newhead;
    q->tail = pointer_array[q->q_size - 1];
    // from array to list

    /*
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
    */
}
