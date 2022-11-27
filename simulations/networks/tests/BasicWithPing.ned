package protocol.simulations.networks.tests;

import critical.simulation.router.*;
import inet.node.ethernet.Eth10*M;
import inet.networklayer.configurator.ipv6.Ipv6FlatNetworkConfigurator;
import inet.node.ipv6.StandardHost6;
import inet.common.scenario.ScenarioManager;

network BasicWithPing
{
    submodules:
        source: StandardHost6 {
            hasIpv4 = false;
            hasIpv6 = true;
            @display("p=50, 200");
        }
        dest: StandardHost6 {
            hasIpv4 = false;
            hasIpv6 = true;
            @display("p=450, 200");
        }
        router1: CriticalRouter {
            @display("p=150, 200");
        }

        router2: CriticalRouter {
            @display("p=250, 100");
        }

        router3: CriticalRouter {
            @display("p=350, 200");
        }

        router4: CriticalRouter {
            @display("p=250, 300");
        }

        router5: CriticalRouter {
            @display("p=250, 200");
        }

        configurator: Ipv6FlatNetworkConfigurator {
            @display("p=757.8,76.30625");
        }

        scenarioManager: ScenarioManager {
            @display("p=757,161");
        }

    connections:
        router1.ethg++ <--> Eth100M <--> router2.ethg++;
        router2.ethg++ <--> Eth100M <--> router3.ethg++;
        router3.ethg++ <--> Eth100M <--> router4.ethg++;
        router4.ethg++ <--> Eth100M <--> router1.ethg++;

        router5.ethg++ <--> Eth100M <--> router1.ethg++;
        router5.ethg++ <--> Eth100M <--> router2.ethg++;
        router5.ethg++ <--> Eth100M <--> router3.ethg++;
        router5.ethg++ <--> Eth100M <--> router4.ethg++;

        source.ethg++ <--> Eth100M <--> router1.ethg++;
        dest.ethg++ <--> Eth100M <--> router3.ethg++;

}
