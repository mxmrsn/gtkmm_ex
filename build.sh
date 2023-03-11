#!/bin/bash
rm -rf build && mkdir build && cd build && cmake .. && make \
&& ./gtkmm_ex