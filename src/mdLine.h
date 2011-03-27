/*
 *  mdLine.h
 *  MappingDraw
 *
 *  Created by mchrbn on 27.03.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */


#pragma once
#include "ofMain.h"

class mdLine{
	
	public:
		mdLine();
		void create(int x, int y);
		void draw();
		void updateP1(int x, int y);
		void updateP2(int x, int y);
		void drawPoint(int p);
		
		int x1;
		int y1;
		int x2;
		int y2;
		float width;
		
	private:
	
	
};

