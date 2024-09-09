/* -*- c++ -*- */
/*
 * Copyright 2018-2024 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_AEP_AEP_METRIC_H
#define INCLUDED_AEP_AEP_METRIC_H

#include <gnuradio/aep/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace aep {

/*!
 * \brief <+description of block+>
 * \ingroup aep
 *
 */
class AEP_API aep_metric : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<aep_metric> sptr;

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
