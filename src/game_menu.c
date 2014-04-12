#include "pebble.h"
#include "main_menu.h"
#include "game_menu.h"
#include "character.h"
  
#define NUM_GAME_MENU_SECTIONS 1
#define NUM_GAME_MENU_ITEMS 4
#define NUM_CLASS_MENU_SECTIONS 1
#define NUM_CLASS_MENU_ITEMS 3
#define CLASS 0
#define LEVEL 1
#define HEALTH 2
#define MANA 3
#define P 4
#define D 5
#define S 6
  
Window *window;
Window *character_window;
SimpleMenuLayer *game_menu_layer;
SimpleMenuSection game_menu_sections[NUM_GAME_MENU_SECTIONS];
static SimpleMenuItem game_menu_items[NUM_GAME_MENU_ITEMS];

SimpleMenuLayer *class_menu_layer;
SimpleMenuSection class_menu_sections[NUM_CLASS_MENU_SECTIONS];
SimpleMenuItem class_menu_items[NUM_CLASS_MENU_ITEMS];

Character character;

void game_menu_select_callback(int index, void *ctx) {
  //Train
  if(index == 0){
    //Train by walking around in the real world
    //Accelerometer
    levelUp(&character);
  }
  //Battle
  else if(index == 1){
    //Fight a randomly generated enemy based on the current difficulty
  }
  //Character
  else if(index == 2){
    //Display character stats
    character_window = window_create();
    ScrollLayer *scroll = scroll_layer_create(layer_get_frame(window_get_root_layer(character_window)));
    TextLayer *character_text_layer = text_layer_create(GRect(0, 0, 144, 154));

    char* h = (char*)malloc(128*sizeof(char));
    snprintf(h, 128, "ME\n%s-%d\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: 32 \nDam: 56-98", 
             setClassname(character), character.level, character.health, character.mana, character.p, character.d, character.s);
    
    text_layer_set_text(character_text_layer, h);
	  text_layer_set_font(character_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	  text_layer_set_text_alignment(character_text_layer, GTextAlignmentLeft);

    scroll_layer_add_child(scroll, text_layer_get_layer(character_text_layer));
	  layer_add_child(window_get_root_layer(character_window), scroll_layer_get_layer(scroll));
    scroll_layer_set_click_config_onto_window(scroll, character_window);
    
      window_set_window_handlers(character_window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_character_window,
    });

    window_stack_push(character_window, true);
  }
  //Settings
  else if(index == 3){
    //launch new window
    //come up with some settings
    
  }
  else{
    
  }
}


void game_menu_create(){  
  GRect bounds = layer_get_frame(window_get_root_layer(window));
  int num_a_items = 0;
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Train",
    .callback = game_menu_select_callback,
  };
  // The menu items appear in the order saved in the menu items array
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Battle",
    .callback = game_menu_select_callback,
  };
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Character",
    .callback = game_menu_select_callback,
  };
  
  game_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Travel",
    .callback = game_menu_select_callback,
  };
  
  game_menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_GAME_MENU_ITEMS,
    .items = game_menu_items,
  };

  game_menu_layer = simple_menu_layer_create(bounds, window, game_menu_sections, NUM_GAME_MENU_SECTIONS, NULL);
}

void class_menu_select_callback(int index, void *ctx){
  character.class = index;  
  simple_menu_layer_destroy(class_menu_layer);
  game_menu_create();    
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(game_menu_layer));
}

void class_menu_create(){
  GRect bounds = layer_get_frame(window_get_root_layer(window));
  int num_a_items = 0;
  
  class_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Fighter",
    .callback = class_menu_select_callback,
  };
  // The menu items appear in the order saved in the menu items array
  class_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Rogue",
    .callback = class_menu_select_callback,
  };
  
  class_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Mage",
    .callback = class_menu_select_callback,
  };
  
  class_menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_CLASS_MENU_ITEMS,
    .items = class_menu_items,
  };

  class_menu_layer = simple_menu_layer_create(bounds, window, class_menu_sections, NUM_CLASS_MENU_SECTIONS, NULL);

}

Window* create_game_window(bool cont){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_game_window
    });
  
  if(!cont){
    //create new character
    //choose a class
    class_menu_create();
    layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(class_menu_layer));
  }
  else{
    if(persist_exists(CLASS))
      character.class = persist_read_int(CLASS);
    if(persist_exists(LEVEL))
      character.level = persist_read_int(LEVEL);
    if(persist_exists(HEALTH))
      character.level = persist_read_int(HEALTH);
    if(persist_exists(MANA))
      character.level = persist_read_int(MANA);
    if(persist_exists(P))
      character.level = persist_read_int(P);
    if(persist_exists(D))
      character.level = persist_read_int(D);
    if(persist_exists(S))
      character.level = persist_read_int(S);

    game_menu_create();
    
    layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(game_menu_layer));
  }
  
  return window;
}

void save_data(){
  APP_LOG(0, "SAVING");
  persist_write_int(CLASS, character.class);
  persist_write_int(LEVEL, character.level);
  persist_write_int(HEALTH, character.health);
  persist_write_int(MANA, character.mana);
  persist_write_int(P, character.p);
  persist_write_int(D, character.d);
  persist_write_int(S, character.s);
}

void deinit_character_window(){
  window_destroy(character_window);
}

void deinit_game_window(){
  save_data();
	simple_menu_layer_destroy(game_menu_layer);
	// Destroy the window
	window_destroy(window);

}
