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

echo open new terminal and execute week7_1.2_netem.sh wait time 30 seconds
# now ping

sudo ip netns exec red ping -c 10 10.0.0.2

# now changing the delay
sudo ip netns exec red tc qdisc add dev eth0 root netem delay 100ms 10ms 25%
# now ping

sudo ip netns exec red ping -c 10 10.0.0.2

echo =============================================original bandwidth====================================
# check the original-bandwidth
sudo ip netns exec red iperf -c 10.0.0.2

echo ===============================================now limiting the bandwidth==============================

sudo  ip netns exec red tc qdisc del dev eth0 root
sudo  ip netns exec red tc qdisc add dev eth0 root tbf rate 256kbit burst 1600 limit 3000




# install iperf
sudo apt-get install iperf

echo open new terminal and execute week7_1.2.sh wait time 30 seconds
echo =============================================Do not Exit the ongoing script====================================================

sleep 30s



echo ==================================================New bandwidth====================================================

#now check the new bandwidth

sudo ip netns exec red iperf -c 10.0.0.2





