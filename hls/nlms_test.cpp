#include <iostream>
#include "nlms_class.h"
#include <cmath>
#include <random>
#include <fstream>
#include <cstdio>

#define L   21
#define SAMP_LEN 1000
using namespace std;

int main(void)
{
    data_t x[SAMP_LEN+L];
    data_t y[SAMP_LEN];
    data_t yhat[SAMP_LEN];
    data_t errors[SAMP_LEN];

    param_t mu = 1;
	param_t delta = 0.001;
	float SNR = 10;

	// FIR low pass filter taps
    data_t taps[L] = {
    -0.02010411882885732,
    -0.05842798004352509,
    -0.061178403647821976,
    -0.010939393385338943,
    0.05125096443534972,
    0.033220867678947885,
    -0.05655276971833928,
    -0.08565500737264514,
    0.0633795996605449,
    0.310854403656636,
    0.4344309124179415,
    0.310854403656636,
    0.0633795996605449,
    -0.08565500737264514,
    -0.05655276971833928,
    0.033220867678947885,
    0.05125096443534972,
    -0.010939393385338943,
    -0.061178403647821976,
    -0.05842798004352509,
    -0.02010411882885732
    };
    // generate data

    default_random_engine gen; 
    normal_distribution<float> x_sampler(0, 1);
	normal_distribution<float> noise(0, 1.0/SNR);

	for (int j = 0; j < SAMP_LEN+L; ++j) {
		x[j] = x_sampler(gen);
		
	}

    for (int i = 0; i < SAMP_LEN; i++)
    {
        y[i] = 0;
        for (int j = 0; j < L; j++)
        {
            y[i] += x[i+j]*taps[j];
        }
		y[i] += noise(gen);
    }

    NLMS<L> filt;

	for (int i = 0; i < L; ++i) {
		filt.fill_sr(x[i]);
	}
    for (int i = 0; i < SAMP_LEN; i++)
    {
        yhat[i] = filt.process(x[i+L], y[i], mu, delta);
        errors[i] = pow(y[i]-yhat[i], 2);
    }


    //cout << "MSEs: ";
	remove("NLMS_MSEs.csv");
	ofstream f("NLMS_MSEs.csv");
	f << "x,y,yhat,MSE" << endl;
    for (int i = 0; i < SAMP_LEN; i++)
    {
        // cout << errors[i] << endl;
		f << x[i+L] << "," << y[i] << "," << yhat[i] << "," << errors[i] << endl;
    }
    
    if (errors[SAMP_LEN] <= errors[0])
    {
        cout << "Congrats, loss actually decreased!" << endl;
        return 0;
    }
    else
    {
        cout << "hmm... error increased for some reason" << endl;
        return 1;
    }
    
}
