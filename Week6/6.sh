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
#Create bridge using iproute package. Brctl is deprecated
sudo ip link add name br0 type bridge
sudo ip link set dev br0 up
#Set the other lose interfaces into the bridge
sudo ip link set eth1 master br0
sudo ip link set eth3 master br0
sudo ip link set eth5 master br0
#Bring bridge interfaces up
sudo ip link set dev eth1 up
sudo ip link set dev eth3 up
sudo ip link set dev eth5 up
#Now ping, it works
sudo ip netns exec red ping 10.0.0.3
sudo ip netns exec red ping 10.0.0.5
sudo ip netns exec green ping 10.0.0.5
#Deleting the network namespaces
sudo ip netns delete red
sudo ip netns delete blue
sudo ip netns delete green
#Deleting the bridge
sudo ip link delete br0 type bridge
