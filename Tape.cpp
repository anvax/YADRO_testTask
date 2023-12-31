//
// Created by 1 on 28.06.2023.
//

#include "Tape.h"
void Tape::Configure(FILE* cfg,int *wr,int *r,int *s){
    char ch;
    string str,strwr,strr,strs;
    //считывание конфига
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
    //сканирование временной ленты на длину (разделители - пробелы)
    do{
        ch=fgetc(input);
        if(ch==EOF){
            break;
        }
        if(ch==' '){
            ch=fgetc(input);
            if (ch!=EOF && ((ch=='-')||(ch=='0')||(ch=='1')||(ch=='2')||(ch=='3')||(ch=='4')||(ch=='5')||(ch=='6')||(ch=='7')||(ch=='8')||(ch=='9'))){
                (*length)++;
            }else{
                break;
            }
        }
    }while (ch!=EOF);
    (*length)++;
}
void Tape::read(FILE *input, int *pos, int *ch, int length) {
    int position=*pos;
    //так как лента циклична, то нужна проверка на сброс прозиции:
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
    //считывание ячейки ленты
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
    //запись символа на выходную ленту
    string str=to_string(*ch);
    for(string::iterator it=str.begin();it!=str.end();it++){
        fputc(*it,output);
    }
    fputc(' ',output);
}
void Tape::left1(int *pos) {
    (*pos)--;//смещение влево по ленте
}
void Tape::right1(int *pos) {
    (*pos)++;//смещение вправо по ленте
}
void Tape::RewindLeft(int *pos, int count) {
    //смещение влево на несколько ячеек
    for (int i = 0; i < count; i++) {
        (*pos)--;
    }
}
void Tape::RewindRight(int *pos, int count) {
    //смещение вправо на несколько ячеек
    for (int i = 0; i < count; i++) {
        (*pos)++;
    }
}