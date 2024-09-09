/* -*- c++ -*- */
/*
 * Copyright 2018-2024 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_AEP_APPLY_WEIGHTS_H
#define INCLUDED_AEP_APPLY_WEIGHTS_H

#include <gnuradio/aep/api.h>
#include <gnuradio/block.h>

namespace gr {
namespace aep {

/*!
 * \brief <+description of block+>
 * \ingroup aep
 *
 */
class AEP_API apply_weights : virtual public gr::block
{
public:
    typedef std::shared_ptr<apply_weights> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of aep::apply_weights.
     *
     * To avoid accidental use of raw pointers, aep::apply_weights's
     * constructor is in a private implementation
     * class. aep::apply_weights::make is the public interface for
     * creating new instances.
     */
    static sptr make(int M, int num_sc, int num_avg);
};

} // namespace aep
} // namespace gr

#endif /* INCLUDED_AEP_APPLY_WEIGHTS_H */
