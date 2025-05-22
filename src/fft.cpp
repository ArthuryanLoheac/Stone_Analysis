#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>
#include "fft.hpp"
#include <bits/stl_numeric.h>
#include <unordered_set>

constexpr int SAMPLE_RATE = 48000;
constexpr int WAV_HEADER_SIZE = 44;

std::vector<std::complex<float>> FFT::readWavSamples(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("Could not open WAV file");

    file.seekg(0, std::ios::end);
    size_t filesize = file.tellg();
    if (filesize < WAV_HEADER_SIZE)
        throw std::runtime_error("Invalid WAV file");

    file.seekg(WAV_HEADER_SIZE);
    size_t sample_count = (filesize - WAV_HEADER_SIZE) / sizeof(int16_t);
    std::vector<int16_t> raw_samples(sample_count);
    file.read(reinterpret_cast<char*>(raw_samples.data()), sample_count *
        sizeof(int16_t));

    std::vector<std::complex<float>> samples;
    for (int16_t sample : raw_samples)
        samples.emplace_back(static_cast<float>(sample), 0.0f);

    return samples;
}

size_t FFT::nextPowerOf2(size_t n) {
    size_t p = 1;
    while (p < n) p <<= 1;
    return p;
}

void FFT::fft(std::vector<std::complex<float>>& a) {
    size_t n = a.size();
    if (n <= 1) return;

    std::vector<std::complex<float>> even(n / 2), odd(n / 2);
    for (size_t i = 0; i < n / 2; i++) {
        even[i] = a[i * 2];
        odd[i] = a[i * 2 + 1];
    }
    fft(even);
    fft(odd);
    for (size_t k = 0; k < n / 2; k++) {
        auto t = static_cast<std::complex<float>>(
            std::polar(1.0, -2.0 * M_PI * k / n) *
            static_cast<std::complex<double>>(odd[k]));
        a[k] = even[k] + t;
        a[k + n / 2] = even[k] - t;
    }
}

FFT::FFT(std::string path) {
    _samples = readWavSamples(path);
    fft(_samples);
}

std::vector<float> FFT::getTopFrequencies(int n) {
    size_t nb = _samples.size();
    std::vector<float> magnitudes(nb / 2);
    for (size_t i = 0; i < nb / 2; i++) {
        magnitudes[i] = std::abs(_samples[i]);
    }
    std::vector<size_t> indices(nb / 2);
    std::iota(indices.begin(), indices.end(), 0);
    std::partial_sort(indices.begin(), indices.begin() + n, indices.end(),
        [&](size_t a, size_t b) { return magnitudes[a] > magnitudes[b]; });

    std::vector<float> top_frequencies;
    for (int i = 0; i < n && i < static_cast<int>(indices.size()); i++) {
        float freq = static_cast<float>(indices[i]) * SAMPLE_RATE / nb;
        top_frequencies.push_back(freq);
    }

    // Sort the frequencies in descending order for display
    std::sort(top_frequencies.begin(), top_frequencies.end(), std::greater<float>());
    return top_frequencies;
}

std::vector<std::complex<float>> FFT::getSamples() {
    return _samples;
}

std::vector<std::complex<float>> FFT::idft(const
    std::vector<std::complex<float>> &freqDomain) {
    size_t n = freqDomain.size();
    std::vector<std::complex<float>> timeDomain(n);
    for (size_t t = 0; t < n; t++) {
        std::complex<float> sum(0.0f, 0.0f);
        for (size_t k = 0; k < n; k++) {
            float angle = 2.0f * M_PI * t * k / n;
            sum += freqDomain[k] * std::polar(1.0f, angle);
        }
        timeDomain[t] = sum / static_cast<float>(n);
    }
    return timeDomain;
}

std::vector<int16_t> FFT::recomposeSignal(const
    std::vector<std::complex<float>> &timeDomain) {
    std::vector<int16_t> signal;
    for (const auto& sample : timeDomain) {
        signal.push_back(static_cast<int16_t>(std::round(sample.real())));
    }
    return signal;
}