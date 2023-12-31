# coding: utf-8
#
# © 2021 Qualcomm Innovation Center, Inc. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

"""
Gunyah general build system.

This module is invoked by configure.py with the global variable `graph` set to
an instance of AbstractBuildGraph, which can be used to add rules, targets and
variables to the build graph.
"""

import os
import sys
import logging
import inspect

from . import config_file as cfg


#
# Global variable & default settings
#
# Silence flake8 warnings about the externally-defined graph variable
graph = graph  # noqa: F821

logging.basicConfig()
logger = logging.getLogger(__name__)

build_dir = graph.build_dir
config_file_name = "build.conf"

#
# Build rules
#


#
# General setup
#
def relpath(path):
    return os.path.relpath(path, start=graph.root_dir)


# parse configure file
# we should compile from repo top header
config = cfg.Configuration(config_file_name, graph)
config.process()

#
# Python dependencies
#
for m in sys.modules.values():
    try:
        f = inspect.getsourcefile(m)
    except TypeError:
        continue
    if f is None:
        continue
    f = os.path.relpath(f)
    if f.startswith('../'):
        continue
    graph.add_gen_source(f)
