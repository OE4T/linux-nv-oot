# SPDX-License-Identifier: GPL-2.0-only
# SPDX-FileCopyrightText: Copyright (c) 2022-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.

LINUX_VERSION := $(shell expr $(VERSION) \* 256 + $(PATCHLEVEL))
LINUX_VERSION_6_6 := $(shell expr 6 \* 256 + 6)

ifeq ($(findstring ack_src,$(NV_BUILD_KERNEL_OPTIONS)),)
ifeq ($(VERSION).$(PATCHLEVEL),5.15)
ifneq ($(NV_OOT_REALTEK_RTL8822CE_SKIP_BUILD),y)
obj-m += rtl8822ce/
endif
endif
ifneq ($(NV_OOT_REALTEK_RTL8852CE_SKIP_BUILD),y)
ifeq ($(shell test $(LINUX_VERSION) -lt $(LINUX_VERSION_6_6); echo $$?),0)
obj-m += rtl8852ce/
endif
endif
endif
