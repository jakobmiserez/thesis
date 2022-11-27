package critical.simulation.applications.server;

import inet.applications.contract.IApp;

//
// FlowServerApp is an UDP application that is run within a router. It handles flow 
// requests with QoS requirements.
//
simple FlowServerApp like IApp {
    parameters:
        @class(critical::FlowServerApp);
        
        string criticalProtocol = "^.protocol";
        int port = 4096;
        double startTime @unit(s) = 1s;
  
    gates:
        input socketIn @labels(UdpControlInfo/up);
        output socketOut @labels(UdpControlInfo/down);  
}
