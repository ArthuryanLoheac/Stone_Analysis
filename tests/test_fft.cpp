#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "fft.hpp"

Test(FFT, readWavSamples_valid_file)
{
    const char *testFile = "tests/test.wav";
    std::ofstream outFile(testFile, std::ios::binary);
    char header[44] = {0};
    outFile.write(header, 44);
    std::vector<int16_t> samples = {1, -1, 2, -2, 3, -3};
    outFile.write(reinterpret_cast<const char *>(samples.data()), samples.size() * sizeof(int16_t));
    outFile.close();

    FFT fftAnalyzer(testFile);
    auto samplesRead = fftAnalyzer.getSamples();
    cr_assert_eq(samplesRead.size(), samples.size(), "Le nombre d'échantillons lus doit correspondre.");
}

Test(FFT, getTopFrequencies)
{
    const char *testFile = "tests/test_frequencies.wav";
    std::ofstream outFile(testFile, std::ios::binary);
    char header[44] = {0};
    outFile.write(header, 44);
    std::vector<int16_t> samples(1024, 1); // Signal constant
    outFile.write(reinterpret_cast<const char *>(samples.data()), samples.size() * sizeof(int16_t));
    outFile.close();

    FFT fftAnalyzer(testFile);
    auto topFrequencies = fftAnalyzer.getTopFrequencies(5);
    cr_assert_eq(topFrequencies.size(), 5, "Le nombre de fréquences retournées doit être 5.");
}
