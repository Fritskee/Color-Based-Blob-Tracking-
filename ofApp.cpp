#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(minH.setup("min H", 44, 0, 100));
    gui.add(maxH.setup("max H", 98, 0, 180));
    gui.add(minS.setup("min S", 67, 0, 255));
    gui.add(maxS.setup("max S", 255, 0, 255));
    gui.add(minV.setup("min V", 96, 0, 255));
    gui.add(maxV.setup("max V", 255, 0, 255));
    
    vidGrabber.initGrabber(640, 480);
    
    started = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){
        im.setFromPixels(vidGrabber.getPixels());
        mat = toCv(im);
        cvtColor(mat, mat_HSV, CV_BGR2HSV);
        inRange(mat_HSV, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), mat_HSV_Threshold);
        erode(mat_HSV_Threshold, mat_HSV_Threshold, Mat());
        dilate(mat_HSV_Threshold, mat_HSV_Threshold, Mat());
        
        ofImage im_temp;
        ofxCvGrayscaleImage im_temp_gray;
        
        toOf(mat_HSV_Threshold, im_temp);
        
        im_temp_gray.setFromPixels(im_temp.getPixels());
        
        contourFinder.findContours(im_temp_gray, 5, (340 * 240) / 4, 4, false, true);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    drawMat(mat, 0, 0);
    if(started == false){
    ofDrawBitmapString("Press 's' to start drawing", 0, 20);
    }
    
    ofRectangle r;
    for(int i = 0; i < contourFinder.nBlobs; i++){
        r = contourFinder.blobs.at(i).boundingRect;
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofDrawRectangle(r);
    }
    
    if(started == true){
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Press 's' to stop drawing", 0, 20);
    ofPoint pt;
    ofSetColor(0,255,0);
    pt.set(r.getX(), r.getY());
    line.back().addVertex(pt);
    }
    ofSetColor(0,255,0);
    for(int i = 0; i < line.size(); i++){
    line[i].draw();
    }
    
    ofSetColor(255, 255, 255);
    drawMat(mat_HSV_Threshold, mat.cols, 0);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(started == false && key == 's')
    {
        started = true;
        line.push_back(ofPolyline());
    }
    else if(key == 's'){
        started = false;
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
