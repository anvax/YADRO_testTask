//
// Created by 1 on 28.06.2023.
//

#include "MyTape.h"
#include "windows.h"

void MyTape::loadConfig(iTape &itape, FILE *cfg) {
    itape.Configure(cfg,&wr,&r,&s);
}
void MyTape::ScanTape(iTape &itape, FILE *input) {
    itape.ScanTape(input,&length);
    fclose(input);
}
void MyTape::MoveLeftOne(iTape &itape) {
    itape.left1(&pos);
    Sleep(s);
}
void MyTape::MoveRightOne(iTape &itape) {
    itape.right1(&pos);
    Sleep(s);
}
void MyTape::MoveRight(iTape &itape, int count) {
    itape.RewindRight(&pos,count);
    Sleep(r);
}
void MyTape::MoveLeft(iTape &itape, int count) {
    itape.RewindLeft(&pos,count);
    Sleep(r);
}
void MyTape::Read(iTape &itape, FILE *input, std::string fname) {
    fclose(input);
    input=fopen(fname.c_str(),"r");
    itape.read(input,&pos,&ch,length);
    Sleep(wr);
}
void MyTape::Write(iTape &itape, FILE *output) {
    itape.write(output,&pos,&ch);
    Sleep(wr);
}
void  MyTape::WriteFromRam(iTape &itape, FILE *output, int symb) {
    itape.write(output,&pos,&symb);
    Sleep(wr);
}