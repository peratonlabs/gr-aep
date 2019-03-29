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
#include "spatial_cov_per_sc_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace aep {

    spatial_cov_per_sc::sptr
    spatial_cov_per_sc::make(int M, int fft_size, int num_avg)
    {
      return gnuradio::get_initial_sptr
        (new spatial_cov_per_sc_impl(M, fft_size, num_avg));
    }

    /*
     * The private constructor
     */
    spatial_cov_per_sc_impl::spatial_cov_per_sc_impl(int M, int fft_size, int num_avg)
      : gr::sync_decimator("spatial_cov_per_sc",
              gr::io_signature::make(1, 1, M*fft_size*sizeof(gr_complex)),
              gr::io_signature::make(1, 1, M*M*fft_size*sizeof(gr_complex)), num_avg)
    {
      d_num_avg = num_avg;
      d_M = M;
      d_fft_size = fft_size;

      d_sample_buf.resize(d_M);
      for(int m=0; m<d_M; m++)
        d_sample_buf[m].resize(d_fft_size*d_num_avg);

      size_t align = volk_get_alignment();
      buf_a = (gr_complex*)volk_malloc(d_num_avg*sizeof(gr_complex), align);
      buf_b = (gr_complex*)volk_malloc(d_num_avg*sizeof(gr_complex), align);

      Xs.set_size(d_M, d_num_avg);
      R.set_size(d_M,d_M);
    }

    /*
     * Our virtual destructor.
     */
    spatial_cov_per_sc_impl::~spatial_cov_per_sc_impl()
    {
      volk_free(buf_a);
      volk_free(buf_b);
    }

    void spatial_cov_per_sc_impl::calc_spatial_covariance(gr_complex *out)
    {
      gr_complex dp;

      //vector < gr_complex > _buf_a(d_num_avg), _buf_b(d_num_avg);

      // Work from sample_buf
      for (int sc = 0; sc < d_fft_size; sc++)
      {
          // printf("Xs[%d]=[",sc);
          for (int i=0; i<d_M; i++)
          {
              for (int j=0; j<d_M; j++)
              {
                for (int k = 0; k < d_num_avg; k++)
                {
                  buf_a[k] = d_sample_buf[i][k*d_fft_size+sc];
                  buf_b[k] = d_sample_buf[j][k*d_fft_size+sc];
                  
                }

                volk_32fc_x2_conjugate_dot_prod_32fc(&dp, &buf_a[0], &buf_b[0], d_num_avg);
                // printf("%e+%ej,",real(dp),imag(dp));

                out[sc*d_M*d_M+i*d_M+j] = dp;

                // void volk_32fc_x2_dot_prod_32fc(lv_32fc_t* result, const lv_32fc_t* input, const lv_32fc_t* taps, unsigned int num_points)
                // volk_32fc_x2_dot_prod_32fc(lv_32fc_t* result, const lv_32fc_t* input, const lv_32fc_t* taps, unsigned int num_points)

              }
          }
          // printf("];\n");
      }

    }

    int
    spatial_cov_per_sc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0]; 
      gr_complex *out = (gr_complex *) output_items[0];
      gr_complex dp;
      // Every navg samples, we want a spatial covariance matrix (MxM) for each subcarrier

      for (int i = 0; i < noutput_items; i++)
      {     
        for (int sc=0; sc<d_fft_size; sc++)
        {
          for (int k=0; k<d_num_avg; k++)
          {
            memcpy(Xs.colptr(k),&in[i*d_M*d_fft_size*d_num_avg+d_M*d_fft_size*k + d_M*sc],sizeof(gr_complex)*d_M);
          }
 
          // R = conj(Xs*Xs.t());
          R = (Xs*Xs.t());
          
          // R = Xs.t()*Xs;

          // for (int m=0; m<d_M; m++)      
          // {
          //   memcpy(&out[i*d_M*d_M*d_fft_size+sc*d_M*d_M + m*d_M], R.colptr(m), sizeof(gr_complex)*d_M);

          // }

          memcpy(&out[i*d_M*d_M*d_fft_size+sc*d_M*d_M], R.memptr(), sizeof(gr_complex)*d_M*d_M);
          
        }
      

                // void volk_32fc_x2_dot_prod_32fc(lv_32fc_t* result, const lv_32fc_t* input, const lv_32fc_t* taps, unsigned int num_points)
                // volk_32fc_x2_dot_prod_32fc(lv_32fc_t* result, const lv_32fc_t* input, const lv_32fc_t* taps, unsigned int num_points)

      }
    


      




      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace aep */
} /* namespace gr */

