#include "esphome.h"

class NullOutputComponent : public Component, public FloatOutput {
 public:
  void write_state(float state) override {
    // Do nothing
  }
};