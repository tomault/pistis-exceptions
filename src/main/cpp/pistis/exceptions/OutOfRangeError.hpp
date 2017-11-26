#ifndef __PISTIS__EXCEPTIONS__OUTOFRANGEERROR_HPP__
#define __PISTIS__EXCEPTIONS__OUTOFRANGEERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class OutOfRangeError : public PistisException {
    public:
      OutOfRangeError(const std::string& details);
      OutOfRangeError(const std::string& details,
		      const ExceptionOrigin& origin);
      virtual ~OutOfRangeError() noexcept;

      virtual OutOfRangeError* duplicate() const;

      static OutOfRangeError of(const std::string& what);
      static OutOfRangeError of(const std::string& what,
				const ExceptionOrigin& origin);
      static OutOfRangeError of(const std::string& what,
				const std::string& details);
      static OutOfRangeError of(const std::string& what,
				const std::string& details,
				const ExceptionOrigin& origin);
    };

  }
}

#endif
