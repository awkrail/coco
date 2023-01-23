#include "error.h"

const char *GetErrName(enum Error err)
{
  switch(err) {
    case kSuccess:
      return "kSuccess";
      break;
    
    case kFull:
      return "kFull";
      break;

    case kEmpty:
      return "kEmpty";
      break;

    case kLastOfCode:
      return "kLastOfCode";
      break;

    default:
      return "kLastOfCode";
      break;
  }
}
