/* -*- c++ -*- */
/*
 * Copyright (c) 2018-2019 Perspecta Labs Inc.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "apply_weights_impl.h"
#include <gnuradio/io_signature.h>

#include <volk/volk.h>

namespace gr {
namespace aep {

apply_weights::sptr apply_weights::make(int M, int num_sc, int num_avg) {
  return gnuradio::get_initial_sptr(new apply_weights_impl(M, num_sc, num_avg));
}

/*
 * The private constructor
 */
apply_weights_impl::apply_weights_impl(int M, int num_sc, int num_avg)
    : gr::block("apply_weights",
                gr::io_signature::make2(2, M + 1,
                                        num_sc * M * sizeof(gr_complex),
                                        num_sc * sizeof(gr_complex)),
                gr::io_signature::make(1, 1, num_sc * sizeof(gr_complex))) {
  d_M = M;
  d_num_sc = num_sc;
  d_num_avg = num_avg;

  set_min_noutput_items(num_avg);
  set_output_multiple(num_avg);

  size_t align = volk_get_alignment();
  d_sample = (gr_complex *)volk_malloc(d_M * sizeof(gr_complex), align);
}

/*
 * Our virtual destructor.
 */
apply_weights_impl::~apply_weights_impl() { volk_free(d_sample); }

void apply_weights_impl::forecast(int noutput_items,
                                  gr_vector_int &ninput_items_required) {

  ninput_items_required[0] = noutput_items / d_num_avg;

  for (int i = 1; i <= d_M; i++) {
    ninput_items_required[i] = noutput_items;
  }
}

int apply_weights_impl::general_work(int noutput_items,
                                     gr_vector_int &ninput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star &output_items) {
  const gr_complex *weights = (const gr_complex *)input_items[0];
  gr_complex *out = (gr_complex *)output_items[0];

  const gr_complex *in[d_M];
  for (int m = 0; m < d_M; m++) {
    in[m] = (const gr_complex *)input_items[m + 1];
  }

  for (int s = 0; s < noutput_items / d_num_avg; s++) {
    for (int a = 0; a < d_num_avg; a++) {
      for (int sc = 0; sc < d_num_sc; sc++) {
        // load up the sample across the elements
        for (int m = 0; m < d_M; m++) {
          d_sample[m] = in[m][s * d_num_sc * d_num_avg + a * d_num_sc + sc];
        }
        volk_32fc_x2_conjugate_dot_prod_32fc(
            &out[s * d_num_avg * d_num_sc + d_num_sc * a + sc], &d_sample[0],
            &weights[s * d_num_sc * d_M + d_M * sc], d_M);
      }
    }
  }

  consume(0, noutput_items / d_num_avg);
  for (int m = 0; m < d_M; m++) {
    consume(m + 1, noutput_items);
  }

  return noutput_items;
}

} /* namespace aep */
} /* namespace gr */
