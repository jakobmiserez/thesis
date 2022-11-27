#ifndef _CRITICAL_IFAILUREHANDLER_H
#define _CRITICAL_IFAILUREHANDLER_H

namespace critical {

class IFailureHandler {
  public:
    virtual ~IFailureHandler() {};

    virtual void handleLinkFailure(int interfaceId) = 0;
};

}


#endif 