// ProgramTransformation.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

#include "LogFile.h"

int main()
{
  {
    LogFile dummy;
    try{
        dummy.write( "Writing from main" );
    }
    catch(exception & e){
          cerr << e.what() << endl;
    }
  }
  
  {
    try{
        LogFile logFile( "Exceptions.log" );
        logFile.write( "Writing from main" );
        logFile.write( "Writing from main - again" );
    }
    catch(exception & e){
          cerr << e.what() << endl;
    }
  }
}
