#include "CVExperiment.h"

using namespace ofxCv;
using namespace cv;
//ofxAutoControlPanel CVExperiment::panel = ;
//--------------------------------------------------------------
void CVExperiment::setup(){
    cam.setVerbose(true);
    cam.listDevices();
    
    cam.setDeviceID(0);
    cam.initGrabber(640, 480);
    
    
    panel.setup(250, 800);
	
	panel.addPanel("Optical Flow");
	
	panel.addSlider("pyrScale", .5, 0, 1);
	panel.addSlider("levels", 4, 1, 8, true);
	panel.addSlider("winsize", 8, 4, 64, true);
	panel.addSlider("iterations", 2, 1, 8, true);
	panel.addSlider("polyN", 7, 5, 10, true);
	panel.addSlider("polySigma", 1.5, 1.1, 2);
	panel.addToggle("OPTFLOW_FARNEBACK_GAUSSIAN", false);
	

    
    panel.addToggle("Draw Flow", false);
    panel.addToggle("Draw Image", true);
    panel.addSlider("numPart", 1000, 10, 10000);
    panel.addSlider("minPart", 2.0, 2.0, 100.0);
    panel.addSlider("maxPart", 10.0, 2.0, 100.0);
    panel.addSlider("maxForce", 50.0, 10.0, 200.0);
    panel.addSlider("minThresh", 10.0, 0.0, 200.0);
    
	curFlow = &farneback;
    constrain.set(20, 20, 600, 440);
    totalParticles = 1000;
    flowRegionsC = 10;
    flowRegionsR = 10;
    frameCount = 0;
    for(int i = 0; i < totalParticles; i++){
        float x = ofRandom(constrain.x,constrain.getWidth());
        float y = ofRandom(constrain.y,constrain.getHeight());
        Particle* p = new Particle(ofVec2f(x,y));
        particles.push_back(p);
    }
}

//--------------------------------------------------------------
void CVExperiment::update(){
    cam.update();
    if(cam.isFrameNew()) {
		frameCount++;
        Particle::minRad = panel.getValueF("minPart");
        Particle::maxRad = panel.getValueF("maxPart");
        Particle::maxForce = panel.getValueF("maxForce");

        curFlow = &farneback;
        farneback.setPyramidScale( panel.getValueF("pyrScale") );
        farneback.setNumLevels( panel.getValueF("levels") );
        farneback.setWindowSize( panel.getValueF("winsize") );
        farneback.setNumIterations( panel.getValueF("iterations") );
        farneback.setPolyN( panel.getValueF("polyN") );
        farneback.setPolySigma( panel.getValueF("polySigma") );
        farneback.setUseGaussian(panel.getValueB("OPTFLOW_FARNEBACK_GAUSSIAN"));
			

		
		//check it out that that you can use Flow polymorphically
		curFlow->calcOpticalFlow(cam);
        float min_thresh = panel.getValueF("minThresh");
        if(frameCount > 2) {
            for (vector<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
                Particle* p = (*it);
                ofVec2f f = farneback.getFlowPosition(max(constrain.x,min(p->getPos().x,constrain.width)), max(constrain.y,min(p->getPos().y,constrain.height)));
                f -= p->getPos();
//                cout << f.x << "," << f.y << endl;
                if(f.lengthSquared() > min_thresh){
                    p->applyForce(f);
                }
                p->update(constrain);
            }

        }
	}
    int numParts = panel.getValueI("numPart");
    if(numParts < particles.size()){
        for(int i = numParts-1; i < particles.size(); i++){
            delete particles[i];
        }
        particles.erase(particles.begin()+numParts-1,particles.end());
    }else if(numParts > particles.size()){
        for(int i = particles.size(); i < numParts; i++){
            float x = ofRandom(constrain.x,constrain.getWidth());
            float y = ofRandom(constrain.y,constrain.getHeight());
            Particle* p = new Particle(ofVec2f(x,y));
            particles.push_back(p);
        }
    }
}

//--------------------------------------------------------------
void CVExperiment::draw(){
    ofBackground(0);
    
	ofSetColor(255);
	if(panel.getValueB("Draw Image")) cam.draw(400,100,640,480);
	if(panel.getValueB("Draw Flow")) curFlow->draw(400,100,640,480);
    ofPushMatrix();
    ofTranslate(400, 100);
    ofNoFill();
    ofRect(constrain);
    for (vector<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
        (*it)->draw();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void CVExperiment::keyPressed(int key){

}

//--------------------------------------------------------------
void CVExperiment::keyReleased(int key){

}

//--------------------------------------------------------------
void CVExperiment::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void CVExperiment::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void CVExperiment::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void CVExperiment::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void CVExperiment::windowResized(int w, int h){

}

//--------------------------------------------------------------
void CVExperiment::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void CVExperiment::dragEvent(ofDragInfo dragInfo){ 

}