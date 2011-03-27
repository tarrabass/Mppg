/**
 
 Pour utiliser:
 
 - dessiner des traits
 - pour les éditer, appuye sur 'e' pour entrer dans le mode édition (rappuyer sur 'e' pour sortir du mode édition)
 - les flèches haut ou bas pour changer le trait à éditer
 - les flèches gauche ou droit pour changer le point du trait à éditer
 - pour supprimer un trait faut appuyer sur 'd' (dans le mode édition)
 
 
 Mapper les touches dans fonction keyPressed
 
 Utiliser effectSelection pour faire appel au draw des fonctions d'effet
 
 */


#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	
	editMode = false;
	curLineEdit = 0;
	curPointEdit = 0;
	curEffect = 0;
	
	///// Sound Analyse /////
	numBands = 256;
	ofSoundStreamSetup(0,2,this, 44100, numBands, 4);	
	left = new float[numBands];
	myDiv = 10;
	////////////////////////	
}

//--------------------------------------------------------------
void testApp::update(){
	
	float totalFFT = 0;
	
	for(int i=0; i<numBands; i++){
		//		totalFFT += fftList[i]*50;
		totalFFT += left[i]*10;
		
	}
	
	averFFT = totalFFT / numBands;
	int soundVelocity =  abs((int)(averFFT*100));
	
	
	float soundVelocityVoulu = ((float)soundVelocity/100);
	
	float diff = soundVelocityVoulu - myDiv;
	myDiv += diff / 10;
	
	printf("%f\n", myDiv);

}

//--------------------------------------------------------------
void testApp::draw(){
	if(!editMode){
		//Affiche l'effect choisi.
		curLine.draw();
	}
	
	effectSelection();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_UP && editMode){
		curLineEdit++;
		if(curLineEdit == lines.size()){
			curLineEdit = 0;
		}
	}
	else if(key == OF_KEY_DOWN && editMode){
		curLineEdit--;
		if(curLineEdit == -1){
			curLineEdit = lines.size()-1;
		}
	}
	else if(key == OF_KEY_RIGHT && editMode){
		curPointEdit = 1;
	}
	else if(key == OF_KEY_LEFT && editMode){
		curPointEdit = 0;
	}
	else if(key == 'e'){
		if (editMode){
			editMode = false;
			curLine.x1 = 0;
			curLine.x2 = 0;
			curLine.y1 = 0;
			curLine.y2 = 0;
		}
		else{
			editMode = true;
			curLineEdit = 0;
			curPointEdit = 0;
			//Repasse en mode sans effets
			curEffect = 0;
		}
	}
	else if(key == 'd'){
		if(editMode){
			lines.erase(lines.begin() + curLineEdit);
			if(curLineEdit == lines.size()){
				curLineEdit--;
			}
		}
	}
	else if(key == '0'){
		curEffect = 0;
	}
	else if(key == '1'){
		//Variable pour dire quel effets est sélectionné
		curEffect = 1;
		//Applique l'effet sur la liste des vecteurs
		ef1.apply(lines);
	}
	//Ajouter les autres effets ici en mappant d'autres touches
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(!editMode){
		curLine.updateP2(mouseX, mouseY);
	}
	else{
		if(curPointEdit == 0){
			lines[curLineEdit].updateP1(mouseX, mouseY);
		}
		else{
			lines[curLineEdit].updateP2(mouseX, mouseY);
		}
	}

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!editMode){
		curLine.create(mouseX, mouseY);
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(!editMode){
		if((curLine.x1 != curLine.x2) || (curLine.y1 != curLine.y2)){
			lines.push_back(curLine);
		}
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

/*
	Effect: ajouter les autres effets ici avec le case
 */
void testApp::effectSelection(){
	switch (curEffect) {
		//Pas d'effets, affiche les lignes normales
		case 0:
			for(int i=0; i<lines.size(); i++){
				if(i == curLineEdit && editMode){
					lines[i].draw();
					lines[i].drawPoint(curPointEdit);
				}
				else {
					lines[i].draw();
				}
				
			}
			break;
		//Effet 1
		case 1:
			//printf("%f\n", myDiv);
			ef1.draw(myDiv);
			break;
		default:
			break;
	}
}



void testApp::audioReceived(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
	}
}
