/*#include "pebble.h"
#include "main_menu.h"
  
Window *window;

void create_start_window(){
  window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));

	// Set the text, font, and text alignment

  text_layer_set_text(text_layer, "Welcome to \nPebbleMan");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
  
  window_set_click_config_provider(window, config_provider);

	// Push the window
	window_stack_push(window, true);

	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");

}
*/