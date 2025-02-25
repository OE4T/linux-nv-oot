/******************************************************************************
 *
 * Copyright(c) 2019 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 ******************************************************************************/

#include "tcpip_checksum_offload.h"

u8 chk_dmac_with_llc[MAX_MACID_NUM_WITH_LLC];

#if MAC_AX_FW_REG_OFLD
u32 mac_tcpip_chksum_ofd(struct mac_ax_adapter *adapter,
			 u8 en_tx_chksum_ofd, u8 en_rx_chksum_ofd)
{
	u32 ret = 0;
	struct h2c_info h2c_info = {0};
	struct mac_ax_en_tcpipchksum *content;

	h2c_info.agg_en = 0;
	h2c_info.content_len = sizeof(struct mac_ax_en_tcpipchksum);
	h2c_info.h2c_cat = FWCMD_H2C_CAT_MAC;
	h2c_info.h2c_class = FWCMD_H2C_CL_FW_OFLD;
	h2c_info.h2c_func = FWCMD_H2C_FUNC_TCPIP_CHKSUM_OFFLOAD_REG;
	h2c_info.rec_ack = 0;
	h2c_info.done_ack = 0;

	content = (struct mac_ax_en_tcpipchksum *)PLTFM_MALLOC(h2c_info.content_len);
	if (!content)
		return MACBUFALLOC;

	content->en_tx_chksum_ofd = en_tx_chksum_ofd;
	content->en_rx_chksum_ofd = en_rx_chksum_ofd;

	ret = mac_h2c_common(adapter, &h2c_info, (u32 *)content);

	PLTFM_FREE(content, h2c_info.content_len);

	return ret;
}
#else
u32 mac_tcpip_chksum_ofd(struct mac_ax_adapter *adapter,
			 u8 en_tx_chksum_ofd, u8 en_rx_chksum_ofd)
{
	u32 val;
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);

	if (en_tx_chksum_ofd) {
		val = MAC_REG_R32(R_AX_TX_TCPIP_CHECKSUM_FUNCTION);
		val |= B_AX_HDT_TCPIP_CHKSUM_EN;
		MAC_REG_W32(R_AX_TX_TCPIP_CHECKSUM_FUNCTION, val);
	} else {
		val = MAC_REG_R32(R_AX_TX_TCPIP_CHECKSUM_FUNCTION);
		val &= (~B_AX_HDT_TCPIP_CHKSUM_EN);
		MAC_REG_W32(R_AX_TX_TCPIP_CHECKSUM_FUNCTION, val);
	}

	if (en_rx_chksum_ofd) {
		val = MAC_REG_R32(R_AX_RX_TCPIP_CHECKSUM_FUNCTION);
		val |= B_AX_HDR_TCPIP_CHKSUM_EN;
		MAC_REG_W32((R_AX_RX_TCPIP_CHECKSUM_FUNCTION), val);
	} else {
		val = MAC_REG_R32((R_AX_RX_TCPIP_CHECKSUM_FUNCTION));
		val &= (~B_AX_HDR_TCPIP_CHKSUM_EN);
		MAC_REG_W32((R_AX_RX_TCPIP_CHECKSUM_FUNCTION), val);
	}

	return MACSUCCESS;
}
#endif
u32 mac_chk_rx_tcpip_chksum_ofd(struct mac_ax_adapter *adapter,
				u8 chksum_status)
{
	u8 chk_val = (chksum_status & 0xF0);

	if (!(chk_val & MAC_AX_CHKOFD_TCP_CHKSUM_VLD))
		return MAC_AX_CHKSUM_OFD_HW_NO_SUPPORT;

	if (chk_val & MAC_AX_CHKOFD_TCP_CHKSUM_ERR)
		return MAC_AX_CHKSUM_OFD_CHKSUM_ERR;

	if (!(chk_val & MAC_AX_CHKOFD_RX_IS_TCP_UDP) &&
	    !(chk_val & MAC_AX_CHKOFD_RX_IPV))
		return MAC_AX_CHKSUM_OFD_IPV4_TCP_OK;

	if (!(chk_val & MAC_AX_CHKOFD_RX_IS_TCP_UDP) &&
	    (chk_val & MAC_AX_CHKOFD_RX_IPV))
		return MAC_AX_CHKSUM_OFD_IPV6_TCP_OK;

	if ((chk_val & MAC_AX_CHKOFD_RX_IS_TCP_UDP) &&
	    !(chk_val & MAC_AX_CHKOFD_RX_IPV))
		return MAC_AX_CHKSUM_OFD_IPV4_UDP_OK;

	return MAC_AX_CHKSUM_OFD_IPV6_UDP_OK;
}

u32 mac_read_with_llc(struct mac_ax_adapter *adapter,
		      u16 macid, u8 *with_llc_en)
{
	if (macid >= adapter->hw_info->macid_num)
		return MACMACIDFL;
	*with_llc_en = chk_dmac_with_llc[macid];

	return MACSUCCESS;
}

u32 mac_write_with_llc(struct mac_ax_adapter *adapter,
		       u16 macid, u8 with_llc_en)
{
	if (macid >= adapter->hw_info->macid_num)
		return MACMACIDFL;
	chk_dmac_with_llc[macid] = with_llc_en;

	return MACSUCCESS;
}

