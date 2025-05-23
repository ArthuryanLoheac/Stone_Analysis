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
constexpr int WAV_HEADER_SIZE = 44;

std::vector<float> analyze(const char *filename, int topN)
{
    FFT fftAnalyzer(filename);

    auto frequencies = fftAnalyzer.getTopFrequencies(topN);
    return frequencies;
}

std::string cryptMessage(const char *message)
{
    std::string cryptedMessage;
    for (size_t i = 0; i < strlen(message); i++) {
        cryptedMessage += message[i] ^ 0xFF; // XOR with 0xFF
    }
    return cryptedMessage;
}

std::string decryptMessage(const std::string &message)
{
    std::string decryptedMessage;
    for (size_t i = 0; i < message.size(); i++) {
        decryptedMessage += message[i] ^ 0xFF; // XOR with 0xFF
    }
    return decryptedMessage;
}

void cypher(const char *inputFile, const char *outputFile, const char *message) {
    std::string messageCrypted = cryptMessage(message);
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile)
        throw std::runtime_error("Le fichier d'entrée est introuvable.");

    char header[WAV_HEADER_SIZE];
    inFile.read(header, WAV_HEADER_SIZE);
    if (inFile.gcount() != WAV_HEADER_SIZE)
        throw std::runtime_error("Le fichier d'entrée n'est pas un fichier WAV valide.");

    std::vector<char> audioData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    size_t messageLength = messageCrypted.size();
    for (size_t i = 50; i < 50 + messageLength + 1; i++) {
        if (i >= audioData.size()) {
            throw std::runtime_error("Le message est trop long pour être caché dans le fichier audio.");
        }
        audioData[i] = (i - 50 < messageLength) ? messageCrypted[i - 50] : '\0';
    }
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile)
        throw std::runtime_error("Impossible de créer le fichier de sortie.");

    outFile.write(header, WAV_HEADER_SIZE);
    outFile.write(audioData.data(), audioData.size());
    outFile.close();
}

void decypher(const char *inputFile) {
    // Ouvrir le fichier d'entrée
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Le fichier d'entrée est introuvable.");
    }

    char header[WAV_HEADER_SIZE];
    inFile.read(header, WAV_HEADER_SIZE);
    if (inFile.gcount() != WAV_HEADER_SIZE) {
        throw std::runtime_error("Le fichier d'entrée n'est pas un fichier WAV valide.");
    }

    std::vector<char> audioData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    std::string hiddenMessage;
    for (size_t i = 50; i < audioData.size(); i++) {
        if (audioData[i] == '\0') {
            break; // Fin du message
        }
        hiddenMessage += audioData[i];
    }
    std::cout << decryptMessage(hiddenMessage) << std::endl;
}

void parseArgs(int ac, char **av)
{
    if (ac == 4 && std::strcmp(av[1], "--analyze") == 0) {
        auto result = analyze(av[2], std::atoi(av[3]));
        std::cout << "Top " << std::atoi(av[3]) << " frequencies: " << std::endl;
        for (const auto &freq : result) {
            printf("%.1f Hz\n", freq);
        }
    } else if (ac == 5 && std::strcmp(av[1], "--cypher") == 0) {
        cypher(av[2], av[3], av[4]); // Appel de la fonction cypher
    } else if (ac == 3 && std::strcmp(av[1], "--decypher") == 0) {
        decypher(av[2]); // Appel de la fonction decypher
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
