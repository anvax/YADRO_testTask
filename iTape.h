//
// Created by 1 on 28.06.2023.
//

#ifndef TESTTASK_ITAPE_H
#define TESTTASK_ITAPE_H
#include <iostream>
using namespace std;
//интерфейс устройства
class iTape{
public:
    string fin;//имя входной ленты (файла)
    string fout;//имя выходной ленты (файла)
    string fname="config.txt";//имя конфигурационного файла
    void virtual Configure(FILE* cfg,int *wr,int *r,int *s)=0;//загружаем конфиг
    void virtual ScanTape(FILE *input,int *length)=0;//сканируем ленту
    void virtual read(FILE *input,int *pos,int *ch,int length)=0;//читаем ленту
    void virtual write(FILE *output,int *pos,int *ch)=0;//записываем на ленту
    void virtual left1(int *pos)=0;//влево на 1
    void virtual right1(int *pos)=0;//вправо на 1
    void virtual RewindLeft(int *pos,int count)=0;//перемотка влево
    void virtual RewindRight(int *pos,int count)=0;//перемотка вправо
};


#endif //TESTTASK_ITAPE_H
