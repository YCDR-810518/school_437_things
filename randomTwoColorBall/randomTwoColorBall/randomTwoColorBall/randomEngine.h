//
//  randomEngine.h
//  randomTwoColorBall
//
//  Created by 姚晨 on 2025/11/11.
//
#ifndef _RANDOMENGINE_H_
#define _RANDOMENGINE_H_
//将简单随机数组中的内容升序排列
void bubbleUp(int doubleR[]);
//随机抽取
void func01();
//幸运数字抽取
void lukyNumRandom(int lukyNum);
//高级随机
void pureRandom();
//单一红区高级随机生成（不启动引擎，需要初始化引擎）
vector<int>redBallrandom(int redBallseed);
//单一蓝区高级随机生成（不启动引擎，需要初始化引擎）
int blueBall(int blueballseed);
#endif // !_RANDOMENGINE_H_
