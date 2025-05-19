/*
** EPITECH PROJECT, 2025
** Test
** File description:
** main
*/

#include <iostream>
#include <cstring>

int main(int ac, char **av)
{
    if (ac == 4 && std::strcmp(av[1], "--analyze") == 0) {
        std::cout << "Analyze." << std::endl;
        // Call the analyze function with the provided arguments
        // analyze(av[2], std::atoi(av[3]));
    } else if (ac == 5 && std::strcmp(av[1], "--cypher") == 0) {
        std::cout << "Cypher." << std::endl;
        // Call the cypher function with the provided arguments
        // cypher(av[2], av[3], av[4]);
    } else if (ac == 3 && std::strcmp(av[1], "--decypher") == 0) {
        std::cout << "Decypher." << std::endl;
        // Call the decypher function with the provided argument
        // decypher(av[2]);
    } else {
        std::cout << "USAGE\n./stone_analysis [--analyze IN_FILE N | --cypher IN_FILE OUT_FILE MESSAGE | --decypher IN_FILE]\n" <<
        "IN_FILE An audio file to be analyzed\n" <<
        "OUT_FILE Output audio file of the cypher mode\n" <<
        "MESSAGE The message to hide in the audio file\n" <<
        "N Number of top frequencies to display\n";
    }
    return 0;
}
