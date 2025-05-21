import numpy as np
import wave
import sys

def get_top_frequencies(file_path, top_n=5):
    # Open the .wav file
    with wave.open(file_path, 'r') as wav_file:
        # Extract raw audio frames and parameters
        n_frames = wav_file.getnframes()
        frame_rate = wav_file.getframerate()
        audio_frames = wav_file.readframes(n_frames)
        n_channels = wav_file.getnchannels()
        sample_width = wav_file.getsampwidth()

        # Convert audio frames to numpy array
        audio_data = np.frombuffer(audio_frames, dtype=np.int16)
        if n_channels > 1:
            audio_data = audio_data[::n_channels]  # Take one channel if stereo

        # Perform FFT
        fft_result = np.fft.fft(audio_data)
        freqs = np.fft.fftfreq(len(fft_result), d=1/frame_rate)

        # Take the positive half of the spectrum
        positive_freqs = freqs[:len(freqs)//2]
        positive_fft = np.abs(fft_result[:len(fft_result)//2])

        # Find the top N frequencies
        top_indices = np.argsort(positive_fft)[-top_n:][::-1]
        top_frequencies = positive_freqs[top_indices]
        top_magnitudes = positive_fft[top_indices]

        return list(zip(top_frequencies, top_magnitudes))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python fft.py <path_to_wav_file>")
        sys.exit(1)

    wav_file_path = sys.argv[1]
    top_frequencies = get_top_frequencies(wav_file_path)

    print("Top 5 Frequencies:")
    for freq, magnitude in top_frequencies:
        print(f"Frequency: {freq:.2f} Hz, Magnitude: {magnitude:.2f}")