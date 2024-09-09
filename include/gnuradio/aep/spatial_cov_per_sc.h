/* -*- c++ -*- */
/*
 * Copyright 2018-2024 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_AEP_SPATIAL_COV_PER_SC_H
#define INCLUDED_AEP_SPATIAL_COV_PER_SC_H

#include <gnuradio/aep/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
namespace aep {

/*!
 * \brief <+description of block+>
 * \ingroup aep
 *
 */
class AEP_API spatial_cov_per_sc : virtual public gr::sync_decimator
{
public:
    typedef std::shared_ptr<spatial_cov_per_sc> sptr;

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
