#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;
// Generate a random number between the minimum and maximum
int getRandomNumber(int min, int max)
{
	//generate the max number between min and max
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	//evenly distribute the generation of the range value 
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);

}

//creating the Creature class
class Creature
{
	//the protected specifier opens access to members only to friendly and child classes
protected:
	//create member variables
	string m_name;
	char  m_symbol;
	int m_health;
	int m_damage;
	int m_gold;
public:
	//Creature constructor to initialize class members
	Creature(string name, char symbol, int health, int damage, int gold)
		:m_name(name), m_symbol(symbol), m_health(health), m_damage(damage), m_gold(gold)
	{
	}
	// getters, accessor functions that simply return a value
	char getSymbol() { return m_symbol; }
	const std::string& getName() { return m_name; }
	bool isDead() { return m_health <= 0; }
	int getGold() { return m_gold; }
	void addGold(int gold) { m_gold += gold; }
	void reduceHealth(int health) { m_health -= health; }
	int getHealth() { return m_health; }
	int getDamage() { return m_damage; }


};
//Child class Player that inherits from parent class Creature
class Player :public Creature
{
	int m_level = 1;
public:
	Player(string name)
		: Creature(name, '@', 10, 1, 0)
	{

	}
	void levelUp()
	{
		++m_level;
		++m_damage;
	}
	int getLevel() { return m_level; }
	bool hasWon() { return m_level >= 3; }
};
//Child class Monster that inherits from parent class Creature
class Monster : public Creature
{
public:
	//list of types that contains the name of the monsters and their maximum number
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};
	//structure with a separate element for each type of monster
	struct MonsterData
	{
		const char* name;
		char symbol;
		int health;
		int damage;
		int gold;

	};

	//Declaring a static array of this structure named monsterData.
	static MonsterData monsterData[MAX_TYPES];
	Type m_type;

	Monster(Type type)
		:Creature(monsterData[type].name, monsterData[type].symbol, monsterData[type].health,
			monsterData[type].damage, monsterData[type].gold), m_type(type)
	{

	}
	static Monster getRandomMonster()
	{
		int num = getRandomNumber(0, MAX_TYPES - 1);
		return Monster(static_cast<Type>(num));
	}


};
//code for defining our lookup table outside the class body
Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'o', 4, 2, 25 },
	{ "slime", 's', 1, 1, 10 }

};
// This method handles the player attacking the monster
void attackMonster(Player& p, Monster& m)
{
	// If the player is dead, then he cannot attack the monster
	if (p.isDead())
		return;

	std::cout << "You hit the " << m.getName() << " for " << p.getDamage() << " damage.\n";

	// Monster health decreases from player damage
	m.reduceHealth(p.getDamage());


	// If the monster is dead, then increase the player's level
	if (m.isDead())
	{
		std::cout << "You killed the " << m.getName() << ".\n";
		p.levelUp();
		std::cout << "You are now level " << p.getLevel() << ".\n";
		std::cout << "You found " << m.getGold() << " gold.\n";
		p.addGold(m.getGold());
	}
}
// This method handles the player's monster attack
void attackPlayer(Monster& m, Player& p)
{
	// This method handles the player's monster attack
	if (m.isDead())
		return;

	// The player's health is reduced by monster damage
	p.reduceHealth(m.getDamage());
	std::cout << "The " << m.getName() << " hit you for " << m.getDamage() << " damage and you still have " << p.getHealth() << "\n";
}
// This method handles the entire fight between the player and a random monster
void fightMonster(Player& p)
{
	// First we generate a random monster
	Monster m = Monster::getRandomMonster();
	std::cout << "You have encountered a " << m.getName() << " (" << m.getSymbol() << ").\n";

	// As long as the monster or player is not dead, the battle continues
	while (!m.isDead() && !p.isDead())
	{
		std::cout << "(R)un or (F)ight: ";
		char input;
		std::cin >> input;
		if (input == 'R' || input == 'r')
		{
			// 50/50 chance of successful escape
			if (getRandomNumber(1, 2) == 1)
			{
				std::cout << "You successfully fled.\n";
				return; // we managed to avoid meeting the monster
			}
			else
			{
				// Failing to escape gives the monster the right to attack
				std::cout << "You failed to flee.\n";
				attackPlayer(m, p);
				continue;

			}
		}
		if (input == 'F' || input == 'f')
		{
			// Player attacks first, then monster
			attackMonster(p, m);
			attackPlayer(m, p);

		}
	}
}
int main()
{
	// set the system clock value as the starting number
	srand(static_cast<unsigned int>(time(0)));
	// reset the first result
	rand();

	std::cout << "Enter your name: ";
	std::string playerName;
	cin >> playerName;

	Player p(playerName);
	std::cout << "Welcome, " << p.getName() << '\n';

	// If the player is not dead and has not yet won, then the game continues
	while (!p.isDead() && !p.hasWon())
		fightMonster(p);

	// At this point the player is either dead or has won
	if (p.isDead())
	{
		std::cout << "You died at level " << p.getLevel() << " and with " << p.getGold() << " gold.\n";
		std::cout << "Too bad you can't take it with you!\n";
	}
	else
	{
		std::cout << " You have  " << p.getHealth() << " health   and " << "You won the game with " << p.getGold() << " gold!\n";
	}

	return 0;
}

