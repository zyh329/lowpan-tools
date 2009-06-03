/*
 * ieee802154_nl.h
 *
 * Copyright (C) 2007, 2008 Siemens AG
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef IEEE802154_NL_H
#define IEEE802154_NL_H

#define IEEE802154_NL_NAME "802.15.4 MAC"
#define IEEE802154_MCAST_COORD_NAME "coordinator"
#define IEEE802154_MCAST_BEACON_NAME "beacon"

enum {
	__IEEE802154_ATTR_INVALID,

	IEEE802154_ATTR_DEV_NAME,
	IEEE802154_ATTR_DEV_INDEX,

	IEEE802154_ATTR_STATUS,

	IEEE802154_ATTR_SHORT_ADDR,
	IEEE802154_ATTR_HW_ADDR,
	IEEE802154_ATTR_PAN_ID,

	IEEE802154_ATTR_CHANNEL,

	IEEE802154_ATTR_COORD_SHORT_ADDR,
	IEEE802154_ATTR_COORD_HW_ADDR,
	IEEE802154_ATTR_COORD_PAN_ID,

	IEEE802154_ATTR_SRC_SHORT_ADDR,
	IEEE802154_ATTR_SRC_HW_ADDR,
	IEEE802154_ATTR_SRC_PAN_ID,

	IEEE802154_ATTR_DEST_SHORT_ADDR,
	IEEE802154_ATTR_DEST_HW_ADDR,
	IEEE802154_ATTR_DEST_PAN_ID,

	IEEE802154_ATTR_CAPABILITY, /* FIXME: this is association */
	IEEE802154_ATTR_REASON,
	IEEE802154_ATTR_SCAN_TYPE,
	IEEE802154_ATTR_CHANNELS,
	IEEE802154_ATTR_DURATION,
	IEEE802154_ATTR_ED_LIST,
	IEEE802154_ATTR_BCN_ORD,
	IEEE802154_ATTR_SF_ORD,
	IEEE802154_ATTR_PAN_COORD,
	IEEE802154_ATTR_BAT_EXT,
	IEEE802154_ATTR_COORD_REALIGN,
	IEEE802154_ATTR_SEC,

	__IEEE802154_ATTR_MAX,
};

#define IEEE802154_ATTR_MAX (__IEEE802154_ATTR_MAX - 1)
#define NLA_HW_ADDR	NLA_U64
#define NLA_GET_HW_ADDR(attr, addr) do { u64 _temp = nla_get_u64(attr); memcpy(addr, &_temp, 8); } while (0)
#define NLA_PUT_HW_ADDR(msg, attr, addr) do { u64 _temp; memcpy(&_temp, addr, 8); NLA_PUT_U64(msg, attr, _temp); } while (0)

#ifdef IEEE802154_NL_WANT_POLICY
static struct nla_policy ieee802154_policy[IEEE802154_ATTR_MAX + 1] = {
	[IEEE802154_ATTR_DEV_NAME] = { .type = NLA_STRING, },
	[IEEE802154_ATTR_DEV_INDEX] = { .type = NLA_U32, },

	[IEEE802154_ATTR_STATUS] = { .type = NLA_U8, },
	[IEEE802154_ATTR_SHORT_ADDR] = { .type = NLA_U16, },
	[IEEE802154_ATTR_HW_ADDR] = { .type = NLA_HW_ADDR, },
	[IEEE802154_ATTR_PAN_ID] = { .type = NLA_U16, },
	[IEEE802154_ATTR_CHANNEL] = { .type = NLA_U8, },
	[IEEE802154_ATTR_COORD_SHORT_ADDR] = { .type = NLA_U16, },
	[IEEE802154_ATTR_COORD_HW_ADDR] = { .type = NLA_HW_ADDR, },
	[IEEE802154_ATTR_COORD_PAN_ID] = { .type = NLA_U16, },
	[IEEE802154_ATTR_SRC_SHORT_ADDR] = { .type = NLA_U16, },
	[IEEE802154_ATTR_SRC_HW_ADDR] = { .type = NLA_HW_ADDR, },
	[IEEE802154_ATTR_SRC_PAN_ID] = { .type = NLA_U16, },
	[IEEE802154_ATTR_DEST_SHORT_ADDR] = { .type = NLA_U16, },
	[IEEE802154_ATTR_DEST_HW_ADDR] = { .type = NLA_HW_ADDR, },
	[IEEE802154_ATTR_DEST_PAN_ID] = { .type = NLA_U16, },

	[IEEE802154_ATTR_CAPABILITY] = { .type = NLA_U8, },
	[IEEE802154_ATTR_REASON] = { .type = NLA_U8, },
	[IEEE802154_ATTR_SCAN_TYPE] = { .type = NLA_U8, },
	[IEEE802154_ATTR_CHANNELS] = { .type = NLA_U32, },
	[IEEE802154_ATTR_DURATION] = { .type = NLA_U8, },
#ifdef __KERNEL__
	[IEEE802154_ATTR_ED_LIST] = { .len = 27 },
#else
	[IEEE802154_ATTR_ED_LIST] = { .minlen = 27, .maxlen = 27 },
#endif
};
#endif

/* commands */
/* REQ should be responded with CONF
 * and INDIC with RESP
 */
enum {
	__IEEE802154_COMMAND_INVALID,

	IEEE802154_ASSOCIATE_REQ,
	IEEE802154_ASSOCIATE_CONF,
	IEEE802154_DISASSOCIATE_REQ,
	IEEE802154_DISASSOCIATE_CONF,
	IEEE802154_GET_REQ,
	IEEE802154_GET_CONF,
	IEEE802154_RESET_REQ,
	IEEE802154_RESET_CONF,
	IEEE802154_SCAN_REQ,
	IEEE802154_SCAN_CONF,
	IEEE802154_SET_REQ,
	IEEE802154_SET_CONF,
	IEEE802154_START_REQ,
	IEEE802154_START_CONF,
	IEEE802154_SYNC_REQ,
	IEEE802154_POLL_REQ,
	IEEE802154_POLL_CONF,

	IEEE802154_ASSOCIATE_INDIC,
	IEEE802154_ASSOCIATE_RESP,
	IEEE802154_DISASSOCIATE_INDIC,
	IEEE802154_BEACON_NOTIFY_INDIC,
	IEEE802154_ORPHAN_INDIC,
	IEEE802154_ORPHAN_RESP,
	IEEE802154_COMM_STATUS_INDIC,
	IEEE802154_SYNC_LOSS_INDIC,

	IEEE802154_GTS_REQ, /* Not supported yet */
	IEEE802154_GTS_INDIC, /* Not supported yet */
	IEEE802154_GTS_CONF, /* Not supported yet */
	IEEE802154_RX_ENABLE_REQ, /* Not supported yet */
	IEEE802154_RX_ENABLE_CONF, /* Not supported yet */

	__IEEE802154_CMD_MAX,
};

#define IEEE802154_CMD_MAX (__IEEE802154_CMD_MAX - 1)


#ifdef __KERNEL__
struct net_device;

int ieee802154_nl_assoc_indic(struct net_device *dev, struct ieee802154_addr *addr, u8 cap);
int ieee802154_nl_assoc_confirm(struct net_device *dev, u16 short_addr, u8 status);
int ieee802154_nl_disassoc_indic(struct net_device *dev, struct ieee802154_addr *addr, u8 reason);
int ieee802154_nl_disassoc_confirm(struct net_device *dev, u8 status);
int ieee802154_nl_scan_confirm(struct net_device *dev, u8 status, u8 scan_type, u32 unscanned,
		u8 *edl/*, struct list_head *pan_desc_list */);
int ieee802154_nl_beacon_indic(struct net_device *dev, u16 panid, u16 coord_addr); /* TODO */
#endif

#endif