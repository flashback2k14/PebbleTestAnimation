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
 * Definition Struct Line
 */
typedef struct {
	TextLayer *time_layer;
	TextLayer *date_layer;
	PropertyAnimation *go_to_right_anim;
	PropertyAnimation *from_the_left_anim;
} Line;

/** 
 * UI Elements
 */
extern Window *main_window;
extern Line line_2_text_layer;

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
	