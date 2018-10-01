#include <stdexcept>

class LogFileException : public std::runtime_error
{
public:
    enum EState { es_COULD_NOT_OPEN_FILE, es_FILENAME_IS_EMPTY };
    
    explicit LogFileException( EState state , const std::string& str = "" )
    : runtime_error(str), state_( state ){}
    
    EState getState() { return state_; }
private:
    EState state_;
};
