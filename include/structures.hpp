#pragma once

/**
 * @struct coordinates
 * @brief Represents a set of coordinates with x and y values.
 */
struct coordinates {
    int x; /**< The x-coordinate. */
    int y; /**< The y-coordinate. */
};

/**
 * @enum TypeCodes
 * @brief Enumeration of type codes with corresponding values.
 */
enum CommandCodes {
    A = 65, /**< Code for command A. */
    B = 66, /**< Code for command B. */
    C = 67, /**< Code for command C. */
    E = 69, /**< Code for command E. */
    K = 75, /**< Code for command K. */
    P = 80, /**< Code for command P. */
    R = 82, /**< Code for command R. */
    S = 83, /**< Code for command S. */
    W = 87 /**< Code for command W. */
};

/**
 * @brief Checks if a file stream is not in a valid state and throws an error message.
 * @param fin The input file stream to check.
 * @param message The error message to display.
 */
void fileNotOk(std::ifstream& fin, std::string message);

/**
 * @brief Checks if an output stream is not in a valid state and throws an error message.
 * @param fin The output stream to check.
 * @param message The error message to display.
 */
void fileNotOk(std::ostream& fin, std::string message);
