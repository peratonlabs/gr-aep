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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "aep_metric_impl.h"

namespace gr {
  namespace aep {

    aep_metric::sptr
    aep_metric::make(int M, int num_sc, int nmem, float thresh)
    {
      return gnuradio::get_initial_sptr
        (new aep_metric_impl(M, num_sc, nmem, thresh));
    }

    /*
     * The private constructor
     */
    aep_metric_impl::aep_metric_impl(int M, int num_sc, int nmem, float thresh)
      : gr::sync_block("aep_metric",
              gr::io_signature::make(1, 1, M*M*num_sc*sizeof(gr_complex)),
              gr::io_signature::make2(2, 2, num_sc*sizeof(float), num_sc*M*sizeof(gr_complex)))
    {
      d_nmem = nmem;
      d_num_sc = num_sc;
      d_M = M;
      d_thresh = thresh;
     

      set_history(nmem);

      R_old.set_size(M,M);
      R_new.set_size(M,M);

      item_size = M*M*num_sc;
    }

    /*
     * Our virtual destructor.
     */
    aep_metric_impl::~aep_metric_impl()
    {
    }

    int
    aep_metric_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];
      gr_complex *out_h = (gr_complex *) output_items[1];

      for (int s=0; s<noutput_items; s++)
      {
        int a = (s + history() - 1);
        for (int sc = 0; sc < d_num_sc; sc++)
        {
          //memcpy(R_old.memptr(), &in[s * item_size + (d_M * d_M * sc)], sizeof(gr_complex)*d_M*d_M);
          //memcpy(R_new.memptr(), &in[a * item_size + (d_M * d_M * sc)], sizeof(gr_complex)*d_M*d_M);

          // cf_mat R_old( (gr_complex *) &in[s * item_size + (d_M * d_M * sc)], d_M, d_M, false, true);
          // cf_mat R_new( (gr_complex *) &in[a * item_size + (d_M * d_M * sc)], d_M, d_M, false, true);
          
          for (int i = 0; i < d_M; i++)
          // for (int j = 0; j < d_M; j++)
          {
            for (int j = 0; j < d_M; j++)
            // for (int i = 0; i < d_M; i++)
            {

              R_old.at(j,i) = in[s * item_size + (d_M * d_M * sc) + i * d_M + j];
              
              R_new.at(j,i) = in[a * item_size + (d_M * d_M * sc) + i * d_M + j];
            }
          }
          

          cf_mat U(d_M,d_M);
          cf_vec D(d_M);
          //cf_mat R_solve = solve(R_new,R_old);
          // cf_mat R_solve = solve(conj(R_old.t()),conj(R_new.t()));
          cf_mat R_solve = solve(R_old,R_new);
          
          // eig_gen(D,U,R_solve);

          // float dd = abs(accu(D));

          // if (dd > 10.0)
          //   float x = dd;

          float dd = abs(trace(R_solve));

          if (dd > d_thresh)
          {
            eig_gen(D,U,R_solve);
            printf("sc %d, %f\n",sc, dd);
          }
          
          out[s*d_num_sc+sc] = dd; // eigenvalues already sorted into max at [0]
          memcpy(&out_h[s*d_num_sc*d_M + d_M*sc], U.colptr(0), sizeof(gr_complex)*d_M);
        }


      }
      // Do <+signal processing+>
      



      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace aep */
} /* namespace gr */

