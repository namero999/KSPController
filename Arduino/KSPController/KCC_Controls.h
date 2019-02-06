#pragma once

class KCC_Controls {

  private:
  int asd = 1;
    static const int SCALE = 100;
    static const int DEADZONE = 5;
    int adjust(int val);

  public:
    void read();

};

extern KCC_Controls _CTRL;
