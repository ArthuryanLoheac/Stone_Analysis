#include "fft.hpp"
#include "const.hpp"
#include "cypher.hpp"

std::string decryptMessage(const std::string &message)
{
    std::string decryptedMessage;
    for (char c : message) {
        if (c != SEPARATOR) {
            decryptedMessage += c ^ XOR_KEY;
        }
    }
    return decryptedMessage;
}

void decypher(const char *inputFile) {
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
            break;
        }
        hiddenMessage += audioData[i];
    }
    std::cout << decryptMessage(hiddenMessage) << std::endl;
}