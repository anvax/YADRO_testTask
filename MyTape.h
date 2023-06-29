//
// Created by 1 on 28.06.2023.
//

#ifndef TESTTASK_MYTAPE_H
#define TESTTASK_MYTAPE_H


#include "iTape.h"


using namespace std;

class MyTape{
protected:
    int wr,r,s;//время задержек
    int ram=5000;//оперативная память устройства
public:
    int length=0;//длина входной/выходной ленты
    int pos=0;//позиция магнитной головки
    int ch;//символ на котором стоит головка
    void loadConfig(iTape &itape,FILE *cfg);//загружаем конфиг
    void ScanTape(iTape &itape,FILE *input);//сканируем ленту на ее размер
    void MoveLeftOne(iTape &itape);//сдвиг ленты влево на 1
    void MoveRightOne(iTape &itape);//сдвиг ленты вправо на 1
    void MoveRight(iTape &itape,int count);//перемотка вправо на count-ячеек
    void MoveLeft(iTape &itape,int count);//перемотка влево на count-ячеек
    void Read(iTape &itape,FILE *input,string fname);//чтение ячейки ленты
    void Write(iTape &itape,FILE *output);//запись прочитанной информации
    void WriteFromRam(iTape &itape,FILE *output,int symb);//запись информации из оперативной памяти
};


#endif //TESTTASK_MYTAPE_H
