#pragma once

#include "ofMain.h"
#include "Particle.hpp"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

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
  
    void new_particle(Particle* _particle = NULL);
  
  vector<Particle> particles;

  ofxPanel  gui;
  ofxIntSlider      slider_particles;
  ofxVec2Slider     slider_life;
  ofxVec2Slider     change_prob;
  ofxVec2Slider     direction_mult;
  ofxFloatSlider    slider_direction;
  ofxColorSlider    color_start;
  ofxColorSlider    color_end;
  ofxButton         button_clear;
  ofxButton         button_save;
  ofxLabel          label_particles_alive;
  
  ofFbo fbo;
  
};
