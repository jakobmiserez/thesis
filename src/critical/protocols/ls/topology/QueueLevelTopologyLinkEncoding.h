#ifndef _CRITICAL_LS_QUEUELEVELTOPOLOGYLINKENCODING_H
#define _CRITICAL_LS_QUEUELEVELTOPOLOGYLINKENCODING_H

namespace critical {

namespace ls {

class QueueLevelTopologyLinkEncoding {
  public:
    typedef int EncodedLink;

    struct DecodedLink {
      int linkId;
      int queue;
    };

  public:
    static DecodedLink decodeLink(EncodedLink link) {
      int linkId = link / 16;
      int queue = link % 16;

      return { linkId, queue };
    };

    static int getLinkId(EncodedLink link) {
      return link / 16;
    };

    static EncodedLink encodeLink(DecodedLink link) {
      return link.linkId * 16 + link.queue;
    };

    static EncodedLink encodeLink(int linkId, int queue) {
      return encodeLink({linkId, queue});
    };
};

}

}


#endif 