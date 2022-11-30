#include "teams.h"
#include "datastructure.h"
#include "sort.h"


int partition(sPlayer *A, int ui, int oi, int (*cmp) (sPlayer*, sPlayer*))
{
   sPlayer *comp = A + ui; // Value to compare
   int i = ui + 1;
   int j = oi;

   while(i <= j)
   {
      while((i <= j) && (cmp(A + i, comp) <= 0))
         i++; // index from left
      while((j >= i) && (cmp(A + j, comp) >= 0))
         j--; // index from right
      if(i < j)                                    //??????????
      {
         swapp(A + i, A + j);
         i++;
         j--;
      }
   }
   i--;
   swapp(A + i, comp);
   return i;
}


void quickSort(sPlayer *A, int ui, int oi, int (*cmp)(sPlayer*, sPlayer*))
{
   int idx;
   if(ui >= oi)
      return;
   idx = partition(A, ui, oi, cmp);
   quickSort(A, ui, idx - 1, cmp);
   quickSort(A, idx + 1, oi, cmp);

}

void QSort(sPlayer *A, int Count, int (*cmp)(sPlayer*, sPlayer*))
{
   quickSort(A, 0, Count - 1, cmp);
}

void swapp(sPlayer *A1, sPlayer *A2)
{
   sPlayer tmp = *A1;
   *A1 = *A2;
   *A2 = tmp;
}
