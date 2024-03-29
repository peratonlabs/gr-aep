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


#ifndef INCLUDED_AEP_AEP_METRIC_H
#define INCLUDED_AEP_AEP_METRIC_H

#include <aep/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace aep {

    /*!
     * \brief Calculates the AEP metric and associated beamforming vector when a threshold is exceeded
     * \ingroup aep
     *
     */
    class AEP_API aep_metric : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<aep_metric> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of aep::aep_metric.
       *
       * To avoid accidental use of raw pointers, aep::aep_metric's
       * constructor is in a private implementation
       * class. aep::aep_metric::make is the public interface for
       * creating new instances.
       */
      static sptr make(int M, int num_sc, int nmem, float thresh);
    };

  } // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_AEP_METRIC_H */

