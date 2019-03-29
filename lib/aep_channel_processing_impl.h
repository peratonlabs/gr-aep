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

#ifndef INCLUDED_AEP_AEP_CHANNEL_PROCESSING_IMPL_H
#define INCLUDED_AEP_AEP_CHANNEL_PROCESSING_IMPL_H

#include <aep/aep_channel_processing.h>

#include <armadillo>
#include <vector>
using namespace std;
using namespace arma;

#include "aep_metric_impl.h" // for now for the typedefs - move this out eventually

namespace gr {
namespace aep {

class aep_channel_processing_impl : public aep_channel_processing {
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
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_AEP_CHANNEL_PROCESSING_IMPL_H */
