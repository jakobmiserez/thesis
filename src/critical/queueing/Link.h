#ifndef _CRITICAL_LINK_H
#define _CRITICAL_LINK_H

#include "critical/queueing/dnc/PredictablePort.h"
#include "critical/flows/Flow.h"

#include <ostream>

namespace critical {

class Link {
  private:
    PredictablePort* port;
    int queue;

  public:
    Link(PredictablePort* port, int queue) : port(port), queue(queue) {};
    Link(const Link& link): port(link.port), queue(link.queue) {};
    
    virtual ~Link() {};

    int getInterfaceId() const {
      return port->getId();
    };

    int getQueue() const {
      return queue;
    }

    uint64_t getDelay() const {
      return port->getQueues()[queue].getDelayBudget() + port->getLinkDelay();
    };

    FlowParameters allocate(const FlowParameters& params) {
      return port->allocateFlow(queue, params);
    };

    void free(const FlowParameters& params) {
      port->freeFlow(queue, params);
    };

    friend std::ostream& operator<<(std::ostream& os, const critical::Link& link);

};

inline std::ostream& operator<<(std::ostream& os, const critical::Link& link) {
  os << "Link(" << link.port << ", " << link.queue << ")";
  return os;
};

}



#endif 