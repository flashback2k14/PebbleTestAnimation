#include <pebble.h>
	
#ifndef LAYERANIMATION_H
#define LAYERANIMATION_H
	
/**
 * Constant variables
 */ 
#define START_PLACE_RECT GRect(0, 60, 144, 56)	
#define TO_RIGHT_RECT GRect(144, 60, 144, 56)
#define FROM_THE_LEFT_RECT GRect(-144, 60, 144, 56)

#define ANIMATION_DURATION_IN_MS 1500
#define ANIMATION_DELAY_IN_MS 500	
	
/** 
 * UI Elements
 */
extern Window *s_main_window;
extern TextLayer *s_time_layer, *s_date_layer;
extern PropertyAnimation *s_go_to_right_anim, *s_from_the_left_anim;
	
/**
 * Global Variables
 */
extern bool isDateShown;
	
/**
 * Global Methods for Aplite
 */
extern void animationStoppedHandler(Animation *anim, bool finished, void *context);
extern void init_animations_aplite();

/**
 * Global Methods for Basalt
 */
extern void init_animations_basalt();

/**
 * Global Methods - Non Device-specific
 */
extern void schedule_animation(struct tm *tick_time);

#endif
	