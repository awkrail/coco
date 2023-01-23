#pragma once

enum Error {
  kSuccess,
  kFull,
  kEmpty,
  kLastOfCode,
};

const char *GetErrName(enum Error err);
