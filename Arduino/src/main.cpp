#include <Arduino.h>
#include "LedButton.h"
#include "Switch.h"
#include "LimitSwitch.h"
#include "PlanetSelectionSubsystem.h"
#include "PowerSubsystem.h"
#include "LaunchSubsystem.h"
#include "DataSubsystem.h"
#include "NavigationSubsystem.h"
#include "ButtonMatrixSubsystem.h"
#include "AsteroidSubsystem.h"
#include "PlaybackSubsystem.h"

// ------Parameters------

// LED Buttons
// Power
constexpr uint8_t power1_led = 51;
constexpr uint8_t power1_but = 52;

constexpr uint8_t power2_led = 36;
constexpr uint8_t power2_but = 44;

// Medbay

constexpr uint8_t medbay1_led = A3;
constexpr uint8_t medbay1_but = 65;

constexpr uint8_t medbay2_led = 29;
constexpr uint8_t medbay2_but = 37;

constexpr uint8_t medbay3_led = 4;
constexpr uint8_t medbay3_but = 3;

// Asteroid
constexpr uint8_t asteroid1_led = 34;
constexpr uint8_t asteroid1_but = 42;

constexpr uint8_t asteroid2_led = 7;
constexpr uint8_t asteroid2_but = 50;

constexpr uint8_t asteroid3_led = A13;
constexpr uint8_t asteroid3_but = 68;

// Launch
constexpr uint8_t launch_led = 53;
constexpr uint8_t launch_but = 45;

// Data
constexpr uint8_t data1_led = 43;
constexpr uint8_t data1_but = 35;

constexpr uint8_t data2_led = 28;
constexpr uint8_t data2_but = 27;

// Thruster
constexpr uint8_t thrust_up_led = A8;
constexpr uint8_t thrust_up_but = 54;

constexpr uint8_t thrust_down_led = A12;
constexpr uint8_t thrust_down_but = 58;

// Matrix
constexpr uint8_t matrix11_led = 8;
constexpr uint8_t matrix11_but = 2;

constexpr uint8_t matrix12_led = 48;
constexpr uint8_t matrix12_but = 5;

constexpr uint8_t matrix13_led = 10;
constexpr uint8_t matrix13_but = 69;

constexpr uint8_t matrix14_led = A7;
constexpr uint8_t matrix14_but = 11;

constexpr uint8_t matrix21_led = 30;
constexpr uint8_t matrix21_but = 47;

constexpr uint8_t matrix22_led = 32;
constexpr uint8_t matrix22_but = 22;

constexpr uint8_t matrix23_led = 25;
constexpr uint8_t matrix23_but = 9;

constexpr uint8_t matrix24_led = 46;
constexpr uint8_t matrix24_but = 33;

constexpr uint8_t matrix31_led = A6;
constexpr uint8_t matrix31_but = 38;

constexpr uint8_t matrix32_led = 31;
constexpr uint8_t matrix32_but = 23;

constexpr uint8_t matrix33_led = 40;
constexpr uint8_t matrix33_but = 24;

constexpr uint8_t matrix34_led = A5;
constexpr uint8_t matrix34_but = 39;

// Switches
constexpr uint8_t mass_switching_bit0_pin = 16;
constexpr uint8_t mass_switching_bit1_pin = 17;
constexpr uint8_t mass_switching_bit2_pin = 19;

// Limit Switches
constexpr uint8_t power_sw1_pin = 41;
constexpr uint8_t power_sw2_pin = 49;
constexpr uint8_t power_sw3_pin = 6;
constexpr uint8_t power_sw4_pin = 26;
constexpr uint8_t power_sw5_pin = 12;

// Joystick
constexpr uint8_t x_positive_pin = 55;
constexpr uint8_t x_negative_pin = 63;
constexpr uint8_t y_positive_pin = 56;
constexpr uint8_t y_negative_pin = 64;

// Volt Dial
constexpr uint8_t volt_dial_pin = 13;

// Displays
constexpr uint8_t data_display_addr = 0xE2;
constexpr uint8_t launch_display_addr = 0xE0;


// ------Classes------

// Mass Switching
PlanetSelectionSubsystem planet_selection_subsystem = PlanetSelectionSubsystem();

// Power Subsystem
PowerSubsystem power_subsystem = PowerSubsystem();

// Launch Subsystem
LaunchSubsystem launch_subsystem = LaunchSubsystem();

// Data Subsystem
DataSubsystem data_subsystem = DataSubsystem();

// Navigation Subsystem
NavigationSubsystem navigation_subsystem = NavigationSubsystem();

// Button Matrix Subsystem
ButtonMatrixSubsystem button_matrix_subsystem = ButtonMatrixSubsystem();

// Asteroid Subsystem
AsteroidSubsystem asteroid_subsystem = AsteroidSubsystem();

// Playback Subsystem
PlaybackSubsystem playback_subsystem = PlaybackSubsystem();


// ----------OTHER VARIABLES---------------

// -------Function Declarations-------
void begin();
void update();

// -------Main Loop------

void setup() {
  Serial.begin(115200);
  begin();
}

void loop() {
  update();
}

// -------Begin-------

void begin(){
  delay(1000);
  // Power Subsystem
  power_subsystem.begin(volt_dial_pin, power_sw1_pin, power_sw2_pin, power_sw3_pin, power_sw4_pin, power_sw5_pin, power2_but, power2_led, power1_but, power1_led);
  // Launch Subsystem
  launch_subsystem.begin(launch_display_addr, launch_led, launch_but);
  // Data Subsystem
  data_subsystem.begin(data_display_addr, data1_led, data1_but, data2_led, data2_but);
  // Navigation Subsystem
  navigation_subsystem.begin(thrust_up_led, thrust_up_but, thrust_down_led, thrust_down_but, x_positive_pin, x_negative_pin, y_positive_pin, y_negative_pin);
  // Button Matrix Subsystem
  button_matrix_subsystem.begin(matrix11_led, matrix11_but, matrix12_led, matrix12_but, matrix13_led, matrix13_but, matrix14_led, matrix14_but, matrix21_led, matrix21_but, matrix22_led, matrix22_but, matrix23_led, matrix23_but, matrix24_led, matrix24_but, matrix31_led, matrix31_but, matrix32_led, matrix32_but, matrix33_led, matrix33_but, matrix34_led, matrix34_but);
  // Asteroid Subsystem
  asteroid_subsystem.begin(asteroid1_led, asteroid1_but, asteroid2_led, asteroid2_but, asteroid3_led, asteroid3_but);
  // Playback Subsystem
  playback_subsystem.begin(medbay1_led, medbay1_but, medbay2_led, medbay2_but, medbay3_led, medbay3_but);
  // Planet Selection Subsystem
  planet_selection_subsystem.begin(mass_switching_bit0_pin, mass_switching_bit1_pin, mass_switching_bit2_pin);
}

// --------Update-------

void update(){
  // Power Subsystem
  power_subsystem.update();
  // Launch Subsystem
  launch_subsystem.update();
  // Data Subsystem
  data_subsystem.update();
  // Navigation Subsystem
  navigation_subsystem.update();
  // Button Matrix Subsystem
  button_matrix_subsystem.update();
  // Asteroid Subsystem
  asteroid_subsystem.update();
  // Playback Subsystem
  playback_subsystem.update();
  // Planet Selection Subsystem
  planet_selection_subsystem.update();
}