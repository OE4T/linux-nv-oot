/* SPDX-License-Identifier: GPL-2.0 */
/*
 * This file is part of NVIDIA MODS kernel driver.
 *
 * Copyright (c) 2008-2023, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA MODS kernel driver is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * NVIDIA MODS kernel driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NVIDIA MODS kernel driver.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MODS_CONFIG_H_
#define _MODS_CONFIG_H_

#define MODS_KERNEL_VERSION LINUX_VERSION_CODE

#if KERNEL_VERSION(2, 6, 30) <= MODS_KERNEL_VERSION && \
	KERNEL_VERSION(4, 16, 0) > MODS_KERNEL_VERSION && \
	defined(CONFIG_X86)
#       define MODS_HAS_DMA_OPS 1
#endif

#if KERNEL_VERSION(2, 6, 30) > MODS_KERNEL_VERSION
#       define MODS_HASNT_PCI_RESCAN_BUS 1
#endif

#if KERNEL_VERSION(2, 6, 31) <= MODS_KERNEL_VERSION
#       define MODS_HAS_IORESOURCE_MEM_64 1
#endif

#if KERNEL_VERSION(2, 6, 33) <= MODS_KERNEL_VERSION
#       define MODS_HAS_NEW_ACPI_WALK 1
#else
#       define MODS_HASNT_NUMA_NO_NODE 1
#endif

#if KERNEL_VERSION(2, 6, 34) <= MODS_KERNEL_VERSION
#       define MODS_HAS_SET_COHERENT_MASK 1
#endif

#if KERNEL_VERSION(2, 6, 38) <= MODS_KERNEL_VERSION
#       if defined(CONFIG_X86)
#               define MODS_HAS_CONSOLE_LOCK 1
#       endif
#endif

#if KERNEL_VERSION(3, 4, 0) > MODS_KERNEL_VERSION
#       define MODS_HASNT_PCI_BUS_REMOVE_DEV 1
#endif

#if KERNEL_VERSION(3, 8, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_NEW_ACPI_HANDLE 1
#       define MODS_HAS_SRIOV 1
#endif

#if KERNEL_VERSION(3, 14, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_MSIX_RANGE 1
#else
#       define MODS_HASNT_PCI_LOCK_RESCAN_REMOVE 1
#endif

#if KERNEL_VERSION(3, 16, 0) <= MODS_KERNEL_VERSION && \
	defined(CONFIG_VT_HW_CONSOLE_BINDING)
#       define MODS_HAS_CONSOLE_BINDING 1
#endif

#if KERNEL_VERSION(3, 19, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_DEV_PROPS 1
#endif

#if defined(CONFIG_PPC64) && KERNEL_VERSION(4, 5, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_PNV_PCI_GET_NPU_DEV 1
#endif

#if KERNEL_VERSION(4, 12, 0) <= MODS_KERNEL_VERSION && \
	KERNEL_VERSION(4, 13, 0) > MODS_KERNEL_VERSION && \
	defined(CONFIG_X86)
#       define MODS_HAS_ASM_SET_MEMORY_HEADER 1
#endif

#if KERNEL_VERSION(4, 13, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_SET_MEMORY_HEADER 1
#endif

#if KERNEL_VERSION(4, 14, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_KERNEL_WRITE
#endif

#if KERNEL_VERSION(4, 16, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_POLL_T 1
#endif

#if defined(CONFIG_ACPI_NUMA) && KERNEL_VERSION(5, 1, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_PXM_TO_NODE 1
#endif

#if KERNEL_VERSION(5, 17, 0) <= MODS_KERNEL_VERSION
#       define MODS_HAS_ACPI_FETCH 1
#endif

#if defined(MODS_HAS_TEGRA) && KERNEL_VERSION(5, 1, 0) <= MODS_KERNEL_VERSION
#       define MODS_ENABLE_BPMP_MRQ_API 1
#endif

#if KERNEL_VERSION(6, 1, 0) > MODS_KERNEL_VERSION
#       define MODS_HAS_FB_SET_SUSPEND 1
#endif

#endif /* _MODS_CONFIG_H_  */