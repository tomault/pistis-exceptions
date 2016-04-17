#ifndef __PISTIS__EXCEPTIONS__STACKFRAME_HPP__
#define __PISTIS__EXCEPTIONS__STACKFRAME_HPP__

#include <iostream>
#include <string>
#include <vector>

namespace pistis {
  namespace exceptions {

    class StackFrame {
    public:
      StackFrame(const std::string& functionSignature, const void* address,
		 const std::string& module, const void* functionStart,
		 const void* functionEnd);

      bool hasSignature() const { return !_sig.empty(); }
      bool hasModule() const { return !_module.empty(); }
      bool hasFunctionStart() const { return _fnStart != nullptr; }
      bool hasFunctionEnd() const { return _fnEnd != nullptr; }

      const std::string& signature() const { return _sig; }
      const void* address() const { return _address; }
      const std::string& module() const { return _module; }
      const void* functionStart() const { return _fnStart; }
      const void* functionEnd() const { return _fnEnd; }

      static std::vector<StackFrame> trace(size_t skip=0,
					   size_t maxFrames=100);

      bool operator==(const StackFrame& other) const;
      bool operator!=(const StackFrame& other) const;

    private:
      std::string _sig;     ///< Signature of function at this frame
      const void* _address; ///< Address of PC in this frame
      std::string _module; ///< Library or executable that contains the function
      const void* _fnStart; ///< Function start
      const void* _fnEnd;   ///< Function end
    };

    std::ostream& operator<<(std::ostream& out, const StackFrame& frame);

  }
}
    
#endif

