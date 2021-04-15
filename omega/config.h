#ifndef __omega__config_h
#define __omega__config_h
#include "mdcore/config.h"

const char* programName = "Omega";
const std::string ownerID = mdcore::readOwnerId(); 
const std::string prefix = mdcore::readPrefix();
#endif