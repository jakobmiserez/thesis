#ifndef _CRITICAL_PROTOCOLCOMPONENT_H
#define _CRITICAL_PROTOCOLCOMPONENT_H

namespace critical {

class CriticalProtocol;

class ProtocolComponent {
  protected:
    CriticalProtocol* protocol;

  public:
    ProtocolComponent(CriticalProtocol* protocol) : protocol(protocol) {};
    virtual ~ProtocolComponent() {};
    
    /**
     * @brief Construct a new protocol component that is a child of this component, sharing the 
     * same protocol instance
     * 
     * @tparam T 
     * @tparam Args 
     * @param args 
     * @return T 
     */
    template <class T, class... Args>
    T constructComponent(Args&&... args) {
      return T(std::forward<Args>(args)..., protocol);
    };

};

}


#endif 