//
// Generated file, do not edit! Created by nedtool 5.6 from critical/protocols/ls/packets/LsPackets.msg.
//

#ifndef __CRITICAL__LS_LSPACKETS_M_H
#define __CRITICAL__LS_LSPACKETS_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif


namespace critical {
namespace ls {

class LsPacketBase;
class LsPacketBaseId;
class LsHelloPacket;
class LinkStateNetworkEntry;
class LinkStateNeighborEntry;
class LsaPacket;
class QosLsaPacket;
class LsEmbedPacket;
class LsEmbedConfirmPacket;
class LsEmbedFailPacket;
} // namespace ls
} // namespace critical

#include "critical/common/packet/CriticalPacketBase_m.h" // import critical.common.packet.CriticalPacketBase

#include "inet/networklayer/contract/ipv6/Ipv6Address_m.h" // import inet.networklayer.contract.ipv6.Ipv6Address

// cplusplus {{
  #include "critical/protocols/ls/topology/QueueLevelTopologyLinkEncoding.h"
// }}


namespace critical {
namespace ls {

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:15</tt> by nedtool.
 * <pre>
 * class LsPacketBase extends CriticalPacketBase
 * {
 * }
 * </pre>
 */
class LsPacketBase : public ::critical::CriticalPacketBase
{
  protected:

  private:
    void copy(const LsPacketBase& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LsPacketBase&);

  public:
    LsPacketBase();
    LsPacketBase(const LsPacketBase& other);
    virtual ~LsPacketBase();
    LsPacketBase& operator=(const LsPacketBase& other);
    virtual LsPacketBase *dup() const override {return new LsPacketBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LsPacketBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LsPacketBase& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:19</tt> by nedtool.
 * <pre>
 * class LsPacketBaseId extends LsPacketBase
 * {
 *     inet::Ipv6Address routerId;  // 17 B
 * }
 * </pre>
 */
class LsPacketBaseId : public ::critical::ls::LsPacketBase
{
  protected:
    inet::Ipv6Address routerId;

  private:
    void copy(const LsPacketBaseId& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LsPacketBaseId&);

  public:
    LsPacketBaseId();
    LsPacketBaseId(const LsPacketBaseId& other);
    virtual ~LsPacketBaseId();
    LsPacketBaseId& operator=(const LsPacketBaseId& other);
    virtual LsPacketBaseId *dup() const override {return new LsPacketBaseId(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const inet::Ipv6Address& getRouterId() const;
    virtual inet::Ipv6Address& getRouterIdForUpdate() { handleChange();return const_cast<inet::Ipv6Address&>(const_cast<LsPacketBaseId*>(this)->getRouterId());}
    virtual void setRouterId(const inet::Ipv6Address& routerId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LsPacketBaseId& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LsPacketBaseId& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:23</tt> by nedtool.
 * <pre>
 * class LsHelloPacket extends LsPacketBaseId
 * {
 *     type = LS_HELLO;  // 17 bytes
 * 
 *     chunkLength = inet::B(17);
 * }
 * </pre>
 */
class LsHelloPacket : public ::critical::ls::LsPacketBaseId
{
  protected:

  private:
    void copy(const LsHelloPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LsHelloPacket&);

  public:
    LsHelloPacket();
    LsHelloPacket(const LsHelloPacket& other);
    virtual ~LsHelloPacket();
    LsHelloPacket& operator=(const LsHelloPacket& other);
    virtual LsHelloPacket *dup() const override {return new LsHelloPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LsHelloPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LsHelloPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:30</tt> by nedtool.
 * <pre>
 * class LinkStateNetworkEntry extends inet::FieldsChunk
 * {
 *     inet::Ipv6Address network;  // 16 bytes 
 *     uint8_t prefixLength;       // 1 byte
 *     uint8_t numQueues;          // 1 byte
 *     int linkId;                 // 2 bytes 
 * 
 *     chunkLength = inet::B(20);
 * }
 * </pre>
 */
class LinkStateNetworkEntry : public ::inet::FieldsChunk
{
  protected:
    inet::Ipv6Address network;
    uint8_t prefixLength = 0;
    uint8_t numQueues = 0;
    int linkId = 0;

  private:
    void copy(const LinkStateNetworkEntry& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LinkStateNetworkEntry&);

  public:
    LinkStateNetworkEntry();
    LinkStateNetworkEntry(const LinkStateNetworkEntry& other);
    virtual ~LinkStateNetworkEntry();
    LinkStateNetworkEntry& operator=(const LinkStateNetworkEntry& other);
    virtual LinkStateNetworkEntry *dup() const override {return new LinkStateNetworkEntry(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const inet::Ipv6Address& getNetwork() const;
    virtual inet::Ipv6Address& getNetworkForUpdate() { handleChange();return const_cast<inet::Ipv6Address&>(const_cast<LinkStateNetworkEntry*>(this)->getNetwork());}
    virtual void setNetwork(const inet::Ipv6Address& network);
    virtual uint8_t getPrefixLength() const;
    virtual void setPrefixLength(uint8_t prefixLength);
    virtual uint8_t getNumQueues() const;
    virtual void setNumQueues(uint8_t numQueues);
    virtual int getLinkId() const;
    virtual void setLinkId(int linkId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LinkStateNetworkEntry& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LinkStateNetworkEntry& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:39</tt> by nedtool.
 * <pre>
 * class LinkStateNeighborEntry extends LinkStateNetworkEntry
 * {
 *     inet::Ipv6Address neighborId; // 16 bytes 
 *     uint8_t cost = 1; // 1 byte
 * 
 *     uint64_t bw;    // 8 bytes
 *     uint64_t delay; // 8 bytes 
 * 
 *     chunkLength = inet::B(53);
 * }
 * </pre>
 */
class LinkStateNeighborEntry : public ::critical::ls::LinkStateNetworkEntry
{
  protected:
    inet::Ipv6Address neighborId;
    uint8_t cost = 1;
    uint64_t bw = 0;
    uint64_t delay = 0;

  private:
    void copy(const LinkStateNeighborEntry& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LinkStateNeighborEntry&);

  public:
    LinkStateNeighborEntry();
    LinkStateNeighborEntry(const LinkStateNeighborEntry& other);
    virtual ~LinkStateNeighborEntry();
    LinkStateNeighborEntry& operator=(const LinkStateNeighborEntry& other);
    virtual LinkStateNeighborEntry *dup() const override {return new LinkStateNeighborEntry(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const inet::Ipv6Address& getNeighborId() const;
    virtual inet::Ipv6Address& getNeighborIdForUpdate() { handleChange();return const_cast<inet::Ipv6Address&>(const_cast<LinkStateNeighborEntry*>(this)->getNeighborId());}
    virtual void setNeighborId(const inet::Ipv6Address& neighborId);
    virtual uint8_t getCost() const;
    virtual void setCost(uint8_t cost);
    virtual uint64_t getBw() const;
    virtual void setBw(uint64_t bw);
    virtual uint64_t getDelay() const;
    virtual void setDelay(uint64_t delay);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LinkStateNeighborEntry& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LinkStateNeighborEntry& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:51</tt> by nedtool.
 * <pre>
 * class LsaPacket extends LsPacketBaseId
 * {
 *     type = LS_LSA;                        // 17 bytes 
 * 
 *     uint8_t networkEntriesCount;              // 1 byte 
 *     uint32_t sequenceNumber;                  // 4 byte
 *     LinkStateNetworkEntry networkEntries[];   // length * 20B
 *     LinkStateNeighborEntry neighborEntries[]; // length * 53B 
 * 
 *     chunkLength = inet::B(22); // DONT FORGET TO ADD  x * 20B + y * 53B
 * }
 * </pre>
 */
class LsaPacket : public ::critical::ls::LsPacketBaseId
{
  protected:
    uint8_t networkEntriesCount = 0;
    uint32_t sequenceNumber = 0;
    LinkStateNetworkEntry *networkEntries = nullptr;
    size_t networkEntries_arraysize = 0;
    LinkStateNeighborEntry *neighborEntries = nullptr;
    size_t neighborEntries_arraysize = 0;

  private:
    void copy(const LsaPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LsaPacket&);

  public:
    LsaPacket();
    LsaPacket(const LsaPacket& other);
    virtual ~LsaPacket();
    LsaPacket& operator=(const LsaPacket& other);
    virtual LsaPacket *dup() const override {return new LsaPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual uint8_t getNetworkEntriesCount() const;
    virtual void setNetworkEntriesCount(uint8_t networkEntriesCount);
    virtual uint32_t getSequenceNumber() const;
    virtual void setSequenceNumber(uint32_t sequenceNumber);
    virtual void setNetworkEntriesArraySize(size_t size);
    virtual size_t getNetworkEntriesArraySize() const;
    virtual const LinkStateNetworkEntry& getNetworkEntries(size_t k) const;
    virtual LinkStateNetworkEntry& getNetworkEntriesForUpdate(size_t k) { handleChange();return const_cast<LinkStateNetworkEntry&>(const_cast<LsaPacket*>(this)->getNetworkEntries(k));}
    virtual void setNetworkEntries(size_t k, const LinkStateNetworkEntry& networkEntries);
    virtual void insertNetworkEntries(const LinkStateNetworkEntry& networkEntries);
    virtual void insertNetworkEntries(size_t k, const LinkStateNetworkEntry& networkEntries);
    virtual void eraseNetworkEntries(size_t k);
    virtual void setNeighborEntriesArraySize(size_t size);
    virtual size_t getNeighborEntriesArraySize() const;
    virtual const LinkStateNeighborEntry& getNeighborEntries(size_t k) const;
    virtual LinkStateNeighborEntry& getNeighborEntriesForUpdate(size_t k) { handleChange();return const_cast<LinkStateNeighborEntry&>(const_cast<LsaPacket*>(this)->getNeighborEntries(k));}
    virtual void setNeighborEntries(size_t k, const LinkStateNeighborEntry& neighborEntries);
    virtual void insertNeighborEntries(const LinkStateNeighborEntry& neighborEntries);
    virtual void insertNeighborEntries(size_t k, const LinkStateNeighborEntry& neighborEntries);
    virtual void eraseNeighborEntries(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LsaPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LsaPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:62</tt> by nedtool.
 * <pre>
 * class QosLsaPacket extends LsPacketBaseId
 * {
 *     type = LS_QOS_LSA;    // 17 bytes 
 *     uint32_t sequenceNumber;  // 4 bytes
 * 
 *     int linkId;               // 2 bytes 
 * 
 *     QueueInfo queues[];       // 16B * length
 * 
 *     chunkLength = inet::B(23); // DONT FORGET TO ADD  16B * length
 * }
 * </pre>
 */
class QosLsaPacket : public ::critical::ls::LsPacketBaseId
{
  protected:
    uint32_t sequenceNumber = 0;
    int linkId = 0;
    QueueInfo *queues = nullptr;
    size_t queues_arraysize = 0;

  private:
    void copy(const QosLsaPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const QosLsaPacket&);

  public:
    QosLsaPacket();
    QosLsaPacket(const QosLsaPacket& other);
    virtual ~QosLsaPacket();
    QosLsaPacket& operator=(const QosLsaPacket& other);
    virtual QosLsaPacket *dup() const override {return new QosLsaPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual uint32_t getSequenceNumber() const;
    virtual void setSequenceNumber(uint32_t sequenceNumber);
    virtual int getLinkId() const;
    virtual void setLinkId(int linkId);
    virtual void setQueuesArraySize(size_t size);
    virtual size_t getQueuesArraySize() const;
    virtual const QueueInfo& getQueues(size_t k) const;
    virtual QueueInfo& getQueuesForUpdate(size_t k) { handleChange();return const_cast<QueueInfo&>(const_cast<QosLsaPacket*>(this)->getQueues(k));}
    virtual void setQueues(size_t k, const QueueInfo& queues);
    virtual void insertQueues(const QueueInfo& queues);
    virtual void insertQueues(size_t k, const QueueInfo& queues);
    virtual void eraseQueues(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const QosLsaPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, QosLsaPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:73</tt> by nedtool.
 * <pre>
 * class LsEmbedPacket extends LsPacketBaseId
 * {
 *     type = LS_EMBED;      // 17B
 * 
 *     critical::Flow flow;  // 60 B
 *     uint32_t hop;         // 4B
 *     QueueLevelTopologyLinkEncoding::DecodedLink path[];  // 4 B * length
 * 
 *     chunkLength = inet::B(81); // DONT FORGET TO ADD 4B * length
 * }
 * </pre>
 */
class LsEmbedPacket : public ::critical::ls::LsPacketBaseId
{
  protected:
    critical::Flow flow;
    uint32_t hop = 0;
    QueueLevelTopologyLinkEncoding::DecodedLink *path = nullptr;
    size_t path_arraysize = 0;

  private:
    void copy(const LsEmbedPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LsEmbedPacket&);

  public:
    LsEmbedPacket();
    LsEmbedPacket(const LsEmbedPacket& other);
    virtual ~LsEmbedPacket();
    LsEmbedPacket& operator=(const LsEmbedPacket& other);
    virtual LsEmbedPacket *dup() const override {return new LsEmbedPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const critical::Flow& getFlow() const;
    virtual critical::Flow& getFlowForUpdate() { handleChange();return const_cast<critical::Flow&>(const_cast<LsEmbedPacket*>(this)->getFlow());}
    virtual void setFlow(const critical::Flow& flow);
    virtual uint32_t getHop() const;
    virtual void setHop(uint32_t hop);
    virtual void setPathArraySize(size_t size);
    virtual size_t getPathArraySize() const;
    virtual const QueueLevelTopologyLinkEncoding::DecodedLink& getPath(size_t k) const;
    virtual QueueLevelTopologyLinkEncoding::DecodedLink& getPathForUpdate(size_t k) { handleChange();return const_cast<QueueLevelTopologyLinkEncoding::DecodedLink&>(const_cast<LsEmbedPacket*>(this)->getPath(k));}
    virtual void setPath(size_t k, const QueueLevelTopologyLinkEncoding::DecodedLink& path);
    virtual void insertPath(const QueueLevelTopologyLinkEncoding::DecodedLink& path);
    virtual void insertPath(size_t k, const QueueLevelTopologyLinkEncoding::DecodedLink& path);
    virtual void erasePath(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LsEmbedPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LsEmbedPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:83</tt> by nedtool.
 * <pre>
 * class LsEmbedConfirmPacket extends LsPacketBase
 * {
 *     type = LS_EMBED_CONFIRM; // 1B 
 * 
 *     critical::FlowId flow; // 36 B 
 * 
 *     chunkLength = inet::B(37);
 * }
 * </pre>
 */
class LsEmbedConfirmPacket : public ::critical::ls::LsPacketBase
{
  protected:
    critical::FlowId flow;

  private:
    void copy(const LsEmbedConfirmPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LsEmbedConfirmPacket&);

  public:
    LsEmbedConfirmPacket();
    LsEmbedConfirmPacket(const LsEmbedConfirmPacket& other);
    virtual ~LsEmbedConfirmPacket();
    LsEmbedConfirmPacket& operator=(const LsEmbedConfirmPacket& other);
    virtual LsEmbedConfirmPacket *dup() const override {return new LsEmbedConfirmPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const critical::FlowId& getFlow() const;
    virtual critical::FlowId& getFlowForUpdate() { handleChange();return const_cast<critical::FlowId&>(const_cast<LsEmbedConfirmPacket*>(this)->getFlow());}
    virtual void setFlow(const critical::FlowId& flow);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LsEmbedConfirmPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LsEmbedConfirmPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>critical/protocols/ls/packets/LsPackets.msg:91</tt> by nedtool.
 * <pre>
 * class LsEmbedFailPacket extends LsPacketBaseId
 * {
 *     type = LS_EMBED_FAIL; // 17 B 
 * 
 *     critical::FlowId flow; // 36 B 
 * 
 *     chunkLength = inet::B(53);
 * }
 * </pre>
 */
class LsEmbedFailPacket : public ::critical::ls::LsPacketBaseId
{
  protected:
    critical::FlowId flow;

  private:
    void copy(const LsEmbedFailPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LsEmbedFailPacket&);

  public:
    LsEmbedFailPacket();
    LsEmbedFailPacket(const LsEmbedFailPacket& other);
    virtual ~LsEmbedFailPacket();
    LsEmbedFailPacket& operator=(const LsEmbedFailPacket& other);
    virtual LsEmbedFailPacket *dup() const override {return new LsEmbedFailPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const critical::FlowId& getFlow() const;
    virtual critical::FlowId& getFlowForUpdate() { handleChange();return const_cast<critical::FlowId&>(const_cast<LsEmbedFailPacket*>(this)->getFlow());}
    virtual void setFlow(const critical::FlowId& flow);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LsEmbedFailPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LsEmbedFailPacket& obj) {obj.parsimUnpack(b);}

} // namespace ls
} // namespace critical

#endif // ifndef __CRITICAL__LS_LSPACKETS_M_H

