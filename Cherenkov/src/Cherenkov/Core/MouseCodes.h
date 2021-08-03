#pragma once

namespace Cherenkov {
	using MouseCode = uint16_t;
	namespace Mouse {
		enum : MouseCode {
			Button_1 = 0,
			Button_2 = 1,
			Button_3 = 2,
			Button_4 = 3,
			Button_5 = 4,
			Button_6 = 5,
			Button_7 = 6,
			Button_8 = 7,
			Button_Last = Button_8,
			Button_Left = Button_1,
			Button_Right = Button_2,
			Button_Middle = Button_3
		};
	}
}

//To be implemented
//#define CK_MOD_SHIFT           0x0001
//#define CK_MOD_CONTROL         0x0002
//#define CK_MOD_ALT             0x0004
//#define CK_MOD_SUPER           0x0008
//#define CK_MOD_CAPS_LOCK       0x0010
//#define CK_MOD_NUM_LOCK        0x0020

//#define CK_JOYSTICK_1             0
//#define CK_JOYSTICK_2             1
//#define CK_JOYSTICK_3             2
//#define CK_JOYSTICK_4             3
//#define CK_JOYSTICK_5             4
//#define CK_JOYSTICK_6             5
//#define CK_JOYSTICK_7             6
//#define CK_JOYSTICK_8             7
//#define CK_JOYSTICK_9             8
//#define CK_JOYSTICK_10            9
//#define CK_JOYSTICK_11            10
//#define CK_JOYSTICK_12            11
//#define CK_JOYSTICK_13            12
//#define CK_JOYSTICK_14            13
//#define CK_JOYSTICK_15            14
//#define CK_JOYSTICK_16            15
//#define CK_JOYSTICK_LAST          CK_JOYSTICK_16

//#define CK_GAMEPAD_BUTTON_A               0
//#define CK_GAMEPAD_BUTTON_B               1
//#define CK_GAMEPAD_BUTTON_X               2
//#define CK_GAMEPAD_BUTTON_Y               3
//#define CK_GAMEPAD_BUTTON_LEFT_BUMPER     4
//#define CK_GAMEPAD_BUTTON_RIGHT_BUMPER    5
//#define CK_GAMEPAD_BUTTON_BACK            6
//#define CK_GAMEPAD_BUTTON_START           7
//#define CK_GAMEPAD_BUTTON_GUIDE           8
//#define CK_GAMEPAD_BUTTON_LEFT_THUMB      9
//#define CK_GAMEPAD_BUTTON_RIGHT_THUMB     10
//#define CK_GAMEPAD_BUTTON_DPAD_UP         11
//#define CK_GAMEPAD_BUTTON_DPAD_RIGHT      12
//#define CK_GAMEPAD_BUTTON_DPAD_DOWN       13
//#define CK_GAMEPAD_BUTTON_DPAD_LEFT       14
//#define CK_GAMEPAD_BUTTON_LAST            CK_GAMEPAD_BUTTON_DPAD_LEFT
//
//#define CK_GAMEPAD_BUTTON_CROSS       CK_GAMEPAD_BUTTON_A
//#define CK_GAMEPAD_BUTTON_CIRCLE      CK_GAMEPAD_BUTTON_B
//#define CK_GAMEPAD_BUTTON_SQUARE      CK_GAMEPAD_BUTTON_X
//#define CK_GAMEPAD_BUTTON_TRIANGLE    CK_GAMEPAD_BUTTON_Y
