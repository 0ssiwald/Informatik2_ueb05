/*******************************************
* includes functions for the quick sort algorithm
********************************************/
#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

int partition(sPlayer *, int, int, int (*) (sPlayer*, sPlayer*));

void quickSort(sPlayer *, int, int, int (*)(sPlayer*, sPlayer*));

void QSort(sPlayer *, int, int (*)(sPlayer*, sPlayer*));

void swapp(sPlayer*, sPlayer*);

#endif // SORT_H_INCLUDED
