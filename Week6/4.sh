trap "set +x; sleep 1; set -x" DEBUG
#Creating two network namespaces
sudo ip netns add neeru
sudo ip netns add neeru1
#Creating veth pairs
sudo ip link add eth0 type veth peer name eth1
sudo ip link add eth2 type veth peer name eth3
#Setting the ends of the veth in the created namespaces
sudo ip link set eth0 netns neeru
sudo ip link set eth2 netns neeru1
#Bring up the interfaces within namespaces
sudo ip netns exec neeru ip link set eth0 up
sudo ip netns exec neeru1 ip link set eth2 up
#Assign ip addresses to the interfaces within the namespace
sudo ip netns exec neeru ip address add 10.0.0.1/24 dev eth0
sudo ip netns exec neeru1 ip address add 10.0.2.1/24 dev eth2
#Create bridge using iproute package.
sudo ip link add name br0 type bridge
sudo ip link set dev br0 up
#Set the other lose interfaces into the bridge
sudo ip link set eth1 master br0
sudo ip link set eth3 master br0
#Setting the bridge interfaces up
sudo ip link set dev eth1 up
sudo ip link set dev eth3 up
#Bringing the loopback interface up
sudo ip netns exec neeru ip link set lo up
sudo ip netns exec neeru1 ip link set lo up
#Pinging the interface in neeru from neeru1
sudo ip netns exec neeru1 ping 10.0.0.1
#Deleting the namespaces
sudo ip netns delete neeru
sudo ip netns delete neeru1
