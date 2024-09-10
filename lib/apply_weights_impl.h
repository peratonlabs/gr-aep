/* -*- c++ -*- */
/*
 * Copyright 2024 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_AEP_APPLY_WEIGHTS_IMPL_H
#define INCLUDED_AEP_APPLY_WEIGHTS_IMPL_H

#include <gnuradio/aep/apply_weights.h>

namespace gr {
namespace aep {

class apply_weights_impl : public apply_weights
{
private:
    // Nothing to declare in this block.
    int d_M;
    int d_num_sc;
    int d_num_avg;

    gr_complex* d_sample;

public:
    apply_weights_impl(int M, int num_sc, int num_avg);
    ~apply_weights_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_APPLY_WEIGHTS_IMPL_H */
