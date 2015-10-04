/**
 * @file hid.h
 * @brief HID service.
 */
#pragma once

//See also: http://3dbrew.org/wiki/HID_Services http://3dbrew.org/wiki/HID_Shared_Memory

typedef enum
{
	KEY_A       = BIT(0),
	KEY_B       = BIT(1),
	KEY_SELECT  = BIT(2),
	KEY_START   = BIT(3),
	KEY_DRIGHT  = BIT(4),
	KEY_DLEFT   = BIT(5),
	KEY_DUP     = BIT(6),
	KEY_DDOWN   = BIT(7),
	KEY_R       = BIT(8),
	KEY_L       = BIT(9),
	KEY_X       = BIT(10),
	KEY_Y       = BIT(11),
	KEY_ZL      = BIT(14),      ///< ZL (new 3DS only)
	KEY_ZR      = BIT(15),      ///< ZR (new 3DS only)
	KEY_TOUCH   = BIT(20),      ///< Not actually provided by HID
	KEY_CSTICK_RIGHT = BIT(24), ///< c-stick right (new 3DS only)
	KEY_CSTICK_LEFT  = BIT(25), ///< c-stick left (new 3DS only)
	KEY_CSTICK_UP    = BIT(26), ///< c-stick up (new 3DS only)
	KEY_CSTICK_DOWN  = BIT(27), ///< c-stick down (new 3DS only)
	KEY_CPAD_RIGHT = BIT(28),   ///< circle pad right
	KEY_CPAD_LEFT  = BIT(29),   ///< circle pad left
	KEY_CPAD_UP    = BIT(30),   ///< circle pad up
	KEY_CPAD_DOWN  = BIT(31),   ///< circle pad down

	// Generic catch-all directions
	KEY_UP    = KEY_DUP    | KEY_CPAD_UP,
	KEY_DOWN  = KEY_DDOWN  | KEY_CPAD_DOWN,
	KEY_LEFT  = KEY_DLEFT  | KEY_CPAD_LEFT,
	KEY_RIGHT = KEY_DRIGHT | KEY_CPAD_RIGHT,
} PAD_KEY;

typedef struct
{
	u16 px, py;
} touchPosition;

typedef struct
{
	s16 dx, dy;
} circlePosition;

typedef struct
{
	s16 x;
	s16 y;
	s16 z;
} accelVector;

typedef struct
{
	s16 x; ///< roll
	s16 z; ///< yaw
	s16 y; ///< pitch
} angularRate;

typedef enum
{
	HIDEVENT_PAD0 = 0, ///< "Event signaled by HID-module, when the sharedmem+0(PAD/circle-pad)/+0xA8(touch-screen) region was updated."
	HIDEVENT_PAD1,     ///< "Event signaled by HID-module, when the sharedmem+0(PAD/circle-pad)/+0xA8(touch-screen) region was updated."
	HIDEVENT_Accel,    ///< "Event signaled by HID-module, when the sharedmem accelerometer state was updated."
	HIDEVENT_Gyro,     ///< "Event signaled by HID-module, when the sharedmem gyroscope state was updated."
	HIDEVENT_DebugPad, ///< "Event signaled by HID-module, when the sharedmem DebugPad state was updated."

	HIDEVENT_MAX,      ///< used to know how many events there are
} HID_Event;

extern Handle hidMemHandle;
extern vu32* hidSharedMem;

Result hidInit(void);
void hidExit(void);

void hidScanInput(void);
u32 hidKeysHeld(void);
u32 hidKeysDown(void);
u32 hidKeysUp(void);
void hidTouchRead(touchPosition* pos);
void hidCircleRead(circlePosition* pos);
void hidAccelRead(accelVector* vector);
void hidGyroRead(angularRate* rate);

void hidWaitForEvent(HID_Event id, bool nextEvent);

// libnds compatibility defines
#define scanKeys   hidScanInput
#define keysHeld   hidKeysHeld
#define keysDown   hidKeysDown
#define keysUp     hidKeysUp
#define touchRead  hidTouchRead
#define circleRead hidCircleRead

Result HIDUSER_GetHandles(Handle* outMemHandle, Handle *eventpad0, Handle *eventpad1, Handle *eventaccel, Handle *eventgyro, Handle *eventdebugpad);
Result HIDUSER_EnableAccelerometer(void);
Result HIDUSER_DisableAccelerometer(void);
Result HIDUSER_EnableGyroscope(void);
Result HIDUSER_DisableGyroscope(void);
Result HIDUSER_GetGyroscopeRawToDpsCoefficient(float *coeff);
/**
 * @brief Gets the current volume slider value. (0-63)
 * @param volume Pointer to write the volume slider value to.
 */
Result HIDUSER_GetSoundVolume(u8 *volume);
