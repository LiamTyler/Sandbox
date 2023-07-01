#include "shared/logger.hpp"

int main( int arc, char** argv )
{
    Logger_Init();
    Logger_AddLogLocation( "stdout", stdout );

    LOG( "Hello world" );

    Logger_Shutdown();
    return 0;
}
