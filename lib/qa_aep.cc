/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file was generated by gr_modtool, a tool from the GNU Radio framework
 * This file is a part of gr-aep
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * This class gathers together all the test cases for the gr-filter
 * directory into a single test suite.  As you create new test cases,
 * add them here.
 */

#include "qa_aep.h"
#include "qa_apply_weights.h"
#include "qa_aep_metric.h"
#include "qa_aep_channel_processing.h"
#include "qa_spatial_cov_per_sc.h"

CppUnit::TestSuite *
qa_aep::suite()
{
  CppUnit::TestSuite *s = new CppUnit::TestSuite("aep");
  s->addTest(gr::aep::qa_apply_weights::suite());
  s->addTest(gr::aep::qa_aep_metric::suite());
  s->addTest(gr::aep::qa_aep_channel_processing::suite());
  s->addTest(gr::aep::qa_spatial_cov_per_sc::suite());

  return s;
}