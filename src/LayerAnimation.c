#include <pebble.h>
#include "LayerAnimation.h"

	
/**
 * Initialisation for Aplite
 */
void animationStoppedHandler(Animation *anim, bool finished, void *context){
	APP_LOG(APP_LOG_LEVEL_INFO, "inside animationStoppedHandler");
	property_animation_destroy((PropertyAnimation *) anim);
}	
	
void init_animations_aplite() {
	APP_LOG(APP_LOG_LEVEL_INFO, "inside init_animations_aplite");
	//
	Layer *layer_time = text_layer_get_layer(line_2_text_layer.time_layer);
	Layer *layer_date = text_layer_get_layer(line_2_text_layer.date_layer);

	if (isDateShown == 0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside IF isDateShown");
		
		line_2_text_layer.go_to_right_anim = property_animation_create_layer_frame(layer_time, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) line_2_text_layer.go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.go_to_right_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerTime = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) line_2_text_layer.go_to_right_anim, handlerTime, NULL);

		line_2_text_layer.from_the_left_anim = property_animation_create_layer_frame(layer_date, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) line_2_text_layer.from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.from_the_left_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerDate = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) line_2_text_layer.go_to_right_anim, handlerDate, NULL);
		
		isDateShown = 1;
	} else {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside ELSE isDateShown");
			
		line_2_text_layer.go_to_right_anim = property_animation_create_layer_frame(layer_date, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) line_2_text_layer.go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.go_to_right_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerTime = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) line_2_text_layer.go_to_right_anim, handlerTime, NULL);
		
		line_2_text_layer.from_the_left_anim = property_animation_create_layer_frame(layer_time, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) line_2_text_layer.from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.from_the_left_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerDate = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) line_2_text_layer.go_to_right_anim, handlerDate, NULL);
		
		isDateShown = 0;
	}
}	

/**
 * Initialisation for Basalt
 */
void init_animations_basalt() {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside init_animations_basalt");
	//
	Layer *layer_time = text_layer_get_layer(line_2_text_layer.time_layer);
	Layer *layer_date = text_layer_get_layer(line_2_text_layer.date_layer);

	if (isDateShown == 0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside IF isDateShown");
		
		line_2_text_layer.go_to_right_anim = property_animation_create_layer_frame(layer_time, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) line_2_text_layer.go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.go_to_right_anim, AnimationCurveEaseOut);

		line_2_text_layer.from_the_left_anim = property_animation_create_layer_frame(layer_date, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) line_2_text_layer.from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.from_the_left_anim, AnimationCurveEaseOut);
		
		isDateShown = 1;
	} else {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside ELSE isDateShown");
			
		line_2_text_layer.go_to_right_anim = property_animation_create_layer_frame(layer_date, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) line_2_text_layer.go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.go_to_right_anim, AnimationCurveEaseOut);
		
		line_2_text_layer.from_the_left_anim = property_animation_create_layer_frame(layer_time, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) line_2_text_layer.from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) line_2_text_layer.from_the_left_anim, AnimationCurveEaseOut);
		
		isDateShown = 0;
	}
}

/**
 * Handle Animations
 */ 
void schedule_animation(struct tm *tick_time) {
  static bool use_go_to_right_rect = false;

  if (use_go_to_right_rect) {
		APP_LOG(APP_LOG_LEVEL_INFO, "schedule_animation inside IF");
		
		animation_set_delay((Animation*) line_2_text_layer.go_to_right_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) line_2_text_layer.go_to_right_anim);
		
		animation_set_delay((Animation*) line_2_text_layer.from_the_left_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) line_2_text_layer.from_the_left_anim);
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "schedule_animation inside ELSE");
		
		animation_set_delay((Animation*) line_2_text_layer.from_the_left_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) line_2_text_layer.from_the_left_anim);
		
		animation_set_delay((Animation*) line_2_text_layer.go_to_right_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) line_2_text_layer.go_to_right_anim);
  }

  use_go_to_right_rect = !use_go_to_right_rect;
}
