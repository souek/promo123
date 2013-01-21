#include "testApp.h"

float Xpos;
float Ypos;
float Zpos;

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    
    Fullscreen  = 0;
    
    
// CAM START POSITION //
    
    Xpos = 0;
    Ypos = 40;
    Zpos = 50.;
    
// Obj MODEL LOAD
    
    model.loadModel("obj/testkule.obj");
    model.setPosition(0,0,0);
}

//--------------------------------------------------------------
void testApp::update(){
    
// HIDE CURSOR OPTIONS
    
    if(Fullscreen){
		ofHideCursor();
	}else{
		ofShowCursor();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    
// Set Cam A, B    
        
    cam[0].setPosition(Xpos, Ypos, Zpos);
	cam[1].setPosition(20+Xpos, Ypos, Zpos);
    
// Set LookAt for Cam A, B
    
    cam[0].lookAt(ofVec3f(0,0,0));
    cam[1].lookAt(ofVec3f(0,0,0));
    
    
    ofBackgroundGradient(210,250);
    ofSetColor(230, 230, 233,20);
    
    
    
    
    // GL SETINGS //
//	glDisable(GL_CULL_FACE);
//	ofSetColor(255);
//	ofDisableLighting();
    
    glEnable(GL_CULL_FACE);
	ofEnableLighting();
    
//    for(int i = 0; i < kNumLights; i++) {
//		light[i].enable();
//	}

	
// activate camera
	cam[camToView].begin();

    
// GRID AXIS   
    
    ofDrawGrid(50,5);
	ofDrawAxis(10);

    
//then we'll learn how to draw it manually so that we have more control over the data
	drawWithMesh();
    
    for(int i = 0; i < kNumLights; i++) {
		light[i].enable();
	}

    
// restore view to previous state (default openFrameworks view)
	cam[camToView].end();
    
    glDisable(GL_CULL_FACE);
	ofSetColor(255);
	ofDisableLighting();

    
    ofSetColor(0, 0, 0);
    
    ofDrawBitmapString("  position Cam A",10,10);
    ofDrawBitmapString("X pos: "+ofToString(Xpos), 10, 21);
    ofDrawBitmapString("Y pos: "+ofToString(Ypos), 10, 32);
    ofDrawBitmapString("Z pos: "+ofToString(Zpos), 10, 43);
    
    ofDrawBitmapString("  position Cam B",200,10);
    ofDrawBitmapString("X pos: "+ofToString(20+Xpos), 200, 21);
    ofDrawBitmapString("Y pos: "+ofToString(Ypos), 200, 32);
    ofDrawBitmapString("Z pos: "+ofToString(Zpos), 200, 43);
    

}
//--------------------------------------------------------------
void testApp::drawWithMesh(){
    
    //get the model attributes we need
	ofVec3f scale = model.getScale();
	ofVec3f position = model.getPosition();
	float normalizedScale = model.getNormalizedScale();
	ofVboMesh mesh = model.getMesh(0);
	ofTexture texture = model.getTextureForMesh(0);
	ofMaterial material = model.getMaterialForMesh(0);
	
    ofPushMatrix();
    //draw the model manually
	texture.bind();
	material.begin();
	//mesh.drawWireframe(); //you can draw wireframe too
	mesh.drawFaces();
	material.end();
	texture.unbind();
	
	ofPopMatrix();

}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    cout << "keyPressed " << key << endl;
    
    //FULL SCREEN OPTIONS //
    
    if(key == 'f'){
        
		Fullscreen = !Fullscreen;
		
		if(!Fullscreen){
			ofSetWindowShape(300,300);
			ofSetFullscreen(false);
			// figure out how to put the window in the center:
			int screenW = ofGetScreenWidth();
			int screenH = ofGetScreenHeight();
			ofSetWindowPosition(screenW/2-300/2, screenH/2-300/2);
		} else if(Fullscreen == 1){
			ofSetFullscreen(true);
		}
	}
    
        // PORUSZANIE CAMERA //
    
    if(key=='w')
    {
        Xpos--;
    }
    if(key=='q')
    {
        Xpos++;
    }
    if(key=='a')
    {
        Ypos--;
    }
    if(key=='s')
    {
        Ypos++;
    }

    if(key=='x')
    {
        Zpos--;
    }
    if(key=='z')
    {
        Zpos++;
    }
    
    switch(key) {
			
		case 'v':
			camToView = 1 - camToView;
			printf("\n\n** SHOWING CAMERA %i **\n", camToView);
			break;
			
		case 't':
			lookatIndex[camToConfigure]++ ; 
			if(lookatIndex[camToConfigure]>=kNumTestNodes) {
				lookatIndex[camToConfigure] = -1;
			}
			break;			
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
