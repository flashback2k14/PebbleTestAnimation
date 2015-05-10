#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer, *s_date_layer;
static PropertyAnimation *s_go_to_right_anim, *s_from_the_left_anim;
bool isDateShown = 1;

#define START_PLACE_RECT GRect(0, 60, 144, 56)	
#define TO_RIGHT_RECT GRect(144, 60, 144, 56)
#define FROM_THE_LEFT_RECT GRect(-144, 60, 144, 56)

#define ANIMATION_DURATION_IN_MS 1500
#define ANIMATION_DELAY_IN_MS 500	

	
//#ifdef PBL_PLATFORM_APLITE
static void animationStoppedHandler(Animation *anim, bool finished, void *context){
	APP_LOG(APP_LOG_LEVEL_INFO, "inside animationStoppedHandler");
	property_animation_destroy((PropertyAnimation *) anim);
}
	
static void init_animations_aplite() {
	APP_LOG(APP_LOG_LEVEL_INFO, "inside init_animations_aplite");
	//
	Layer *layer_time = text_layer_get_layer(s_time_layer);
	Layer *layer_date = text_layer_get_layer(s_date_layer);

	if (isDateShown == 0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside IF isDateShown");
		
		s_go_to_right_anim = property_animation_create_layer_frame(layer_time, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) s_go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_go_to_right_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerTime = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) s_go_to_right_anim, handlerTime, NULL);

		s_from_the_left_anim = property_animation_create_layer_frame(layer_date, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) s_from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_from_the_left_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerDate = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) s_go_to_right_anim, handlerDate, NULL);
		
		isDateShown = 1;
	} else {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside ELSE isDateShown");
			
		s_go_to_right_anim = property_animation_create_layer_frame(layer_date, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) s_go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_go_to_right_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerTime = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) s_go_to_right_anim, handlerTime, NULL);
		
		s_from_the_left_anim = property_animation_create_layer_frame(layer_time, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) s_from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_from_the_left_anim, AnimationCurveEaseOut);
		AnimationHandlers handlerDate = {
			.stopped = (AnimationStoppedHandler) animationStoppedHandler
		};
		animation_set_handlers((Animation *) s_go_to_right_anim, handlerDate, NULL);
		
		isDateShown = 0;
	}
}
//#endif	
	
static void init_animations_basalt() {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside init_animations_basalt");
	//
	Layer *layer_time = text_layer_get_layer(s_time_layer);
	Layer *layer_date = text_layer_get_layer(s_date_layer);

	if (isDateShown == 0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside IF isDateShown");
		
		s_go_to_right_anim = property_animation_create_layer_frame(layer_time, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) s_go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_go_to_right_anim, AnimationCurveEaseOut);

		s_from_the_left_anim = property_animation_create_layer_frame(layer_date, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) s_from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_from_the_left_anim, AnimationCurveEaseOut);
		
		isDateShown = 1;
	} else {
		APP_LOG(APP_LOG_LEVEL_INFO, "inside ELSE isDateShown");
			
		s_go_to_right_anim = property_animation_create_layer_frame(layer_date, &START_PLACE_RECT, &TO_RIGHT_RECT);
		animation_set_duration((Animation*) s_go_to_right_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_go_to_right_anim, AnimationCurveEaseOut);
		
		s_from_the_left_anim = property_animation_create_layer_frame(layer_time, &FROM_THE_LEFT_RECT, &START_PLACE_RECT);
		animation_set_duration((Animation*) s_from_the_left_anim, ANIMATION_DURATION_IN_MS);
		animation_set_curve((Animation*) s_from_the_left_anim, AnimationCurveEaseOut);
		
		isDateShown = 0;
	}
}

static void schedule_animation(struct tm *tick_time) {
  static bool s_use_go_to_right_rect = false;

  if (s_use_go_to_right_rect) {
		APP_LOG(APP_LOG_LEVEL_INFO, "schedule_animation inside IF");
		
		animation_set_delay((Animation*) s_go_to_right_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) s_go_to_right_anim);
		
		animation_set_delay((Animation*) s_from_the_left_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) s_from_the_left_anim);
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "schedule_animation inside ELSE");
		
		animation_set_delay((Animation*) s_from_the_left_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) s_from_the_left_anim);
		
		animation_set_delay((Animation*) s_go_to_right_anim, ANIMATION_DELAY_IN_MS);
		animation_schedule((Animation*) s_go_to_right_anim);
  }

  s_use_go_to_right_rect = !s_use_go_to_right_rect;
}

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

static void deinit() {
  APP_LOG(APP_LOG_LEVEL_INFO, "inside deinit");
	//
	window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}