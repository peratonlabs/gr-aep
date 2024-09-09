/* -*- c++ -*- */
/*
 * Copyright 2024 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_AEP_SPATIAL_COV_PER_SC_IMPL_H
#define INCLUDED_AEP_SPATIAL_COV_PER_SC_IMPL_H

#include <gnuradio/aep/spatial_cov_per_sc.h>

#include <vector>

using namespace std;
#include <armadillo>
using namespace arma;

#include "aep_metric_impl.h"
namespace gr {
namespace aep {

class spatial_cov_per_sc_impl : public spatial_cov_per_sc
{
private:
    int d_num_avg;
    int d_fft_size;
    int d_M;

    vector<vector<gr_complex>> d_sample_buf; // for each of the M streams
    int d_sample_buf_index;

    gr_complex* buf_a;
    gr_complex* buf_b;

    cf_mat Xs;
    cf_mat R;

    void calc_spatial_covariance(gr_complex* out);

public:
    spatial_cov_per_sc_impl(int M, int fft_size, int num_avg);
    ~spatial_cov_per_sc_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_SPATIAL_COV_PER_SC_IMPL_H */
