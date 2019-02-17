#pragma once

#include "ofMain.h"
#include "Coins.hpp"
#include "ofxBox2D.h"
#include "ofxRestartOFApp.h"



class Hero{
public:
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
};


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    //時間関連
    ofxRestartOFApp        restartApp;
    int loop=0;//loop回数を保存する
    double msBefore=0;
    double msNow=0;
    double msDiff=0.0166667;
    double msDiffBefore=0.0166667;
    int tempFlag=0;//一回だけ速度や加速度を変えたりする時に立てるフラグ,2まで増えたら元に戻す
    ofVec2f tempVelocity={0,0};
    ofVec2f tempAcceleration={0,0};
    int initedFlag=0;
    ofImage initImage;
    int youAreWritingYourNameFlag=0;
    int youAreWritingYourNameFinishedFlag=0;
    int yourNameCount=0;
    //背景画像関連
    ofImage backImage;
    double diffScrolX=0;
    double diffScrolY=0;
    
    //主人公
    Hero hero;
    double heroPositionFirstX=300;
    double heroPositionFirstY=100;
    int heroRadius=10;
    int MaxPower=200;
    int hitPower=0;
    double angle=0;
    int flagPowerOned=0;
    int flagLoopAddStop=0;
    int gameOverFlag=0;
    int score=0;
    int JUsedFlag=0;
    int newRankeWritedFlag=0;
    int yourRankWroteFlag=0;
    ofTrueTypeFont PleaseEnterYourNameText;
    ofTrueTypeFont yourNameText;
    ofTrueTypeFont rankingText[10];
    //金森先生
    ofImage kanamoriImage;
    //矢印
    ofImage yazirushiImage;
    
    //box2dのインスタンス化
    //ofxBox2d box2d;
    //主人公の円を描く
    //ofxBox2dCircle heroCircle;
    
    //主人公が最初に乗る台
    //ofxBox2dRect rectInitOn;
    
    //ゲームオーバー画面
    ofImage gameOverImage;
    ofImage PEYNImage;
    
    
    double absReFunction(int inputX,int loopNum,double height);
    
    //ここから他のオブジェクトの作成
    VelocityUpCoin upCoins[upCoinsNum];
    
    //音
    ofSoundPlayer InitPageSound;
    int InitedPageSoundFlag=0;
    ofSoundPlayer MainGameSound;
    int MainGameSoundFlag=0;
    ofSoundPlayer GameOverSound;
    ofSoundPlayer EndSound;
    int GameOverSoundFlag=0;
    
    //説明
    ofImage setumeiImage;
};



