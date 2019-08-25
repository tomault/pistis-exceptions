#ifndef __PISTIS__EXCEPTIONS__ENDOFSTREAM_HPP__
#define __PISTIS__EXCEPTIONS__ENDOFSTREAM_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class EndOfStream : public PistisException {
    public:
      EndOfStream(const ExceptionOrigin& origin);
      EndOfStream(const std::string& details, const ExceptionOrigin& origin);
    };
    
  }
}
#endif
