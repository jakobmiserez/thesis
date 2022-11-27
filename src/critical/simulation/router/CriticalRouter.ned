package critical.simulation.router;

import inet.node.ipv6.Router6;
import inet.node.base.NetworkLayerNodeBase;
import critical.*;

module CriticalRouter extends Router6
{
    parameters:
        int numQueues = default(9);
        hasUdp = true;
        hasOspf = false;
        hasRip = false;
        hasBgp = false;
        hasPim = false;
        hasDhcp = false;
        numWlanInterfaces = 0;
        
        numApps = 1;
        app[0].typename = "FlowServerApp";
        
        eth[*].mac.queue.typename = "EtherQosQueue";
        eth[*].mac.queue.dataQueue.typename = "PriorityQueue";
        eth[*].mac.queue.dataQueue.numQueues = numQueues;
        eth[*].mac.queue.dataQueue.classifier.typename = "QosClassifier";
        
        ppp[*].ppp.queue.typename = "PriorityQueue";
        ppp[*].ppp.queue.numQueues = numQueues;
        ppp[*].ppp.queue.classifier.typename = "QosClassifier";
        @display("i=block/routing,gold;bgb=1395.45,760.725");
        
    submodules: 
        protocol: CriticalProtocol {
            @display("p=1125,226");
        }
        
    connections:
        protocol.ipOut --> tn.in++;
        protocol.ipIn <-- tn.out++;
}
