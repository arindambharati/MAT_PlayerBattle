#include <iostream>
#include <memory>
using namespace std;

class Constants {
  public:
    static int powerPlayer_Health;
    static int powerPlayer_BaseDamage;
    static int skillPlayer_Health;
    static int skillPlayer_BaseDamage;
    static int ragedPlayer_Health;
    static int ragedPlayer_BaseDamage;

    static void message() {
      cout << "!!Welcome to the Player Battleground!!\n\n";
      cout << "There are 3 types of player in our game\n\n";
      cout << "1. Powerful Player--has High Health, Avg Heal, Low Base Damage, "
              "High Additional Damage\nSpecial Ability-Huge Heal (Heals Higher "
              "Hp)\nDouble Attack! (Attacks two times in a single turn)\n\n2. "
              "Skillful Player--has Avg Health, High Heal, Avg Base Damage, Avg "
              "Additional Damage.\nSpecial Abitlity-Attack Blocker\nHeal + "
              "Damage in single turn\n\n3.Raged Player--has Low Health, very "
              "High Heal, High Base Damage, Very High Additional "
              "Damage.\nSpecial Ability-Dependent on health(Damage increases "
              "when close to death)\nHigh chances for Crititcal Hit\n\n\n\n\n";
    }
};

int Constants ::powerPlayer_Health = 100;
int Constants ::powerPlayer_BaseDamage = 20;
int Constants ::skillPlayer_Health = 75;
int Constants ::skillPlayer_BaseDamage = 50;
int Constants ::ragedPlayer_Health = 50;
int Constants ::ragedPlayer_BaseDamage = 60;

class Player {
  private:
    int health;
    int base_Damage;
    int additional_Damage;
    int heal;

  public:
    int getHealth() { 
      return health; 
    }

    int getBaseDamage() {
      return base_Damage;
    }

    int getAdditionalDamage() {
      return additional_Damage;
    }

    int getHeal() {
       return heal; 
       }

    void setHealth(int addHealth) {
      if (addHealth <= 0) {
        health = 0;
        return;
      }
      health = addHealth;
    }

    void setDamage(int addDamage) { 
      base_Damage = addDamage;
    }

    void setAdditionalDamage(int lowerRange, int upperRange) {
      additional_Damage = (rand() % (upperRange - lowerRange + 1) + lowerRange);
    }

    void setHeal(int lowerRange, int upperRange) {
      heal = (rand() % (upperRange - lowerRange + 1) + lowerRange);
    }

    virtual int giveDamage() = 0;
    virtual void takeDamage(int) = 0;
    virtual void Heal() = 0;
};

class PowerPlayer : public Player {
public:
  PowerPlayer() {
    setHealth(Constants::powerPlayer_Health);
    setDamage(Constants::powerPlayer_BaseDamage);
    cout << "!!PowerPlayer Stats!!" << endl;
    cout << "The health of PowerPlayer is:" << getHealth() << endl;
    cout << "The base_Damage of PowerPlayer is:" << getBaseDamage() << endl;
    cout << "The additional damage is:(5-15)" << endl;
    cout << "The heal capacity of PowerPlayer:(5-10)" << endl;
  }

  int giveDamage() {
    setAdditionalDamage(5, 15);
    return (getAdditionalDamage() + getBaseDamage());
  }

  void takeDamage(int damage) { setHealth(getHealth() - damage); }

  void Heal() {
    setHeal(5, 10);
    int afterHeal=getHealth() + getHeal();
    if(afterHeal>=Constants::powerPlayer_Health){
      afterHeal=Constants::powerPlayer_Health;
    }
    
    setHealth(afterHeal);
  }
};

class SkillPlayer : public Player {
public:
  SkillPlayer() {
    setHealth(Constants::skillPlayer_Health);
    setDamage(Constants::skillPlayer_BaseDamage);
    cout << "!!SkillPlayer Stats!!" << endl;
    cout << "The health of SkillPlayer is:" << getHealth() << endl;
    cout << "The base_Damage of SkillPlayer is:" << getBaseDamage() << endl;
    cout << "The additional damage is:(6-16)" << endl;
    cout << "The heal capacity of SkillPlayer:(5-10)" << endl;
  }

  int giveDamage() {
    setAdditionalDamage(6, 16);
    return (getAdditionalDamage() + getBaseDamage());
  }

  void takeDamage(int damage) { setHealth(getHealth() - damage); }

  void Heal() {
    setHeal(5, 10);
    int afterHeal=getHealth() + getHeal();
    if(afterHeal>=Constants::skillPlayer_Health){
      afterHeal=Constants::skillPlayer_Health;
    }
    setHealth(afterHeal);
  }
};

class RagedPlayer : public Player {

public:
  RagedPlayer() {
    setHealth(Constants::ragedPlayer_Health);
    setDamage(Constants::ragedPlayer_BaseDamage);
    cout << "!!RagedPlayer Stats!!" << endl;
    cout << "The health of RagedPlayer is:" << getHealth() << endl;
    cout << "The base_Damage of RagedPlayer is:" << getBaseDamage() << endl;
    cout << "The additional damage is:(6-16)" << endl;
    cout << "The heal capacity of RagedPlayer:(15-30)" << endl;
  }

  int giveDamage() {
    setAdditionalDamage(6, 16);
    return (getAdditionalDamage() + getBaseDamage());
  }

  void takeDamage(int damage) { setHealth(getHealth() - damage); }

  void Heal() {

    setHeal(15, 30);

    int afterHeal=getHealth() + getHeal();
    if(afterHeal>=Constants::ragedPlayer_Health){
      afterHeal=Constants::ragedPlayer_Health;
    }

    setHealth(afterHeal);
  }
};

class TwoPlayerBattle {
  private:
    shared_ptr<Player> player1, player2, player;

    void SelectPlayer() {
      int counter_for_number_of_Players = 1;
      char selectPlayer;

      while (true) {
        cout << "Select " << counter_for_number_of_Players<< "st type of player(1/2/3):";
        cin >> selectPlayer;
        cout << "\n";
        switch (selectPlayer) {
          case '1': {
            shared_ptr<PowerPlayer> powerPlayer = std::make_shared<PowerPlayer>();
            player = powerPlayer;
            counter_for_number_of_Players++;
            break;
          }

          case '2': {
            shared_ptr<SkillPlayer> skillPlayer = std::make_shared<SkillPlayer>();
            player = skillPlayer;
            counter_for_number_of_Players++;
            break;
          }

          case '3': {
            shared_ptr<RagedPlayer> ragedPlayer = std::make_shared<RagedPlayer>();
            player = ragedPlayer;
            counter_for_number_of_Players++;
            break;
          }

          default: {
            cout << "Wrong Input!!" << endl;
            break;
          }
        }

        if (counter_for_number_of_Players == 2) {
          player1 = player;
        } else if (counter_for_number_of_Players == 3) {
          player2 = player;
          break;
        }
        cout << endl;
      }
    }

public:
  TwoPlayerBattle() {
    Constants::message();
    SelectPlayer();
  }

  void Play() {
    char select_Player_Ability;
    shared_ptr<Player> players[2] = {player1, player2};
    int number_of_Player = sizeof(players) / sizeof(players[0]);
    cout << endl;
    cout << "!!!Game Starts!!!\n";
    while ((player1->getHealth() > 0) && (player2->getHealth() > 0)) {
      for (int index = 0; index < number_of_Player; index++) {
        cout << endl;
        cout << "**Player " << index + 1 << " Turn**" << endl;
        cout << "Input 'D' for Damage 'H' for Heal:";
        cin >> select_Player_Ability;

        switch (select_Player_Ability) {
        case 'D': {
          int damage = players[index]->giveDamage();
          cout << "Damage given by Player " << index + 1 << ":"
               << players[index]->getBaseDamage() << " + "
               << players[index]->getAdditionalDamage() << endl;

          players[(index + 1) % number_of_Player]->takeDamage(damage);
          cout << "Health of Player " << ((index + 1) % number_of_Player) + 1
               << " after Taking Damage:"
               << players[(index + 1) % number_of_Player]->getHealth() << endl;

          cout << endl;
          break;
        }

        case 'H': {
          int health_Without_Heal = players[index]->getHealth();
          players[index]->Heal();
          cout << "Player " << index + 1
               << " Healed by: " << health_Without_Heal << " + "
               << players[index]->getHeal() << endl;

          cout << "Health after Healing:" << players[index]->getHealth();
          cout << endl;
          break;
        }

        default:
          break;
        }

        if (players[(index + 1) % number_of_Player]->getHealth() <= 0) {
          cout << "Player " << index + 1 << " Won the match!!" << endl;
          break;
        }
      }
    }

    cout << "\n!!!Game End!!!";
  }
};

int main() {
  srand(time(NULL));
  TwoPlayerBattle game;
  game.Play();
}