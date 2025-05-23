#include "fft.hpp"
#include "const.hpp"
#include "cypher.hpp"

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
            printf("%.1f Hz\n", freq);
        }
    } else if (ac == 5 && std::strcmp(av[1], "--cypher") == 0) {
        cypher(av[2], av[3], av[4]);
    } else if (ac == 3 && std::strcmp(av[1], "--decypher") == 0) {
        decypher(av[2]);
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
