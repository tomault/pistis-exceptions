#ifndef __PISTIS__EXCEPTIONS__PISTISEXCEPTION_HPP__
#define __PISTIS__EXCEPTIONS__PISTISEXCEPTION_HPP__

#include <pistis/exceptions/ExceptionOrigin.hpp>
#include <pistis/exceptions/StackFrame.hpp>
#include <exception>
#include <memory>
#include <string>
#include <vector>

namespace pistis {
  namespace exceptions {

    class PistisException : public std::exception {
    public:
      PistisException();
      PistisException(const std::string& details);
      PistisException(const ExceptionOrigin& origin);
      PistisException(const std::string& details,
		      const ExceptionOrigin& origin);
      PistisException(const std::string& details,
		      const PistisException& cause);
      PistisException(const std::string& details,
		      const PistisException& cause,
		      const ExceptionOrigin& origin);
      PistisException(const PistisException& ex);
      PistisException(PistisException&& other) noexcept;
      virtual ~PistisException() noexcept;

      const std::string& details() const { return _details; }
      const ExceptionOrigin& origin() const { return _origin; }
      const PistisException* cause() const { return _cause.get(); }
      const std::vector<StackFrame>& backtrace() const { return _backtrace; }

      virtual std::ostream& print(std::ostream& out, bool brief=false) const;
      virtual std::string toString(bool brief=false) const;

      virtual PistisException* duplicate() const;
      virtual const char* what() const noexcept;

      PistisException& operator=(const PistisException& other);
      PistisException& operator=(PistisException&& other) noexcept;

    protected:
      virtual void printDetails_(std::ostream& out) const;

    private:
      std::string _details;
      ExceptionOrigin _origin;
      std::unique_ptr<PistisException> _cause;
      std::vector<StackFrame> _backtrace;
      mutable std::unique_ptr<char[]> _msg;

      static const std::string& defaultDetails();
    };

    inline std::ostream& operator<<(std::ostream& out,
				    const PistisException& e) {
      return e.print(out);
    }

  }
}
#endif
