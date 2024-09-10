/* -*- c++ -*- */
/*
 * Copyright 2024 Peraton Labs Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_AEP_AEP_CHANNEL_PROCESSING_IMPL_H
#define INCLUDED_AEP_AEP_CHANNEL_PROCESSING_IMPL_H

#include <gnuradio/aep/aep_channel_processing.h>

#include <armadillo>
#include <vector>
using namespace std;
using namespace arma;

#include "aep_metric_impl.h" // for now for the typedefs - move this out eventually

namespace gr {
namespace aep {

class aep_channel_processing_impl : public aep_channel_processing
{
private:
    float d_thresh;
    int d_num_sc;
    int d_M;

    int d_sample_num;

    vector<vector<gr_complex>> weight_vectors;
    vector<float> prev_metric; // save the metric from the previous sample window

public:
    aep_channel_processing_impl(int M, int num_sc, float thresh);
    ~aep_channel_processing_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_AEP_CHANNEL_PROCESSING_IMPL_H */
