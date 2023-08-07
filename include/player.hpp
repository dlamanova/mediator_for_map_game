#pragma once
#include "mob.hpp"
/**
 * @class Player
 * @brief Represents a player in the game.
 */
class Player {
public:
    long int money = 2000; /**< The amount of money the player has. */
    std::string rozkazyfile; /**< The file containing commands for the player. */
    std::string file; /**< The player's file. */
    std::shared_ptr<Mob> base; /**< The player's base mob. */
    Mob* buildedMob; /**< The currently built mob. */
    std::unordered_map<int, std::shared_ptr<Mob>> mobs; /**< A map of player's mobs. */

    /**
     * @brief Constructs a new Player object with given files.
     * @param rozkazyFile The file containing commands for the player.
     * @param file The player's file.
     */
    Player(std::string rozkazyFile, std::string file) : rozkazyfile(rozkazyFile), file(file) {};

    /**
     * @brief Default constructor for the Player class.
     */
    Player() {};

    /**
     * @brief Finds a mob belonging to the player at the specified coordinates.
     * @param x The x-coordinate to search for.
     * @param y The y-coordinate to search for.
     * @return A shared pointer to the found mob, or nullptr if not found.
     */
    std::shared_ptr<Mob> findPlayerMobOnCoordinates(int x, int y);

    /**
     * @brief Spends a certain amount of money from the player's funds.
     * @param cnt The amount of money to spend.
     * @return The remaining amount of money after spending.
     */
    long int spend(long int cnt);

    /**
     * @brief Reloads player's resources or assets.
     */
    void reload();

    /**
     * @brief Digs in specified mines to gather resources.
     * @param mines A vector of coordinates representing the mines to dig.
     */
    void dig(std::vector<coordinates> mines);
};
