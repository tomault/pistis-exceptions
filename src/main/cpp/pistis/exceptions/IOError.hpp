#ifndef __PISTIS__EXCEPTIONS__IOERROR_HPP__
#define __PISTIS__EXCEPTIONS__IOERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class IOError : public PistisException {
    public:
      IOError(const std::string& details, const ExceptionOrigin& origin);
      IOError(const std::string& details,
	      const PistisException& cause,
	      const ExceptionOrigin& origin);
      IOError(const IOError&)= default;
      IOError(IOError&&)= default;

      virtual IOError* duplicate() const;

      static std::string detailsFromSystemError(const std::string& msg,
						int errorCode);
      static std::string detailsFromSystemError(const std::string& msg);
      static IOError fromSystemError(const std::string& msg, int errorCode,
				     const ExceptionOrigin& origin);
      static IOError fromSystemError(const std::string& msg, int errorCode,
				     const PistisException& cause,
				     const ExceptionOrigin& origin);
      static IOError fromSystemError(const std::string& msg,
				     const ExceptionOrigin& origin);
      static IOError fromSystemError(const std::string& msg,
				     const PistisException& cause,
				     const ExceptionOrigin& origin);
    };

  }
}

#endif
