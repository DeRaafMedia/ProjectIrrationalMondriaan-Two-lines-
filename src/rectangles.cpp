//
//  rectangels.cpp
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 18-11-14.
//
//

#include "rectangles.h"

void rectangles::draw(string squareId,
                      int initXAxis,
                      int initYAxis,
                      int initWidth,
                      int initHeight,
                      int initRed,
                      int initGeen,
                      int initBlue,
                      int initRotation,
                      bool showSquaresId,
                      bool oscEnabled){
    
    ofPushMatrix();
        ofTranslate(initXAxis, initYAxis);
        ofSetColor(initRed, initGeen, initBlue);
        ofRotate(initRotation);
        ofDrawRectangle(0, 0, initWidth, initHeight);
    ofPopMatrix();
}