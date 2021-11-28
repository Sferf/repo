#include "string.h"

bool runAllTests() {
  String a = "123";
  String b = "456";
  String c = a + b;

  if (c == a + b) {
    return true;
  } else {
    return false;
  }
}
