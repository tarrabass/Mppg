#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "mdLine.h"
#include "effectOne.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	private:
		vector <mdLine> lines;
		mdLine curLine;
		bool editMode;
		int curLineEdit;
		int curPointEdit;
		
		int curEffect;
		effectOne ef1;
		void effectSelection();
	
		float * left;
		float myDiv;
		int numBands;
		float averFFT;
		void audioReceived(float * input, int bufferSize, int nChannels);
};

#endif
