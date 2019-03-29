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

#ifndef INCLUDED_AEP_SPATIAL_COV_PER_SC_IMPL_H
#define INCLUDED_AEP_SPATIAL_COV_PER_SC_IMPL_H

#include <aep/spatial_cov_per_sc.h>

#include <vector>

using namespace std;
#include <armadillo>
using namespace arma;

#include "aep_metric_impl.h"
namespace gr {
namespace aep {

class spatial_cov_per_sc_impl : public spatial_cov_per_sc {
private:
  int d_num_avg;
  int d_fft_size;
  int d_M;

  vector<vector<gr_complex>> d_sample_buf; // for each of the M streams
  int d_sample_buf_index;

  gr_complex *buf_a;
  gr_complex *buf_b;

  cf_mat Xs;
  cf_mat R;

  void calc_spatial_covariance(gr_complex *out);

public:
  spatial_cov_per_sc_impl(int M, int fft_size, int num_avg);
  ~spatial_cov_per_sc_impl();

  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_SPATIAL_COV_PER_SC_IMPL_H */
