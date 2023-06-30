//
// Created by 1 on 28.06.2023.
//

#include "sort.h"
#include "Tape.h"

void sort::tmpTapes(MyTape &mtp) {
    //если оперативная память меньше, чем длина ленты
    if(ram<=mtp.length){
        if(mtp.length%ram==0){
            TapeCount=mtp.length/ram;
        }else{
            TapeCount=mtp.length/ram+1;
        }
    }else{
        TapeCount=1;//иначе временная лента одна
    }
    //проверка - хватит ли озу на работу с временными лентами одновременно
    if (TapeCount>ram){
        cout<<"Not enough RAM"<<endl;
        exit(0);
    }
    //создаем временные ленты
    for (int i = 1; i <=TapeCount ; i++) {
        FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( i ) +".txt" ).c_str(),"w");
        fclose(fl);
    }
}
void sort::removeTmpTapes(MyTape &mtp) {
    int tpCount=0;
    //если оперативная память меньше, чем длина ленты
    if(ram<=mtp.length){
        if(mtp.length%ram==0){
            tpCount=mtp.length/ram;
        }else{
            tpCount=mtp.length/ram+1;
        }
    }else{
        tpCount=1;//иначе временная лента одна
    }
    //удаляем временные ленты
    for (int i = 1; i <=tpCount ; i++) {
        remove(string( "tmp\\tmpTape" + to_string( i ) +".txt" ).c_str());
    }
}
void sort::sortEachTmpTape(MyTape &mtp, iTape &itape, FILE *input) {
    string fin=itape.fin;
    string fout=itape.fout;
    if(ram<=mtp.length){
        cout<<"Starting sorting temporary tapes..."<<endl;
        //цикл по каждой ленте, кроме последней
        for (int k = 0; k < TapeCount-1; k++) {
            int Mem[ram];//память
            for (int i = ram*k; i < ram*(k+1); i++) {
                mtp.pos=i;
                mtp.Read(itape,input,fin);
                mtp.MoveRightOne(itape);
                Mem[i-ram*k]=mtp.ch;
            }
            int temp;
            //сортировка массива
            for (int i = 0; i < ram - 1; i++) {
                for (int j = 0; j < ram - i - 1; j++) {
                    if (Mem[j] > Mem[j + 1]) {
                        // меняем элементы местами
                        temp = Mem[j];
                        Mem[j] = Mem[j + 1];
                        Mem[j + 1] = temp;
                    }
                }
            }
            //запись отсортированных данных на временную ленту
            FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( k+1 ) +".txt" ).c_str(),"w");
            mtp.pos=0;
            for (int j = 0; j < ram; j++) {
                mtp.WriteFromRam(itape,fl,Mem[j]);
            }
            fclose(fl);
            cout<<k+1<<" temporary tape is sorted"<<endl;
        }
        //запись в последнюю ленту
        if(mtp.length%ram==0){
            int Mem[ram];
            for (int i = ram*(TapeCount-1); i < mtp.length; i++) {
                mtp.pos=i;
                mtp.Read(itape,input,fin);
                mtp.MoveRightOne(itape);
                Mem[i-ram*(TapeCount-1)]=mtp.ch;
            }
            int temp;
            //сортировка массива
            for (int i = 0; i < ram - 1; i++) {
                for (int j = 0; j < ram - i - 1; j++) {
                    if (Mem[j] > Mem[j + 1]) {
                        temp = Mem[j];
                        Mem[j] = Mem[j + 1];
                        Mem[j + 1] = temp;
                    }
                }
            }
            //запись
            FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( TapeCount ) +".txt" ).c_str(),"w");
            mtp.pos=0;
            for (int j = 0; j < ram; j++) {
                mtp.WriteFromRam(itape,fl,Mem[j]);
            }
            fclose(fl);
            cout<<TapeCount<<" temporary tape is sorted"<<endl;
        }else{
            int Mem[mtp.length%ram];
            for (int i = ram*(TapeCount-1); i < mtp.length; i++) {
                mtp.pos=i;
                mtp.Read(itape,input,fin);
                mtp.MoveRightOne(itape);
                Mem[i-ram*(TapeCount-1)]=mtp.ch;
            }
            int temp;
            //сортировка массива
            for (int i = 0; i < mtp.length%ram - 1; i++) {
                for (int j = 0; j < mtp.length%ram - i - 1; j++) {
                    if (Mem[j] > Mem[j + 1]) {
                        temp = Mem[j];
                        Mem[j] = Mem[j + 1];
                        Mem[j + 1] = temp;
                    }
                }
            }
            //запись
            FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( TapeCount ) +".txt" ).c_str(),"w");
            mtp.pos=0;
            for (int j = 0; j < mtp.length%ram; j++) {
                mtp.WriteFromRam(itape,fl,Mem[j]);
            }
            fclose(fl);
            cout<<TapeCount<<" temporary tape is sorted"<<endl;
        }
    }else{
        cout<<"Starting sorting tape..."<<endl;
        int Mem[mtp.length];
        for (int i = 0; i < mtp.length; i++) {
            mtp.pos=i;
            mtp.Read(itape,input,fin);
            mtp.MoveRightOne(itape);
            Mem[i]=mtp.ch;
        }
        int temp;
        //сортировка массива
        for (int i = 0; i < mtp.length - 1; i++) {
            for (int j = 0; j < mtp.length - i - 1; j++) {
                if (Mem[j] > Mem[j + 1]) {
                    // меняем элементы местами
                    temp = Mem[j];
                    Mem[j] = Mem[j + 1];
                    Mem[j + 1] = temp;
                }
            }
        }
        //запись
        FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( 1 ) +".txt" ).c_str(),"w");
        mtp.pos=0;
        for (int j = 0; j < mtp.length; j++) {
            mtp.WriteFromRam(itape,fl,Mem[j]);
        }
        fclose(fl);
        cout<<1<<" temporary tape is sorted"<<endl;
    }
}
//сортировка временных лент в одну выходную (берется первый элемент в каждой ленте, ищется минимальный.
// Минимальный элемент записывается в выходную ленту, а временная лента с этим элементов смещается вправо.
// Дальше идет проверка нового элемента с предыдущими в других временных лентах и так до того момента, когда все
// ленты дойдут до конца)
void sort::SortTapes(MyTape &mtp, iTape &itape, FILE *output) {
    string fin=itape.fin;
    string fout=itape.fout;
    int ch[TapeCount];
    int pos[TapeCount];
    for (int i = 0; i < TapeCount; i++) {
        pos[i]=0;
    }
    int sizeOfLastCh=mtp.length%ram;
    FILE* tmp[TapeCount];
    vector<int> idError,bufId;
    int flag=0;
    start:
    for (int i = 0; i < TapeCount; i++) {
        string fname=string("tmp\\tmpTape"+to_string(i+1)+".txt");
        tmp[i]=fopen(fname.c_str(),"r");
        mtp.pos=pos[i];
        mtp.Read(itape,tmp[i],fname);
        ch[i]=mtp.ch;
        fclose(tmp[i]);
    }
    int min=INT32_MAX;
    //проверка на то, что лента добежала до конца
    //если вектор из лент, которые добежали не пуст,
    //то данная лента не участвует в рассчете минимума
    for (int i = 0; i < TapeCount; i++) {
        flag=0;
        if(idError.empty()==false){
            for (int j = 0; j < idError.size(); j++) {
                if (i==idError.at(j)){
                    flag=1;
                }
            }
        }
        if(flag)
            continue;
        if(ch[i]<=min){
            min=ch[i];
        }
    }
    bufId.clear();
    bufId=idError;
    for (int i = 0; i < TapeCount; i++) {
        flag=0;
        //если временная лента добежала до конца, то ее скипаем и не записываем в выходную ленту
        if(bufId.empty()==false){
            for (int j = 0; j < bufId.size(); j++) {
                if (i==bufId.at(j)){
                    flag=1;
                }
            }
        }
        if(flag)
            continue;
        string fname=string("tmp\\tmpTape"+to_string(i+1)+".txt");
        tmp[i]=fopen(fname.c_str(),"r");
        //cout<<i<<" "<<ch[i]<<" "<<pos[i]<<" "<<min<<endl;
        cout<<"Processing..."<<endl;
        //если символ минимум, то записываем его в выходную ленту и смещаемся по этой ленте вправо
        if(ch[i]==min){
            mtp.pos=pos[i];
            if(((ram-1)==pos[i])||(((sizeOfLastCh-1)==pos[TapeCount-1])&&(i==TapeCount-1))){
                idError.push_back(i);
                mtp.Read(itape,tmp[i],fname);
                mtp.Write(itape,output);
            }else{
                mtp.Read(itape,tmp[i],fname);
                mtp.Write(itape,output);
                mtp.MoveRightOne(itape);
                pos[i]++;
            }
        }
        fclose(tmp[i]);
    }
    //если все ленты дошли до конца, то сортировка завершена
    if(min!=INT32_MAX){
        goto start;
    }
    cout<<"Done!";
}