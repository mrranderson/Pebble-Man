typedef struct {
  int class; // FIGHTER = 0; ROGUE = 1; MAGE = 2
  int level;
  int maxhealth;
  int health;
  int mana;
  int p;
  int d;
  int s;
  int ac;
  int damage;
  //char* classname;
} Character;

int getAC(Character c);
int getDamage(Character c);
char* setClassname(Character c);