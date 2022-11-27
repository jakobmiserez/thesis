//
// Generated file, do not edit! Created by nedtool 5.6 from critical/protocols/probing/packets/ProbingPackets.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "ProbingPackets_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace critical {
namespace probing {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(ProbingPacketBase)

ProbingPacketBase::ProbingPacketBase() : ::critical::CriticalPacketBase()
{
    this->setChunkLength(inet::B(37));

}

ProbingPacketBase::ProbingPacketBase(const ProbingPacketBase& other) : ::critical::CriticalPacketBase(other)
{
    copy(other);
}

ProbingPacketBase::~ProbingPacketBase()
{
}

ProbingPacketBase& ProbingPacketBase::operator=(const ProbingPacketBase& other)
{
    if (this == &other) return *this;
    ::critical::CriticalPacketBase::operator=(other);
    copy(other);
    return *this;
}

void ProbingPacketBase::copy(const ProbingPacketBase& other)
{
    this->flow = other.flow;
}

void ProbingPacketBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::CriticalPacketBase::parsimPack(b);
    doParsimPacking(b,this->flow);
}

void ProbingPacketBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::CriticalPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->flow);
}

const critical::FlowId& ProbingPacketBase::getFlow() const
{
    return this->flow;
}

void ProbingPacketBase::setFlow(const critical::FlowId& flow)
{
    handleChange();
    this->flow = flow;
}

class ProbingPacketBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_flow,
    };
  public:
    ProbingPacketBaseDescriptor();
    virtual ~ProbingPacketBaseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ProbingPacketBaseDescriptor)

ProbingPacketBaseDescriptor::ProbingPacketBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::probing::ProbingPacketBase)), "critical::CriticalPacketBase")
{
    propertynames = nullptr;
}

ProbingPacketBaseDescriptor::~ProbingPacketBaseDescriptor()
{
    delete[] propertynames;
}

bool ProbingPacketBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ProbingPacketBase *>(obj)!=nullptr;
}

const char **ProbingPacketBaseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ProbingPacketBaseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ProbingPacketBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int ProbingPacketBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_flow
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *ProbingPacketBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flow",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int ProbingPacketBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'f' && strcmp(fieldName, "flow") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ProbingPacketBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "critical::FlowId",    // FIELD_flow
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **ProbingPacketBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ProbingPacketBaseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ProbingPacketBaseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ProbingPacketBase *pp = (ProbingPacketBase *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ProbingPacketBaseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ProbingPacketBase *pp = (ProbingPacketBase *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ProbingPacketBaseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ProbingPacketBase *pp = (ProbingPacketBase *)object; (void)pp;
    switch (field) {
        case FIELD_flow: {std::stringstream out; out << pp->getFlow(); return out.str();}
        default: return "";
    }
}

bool ProbingPacketBaseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ProbingPacketBase *pp = (ProbingPacketBase *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ProbingPacketBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_flow: return omnetpp::opp_typename(typeid(critical::FlowId));
        default: return nullptr;
    };
}

void *ProbingPacketBaseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ProbingPacketBase *pp = (ProbingPacketBase *)object; (void)pp;
    switch (field) {
        case FIELD_flow: return toVoidPtr(&pp->getFlow()); break;
        default: return nullptr;
    }
}

Register_Class(FlowPrunePacket)

FlowPrunePacket::FlowPrunePacket() : ::critical::probing::ProbingPacketBase()
{
    this->setType(PROBE_PRUNE);
    this->setChunkLength(inet::B(38));
}

FlowPrunePacket::FlowPrunePacket(const FlowPrunePacket& other) : ::critical::probing::ProbingPacketBase(other)
{
    copy(other);
}

FlowPrunePacket::~FlowPrunePacket()
{
}

FlowPrunePacket& FlowPrunePacket::operator=(const FlowPrunePacket& other)
{
    if (this == &other) return *this;
    ::critical::probing::ProbingPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowPrunePacket::copy(const FlowPrunePacket& other)
{
}

void FlowPrunePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::probing::ProbingPacketBase::parsimPack(b);
}

void FlowPrunePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::probing::ProbingPacketBase::parsimUnpack(b);
}

class FlowPrunePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    FlowPrunePacketDescriptor();
    virtual ~FlowPrunePacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FlowPrunePacketDescriptor)

FlowPrunePacketDescriptor::FlowPrunePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::probing::FlowPrunePacket)), "critical::probing::ProbingPacketBase")
{
    propertynames = nullptr;
}

FlowPrunePacketDescriptor::~FlowPrunePacketDescriptor()
{
    delete[] propertynames;
}

bool FlowPrunePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowPrunePacket *>(obj)!=nullptr;
}

const char **FlowPrunePacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowPrunePacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowPrunePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int FlowPrunePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *FlowPrunePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int FlowPrunePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowPrunePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **FlowPrunePacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlowPrunePacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlowPrunePacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowPrunePacket *pp = (FlowPrunePacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowPrunePacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowPrunePacket *pp = (FlowPrunePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowPrunePacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowPrunePacket *pp = (FlowPrunePacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool FlowPrunePacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowPrunePacket *pp = (FlowPrunePacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *FlowPrunePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *FlowPrunePacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowPrunePacket *pp = (FlowPrunePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

FlowProbeStats::FlowProbeStats()
{
    this->accumulatedDelay = 0;
    this->hops = 0;
    this->totalHopEstimate = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const FlowProbeStats& a)
{
    doParsimPacking(b,a.accumulatedDelay);
    doParsimPacking(b,a.hops);
    doParsimPacking(b,a.totalHopEstimate);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FlowProbeStats& a)
{
    doParsimUnpacking(b,a.accumulatedDelay);
    doParsimUnpacking(b,a.hops);
    doParsimUnpacking(b,a.totalHopEstimate);
}

class FlowProbeStatsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_accumulatedDelay,
        FIELD_hops,
        FIELD_totalHopEstimate,
    };
  public:
    FlowProbeStatsDescriptor();
    virtual ~FlowProbeStatsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FlowProbeStatsDescriptor)

FlowProbeStatsDescriptor::FlowProbeStatsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::probing::FlowProbeStats)), "")
{
    propertynames = nullptr;
}

FlowProbeStatsDescriptor::~FlowProbeStatsDescriptor()
{
    delete[] propertynames;
}

bool FlowProbeStatsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowProbeStats *>(obj)!=nullptr;
}

const char **FlowProbeStatsDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowProbeStatsDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowProbeStatsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int FlowProbeStatsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_accumulatedDelay
        FD_ISEDITABLE,    // FIELD_hops
        FD_ISEDITABLE,    // FIELD_totalHopEstimate
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *FlowProbeStatsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "accumulatedDelay",
        "hops",
        "totalHopEstimate",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int FlowProbeStatsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'a' && strcmp(fieldName, "accumulatedDelay") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hops") == 0) return base+1;
    if (fieldName[0] == 't' && strcmp(fieldName, "totalHopEstimate") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowProbeStatsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_accumulatedDelay
        "uint32_t",    // FIELD_hops
        "uint32_t",    // FIELD_totalHopEstimate
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowProbeStatsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlowProbeStatsDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlowProbeStatsDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowProbeStats *pp = (FlowProbeStats *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowProbeStatsDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowProbeStats *pp = (FlowProbeStats *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowProbeStatsDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowProbeStats *pp = (FlowProbeStats *)object; (void)pp;
    switch (field) {
        case FIELD_accumulatedDelay: return uint642string(pp->accumulatedDelay);
        case FIELD_hops: return ulong2string(pp->hops);
        case FIELD_totalHopEstimate: return ulong2string(pp->totalHopEstimate);
        default: return "";
    }
}

bool FlowProbeStatsDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowProbeStats *pp = (FlowProbeStats *)object; (void)pp;
    switch (field) {
        case FIELD_accumulatedDelay: pp->accumulatedDelay = string2uint64(value); return true;
        case FIELD_hops: pp->hops = string2ulong(value); return true;
        case FIELD_totalHopEstimate: pp->totalHopEstimate = string2ulong(value); return true;
        default: return false;
    }
}

const char *FlowProbeStatsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FlowProbeStatsDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowProbeStats *pp = (FlowProbeStats *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(FlowProbePacket)

FlowProbePacket::FlowProbePacket() : ::critical::probing::ProbingPacketBase()
{
    this->setType(PROBE_PROBE);
    this->setChunkLength(inet::B(77));

}

FlowProbePacket::FlowProbePacket(const FlowProbePacket& other) : ::critical::probing::ProbingPacketBase(other)
{
    copy(other);
}

FlowProbePacket::~FlowProbePacket()
{
}

FlowProbePacket& FlowProbePacket::operator=(const FlowProbePacket& other)
{
    if (this == &other) return *this;
    ::critical::probing::ProbingPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowProbePacket::copy(const FlowProbePacket& other)
{
    this->params = other.params;
    this->stats = other.stats;
}

void FlowProbePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::probing::ProbingPacketBase::parsimPack(b);
    doParsimPacking(b,this->params);
    doParsimPacking(b,this->stats);
}

void FlowProbePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::probing::ProbingPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->params);
    doParsimUnpacking(b,this->stats);
}

const critical::FlowParameters& FlowProbePacket::getParams() const
{
    return this->params;
}

void FlowProbePacket::setParams(const critical::FlowParameters& params)
{
    handleChange();
    this->params = params;
}

const FlowProbeStats& FlowProbePacket::getStats() const
{
    return this->stats;
}

void FlowProbePacket::setStats(const FlowProbeStats& stats)
{
    handleChange();
    this->stats = stats;
}

class FlowProbePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_params,
        FIELD_stats,
    };
  public:
    FlowProbePacketDescriptor();
    virtual ~FlowProbePacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FlowProbePacketDescriptor)

FlowProbePacketDescriptor::FlowProbePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::probing::FlowProbePacket)), "critical::probing::ProbingPacketBase")
{
    propertynames = nullptr;
}

FlowProbePacketDescriptor::~FlowProbePacketDescriptor()
{
    delete[] propertynames;
}

bool FlowProbePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowProbePacket *>(obj)!=nullptr;
}

const char **FlowProbePacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowProbePacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowProbePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int FlowProbePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_params
        FD_ISCOMPOUND,    // FIELD_stats
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *FlowProbePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "params",
        "stats",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int FlowProbePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "params") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "stats") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowProbePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "critical::FlowParameters",    // FIELD_params
        "critical::probing::FlowProbeStats",    // FIELD_stats
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowProbePacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlowProbePacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlowProbePacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowProbePacket *pp = (FlowProbePacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowProbePacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowProbePacket *pp = (FlowProbePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowProbePacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowProbePacket *pp = (FlowProbePacket *)object; (void)pp;
    switch (field) {
        case FIELD_params: {std::stringstream out; out << pp->getParams(); return out.str();}
        case FIELD_stats: {std::stringstream out; out << pp->getStats(); return out.str();}
        default: return "";
    }
}

bool FlowProbePacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowProbePacket *pp = (FlowProbePacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *FlowProbePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_params: return omnetpp::opp_typename(typeid(critical::FlowParameters));
        case FIELD_stats: return omnetpp::opp_typename(typeid(FlowProbeStats));
        default: return nullptr;
    };
}

void *FlowProbePacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowProbePacket *pp = (FlowProbePacket *)object; (void)pp;
    switch (field) {
        case FIELD_params: return toVoidPtr(&pp->getParams()); break;
        case FIELD_stats: return toVoidPtr(&pp->getStats()); break;
        default: return nullptr;
    }
}

Register_Class(FlowConfirmPacket)

FlowConfirmPacket::FlowConfirmPacket() : ::critical::probing::ProbingPacketBase()
{
    this->setType(PROBE_CONFIRM);
}

FlowConfirmPacket::FlowConfirmPacket(const FlowConfirmPacket& other) : ::critical::probing::ProbingPacketBase(other)
{
    copy(other);
}

FlowConfirmPacket::~FlowConfirmPacket()
{
}

FlowConfirmPacket& FlowConfirmPacket::operator=(const FlowConfirmPacket& other)
{
    if (this == &other) return *this;
    ::critical::probing::ProbingPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowConfirmPacket::copy(const FlowConfirmPacket& other)
{
}

void FlowConfirmPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::probing::ProbingPacketBase::parsimPack(b);
}

void FlowConfirmPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::probing::ProbingPacketBase::parsimUnpack(b);
}

class FlowConfirmPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    FlowConfirmPacketDescriptor();
    virtual ~FlowConfirmPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FlowConfirmPacketDescriptor)

FlowConfirmPacketDescriptor::FlowConfirmPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::probing::FlowConfirmPacket)), "critical::probing::ProbingPacketBase")
{
    propertynames = nullptr;
}

FlowConfirmPacketDescriptor::~FlowConfirmPacketDescriptor()
{
    delete[] propertynames;
}

bool FlowConfirmPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowConfirmPacket *>(obj)!=nullptr;
}

const char **FlowConfirmPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowConfirmPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowConfirmPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int FlowConfirmPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *FlowConfirmPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int FlowConfirmPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowConfirmPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **FlowConfirmPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlowConfirmPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlowConfirmPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowConfirmPacket *pp = (FlowConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowConfirmPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowConfirmPacket *pp = (FlowConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowConfirmPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowConfirmPacket *pp = (FlowConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool FlowConfirmPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowConfirmPacket *pp = (FlowConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *FlowConfirmPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *FlowConfirmPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowConfirmPacket *pp = (FlowConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(FlowFreePacket)

FlowFreePacket::FlowFreePacket() : ::critical::probing::ProbingPacketBase()
{
    this->setType(PROBE_FREE);
}

FlowFreePacket::FlowFreePacket(const FlowFreePacket& other) : ::critical::probing::ProbingPacketBase(other)
{
    copy(other);
}

FlowFreePacket::~FlowFreePacket()
{
}

FlowFreePacket& FlowFreePacket::operator=(const FlowFreePacket& other)
{
    if (this == &other) return *this;
    ::critical::probing::ProbingPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowFreePacket::copy(const FlowFreePacket& other)
{
}

void FlowFreePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::probing::ProbingPacketBase::parsimPack(b);
}

void FlowFreePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::probing::ProbingPacketBase::parsimUnpack(b);
}

class FlowFreePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    FlowFreePacketDescriptor();
    virtual ~FlowFreePacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FlowFreePacketDescriptor)

FlowFreePacketDescriptor::FlowFreePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::probing::FlowFreePacket)), "critical::probing::ProbingPacketBase")
{
    propertynames = nullptr;
}

FlowFreePacketDescriptor::~FlowFreePacketDescriptor()
{
    delete[] propertynames;
}

bool FlowFreePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowFreePacket *>(obj)!=nullptr;
}

const char **FlowFreePacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowFreePacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowFreePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int FlowFreePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *FlowFreePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int FlowFreePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowFreePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **FlowFreePacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlowFreePacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlowFreePacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowFreePacket *pp = (FlowFreePacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowFreePacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowFreePacket *pp = (FlowFreePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowFreePacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowFreePacket *pp = (FlowFreePacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool FlowFreePacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowFreePacket *pp = (FlowFreePacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *FlowFreePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *FlowFreePacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowFreePacket *pp = (FlowFreePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(FlowFreeFailurePacket)

FlowFreeFailurePacket::FlowFreeFailurePacket() : ::critical::probing::ProbingPacketBase()
{
    this->setType(PROBE_FREE_FAILURE);
}

FlowFreeFailurePacket::FlowFreeFailurePacket(const FlowFreeFailurePacket& other) : ::critical::probing::ProbingPacketBase(other)
{
    copy(other);
}

FlowFreeFailurePacket::~FlowFreeFailurePacket()
{
}

FlowFreeFailurePacket& FlowFreeFailurePacket::operator=(const FlowFreeFailurePacket& other)
{
    if (this == &other) return *this;
    ::critical::probing::ProbingPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowFreeFailurePacket::copy(const FlowFreeFailurePacket& other)
{
}

void FlowFreeFailurePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::probing::ProbingPacketBase::parsimPack(b);
}

void FlowFreeFailurePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::probing::ProbingPacketBase::parsimUnpack(b);
}

class FlowFreeFailurePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    FlowFreeFailurePacketDescriptor();
    virtual ~FlowFreeFailurePacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FlowFreeFailurePacketDescriptor)

FlowFreeFailurePacketDescriptor::FlowFreeFailurePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::probing::FlowFreeFailurePacket)), "critical::probing::ProbingPacketBase")
{
    propertynames = nullptr;
}

FlowFreeFailurePacketDescriptor::~FlowFreeFailurePacketDescriptor()
{
    delete[] propertynames;
}

bool FlowFreeFailurePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowFreeFailurePacket *>(obj)!=nullptr;
}

const char **FlowFreeFailurePacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowFreeFailurePacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowFreeFailurePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int FlowFreeFailurePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *FlowFreeFailurePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int FlowFreeFailurePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowFreeFailurePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **FlowFreeFailurePacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlowFreeFailurePacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlowFreeFailurePacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowFreeFailurePacket *pp = (FlowFreeFailurePacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowFreeFailurePacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowFreeFailurePacket *pp = (FlowFreeFailurePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowFreeFailurePacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowFreeFailurePacket *pp = (FlowFreeFailurePacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool FlowFreeFailurePacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowFreeFailurePacket *pp = (FlowFreeFailurePacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *FlowFreeFailurePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *FlowFreeFailurePacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowFreeFailurePacket *pp = (FlowFreeFailurePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace probing
} // namespace critical

