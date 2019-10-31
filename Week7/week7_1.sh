#if toplology already exists
sudo ip netns del red
sudo ip netns del green

# create two namespaces 

sudo ip netns add red
sudo ip netns add green


# create veth pairs

sudo ip link add eth0 type veth peer name eth1

# Set the veth interfaces inside the namespaces


sudo ip link set eth0 netns red
sudo ip link set eth1 netns green

# Bring loopback interfaces up


sudo ip netns exec red ip link set lo up
sudo ip netns exec green ip link set lo up

# Bring up the interfaces within namespaces

sudo ip netns exec red ip link set eth0 up
sudo ip netns exec green ip link set eth1 up

# assign ip address
sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
sudo ip netns exec green ip address add 10.0.0.2/24 dev eth1

# install iperf
sudo apt-get install iperf
echo open new terminal and execute week7_1.2.sh wait time 30 seconds
sleep 30s

# check the original-bandwidth
echo ==================================================original bandwidth====================================================
sudo ip netns exec red iperf -c 10.0.0.2
#now changing the bandwidth
echo ==================================================Changing bandwidth using TBF====================================================


sudo ip netns exec red tc qdisc add dev eth0 root tbf rate 1mbit burst 100kbit latency 4ms

#now check the new bandwidth
echo ==================================================Changed bandwidth====================================================


sudo ip netns exec red iperf -c 10.0.0.2





