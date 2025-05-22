/*
** EPITECH PROJECT, 2025
** Test
** File description:
** main
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <complex>
#include <unordered_map>
#include "fft.hpp"

constexpr int SAMPLE_RATE = 48000;

std::vector<float> analyze(const char *filename, int topN)
{
    FFT fftAnalyzer(filename);

    auto frequencies = fftAnalyzer.getTopFrequencies(topN);
    return frequencies;
}

void parseArgs(int ac, char **av)
{
    if (ac == 4 && std::strcmp(av[1], "--analyze") == 0) {
        auto result = analyze(av[2], std::atoi(av[3]));
        std::cout << "Top " << std::atoi(av[3]) << " frequencies: " << std::endl;
        for (const auto &freq : result) {
            std::cout << freq << std::endl;
        }
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
}

int main(int ac, char **av)
{
    try {
        parseArgs(ac, av);
        return 0;
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
}
