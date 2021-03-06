#pragma once

/* include files */
// general includes
#include <stdlib.h>
#include <math.h>
// networking
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
// libraries
#include <oslib/oslib.h>
// custom includes
#include "PNGLoad.h"
#include "SegmentDisplay.h"
#include "ETS2_Telemetry.h"
#include "NetPackets.h"

/* testing */
//#define NO_SERVER
void getTestTelemetryData(TETS2_Telemetry &data);

/* definitions */
// general
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define printf pspDebugScreenPrintf
#define MAX_AP_CONFIGS_TO_SCAN 50
#define RECV_BUFFER_SIZE (4 * 1024)
#define PACKET_BUFFER_SIZE (16 * 1024)
#define PACKET_PAYLOAD_BUFFER_SIZE (4 * 1024)
// textures
#define TEXTURE_COUNT 30
#define TEXTURE_FRAMEBUFFER 0
#define TEXTURE_BACKGROUND 1
#define TEXTURE_PAUSE 2
#define TEXTURE_HOR_NUMB_BAR 3
#define TEXTURE_VER_NUMB_BAR 4
#define TEXTURE_SPEED_CIRCLE 5
#define TEXTURE_CRUISE_CONTROL 6
#define TEXTURE_TACHOMETER 7
#define TEXTURE_TACHOMETER_NEEDLE 8
#define TEXTURE_LEFT_BLINKER_LIGHT 9
#define TEXTURE_RIGHT_BLINKER_LIGHT 10
#define TEXTURE_LOW_BEAM_LIGHT 11
#define TEXTURE_HIGH_BEAM_LIGHT 12
#define TEXTURE_LOW_FUEL_LIGHT 13
#define TEXTURE_RETARDER_LIGHT 14
#define TEXTURE_PARKING_BRAKE_LIGHT 15
#define TEXTURE_BATTERY_LOW_LIGHT 16
#define TEXTURE_AIR_WARNING_LIGHT 17
#define TEXTURE_AIR_EMERGENCY_LIGHT 18
#define TEXTURE_BEACON_LIGHT 19
#define TEXTURE_SERVICE_LIGHT 20
#define TEXTURE_WATER_TEMPERATURE_LIGHT 21
#define TEXTURE_OIL_PRESSURE_LIGHT 22
#define TEXTURE_FUEL_BAR 23
#define TEXTURE_TRAILER 24
#define TEXTURE_NAVIGATION 25
#define TEXTURE_WATER_ICON 26
#define TEXTURE_OIL_ICON 27
#define TEXTURE_FUEL_ICON 28
#define TEXTURE_AIR_ICON 29
// fonts
#define FONT_COUNT 2
#define FONT_DEFAULT 0
#define FONT_LIGHT 1
// packets
#define PACKET_NAME 1
#define PACKET_TELDATA 2

/* constants */
// general
extern const char* CLIENT_NAME;
// file constants (general)
extern const char* FILE_SERVER_ADDRESS;
extern const char* FILE_GEAR_MAP;
// file constants (textures)
extern const char* FILE_BACKGROUND;
extern const char* FILE_PAUSE;
extern const char* FILE_HOR_NUMB_BAR;
extern const char* FILE_VER_NUMB_BAR;
extern const char* FILE_VER_SPEED_CIRCLE;
extern const char* FILE_CRUISE_CONTROL;
extern const char* FILE_TACHOMETER;
extern const char* FILE_NEEDLE;
extern const char* FILE_LEFT_BLINKER_LIGHT;
extern const char* FILE_RIGHT_BLINKER_LIGHT;
extern const char* FILE_LOW_BEAM_LIGHT;
extern const char* FILE_HIGH_BEAM_LIGHT;
extern const char* FILE_LOW_FUEL_LIGHT;
extern const char* FILE_RETARDER_LIGHT;
extern const char* FILE_PARKING_BRAKE_LIGHT;
extern const char* FILE_BATTERY_LOW_LIGHT;
extern const char* FILE_AIR_WARNING_LIGHT;
extern const char* FILE_AIR_EMERGENCY_LIGHT;
extern const char* FILE_BEACON_LIGHT;
extern const char* FILE_SERVICE_LIGHT;
extern const char* FILE_WATER_TEMPERATURE_LIGHT;
extern const char* FILE_OIL_PRESSURE_LIGHT;
extern const char* FILE_FUEL_BAR;
extern const char* FILE_TRAILER;
extern const char* FILE_NAVIGATION;
extern const char* FILE_WATER_ICON;
extern const char* FILE_OIL_ICON;
extern const char* FILE_FUEL_ICON;
extern const char* FILE_AIR_ICON;
// file constants (fonts)
extern const char* FILE_FONT_DEFAULT;
extern const char* FILE_FONT_LIGHT;

/* variables */
// textures
OSL_IMAGE* textures[TEXTURE_COUNT];
// fonts
OSL_FONT* fonts[FONT_COUNT];
// dashboard
SegmentDisplay* speedometer;
int selectedTab;
bool useMetric;
// for connecting
char serverIP[16];
uint16_t serverPort;
int connection;
// forward gear map
char gears[32][10];
// threads
SceUID telemetryThreadID;
// telemetry data
SceUID telDataSemaphore;
uint8_t telDataBlock[TEL_DATA_BLOCK_SIZE];

/* methods */
int main();
void sleepS(unsigned int seconds);
void sleepMS(unsigned int milliseconds);
void connect();
void disconnect();
void waitForTelemetryThread();
void setName();
bool isConnectedToAP();
bool isTelemetryThreadRunning();
void getTelemetryData(TETS2_Telemetry &data, bool &telemetryPresent, bool &changed);
// rendering
void renderDashboard(TETS2_Telemetry &data, bool connected, bool telemetryPresent);
// initialization
int initOSLib();
void resetHandles();
void getServerAddress();
void getGearMap();
void createFramebuffer();
bool loadTexture(unsigned int textureId, const char* filename, bool swizzle = true);
void loadTextures();
void loadFonts();
void loadDashboard();
void initNetworking();
void connectToAccessPoint();
// finalization
void disconnectFromAccessPoint();
void freeResources();
void terminate(bool waitForUser);
// threads
int telemetryThread(SceSize args, void *argp);
// miscellaneous
// ...