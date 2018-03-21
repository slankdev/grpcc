#!/bin/sh

ip netns add ns0
ip link add veth0 type veth peer name veth1
ip link set veth1 netns ns0

ip netns exec ns0 ip link set lo up
ip netns exec ns0 ip link set veth1 up
ip netns exec ns0 ethtool -K  veth1 rx off tx off
ip netns exec ns0 ip addr add 10.0.10.2/24 dev veth1

ip link set veth0 up
ip addr add 10.0.10.1/24 dev veth0

