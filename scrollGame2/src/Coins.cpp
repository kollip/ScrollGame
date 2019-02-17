//
//  Coins.cpp
//  scrollGame2
//
//  Created by 頃安祐輔 on 2019/02/16.
//

#include "Coins.hpp"
void VelocityUpCoin::drawUpCoins(){
    ofSetColor(255,255,0);
    ofCircle(this->position.x,this->position.y,CoinRadius);
}
