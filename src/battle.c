#include "pebble.h"
#include "character.h"
#include "battle.h"

#define NUM_BATTLE_MENU_SECTIONS 1
#define NUM_BATTLE_MENU_ITEMS 11
  
Window* window;
Window* skill_window;

TextLayer* battle_text_layer;

SimpleMenuLayer *battle_menu_layer;
SimpleMenuSection battle_menu_sections[NUM_BATTLE_MENU_SECTIONS];
SimpleMenuItem battle_menu_items[NUM_BATTLE_MENU_ITEMS];

char* my_text;
char* enemy_text;
bool showing_my_text;

Character character;

void battle_menu_select_callback(int index, void *ctx){
  if(index == 0){
    
  }
}

void battle_menu_create(){  
  GRect bounds = layer_get_frame(window_get_root_layer(skill_window));
  int num_a_items = 0;
  
  // SKILL 0: ATTACK
  char* a = (char*)malloc(16*sizeof(char));
  snprintf(a, 16, "%s", getSkill(character, 0));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = a,
    .callback = battle_menu_select_callback,
  };
  //free(a);
  
  // SKILL 1
  char* b = (char*)malloc(16*sizeof(char));
  snprintf(b, 16, "%s", getSkill(character, 1));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = b,
    .callback =  battle_menu_select_callback,
  };
  //free(b);
  
  // SKIL 2
  char* c = (char*)malloc(16*sizeof(char));
  snprintf(c, 16, "%s", getSkill(character, 2));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = c,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 3
  char* d = (char*)malloc(16*sizeof(char));
  snprintf(d, 16, "%s", getSkill(character, 3));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = d,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 4
  char* e = (char*)malloc(16*sizeof(char));
  snprintf(e, 16, "%s", getSkill(character, 4));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = e,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 5
  char* f = (char*)malloc(16*sizeof(char));
  snprintf(f, 16, "%s", getSkill(character, 5));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = f,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 6
  char* g = (char*)malloc(16*sizeof(char));
  snprintf(g, 16, "%s", getSkill(character, 6));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = g,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 7
  char* h = (char*)malloc(16*sizeof(char));
  snprintf(h, 16, "%s", getSkill(character, 7));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = h,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 8
  char* i = (char*)malloc(16*sizeof(char));
  snprintf(i, 16, "%s", getSkill(character, 8));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = i,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 9
  char* j = (char*)malloc(16*sizeof(char));
  snprintf(j, 16, "%s", getSkill(character, 9));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = j,
    .callback = battle_menu_select_callback,
  };
  
  // SKILL 10
  char* k = (char*)malloc(16*sizeof(char));
  snprintf(k, 16, "%s", getSkill(character, 10));
  battle_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = k,
    .callback = battle_menu_select_callback,
  };
  
  battle_menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_BATTLE_MENU_ITEMS,
    .items = battle_menu_items,
  };

  battle_menu_layer = simple_menu_layer_create(bounds, skill_window, battle_menu_sections, NUM_BATTLE_MENU_SECTIONS, NULL);
}


void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(showing_my_text){
    text_layer_set_text(battle_text_layer, enemy_text);
    showing_my_text = false;
  }
  else{
    text_layer_set_text(battle_text_layer, my_text);
    showing_my_text = true;
  }
}

void battle_select_click_handler(ClickRecognizerRef recognizer, void *context){
  skill_window = window_create();
  
  window_set_window_handlers(window, (WindowHandlers) {
    //.load = window_load,
    //.appear = window_appear,
    //.disappear = window_disappear,
    .unload = deinit_skill_window
  });

  battle_menu_create();
  layer_add_child(window_get_root_layer(skill_window), simple_menu_layer_get_layer(battle_menu_layer));
  window_stack_push(skill_window, true);
}

void battle_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, battle_select_click_handler);
 }
  


Window* create_battle_window(Character c){
  character = c;
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
        //.load = window_load,
        //.appear = window_appear,
        //.disappear = window_disappear,
        .unload = deinit_battle_window
    });
  
  Character enemy = (Character)generate_enemy(character);
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  battle_text_layer = text_layer_create(bounds);
  
  my_text = (char*)malloc(256*sizeof(char));
  snprintf(my_text, 256, "%s   %s-%d\n------------------------\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: %d   Damage: %d\n\n\n", 
          "Pebble", setClassname(character), character.level, character.health, character.mana, character.p, character.d, character.s,  
           character.ac, character.damage);

  enemy_text = (char*)malloc(256*sizeof(char));
  snprintf(enemy_text, 256, "%s   %s-%d\n------------------------\nHP: %d  Mana: %d\nP: %d   D: %d   S: %d\nAC: %d   Damage: %d\n\n\n", 
           "Enemy", setClassname(enemy), enemy.level, enemy.health, enemy.mana, enemy.p, enemy.d, enemy.s, enemy.ac, enemy.damage);
 
  text_layer_set_text(battle_text_layer, my_text);
  text_layer_set_font(battle_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(battle_text_layer, GTextAlignmentLeft);
 
  layer_add_child(window_layer, text_layer_get_layer(battle_text_layer));
  
  window_set_click_config_provider(window, battle_config_provider);

  return window;
}

Character generate_enemy(){
  srand(time(NULL));
  Character enemy;
  int eclass = rand()%3;
  int elevel = character.difficulty;
  int pds = 1+elevel;
  enemy = (Character){eclass, elevel, 10+5*character.difficulty, 0, 0, pds, pds, pds, 0, 0, 0};
  levelUp(&enemy);
  
  //if dead xp - 2*xp_reward  
  return enemy;
}

void deinit_skill_window(){
  simple_menu_layer_destroy(battle_menu_layer);
  window_destroy(skill_window);
}

void deinit_battle_window(){
  text_layer_destroy(battle_text_layer);
  window_destroy(window);
}