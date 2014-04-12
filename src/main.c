#include <pebble.h>
#include "main_menu.h"
#include "character.h"
#include "game_menu.h"

Window* start_window;

void handle_init(void) {
  start_window = create_start_window();
  window_stack_push(start_window, true);
}

void handle_deinit(void) {
  deinit_game_window();
  deinit_start_window();
	window_destroy(start_window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}