#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2024 Peraton Labs, Inc.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#


import numpy as np
from gnuradio import gr
from math import pi, sin

class uniform_linear_array(gr.sync_block):
    """
    docstring for block uniform_linear_array
    """
    def __init__(self, num_elements, sep_lambda, angle_degrees):
        gr.sync_block.__init__(self,
            name="uniform_linear_array",
            in_sig=[np.complex64],
            out_sig=[(np.complex64,num_elements)])

        self.sep_lambda = sep_lambda
        self.num_elements = num_elements
        self.angle_degrees = angle_degrees
        self.theta = self.angle_degrees * pi / 180.0


    def work(self, input_items, output_items):
        in0 = input_items[0]
        out = output_items[0]
        
        m = 0
        for m in range(self.num_elements):
            out[:,m] = in0*np.exp(((-2.0*pi*float(m)*self.sep_lambda*sin(self.theta)))*1.0j)

        return len(output_items[0])

