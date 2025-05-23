/*
** EPITECH PROJECT, 2025
** Stone_Analysis
** File description:
** fft
*/

#ifndef FFT_HPP_
#define FFT_HPP_
#include <vector>
#include <cstdint>
#include <complex>


class FFT {
public:
    FFT(std::string path);
    ~FFT() = default;

    std::vector<std::complex<float>> getSamples();
    std::vector<float> getTopFrequencies(int n);
    std::vector<std::complex<float>> idft(const
        std::vector<std::complex<float>> &freqDomain);
    std::vector<int16_t> recomposeSignal(const
        std::vector<std::complex<float>> &timeDomain);
    std::vector<float> getAllFrequencies();
private:
    std::vector<std::complex<float>> readWavSamples(const std::string& path);
    size_t nextPowerOf2(size_t n);
    void fft(std::vector<std::complex<float>>& a);

    std::vector<std::complex<float>> _samples;
};

#endif /* !FFT_HPP_ */
