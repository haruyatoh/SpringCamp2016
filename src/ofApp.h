#pragma once

#define NUM 5000

#include "ofMain.h"
#include "ofxLeapMotion2.h"

class ofApp : public ofBaseApp{
    
private:
    ofImage image;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void exit();
    
    ofBoxPrimitive box, mBox[NUM];
    
    int boxSize;
    
    
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    
    ofEasyCam cam;
    
    vector <ofVec3f> fingerPos;
    
    vector <ofPoint> handPos;
    
    ofSoundPlayer sound;
    int time;
    
    ofImage BackgroundImage;

};
