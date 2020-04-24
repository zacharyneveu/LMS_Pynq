#ifndef __DATATYPES_INCLUDE_H__
#define __DATATYPES_INCLUDE_H__
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

// typedef ap_fixed<18,1,AP_RND,AP_SAT> data_t;
// typedef ap_fixed<18,1,AP_RND,AP_SAT> coef_t;
// typedef ap_fixed<18,2,AP_RND,AP_SAT> acc_t;
// typedef ap_fixed<16,1,AP_RND,AP_SAT> param_t;

// typedef ap_int<18> data_t;
// typedef ap_int<18> coef_t;
// typedef ap_int<18> acc_t;
// typedef ap_int<18> param_t;

typedef int data_t;
typedef int coef_t;
typedef int acc_t;
typedef int param_t;

// typedef half data_t;
// typedef half coef_t;
// typedef half acc_t;
// typedef half param_t;

typedef ap_axis<32,1,1,1> axis_t;

#endif
