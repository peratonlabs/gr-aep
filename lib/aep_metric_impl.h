/* -*- c++ -*- */
/* 
 * Copyright 2019 Perspecta Labs.
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

#ifndef INCLUDED_AEP_AEP_METRIC_IMPL_H
#define INCLUDED_AEP_AEP_METRIC_IMPL_H

#include <aep/aep_metric.h>
#include <armadillo>
using namespace std;
using namespace arma;
namespace gr {
  namespace aep {


    typedef Mat < complex < float > > cf_mat;
    typedef Col < complex < float > > cf_vec;
    typedef Mat < float > r_mat;
    typedef Col < float > r_vec;


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

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_AEP_METRIC_IMPL_H */

