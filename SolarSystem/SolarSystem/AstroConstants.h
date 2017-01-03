#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

const float SWEET_SPOT = 2.0f;


const float EARTH = 1.50f * SWEET_SPOT;
const float SUN = EARTH * 109.3f;
const float MOON = EARTH * 0.2727f;

const float MERCURY = EARTH * 0.3829f;
const float VENUS = EARTH * 0.9499f;
const float MARS = EARTH * 0.5320f;

const float JUPITER = EARTH * 10.97f;
const float GANYMEDE = EARTH * 0.4135f;
const float CALLISTO = EARTH * 0.3783f;
const float IO = EARTH * 0.2859f;
const float EUROPA = EARTH * 0.2450f;

const float SATURN = EARTH * 9.140f;
const float TITAN = EARTH * 0.4043f;
const float RHEA = EARTH * 0.1199f;
const float IAPETUS = EARTH * 0.1153f;
const float DIONE = EARTH * 0.0881f;
const float TETHYS = EARTH * 0.0834f;

const float URANUS = EARTH * 3.981f;
const float TITANIA = EARTH * 0.1237f;
const float OBERON = EARTH * 0.1195f;
const float UMBRIEL = EARTH * 0.0918f;
const float ARIEL = EARTH * 0.0909f;

const float NEPTUNE = EARTH * 3.865f;
const float TRITON = EARTH * 0.2124f;

const float PLUTO = EARTH * 0.186f;
const float CHARON = EARTH * 0.0951f;

const float STEP = ((SUN / 2.0f) + SATURN) * SWEET_SPOT;

