/* 
 * File:   ControlPanel.h
 * Author: Mathilde
 *
 * Created on 18 octobre 2016, 11:37
 */


#include <StandardCplusplus.h>
#include <vector>
#include "Button.h"

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

class ControlPanel {
 public: 
    int btnNumber;
    int btnNumberMax;
    std::vector<Button> btnList;
    
public:
    
    ControlPanel();
    ControlPanel(int);
    
    //getter
    //std::vector::size_type getBtnNumber();
    int getBtnNumberMax();
    std::vector<Button> getBtnList();
    
    //setters
    void setBtnNumberMax(int);
      
    //l'utilitaire du boutton
    void addButton(Button); 
    void reserve(int);
    void controlRead();
    //int toBinary();
    int analyze();
};

#endif /* CONTROLPANEL_H */

