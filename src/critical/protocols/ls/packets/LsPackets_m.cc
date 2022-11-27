//
// Generated file, do not edit! Created by nedtool 5.6 from critical/protocols/ls/packets/LsPackets.msg.
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
#include "LsPackets_m.h"

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
namespace ls {

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

class QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor();
    virtual ~QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor();

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

Register_ClassDescriptor(QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor)

QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::QueueLevelTopologyLinkEncoding::DecodedLink)), "")
{
    propertynames = nullptr;
}

QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::~QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor()
{
    delete[] propertynames;
}

bool QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QueueLevelTopologyLinkEncoding::DecodedLink *>(obj)!=nullptr;
}

const char **QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldPropertyNames(int field) const
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

const char *QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QueueLevelTopologyLinkEncoding::DecodedLink *pp = (QueueLevelTopologyLinkEncoding::DecodedLink *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QueueLevelTopologyLinkEncoding::DecodedLink *pp = (QueueLevelTopologyLinkEncoding::DecodedLink *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QueueLevelTopologyLinkEncoding::DecodedLink *pp = (QueueLevelTopologyLinkEncoding::DecodedLink *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QueueLevelTopologyLinkEncoding::DecodedLink *pp = (QueueLevelTopologyLinkEncoding::DecodedLink *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *QueueLevelTopologyLinkEncoding__DecodedLinkDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QueueLevelTopologyLinkEncoding::DecodedLink *pp = (QueueLevelTopologyLinkEncoding::DecodedLink *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(LsPacketBase)

LsPacketBase::LsPacketBase() : ::critical::CriticalPacketBase()
{
}

LsPacketBase::LsPacketBase(const LsPacketBase& other) : ::critical::CriticalPacketBase(other)
{
    copy(other);
}

LsPacketBase::~LsPacketBase()
{
}

LsPacketBase& LsPacketBase::operator=(const LsPacketBase& other)
{
    if (this == &other) return *this;
    ::critical::CriticalPacketBase::operator=(other);
    copy(other);
    return *this;
}

void LsPacketBase::copy(const LsPacketBase& other)
{
}

void LsPacketBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::CriticalPacketBase::parsimPack(b);
}

void LsPacketBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::CriticalPacketBase::parsimUnpack(b);
}

class LsPacketBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    LsPacketBaseDescriptor();
    virtual ~LsPacketBaseDescriptor();

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

Register_ClassDescriptor(LsPacketBaseDescriptor)

LsPacketBaseDescriptor::LsPacketBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LsPacketBase)), "critical::CriticalPacketBase")
{
    propertynames = nullptr;
}

LsPacketBaseDescriptor::~LsPacketBaseDescriptor()
{
    delete[] propertynames;
}

bool LsPacketBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LsPacketBase *>(obj)!=nullptr;
}

const char **LsPacketBaseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LsPacketBaseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LsPacketBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int LsPacketBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *LsPacketBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int LsPacketBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LsPacketBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **LsPacketBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *LsPacketBaseDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LsPacketBaseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LsPacketBase *pp = (LsPacketBase *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LsPacketBaseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsPacketBase *pp = (LsPacketBase *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LsPacketBaseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsPacketBase *pp = (LsPacketBase *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool LsPacketBaseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LsPacketBase *pp = (LsPacketBase *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *LsPacketBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *LsPacketBaseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LsPacketBase *pp = (LsPacketBase *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(LsPacketBaseId)

LsPacketBaseId::LsPacketBaseId() : ::critical::ls::LsPacketBase()
{
}

LsPacketBaseId::LsPacketBaseId(const LsPacketBaseId& other) : ::critical::ls::LsPacketBase(other)
{
    copy(other);
}

LsPacketBaseId::~LsPacketBaseId()
{
}

LsPacketBaseId& LsPacketBaseId::operator=(const LsPacketBaseId& other)
{
    if (this == &other) return *this;
    ::critical::ls::LsPacketBase::operator=(other);
    copy(other);
    return *this;
}

void LsPacketBaseId::copy(const LsPacketBaseId& other)
{
    this->routerId = other.routerId;
}

void LsPacketBaseId::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LsPacketBase::parsimPack(b);
    doParsimPacking(b,this->routerId);
}

void LsPacketBaseId::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LsPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->routerId);
}

const inet::Ipv6Address& LsPacketBaseId::getRouterId() const
{
    return this->routerId;
}

void LsPacketBaseId::setRouterId(const inet::Ipv6Address& routerId)
{
    handleChange();
    this->routerId = routerId;
}

class LsPacketBaseIdDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_routerId,
    };
  public:
    LsPacketBaseIdDescriptor();
    virtual ~LsPacketBaseIdDescriptor();

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

Register_ClassDescriptor(LsPacketBaseIdDescriptor)

LsPacketBaseIdDescriptor::LsPacketBaseIdDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LsPacketBaseId)), "critical::ls::LsPacketBase")
{
    propertynames = nullptr;
}

LsPacketBaseIdDescriptor::~LsPacketBaseIdDescriptor()
{
    delete[] propertynames;
}

bool LsPacketBaseIdDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LsPacketBaseId *>(obj)!=nullptr;
}

const char **LsPacketBaseIdDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LsPacketBaseIdDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LsPacketBaseIdDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int LsPacketBaseIdDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_routerId
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *LsPacketBaseIdDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routerId",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int LsPacketBaseIdDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routerId") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LsPacketBaseIdDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_routerId
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **LsPacketBaseIdDescriptor::getFieldPropertyNames(int field) const
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

const char *LsPacketBaseIdDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LsPacketBaseIdDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LsPacketBaseId *pp = (LsPacketBaseId *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LsPacketBaseIdDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsPacketBaseId *pp = (LsPacketBaseId *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LsPacketBaseIdDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsPacketBaseId *pp = (LsPacketBaseId *)object; (void)pp;
    switch (field) {
        case FIELD_routerId: return pp->getRouterId().str();
        default: return "";
    }
}

bool LsPacketBaseIdDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LsPacketBaseId *pp = (LsPacketBaseId *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *LsPacketBaseIdDescriptor::getFieldStructName(int field) const
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

void *LsPacketBaseIdDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LsPacketBaseId *pp = (LsPacketBaseId *)object; (void)pp;
    switch (field) {
        case FIELD_routerId: return toVoidPtr(&pp->getRouterId()); break;
        default: return nullptr;
    }
}

Register_Class(LsHelloPacket)

LsHelloPacket::LsHelloPacket() : ::critical::ls::LsPacketBaseId()
{
    this->setType(LS_HELLO);
    this->setChunkLength(inet::B(17));
}

LsHelloPacket::LsHelloPacket(const LsHelloPacket& other) : ::critical::ls::LsPacketBaseId(other)
{
    copy(other);
}

LsHelloPacket::~LsHelloPacket()
{
}

LsHelloPacket& LsHelloPacket::operator=(const LsHelloPacket& other)
{
    if (this == &other) return *this;
    ::critical::ls::LsPacketBaseId::operator=(other);
    copy(other);
    return *this;
}

void LsHelloPacket::copy(const LsHelloPacket& other)
{
}

void LsHelloPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LsPacketBaseId::parsimPack(b);
}

void LsHelloPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LsPacketBaseId::parsimUnpack(b);
}

class LsHelloPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    LsHelloPacketDescriptor();
    virtual ~LsHelloPacketDescriptor();

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

Register_ClassDescriptor(LsHelloPacketDescriptor)

LsHelloPacketDescriptor::LsHelloPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LsHelloPacket)), "critical::ls::LsPacketBaseId")
{
    propertynames = nullptr;
}

LsHelloPacketDescriptor::~LsHelloPacketDescriptor()
{
    delete[] propertynames;
}

bool LsHelloPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LsHelloPacket *>(obj)!=nullptr;
}

const char **LsHelloPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LsHelloPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LsHelloPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int LsHelloPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *LsHelloPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int LsHelloPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LsHelloPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **LsHelloPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *LsHelloPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LsHelloPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LsHelloPacket *pp = (LsHelloPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LsHelloPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsHelloPacket *pp = (LsHelloPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LsHelloPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsHelloPacket *pp = (LsHelloPacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool LsHelloPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LsHelloPacket *pp = (LsHelloPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *LsHelloPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *LsHelloPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LsHelloPacket *pp = (LsHelloPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(LinkStateNetworkEntry)

LinkStateNetworkEntry::LinkStateNetworkEntry() : ::inet::FieldsChunk()
{
    this->setChunkLength(inet::B(20));

}

LinkStateNetworkEntry::LinkStateNetworkEntry(const LinkStateNetworkEntry& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LinkStateNetworkEntry::~LinkStateNetworkEntry()
{
}

LinkStateNetworkEntry& LinkStateNetworkEntry::operator=(const LinkStateNetworkEntry& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LinkStateNetworkEntry::copy(const LinkStateNetworkEntry& other)
{
    this->network = other.network;
    this->prefixLength = other.prefixLength;
    this->numQueues = other.numQueues;
    this->linkId = other.linkId;
}

void LinkStateNetworkEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->network);
    doParsimPacking(b,this->prefixLength);
    doParsimPacking(b,this->numQueues);
    doParsimPacking(b,this->linkId);
}

void LinkStateNetworkEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->network);
    doParsimUnpacking(b,this->prefixLength);
    doParsimUnpacking(b,this->numQueues);
    doParsimUnpacking(b,this->linkId);
}

const inet::Ipv6Address& LinkStateNetworkEntry::getNetwork() const
{
    return this->network;
}

void LinkStateNetworkEntry::setNetwork(const inet::Ipv6Address& network)
{
    handleChange();
    this->network = network;
}

uint8_t LinkStateNetworkEntry::getPrefixLength() const
{
    return this->prefixLength;
}

void LinkStateNetworkEntry::setPrefixLength(uint8_t prefixLength)
{
    handleChange();
    this->prefixLength = prefixLength;
}

uint8_t LinkStateNetworkEntry::getNumQueues() const
{
    return this->numQueues;
}

void LinkStateNetworkEntry::setNumQueues(uint8_t numQueues)
{
    handleChange();
    this->numQueues = numQueues;
}

int LinkStateNetworkEntry::getLinkId() const
{
    return this->linkId;
}

void LinkStateNetworkEntry::setLinkId(int linkId)
{
    handleChange();
    this->linkId = linkId;
}

class LinkStateNetworkEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_network,
        FIELD_prefixLength,
        FIELD_numQueues,
        FIELD_linkId,
    };
  public:
    LinkStateNetworkEntryDescriptor();
    virtual ~LinkStateNetworkEntryDescriptor();

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

Register_ClassDescriptor(LinkStateNetworkEntryDescriptor)

LinkStateNetworkEntryDescriptor::LinkStateNetworkEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LinkStateNetworkEntry)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

LinkStateNetworkEntryDescriptor::~LinkStateNetworkEntryDescriptor()
{
    delete[] propertynames;
}

bool LinkStateNetworkEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinkStateNetworkEntry *>(obj)!=nullptr;
}

const char **LinkStateNetworkEntryDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LinkStateNetworkEntryDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LinkStateNetworkEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int LinkStateNetworkEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_network
        FD_ISEDITABLE,    // FIELD_prefixLength
        FD_ISEDITABLE,    // FIELD_numQueues
        FD_ISEDITABLE,    // FIELD_linkId
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *LinkStateNetworkEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "network",
        "prefixLength",
        "numQueues",
        "linkId",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int LinkStateNetworkEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "network") == 0) return base+0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefixLength") == 0) return base+1;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numQueues") == 0) return base+2;
    if (fieldName[0] == 'l' && strcmp(fieldName, "linkId") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LinkStateNetworkEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_network
        "uint8_t",    // FIELD_prefixLength
        "uint8_t",    // FIELD_numQueues
        "int",    // FIELD_linkId
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **LinkStateNetworkEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *LinkStateNetworkEntryDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LinkStateNetworkEntryDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LinkStateNetworkEntry *pp = (LinkStateNetworkEntry *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LinkStateNetworkEntryDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LinkStateNetworkEntry *pp = (LinkStateNetworkEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinkStateNetworkEntryDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LinkStateNetworkEntry *pp = (LinkStateNetworkEntry *)object; (void)pp;
    switch (field) {
        case FIELD_network: return pp->getNetwork().str();
        case FIELD_prefixLength: return ulong2string(pp->getPrefixLength());
        case FIELD_numQueues: return ulong2string(pp->getNumQueues());
        case FIELD_linkId: return long2string(pp->getLinkId());
        default: return "";
    }
}

bool LinkStateNetworkEntryDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LinkStateNetworkEntry *pp = (LinkStateNetworkEntry *)object; (void)pp;
    switch (field) {
        case FIELD_prefixLength: pp->setPrefixLength(string2ulong(value)); return true;
        case FIELD_numQueues: pp->setNumQueues(string2ulong(value)); return true;
        case FIELD_linkId: pp->setLinkId(string2long(value)); return true;
        default: return false;
    }
}

const char *LinkStateNetworkEntryDescriptor::getFieldStructName(int field) const
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

void *LinkStateNetworkEntryDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LinkStateNetworkEntry *pp = (LinkStateNetworkEntry *)object; (void)pp;
    switch (field) {
        case FIELD_network: return toVoidPtr(&pp->getNetwork()); break;
        default: return nullptr;
    }
}

Register_Class(LinkStateNeighborEntry)

LinkStateNeighborEntry::LinkStateNeighborEntry() : ::critical::ls::LinkStateNetworkEntry()
{
    this->setChunkLength(inet::B(53));

}

LinkStateNeighborEntry::LinkStateNeighborEntry(const LinkStateNeighborEntry& other) : ::critical::ls::LinkStateNetworkEntry(other)
{
    copy(other);
}

LinkStateNeighborEntry::~LinkStateNeighborEntry()
{
}

LinkStateNeighborEntry& LinkStateNeighborEntry::operator=(const LinkStateNeighborEntry& other)
{
    if (this == &other) return *this;
    ::critical::ls::LinkStateNetworkEntry::operator=(other);
    copy(other);
    return *this;
}

void LinkStateNeighborEntry::copy(const LinkStateNeighborEntry& other)
{
    this->neighborId = other.neighborId;
    this->cost = other.cost;
    this->bw = other.bw;
    this->delay = other.delay;
}

void LinkStateNeighborEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LinkStateNetworkEntry::parsimPack(b);
    doParsimPacking(b,this->neighborId);
    doParsimPacking(b,this->cost);
    doParsimPacking(b,this->bw);
    doParsimPacking(b,this->delay);
}

void LinkStateNeighborEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LinkStateNetworkEntry::parsimUnpack(b);
    doParsimUnpacking(b,this->neighborId);
    doParsimUnpacking(b,this->cost);
    doParsimUnpacking(b,this->bw);
    doParsimUnpacking(b,this->delay);
}

const inet::Ipv6Address& LinkStateNeighborEntry::getNeighborId() const
{
    return this->neighborId;
}

void LinkStateNeighborEntry::setNeighborId(const inet::Ipv6Address& neighborId)
{
    handleChange();
    this->neighborId = neighborId;
}

uint8_t LinkStateNeighborEntry::getCost() const
{
    return this->cost;
}

void LinkStateNeighborEntry::setCost(uint8_t cost)
{
    handleChange();
    this->cost = cost;
}

uint64_t LinkStateNeighborEntry::getBw() const
{
    return this->bw;
}

void LinkStateNeighborEntry::setBw(uint64_t bw)
{
    handleChange();
    this->bw = bw;
}

uint64_t LinkStateNeighborEntry::getDelay() const
{
    return this->delay;
}

void LinkStateNeighborEntry::setDelay(uint64_t delay)
{
    handleChange();
    this->delay = delay;
}

class LinkStateNeighborEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_neighborId,
        FIELD_cost,
        FIELD_bw,
        FIELD_delay,
    };
  public:
    LinkStateNeighborEntryDescriptor();
    virtual ~LinkStateNeighborEntryDescriptor();

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

Register_ClassDescriptor(LinkStateNeighborEntryDescriptor)

LinkStateNeighborEntryDescriptor::LinkStateNeighborEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LinkStateNeighborEntry)), "critical::ls::LinkStateNetworkEntry")
{
    propertynames = nullptr;
}

LinkStateNeighborEntryDescriptor::~LinkStateNeighborEntryDescriptor()
{
    delete[] propertynames;
}

bool LinkStateNeighborEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinkStateNeighborEntry *>(obj)!=nullptr;
}

const char **LinkStateNeighborEntryDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LinkStateNeighborEntryDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LinkStateNeighborEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int LinkStateNeighborEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_neighborId
        FD_ISEDITABLE,    // FIELD_cost
        FD_ISEDITABLE,    // FIELD_bw
        FD_ISEDITABLE,    // FIELD_delay
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *LinkStateNeighborEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "neighborId",
        "cost",
        "bw",
        "delay",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int LinkStateNeighborEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "neighborId") == 0) return base+0;
    if (fieldName[0] == 'c' && strcmp(fieldName, "cost") == 0) return base+1;
    if (fieldName[0] == 'b' && strcmp(fieldName, "bw") == 0) return base+2;
    if (fieldName[0] == 'd' && strcmp(fieldName, "delay") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LinkStateNeighborEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_neighborId
        "uint8_t",    // FIELD_cost
        "uint64_t",    // FIELD_bw
        "uint64_t",    // FIELD_delay
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **LinkStateNeighborEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *LinkStateNeighborEntryDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LinkStateNeighborEntryDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LinkStateNeighborEntry *pp = (LinkStateNeighborEntry *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LinkStateNeighborEntryDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LinkStateNeighborEntry *pp = (LinkStateNeighborEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinkStateNeighborEntryDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LinkStateNeighborEntry *pp = (LinkStateNeighborEntry *)object; (void)pp;
    switch (field) {
        case FIELD_neighborId: return pp->getNeighborId().str();
        case FIELD_cost: return ulong2string(pp->getCost());
        case FIELD_bw: return uint642string(pp->getBw());
        case FIELD_delay: return uint642string(pp->getDelay());
        default: return "";
    }
}

bool LinkStateNeighborEntryDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LinkStateNeighborEntry *pp = (LinkStateNeighborEntry *)object; (void)pp;
    switch (field) {
        case FIELD_cost: pp->setCost(string2ulong(value)); return true;
        case FIELD_bw: pp->setBw(string2uint64(value)); return true;
        case FIELD_delay: pp->setDelay(string2uint64(value)); return true;
        default: return false;
    }
}

const char *LinkStateNeighborEntryDescriptor::getFieldStructName(int field) const
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

void *LinkStateNeighborEntryDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LinkStateNeighborEntry *pp = (LinkStateNeighborEntry *)object; (void)pp;
    switch (field) {
        case FIELD_neighborId: return toVoidPtr(&pp->getNeighborId()); break;
        default: return nullptr;
    }
}

Register_Class(LsaPacket)

LsaPacket::LsaPacket() : ::critical::ls::LsPacketBaseId()
{
    this->setType(LS_LSA);
    this->setChunkLength(inet::B(22));

}

LsaPacket::LsaPacket(const LsaPacket& other) : ::critical::ls::LsPacketBaseId(other)
{
    copy(other);
}

LsaPacket::~LsaPacket()
{
    delete [] this->networkEntries;
    delete [] this->neighborEntries;
}

LsaPacket& LsaPacket::operator=(const LsaPacket& other)
{
    if (this == &other) return *this;
    ::critical::ls::LsPacketBaseId::operator=(other);
    copy(other);
    return *this;
}

void LsaPacket::copy(const LsaPacket& other)
{
    this->networkEntriesCount = other.networkEntriesCount;
    this->sequenceNumber = other.sequenceNumber;
    delete [] this->networkEntries;
    this->networkEntries = (other.networkEntries_arraysize==0) ? nullptr : new LinkStateNetworkEntry[other.networkEntries_arraysize];
    networkEntries_arraysize = other.networkEntries_arraysize;
    for (size_t i = 0; i < networkEntries_arraysize; i++) {
        this->networkEntries[i] = other.networkEntries[i];
    }
    delete [] this->neighborEntries;
    this->neighborEntries = (other.neighborEntries_arraysize==0) ? nullptr : new LinkStateNeighborEntry[other.neighborEntries_arraysize];
    neighborEntries_arraysize = other.neighborEntries_arraysize;
    for (size_t i = 0; i < neighborEntries_arraysize; i++) {
        this->neighborEntries[i] = other.neighborEntries[i];
    }
}

void LsaPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LsPacketBaseId::parsimPack(b);
    doParsimPacking(b,this->networkEntriesCount);
    doParsimPacking(b,this->sequenceNumber);
    b->pack(networkEntries_arraysize);
    doParsimArrayPacking(b,this->networkEntries,networkEntries_arraysize);
    b->pack(neighborEntries_arraysize);
    doParsimArrayPacking(b,this->neighborEntries,neighborEntries_arraysize);
}

void LsaPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LsPacketBaseId::parsimUnpack(b);
    doParsimUnpacking(b,this->networkEntriesCount);
    doParsimUnpacking(b,this->sequenceNumber);
    delete [] this->networkEntries;
    b->unpack(networkEntries_arraysize);
    if (networkEntries_arraysize == 0) {
        this->networkEntries = nullptr;
    } else {
        this->networkEntries = new LinkStateNetworkEntry[networkEntries_arraysize];
        doParsimArrayUnpacking(b,this->networkEntries,networkEntries_arraysize);
    }
    delete [] this->neighborEntries;
    b->unpack(neighborEntries_arraysize);
    if (neighborEntries_arraysize == 0) {
        this->neighborEntries = nullptr;
    } else {
        this->neighborEntries = new LinkStateNeighborEntry[neighborEntries_arraysize];
        doParsimArrayUnpacking(b,this->neighborEntries,neighborEntries_arraysize);
    }
}

uint8_t LsaPacket::getNetworkEntriesCount() const
{
    return this->networkEntriesCount;
}

void LsaPacket::setNetworkEntriesCount(uint8_t networkEntriesCount)
{
    handleChange();
    this->networkEntriesCount = networkEntriesCount;
}

uint32_t LsaPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void LsaPacket::setSequenceNumber(uint32_t sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

size_t LsaPacket::getNetworkEntriesArraySize() const
{
    return networkEntries_arraysize;
}

const LinkStateNetworkEntry& LsaPacket::getNetworkEntries(size_t k) const
{
    if (k >= networkEntries_arraysize) throw omnetpp::cRuntimeError("Array of size networkEntries_arraysize indexed by %lu", (unsigned long)k);
    return this->networkEntries[k];
}

void LsaPacket::setNetworkEntriesArraySize(size_t newSize)
{
    handleChange();
    LinkStateNetworkEntry *networkEntries2 = (newSize==0) ? nullptr : new LinkStateNetworkEntry[newSize];
    size_t minSize = networkEntries_arraysize < newSize ? networkEntries_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        networkEntries2[i] = this->networkEntries[i];
    delete [] this->networkEntries;
    this->networkEntries = networkEntries2;
    networkEntries_arraysize = newSize;
}

void LsaPacket::setNetworkEntries(size_t k, const LinkStateNetworkEntry& networkEntries)
{
    if (k >= networkEntries_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->networkEntries[k] = networkEntries;
}

void LsaPacket::insertNetworkEntries(size_t k, const LinkStateNetworkEntry& networkEntries)
{
    handleChange();
    if (k > networkEntries_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = networkEntries_arraysize + 1;
    LinkStateNetworkEntry *networkEntries2 = new LinkStateNetworkEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        networkEntries2[i] = this->networkEntries[i];
    networkEntries2[k] = networkEntries;
    for (i = k + 1; i < newSize; i++)
        networkEntries2[i] = this->networkEntries[i-1];
    delete [] this->networkEntries;
    this->networkEntries = networkEntries2;
    networkEntries_arraysize = newSize;
}

void LsaPacket::insertNetworkEntries(const LinkStateNetworkEntry& networkEntries)
{
    insertNetworkEntries(networkEntries_arraysize, networkEntries);
}

void LsaPacket::eraseNetworkEntries(size_t k)
{
    if (k >= networkEntries_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = networkEntries_arraysize - 1;
    LinkStateNetworkEntry *networkEntries2 = (newSize == 0) ? nullptr : new LinkStateNetworkEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        networkEntries2[i] = this->networkEntries[i];
    for (i = k; i < newSize; i++)
        networkEntries2[i] = this->networkEntries[i+1];
    delete [] this->networkEntries;
    this->networkEntries = networkEntries2;
    networkEntries_arraysize = newSize;
}

size_t LsaPacket::getNeighborEntriesArraySize() const
{
    return neighborEntries_arraysize;
}

const LinkStateNeighborEntry& LsaPacket::getNeighborEntries(size_t k) const
{
    if (k >= neighborEntries_arraysize) throw omnetpp::cRuntimeError("Array of size neighborEntries_arraysize indexed by %lu", (unsigned long)k);
    return this->neighborEntries[k];
}

void LsaPacket::setNeighborEntriesArraySize(size_t newSize)
{
    handleChange();
    LinkStateNeighborEntry *neighborEntries2 = (newSize==0) ? nullptr : new LinkStateNeighborEntry[newSize];
    size_t minSize = neighborEntries_arraysize < newSize ? neighborEntries_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        neighborEntries2[i] = this->neighborEntries[i];
    delete [] this->neighborEntries;
    this->neighborEntries = neighborEntries2;
    neighborEntries_arraysize = newSize;
}

void LsaPacket::setNeighborEntries(size_t k, const LinkStateNeighborEntry& neighborEntries)
{
    if (k >= neighborEntries_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->neighborEntries[k] = neighborEntries;
}

void LsaPacket::insertNeighborEntries(size_t k, const LinkStateNeighborEntry& neighborEntries)
{
    handleChange();
    if (k > neighborEntries_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = neighborEntries_arraysize + 1;
    LinkStateNeighborEntry *neighborEntries2 = new LinkStateNeighborEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborEntries2[i] = this->neighborEntries[i];
    neighborEntries2[k] = neighborEntries;
    for (i = k + 1; i < newSize; i++)
        neighborEntries2[i] = this->neighborEntries[i-1];
    delete [] this->neighborEntries;
    this->neighborEntries = neighborEntries2;
    neighborEntries_arraysize = newSize;
}

void LsaPacket::insertNeighborEntries(const LinkStateNeighborEntry& neighborEntries)
{
    insertNeighborEntries(neighborEntries_arraysize, neighborEntries);
}

void LsaPacket::eraseNeighborEntries(size_t k)
{
    if (k >= neighborEntries_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = neighborEntries_arraysize - 1;
    LinkStateNeighborEntry *neighborEntries2 = (newSize == 0) ? nullptr : new LinkStateNeighborEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborEntries2[i] = this->neighborEntries[i];
    for (i = k; i < newSize; i++)
        neighborEntries2[i] = this->neighborEntries[i+1];
    delete [] this->neighborEntries;
    this->neighborEntries = neighborEntries2;
    neighborEntries_arraysize = newSize;
}

class LsaPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_networkEntriesCount,
        FIELD_sequenceNumber,
        FIELD_networkEntries,
        FIELD_neighborEntries,
    };
  public:
    LsaPacketDescriptor();
    virtual ~LsaPacketDescriptor();

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

Register_ClassDescriptor(LsaPacketDescriptor)

LsaPacketDescriptor::LsaPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LsaPacket)), "critical::ls::LsPacketBaseId")
{
    propertynames = nullptr;
}

LsaPacketDescriptor::~LsaPacketDescriptor()
{
    delete[] propertynames;
}

bool LsaPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LsaPacket *>(obj)!=nullptr;
}

const char **LsaPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LsaPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LsaPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int LsaPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_networkEntriesCount
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_networkEntries
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_neighborEntries
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *LsaPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkEntriesCount",
        "sequenceNumber",
        "networkEntries",
        "neighborEntries",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int LsaPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "networkEntriesCount") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sequenceNumber") == 0) return base+1;
    if (fieldName[0] == 'n' && strcmp(fieldName, "networkEntries") == 0) return base+2;
    if (fieldName[0] == 'n' && strcmp(fieldName, "neighborEntries") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LsaPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_networkEntriesCount
        "uint32_t",    // FIELD_sequenceNumber
        "critical::ls::LinkStateNetworkEntry",    // FIELD_networkEntries
        "critical::ls::LinkStateNeighborEntry",    // FIELD_neighborEntries
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **LsaPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *LsaPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LsaPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LsaPacket *pp = (LsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_networkEntries: return pp->getNetworkEntriesArraySize();
        case FIELD_neighborEntries: return pp->getNeighborEntriesArraySize();
        default: return 0;
    }
}

const char *LsaPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsaPacket *pp = (LsaPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LsaPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsaPacket *pp = (LsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_networkEntriesCount: return ulong2string(pp->getNetworkEntriesCount());
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_networkEntries: {std::stringstream out; out << pp->getNetworkEntries(i); return out.str();}
        case FIELD_neighborEntries: {std::stringstream out; out << pp->getNeighborEntries(i); return out.str();}
        default: return "";
    }
}

bool LsaPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LsaPacket *pp = (LsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_networkEntriesCount: pp->setNetworkEntriesCount(string2ulong(value)); return true;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); return true;
        default: return false;
    }
}

const char *LsaPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_networkEntries: return omnetpp::opp_typename(typeid(LinkStateNetworkEntry));
        case FIELD_neighborEntries: return omnetpp::opp_typename(typeid(LinkStateNeighborEntry));
        default: return nullptr;
    };
}

void *LsaPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LsaPacket *pp = (LsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_networkEntries: return toVoidPtr(&pp->getNetworkEntries(i)); break;
        case FIELD_neighborEntries: return toVoidPtr(&pp->getNeighborEntries(i)); break;
        default: return nullptr;
    }
}

Register_Class(QosLsaPacket)

QosLsaPacket::QosLsaPacket() : ::critical::ls::LsPacketBaseId()
{
    this->setType(LS_QOS_LSA);
    this->setChunkLength(inet::B(23));

}

QosLsaPacket::QosLsaPacket(const QosLsaPacket& other) : ::critical::ls::LsPacketBaseId(other)
{
    copy(other);
}

QosLsaPacket::~QosLsaPacket()
{
    delete [] this->queues;
}

QosLsaPacket& QosLsaPacket::operator=(const QosLsaPacket& other)
{
    if (this == &other) return *this;
    ::critical::ls::LsPacketBaseId::operator=(other);
    copy(other);
    return *this;
}

void QosLsaPacket::copy(const QosLsaPacket& other)
{
    this->sequenceNumber = other.sequenceNumber;
    this->linkId = other.linkId;
    delete [] this->queues;
    this->queues = (other.queues_arraysize==0) ? nullptr : new QueueInfo[other.queues_arraysize];
    queues_arraysize = other.queues_arraysize;
    for (size_t i = 0; i < queues_arraysize; i++) {
        this->queues[i] = other.queues[i];
    }
}

void QosLsaPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LsPacketBaseId::parsimPack(b);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->linkId);
    b->pack(queues_arraysize);
    doParsimArrayPacking(b,this->queues,queues_arraysize);
}

void QosLsaPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LsPacketBaseId::parsimUnpack(b);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->linkId);
    delete [] this->queues;
    b->unpack(queues_arraysize);
    if (queues_arraysize == 0) {
        this->queues = nullptr;
    } else {
        this->queues = new QueueInfo[queues_arraysize];
        doParsimArrayUnpacking(b,this->queues,queues_arraysize);
    }
}

uint32_t QosLsaPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void QosLsaPacket::setSequenceNumber(uint32_t sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

int QosLsaPacket::getLinkId() const
{
    return this->linkId;
}

void QosLsaPacket::setLinkId(int linkId)
{
    handleChange();
    this->linkId = linkId;
}

size_t QosLsaPacket::getQueuesArraySize() const
{
    return queues_arraysize;
}

const QueueInfo& QosLsaPacket::getQueues(size_t k) const
{
    if (k >= queues_arraysize) throw omnetpp::cRuntimeError("Array of size queues_arraysize indexed by %lu", (unsigned long)k);
    return this->queues[k];
}

void QosLsaPacket::setQueuesArraySize(size_t newSize)
{
    handleChange();
    QueueInfo *queues2 = (newSize==0) ? nullptr : new QueueInfo[newSize];
    size_t minSize = queues_arraysize < newSize ? queues_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        queues2[i] = this->queues[i];
    delete [] this->queues;
    this->queues = queues2;
    queues_arraysize = newSize;
}

void QosLsaPacket::setQueues(size_t k, const QueueInfo& queues)
{
    if (k >= queues_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->queues[k] = queues;
}

void QosLsaPacket::insertQueues(size_t k, const QueueInfo& queues)
{
    handleChange();
    if (k > queues_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = queues_arraysize + 1;
    QueueInfo *queues2 = new QueueInfo[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        queues2[i] = this->queues[i];
    queues2[k] = queues;
    for (i = k + 1; i < newSize; i++)
        queues2[i] = this->queues[i-1];
    delete [] this->queues;
    this->queues = queues2;
    queues_arraysize = newSize;
}

void QosLsaPacket::insertQueues(const QueueInfo& queues)
{
    insertQueues(queues_arraysize, queues);
}

void QosLsaPacket::eraseQueues(size_t k)
{
    if (k >= queues_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = queues_arraysize - 1;
    QueueInfo *queues2 = (newSize == 0) ? nullptr : new QueueInfo[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        queues2[i] = this->queues[i];
    for (i = k; i < newSize; i++)
        queues2[i] = this->queues[i+1];
    delete [] this->queues;
    this->queues = queues2;
    queues_arraysize = newSize;
}

class QosLsaPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_sequenceNumber,
        FIELD_linkId,
        FIELD_queues,
    };
  public:
    QosLsaPacketDescriptor();
    virtual ~QosLsaPacketDescriptor();

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

Register_ClassDescriptor(QosLsaPacketDescriptor)

QosLsaPacketDescriptor::QosLsaPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::QosLsaPacket)), "critical::ls::LsPacketBaseId")
{
    propertynames = nullptr;
}

QosLsaPacketDescriptor::~QosLsaPacketDescriptor()
{
    delete[] propertynames;
}

bool QosLsaPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QosLsaPacket *>(obj)!=nullptr;
}

const char **QosLsaPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QosLsaPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QosLsaPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int QosLsaPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_linkId
        FD_ISARRAY | FD_ISCOMPOUND,    // FIELD_queues
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *QosLsaPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sequenceNumber",
        "linkId",
        "queues",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int QosLsaPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sequenceNumber") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "linkId") == 0) return base+1;
    if (fieldName[0] == 'q' && strcmp(fieldName, "queues") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QosLsaPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_sequenceNumber
        "int",    // FIELD_linkId
        "critical::QueueInfo",    // FIELD_queues
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **QosLsaPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *QosLsaPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int QosLsaPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QosLsaPacket *pp = (QosLsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_queues: return pp->getQueuesArraySize();
        default: return 0;
    }
}

const char *QosLsaPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QosLsaPacket *pp = (QosLsaPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QosLsaPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QosLsaPacket *pp = (QosLsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_linkId: return long2string(pp->getLinkId());
        case FIELD_queues: {std::stringstream out; out << pp->getQueues(i); return out.str();}
        default: return "";
    }
}

bool QosLsaPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QosLsaPacket *pp = (QosLsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); return true;
        case FIELD_linkId: pp->setLinkId(string2long(value)); return true;
        default: return false;
    }
}

const char *QosLsaPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_queues: return omnetpp::opp_typename(typeid(QueueInfo));
        default: return nullptr;
    };
}

void *QosLsaPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QosLsaPacket *pp = (QosLsaPacket *)object; (void)pp;
    switch (field) {
        case FIELD_queues: return toVoidPtr(&pp->getQueues(i)); break;
        default: return nullptr;
    }
}

Register_Class(LsEmbedPacket)

LsEmbedPacket::LsEmbedPacket() : ::critical::ls::LsPacketBaseId()
{
    this->setType(LS_EMBED);
    this->setChunkLength(inet::B(81));

}

LsEmbedPacket::LsEmbedPacket(const LsEmbedPacket& other) : ::critical::ls::LsPacketBaseId(other)
{
    copy(other);
}

LsEmbedPacket::~LsEmbedPacket()
{
    delete [] this->path;
}

LsEmbedPacket& LsEmbedPacket::operator=(const LsEmbedPacket& other)
{
    if (this == &other) return *this;
    ::critical::ls::LsPacketBaseId::operator=(other);
    copy(other);
    return *this;
}

void LsEmbedPacket::copy(const LsEmbedPacket& other)
{
    this->flow = other.flow;
    this->hop = other.hop;
    delete [] this->path;
    this->path = (other.path_arraysize==0) ? nullptr : new QueueLevelTopologyLinkEncoding::DecodedLink[other.path_arraysize];
    path_arraysize = other.path_arraysize;
    for (size_t i = 0; i < path_arraysize; i++) {
        this->path[i] = other.path[i];
    }
}

void LsEmbedPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LsPacketBaseId::parsimPack(b);
    doParsimPacking(b,this->flow);
    doParsimPacking(b,this->hop);
    b->pack(path_arraysize);
    doParsimArrayPacking(b,this->path,path_arraysize);
}

void LsEmbedPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LsPacketBaseId::parsimUnpack(b);
    doParsimUnpacking(b,this->flow);
    doParsimUnpacking(b,this->hop);
    delete [] this->path;
    b->unpack(path_arraysize);
    if (path_arraysize == 0) {
        this->path = nullptr;
    } else {
        this->path = new QueueLevelTopologyLinkEncoding::DecodedLink[path_arraysize];
        doParsimArrayUnpacking(b,this->path,path_arraysize);
    }
}

const critical::Flow& LsEmbedPacket::getFlow() const
{
    return this->flow;
}

void LsEmbedPacket::setFlow(const critical::Flow& flow)
{
    handleChange();
    this->flow = flow;
}

uint32_t LsEmbedPacket::getHop() const
{
    return this->hop;
}

void LsEmbedPacket::setHop(uint32_t hop)
{
    handleChange();
    this->hop = hop;
}

size_t LsEmbedPacket::getPathArraySize() const
{
    return path_arraysize;
}

const QueueLevelTopologyLinkEncoding::DecodedLink& LsEmbedPacket::getPath(size_t k) const
{
    if (k >= path_arraysize) throw omnetpp::cRuntimeError("Array of size path_arraysize indexed by %lu", (unsigned long)k);
    return this->path[k];
}

void LsEmbedPacket::setPathArraySize(size_t newSize)
{
    handleChange();
    QueueLevelTopologyLinkEncoding::DecodedLink *path2 = (newSize==0) ? nullptr : new QueueLevelTopologyLinkEncoding::DecodedLink[newSize];
    size_t minSize = path_arraysize < newSize ? path_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        path2[i] = this->path[i];
    delete [] this->path;
    this->path = path2;
    path_arraysize = newSize;
}

void LsEmbedPacket::setPath(size_t k, const QueueLevelTopologyLinkEncoding::DecodedLink& path)
{
    if (k >= path_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->path[k] = path;
}

void LsEmbedPacket::insertPath(size_t k, const QueueLevelTopologyLinkEncoding::DecodedLink& path)
{
    handleChange();
    if (k > path_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = path_arraysize + 1;
    QueueLevelTopologyLinkEncoding::DecodedLink *path2 = new QueueLevelTopologyLinkEncoding::DecodedLink[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        path2[i] = this->path[i];
    path2[k] = path;
    for (i = k + 1; i < newSize; i++)
        path2[i] = this->path[i-1];
    delete [] this->path;
    this->path = path2;
    path_arraysize = newSize;
}

void LsEmbedPacket::insertPath(const QueueLevelTopologyLinkEncoding::DecodedLink& path)
{
    insertPath(path_arraysize, path);
}

void LsEmbedPacket::erasePath(size_t k)
{
    if (k >= path_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = path_arraysize - 1;
    QueueLevelTopologyLinkEncoding::DecodedLink *path2 = (newSize == 0) ? nullptr : new QueueLevelTopologyLinkEncoding::DecodedLink[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        path2[i] = this->path[i];
    for (i = k; i < newSize; i++)
        path2[i] = this->path[i+1];
    delete [] this->path;
    this->path = path2;
    path_arraysize = newSize;
}

class LsEmbedPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_flow,
        FIELD_hop,
        FIELD_path,
    };
  public:
    LsEmbedPacketDescriptor();
    virtual ~LsEmbedPacketDescriptor();

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

Register_ClassDescriptor(LsEmbedPacketDescriptor)

LsEmbedPacketDescriptor::LsEmbedPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LsEmbedPacket)), "critical::ls::LsPacketBaseId")
{
    propertynames = nullptr;
}

LsEmbedPacketDescriptor::~LsEmbedPacketDescriptor()
{
    delete[] propertynames;
}

bool LsEmbedPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LsEmbedPacket *>(obj)!=nullptr;
}

const char **LsEmbedPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LsEmbedPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LsEmbedPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int LsEmbedPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_flow
        FD_ISEDITABLE,    // FIELD_hop
        FD_ISARRAY | FD_ISCOMPOUND,    // FIELD_path
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LsEmbedPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flow",
        "hop",
        "path",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LsEmbedPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'f' && strcmp(fieldName, "flow") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hop") == 0) return base+1;
    if (fieldName[0] == 'p' && strcmp(fieldName, "path") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LsEmbedPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "critical::Flow",    // FIELD_flow
        "uint32_t",    // FIELD_hop
        "critical::ls::QueueLevelTopologyLinkEncoding::DecodedLink",    // FIELD_path
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LsEmbedPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *LsEmbedPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LsEmbedPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LsEmbedPacket *pp = (LsEmbedPacket *)object; (void)pp;
    switch (field) {
        case FIELD_path: return pp->getPathArraySize();
        default: return 0;
    }
}

const char *LsEmbedPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedPacket *pp = (LsEmbedPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LsEmbedPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedPacket *pp = (LsEmbedPacket *)object; (void)pp;
    switch (field) {
        case FIELD_flow: {std::stringstream out; out << pp->getFlow(); return out.str();}
        case FIELD_hop: return ulong2string(pp->getHop());
        case FIELD_path: {std::stringstream out; out << pp->getPath(i); return out.str();}
        default: return "";
    }
}

bool LsEmbedPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LsEmbedPacket *pp = (LsEmbedPacket *)object; (void)pp;
    switch (field) {
        case FIELD_hop: pp->setHop(string2ulong(value)); return true;
        default: return false;
    }
}

const char *LsEmbedPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_flow: return omnetpp::opp_typename(typeid(critical::Flow));
        case FIELD_path: return omnetpp::opp_typename(typeid(QueueLevelTopologyLinkEncoding::DecodedLink));
        default: return nullptr;
    };
}

void *LsEmbedPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedPacket *pp = (LsEmbedPacket *)object; (void)pp;
    switch (field) {
        case FIELD_flow: return toVoidPtr(&pp->getFlow()); break;
        case FIELD_path: return toVoidPtr(&pp->getPath(i)); break;
        default: return nullptr;
    }
}

Register_Class(LsEmbedConfirmPacket)

LsEmbedConfirmPacket::LsEmbedConfirmPacket() : ::critical::ls::LsPacketBase()
{
    this->setType(LS_EMBED_CONFIRM);
    this->setChunkLength(inet::B(37));

}

LsEmbedConfirmPacket::LsEmbedConfirmPacket(const LsEmbedConfirmPacket& other) : ::critical::ls::LsPacketBase(other)
{
    copy(other);
}

LsEmbedConfirmPacket::~LsEmbedConfirmPacket()
{
}

LsEmbedConfirmPacket& LsEmbedConfirmPacket::operator=(const LsEmbedConfirmPacket& other)
{
    if (this == &other) return *this;
    ::critical::ls::LsPacketBase::operator=(other);
    copy(other);
    return *this;
}

void LsEmbedConfirmPacket::copy(const LsEmbedConfirmPacket& other)
{
    this->flow = other.flow;
}

void LsEmbedConfirmPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LsPacketBase::parsimPack(b);
    doParsimPacking(b,this->flow);
}

void LsEmbedConfirmPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LsPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->flow);
}

const critical::FlowId& LsEmbedConfirmPacket::getFlow() const
{
    return this->flow;
}

void LsEmbedConfirmPacket::setFlow(const critical::FlowId& flow)
{
    handleChange();
    this->flow = flow;
}

class LsEmbedConfirmPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_flow,
    };
  public:
    LsEmbedConfirmPacketDescriptor();
    virtual ~LsEmbedConfirmPacketDescriptor();

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

Register_ClassDescriptor(LsEmbedConfirmPacketDescriptor)

LsEmbedConfirmPacketDescriptor::LsEmbedConfirmPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LsEmbedConfirmPacket)), "critical::ls::LsPacketBase")
{
    propertynames = nullptr;
}

LsEmbedConfirmPacketDescriptor::~LsEmbedConfirmPacketDescriptor()
{
    delete[] propertynames;
}

bool LsEmbedConfirmPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LsEmbedConfirmPacket *>(obj)!=nullptr;
}

const char **LsEmbedConfirmPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LsEmbedConfirmPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LsEmbedConfirmPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int LsEmbedConfirmPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *LsEmbedConfirmPacketDescriptor::getFieldName(int field) const
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

int LsEmbedConfirmPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'f' && strcmp(fieldName, "flow") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LsEmbedConfirmPacketDescriptor::getFieldTypeString(int field) const
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

const char **LsEmbedConfirmPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *LsEmbedConfirmPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LsEmbedConfirmPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LsEmbedConfirmPacket *pp = (LsEmbedConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LsEmbedConfirmPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedConfirmPacket *pp = (LsEmbedConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LsEmbedConfirmPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedConfirmPacket *pp = (LsEmbedConfirmPacket *)object; (void)pp;
    switch (field) {
        case FIELD_flow: {std::stringstream out; out << pp->getFlow(); return out.str();}
        default: return "";
    }
}

bool LsEmbedConfirmPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LsEmbedConfirmPacket *pp = (LsEmbedConfirmPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *LsEmbedConfirmPacketDescriptor::getFieldStructName(int field) const
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

void *LsEmbedConfirmPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedConfirmPacket *pp = (LsEmbedConfirmPacket *)object; (void)pp;
    switch (field) {
        case FIELD_flow: return toVoidPtr(&pp->getFlow()); break;
        default: return nullptr;
    }
}

Register_Class(LsEmbedFailPacket)

LsEmbedFailPacket::LsEmbedFailPacket() : ::critical::ls::LsPacketBaseId()
{
    this->setType(LS_EMBED_FAIL);
    this->setChunkLength(inet::B(53));

}

LsEmbedFailPacket::LsEmbedFailPacket(const LsEmbedFailPacket& other) : ::critical::ls::LsPacketBaseId(other)
{
    copy(other);
}

LsEmbedFailPacket::~LsEmbedFailPacket()
{
}

LsEmbedFailPacket& LsEmbedFailPacket::operator=(const LsEmbedFailPacket& other)
{
    if (this == &other) return *this;
    ::critical::ls::LsPacketBaseId::operator=(other);
    copy(other);
    return *this;
}

void LsEmbedFailPacket::copy(const LsEmbedFailPacket& other)
{
    this->flow = other.flow;
}

void LsEmbedFailPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::critical::ls::LsPacketBaseId::parsimPack(b);
    doParsimPacking(b,this->flow);
}

void LsEmbedFailPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::critical::ls::LsPacketBaseId::parsimUnpack(b);
    doParsimUnpacking(b,this->flow);
}

const critical::FlowId& LsEmbedFailPacket::getFlow() const
{
    return this->flow;
}

void LsEmbedFailPacket::setFlow(const critical::FlowId& flow)
{
    handleChange();
    this->flow = flow;
}

class LsEmbedFailPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_flow,
    };
  public:
    LsEmbedFailPacketDescriptor();
    virtual ~LsEmbedFailPacketDescriptor();

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

Register_ClassDescriptor(LsEmbedFailPacketDescriptor)

LsEmbedFailPacketDescriptor::LsEmbedFailPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(critical::ls::LsEmbedFailPacket)), "critical::ls::LsPacketBaseId")
{
    propertynames = nullptr;
}

LsEmbedFailPacketDescriptor::~LsEmbedFailPacketDescriptor()
{
    delete[] propertynames;
}

bool LsEmbedFailPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LsEmbedFailPacket *>(obj)!=nullptr;
}

const char **LsEmbedFailPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LsEmbedFailPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LsEmbedFailPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int LsEmbedFailPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *LsEmbedFailPacketDescriptor::getFieldName(int field) const
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

int LsEmbedFailPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'f' && strcmp(fieldName, "flow") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LsEmbedFailPacketDescriptor::getFieldTypeString(int field) const
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

const char **LsEmbedFailPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *LsEmbedFailPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int LsEmbedFailPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LsEmbedFailPacket *pp = (LsEmbedFailPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LsEmbedFailPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedFailPacket *pp = (LsEmbedFailPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LsEmbedFailPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedFailPacket *pp = (LsEmbedFailPacket *)object; (void)pp;
    switch (field) {
        case FIELD_flow: {std::stringstream out; out << pp->getFlow(); return out.str();}
        default: return "";
    }
}

bool LsEmbedFailPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LsEmbedFailPacket *pp = (LsEmbedFailPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *LsEmbedFailPacketDescriptor::getFieldStructName(int field) const
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

void *LsEmbedFailPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LsEmbedFailPacket *pp = (LsEmbedFailPacket *)object; (void)pp;
    switch (field) {
        case FIELD_flow: return toVoidPtr(&pp->getFlow()); break;
        default: return nullptr;
    }
}

} // namespace ls
} // namespace critical

