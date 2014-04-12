#include "character.h"
  
int getAC(Character c) {
  c.ac = c.d / 3;
  return c.ac;
}

int getDamage(Character c) {
  if (c.class == 0)
    c.damage = c.p / 2;
  else if (c.class == 1)
    c.damage = c.d / 2;
  else
    c.damage = c.s / 2;
  return c.damage;
}

char* setClassname(Character c) {
  if (c.class == 0) return "Fighter";
  else if (c.class == 1) return "Rogue";
  else return "Mage";
}

void levelUp(Character* c){
  c->level++;
  c->s++;
  c->p++;
  c->d++;
  if(c->level == 1 || c->level % 3 == 0) {
    if(c->class == 0)
      c->p++;
    if(c->class == 1)
      c->d++;
    if(c->class == 2)
      c->s++;
  }
  c->damage = getDamage(*c);
  c->ac = getAC(*c);
  c->health=c->p + 2;
  c->mana=c->s + 2;
}

char* getSkill(Character c, int i) {
 char *f[10] = { "1", "2", "Aim", "3", "Focus", "4", "First aid", "5", "Paragon", "6" };
 if (c.class == 0) {
   f[0] = "Flurry";
   f[1] = "Warm Up";
   f[3] = "Rising Fury";
   f[5] = "Parry";
   f[7] = "Retaliate";
   f[9] = "Go For the Kill";
 }
 else if (c.class == 1) {
   f[0] = "Disarm";
   f[1] = "Low Blow";
   f[3] = "Spellthief";
   f[5] = "Evasion";
   f[7] = "Disable";
   f[9] = "Assassinate";
 }
 else {
   f[0] = "Magic Missle";
   f[1] = "Rock Blask";
   f[3] = "Absorb";
   f[5] = "Mana Shield";
   f[7] = "Avalanche";
   f[9] = "Disintegrate";
 }
 return f[i];
}

