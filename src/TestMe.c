#include <pebble.h>
#include "LayerAnimation.h"	

/**
 * Initialisation UI Elements from Header file
 */
Window *s_main_window;
TextLayer *s_time_layer, *s_date_layer;
PropertyAnimation *s_go_to_right_anim, *s_from_the_left_anim;

/**
 * Initialisation Global Variables from Header file
 */
bool isDateShown = 1;	

/**
 * Handle Time changes
 */
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside handle_minute_tick");
	// Need to be static because it's used by the system later.
  static char s_time_text[] = "00:00";
	static char s_date_text[] = "01.01";

  strftime(s_time_text, sizeof(s_time_text), "%R", tick_time);
	strftime(s_date_text, sizeof(s_date_text), "%d.%m", tick_time);
	
  text_layer_set_text(s_time_layer, s_time_text);
	text_layer_set_text(s_date_layer, s_date_text);

	#ifndef PBL_PLATFORM_APLITE
		init_animations_basalt();
	#else
		init_animations_aplite();
	#endif	
  schedule_animation(tick_time);
}

/**
 * Initialisation of Window and Layers
 */
static void main_window_load(Window *window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside main_window_load");
	//
	s_time_layer = text_layer_create(START_PLACE_RECT);
  text_layer_set_text_color(s_time_layer, GColorWhite);
	#ifdef PBL_COLOR
		text_layer_set_background_color(s_time_layer, GColorRed);
	#else
		text_layer_set_background_color(s_time_layer, GColorClear);
	#endif
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	
	s_date_layer = text_layer_create(FROM_THE_LEFT_RECT);
  text_layer_set_text_color(s_date_layer, GColorWhite);
	#ifdef PBL_COLOR
		text_layer_set_background_color(s_date_layer, GColorRed);
	#else
		text_layer_set_background_color(s_date_layer, GColorClear);
	#endif  
	text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));

  #ifdef PBL_PLATFORM_APLITE
		init_animations_aplite();
	#endif
  tick_timer_service_subscribe(MINUTE_UNIT, &handle_minute_tick);
}

/**
 * Free Resources after Unload Watchface
 */
static void main_window_unload(Window *window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside main_window_unload");
	//
  #ifdef PBL_PLATFORM_APLITE
		property_animation_destroy(s_go_to_right_anim);
 		property_animation_destroy(s_from_the_left_anim);
	#endif
	
  text_layer_destroy(s_time_layer);
	text_layer_destroy(s_date_layer);
}

/**
 * Initialisation of the Watchface
 */
static void init() {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside init");
	//
	s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

/**
 * Destroy Watchface
 */
static void deinit() {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside deinit");
	//
	window_destroy(s_main_window);
}

/**
 * Entry Point
 */
int main(void) {
  init();
  app_event_loop();
  deinit();
}
