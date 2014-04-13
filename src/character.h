typedef struct {
  int class; // FIGHTER = 0; ROGUE = 1; MAGE = 2
  int level;
  int xp;
  int health;
  int mana;
  int p;
  int d;
  int s;
  int ac;
  int damage;
  int difficulty;
  //char* classname;
} Character;

int getAC(Character c);
int getDamage(Character c);
char* setClassname(Character c);
void levelUp(Character* c);
char* getSkill(Character c, int i);
void restore(Character* original, Character* backup);