//
// Generated file, do not edit! Created by nedtool 5.6 from critical/common/packet/CriticalPacketBase.msg.
//

#ifndef __CRITICAL_CRITICALPACKETBASE_M_H
#define __CRITICAL_CRITICALPACKETBASE_M_H

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

class CriticalPacketBase;
struct QueueInfo;
} // namespace critical

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

// cplusplus {{
  #include "critical/flows/Flow.h"
// }}


namespace critical {

/**
 * Enum generated from <tt>critical/common/packet/CriticalPacketBase.msg:19</tt> by nedtool.
 * <pre>
 * enum PacketType
 * {
 *     PROBE_PROBE = 1;
 *     PROBE_PRUNE = 2;
 *     PROBE_CONFIRM = 3;
 *     PROBE_FREE = 4;
 *     PROBE_FREE_FAILURE = 5;
 * 
 *     LS_HELLO = 11;
 *     LS_LSA = 12;
 *     LS_QOS_LSA = 13;
 *     LS_EMBED = 14;
 *     LS_EMBED_CONFIRM = 15;
 *     LS_EMBED_FAIL = 16;
 * }
 * </pre>
 */
enum PacketType {
    PROBE_PROBE = 1,
    PROBE_PRUNE = 2,
    PROBE_CONFIRM = 3,
    PROBE_FREE = 4,
    PROBE_FREE_FAILURE = 5,
    LS_HELLO = 11,
    LS_LSA = 12,
    LS_QOS_LSA = 13,
    LS_EMBED = 14,
    LS_EMBED_CONFIRM = 15,
    LS_EMBED_FAIL = 16
};

/**
 * Class generated from <tt>critical/common/packet/CriticalPacketBase.msg:34</tt> by nedtool.
 * <pre>
 * class CriticalPacketBase extends inet::FieldsChunk
 * {
 *     PacketType type = static_cast<PacketType>(-1); // 1 byte 
 * }
 * </pre>
 */
class CriticalPacketBase : public ::inet::FieldsChunk
{
  protected:
    critical::PacketType type = static_cast<PacketType>(-1);

  private:
    void copy(const CriticalPacketBase& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CriticalPacketBase&);

  public:
    CriticalPacketBase();
    CriticalPacketBase(const CriticalPacketBase& other);
    virtual ~CriticalPacketBase();
    CriticalPacketBase& operator=(const CriticalPacketBase& other);
    virtual CriticalPacketBase *dup() const override {return new CriticalPacketBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual critical::PacketType getType() const;
    virtual void setType(critical::PacketType type);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CriticalPacketBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CriticalPacketBase& obj) {obj.parsimUnpack(b);}

/**
 * Struct generated from critical/common/packet/CriticalPacketBase.msg:38 by nedtool.
 */
struct QueueInfo
{
    QueueInfo();
    double burst;
    double rate;
};

// helpers for local use
void __doPacking(omnetpp::cCommBuffer *b, const QueueInfo& a);
void __doUnpacking(omnetpp::cCommBuffer *b, QueueInfo& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const QueueInfo& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, QueueInfo& obj) { __doUnpacking(b, obj); }

} // namespace critical

#endif // ifndef __CRITICAL_CRITICALPACKETBASE_M_H

