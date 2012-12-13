#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxAutoControlPanel.h"
#include "Particle.h"
class CVExperiment : public ofBaseApp{
    private:
        ofVideoGrabber cam;
    
        ofxCv::FlowFarneback farneback;
        ofxCv::Flow* curFlow;
        
        ofxAutoControlPanel panel;
        vector<Particle*> particles;
        ofRectangle constrain;
        int totalParticles = 100;
        int flowRegionsC = 10;
        int flowRegionsR = 10;
    int frameCount = 0;
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
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

};
