#ifndef __PISTIS__EXCEPTIONS__ILLEGALSTATEERROR_HPP__
#define __PISTIS__EXCEPTIONS__ILLEGALSTATEERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class IllegalStateError : public PistisException {
    public:
      IllegalStateError(const std::string& details,
			const ExceptionOrigin& origin);
      IllegalStateError(const std::string& details,
			const PistisException& cause,
			const ExceptionOrigin& origin);

      virtual IllegalStateError* duplicate() const;
    };

  }
}
#endif

