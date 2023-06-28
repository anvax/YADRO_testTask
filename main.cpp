#include <iostream>
#include <vector>
#include "sort.h"
#include "Tape.h"

using namespace std;
const char* fname="config.txt";


int main() {
    string fin;
    string fout;
    cout<<"Enter the name of the input file (with .txt):"<<endl;
    cin>>fin;
    cout<<"Enter the name of the output file (with .txt):"<<endl;
    cin>>fout;
    FILE* cfg=fopen(fname,"r");
    FILE* input=fopen(fin.c_str(),"r");
    FILE* output=fopen(fout.c_str(),"w");
    if(cfg==NULL){
        cout<<"No config file"<<endl;
        exit(0);
    }else{
        cout<<"Config is open: "<<fname<<endl;
    }
    Tape tp;
    MyTape mtp;
    mtp.loadConfig(tp,cfg);
    fclose(cfg);
    mtp.ScanTape(tp,input);

    input=fopen(fin.c_str(),"r");
    sort sort;
    sort.tmpTapes(mtp);
    sort.sortEachTmpTape(mtp,tp,input);
    sort.SortTapes(mtp,tp,output);
    fclose(output);
    return 0;
}
