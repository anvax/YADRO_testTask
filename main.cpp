#include <iostream>
#include <vector>
#include "sort.h"
#include "Tape.h"

using namespace std;

int main() {
    Tape tp;
    MyTape mtp;
    sort sort;
    //ввод названий файлов
    cout<<"Enter the name of the input file (with .txt):"<<endl;
    cin>>tp.fin;
    cout<<"Enter the name of the output file (with .txt):"<<endl;
    cin>>tp.fout;
    //создаем файлы
    FILE* cfg=fopen(tp.fname.c_str(),"r");
    FILE* input=fopen(tp.fin.c_str(),"r");
    FILE* output=fopen(tp.fout.c_str(),"w");
    //проверка на наличие конфигурационного файла
    if(cfg==NULL){
        cout<<"No config file"<<endl;
        exit(0);
    }else{
        cout<<"Config is open: "<<tp.fname.c_str()<<endl;
    }

    mtp.loadConfig(tp,cfg);//загружаем коонфиг
    fclose(cfg);
    mtp.ScanTape(tp,input);//сканируем ленту на размер
    sort.removeTmpTapes(mtp);//удаление старых временных лент
    input=fopen(tp.fin.c_str(),"r");
    sort.tmpTapes(mtp);//создаем временные ленты
    sort.sortEachTmpTape(mtp,tp,input);//сортируем временные ленты
    sort.SortTapes(mtp,tp,output);//сортируем временные ленты в одну выходную ленту
    //закрываем файлы
    fclose(output);
    fclose(input);
    return 0;
}
