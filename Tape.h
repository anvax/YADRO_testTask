//
// Created by 1 on 28.06.2023.
//


#ifndef TESTTASK_TAPE_H
#define TESTTASK_TAPE_H
#include "iTape.h"
#include <iostream>
#include <fstream>
using namespace std;
//const char* fname="config.txt";



class Tape: public iTape{
public:
    void Configure(FILE* cfg,int *wr,int *r,int *s) override;//конфигурация устройства
    void ScanTape(FILE *input,int *length) override;//сканировние ленты
    void read(FILE *input,int *pos,int *ch,int length) override;//чтение ленты
    void write(FILE *output,int *pos,int *ch) override;//запись на ленту
    void left1(int *pos) override;//сдвиг влево на 1
    void right1(int *pos) override;//сдвиг вправо на 1
    void RewindRight(int *pos,int count) override;//перемотка вправо
    void RewindLeft(int *pos,int count) override;//перемотка влево
};


#endif //TESTTASK_TAPE_H
