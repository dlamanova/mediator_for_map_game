#pragma once
#include "include.hpp"
#include "player.hpp"

/**
 * @class Mediator
 * @brief Acts as a mediator between players and the game environment.
 */
class Mediator {
    int X; /**< The X dimension of the game map. */
    int Y; /**< The Y dimension of the game map. */
    Player players[2]; /**< An array of two players. */
    int curObjId; /**< The current object ID. */

public:
    int rounds; /**< The number of rounds in the game. */
    bool playerTurn; /**< Flag indicating the current player's turn. */
    std::string mapFile; /**< The file containing the game map. */
    std::string statusFile; /**< The file containing game status. */
    std::vector<std::vector<char>> map; /**< The game map represented as a 2D vector of map. */
    std::vector<coordinates> walls; /**< A vector of wall coordinates on the map. */
    std::vector<coordinates> mines; /**< A vector of mine coordinates on the map. */

    /**
     * @brief Constructs a Mediator object with specified parameters.
     * @param mapFile The file containing the game map.
     * @param statusFile The file containing game status.
     * @param player1 The first player object.
     * @param player2 The second player object.
     */
    Mediator(std::string mapFile, std::string statusFile, Player player1, Player player2);

    void swapTurn();
    void round();
    void setX(int x);
    void setY(int y);
    void readMap();
    void findBases();

    /**
     * @brief Finds a mob on specified coordinates.
     * @param x The x-coordinate to search for.
     * @param y The y-coordinate to search for.
     * @return A shared pointer to the found mob, or nullptr if not found.
     */
    std::shared_ptr<Mob> findMobOnCoordinates(int x, int y);

    /**
     * @brief Finds coordinates of a specific type of object.
     * @param c The character representing the object.
     * @return The coordinates of the object.
     */
    coordinates find(char c);

    void findWalls();
    void findMines();
    bool isWallOnCoordinates(int x, int y);

    int getObjId();

    template <typename T>
    int countX(const std::vector<std::vector<T>>& v, int numY);

    template <typename T>
    int countY(std::vector<T>& v);

    template <typename T>
    friend std::istream& operator>>(std::istream& in, std::vector<T>& v);

    template <typename T>
    friend std::istream& operator>>(std::istream& in, std::vector<std::vector<T>>& v);

    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, const std::vector<T>& v);

    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v);
};

// Template operator overloads...

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& v) {
	std::copy(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::back_inserter(v));
	return in;
}

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<std::vector<T> >& v) {
	for (std::string line; std::getline(in, line);) {
		std::istringstream iss(line);
		std::vector<T> row;
		iss >> row;
		v.push_back(row);
	}
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
	std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>(out, " "));
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T> >& v) {
	for (const auto& i : v) {
		out << i << '\n';
	}
	return out;
}

