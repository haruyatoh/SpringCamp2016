#include "ofApp.h"

float circle_centerZ;
float formerZ;

bool ball_thrown;
int camera_mode;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(600,400);
    ofSetFrameRate(30);
    ofBackground(0, 80, 0);
    ofSetColor(255);
    image.load("earth.jpg");
    
    ofSetVerticalSync(true);
    cam.setOrientation(ofPoint(0,0,0));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    leap.open();
    
    boxSize = 10;
    for (int i=0; i<NUM; i++){
        mBox[i].setPosition(ofRandom(-4000,4000),ofRandom(-1000,1000),ofRandom(-4000,4000));
        mBox[i].set(boxSize);
        
    }
    sound.load("FLASH.mp3");
    sound.play();
    
    ball_thrown = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    simpleHands = leap.getSimpleHands();
    if(leap.isFrameNew() && simpleHands.size()){
        fingerPos.clear();
        
        handPos.clear();
        
        leap.setMappingX(-230,230,-ofGetWidth()/2,ofGetWidth()/2);
        leap.setMappingY(90,490,-ofGetHeight()/2,ofGetHeight()/2);
        leap.setMappingZ(-150,150,-200,200);
        
        fingerType fingerTypes[] = {THUMB,INDEX,MIDDLE,RING,PINKY};
        
        
        for(int i = 0; i <simpleHands.size(); i++){
            handPos.push_back(simpleHands[i].handPos);
            for(int f=0; f<5; f++){
                ofPoint mcp = simpleHands[i].fingers[fingerTypes[f]].mcp;
                fingerPos.push_back(mcp);
                
                ofPoint pip = simpleHands[i].fingers[fingerTypes[f]].pip;
                fingerPos.push_back(pip);
                
                ofPoint dip = simpleHands[i].fingers[fingerTypes[f]].dip;
                fingerPos.push_back(dip);
                
                ofPoint tip = simpleHands[i].fingers[fingerTypes[f]].tip;
                fingerPos.push_back(tip);
                
                
            }
        }
        
        
        
        if(simpleHands.size() == 2 && ball_thrown == false){
            if(ofDist(handPos.at(0).x,handPos.at(0).y,handPos.at(1).x,handPos.at(1).y)>800){
                circle_centerZ = -3000;
                ball_thrown = true;
            }else{
                
                circle_centerZ = (handPos.at(0).z+handPos.at(1).z)/2;
                cam.setOrientation(ofPoint(0,0,0));
            }
            formerZ = (handPos.at(0).z+handPos.at(1).z)/2;
        }
        
        if(simpleHands.size() == 2 && ball_thrown == true){
            time++;
            circle_centerZ =  - time*50;
            cam.setPosition((handPos.at(0).x+handPos.at(1).x)/2, (handPos.at(0).y+handPos.at(1).y)/2, circle_centerZ+200);
            
            if(circle_centerZ < -3000 || simpleHands.size() == 0){
                time =0;
                ball_thrown = false;
                circle_centerZ = 0;
                cam.setOrientation(ofPoint(0,0,0));
                cam.setPosition(0, 0, 500);
            }
            
        }
        
    }
    
    leap.markFrameAsOld();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cout << circle_centerZ << endl;
    
    ofBackground(0);
    
    cam.begin();
    ofSetColor(255);
    image.draw(-750,-750,-3100,1500,1500);
    
    ofPushMatrix();
    
    ofNoFill();
    ofSetLineWidth(20);
    ofSetCircleResolution(150);
    if(circle_centerZ < -1200){
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }else{
        ofSetColor(103,58,183,150);
    }
    ofDrawCircle(0, 0, -2400, 200);
    
    if(circle_centerZ < -1000){
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }else{
        ofSetColor(33,150,243,150);
    }
    ofDrawCircle(0, 0, -2200, 200);
    
    if(circle_centerZ < -1000){
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }else{
        ofSetColor(139,195,74,150);
    }
    ofDrawCircle(0, 0, -2000, 200);
    
    if(circle_centerZ < -1000){
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }else{
        ofSetColor(255,235,59,150);
    }
    ofDrawCircle(0, 0, -1800, 200);
    
    if(circle_centerZ < -1000){
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }else{
        ofSetColor(255,152,0,150);
    }
    ofDrawCircle(0, 0, -1600, 200);
    
    if(circle_centerZ < -1000){
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }else{
        ofSetColor(255,82,82,150);
    }
    ofDrawCircle(0, 0, -1400, 200);
    
    ofRotateY(ofGetFrameNum());
    //　ofRotateZ(ofGetFrameNum());
    
    if(circle_centerZ < -2400){
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255),200);
    }else{
        ofSetColor(255,200);
    }
    
    
    for(int i=0; i<NUM; i++){
        mBox[i].draw();
        if(circle_centerZ < -1200){
            ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255),200);
        }else{
            ofSetColor(255,200);
        }
        
    }
    
    ofPopMatrix();
    
    for(int i=0; i < simpleHands.size(); i++){
        
        
        
        
        for(int f=0; f<5; f++){
            ofSetColor(220);
            ofDrawSphere(fingerPos.at(20*i+4*f+0),10);
            
            ofSetColor(185);
            ofDrawSphere(fingerPos.at(20*i+4*f+1),10);
            
            ofSetColor(155);
            ofDrawSphere(fingerPos.at(20*i+4*f+2),10);
            
            ofSetColor(120);
            ofDrawSphere(fingerPos.at(20*i+4*f+3),10);
            
            ofDrawLine(fingerPos.at(20*i+4*f+0),fingerPos.at(20*i+4*f+1));
            ofDrawLine(fingerPos.at(20*i+4*f+1),fingerPos.at(20*i+4*f+2));
            ofDrawLine(fingerPos.at(20*i+4*f+2),fingerPos.at(20*i+4*f+3));
            
            
        }
    }
    if(fingerPos.size()==40){
        float distance = sqrt(pow(fingerPos.at(11).x-fingerPos.at(31).x,2)
                              +pow(fingerPos.at(11).y-fingerPos.at(31).y,2)
                              +pow(fingerPos.at(11).z-fingerPos.at(31).z,2));
        ofSetColor(249,31,99,150);
        ofFill();
        
        
        if(ball_thrown == false){
            ofDrawSphere((fingerPos.at(11).x+fingerPos.at(31).x)/2,
                         (fingerPos.at(11).y+fingerPos.at(31).y)/2,
                         (fingerPos.at(11).z+fingerPos.at(31).z)/2,
                         distance/4);
            
            
        }else{
            ofDrawSphere((handPos.at(0).x+handPos.at(1).x)/2, (handPos.at(0).y+handPos.at(1).y)/2, circle_centerZ,30);
            
        }
    }
    
    
    
    cam.end();
    ofDrawBitmapStringHighlight(ofToString(ball_thrown), 10,10);

}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'f') {
        ofToggleFullscreen();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
