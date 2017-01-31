
/* 
 * File:   ControlPanel.cpp
 * Author: Mathilde
 * 
 * Created on 18 octobre 2016, 11:37
 */

#include <map>
#include "vector"
#include <math.h>
#include <iostream>
#include "Arduino.h"
#include "ControlPanel.h"
#include "Button.h"


// constructors
ControlPanel::ControlPanel() {

}

ControlPanel::ControlPanel(int newBtnNumberMax) {
    this->btnList.reserve(newBtnNumberMax);
}

//getter
/*
std::vector::size_type ControlPanel::getBtnNumber(){
    return this->btnList.size;
}*/

int ControlPanel::getBtnNumberMax(){
    return this->btnList.capacity();
}

std::vector<Button> ControlPanel::getBtnList() {
    return this->btnList;
}

//setters

void ControlPanel::setBtnNumberMax(int newBtnNumberMax){
    this->btnList.reserve(newBtnNumberMax);
}

//functions

void ControlPanel::addButton(Button newBtn){ 
        this->btnList.push_back(newBtn);  
}

void ControlPanel::reserve(int newBtnNumberMax){
    this->btnList.reserve(newBtnNumberMax);
}

void ControlPanel::controlRead(){
    for (auto &btn: this->btnList){
        btn.readValue();
    }
}

//int ControlPanel::toBinary(){
//    int count=0;
//    int binary=0;
//
//    controlRead();
//    for (auto &btn: this->btnList){
//        if(btn.getValue() == LOW){
//            binary = binary + pow(10,count);
//        }
//        count++;
//    }
//    return binary;
//}

int ControlPanel::analyze(){
    controlRead();
    
    if(this->btnList[0].value == LOW){
      return 1;
    }
    else if(this->btnList[1].value == LOW){
      return 2;
    }
    else if(this->btnList[2].value == LOW){
      return 3;
    }
    else if(this->btnList[3].value == LOW){
      return 4;
    }
    else if(this->btnList[4].value == LOW){
      return 5;
    }else{
      return 0;
    }
    
}

