
#if !defined(_LOGFILE_H_)
#define _LOGFILE_H_

#include <string>
#include "LogFileException.h"

class LogFile
{
public:
	bool write( const std::string& data );
	bool init( const std::string& logfilename );
    
	LogFile();
	explicit LogFile( const std::string& logfilename );
	~LogFile();

private:
	std::string logfilename_;
	bool internalWrite( const std::string& data );
};

#endif // !defined(AFX_LOGFILE_H__4A9D73D5_7588_11D3_A2E2_00104BB8D7A4__INCLUDED_)
