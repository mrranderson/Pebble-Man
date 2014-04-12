#include "pebble.h"
#include "main_menu.h"
#include "game_menu.h"
#include "character.h"
  
#define NUM_GAME_MENU_SECTIONS 1
#define NUM_GAME_MENU_ITEMS 4
  
Window *window;
SimpleMenuLayer *game_menu_layer;
SimpleMenuSection game_menu_sections[NUM_GAME_MENU_SECTIONS];
static SimpleMenuItem game_menu_items[NUM_GAME_MENU_ITEMS];
Character character;

void game_menu_create(){  
  GRect bounds = layer_get_frame(window_get_root_layer(window));
  int num_a_items = 0;
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Train",
    //.callback = menu_select_callback,
    //callback indicates what's executed when you select that item
  };
  // The menu items appear in the order saved in the menu items array
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Battle",
    //.callback = menu_select_callback,
  };
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Help",
    //.callback = menu_select_callback,
  };
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Character",
    //.callback = menu_select_callback,
  };
  
  game_menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_GAME_MENU_ITEMS,
    .items = game_menu_items,
  };

  game_menu_layer = simple_menu_layer_create(bounds, window, game_menu_sections, NUM_GAME_MENU_SECTIONS, NULL);

}



Window* create_game_window(bool cont){
  if(!cont){
    //create new character
  }
  
  window = window_create();
  //indow_set_click_config_provider(window, config_provider);

  game_menu_create();
  
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(game_menu_layer));

  return window;
}

void deinit_game_window(){
	simple_menu_layer_destroy(game_menu_layer);
	// Destroy the window
	window_destroy(window);

}
