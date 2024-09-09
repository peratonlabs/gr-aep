/* -*- c++ -*- */
/*
 * Copyright 2024 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_AEP_AEP_METRIC_IMPL_H
#define INCLUDED_AEP_AEP_METRIC_IMPL_H

#include <gnuradio/aep/aep_metric.h>
#include <armadillo>
using namespace std;
using namespace arma;
namespace gr {
namespace aep {

typedef Mat<complex<float>> cf_mat;
typedef Col<complex<float>> cf_vec;
typedef Mat<float> r_mat;
typedef Col<float> r_vec;

class aep_metric_impl : public aep_metric
{
private:
    int d_nmem;
    int d_num_sc;
    int d_M;
    float d_thresh;

    cf_mat R_old, R_new;
    int item_size;

public:
    aep_metric_impl(int M, int num_sc, int nmem, float thresh);
    ~aep_metric_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_AEP_METRIC_IMPL_H */
