#include <pebble.h>
#include "LayerAnimation.h"	

/**
 * Initialisation UI Elements from Header file
 */
Window *main_window;
Line line_2_text_layer;

/**
 * Initialisation Global Variables from Header file
 */
bool isDateShown = 1;	

/**
 * Initialisation TextLayers
 */
static TextLayer* init_text_layer(GRect location, GColor textColor, GColor backgroundColor, const char *textFont, GTextAlignment alignment) {
  TextLayer *layer = text_layer_create(location);
  text_layer_set_text_color(layer, textColor);
  text_layer_set_background_color(layer, backgroundColor);
  text_layer_set_font(layer, fonts_get_system_font(textFont));
  text_layer_set_text_alignment(layer, alignment);
  return layer;
}

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
	
  text_layer_set_text(line_2_text_layer.time_layer, s_time_text);
	text_layer_set_text(line_2_text_layer.date_layer, s_date_text);

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
	
	#ifdef PBL_COLOR
		line_2_text_layer.time_layer = init_text_layer(START_PLACE_RECT, GColorWhite, GColorRed, FONT_KEY_BITHAM_42_BOLD, GTextAlignmentCenter);
		line_2_text_layer.date_layer = init_text_layer(FROM_THE_LEFT_RECT, GColorWhite, GColorRed, FONT_KEY_BITHAM_42_BOLD, GTextAlignmentCenter);
	#else
		line_2_text_layer.time_layer = init_text_layer(START_PLACE_RECT, GColorWhite, GColorClear, FONT_KEY_BITHAM_42_BOLD, GTextAlignmentCenter);
		line_2_text_layer.date_layer = init_text_layer(FROM_THE_LEFT_RECT, GColorWhite, GColorClear, FONT_KEY_BITHAM_42_BOLD, GTextAlignmentCenter);
	#endif	
	
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(line_2_text_layer.time_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(line_2_text_layer.date_layer));

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
		property_animation_destroy(line_2_text_layer.go_to_right_anim);
 		property_animation_destroy(line_2_text_layer.from_the_left_anim);
	#endif
	
  text_layer_destroy(line_2_text_layer.time_layer);
	text_layer_destroy(line_2_text_layer.date_layer);
}

/**
 * Initialisation of the Watchface
 */
static void init() {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside init");
	//
	main_window = window_create();
  window_set_background_color(main_window, GColorBlack);
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(main_window, true);
}

/**
 * Destroy Watchface
 */
static void deinit() {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside deinit");
	//
	window_destroy(main_window);
}

/**
 * Entry Point
 */
int main(void) {
  init();
  app_event_loop();
  deinit();
}
