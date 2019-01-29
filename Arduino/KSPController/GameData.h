#pragma once

static const char DEG = 0xDF;
static const char METERS[] = "m";
static const char KILOMETERS[] = "Km";
static const char MEGAMETERS[] = "Mm";

struct GameData {

  char vessel[11];
  
  float ap;
  float pe;
  float in;

  char body[11];

  float alt;
  float vS;
  float hS;

};

static const uint8_t GD_SIZE = sizeof(GameData);
