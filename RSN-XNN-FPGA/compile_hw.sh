#!/bin/bash
# Copyright (C) 2025 Chengyue Wang
# SPDX-License-Identifier: AGPL-3.0-only


make kernels xsa package TARGET=hw EN_TRACE=1 PL_FREQ=$TARGET_FREQ
