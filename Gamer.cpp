//
//  Gamer.cpp
//  Panda
//
//  Created by Saga on /6/716.
//  Copyright © 2016 Zhenzhang. All rights reserved.
//

#include "Gamer.hpp"
#include <iostream>
#include <ctime>
#define INITIAL_POS 0.25

using namespace std;

void Gamer::setMatrix(float (*resultMatrix)[16]){
    std::memcpy(leftPanda, resultMatrix[0], sizeof(float)*16);
    std::memcpy(rightPanda, resultMatrix[1], sizeof(float)*16);
}

bool Gamer::isOver(){
    return (current_life==0);
}

void Gamer::gameOver(cv::Mat &img){
    CvFont font;
    double hScale=4;
    double vScale=4;
    int lineWidth=7;
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
    IplImage arr = img;
    char show_msg[11] = "Game Over!";
    cvPutText(&arr, show_msg, cv::Point(300,400),&font, cv::Scalar(205,0,0));
    img = cv::cvarrToMat(&arr);
}

void Gamer::playGame(std::vector<bool> &markers){
    if(current_pos == 1){
        markers[0] = true;
        markers[1] = false;
    }
    
    if(current_pos == 2){
        markers[0] = false;
        markers[1] = true;
    }
    
    if(markers[2] == false){
        markers[0] = true;
        markers[1] = false;
        current_pos = 1;
    }

    if(markers[3] == false){
        markers[0] = false;
        markers[1] = true;
        current_pos = 2;
    }
    count++;
    if(count%interval == 0){
        srand(rand());
        int a = rand()%5-2;
        int b = rand()%5-2;
        int left_num, right_num;
        if(a<0){
            left_num = -1;
        }else if (a==0){
            left_num = 0;
        }else{
            left_num =1;
        }
        if(b<0){
            right_num = -1;
        }else if (b==0){
            right_num = 0;
        }else{
            right_num =1;
        }
        if((left_num<0)&&(right_num <0)){
            if(rand()%2 == 0){
                left_num = 0;
            }else{
                right_num = 0;
            }
        }
        if((left_num == right_num)&&(left_num ==0)){
            if(rand()%2 ==0){
                if(rand()%2 ==0){
                    left_num = 1;
                }else{
                    left_num = -1;
                }
            }else{
                if(rand()%2 ==0){
                    right_num = 1;
                }else{
                    right_num = -1;
                }
                
            }
        }

        leftList.push_back(Stuff(left_num));
        rightList.push_back(Stuff(right_num));
        count = 1;
    }
    
}

void Gamer::drawStuff(){
    float tempLPanda[16],tempRPanda[16];
    std::memcpy(tempLPanda, leftPanda, sizeof(float)*16);
    std::memcpy(tempRPanda, rightPanda, sizeof(float)*16);
    std::list<Stuff>::iterator it;
    for(it = leftList.begin();it!=leftList.end();it++){
        tempLPanda[11] = leftPanda[11]+INITIAL_POS;
        getTrans(tempLPanda, it->step++);
        if(it->getType() == 1){
            it->drawBamboo(tempLPanda);
        }else if (it->getType()==-1){
            it->drawStone(tempLPanda);
        }
        if(it->step == step_max){
            if(current_pos == 1){
                if(it->getType() == 1){
                    current_grade++;
                }
                if(it->getType() == -1){
                    current_life--;
                }
            }
            leftList.pop_front();
        }
    }
    for(it = rightList.begin();it!=rightList.end();it++){
        tempRPanda[11] = rightPanda[11]+INITIAL_POS;
        getTrans(tempRPanda,it->step++);
        if(it->getType() == 1){
            it->drawBamboo(tempRPanda);
        }else if (it->getType()==-1){
            it->drawStone(tempRPanda);
        }
        if(it->step == step_max){
            if(current_pos == 2){
                if(it->getType() == 1){
                    current_grade++;
                }
                if(it->getType() == -1){
                    current_life--;
                }
            }
            rightList.pop_front();
        }
    }
}

void Gamer::showGold(cv::Mat &img){
    CvFont font;
    double hScale=2;
    double vScale=2;
    int lineWidth=3;
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
    IplImage arr = img;
    char show_msg[20] = "Grade: ";
    std::string s = std::to_string(current_grade);
    std::strcpy((show_msg+7), s.c_str());
    cvPutText(&arr, show_msg, cv::Point(900,100),&font, cv::Scalar(0,102,255));
    img = cv::cvarrToMat(&arr);
}

void Gamer::getTrans(float *matrix, double step){
    matrix[11] -= step/step_each;
}

void Gamer::showLife(cv::Mat &img){
    CvFont font;
    double hScale=2;
    double vScale=2;
    int lineWidth=3;
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
    IplImage arr = img;
    char show_msg[20] = "life: ";
    std::string s = std::to_string(current_life);
    std::strcpy((show_msg+6), s.c_str());
    cvPutText(&arr, show_msg, cv::Point(100,100),&font, cv::Scalar(51, 153, 51));
    img = cv::cvarrToMat(&arr);
}

void Gamer::playBGM(){
}

void Gamer::setDifficult(){
    if((current_grade>0)&&(current_grade<30)){
        if (current_grade/5 == current_level){
            current_level++;
            step_each -= 200;
            step_max = INITIAL_POS*step_each - 8*current_level;
        }
    }
}