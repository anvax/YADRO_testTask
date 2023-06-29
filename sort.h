//
// Created by 1 on 28.06.2023.
//

#ifndef TESTTASK_SORT_H
#define TESTTASK_SORT_H

#include <fstream>
#include "MyTape.h"
#include "vector"

using namespace std;

class sort: public MyTape{
private:int TapeCount;//количество временных лент
public:
    void tmpTapes(MyTape &mtp);//создаем временные ленты
    void sortEachTmpTape(MyTape &mtp,iTape &itape,FILE *input);//сортируем каждую временную ленту
    void SortTapes(MyTape &mtp,iTape &itape,FILE* output);//сортируем все временные ленты между собой в одну выходную ленту
    void removeTmpTapes();
};


#endif //TESTTASK_SORT_H
