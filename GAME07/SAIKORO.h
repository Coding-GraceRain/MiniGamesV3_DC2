#pragma once
class SAIKORO
{
protected:
    int Img[7] = { 0 };//画像
    int A = 0,B = 0,C = 0;//サイコロ1,2,3
    int num[2] = { 3,5 };// 0:さいころを振る回数の管理 1:ラウンド数の管理
    int cnt[11] = { 0 };//  0:さいころを振る回数の管理 1:ラウンド数の管理
    int Coin = 1000;//持ち金
    int Coinkake = 50;//掛け金
    int Yaku = 0;//サイコロの役
    int Flag[3] = {};
    int i = 0;
public:
    int create();
    void set(int x, int y,int n);
    void judge(int x,int y);
    void init();
    void reset();
    int yakur();
    int flagr();
    int Coinr();
    void kari(int x,int y);
    void kakekin();
    int kaker();
    void kakef();
    void kakekati(int n);
    void kakemake(int n);
    void syouhai(int p1, int p2, SAIKORO* n1,SAIKORO*n2);
    void kakekinf();
    //int* saigazou();
    void saihyouzi();

};

