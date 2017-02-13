#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  gui.setup("params");
  slider_particles.setup("Max Particles",100,1,500);
  slider_life.setup("Life Range",ofVec2f(30,100),ofVec2f(0,0),ofVec2f(500,500));
  slider_direction.setup("Direction Random",5,2,180);
  change_prob.setup("Direction Prob",ofVec2f(10,90),ofVec2f(0,0),ofVec2f(100,100));
  direction_mult.setup("Direction Mult",ofVec2f(.1,.1),ofVec2f(0,0),ofVec2f(5.0,5.0));
  label_particles_alive.setup("Alive","0");
  
  color_start.setup("Color Start",ofColor(255),ofColor(0),ofColor(255));
  color_end.setup("Color End",ofColor(0),ofColor(0),ofColor(255));
  
  button_clear.setup("Clear",false);
  button_save.setup("Save",false);

  gui.add(&slider_particles);
  gui.add(&slider_life);
  gui.add(&slider_direction);
  gui.add(&change_prob);
  gui.add(&direction_mult);
  gui.add(&color_start);
  gui.add(&color_end);
  gui.add(&button_clear);
  gui.add(&button_save);
  gui.add(&label_particles_alive);
  
  ofFbo::Settings s;
  s.width = ofGetWidth();
  s.height = ofGetHeight();
  s.numSamples = 8;
  s.internalformat = GL_RGBA32F;
  
  fbo.allocate(s);
  fbo.begin();
  ofBackground(255);
  fbo.end();


}

//--------------------------------------------------------------
void ofApp::update(){
  
  if(ofGetFrameNum() == 1)
  {
    gui.loadFromFile("settings.xml");
  }
  
  if(particles.size() > slider_particles)
  {
    bool can_delete = true;
    int i =0;
    while(can_delete && i<particles.size() && particles.size() > slider_particles)
    {
      if(!particles.at(i).alive)
      {
        particles.erase(particles.begin()+i);
      }
      i++;
    }
  }
  
  
  int free_particle = -1;
  int i = 0;
  while(i < particles.size() && free_particle == -1)
  {
    if(!particles.at(i).alive)
    {
      free_particle = i;
    }
    i++;
  }
  if(free_particle == -1)
  {
    if(particles.size() < slider_particles)
    {
      new_particle();
    }
  }else{
    new_particle(&particles.at(free_particle));
  }
  int alive_pars = 0;
  for(int i=0;i<particles.size();i++)
  {
    particles.at(i).update();
    if(particles.at(i).alive)
      alive_pars++;
  }
  label_particles_alive = ofToString(alive_pars);
  
  //  draw
  
  fbo.begin();
  if(button_clear)
  {
    ofBackground(255);
  }
  for(int i=0;i<particles.size();i++)
  {
    if(particles.at(i).alive){
      ofPushMatrix();
      ofTranslate(particles.at(i));

      ofColor _color_end = color_end;
      ofColor color = _color_end.getLerped(color_start,particles.at(i).life_norm);
      ofSetColor(color);
      
      ofDrawCircle(0,0,10*particles.at(i).life_norm);
      ofPopMatrix();
    }
  }
  fbo.end();
  
  //  save
  
  if(button_save){
    string file_name = ofToString(ofGetDay())+"_"+ofToString(ofGetMonth())+"_"+ofToString(ofGetHours())+"_"+ofToString(ofGetMinutes())+"_"+ofToString(ofGetSeconds());
    ofImage image_save;
    fbo.readToPixels(image_save.getPixels());
    image_save.save("render/"+file_name+".png");
    image_save.clear();
  }
  
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofSetColor(255);
  fbo.draw(0,0);

  gui.draw();
  
}

//--------------------------------------------------------------

void ofApp::new_particle(Particle* _particle)
{
  if(_particle == NULL)
  {
    //  need to create a new
    Particle new_particle;
    new_particle.born(ofGetWidth()*.5,ofGetHeight()*.5);
    particles.push_back(new_particle);
    _particle = &particles.at(particles.size()-1);
  }else{
    _particle->born(ofGetWidth()*.5,ofGetHeight()*.5);
  }
  _particle->max_life = ofRandom(slider_life->x,slider_life->y);
  _particle->direction_mult = ofRandom(direction_mult->x,direction_mult->y);
  _particle->direction_change_rule = ofRandom(change_prob->x,change_prob->y);
  _particle->random_direction = ofRandom(-slider_direction,slider_direction);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
