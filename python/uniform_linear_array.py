#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 Perspecta Labs.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
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
        
        # static gr_complex j(0,1);
        # float theta = d_angle_degrees * M_PI / 180.0;
        # d_scale_lin = pow(10.0, d_scale_db/20.0);
        
        # d_multiplier.resize(d_num_elements);
        # for (int m = 0; m < d_num_elements; m++)
        # {
        #     d_multiplier[m] = d_scale_lin * exp(((float)(-2.0*M_PI*m*d_sep_lambda*sin(theta)))*j);
        # }

        # )
        # for mm in range(self.num_elements):
        #     out[] = in[s]*d_multiplier[m];



        m = 0
        for m in range(self.num_elements):

            out[:,m] = in0*np.exp(((-2.0*pi*float(m)*self.sep_lambda*sin(self.theta)))*1.0j)
            


        return len(output_items[0])

