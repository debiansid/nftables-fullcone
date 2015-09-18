/*
 * Copyright (c) 2015 Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include <libmnl/libmnl.h>
#include <linux/rtnetlink.h>

#include <nftables.h>
#include <list.h>
#include <netlink.h>
#include <iface.h>

static LIST_HEAD(iface_list);
static bool iface_cache_init;

static int data_attr_cb(const struct nlattr *attr, void *data)
{
	const struct nlattr **tb = data;
	int type = mnl_attr_get_type(attr);

	if (mnl_attr_type_valid(attr, IFLA_MAX) < 0)
		return MNL_CB_OK;

	switch(type) {
	case IFLA_IFNAME:
		if (mnl_attr_validate(attr, MNL_TYPE_STRING) < 0)
			netlink_abi_error();
		break;
	default:
		return MNL_CB_OK;
	}
	tb[type] = attr;
	return MNL_CB_OK;
}

static int data_cb(const struct nlmsghdr *nlh, void *data)
{
	struct nlattr *tb[IFLA_MAX + 1] = {};
	struct ifinfomsg *ifm = mnl_nlmsg_get_payload(nlh);
	struct iface *iface;

	iface = xmalloc(sizeof(struct iface));
	iface->ifindex = ifm->ifi_index;
	mnl_attr_parse(nlh, sizeof(*ifm), data_attr_cb, tb);
	strncpy(iface->name, mnl_attr_get_str(tb[IFLA_IFNAME]), IFNAMSIZ);
	list_add(&iface->list, &iface_list);

	return MNL_CB_OK;
}

void iface_cache_update(void)
{
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct mnl_socket *nl;
	struct nlmsghdr *nlh;
	struct rtgenmsg *rt;
	uint32_t seq, portid;
	int ret;

	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type	= RTM_GETLINK;
	nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
	nlh->nlmsg_seq = seq = time(NULL);
	rt = mnl_nlmsg_put_extra_header(nlh, sizeof(struct rtgenmsg));
	rt->rtgen_family = AF_PACKET;

	nl = mnl_socket_open(NETLINK_ROUTE);
	if (nl == NULL)
		netlink_init_error();

	if (mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0)
		netlink_init_error();

	portid = mnl_socket_get_portid(nl);

	if (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0)
		netlink_init_error();

	ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	while (ret > 0) {
		ret = mnl_cb_run(buf, ret, seq, portid, data_cb, NULL);
		if (ret <= MNL_CB_STOP)
			break;
		ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	}
	if (ret == -1)
		netlink_init_error();

	mnl_socket_close(nl);

	iface_cache_init = true;
}

void iface_cache_release(void)
{
	struct iface *iface, *next;

	if (!iface_cache_init)
		return;

	list_for_each_entry_safe(iface, next, &iface_list, list) {
		list_del(&iface->list);
		free(iface);
	}
	iface_cache_init = false;
}

unsigned int nft_if_nametoindex(const char *name)
{
	struct iface *iface;

	if (!iface_cache_init)
		iface_cache_update();

	list_for_each_entry(iface, &iface_list, list) {
		if (strncmp(name, iface->name, IFNAMSIZ) == 0)
			return iface->ifindex;
	}
	return 0;
}

char *nft_if_indextoname(unsigned int ifindex, char *name)
{
	struct iface *iface;

	if (!iface_cache_init)
		iface_cache_update();

	list_for_each_entry(iface, &iface_list, list) {
		if (iface->ifindex == ifindex) {
			strncpy(name, iface->name, IFNAMSIZ);
			return name;
		}
	}
	return NULL;
}
