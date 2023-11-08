#ifndef _CRITICAL_LINEARFLOWMAP_H
#define _CRITICAL_LINEARFLOWMAP_H

#include "critical/flows/map/IFlowMap.h"
#include "critical/common/util/NonCopyable.h"
#include "critical/common/util/Util.h"
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

template <class T>
class LinearFlowMap: public IFlowMap<T>, public NonCopyable {
  protected:
    std::vector<FlowMapEntry<T>*> entries;

  public:
    LinearFlowMap();
    virtual ~LinearFlowMap();

    virtual void clear() override;

    virtual FlowMapEntry<T>* insertFlow(const FlowId& flow, T data) override;

    virtual FlowMapEntry<T> deleteFlow(const FlowId& flow) override;

    virtual std::optional<FlowMapEntry<T>> deleteFlowIfPresent(const FlowId& flow) override;

    virtual FlowMapEntry<T>* lookupFlow(const FlowId& flow) override;

    virtual FlowMapEntry<T>* removeFlow(const FlowId& flow) override;

    virtual size_t size() const override;

    FlowMapEntry<T>* insertIfAbsent(const FlowId& flow, T data);

  private:
    int indexOf(const FlowId& flow) const;
};

typedef LinearFlowMap<Empty> LinearFlowSet;

}

#include "LinearFlowMap.tcc"

#endif