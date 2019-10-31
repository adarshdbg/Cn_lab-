#Creating a network namespace
sudo ip netns add neeru
#Creating a veth pair
sudo ip link add eth0 type veth peer name eth1
#Setting one end of the veth in the created namespace
sudo ip link set eth0 netns neeru
#Bringing the loopback interface up
sudo ip netns exec neeru ip link set lo up
#Bring up the interfaces within namespaces
sudo ip netns exec neeru ip link set eth0 up
#Assign an ip address to the interfaces within the namespace
sudo ip netns exec neeru ip address add 10.0.0.1/24 dev eth0
#Pinging the interface in the created namespace from the default namespace
sudo ping -c 5 10.0.0.3
#Deleting the namespace
sudo ip netns delete neeru
#Deleting the link 
sudo ip link delete eth1
