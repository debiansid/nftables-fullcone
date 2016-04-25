#!/bin/sh

SERVICE=nftables.service

set -e

if systemctl -q is-active $SERVICE ; then
	echo "W: initial service running, stopping now" >&2
	systemctl stop $SERVICE
fi

if [ $(nft list ruleset | wc -l) -ne 0 ] ; then
	echo "W: initial ruleset is not empty, flushing now" >&2
	nft flush ruleset
fi

systemctl start $SERVICE
if [ $(nft list ruleset | wc -l) -eq 0 ] ; then
	echo "E: called 'systemctl start ${SERVICE}' but no ruleset loaded" >&2
	exit 1
fi

systemctl status $SERVICE
systemctl stop $SERVICE
if [ $(nft list ruleset | wc -l) -ne 0 ] ; then
	echo "E: called 'systemctl stop ${SERVICE}' but ruleset still loaded" >&2
	exit 1
fi

systemctl restart $SERVICE
if [ $(nft list ruleset | wc -l) -eq 0 ] ; then
	echo "E: called 'systemctl restart ${SERVICE}' but no ruleset loaded" >&2
	exit 1
fi

exit 0
