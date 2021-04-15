#include "mdcore/logger.h"

int main()
{
    mdcore::Logger::Logger logger("omega");
    logger.info("Successfully Built with Dependencies");
    return 0;
}