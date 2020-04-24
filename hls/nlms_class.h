#include "datatypes.h"

/**
 * Treat integers like fixed point numbers by dividing after multiply
 * operations. Idea is, weights less than size IDENTITY are treated as <1
 * while weights > IDENTITY are treated as >1
 */
#define IDENTITY 16384 // 2^14

template<int L>
class NLMS {

    data_t sr[L];
    acc_t yhat;
    coef_t w[L];
    public:
        acc_t process(data_t  x, data_t y, param_t mu, param_t delta);
		void fill_sr(data_t x);
        void init(void);
};

template<int L>
acc_t NLMS<L>::process(data_t x, data_t y, param_t mu, param_t delta)
{
    // update shift reg and accumulate 
    yhat = 0;
SR_LOOP:
    for (int i = L-1; i > 0; i--)
    {
#pragma HLS UNROLL
        sr[i] = sr[i-1];
        yhat += sr[i]*w[i]/IDENTITY;
    }
    sr[0] = x;
    yhat += sr[0]*w[0]/IDENTITY;

	acc_t xtx = 0;
XTX_LOOP:
	for (int i = 0; i < L; ++i) {
#pragma HLS UNROLL
		xtx += sr[i]*sr[i]/IDENTITY;
	}

    // update weights
    data_t nu;
WEIGHTS_LOOP:
    for (int i = 0; i < L; i++)
    {
#pragma HLS UNROLL
        nu = mu / (delta + xtx);
        w[i] += (y-yhat)*nu*sr[i]/IDENTITY;
    }
	return yhat;
}

template<int L>
void NLMS<L>::fill_sr(data_t x)
{
    for (int i = L; i > 0; i--)
    {
        sr[i] = sr[i-1];
    }
    sr[0] = x;
}
	
