# Linux Traffic Control

## Reading Material:

### What is traffic Policing?

        In the same way, Traffic Policing is about performing an action (typically transmit/pass) to packets that conform to a specified rate and performing another action (typically drop) to packets that violate that rate.


### What is traffic Shaping?

        While traffic policing is about dropping or reclassifying packets, traffic shaping tries to make traffic conform to a certain rate by delaying the packets in a buffer and sending them out as “space” becomes available.

### Difference Between Them:

            Refer:
            https://www.routerfreak.com/traffic-policing-vs-traffic-shaping/


### What is a qdisc in Linux?

        Qdisc is algorithm which tell how to queue packets in linux traffic control 
        algorithm like traffic shapping.


### What is a Token Bucket Filter (TBF)?

        Refer Cisco implementaion of traffic policing and shaping To know the use 
        of Token Bucket Filter in the implementaion of above algorithms.
        https://www.routerfreak.com/traffic-policing-vs-traffic-shaping/

