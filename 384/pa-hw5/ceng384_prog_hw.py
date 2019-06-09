#!/usr/bin/env python

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from scipy.io import wavfile

def tic():
    import time
    global startTime_for_tictoc
    startTime_for_tictoc = time.time()

def toc():
    import time
    if 'startTime_for_tictoc' in globals():
        print "Elapsed time is " + str(time.time() - startTime_for_tictoc) + " seconds."
    else:
        print "Toc: start time not set"

class Sound:
    def __init__(self, filename, verbose=False):
        # Load data
        sampling_rate, sound_data = wavfile.read(filename)

        #Convert data to floating values ranging from -1 to 1:
        sound_data = sound_data / (2. ** 15)

        #If two channels, then select only one channel
        if sound_data.ndim > 1:
            sound_data = sound_data[:, 0]

        self.data = sound_data
        self.sampling_rate = sampling_rate
        self.duration = sound_data.shape[0] / float(sampling_rate)
        self.number_of_samples = sound_data.shape[0]

        if verbose:
            print "Sound() is finishing with:"
            print "\t source file: ", filename
            print "\t sampling rate (Hz): ", self.sampling_rate
            print "\t duration (s): ", self.duration
            print "\t number of samples: ", self.number_of_samples


    def plot_sound(self, name=""):
        #Create an array of time values
        time_values = np.arange(0, self.number_of_samples, 1) / float(self.sampling_rate)

        #Convert to milliSeconds
        time_values = time_values * 1000

        fig, ax = plt.subplots()

        plt.plot(time_values, self.data, color='G')
        plt.xlabel('Time (ms)')
        plt.ylabel('Amplitude')
        plt.title(name)
        plt.show()


def dft(x):
    """
        Calculate Discrete Fourier Transform (DFT) for 1D signal x.

        x: A 1D signal of length N.
            Could be a Python iterable object or a Numpy array.

        Output:
            F_x: A 1D complex array, denoting the DFT of x. Its length
                should be N.
    """
    N = len(x)
    F_x = np.zeros(N, dtype=np.complex128)

    ###########################################################################
    #                        YOUR SOLUTION                                    #
    ###########################################################################
    for k in range(N):
        for n in range(N):
            lst = [-1j * k * (2 * np.pi / N) * n]
            F_x[k] += x[n] * np.exp(lst)

    ###########################################################################

    return F_x


def calculate_spectogram(x, window_size=100, stride=50, dft_function=None):
    """
        Calculate the spectogram (S) for 1D signal x.

        x: A 1D signal of length N.
            Could be a Python iterable object or a Numpy array.
        window_size: The length of the segment for which we will calculate DFT.
        stride: How many samples will be skipped between window positions.
        dft_function: The DFT function to use. Since your implementation
            will be very slow, you should use np.fft.fft() here.

        Output:
            S: A numpy complex 2D array, denoting the S of x.
    """
    N = len(x)

    ###########################################################################
    #                        YOUR SOLUTION                                    #
    ###########################################################################
    S = []
    i = 0
    while (i*stride) + window_size-1 < N:
        S.append(dft_function(x[i*stride : (i*stride) + window_size-1]))
        i += 1

    ###########################################################################

    return np.array(S)


def plot_spectogram(S, stride=50, window_size=100, duration=5, Fs=100, name=""):
    t = np.linspace(0, duration, len(S))
    f = np.arange(0, window_size / 2, dtype=np.float) * Fs / window_size # Hz

    # Since DFT is symmetric, we take only half:
    S = S[:, 0:int(window_size/2)]

    # find magnitude of S
    S = np.abs(S) #/ (window_size/2)

    # logarithmic scale (decibel)
    epsilon = 10**-13
    S = 20 * np.log10(S+epsilon) # To get rid of division-by-zero errors

    fig, ax = plt.subplots()
    plt.pcolormesh(t, f, S.transpose(), cmap=plt.get_cmap('jet'))

    #plt.yscale('symlog', linthreshy=1000, linscaley=0.25)
    #ax.yaxis.set_major_formatter(matplotlib.ticker.ScalarFormatter())

    plt.xlim(t[0], t[-1])
    plt.ylim(f[0], f[-1])

    plt.xlabel("Time (s)")
    plt.ylabel("Frequency (Hz)")

    plt.title(name)

    cbar = plt.colorbar()
    cbar.set_label("Intensity (dB)")
