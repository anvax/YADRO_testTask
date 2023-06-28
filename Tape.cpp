//
// Created by 1 on 28.06.2023.
//

#include "Tape.h"
void Tape::Configure(FILE* cfg,int *wr,int *r,int *s){
    char ch;
    string str,strwr,strr,strs;
    do{
        if (ch==10){
            str="";
        }
        if(ch==EOF)
            break;
        ch=fgetc(cfg);
        str+=ch;
        if (str=="Write/Read"){
            ch=fgetc(cfg);
            ch=fgetc(cfg);
            while (isdigit(ch)){
                strwr+=ch;
                ch=fgetc(cfg);
            }
        }
        if (str=="Rewind"){
            ch=fgetc(cfg);
            ch=fgetc(cfg);
            while (isdigit(ch)){
                strr+=ch;
                ch=fgetc(cfg);
            }
        }
        if (str=="Shift"){
            ch=fgetc(cfg);
            ch=fgetc(cfg);
            while (isdigit(ch)){
                strs+=ch;
                ch=fgetc(cfg);
            }
        }
    }while (ch!=EOF);
    *wr=stoi(strwr);
    *r=stoi(strr);
    *s=stoi(strs);
}
void Tape::ScanTape(FILE *input, int *length) {
    char ch;
    do{
        ch=fgetc(input);
        if(ch==' '){
            (*length)++;
        }
    }while (ch!=EOF);
}
void Tape::read(FILE *input, int *pos, int *ch, int length) {
    int position=*pos;
    if(abs(position)<length){
        if (position<0)
            (*pos)=length-abs(position);
        else
            (*pos)=position;
    }else{
        if (position<0){
            int mod=abs(position)%length;
            (*pos)=length-abs(mod);
        }
        else{
            int mod=position%length;
            (*pos)=mod;
        }
    }
    char symb;
    string num;
    int count=0;
    do{
        symb=fgetc(input);
        if(symb==EOF){
            break;
        }
        num+=symb;
        if(symb==' '){
            if((*pos)==count){
                break;
            }else{
                count++;
                num="";
            }
        }
    }while (symb!=EOF);
    (*ch)=stoi(num);
}
void Tape::write(FILE *output, int *pos, int *ch) {
    string str=to_string(*ch);
    for(string::iterator it=str.begin();it!=str.end();it++){
        fputc(*it,output);
    }
    fputc(' ',output);
}
void Tape::left1(int *pos) {
    (*pos)--;
}
void Tape::right1(int *pos) {
    (*pos)++;
}
void Tape::RewindLeft(int *pos, int count) {
    for (int i = 0; i < count; i++) {
        (*pos)--;
    }
}
void Tape::RewindRight(int *pos, int count) {
    for (int i = 0; i < count; i++) {
        (*pos)++;
    }
}