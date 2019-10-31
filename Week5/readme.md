# Network Namespaces

## Reading Material

### What is container:
        A container is a standard unit of software that packages up code and all its dependencies so the application runs quickly and reliably from one computing environment to another.

        Put simply, a container consists of an entire runtime environment: an application, plus all its dependencies, libraries and other binaries, and configuration files needed to run it, bundled into one package. By containerizing the application platform and its dependencies, differences in OS distributions and underlying infrastructure are abstracted away.

### What is the difference between a container and a virtual machine?

        The container’s system requires an underlying operating system that provides the basic services to all of the containerized applications using virtual-memory support for isolation.
        Container systems have a lower overhead than VMs and container systems typically target environments where thousands of containers are in play.
### What are Linux namespaces?

        A namespace wraps a global system resource in an abstraction that
        makes it appear to the processes within the namespace that they have
        their own isolated instance of the global resource.  Changes to the
        global resource are visible to other processes that are members of
        the namespace, but are invisible to other processes.  One use of
        namespaces is to implement containers.

### What is the difference between a Linux namespace and a container?

        Yet to be done

### What is a network namespace in Linux?

        A network namespace is logically another copy of the network stack,
        with its own routes, firewall rules, and network devices.

## Hands On:

### Install, Setup and run an LXC container on your system

        sudo apt-get install lxc

### Manage named network namespaces using iproute2:

####  Create a network namespace.

        sudo ip netns add red

#### Run a network application inside the network namespace.

        Lets Run Ping:

       // create namespace 
        sudo ip netns add red

        
        // Bring loopback interfaces up 
        sudo ip netns exec red ip link set lo up

        
        //ping ip address 
        sudo ip netns exec red ping 127.0.0.1

#### Move the physical NIC interface inside the network namespace.

        // create namespace
        sudo ip netns add red

        
        // Create veth pairs
        sudo ip link add eth0 type veth peer name eth1

        
        // Set the (nic) veth interfaces inside the namespaces 
        sudo ip link set eth0 netns red


#### Destroy an existing network namespace after killing the processes running inside it.

        
        //After Killing Ping process with ctrl+C
        sudo ip netns delete red




