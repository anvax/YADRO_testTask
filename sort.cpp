//
// Created by 1 on 28.06.2023.
//

#include "sort.h"
string fname="config.txt";
string fin="input.txt";
string fout="output.txt";

void sort::tmpTapes(MyTape &mtp) {
    if(mtp.length%ram==0){
        TapeCount=mtp.length/ram;
    }else{
        TapeCount=mtp.length/ram+1;
    }
    for (int i = 1; i <=TapeCount ; i++) {
        //ofstream file( string( "tmp\\tmpTape" + to_string( i ) +".txt" ).c_str());
        FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( i ) +".txt" ).c_str(),"w");
        //file.close();
        fclose(fl);
    }
}
void sort::sortEachTmpTape(MyTape &mtp, iTape &itape, FILE *input) {
    cout<<"Starting sorting temporary tapes..."<<endl;
    for (int k = 0; k < TapeCount-1; k++) {
        int Mem[ram];
        for (int i = ram*k; i < ram*(k+1); i++) {
            mtp.pos=i;
            mtp.Read(itape,input,fin);
            mtp.MoveRightOne(itape);
            Mem[i-ram*k]=mtp.ch;
        }
        int temp; // временная переменная для обмена элементов местами
        // Сортировка массива пузырьком
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
        //ofstream file( string( "tmp\\tmp" + to_string( k+1 ) +".txt" ).c_str());
        FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( k+1 ) +".txt" ).c_str(),"w");
        mtp.pos=0;
        for (int j = 0; j < ram; j++) {
            mtp.WriteFromRam(itape,fl,Mem[j]);
            //file<<Mem[j]<<' ';
        }
        fclose(fl);
        //file.close();
        cout<<k+1<<" temporary tape is sorted"<<endl;
    }
    if(mtp.length%ram==0){
        int Mem[ram];
        for (int i = ram*(TapeCount-1); i < mtp.length; i++) {
            mtp.pos=i;
            mtp.Read(itape,input,fin);
            mtp.MoveRightOne(itape);
            Mem[i-ram*(TapeCount-1)]=mtp.ch;
        }
        int temp;
        // Сортировка массива пузырьком
        for (int i = 0; i < ram - 1; i++) {
            for (int j = 0; j < ram - i - 1; j++) {
                if (Mem[j] > Mem[j + 1]) {
                    temp = Mem[j];
                    Mem[j] = Mem[j + 1];
                    Mem[j + 1] = temp;
                }
            }
        }
        FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( TapeCount ) +".txt" ).c_str(),"w");
        mtp.pos=0;
        //ofstream file( string( "tmp\\tmp" + to_string( TapeCount ) +".txt" ).c_str());
        for (int j = 0; j < ram; j++) {
            mtp.WriteFromRam(itape,fl,Mem[j]);
            //file<<Mem[j]<<' ';
        }
        fclose(fl);
        //file.close();
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
        // Сортировка массива пузырьком
        for (int i = 0; i < mtp.length%ram - 1; i++) {
            for (int j = 0; j < mtp.length%ram - i - 1; j++) {
                if (Mem[j] > Mem[j + 1]) {
                    temp = Mem[j];
                    Mem[j] = Mem[j + 1];
                    Mem[j + 1] = temp;
                }
            }
        }
        FILE* fl=fopen(string( "tmp\\tmpTape" + to_string( TapeCount ) +".txt" ).c_str(),"w");
        mtp.pos=0;
        //ofstream file( string( "tmp\\tmp" + to_string( TapeCount ) +".txt" ).c_str());
        for (int j = 0; j < ram; j++) {
            mtp.WriteFromRam(itape,fl,Mem[j]);
            //file<<Mem[j]<<' ';
        }
        fclose(fl);
        //file.close();
        cout<<TapeCount<<" temporary tape is sorted"<<endl;
    }
}
void sort::SortTapes(MyTape &mtp, iTape &itape, FILE *output) {
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
    if(min!=INT32_MAX){
        goto start;
    }
    cout<<"Done!";
}