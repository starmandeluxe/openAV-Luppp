
#ifndef LUPPP_G_UNIT_TRACK_H
#define LUPPP_G_UNIT_TRACK_H

#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Slider.H>

#include "avtk/avtk_dial.h"
#include "avtk/avtk_button.h"
#include "avtk/avtk_background.h"


#include "eventhandler.hxx"

using namespace std;

static void gunittrack_button_callback(Fl_Widget *w, void *data) {
  
  
  int track = 0;
  if ( data )
   track = *(int*)data;
  
  if ( strcmp( w->label(), "Metro" ) == 0 )
  {
    Avtk::Button* b = (Avtk::Button*)w;
    b->value( !b->value() );
    EventMetronomeActive e = EventMetronomeActive( b->value() );
    writeToDspRingbuffer( &e );
  }
  else if ( strcmp( w->label(), "BPM" ) == 0 )
  {
    Avtk::Dial* b = (Avtk::Dial*)w;
    float bpm = b->value() * 160 + 60; // 60 - 220
    EventTimeBPM e = EventTimeBPM( bpm );
    writeToDspRingbuffer( &e );
  }
  else if ( strcmp( w->label(), "Tap" ) == 0 )
  {
    Avtk::Button* b = (Avtk::Button*)w;
    EventTimeTempoTap e;
    writeToDspRingbuffer( &e );
  }
  else
  {
    cout << __FILE__ << __LINE__ << " Error: unknown command string" << endl;
  }
}

class GUnitTrack : public Fl_Group
{
  public:
    GUnitTrack(int x, int y, int w, int h, const char* l = 0 ) :
      Fl_Group(x, y, w, h),
      title( strdup(l) ),
      bg( x, y , w, h, title ),
      
      tapTempo(x + 25 + 22, y + 75, 44, 44,"Tap"),
      /*
      button2(x + 5, y + 44, 100, 18,"Play"),
      button3(x + 5, y + 64, 100, 18,"Stop"),
      button4(x + 5, y + 84,  48, 18,"-"),
      button5(x +57, y + 84,  48, 18,"+"),
      button6(x + 5, y +104, 18, 18,"6"),
      */
      metronomeButton(x + 5,y + 124,140,30,"Metro"),
      
      dial1(x+25-22, y +75, 44, 44, "BPM")
      /*
      dial2(x+45, y +155, 24, 24, "B"),
      dial3(x+75, y +155, 24, 24, "C")
      */
    {
      //tapTempo.callback( gmastertrack_button_callback, &ID );
      
      /*
      button2.callback( gmastertrack_button_callback, &ID );
      button3.callback( gmastertrack_button_callback, &ID );
      button4.callback( gmastertrack_button_callback, &ID );
      button5.callback( gmastertrack_button_callback, &ID );
      button6.callback( gmastertrack_button_callback, &ID );
      */
      metronomeButton.callback( gunittrack_button_callback, 0 );
      dial1.callback( gunittrack_button_callback, 0 );
      
      end(); // close the group
    }
    
    ~GUnitTrack()
    {
      free(title);
    }
    
  
  private:
    char* title;
    
    Avtk::Background bg;
    
    Avtk::Button tapTempo;
    /*
    Avtk::Button button2;
    Avtk::Button button3;
    Avtk::Button button4;
    Avtk::Button button5;
    Avtk::Button button6;
    */
    Avtk::LightButton metronomeButton;
    
    Avtk::Dial dial1;
    /*
    Avtk::Dial dial2;
    Avtk::Dial dial3;
    */
    
};

#endif // LUPPP_G_UNIT_TRACK_H
