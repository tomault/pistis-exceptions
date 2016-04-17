#ifndef __PISTIS__EXCEPTIONS__ILLEGALVALUEERROR_HPP__
#define __PISTIS__EXCEPTIONS__ILLEGALVALUEERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class IllegalValueError : public PistisException {
    public:
      IllegalValueError(const std::string& details,
			const ExceptionOrigin& origin);
      IllegalValueError(const std::string& what,
			const std::string& details,
			const ExceptionOrigin& origin);
      IllegalValueError(const std::string& what,
			const std::string& value,
			const std::string& details,
			const ExceptionOrigin& origin);

      virtual IllegalValueError* duplicate() const;

    private:
      static std::string _createMessage(const std::string& what,
					const std::string& value,
					const std::string& details);
    };

  }
}
#endif
