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


#ifndef INCLUDED_AEP_SPATIAL_COV_PER_SC_H
#define INCLUDED_AEP_SPATIAL_COV_PER_SC_H

#include <aep/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace aep {

    /*!
     * \brief Spatial Covariance per subcarrier calculation 
     * \ingroup aep
     *
     */
    class AEP_API spatial_cov_per_sc : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<spatial_cov_per_sc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of aep::spatial_cov_per_sc.
       *
       * To avoid accidental use of raw pointers, aep::spatial_cov_per_sc's
       * constructor is in a private implementation
       * class. aep::spatial_cov_per_sc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int M, int fft_size, int num_avg);
    };

  } // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_SPATIAL_COV_PER_SC_H */

