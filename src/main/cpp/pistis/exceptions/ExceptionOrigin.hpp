#ifndef __PISTIS__EXCEPTIONS__EXCEPTIONORIGIN_HPP__
#define __PISTIS__EXCEPTIONS__EXCEPTIONORIGIN_HPP__

#include <iostream>
#include <string>

namespace pistis {
  namespace exceptions {

    /** @brief Describes where an exception was thrown from */
    class ExceptionOrigin {
    public:
      ExceptionOrigin();
      ExceptionOrigin(const std::string& signature,
		      const std::string& filename, int line);
      ExceptionOrigin(std::string&& signature, std::string&& name, int line);
      ExceptionOrigin(const ExceptionOrigin& other) = default;
      ExceptionOrigin(ExceptionOrigin&& other) = default;

      bool empty() const { return _sig.empty() && _filename.empty(); }
      const std::string& sig() const { return _sig; }
      const std::string& filename() const { return _filename; }
      int line() const { return _line; }

      ExceptionOrigin& operator=(const ExceptionOrigin& other) = default;
      ExceptionOrigin& operator=(ExceptionOrigin&& other) = default;

      bool operator==(const ExceptionOrigin& other) const;
      bool operator!=(const ExceptionOrigin& other) const;

    private:
      std::string _sig;
      std::string _filename;
      int _line;
    };

    std::ostream& operator<<(std::ostream& out, const ExceptionOrigin& o);

  }
}

#define PISTIS_EX_HERE pistis::exceptions::ExceptionOrigin(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif
