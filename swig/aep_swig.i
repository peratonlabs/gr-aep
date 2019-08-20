/* -*- c++ -*- */

#define AEP_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "aep_swig_doc.i"

%{
#include "aep/apply_weights.h"
#include "aep/aep_metric.h"
#include "aep/spatial_cov_per_sc.h"
#include "aep/aep_channel_processing.h"
%}

%include "aep/apply_weights.h"
GR_SWIG_BLOCK_MAGIC2(aep, apply_weights);

%include "aep/aep_metric.h"
GR_SWIG_BLOCK_MAGIC2(aep, aep_metric);
%include "aep/spatial_cov_per_sc.h"
GR_SWIG_BLOCK_MAGIC2(aep, spatial_cov_per_sc);
%include "aep/aep_channel_processing.h"
GR_SWIG_BLOCK_MAGIC2(aep, aep_channel_processing);
