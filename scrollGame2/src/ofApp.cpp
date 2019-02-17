#include "ofApp.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#define PI 3.141592
//ランキング用の変数
char rankingName[20][10];//名前は最大20文字
char yourName[20];
int rankingScore[10];
//--------------------------------------------------------------
void ofApp::setup(){
    InitPageSound.load("init.mp3");
    MainGameSound.load("main.mp3");
    GameOverSound.load("gameOver.mp3");
    EndSound.load("end.mp3");
    
    
    FILE *fp;
    fp=fopen("rankingData.txt","r+");
    fp=fopen("../../../data/rankingData.txt","r+");
    
    if(fp==NULL){
        cout<<"no file"<<endl;
    }
    for(int i=0;i<10;i++){
        fscanf(fp,"%s %d",rankingName[i],&rankingScore[i]);
        cout<<"Name:"<<rankingName[i]<<" Score:"<<rankingScore[i]<<endl;
    }
    fclose(fp);
    DELAY(3);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofLogToConsole();
    ofSetFrameRate(60);
    ofBackground(255,255,255);
    ofEnableAlphaBlending();    //アルファチャネルを有効化
    backImage.load("backImage5.png");
    //金森先生の読み込み
    //kanamoriImage.load("kanamori.jpeg");
    kanamoriImage.load("koroyu.jpg");/////
    //矢印画像の読み込み
    yazirushiImage.load("yazirushi.png");
    //ゲームオーバー画像の読み込み
    gameOverImage.load("gameOver.png");
    PEYNImage.load("PEYN.png");
    //初期画面の画像の読み込み
    initImage.load("InitImage.png");
    //説明画像の読み込み
    setumeiImage.load("setumei.png");
    
    //コイン系
    for(int i=0;i<upCoinsNum;i++){
        upCoins[i].position.x=ofRandom(5000,45000);
        upCoins[i].position.y=ofRandom(200,10000);
        upCoins[i].positionInit=upCoins[i].position;
    }
    
    //Box2Dのセットアップ
    /*
     box2d.init();//Box2Dの世界を初期化
     box2d.setGravity(0,-10);//重力を下向きに10
     box2d.setFPS(30);
     */
    
    //主人公のセットアップ
    hero.position.set(heroPositionFirstX,heroPositionFirstY);
    hero.velocity.set(0,0);
    hero.acceleration.set(0,0);
    //heroCircle.setPhysics(2.0, 0.9, 1.5);  // 円の物理パラメータを設定 (重さ、反発係数、摩擦係数)
    //heroCircle.setup(box2d.getWorld(), heroPositionFirstX, heroPositionFirstY, heroRadius); // 円を物理世界に置く(Box2dの世界,座標(x,y),半径)
    
    //主人公が最初に乗る台のセットアップ
    //rectInitOn.setPhysics(0.0,0,1.5);//物理パラメータを設定 (重さ、反発係数、摩擦係数)
    //rectInitOn.setup(box2d.getWorld(),heroPositionFirstX-30, heroPositionFirstY-100,100,30);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(flagLoopAddStop==0){
        loop++;
        hitPower=(MaxPower/2)*(1-cos(double(loop)/5));//5が逆数速度
    }else if(flagLoopAddStop==1){
        loop++;
        angle=(PI*cos(double(loop)/8)+PI)/PI;//5が逆数速度
    }else if(flagLoopAddStop>=2){
        hero.velocity+={float(hitPower/10)*float(cos(angle)),float(hitPower/10)*float(sin(angle))};
        hero.acceleration.y-=9.8;
    }
    //時間の処理
    msDiff=1/float(ofGetFrameRate());
    if(msDiff>1){
        msDiff=msDiffBefore;
    }else{
        msDiffBefore=msDiff;
    }
    //cout<<"timeDiff:"<<msDiff<<endl;
    //時間を元にしたheroの情報の更新
    if(gameOverFlag!=1){
        hero.velocity+=hero.acceleration*msDiff;
        hero.position+=0.5*hero.acceleration*msDiff*msDiff+hero.velocity*msDiff;
        
        //~~~ここでコインの位置の計算と補正をする
        for(int i=0;i<upCoinsNum;i++){
            upCoins[i].position.x=upCoins[i].positionInit.x-(hero.position.x-heroPositionFirstX);
            upCoins[i].position.y=upCoins[i].positionInit.y-(hero.position.y-heroPositionFirstY);
        }
    }
    //cout<<"a:"<<hero.acceleration<<endl;
    //cout<<"v:"<<hero.velocity<<endl;
    //cout<<"p:"<<hero.position<<endl;
    
    diffScrolX=hero.position.x-heroPositionFirstX;
    diffScrolY=hero.position.y-heroPositionFirstY;
    if((hero.position.y<heroPositionFirstY)||(gameOverFlag==1)){//元の位置より下に行ってしまったときの処理,
        hero.position.y=heroPositionFirstY;
        hero.velocity={0,0};
        hero.acceleration={0,0};
        gameOverFlag=1;
        //この時処理を止めて，ゲーム終了にする
    }
    if(hero.position.x<=0){
        hero.position.x=0;
        hero.velocity={0,0};
        hero.acceleration={0,0};
        gameOverFlag=1;
    }
    //box2d.update();
    //hero.position=heroCircle.getPosition();
    
    //スコアの更新
    score=hero.position.x-heroPositionFirstX;
    
    if(gameOverFlag==1){
        youAreWritingYourNameFlag=1;
        if(score>rankingScore[9]&&newRankeWritedFlag==0){//スコアが10位の人のよりも良ければ
            if(youAreWritingYourNameFinishedFlag==1){
                newRankeWritedFlag++;
                FILE *fpNewRank;
                fpNewRank=fopen("../../../data/rankingData.txt","w");
                if(fpNewRank==NULL){
                    printf("テキストファイルがありません\n");
                }
                //名前を入力させる
                //printf("あなたの名前を教えてください\n");
                //scanf("%s",yourName);
                int countRankBefore=0;
                for(int rankCount=0;rankCount<10;rankCount++){
                    if(score>rankingScore[rankCount]&&(yourRankWroteFlag==0)){
                        fprintf(fpNewRank, "%s %d\n", yourName, score);
                        yourRankWroteFlag++;
                    }else{
                        fprintf(fpNewRank,"%s %d\n", rankingName[countRankBefore], rankingScore[countRankBefore]);
                        countRankBefore++;
                    }
                }
                fclose(fpNewRank);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(initedFlag==0){
        if(InitedPageSoundFlag==0){
            InitPageSound.play();
            InitedPageSoundFlag++;
        }
        initImage.draw(0,0,1500,1000);
        setumeiImage.draw(700,350,600,400);
        for(int i=0;i<10;i++){
            rankingText[i].load("HelveticaNeue.ttc",24);
        }
        
        ofPushMatrix();
        ofTranslate(250,400);
        for(int i=0;i<10;i++){
            rankingText[i].drawString(ofToString(rankingName[i]),0,i*45);
        }
        ofTranslate(150,0);
        for(int i=0;i<10;i++){
            rankingText[i].drawString(ofToString(rankingScore[i]),0,i*45);
        }
        ofPopMatrix();
        
    }else if(gameOverFlag==1){
        if(GameOverSoundFlag==0){
            GameOverSoundFlag++;
            MainGameSound.stop();
            EndSound.play();
        }
        youAreWritingYourNameFlag=1;
        sleep(1);
        gameOverImage.draw(0,0,1500,1000);
        
        ofPushMatrix();
        PleaseEnterYourNameText.load("HelveticaNeue.ttc",36);
        yourNameText.load("HelveticaNeue.ttc",36);
        ofSetColor(255,0,0);
        //PleaseEnterYourNameText.drawString(yourName, 500, 500);
        PleaseEnterYourNameText.drawString("Plese enter your name and press 'ENTER' (Restar:'r')", 100, 100);
        if(youAreWritingYourNameFinishedFlag==0){
            yourNameText.drawString(yourName, 100, 200);
        }else{
            yourNameText.drawString(ofToString(yourName)+", your score is "+ofToString(score)+"!", 100, 200);
        }
        ofPopMatrix();
    }else{//メインシーン
        if(MainGameSoundFlag==0){
            MainGameSoundFlag++;
            InitPageSound.stop();
            MainGameSound.play();
        }
        ofSetColor(255,255,255);
        backImage.draw(-diffScrolX,diffScrolY-10000+1000,45000,10000);//
        
        //座標軸の変更
        ofScale(1, -1);
        ofTranslate(0,-ofGetHeight());
        //主人公
        ofSetColor(0,255,50);
        ofCircle(heroPositionFirstX,heroPositionFirstY, heroRadius);
        //heroCircle.draw();
        
        //主人公が乗る台を設定
        //ofSetColor(0,0,250);
        //rectInitOn.draw();
        
        //主人公が今いる位置に金森先生の写真を描画する
        ofPushMatrix();
        ofSetColor(255,255,255);
        //kanamoriImage.draw(heroPositionFirstX-15,heroPositionFirstY+15,37,-50);/////
        kanamoriImage.draw(heroPositionFirstX-15,heroPositionFirstY+15,50,-50);
        ofPopMatrix();
        
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 20, 20);
        
        //パワーバーを追加
        ofPushMatrix();
        ofTranslate(10,ofGetHeight()-40);
        ofSetColor(255,0,0);
        ofDrawBitmapString("power", 0, 0);
        ofTranslate(50,0);
        ofRect(0,0,hitPower,15);
        ofPopMatrix();
        
        //角度バーの追加
        ofPushMatrix();
        ofTranslate(10,ofGetHeight()-70);
        ofSetColor(255,0,0);
        ofDrawBitmapString("angle", 0, 0);
        ofTranslate(50,0);
        ofRect(0,0,angle*100,15);
        ofPopMatrix();
        
        //矢印の描画
        if(flagLoopAddStop<=1){
            ofPushMatrix();
            ofTranslate(heroPositionFirstX,heroPositionFirstY);
            ofTranslate(50,0);
            ofRotateZRad(angle);
            yazirushiImage.draw(0,0,150,100);
            ofPopMatrix();
        }
        
        //何m飛んだかの記録
        ofPushMatrix();
        ofTranslate(10,ofGetHeight()-100);
        ofSetColor(0,0,0);
        ofDrawBitmapString("score: "+ofToString(score), 0, 0);
        ofPopMatrix();
        
        //コインの描画
        //upCoins
        for(int i=0;i<upCoinsNum;i++){
            ofSetColor(0,255,255);
            upCoins[i].drawUpCoins();
            ofSetColor(255,255,255);
        }
        //コインと主人公との距離がCoinsRadius以下なら~CoinsGetFlagを立てる
        for(int i=0;i<upCoinsNum;i++){
            if(upCoins[i].position.distance(hero.position)<CoinRadius){//接触したとき|||||
                int upVelo=500;
                if(hero.velocity.y>0){//上に向いて進んでいるとき
                    hero.velocity.y+=upVelo;
                }else{//下に向いて進んでいる時
                    hero.velocity.y=upVelo;
                }
                cout<<"up"<<endl;
            }
        }
        ofSetColor(255,0,0);//ここでGameOverの色が決まる
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(youAreWritingYourNameFinishedFlag==1){
        switch(key){
            case 'r':
                restartApp.initRestart(2);
                break;
        }
    }
    if((youAreWritingYourNameFlag!=0)&&(youAreWritingYourNameFinishedFlag==0)){
        if(key==OF_KEY_RETURN){
            youAreWritingYourNameFinishedFlag=1;
        }else{
            yourName[yourNameCount]=key;
            yourNameCount++;
        }
        
    }else if(youAreWritingYourNameFlag==0){
        switch(key){
            case OF_KEY_RIGHT:
                hero.position.x+=100;
                break;
            case OF_KEY_LEFT:
                hero.position.x-=100;
                break;
            case OF_KEY_UP:
                hero.position.y+=100;
                break;
            case OF_KEY_DOWN:
                hero.position.y-=100;
                break;
            case OF_KEY_RETURN:
                flagLoopAddStop++;
                break;
            case 'g':
                hero.acceleration.y-=9.8*50;
                break;
            case 's':
                initedFlag=1;
                break;
            case 'f':
                tempFlag=1;
                tempVelocity=hero.velocity;
                tempAcceleration=hero.acceleration;
                hero.velocity+={1000,1000};
                break;
            case 'r':
                restartApp.initRestart(2);
                break;
            case 'j'://落下中にjを押した時に2回までジャンプできる(落下中じゃないと，速度が大きくなりすぎてゲームバランスが悪い)
                if(JUsedFlag<=2&&hero.velocity.y<0){
                    JUsedFlag++;
                    hero.velocity.y+=3000;
                }else{
                    JUsedFlag++;
                }
        }
        //cout<<hero.position<<endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

/////////

