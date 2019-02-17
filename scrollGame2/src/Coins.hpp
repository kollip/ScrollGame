//
//  Coins.hpp
//  scrollGame2
//
//  Created by 頃安祐輔 on 2019/02/16.
//

#ifndef Coins_hpp
#define Coins_hpp

#include <stdio.h>
#include "ofMain.h"

#define upCoinsNum 500
#define CoinRadius 100

int velocityUpCoinGetFlag=0;

class VelocityUpCoin{
public:
    ofVec2f position;
    ofVec2f positionInit;
    int upVelocity=10;//ここを帰ると，ここに触れた時に上昇する感じが増える
    void drawUpCoins();
};
#endif /* Coins_hpp */
