package protocol.simulations.networks.evaluation;

import critical.simulation.router.*;
import inet.networklayer.configurator.ipv6.Ipv6FlatNetworkConfigurator;
import inet.node.ipv6.StandardHost6;
import critical.simulation.scheduler.*;
import inet.common.scenario.ScenarioManager;

network Grid3
{
    types:
        channel fiberline extends ned.DatarateChannel
        {
            parameters:
                datarate = 1Gbps;
                double distance @unit(km);
                delay = this.distance / 200000km * 1s;
        }

    submodules:
        scenarioManager: ScenarioManager {};
        r0: CriticalAreaRouter {
            @display("p=82,122");
        }
        r1: CriticalAreaRouter {
            @display("p=26,243");
        }
        r2: CriticalAreaRouter {
            @display("p=82,372");
        }
        r3: CriticalAreaRouter {
            @display("p=165,217");
        }
        r4: CriticalAreaRouter {
            @display("p=289,271");
        }
        r5: CriticalAreaRouter {
            @display("p=354,420");
        }
        r6: CriticalAreaRouter {
            @display("p=384,217");
        }
        r7: CriticalAreaRouter {
            @display("p=474,178");
        }
        r8: CriticalAreaRouter {
            @display("p=572,178");
        }

        configurator: Ipv6FlatNetworkConfigurator {
            @display("p=786,38");
        }

        scheduler: Scheduler {

            @display("p=786,110");
        }
    connections:
        // First row
        r0.pppg++ <--> fiberline {  distance = 600km; } <--> r1.pppg++;
        r0.pppg++ <--> fiberline {  distance = 600km; } <--> r3.pppg++;

        r1.pppg++ <--> fiberline {  distance = 600km; } <--> r2.pppg++;
        r1.pppg++ <--> fiberline {  distance = 600km; } <--> r4.pppg++;

        r2.pppg++ <--> fiberline {  distance = 600km; } <--> r5.pppg++;

        // Second row

        r3.pppg++ <--> fiberline {  distance = 600km; } <--> r4.pppg++;
        r3.pppg++ <--> fiberline {  distance = 600km; } <--> r6.pppg++;

        r4.pppg++ <--> fiberline {  distance = 600km; } <--> r5.pppg++;
        r4.pppg++ <--> fiberline {  distance = 600km; } <--> r7.pppg++;

        r5.pppg++ <--> fiberline {  distance = 600km; } <--> r8.pppg++;

        // Third row

        r6.pppg++ <--> fiberline {  distance = 600km; } <--> r7.pppg++;
        r7.pppg++ <--> fiberline {  distance = 600km; } <--> r8.pppg++;

}

