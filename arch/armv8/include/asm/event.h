// © 2021 Qualcomm Innovation Center, Inc. All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause

#define asm_event_wait(p) __asm__ volatile("wfe" ::"m"(*p))
