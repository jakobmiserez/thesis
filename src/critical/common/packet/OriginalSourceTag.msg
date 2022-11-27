import inet.common.INETDefs;
import inet.common.TagBase;

import inet.networklayer.contract.ipv6.Ipv6Address;

namespace critical;

class OriginalSourceTag extends inet::TagBase {
  inet::Ipv6Address originalSourceAddress;
  int originalInterface = -1;
}