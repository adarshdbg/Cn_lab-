#Create three namespaces
sudo ip netns add red
sudo ip netns add blue
sudo ip netns add green
#Create veth pairs
sudo ip link add eth0 type veth peer name eth1
sudo ip link add eth2 type veth peer name eth3
sudo ip link add eth4 type veth peer name eth5
#Set the veth interfaces inside the namespaces
sudo ip link set eth0 netns red
sudo ip link set eth2 netns green
sudo ip link set eth4 netns blue
#Bring loopback interfaces up
sudo ip netns exec red ip link set lo up
sudo ip netns exec green ip link set lo up
sudo ip netns exec blue ip link set lo up
#Bring up the interfaces within namespaces
sudo ip netns exec red ip link set eth0 up
sudo ip netns exec green ip link set eth2 up
sudo ip netns exec blue ip link set eth4 up
#Assign interfaces within namespaces IP addresses
sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
sudo ip netns exec green ip address add 10.0.0.3/24 dev eth2
sudo ip netns exec blue ip address add 10.0.0.5/24 dev eth4
#Create 3 bridges using iproute package.
sudo ip link add name br0 type bridge
sudo ip link set dev br0 up
sudo ip link add name br1 type bridge
sudo ip link set dev br1 up
sudo ip link add name br2 type bridge
sudo ip link set dev br2 up
#Set the other lose interfaces into the bridges
sudo ip link set eth1 master br0
sudo ip link set eth3 master br1
sudo ip link set eth5 master br2
#Bring bridge interfaces up
sudo ip link set dev eth1 up
sudo ip link set dev eth3 up
sudo ip link set dev eth5 up
#Create veth pairs for the bridges
sudo ip link add b0 type veth peer name b1
sudo ip link add b2 type veth peer name b3
sudo ip link add b4 type veth peer name b5
#Assign veth ends to the bridges
sudo ip link set b0 master br0
sudo ip link set b1 master br1
sudo ip link set b2 master br1
sudo ip link set b3 master br2
sudo ip link set b4 master br2
sudo ip link set b5 master br0
#Bringing the new veth pairs up
sudo ip link set b0 up
sudo ip link set b1 up
sudo ip link set b2 up
sudo ip link set b3 up
sudo ip link set b4 up
sudo ip link set b5 up
#Now ping, it won't work as there is a network loop
sudo ip netns exec red ping 10.0.0.3
sudo ip netns exec red ping 10.0.0.5
sudo ip netns exec green ping 10.0.0.5
#Deleting the network namespaces
sudo ip netns delete red
sudo ip netns delete blue
sudo ip netns delete green
#Deleting the bridges
sudo ip link delete br0 type bridge
sudo ip link delete br1 type bridge
sudo ip link delete br2 type bridge
