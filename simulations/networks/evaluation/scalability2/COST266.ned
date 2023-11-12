package protocol.simulations.networks.evaluation.scalability2;

import critical.simulation.router.*;
import inet.networklayer.configurator.ipv6.Ipv6FlatNetworkConfigurator;
import inet.node.ipv6.StandardHost6;
import critical.simulation.scheduler.*;
import inet.common.scenario.ScenarioManager;
import critical.simulation.lsaoptimizer.*;


network COST266s
{
    @display("bgb=1669.72,1345.24;bgi=maps/europe,s");
    types:
        channel fiberline extends ned.DatarateChannel
        {
            parameters:
                datarate = 1Gbps;
                double distance @unit(km);
                delay = this.distance / 200000km * 1s;
        }

    submodules:
        lsaOptimizer: LsaOptimizer {};
        Amsterdam: CriticalAreaRouter {
            @display("p=628.68,723.32;is=s");
        }
        Athens: CriticalAreaRouter {
            @display("p=1228.63,1204.97;is=s");
        }
        Barcelona: CriticalAreaRouter {
            @display("p=457.99,1115.4;is=s");
        }
        Belgrade: CriticalAreaRouter {
            @display("p=1093.4299,986.95996;is=s");
        }
        Berlin: CriticalAreaRouter {
            @display("p=863.58997,711.49;is=s");
        }
        Birmingham: CriticalAreaRouter {
            @display("p=419.12,645.57996;is=s");
        }
        Bordeaux: CriticalAreaRouter {
            @display("p=430.94998,986.95996;is=s");
        }
        Brussels: CriticalAreaRouter {
            @display("p=589.81,787.54;is=s");
        }
        Budapest: CriticalAreaRouter {
            @display("p=1027.52,900.76996;is=s");
        }
        Copenhagen: CriticalAreaRouter {
            @display("p=802.75,599.95;is=s");
        }
        Dublin: CriticalAreaRouter {
            @display("p=290.68,662.48;is=s");
        }
        Dusseldorf: CriticalAreaRouter {
            @display("p=667.55,762.19;is=s");
        }
        Frankfurt: CriticalAreaRouter {
            @display("p=763.88,787.54;is=s");
        }
        Glasgow: CriticalAreaRouter {
            @display("p=392.08,562.76996;is=s");
        }
        Hamburg: CriticalAreaRouter {
            @display("p=731.76996,701.35;is=s");
        }
        Helsinki: CriticalAreaRouter {
            @display("p=1066.39,398.84;is=s");
        }
        Krakow: CriticalAreaRouter {
            @display("p=1027.52,787.54;is=s");
        }
        Lisbon: CriticalAreaRouter {
            @display("p=101.399994,1169.48;is=s");
        }
        London: CriticalAreaRouter {
            @display("p=457.99,741.91;is=s");
        }
        Lyon: CriticalAreaRouter {
            @display("p=608.39996,961.61;is=s");
        }
        Madrid: CriticalAreaRouter {
            @display("p=300.82,1115.4;is=s");
        }
        Marseille: CriticalAreaRouter {
            @display("p=608.39996,1044.4199;is=s");
        }
        Milan: CriticalAreaRouter {
            @display("p=748.67,986.95996;is=s");
        }
        Munich: CriticalAreaRouter {
            @display("p=787.54,851.75995;is=s");
        }
        Oslo: CriticalAreaRouter {
            @display("p=763.88,437.71;is=s");
        }
        Palermo: CriticalAreaRouter {
            @display("p=902.45996,1257.36;is=s");
        }
        Paris: CriticalAreaRouter {
            @display("p=579.67,850.07;is=s");
        }
        Prague: CriticalAreaRouter {
            @display("p=902.45996,811.19995;is=s");
        }
        Rome: CriticalAreaRouter {
            @display("p=826.41,1091.74;is=s");
        }
        Seville: CriticalAreaRouter {
            @display("p=182.51999,1206.6599;is=s");
        }
        Sofia: CriticalAreaRouter {
            @display("p=1215.11,1063.01;is=s");
        }
        Stockholm: CriticalAreaRouter {
            @display("p=902.45996,457.99;is=s");
        }
        Strasbourg: CriticalAreaRouter {
            @display("p=667.55,870.35;is=s");
        }
        Vienna: CriticalAreaRouter {
            @display("p=914.29,880.49;is=s");
        }
        Warsaw: CriticalAreaRouter {
            @display("p=1027.52,684.45;is=s");
        }
        Zagreb: CriticalAreaRouter {
            @display("p=963.3,973.44;is=s");
        }
        Zurich: CriticalAreaRouter {
            @display("p=692.89996,934.56995;is=s");
        }

        configurator: Ipv6FlatNetworkConfigurator {
            @display("p=490.1,128.7");
        }

        scheduler: Scheduler {
            @display("p=668.2,128.7");
        }

        scenarioManager: ScenarioManager {
            @display("p=309.4,128.7");
        }


    connections:

        Amsterdam.pppg++ <--> fiberline {  distance = 174km; } <--> Brussels.pppg++;
        Amsterdam.pppg++ <--> fiberline {  distance = 710km; } <--> Glasgow.pppg++;
        Amsterdam.pppg++ <--> fiberline {  distance = 366km; } <--> Hamburg.pppg++;
        Amsterdam.pppg++ <--> fiberline {  distance = 360km; } <--> London.pppg++;
        Athens.pppg++ <--> fiberline {  distance = 909km; } <--> Palermo.pppg++;
        Athens.pppg++ <--> fiberline {  distance = 526km; } <--> Sofia.pppg++;
        Athens.pppg++ <--> fiberline {  distance = 1081km; } <--> Zagreb.pppg++;
        Barcelona.pppg++ <--> fiberline {  distance = 505km; } <--> Madrid.pppg++;
        Barcelona.pppg++ <--> fiberline {  distance = 339km; } <--> Marseille.pppg++;
        Barcelona.pppg++ <--> fiberline {  distance = 829km; } <--> Seville.pppg++;
        Belgrade.pppg++ <--> fiberline {  distance = 315km; } <--> Budapest.pppg++;
        Belgrade.pppg++ <--> fiberline {  distance = 334km; } <--> Sofia.pppg++;
        Belgrade.pppg++ <--> fiberline {  distance = 364km; } <--> Zagreb.pppg++;
        Berlin.pppg++ <--> fiberline {  distance = 355km; } <--> Copenhagen.pppg++;
        Berlin.pppg++ <--> fiberline {  distance = 256km; } <--> Hamburg.pppg++;
        Berlin.pppg++ <--> fiberline {  distance = 505km; } <--> Munich.pppg++;
        Berlin.pppg++ <--> fiberline {  distance = 290km; } <--> Prague.pppg++;
        Berlin.pppg++ <--> fiberline {  distance = 517km; } <--> Warsaw.pppg++;
        Birmingham.pppg++ <--> fiberline {  distance = 407km; } <--> Glasgow.pppg++;
        Birmingham.pppg++ <--> fiberline {  distance = 161km; } <--> London.pppg++;
        Bordeaux.pppg++ <--> fiberline {  distance = 555km; } <--> Madrid.pppg++;
        Bordeaux.pppg++ <--> fiberline {  distance = 506km; } <--> Marseille.pppg++;
        Bordeaux.pppg++ <--> fiberline {  distance = 499km; } <--> Paris.pppg++;
        Brussels.pppg++ <--> fiberline {  distance = 175km; } <--> Dusseldorf.pppg++;
        Brussels.pppg++ <--> fiberline {  distance = 264km; } <--> Paris.pppg++;
        Budapest.pppg++ <--> fiberline {  distance = 293km; } <--> Krakow.pppg++;
        Budapest.pppg++ <--> fiberline {  distance = 445km; } <--> Prague.pppg++;
        Copenhagen.pppg++ <--> fiberline {  distance = 484km; } <--> Oslo.pppg++;
        Copenhagen.pppg++ <--> fiberline {  distance = 523km; } <--> Stockholm.pppg++;
        Dublin.pppg++ <--> fiberline {  distance = 310km; } <--> Glasgow.pppg++;
        Dublin.pppg++ <--> fiberline {  distance = 460km; } <--> London.pppg++;
        Dusseldorf.pppg++ <--> fiberline {  distance = 181km; } <--> Frankfurt.pppg++;
        Frankfurt.pppg++ <--> fiberline {  distance = 392km; } <--> Hamburg.pppg++;
        Frankfurt.pppg++ <--> fiberline {  distance = 307km; } <--> Munich.pppg++;
        Frankfurt.pppg++ <--> fiberline {  distance = 185km; } <--> Strasbourg.pppg++;
        Helsinki.pppg++ <--> fiberline {  distance = 787km; } <--> Oslo.pppg++;
        Helsinki.pppg++ <--> fiberline {  distance = 396km; } <--> Stockholm.pppg++;
        Helsinki.pppg++ <--> fiberline {  distance = 916km; } <--> Warsaw.pppg++;
        Krakow.pppg++ <--> fiberline {  distance = 253km; } <--> Warsaw.pppg++;
        Lisbon.pppg++ <--> fiberline {  distance = 1584km; } <--> London.pppg++;
        Lisbon.pppg++ <--> fiberline {  distance = 503km; } <--> Madrid.pppg++;
        Lisbon.pppg++ <--> fiberline {  distance = 314km; } <--> Seville.pppg++;
        London.pppg++ <--> fiberline {  distance = 345km; } <--> Paris.pppg++;
        Lyon.pppg++ <--> fiberline {  distance = 278km; } <--> Marseille.pppg++;
        Lyon.pppg++ <--> fiberline {  distance = 392km; } <--> Paris.pppg++;
        Lyon.pppg++ <--> fiberline {  distance = 336km; } <--> Zurich.pppg++;
        Marseille.pppg++ <--> fiberline {  distance = 605km; } <--> Rome.pppg++;
        Milan.pppg++ <--> fiberline {  distance = 349km; } <--> Munich.pppg++;
        Milan.pppg++ <--> fiberline {  distance = 479km; } <--> Rome.pppg++;
        Milan.pppg++ <--> fiberline {  distance = 218km; } <--> Zurich.pppg++;
        Munich.pppg++ <--> fiberline {  distance = 356km; } <--> Vienna.pppg++;
        Palermo.pppg++ <--> fiberline {  distance = 424km; } <--> Rome.pppg++;
        Paris.pppg++ <--> fiberline {  distance = 398km; } <--> Strasbourg.pppg++;
        Prague.pppg++ <--> fiberline {  distance = 253km; } <--> Vienna.pppg++;
        Rome.pppg++ <--> fiberline {  distance = 517km; } <--> Zagreb.pppg++;
        Strasbourg.pppg++ <--> fiberline {  distance = 148km; } <--> Zurich.pppg++;
        Vienna.pppg++ <--> fiberline {  distance = 269km; } <--> Zagreb.pppg++;
}
