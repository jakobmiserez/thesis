package protocol.simulations.networks.tests;


package protocol.simulations.networks.tests;

import critical.simulation.router.*;
import inet.node.ethernet.Eth10*M;
import inet.networklayer.configurator.ipv6.Ipv6FlatNetworkConfigurator;
import inet.node.ipv6.StandardHost6;
import inet.common.scenario.ScenarioManager;
import critical.simulation.scheduler.*;

network Line
{
    types:
        channel fiberline extends ned.DatarateChannel
        {
            parameters:
                datarate = 1Gbps;
        }
    submodules:
        router1: CriticalAreaRouter {
            @display("p=70,176");
        }

        router2: CriticalRouter {
            @display("p=157,176");
        }

        router3: CriticalRouter {
            @display("p=257,176");
        }

        router4: CriticalRouter {
            @display("p=350,176");
        }

        router5: CriticalAreaRouter {
            @display("p=471,176");
        }

        extra: CriticalRouter {
            @display("p=257,265");
        }

        configurator: Ipv6FlatNetworkConfigurator {
            @display("p=551,69");
        }


        scheduler: Scheduler {

            @display("p=543,251");
        }
    connections:
        router1.pppg++ <--> fiberline { delay = 1ms; } <--> router2.pppg++;
        router2.pppg++ <--> fiberline { delay = 1ms; } <--> router3.pppg++;
        router3.pppg++ <--> fiberline { delay = 1ms; } <--> router4.pppg++;
        router4.pppg++ <--> fiberline { delay = 1ms; } <--> router5.pppg++;

        router2.pppg++ <--> fiberline {delay = 2ms; } <--> extra.pppg++;
        extra.pppg++ <--> fiberline { delay = 2ms; } <--> router4.pppg++;
}

