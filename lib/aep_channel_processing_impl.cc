/* -*- c++ -*- */
/*
 * Copyright 2024 Peraton Labs Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include "aep_channel_processing_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace aep {

aep_channel_processing::sptr aep_channel_processing::make(int M, int num_sc, float thresh)
{
    return gnuradio::get_initial_sptr(new aep_channel_processing_impl(M, num_sc, thresh));
}

aep_channel_processing_impl::aep_channel_processing_impl(int M, int num_sc, float thresh)
    : gr::sync_block("aep_channel_processing",
                     gr::io_signature::make2(
                         2, 2, num_sc * sizeof(float), M * num_sc * sizeof(gr_complex)),
                     gr::io_signature::make(1, 1, M * num_sc * sizeof(gr_complex)))
{
    d_num_sc = num_sc;
    d_M = M;
    d_thresh = thresh;

    d_sample_num = 0;

    // Initialize all the weight vectors to single element
    weight_vectors.resize(d_num_sc);
    for (int i = 0; i < d_num_sc; i++) {
        weight_vectors[i].resize(d_M);
        weight_vectors[i][0] = gr_complex(1.0, 0.0);
    }

    prev_metric.resize(d_num_sc);
    for (int i = 0; i < d_num_sc; i++)
        prev_metric[i] = 0.0;
}

/*
 * Our virtual destructor.
 */
aep_channel_processing_impl::~aep_channel_processing_impl() {}

int aep_channel_processing_impl::work(int noutput_items,
                                      gr_vector_const_void_star& input_items,
                                      gr_vector_void_star& output_items)
{
    const float* aep_metric = (const float*)input_items[0];     // The AEP metric
    const gr_complex* in_h = (const gr_complex*)input_items[1]; // The weights
    gr_complex* out = (gr_complex*)output_items[0];

    for (int s = 0; s < noutput_items; s++) {
        for (int sc = 0; sc < d_num_sc; sc++) {
            float aepm = aep_metric[d_num_sc * s + sc];
            if (aepm >= d_thresh && aepm > prev_metric[sc]) {
                // copy the weight vector into the saved weight vectors
                cf_mat h(&in_h[s * d_M * d_num_sc + d_M * sc], d_M, 1);
                cf_mat H(h * h.t());
                cf_mat U(d_M, d_M);
                r_vec D(d_M);
                eig_sym(D, U, H);
                memcpy(
                    &weight_vectors[sc][0], U.colptr(d_M - 1), sizeof(gr_complex) * d_M);
            }

            prev_metric[sc] = aepm;

            // Copy the weight vector to the output
            // Note: why not do the beamforming here:
            //    Because the incoming samples are at a different rate
            //    due to the downsampling of the spectral covariance

            memcpy(&out[s * d_M * d_num_sc + d_M * sc],
                   &weight_vectors[sc][0],
                   sizeof(gr_complex) * d_M);
        }

        d_sample_num++;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace aep */
} /* namespace gr */
