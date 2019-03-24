// Created by David Zashkolny on 18.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#ifndef CPP_QSORT_H
#define CPP_QSORT_H

#endif //CPP_QSORT_H

// функция сортировки
void quicksort(int *mas, int first, int last){
    int mid, count;
    int f = first, l = last;
    mid = mas[(f + l) / 2]; // вычисление опорного элемента
    do {
        while (mas[f] < mid) f++;
        while (mas[l] > mid) l--;
        // перестановка элементов
        if (f <= l){
            count = mas[f];
            mas[f] = mas[l];
            mas[l] = count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) quicksort(mas, first, l);
    if (f < last) quicksort(mas, f, last);
}
