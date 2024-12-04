#ifndef AUDIO_H
#define AUDIO_H

#include "assets.h"

void audio_init();                      
void audio_update();                      
void audio_shutdown();                   
void audio_toggle_mute();                 
void audio_increase_volume();            
void audio_decrease_volume();              
void audio_draw_ui();                     

#endif // AUDIO_H
