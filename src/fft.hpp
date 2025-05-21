/*
** EPITECH PROJECT, 2025
** Stone_Analysis
** File description:
** fft
*/

#ifndef FFT_HPP_
#define FFT_HPP_

class FFT {
public:
    FFT(std::string path);
    ~FFT() = default;

    std::vector<std::complex<float>> getSamples();
    std::vector<float> getTopFrequencies(int n);
private:
    std::vector<std::complex<float>> readWavSamples(const std::string& path);
    size_t nextPowerOf2(size_t n);
    void fft(std::vector<std::complex<float>>& a);

    std::vector<std::complex<float>> _samples;
};

#endif /* !FFT_HPP_ */
