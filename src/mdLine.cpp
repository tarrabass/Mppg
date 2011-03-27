/*
 *  mdLine.cpp
 *  MappingDraw
 *
 *  Created by mchrbn on 27.03.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#include "mdLine.h"

mdLine::mdLine(){
	x1=0;
	x2=0;
	y1=0;
	y2=0;
}

void mdLine::create(int x, int y){
	
	x1 = x;
	x2 = x;
	y1 = y;
	y2 = y;
	
	width = 1;
	
}

void mdLine::draw(){
	
	ofSetLineWidth(width);
	
	ofFill();
	ofSetColor(255, 255, 255);
	ofLine(x1, y1, x2, y2);
}

void mdLine::drawPoint(int p){
	
	
	ofNoFill();
	ofSetColor(255, 0, 0);
	
	if(p == 0)
		ofCircle(x1, y1, 5);
	else
		ofCircle(x2, y2, 5);
}

void mdLine::updateP1(int x, int y){
	x1 = x;
	y1 = y;
}

void mdLine::updateP2(int x, int y){
	x2 = x;
	y2 = y;
}