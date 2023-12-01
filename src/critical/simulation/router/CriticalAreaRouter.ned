package critical.simulation.router;

import inet.node.ipv6.StandardHost6;
import inet.node.base.NetworkLayerNodeBase;
import critical.*;

module CriticalAreaRouter
{
    parameters:
        @display("i=block/routing,blue;bgb=1395.45,760.725");

    gates:
        inout pppg[];

    submodules:
        area: CriticalApplicationHost {
            hasTcp = false;
            @display("i=misc/cloud,blue;p=368.98627,419.7;is=vl");
        }

        router: CriticalRouter {
            ppp[0].ppp.queue.queue[*].dataCapacity = -1b;
            ppp[*].ppp.queue.queue[*].dataCapacity = -1b; //97000*8b;
            @display("p=368.98627,587.58");
        }

    connections:
        area.pppg++ <--> ned.DatarateChannel { datarate=100000Gbps; delay=0s; } <--> router.pppg++;
        for i=0..sizeof(pppg)-1 {
            router.pppg++ <--> ned.IdealChannel <--> pppg[i];
        }
}
