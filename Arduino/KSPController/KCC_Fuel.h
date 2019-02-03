#pragma once

class KCC_Fuel {

  private:
    short solid    = -1;
    short liquid   = -1;
    short oxidizer = -1;
    short monoprop = -1;
    short electro  = -1;

  public:
    void update();

};

extern KCC_Fuel _FUEL;
