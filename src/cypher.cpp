#include "fft.hpp"
#include "const.hpp"
#include "cypher.hpp"

std::string cryptMessage(const char *message)
{
    std::string cryptedMessage;
    size_t count = 0;
    for (size_t i = 0; i < strlen(message); i++) {
        cryptedMessage += message[i] ^ XOR_KEY;
        count++;
        if (count == 10) {
            cryptedMessage += SEPARATOR;
            count = 0;
        }
    }
    return cryptedMessage;
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