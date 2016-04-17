#ifndef __PISTIS__EXCEPTIONS__ITERATORRANGEERROR_HPP__
#define __PISTIS__EXCEPTIONS__ITERATORRANGEERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class IteratorRangeError : public PistisException {
    public:
      IteratorRangeError(const ExceptionOrigin& origin);
      IteratorRangeError(const std::string& details,
			 const ExceptionOrigin& origin);

      virtual IteratorRangeError* duplicate() const;
    };

  }
}
#endif
