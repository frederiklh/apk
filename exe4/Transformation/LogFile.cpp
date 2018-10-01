
#include <iostream>
#include <fstream>
using namespace std;

#include "LogFile.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LogFile::LogFile()
{
	cout << "Creating LogFile Object" << endl;
}

LogFile::LogFile( const string& logfilename )
{
	cout << "Creating LogFile Object: " + logfilename << endl;
	init( logfilename );
}

LogFile::~LogFile()
{
	cout << "Deleting LogFile Object" << endl;
}

bool LogFile::init( const string& logfilename )
{
	logfilename_ = logfilename;
	return internalWrite( "" );
}

bool LogFile::write( const string& data )
{
	return internalWrite( data+"\n" );
}

bool LogFile::internalWrite( const string& data )
{
	if( logfilename_ == "" )
		throw LogFileException(LogFileException::es_FILENAME_IS_EMPTY, "LogFile filename is empty");
    
	std::ofstream out;
	out.open( logfilename_.c_str(), std::ofstream::out | std::ofstream::app);
	if( out )
		out << data;
	else
		throw LogFileException(LogFileException::es_COULD_NOT_OPEN_FILE, "Could not open LogFile: " + logfilename_);
}

