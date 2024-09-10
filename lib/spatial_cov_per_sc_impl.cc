/* -*- c++ -*- */
/*
 * Copyright 2024 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "spatial_cov_per_sc_impl.h"
#include <gnuradio/io_signature.h>
#include <volk/volk.h>

namespace gr {
namespace aep {

spatial_cov_per_sc::sptr spatial_cov_per_sc::make(int M, int fft_size, int num_avg)
{
    return gnuradio::get_initial_sptr(new spatial_cov_per_sc_impl(M, fft_size, num_avg));
}

/*
 * The private constructor
 */
spatial_cov_per_sc_impl::spatial_cov_per_sc_impl(int M, int fft_size, int num_avg)
    : gr::sync_decimator(
          "spatial_cov_per_sc",
          gr::io_signature::make(1, 1, M * fft_size * sizeof(gr_complex)),
          gr::io_signature::make(1, 1, M * M * fft_size * sizeof(gr_complex)),
          num_avg)
{
    d_num_avg = num_avg;
    d_M = M;
    d_fft_size = fft_size;

    d_sample_buf.resize(d_M);
    for (int m = 0; m < d_M; m++)
        d_sample_buf[m].resize(d_fft_size * d_num_avg);

    size_t align = volk_get_alignment();
    buf_a = (gr_complex*)volk_malloc(d_num_avg * sizeof(gr_complex), align);
    buf_b = (gr_complex*)volk_malloc(d_num_avg * sizeof(gr_complex), align);

    Xs.set_size(d_M, d_num_avg);
    R.set_size(d_M, d_M);
}

/*
 * Our virtual destructor.
 */
spatial_cov_per_sc_impl::~spatial_cov_per_sc_impl()
{
    volk_free(buf_a);
    volk_free(buf_b);
}

int spatial_cov_per_sc_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    const gr_complex* in = (const gr_complex*)input_items[0];
    gr_complex* out = (gr_complex*)output_items[0];
    gr_complex dp;
    // Every navg samples, we want a spatial covariance matrix (MxM) for each
    // subcarrier

    for (int i = 0; i < noutput_items; i++) {
        for (int sc = 0; sc < d_fft_size; sc++) {
            for (int k = 0; k < d_num_avg; k++) {
                memcpy(Xs.colptr(k),
                       &in[i * d_M * d_fft_size * d_num_avg + d_M * d_fft_size * k +
                           d_M * sc],
                       sizeof(gr_complex) * d_M);
            }

            R = (Xs * Xs.t());

            memcpy(&out[i * d_M * d_M * d_fft_size + sc * d_M * d_M],
                   R.memptr(),
                   sizeof(gr_complex) * d_M * d_M);
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace aep */
} /* namespace gr */
