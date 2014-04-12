#include "pebble.h"
#include "main_menu.h"
#include "game_menu.h"
#include "character.h"
  
#define NUM_MENU_SECTIONS 1
#define NUM_MAIN_MENU_ITEMS 4

  
Window *window;
Window *game_window;
TextLayer *text_layer;
SimpleMenuLayer *simple_menu_layer;
SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem main_menu_items[NUM_MAIN_MENU_ITEMS];

//Method prototypes
void select_click_handler(ClickRecognizerRef recognizer, void *context);
void config_provider(void *context);
void menu_select_callback(int index, void *ctx);
void main_menu_create();

void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Select");
  text_layer_destroy(text_layer);
  main_menu_create();
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(simple_menu_layer));
}

void config_provider(void *context) {
   window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
 }

void menu_select_callback(int index, void *ctx) {
  // Here we just change the subtitle to a literal string
  //main_menu_items[index].subtitle = "You've hit select here!";
  // Mark the layer to be updated
  //layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
  //Continue
  //game_window = window_create();//create_game_window();
  if(index == 0){
    game_window = create_game_window(true);
  }
  //New game
  else if(index == 1){
    //launch new window
    game_window = create_game_window(false);
  }
  //Help
  else if(index == 2){
    //launch new window
    //display general information
    game_window = window_create();
    TextLayer *help_text_layer = text_layer_create(GRect(0, 0, 144, 154));

    text_layer_set_text(help_text_layer, "This is a help screen!\nFuck you!");
	  text_layer_set_font(help_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	  text_layer_set_text_alignment(help_text_layer, GTextAlignmentCenter);

	  layer_add_child(window_get_root_layer(game_window), text_layer_get_layer(help_text_layer));
  }
  //Settings
  else if(index == 3){
    //launch new window
    //come up with some settings
    
  }
  else{
    
  }
  window_stack_push(game_window, true);
}

//Sets up the main menu layer
void main_menu_create(){  
  GRect bounds = layer_get_frame(window_get_root_layer(window));
  int num_a_items = 0;
  
  main_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Continue",
    .subtitle = "New game if no save",
    .callback = menu_select_callback,
    //callback indicates what's executed when you select that item
  };
  // The menu items appear in the order saved in the menu items array
  main_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "New Game",
    .callback = menu_select_callback,
  };
  
  main_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Help",
    .callback = menu_select_callback,
    // This is how you would give a menu item an icon
    //.icon = menu_icon_image,
  };
  
  main_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Settings",
    .callback = menu_select_callback,
  };
  
  menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_MAIN_MENU_ITEMS,
    .items = main_menu_items,
  };

  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);
}



Window* create_start_window(){
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
	//window_stack_push(window, true);
    window_set_window_handlers(window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_start_window
    });

  return window;
}

void deinit_start_window(){
	text_layer_destroy(text_layer);
	simple_menu_layer_destroy(simple_menu_layer);
	window_destroy(window);
}
