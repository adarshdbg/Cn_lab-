# Virtual Networks

# Reading Material 

## What is the difference between a hub, a switch and a router?

### Hub:
A hub works on the physical layer (Layer 1) of OSI model.
A hub is the least expensive, least intelligent, and least complicated of the three. Its job is very simple: anything that comes in one port is sent out to the others. 

### Switch:
Switch works on the data link layer (Layer 2)
Switches learn the location of the devices they are connected to almost instantaneously. The result is, most network traffic only goes where it needs to, rather than to every port. On busy networks, this can make the network significantly faster.

## Routers:
Router is working on a higher level of network layer (Layer 3)
A router operates as a switch for basic routing: it learns the location of the computers sending traffic, and routes information only to the necessary connections.
Consumer-grade routers perform (at minimum) two additional and important tasks: DHCP and NAT.
DHCP — Dynamic Host Configuration Protocol — is how dynamic IP addresses are assigned
NAT — Network Address Translation- – is the way the router translates the IP addresses of packets that cross the internet/local network boundary.

## What is a Linux bridge?
Linux bridge is a layer 2 virtual device that on its own cannot receive or transmit anything unless you bind one or more real devices to it

##  What is Open vSwitch?
A virtual switch (vSwitch) is a software application that allows communication between virtual machines. A vSwitch does more than just forward data packets, it intelligently directs the communication on a network by checking data packets before moving them to a destination.
Open vSwitch is a production quality, multilayer virtual switch

##  What is a veth interface?
The veth devices are virtual Ethernet devices.  They can act as
tunnels between network namespaces to create a bridge to a physical
network device in another namespace

## What is a route?
In general, a route refers to the path a data packet travels on a network

## What is a routing table?
A routing table contains the information necessary to forward a packet along the best path toward its destination. Each packet contains information about its origin and destination. When a packet is received, a network device examines the packet and matches it to the routing table entry providing the best match for its destination. The table then provides the device with instructions for sending the packet to the next hop on its route across the network.



# Hands On

## Ping a network namespace from the default namespace.
        
        // create namespace 
        sudo ip netns add red

        
        // Bring loopback interfaces up 
        sudo ip netns exec red ip link set lo up

        
        //ping ip address 
        sudo ip netns exec red ping 127.0.0.1

## Ping a network namespace from another network namespace.
        
        // create namespace
        sudo ip netns add red
        sudo ip netns add blue

        
        // Create veth pairs
        sudo ip link add eth0 type veth peer name eth1

        
        // Set the veth interfaces inside the namespaces 
        sudo ip link set eth0 netns red
        sudo ip link set eth1 netns blue

        
        // Bring loopback interfaces up 
        sudo ip netns exec red ip link set lo up
        sudo ip netns exec blue ip link set lo up

        
        // Bring up the interfaces within namespaces
        sudo ip netns exec red ip link set eth0 up
        sudo ip netns exec blue ip link set eth1 up

        
        // Assign interfaces within namespaces IP addresses
        sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
        sudo ip netns exec blue ip address add 10.0.0.3/24 dev eth1

        
        // Now ping, it works
        sudo ip netns exec red ping 10.0.0.3
        sudo ip netns exec blue ping 10.0.0.1

## ● Access the Internet from inside a network namespace (without moving any physical NIC
## interface inside it) by using:
## ○ A Linux bridge
## ○ Open vSwitch


        
        // yet to be done

## Ping a network namespace from another network namespace via a Linux bridge.

        
        // create namespace
        sudo ip netns add red
        sudo ip netns add blue

        
        // Create veth pairs
        sudo ip link add eth0 type veth peer name eth1
        sudo ip link add eth2 type veth peer name eth3

        
        // Set the veth interfaces inside the namespaces
        sudo ip link set eth0 netns red
        sudo ip link set eth2 netns blue

        
        // Bring loopback interfaces up
        sudo ip netns exec red ip link set lo up
        sudo ip netns exec blue ip link set lo up

        
        // Bring up the interfaces within namespaces
        sudo ip netns exec red ip link set eth0 up
        sudo ip netns exec blue ip link set eth2 up

        
        // Assign interfaces within namespaces IP addresses
        sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
        sudo ip netns exec blue ip address add 10.0.0.3/24 dev eth2

        
        // Create bridge using iproute package. Brctl is deprecated
        sudo ip link add name br0 type bridge
        sudo ip link set dev br0 up

        
        // Set the other lose interfaces into the bridge
        sudo ip link set eth1 master br0
        sudo ip link set eth3 master br0

        
        //Bring bridge interfaces up
        sudo ip link set dev eth1 up
        sudo ip link set dev eth3 up

        
        // Now ping, it works
        sudo ip netns exec red ping 10.0.0.3
        sudo ip netns exec blue ping 10.0.0.1

## Ping a network namespace from another network namespace via a third network namespace.

        
        // Create two namespaces
        sudo ip netns add red
        sudo ip netns add green

        
        // Create three veth pairs
        sudo ip link add eth0 type veth peer name eth1
        sudo ip link add eth2 type veth peer name eth3

        
        // Set them into the namespaces
        sudo ip link set eth0 netns red
        sudo ip link set eth2 netns green

        
        // Bring them up
        sudo ip netns exec red ip link set eth0 up
        sudo ip netns exec green ip link set eth2 up

        
        // Assign IP address to them (all different subnets)
        sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
        sudo ip netns exec green ip address add 10.0.2.1/24 dev eth2

        
        // Create router namespace and add appropriate interfaces into it
        sudo ip netns add router
        sudo ip link set eth1 netns router
        sudo ip link set eth3 netns router

        
        // Bring the interface up
        sudo ip netns exec router ip link set eth1 up
        sudo ip netns exec router ip link set eth3 up

        
        // Assign IP addresses to the interfaces within router
        sudo ip netns exec router ip address add 10.0.0.2/24 dev eth1
        sudo ip netns exec router ip address add 10.0.2.2/24 dev eth3

        
        // Bring loopback interfaces up
        sudo ip netns exec router ip link set lo up
        sudo ip netns exec red ip link set lo up
        sudo ip netns exec green ip link set lo up

        
        //Try ping, won’t work as there is no way to know where to send packets
        sudo ip netns exec red ping 10.0.2.1

        
        // Add default gateway, i.e. it serves as a forwarding host to connect to other networks
        sudo ip netns exec red ip route add default via 10.0.0.2 dev eth0
        sudo ip netns exec green ip route add default via 10.0.2.2 dev eth2

        
        //Enable IP forwarding : Make a system to act as a router i.e., it should determine the path a packet has to take to reach it’s destination 
        sudo ip netns exec router sysctl -w net.ipv4.ip_forward=1

        
        // Try ping now, it works
        sudo ip netns exec red ping 10.0.2.1








