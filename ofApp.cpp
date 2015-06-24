#include "ofApp.h"
#define SCSHOTS_PER_SEC 10 //SCSHOTS_PER_SECは一秒間あたりの表示画像数。
#define NUM_IMG 10//NUM_IMGは 画像の枚数である。
#define NUM 100

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofSetCircleResolution(60);
    ofSetFrameRate(60);
    
    int i = 1;
    string fileName = "0001.jpeg";
    while (ofFile::doesFileExist(fileName)){
        ofImage aImage;
        aImage.loadImage(fileName);
        image.push_back(aImage);
        i++;
        char char1[32];
        sprintf(char1, "%04d.jpeg", i);
        fileName = ofToString(char1);
    }
    currentFrame =0;
    
    myFbo.allocate(ofGetWidth(), ofGetHeight());
    myGlitch.setup(&myFbo);
    
    myFbo1.allocate(ofGetWidth(), ofGetHeight());
    myGlitch1.setup(&myFbo1);
    ttf.loadFont(OF_TTF_SANS, 100);//ofTrueTypeFontのインスタンス.loadFont(文字の種類,文字の高さ)
    s = "Schoenberg";
    
    bdrawimage =false;
    bdrawtitle = false;
    
    mySound.loadSound("sample.mp3"); //サウンドファイルの読込み
    mySound.setLoop(true); //ループ再生をONに
    mySound.play(); //サウンド再生開始
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(bdrawimage){
        myFbo.begin();
        ofClear(0, 0, 0, 255);
        if (ofGetFrameNum()%(60/SCSHOTS_PER_SEC)==0)currentFrame++;
        if (currentFrame >= NUM_IMG) currentFrame = 0;
        image[currentFrame].draw(0,0,ofGetWidth(),ofGetHeight());
        myFbo.end();
    }
    
    if(bdrawtitle){
        myFbo1.begin();
        ofBackground(0);
        ofRectangle r = ttf.getStringBoundingBox(s, 0, 0);
        ofVec2f offset = ofVec2f(floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f));
        ofSetColor(255);
        ttf.drawString(s, ofGetWidth() / 2 + offset.x, ofGetHeight() / 2 + offset.y);//インスタンス(文字列、場所)
        myFbo1.end();
    }
    
    volume = ofSoundGetSpectrum(GetPrecision);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    while(ofGetElapsedTimef()<20){
        switch(int(ofGetElapsedTimef())%4){
                
            case 0:case 1:{
                bdrawimage = !bdrawimage;
                bdrawtitle = false;
                break;
            }
            case 2:case 3:{
                bdrawtitle = !bdrawtitle;
                bdrawimage = false;
                break;
            }
        }//switch文終わり
        if(bdrawimage){
            myGlitch.setFx(OFXPOSTGLITCH_NOISE, true);
            myGlitch.generateFx();
            myFbo.draw(0, 0);
        }
        if(bdrawtitle){
            myGlitch1.setFx(OFXPOSTGLITCH_TWIST, true);
            myGlitch1.generateFx();
            myFbo1.draw(0, 0);
        }
        break;
    }//while文終わり
    
    if(ofGetElapsedTimef()>20){
        ofPushMatrix();
        ofSetColor(255);
        ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
        for(int i=0;i<NUM;i++){
            ofCircle(i*ofRandom(-200,200),i*ofRandom(-200,200),100*volume[i]);
        }
        ofPopMatrix();
    }
    
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
    if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
    if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
    if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
    if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
    if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
    if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
    if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
    if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
    if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
    
    if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
    if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
    if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
    if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
    if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
    if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
    if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
    if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
    if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
    if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
    if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
    if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
    if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
    if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
    if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
    
    if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
    if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
    if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
    if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
    if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
    if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
