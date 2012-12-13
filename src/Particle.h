//
//  Particle.h
//  ofxCVExperiment001
//
//  Created by Isaac Gierard on 12/11/12.
//
//

#ifndef __ofxCVExperiment001__Particle__
#define __ofxCVExperiment001__Particle__
#include "ofMain.h"
#include "ofxAutoControlPanel.h"
class Particle{
public:
    Particle(ofVec2f pos);
private:
    ofVec2f pos, vel,last;
    float   friction;
    ofColor color;
public:
    void draw();
    void update(ofRectangle constrain);
    void applyForce(ofVec2f force);
    ofVec2f& getPos();
    inline void setColor(ofColor color){this->color = color;}
    static float minRad;
    static float maxRad;
    static float maxForce;
};

#endif /* defined(__ofxCVExperiment001__Particle__) */
