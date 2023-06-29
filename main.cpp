#include <iostream>
#include <vector>
#include "sort.h"
#include "Tape.h"

using namespace std;


int main() {
    Tape tp;
    MyTape mtp;
    sort sort;
    sort.removeTmpTapes();
    cout<<"Enter the name of the input file (with .txt):"<<endl;
    cin>>tp.fin;
    cout<<"Enter the name of the output file (with .txt):"<<endl;
    cin>>tp.fout;

    FILE* cfg=fopen(tp.fname.c_str(),"r");
    FILE* input=fopen(tp.fin.c_str(),"r");
    FILE* output=fopen(tp.fout.c_str(),"w");

    if(cfg==NULL){
        cout<<"No config file"<<endl;
        exit(0);
    }else{
        cout<<"Config is open: "<<tp.fname.c_str()<<endl;
    }

    mtp.loadConfig(tp,cfg);
    fclose(cfg);
    mtp.ScanTape(tp,input);
    input=fopen(tp.fin.c_str(),"r");
    sort.tmpTapes(mtp);
    sort.sortEachTmpTape(mtp,tp,input);
    sort.SortTapes(mtp,tp,output);

    fclose(output);
    return 0;
}
