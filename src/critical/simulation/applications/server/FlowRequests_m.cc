//
// Generated file, do not edit! Created by nedtool 5.6 from critical/models/applications/server/FlowRequests.msg.
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
#include "FlowRequests_m.h"

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

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("critical::FlowPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("critical::FlowPacketType"));
    e->insert(FLOW_REQUEST, "FLOW_REQUEST");
    e->insert(FLOW_RESPONSE, "FLOW_RESPONSE");
    e->insert(FLOW_FREE, "FLOW_FREE");
    e->insert(FLOW_INTERRUPTED, "FLOW_INTERRUPTED");
)

Register_Class(FlowRequestPacketBase)

FlowRequestPacketBase::FlowRequestPacketBase() : ::inet::FieldsChunk()
{
    this->setChunkLength(inet::B(1));

}

FlowRequestPacketBase::FlowRequestPacketBase(const FlowRequestPacketBase& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

FlowRequestPacketBase::~FlowRequestPacketBase()
{
}

FlowRequestPacketBase& FlowRequestPacketBase::operator=(const FlowRequestPacketBase& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void FlowRequestPacketBase::copy(const FlowRequestPacketBase& other)
{
    this->source = other.source;
    this->destination = other.destination;
    this->label = other.label;
    this->type = other.type;
}

void FlowRequestPacketBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->label);
    doParsimPacking(b,this->type);
}

void FlowRequestPacketBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->label);
    doParsimUnpacking(b,this->type);
}

const inet::Ipv6Address& FlowRequestPacketBase::getSource() const
{
    return this->source;
}

void FlowRequestPacketBase::setSource(const inet::Ipv6Address& source)
{
    handleChange();
    this->source = source;
}

const inet::Ipv6Address& FlowRequestPacketBase::getDestination() const
{
    return this->destination;
}

void FlowRequestPacketBase::setDestination(const inet::Ipv6Address& destination)
{
    handleChange();
    this->destination = destination;
}

uint32_t FlowRequestPacketBase::getLabel() const
{
    return this->label;
}

void FlowRequestPacketBase::setLabel(uint32_t label)
{
    handleChange();
    this->label = label;
}

critical::FlowPacketType FlowRequestPacketBase::getType() const
{
    return this->type;
}

void FlowRequestPacketBase::setType(critical::FlowPacketType type)
{
    handleChange();
    this->type = type;
}

class FlowRequestPacketBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_source,
        FIELD_destination,
        FIELD_label,
        FIELD_type,
    };
  public:
    FlowRequestPacketBaseDescriptor();
    virtual ~FlowRequestPacketBaseDescriptor();

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

Register_ClassDescriptor(FlowRequestPacketBaseDescriptor)

FlowRequestPacketBaseDescriptor::FlowRequestPacketBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::FlowRequestPacketBase)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

FlowRequestPacketBaseDescriptor::~FlowRequestPacketBaseDescriptor()
{
    delete[] propertynames;
}

bool FlowRequestPacketBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowRequestPacketBase *>(obj)!=nullptr;
}

const char **FlowRequestPacketBaseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowRequestPacketBaseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowRequestPacketBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int FlowRequestPacketBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_source
        0,    // FIELD_destination
        FD_ISEDITABLE,    // FIELD_label
        0,    // FIELD_type
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *FlowRequestPacketBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "source",
        "destination",
        "label",
        "type",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int FlowRequestPacketBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "source") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destination") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "label") == 0) return base+2;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowRequestPacketBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_source
        "inet::Ipv6Address",    // FIELD_destination
        "uint32_t",    // FIELD_label
        "critical::FlowPacketType",    // FIELD_type
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowRequestPacketBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *FlowRequestPacketBaseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyname, "enum")) return "critical::FlowPacketType";
            return nullptr;
        default: return nullptr;
    }
}

int FlowRequestPacketBaseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacketBase *pp = (FlowRequestPacketBase *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowRequestPacketBaseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacketBase *pp = (FlowRequestPacketBase *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowRequestPacketBaseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacketBase *pp = (FlowRequestPacketBase *)object; (void)pp;
    switch (field) {
        case FIELD_source: return pp->getSource().str();
        case FIELD_destination: return pp->getDestination().str();
        case FIELD_label: return ulong2string(pp->getLabel());
        case FIELD_type: return enum2string(pp->getType(), "critical::FlowPacketType");
        default: return "";
    }
}

bool FlowRequestPacketBaseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacketBase *pp = (FlowRequestPacketBase *)object; (void)pp;
    switch (field) {
        case FIELD_label: pp->setLabel(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FlowRequestPacketBaseDescriptor::getFieldStructName(int field) const
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

void *FlowRequestPacketBaseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacketBase *pp = (FlowRequestPacketBase *)object; (void)pp;
    switch (field) {
        case FIELD_source: return toVoidPtr(&pp->getSource()); break;
        case FIELD_destination: return toVoidPtr(&pp->getDestination()); break;
        default: return nullptr;
    }
}

Register_Class(FlowRequestPacket)

FlowRequestPacket::FlowRequestPacket() : ::critical::FlowRequestPacketBase()
{
    this->setType(FLOW_REQUEST);
    this->setChunkLength(inet::B(61));

}

FlowRequestPacket::FlowRequestPacket(const FlowRequestPacket& other) : ::critical::FlowRequestPacketBase(other)
{
    copy(other);
}

FlowRequestPacket::~FlowRequestPacket()
{
}

FlowRequestPacket& FlowRequestPacket::operator=(const FlowRequestPacket& other)
{
    if (this == &other) return *this;
    ::critical::FlowRequestPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowRequestPacket::copy(const FlowRequestPacket& other)
{
    this->burst = other.burst;
    this->bandwidth = other.bandwidth;
    this->delay = other.delay;
}

void FlowRequestPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::FlowRequestPacketBase::parsimPack(b);
    doParsimPacking(b,this->burst);
    doParsimPacking(b,this->bandwidth);
    doParsimPacking(b,this->delay);
}

void FlowRequestPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::FlowRequestPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->burst);
    doParsimUnpacking(b,this->bandwidth);
    doParsimUnpacking(b,this->delay);
}

uint64_t FlowRequestPacket::getBurst() const
{
    return this->burst;
}

void FlowRequestPacket::setBurst(uint64_t burst)
{
    handleChange();
    this->burst = burst;
}

uint64_t FlowRequestPacket::getBandwidth() const
{
    return this->bandwidth;
}

void FlowRequestPacket::setBandwidth(uint64_t bandwidth)
{
    handleChange();
    this->bandwidth = bandwidth;
}

uint64_t FlowRequestPacket::getDelay() const
{
    return this->delay;
}

void FlowRequestPacket::setDelay(uint64_t delay)
{
    handleChange();
    this->delay = delay;
}

class FlowRequestPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_burst,
        FIELD_bandwidth,
        FIELD_delay,
    };
  public:
    FlowRequestPacketDescriptor();
    virtual ~FlowRequestPacketDescriptor();

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

Register_ClassDescriptor(FlowRequestPacketDescriptor)

FlowRequestPacketDescriptor::FlowRequestPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::FlowRequestPacket)), "critical::FlowRequestPacketBase")
{
    propertynames = nullptr;
}

FlowRequestPacketDescriptor::~FlowRequestPacketDescriptor()
{
    delete[] propertynames;
}

bool FlowRequestPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowRequestPacket *>(obj)!=nullptr;
}

const char **FlowRequestPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowRequestPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowRequestPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int FlowRequestPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_burst
        FD_ISEDITABLE,    // FIELD_bandwidth
        FD_ISEDITABLE,    // FIELD_delay
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *FlowRequestPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "burst",
        "bandwidth",
        "delay",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int FlowRequestPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'b' && strcmp(fieldName, "burst") == 0) return base+0;
    if (fieldName[0] == 'b' && strcmp(fieldName, "bandwidth") == 0) return base+1;
    if (fieldName[0] == 'd' && strcmp(fieldName, "delay") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowRequestPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_burst
        "uint64_t",    // FIELD_bandwidth
        "uint64_t",    // FIELD_delay
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowRequestPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowRequestPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int FlowRequestPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacket *pp = (FlowRequestPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowRequestPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacket *pp = (FlowRequestPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowRequestPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacket *pp = (FlowRequestPacket *)object; (void)pp;
    switch (field) {
        case FIELD_burst: return uint642string(pp->getBurst());
        case FIELD_bandwidth: return uint642string(pp->getBandwidth());
        case FIELD_delay: return uint642string(pp->getDelay());
        default: return "";
    }
}

bool FlowRequestPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacket *pp = (FlowRequestPacket *)object; (void)pp;
    switch (field) {
        case FIELD_burst: pp->setBurst(string2uint64(value)); return true;
        case FIELD_bandwidth: pp->setBandwidth(string2uint64(value)); return true;
        case FIELD_delay: pp->setDelay(string2uint64(value)); return true;
        default: return false;
    }
}

const char *FlowRequestPacketDescriptor::getFieldStructName(int field) const
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

void *FlowRequestPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowRequestPacket *pp = (FlowRequestPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(FlowResponsePacket)

FlowResponsePacket::FlowResponsePacket() : ::critical::FlowRequestPacketBase()
{
    this->setType(FLOW_RESPONSE);
    this->setChunkLength(inet::B(38));

}

FlowResponsePacket::FlowResponsePacket(const FlowResponsePacket& other) : ::critical::FlowRequestPacketBase(other)
{
    copy(other);
}

FlowResponsePacket::~FlowResponsePacket()
{
}

FlowResponsePacket& FlowResponsePacket::operator=(const FlowResponsePacket& other)
{
    if (this == &other) return *this;
    ::critical::FlowRequestPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowResponsePacket::copy(const FlowResponsePacket& other)
{
    this->accepted = other.accepted;
}

void FlowResponsePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::FlowRequestPacketBase::parsimPack(b);
    doParsimPacking(b,this->accepted);
}

void FlowResponsePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::FlowRequestPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->accepted);
}

bool FlowResponsePacket::getAccepted() const
{
    return this->accepted;
}

void FlowResponsePacket::setAccepted(bool accepted)
{
    handleChange();
    this->accepted = accepted;
}

class FlowResponsePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_accepted,
    };
  public:
    FlowResponsePacketDescriptor();
    virtual ~FlowResponsePacketDescriptor();

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

Register_ClassDescriptor(FlowResponsePacketDescriptor)

FlowResponsePacketDescriptor::FlowResponsePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::FlowResponsePacket)), "critical::FlowRequestPacketBase")
{
    propertynames = nullptr;
}

FlowResponsePacketDescriptor::~FlowResponsePacketDescriptor()
{
    delete[] propertynames;
}

bool FlowResponsePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowResponsePacket *>(obj)!=nullptr;
}

const char **FlowResponsePacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowResponsePacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowResponsePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int FlowResponsePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_accepted
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *FlowResponsePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "accepted",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int FlowResponsePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'a' && strcmp(fieldName, "accepted") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowResponsePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_accepted
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowResponsePacketDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowResponsePacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int FlowResponsePacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowResponsePacket *pp = (FlowResponsePacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowResponsePacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowResponsePacket *pp = (FlowResponsePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowResponsePacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowResponsePacket *pp = (FlowResponsePacket *)object; (void)pp;
    switch (field) {
        case FIELD_accepted: return bool2string(pp->getAccepted());
        default: return "";
    }
}

bool FlowResponsePacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowResponsePacket *pp = (FlowResponsePacket *)object; (void)pp;
    switch (field) {
        case FIELD_accepted: pp->setAccepted(string2bool(value)); return true;
        default: return false;
    }
}

const char *FlowResponsePacketDescriptor::getFieldStructName(int field) const
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

void *FlowResponsePacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowResponsePacket *pp = (FlowResponsePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(FlowFreePacket)

FlowFreePacket::FlowFreePacket() : ::critical::FlowRequestPacketBase()
{
    this->setType(FLOW_FREE);
    this->setChunkLength(inet::B(37));
}

FlowFreePacket::FlowFreePacket(const FlowFreePacket& other) : ::critical::FlowRequestPacketBase(other)
{
    copy(other);
}

FlowFreePacket::~FlowFreePacket()
{
}

FlowFreePacket& FlowFreePacket::operator=(const FlowFreePacket& other)
{
    if (this == &other) return *this;
    ::critical::FlowRequestPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowFreePacket::copy(const FlowFreePacket& other)
{
}

void FlowFreePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::FlowRequestPacketBase::parsimPack(b);
}

void FlowFreePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::FlowRequestPacketBase::parsimUnpack(b);
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

FlowFreePacketDescriptor::FlowFreePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::FlowFreePacket)), "critical::FlowRequestPacketBase")
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

Register_Class(FlowInterruptedPacket)

FlowInterruptedPacket::FlowInterruptedPacket() : ::critical::FlowRequestPacketBase()
{
    this->setType(FLOW_INTERRUPTED);
    this->setChunkLength(inet::B(38));

}

FlowInterruptedPacket::FlowInterruptedPacket(const FlowInterruptedPacket& other) : ::critical::FlowRequestPacketBase(other)
{
    copy(other);
}

FlowInterruptedPacket::~FlowInterruptedPacket()
{
}

FlowInterruptedPacket& FlowInterruptedPacket::operator=(const FlowInterruptedPacket& other)
{
    if (this == &other) return *this;
    ::critical::FlowRequestPacketBase::operator=(other);
    copy(other);
    return *this;
}

void FlowInterruptedPacket::copy(const FlowInterruptedPacket& other)
{
    this->continued = other.continued;
}

void FlowInterruptedPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::FlowRequestPacketBase::parsimPack(b);
    doParsimPacking(b,this->continued);
}

void FlowInterruptedPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::FlowRequestPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->continued);
}

bool FlowInterruptedPacket::getContinued() const
{
    return this->continued;
}

void FlowInterruptedPacket::setContinued(bool continued)
{
    handleChange();
    this->continued = continued;
}

class FlowInterruptedPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_continued,
    };
  public:
    FlowInterruptedPacketDescriptor();
    virtual ~FlowInterruptedPacketDescriptor();

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

Register_ClassDescriptor(FlowInterruptedPacketDescriptor)

FlowInterruptedPacketDescriptor::FlowInterruptedPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::FlowInterruptedPacket)), "critical::FlowRequestPacketBase")
{
    propertynames = nullptr;
}

FlowInterruptedPacketDescriptor::~FlowInterruptedPacketDescriptor()
{
    delete[] propertynames;
}

bool FlowInterruptedPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowInterruptedPacket *>(obj)!=nullptr;
}

const char **FlowInterruptedPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlowInterruptedPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlowInterruptedPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int FlowInterruptedPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_continued
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *FlowInterruptedPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "continued",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int FlowInterruptedPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'c' && strcmp(fieldName, "continued") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlowInterruptedPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_continued
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowInterruptedPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowInterruptedPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int FlowInterruptedPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlowInterruptedPacket *pp = (FlowInterruptedPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlowInterruptedPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowInterruptedPacket *pp = (FlowInterruptedPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowInterruptedPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlowInterruptedPacket *pp = (FlowInterruptedPacket *)object; (void)pp;
    switch (field) {
        case FIELD_continued: return bool2string(pp->getContinued());
        default: return "";
    }
}

bool FlowInterruptedPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlowInterruptedPacket *pp = (FlowInterruptedPacket *)object; (void)pp;
    switch (field) {
        case FIELD_continued: pp->setContinued(string2bool(value)); return true;
        default: return false;
    }
}

const char *FlowInterruptedPacketDescriptor::getFieldStructName(int field) const
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

void *FlowInterruptedPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlowInterruptedPacket *pp = (FlowInterruptedPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace critical

