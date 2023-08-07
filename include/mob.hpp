#pragma once
#include "include.hpp"
#include "structures.hpp"

/**
 * @class Mob
 * @brief Represents a mobile entity in the game.
 */
class Mob {
public:
    char type; /**< The type of the mob. */
    int ID; /**< The ID of the mob. */
    int x; /**< The x-coordinate of the mob's position. */
    int y; /**< The y-coordinate of the mob's position. */
    int hitPoint; /**< The hit points of the mob. */
    bool isEnemy; /**< Flag indicating whether the mob is an enemy. */
    char product; /**< The product type of the mob. */
    int maxVelocity; /**< The maximum velocity of the mob. */
    int velocity; /**< The current velocity of the mob. */
    int cost; /**< The cost of the mob. */
    int attackRange; /**< The attack range of the mob. */
    int buildTime; /**< The build time of the mob. */
    std::unordered_map<int, int> dmg; /**< The damage values against various mob types. */

    /**
     * @brief Constructs a Mob object with specified parameters.
     * @param type The type of the mob.
     * @param hitPoint The hit points of the mob.
     * @param velocity The velocity of the mob.
     * @param cost The cost of the mob.
     * @param attackRange The attack range of the mob.
     * @param buildTime The build time of the mob.
     */
    Mob(char type, int hitPoint, int velocity, int cost, int attackRange, int buildTime) : type(type), product(0), isEnemy(0), hitPoint(hitPoint), velocity(velocity), maxVelocity(velocity), cost(cost), attackRange(attackRange), buildTime(buildTime) {};

    /**
     * @brief Default constructor for the Mob class.
     */
    Mob() {};

    /**
     * @brief Converts the mob's attributes to a string representation.
     * @return A string representation of the mob.
     */
    virtual operator std::string() const {
		return this->type + " " + std::to_string(this->getID()) + " " + std::to_string(this->x) + " " + std::to_string(this->y) + " " + std::to_string(this->hitPoint);
	};

    /**
     * @brief Moves the mob to a specified position.
     * @param x The target x-coordinate.
     * @param y The target y-coordinate.
     * @param map The map containing game entities.
     */
    void move(int x, int y, std::vector<std::vector<char>> map);

    /**
     * @brief Initiates an attack against an enemy mob.
     * @param enemy The target enemy mob to attack.
     */
    void attack(std::shared_ptr<Mob> enemy);
    /**
     * @brief Retrieves the ID of the mob.
     * @return The ID of the mob.
     */
    int getID() const{
		return this->ID;
	};

    /**
     * @brief Retrieves the damage value of the mob against a specific type.
     * @param type The type of the target mob.
     * @return The damage value against the specified type.
     */
    int getAttack(char type){
		return dmg[type];
	};
    virtual ~Mob() = default;
};


/**
 * @class Base
 * @brief Represents a base mob in the game, which is a specialized form of the Mob class.
 */
class Base : public Mob {
public:
    /**
     * @brief Constructs a Base object with specified parameters.
     * @param id The ID of the base.
     * @param x The x-coordinate of the base's position.
     * @param y The y-coordinate of the base's position.
     */
    Base(int id, int x, int y) : Mob(B, 200, 0, 0, 0, 0) { this->ID = id; this->x = x; this->y = y; };

    /**
     * @brief Converts the base's attributes to a string representation.
     * @return A string representation of the base.
     */
    operator std::string() const{
		std::string st = this->type + " " + std::to_string(this->getID()) + " " + std::to_string(this->x) + " " + std::to_string(this->y) + " " + std::to_string(this->hitPoint);
		if (product != B) {
			st += " " [+this->product];
		}
		return st;
	};

    /**
     * @brief Retrieves the damage value of the base (always returns 0 for Base).
     * @param type The type of the target mob.
     * @return The damage value (always 0).
     */
    int getAttack() {
		return 0;
	};
};


/**
 * @class Knight
 * @brief Represents a knight mob in the game.
 */
class Knight : public Mob {
public:
    /**
     * @brief Constructs a Knight object with specified parameters.
     * @param id The ID of the knight.
     * @param x The x-coordinate of the knight's position.
     * @param y The y-coordinate of the knight's position.
     */
    Knight(int id, int x, int y): Mob(K, 70, 5, 400, 1, 5) { this->ID = id; this->x = x; this->y = y; 
	this->dmg.insert(std::make_pair(K, 35));
	this->dmg.insert(std::make_pair(S, 35));
	this->dmg.insert(std::make_pair(A, 35));
	this->dmg.insert(std::make_pair(P, 35));
	this->dmg.insert(std::make_pair(C, 35));
	this->dmg.insert(std::make_pair(R, 50));
	this->dmg.insert(std::make_pair(W, 35));
	this->dmg.insert(std::make_pair(B, 35));
	};;
};

/**
 * @class Swordsman
 * @brief Represents a swordsman mob in the game.
 */
class Swordsman : public Mob {
public:
    /**
     * @brief Constructs a Swordsman object with specified parameters.
     * @param id The ID of the swordsman.
     * @param x The x-coordinate of the swordsman's position.
     * @param y The y-coordinate of the swordsman's position.
     */
    Swordsman(int id, int x, int y) : Mob(S, 60, 2, 250, 1, 3) { this->ID = id; this->x = x; this->y = y; 
	this->dmg.insert(std::make_pair(K, 30));
	this->dmg.insert(std::make_pair(S, 30));
	this->dmg.insert(std::make_pair(A, 30));
	this->dmg.insert(std::make_pair(P, 20));
	this->dmg.insert(std::make_pair(C, 20));
	this->dmg.insert(std::make_pair(R, 30));
	this->dmg.insert(std::make_pair(W, 30));
	this->dmg.insert(std::make_pair(B, 30));
	};
};

/**
 * @class Archer
 * @brief Represents an archer mob in the game.
 */
class Archer : public Mob {
public:
    /**
     * @brief Constructs an Archer object with specified parameters.
     * @param id The ID of the archer.
     * @param x The x-coordinate of the archer's position.
     * @param y The y-coordinate of the archer's position.
     */
    Archer(int id, int x, int y) : Mob(A, 40, 2, 250, 5, 3) { this->ID = id; this->x = x; this->y = y; 
	this->dmg.insert(std::make_pair(K, 15));
	this->dmg.insert(std::make_pair(S, 15));
	this->dmg.insert(std::make_pair(A, 15));
	this->dmg.insert(std::make_pair(P, 15));
	this->dmg.insert(std::make_pair(C, 10));
	this->dmg.insert(std::make_pair(R, 10));
	this->dmg.insert(std::make_pair(W, 15));
	this->dmg.insert(std::make_pair(B, 15));
	};
};

/**
 * @class Pikeman
 * @brief Represents a pikeman mob in the game.
 */
class Pikeman : public Mob {
public:
    /**
     * @brief Constructs a Pikeman object with specified parameters.
     * @param id The ID of the pikeman.
     * @param x The x-coordinate of the pikeman's position.
     * @param y The y-coordinate of the pikeman's position.
     */
    Pikeman(int id, int x, int y) : Mob(P, 50, 2, 200, 2, 3) { this->ID = id; this->x = x; this->y = y; 
	this->dmg.insert(std::make_pair(K, 35));
	this->dmg.insert(std::make_pair(S, 15));
	this->dmg.insert(std::make_pair(A, 15));
	this->dmg.insert(std::make_pair(P, 15));
	this->dmg.insert(std::make_pair(C, 15));
	this->dmg.insert(std::make_pair(R, 10));
	this->dmg.insert(std::make_pair(W, 15));
	this->dmg.insert(std::make_pair(B, 10));
	};
};

/**
 * @class Ram
 * @brief Represents a ram mob in the game.
 */
class Ram : public Mob {
public:
    /**
     * @brief Constructs a Ram object with specified parameters.
     * @param id The ID of the ram.
     * @param x The x-coordinate of the ram's position.
     * @param y The y-coordinate of the ram's position.
     */
    Ram(int id, int x, int y): Mob(R, 90, 2, 500, 1, 4) { this->ID = id; this->x = x; this->y = y; 
	this->dmg.insert(std::make_pair(K, 10));
	this->dmg.insert(std::make_pair(S, 10));
	this->dmg.insert(std::make_pair(A, 10));
	this->dmg.insert(std::make_pair(P, 10));
	this->dmg.insert(std::make_pair(C, 10));
	this->dmg.insert(std::make_pair(R, 10));
	this->dmg.insert(std::make_pair(W, 10));
	this->dmg.insert(std::make_pair(B, 50));
	};
};

/**
 * @class Catapult
 * @brief Represents a catapult mob in the game.
 */
class Catapult : public Mob {
public:
    /**
     * @brief Constructs a Catapult object with specified parameters.
     * @param id The ID of the catapult.
     * @param x The x-coordinate of the catapult's position.
     * @param y The y-coordinate of the catapult's position.
     */
    Catapult(int id, int x, int y) : Mob(C, 50, 2, 800, 7, 6) { this->ID = id; this->x = x; this->y = y; 
	this->dmg.insert(std::make_pair(K, 40));
	this->dmg.insert(std::make_pair(S, 40));
	this->dmg.insert(std::make_pair(A, 40));
	this->dmg.insert(std::make_pair(P, 40));
	this->dmg.insert(std::make_pair(C, 40));
	this->dmg.insert(std::make_pair(R, 40));
	this->dmg.insert(std::make_pair(W, 40));
	this->dmg.insert(std::make_pair(B, 50));
	};
};

/**
 * @class Worker
 * @brief Represents a worker mob in the game.
 */
class Worker : public Mob {
public:
    /**
     * @brief Constructs a Worker object with specified parameters.
     * @param id The ID of the worker.
     * @param x The x-coordinate of the worker's position.
     * @param y The y-coordinate of the worker's position.
     */
    Worker(int id, int x, int y) : Mob(W, 20, 2, 100, 1, 2) { this->ID = id; this->x = x; this->y = y; 
	this->dmg.insert(std::make_pair(K, 5));
	this->dmg.insert(std::make_pair(S, 5));
	this->dmg.insert(std::make_pair(A, 5));
	this->dmg.insert(std::make_pair(P, 5));
	this->dmg.insert(std::make_pair(C, 5));
	this->dmg.insert(std::make_pair(R, 5));
	this->dmg.insert(std::make_pair(W, 5));
	this->dmg.insert(std::make_pair(B, 1));
	};
};

