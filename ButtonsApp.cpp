//
//  ButtonsApp.cpp
//  ButtonsForArduino
//
/*
 Buttons for Arduino is licensed under the BSD 3-Clause License
 http://www.opensource.org/licenses/BSD-3-Clause
 
 Buttons for Arduino Copyright (c) 2011, RobotGrrl.com. All rights reserved.
 */

#include "ButtonsApp.h"

ButtonsApp::ButtonsApp() {
}


void ButtonsApp::begin() {
    
    for (int i=0; i<12; i++) {
        inv[i] = false;
    }
    
    Serial.begin(115200);
    
    for(int i=2; i<14; i++) {
        pinMode(i, OUTPUT);
    }
    
}


void ButtonsApp::refresh() {
    
    if(Serial.available() > 0) {
        msg[p] = Serial.read();
        p++;
    }
    
    if(p == LEN) {
        p = 0;
        
        for(int i=0; i<LEN; i++) {
            char c = msg[i];
            if(c == 'P') {
                if(i < 9) parseMessage(i);
                break;
            }
        }
        
        for(int i=0; i<LEN; i++) {
            msg[i] = '/';
        }
        
        Serial.flush();
        
    }
    
}


void ButtonsApp::setInverted(int pin)  {
    inv[pin-2] = true;
}


void ButtonsApp::lastButton(int &pin, int &val, int &type) {
    pin = _pin;
    val = _val;
    type = _type;
}


void ButtonsApp::parseMessage(int i) {
    _pin = (((int)msg[i+1]-48)*10) + ((int)msg[i+2]-48);
    _type = msg[i+3];
    _val = (((int)msg[i+4]-48)*1000) + (((int)msg[i+5]-48)*100) + (((int)msg[i+6]-48)*10) + ((int)msg[i+7]-48);
    
    switch (_type) {
            
        case 'B': {
            
            if(_val == 0) {
                
                if(inv[_pin-2]) {
                    digitalWrite(_pin, HIGH);
                } else {
                    digitalWrite(_pin, LOW);
                }
                
            } else {
                
                if(inv[_pin-2]) {
                    digitalWrite(_pin, LOW);
                } else {
                    digitalWrite(_pin, HIGH);
                }
                
            }
            
            break;
        }
            
        case 'R': {
            
            if(inv[_pin-2]) _val = 255-_val;
            analogWrite(_pin, _val);
            
            break;
        }
        default:
            break;
    }
    
}
