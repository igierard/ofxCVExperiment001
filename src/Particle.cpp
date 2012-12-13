//
//  Particle.cpp
//  ofxCVExperiment001
//
//  Created by Isaac Gierard on 12/11/12.
//
//

#include "Particle.h"
#include "CVExperiment.h"

float Particle::minRad = 2.0;
float Particle::maxRad = 10.0;
float Particle::maxForce = 50.0;

Particle::Particle(ofVec2f pos):
pos(pos),
friction(0.95),
vel(ofVec2f::one()),
color(ofColor::blue){
    if(ofRandomf() > 0.5){
        vel.x *= -1;
    }
    if(ofRandomf() > 0.5){
        vel.y *= -1;
    }
}
void Particle::draw(){
    float l = max(5.0f,vel.length());
    float r = min(l,maxForce)/maxForce;
    color = ofColor::blue;
    ofSetColor(color.lerp(ofColor::red, r));
    ofFill();
    
    ofCircle(pos.x, pos.y, max(minRad,maxRad*r));
}
void Particle::update(ofRectangle constrain){
    last = pos;
    ofVec2f old = vel;
    vel *= friction;
    if(vel.lengthSquared() < 0.5){ vel = old;}
    const float jitter = 0.0001;
    pos += vel;


    if (pos.x > (constrain.x+constrain.width)) {
        pos.x -= (pos.x-(constrain.x+constrain.width))*2;
        vel.x *= -1;
    }
    if (pos.x < constrain.x) {
        pos.x += (constrain.x-pos.x)*2;
        vel.x *= -1;
    }
    if (pos.y > (constrain.x+constrain.height)) {
        pos.y -= (pos.y-(constrain.x+constrain.height))*2;
        vel.y *= -1;
    }
    if (pos.y < constrain.y) {
        pos.y += (constrain.y-pos.y)*2;
        vel.y *= -1;
    }

    if(vel == ofVec2f::zero()){cout << "stoped" << endl;}
}
void Particle::applyForce(ofVec2f force){
    vel += force;
    vel = vel.limit(maxForce);
}

ofVec2f& Particle::getPos(){
    return pos;
}