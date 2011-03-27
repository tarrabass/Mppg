/*
 *  effectOne.cpp
 *  MappingDraw
 *
 *  Created by mchrbn on 27.03.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#include "effectOne.h"


void effectOne::apply(vector <mdLine> lns){
	lines = lns;
	noise = new Perlin(1,1.0,1.0, time(NULL));
}


void effectOne::draw(float sound){
	
	ofSetLineWidth(1);
	ofFill();
	ofSetColor(255, 255, 255);
	
	//Applique l'effet sur toutes les lignes
	for(int i=0; i<lines.size(); i++){
		
		int div = 10;
		
		int posx1 = lines[i].x1;
		int posy1 = lines[i].y1;
		int posx2 = lines[i].x2;
		int posy2 = lines[i].y2;
		 
		float dist = sqrt(ofDistSquared(posx1, posy1, posx2, posy2 ));
		
		float coeff = 256.0 / dist;
		float hight = 200.0 / coeff;
		float angle = atan2(double(posy2-posy1) , double(posx2-posx1));
		
		float mydegreangle = ofRadToDeg(angle);			
		
		
		glPushMatrix();
		ofTranslate(posx1, posy1,0);
		glColor3ub((unsigned char)255,(unsigned char)255,(unsigned char)255);
		glPointSize(2);
		ofRotateZ(mydegreangle);
		glBegin(GL_POINTS);
		for(int x = 1; x < dist; x +=4) {
			float tempx = noise->noise3((float)x/div,(float)0/div,ofGetFrameNum()/3)*sound*100;
			float tempy = noise->noise3((float)x/div,(float)0/div,ofGetFrameNum()/3)*sound*100;
			glVertex3f(x + tempx,tempy, 0);
		}
		glEnd();
		glPopMatrix();
	}
}