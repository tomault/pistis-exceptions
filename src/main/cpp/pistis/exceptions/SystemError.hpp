#ifndef __PISTIS__EXCEPTIONS__SYSTEMERROR_HPP__
#define __PISTIS__EXCEPTIONS__SYSTEMERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class SystemError : public PistisException {
    public:
      SystemError(const std::string& details, const ExceptionOrigin& origin);
      SystemError(const std::string& details,
		  const PistisException& cause,
		  const ExceptionOrigin& origin);
      SystemError(const SystemError&)= default;
      SystemError(SystemError&&)= default;

      virtual SystemError* duplicate() const;

      static std::string detailsFromSystemCode(const std::string& msg,
					       int errorCode);
      static std::string detailsFromSystemCode(const std::string& msg);
      static SystemError fromSystemCode(const std::string& msg, int errorCode,
					const ExceptionOrigin& origin);
      static SystemError fromSystemCode(const std::string& msg, int errorCode,
					const PistisException& cause,
					const ExceptionOrigin& origin);
      static SystemError fromSystemCode(const std::string& msg,
					const ExceptionOrigin& origin);
      static SystemError fromSystemCode(const std::string& msg,
					const PistisException& cause,
					const ExceptionOrigin& origin);
    };

  }
}

#endif
