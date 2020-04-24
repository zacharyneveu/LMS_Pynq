#include "nlms_class.h"
#include "datatypes.h"



#define L   11

void lms(axis_t *x, axis_t *y, param_t mu, param_t delta, axis_t *retval)
{
#pragma HLS INTERFACE axis register both port=retval
#pragma HLS INTERFACE axis register both port=y
#pragma HLS INTERFACE axis register both port=x
#pragma HLS INTERFACE s_axilite port=delta
#pragma HLS INTERFACE s_axilite port=mu
#pragma HLS INTERFACE ap_ctrl_none port=return

    static NLMS<L> nlms;
	retval->data = nlms.process(x->data, y->data, mu, delta);
	retval->keep = x->keep;
	retval->strb = x->strb;
	retval->user = x->user;
	retval->last = x->last;
	retval->id = x->id;
	retval->dest = x->dest;
}
