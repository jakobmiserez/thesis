package protocol.simulations.networks.evaluation;

import critical.simulation.router.*;
import inet.networklayer.configurator.ipv6.Ipv6FlatNetworkConfigurator;
import inet.node.ipv6.StandardHost6;
import critical.simulation.scheduler.*;
import inet.common.scenario.ScenarioManager;

network NSFNET
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
        r1: CriticalAreaRouter {
            @display("p=82,122");
        }
        r2: CriticalAreaRouter {
            @display("p=26,243");
        }
        r3: CriticalAreaRouter {
            @display("p=82,372");
        }
        r4: CriticalAreaRouter {
            @display("p=165,217");
        }
        r5: CriticalAreaRouter {
            @display("p=289,271");
        }
        r6: CriticalAreaRouter {
            @display("p=354,420");
        }
        r7: CriticalAreaRouter {
            @display("p=384,217");
        }
        r8: CriticalAreaRouter {
            @display("p=474,178");
        }
        r9: CriticalAreaRouter {
            @display("p=572,178");
        }
        r10: CriticalAreaRouter {
            @display("p=548,420");
        }
        r11: CriticalAreaRouter {
            @display("p=493,83");
        }
        r12: CriticalAreaRouter {
            @display("p=653,101");
        }
        r13: CriticalAreaRouter {
            @display("p=679,297");
        }
        r14: CriticalAreaRouter {
            @display("p=747,190");
        }

        configurator: Ipv6FlatNetworkConfigurator {
            @display("p=786,38");
        }

        scheduler: Scheduler {

            @display("p=786,110");
        }
    connections:
        r1.pppg++ <--> fiberline {  distance = 1100km; } <--> r2.pppg++;
        r1.pppg++ <--> fiberline {  distance = 1600km; } <--> r3.pppg++;
        r1.pppg++ <--> fiberline {  distance = 2800km; } <--> r8.pppg++;
        r2.pppg++ <--> fiberline {  distance = 600   km; } <--> r3.pppg++;
        r2.pppg++ <--> fiberline {  distance = 1000km; } <--> r4.pppg++;
        r3.pppg++ <--> fiberline {  distance = 2000km; } <--> r6.pppg++;
        r4.pppg++ <--> fiberline {  distance = 600  km; } <--> r5.pppg++;
        r4.pppg++ <--> fiberline {  distance = 2400km; } <--> r11.pppg++;
        r5.pppg++ <--> fiberline {  distance = 1100km; } <--> r6.pppg++;
        r5.pppg++ <--> fiberline {  distance = 800  km; } <--> r7.pppg++;
        r6.pppg++ <--> fiberline {  distance = 1200km; } <--> r10.pppg++;
        r6.pppg++ <--> fiberline {  distance = 2000km; } <--> r13.pppg++;
        r7.pppg++ <--> fiberline {  distance = 700  km; } <--> r8.pppg++;
        r8.pppg++ <--> fiberline {  distance = 700  km; } <--> r9.pppg++;
        r9.pppg++ <--> fiberline {  distance = 900  km; } <--> r10.pppg++;
        r9.pppg++ <--> fiberline {  distance = 500  km; } <--> r12.pppg++;
        r9.pppg++ <--> fiberline {  distance = 500  km; } <--> r14.pppg++;
        r11.pppg++ <--> fiberline {  distance = 800  km; } <--> r12.pppg++;
        r11.pppg++ <--> fiberline {  distance = 800  km; } <--> r14.pppg++;
        r12.pppg++ <--> fiberline {  distance = 300  km; } <--> r13.pppg++;
        r13.pppg++ <--> fiberline {  distance = 300  km; } <--> r14.pppg++;
}

