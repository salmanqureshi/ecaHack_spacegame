#pragma once
#include "cocos2d.h"
void setSoundOpt(bool en);
void setMusicOpt(bool en);
void setControls(bool en);
void setHiScore(int score);
void addCrystals(int cry);
bool isSoundEnabled();
bool isMusicEnabled();
int getHightScore();
int getCrystals();
bool isAccelerometrControl();
void saveUD();
