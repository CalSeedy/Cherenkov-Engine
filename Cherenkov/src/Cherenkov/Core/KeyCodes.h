#pragma once

namespace Cherenkov {
	typedef enum class KeyCode : uint16_t {
		Space					= 32,
		Apostrophe				= 39, /* ' */
		Comma					= 44, /* , */
		Minus					= 45, /* - */
		Period					= 46, /* . */
		Slash					= 47, /* / */

		Zero					= 48,
		One						= 49,
		Two						= 50,
		Three					= 51,
		Four					= 52,
		Five					= 53,
		Six						= 54,
		Seven					= 55,
		Eight					= 56,
		Nine					= 57,

		Semicolon				= 59,
		Equal					= 61,

		A						= 65,
		B						= 66,
		C						= 67,
		D						= 68,
		E						= 69,
		F						= 70,
		G						= 71,
		H						= 72,
		I						= 73,
		J						= 74,
		K						= 75,
		L						= 76,
		M						= 77,
		N						= 78,
		O						= 79,
		P						= 80,
		Q						= 81,
		R						= 82,
		S						= 83,
		T						= 84,
		U						= 85,
		V						= 86,
		W						= 87,
		X						= 88,
		Y						= 89,
		Z						= 90,
		Left_Bracket			= 91, /* [ */
		Backslash				= 92, /* \ */
		Right_Bracket			= 93, /* ] */
		Grave					= 96, /* ` */
		World_1					= 161, /* non-US #1 */
		World_2					= 162, /* non-US #2 */
		
		Escape					= 256,
		Enter					= 257,
		Tab						= 258,
		Backspace				= 259,
		Insert					= 260,
		Delete					= 261,
		Right					= 262,
		Left					= 263,
		Down					= 264,
		Up						= 265,
		Page_Up					= 266,
		Page_Down				= 267,
		Home					= 268,
		End						= 269,
		Caps_Lock				= 280,
		Scroll_Lock				= 281,
		Num_Lock				= 282,
		Print_Screen			= 283,
		Pause					= 284,
		F1						= 290,
		F2						= 291,
		F3						= 292,
		F4						= 293,
		F5						= 294,
		F6						= 295,
		F7						= 296,
		F8						= 297,
		F9						= 298,
		F10						= 299,
		F11						= 300,
		F12						= 301,
		F13						= 302,
		F14						= 303,
		F15						= 304,
		F16						= 305,
		F17						= 306,
		F18						= 307,
		F19						= 308,
		F20						= 309,
		F21						= 310,
		F22						= 311,
		F23						= 312,
		F24						= 313,
		F25						= 314,
		KP_0					= 320,
		KP_1					= 321,
		KP_2					= 322,
		KP_3					= 323,
		KP_4					= 324,
		KP_5					= 325,
		KP_6					= 326,
		KP_7					= 327,
		KP_8					= 328,
		KP_9					= 329,
		KP_Decimal				= 330,
		KP_Divide				= 331,
		KP_Multiply				= 332,
		KP_Subtract				= 333,
		KP_Add					= 334,
		KP_Enter				= 335,
		KP_Equal				= 336,
		Left_Shift				= 340,
		Left_Control			= 341,
		Left_Alt				= 342,
		Left_Super				= 343,
		Right_Shift				= 344,
		Right_Control			= 345,
		Right_Alt				= 346,
		Right_Super				= 347,
		Menu					= 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

//GLFW keys from glfw3.h
/* Printable keys */
#define CK_KEY_SPACE			::Cherenkov::Key::Space
#define CK_KEY_APOSTROPHE       ::Cherenkov::Key::Apostrophe
#define CK_KEY_COMMA            ::Cherenkov::Key::Comma
#define CK_KEY_MINUS            ::Cherenkov::Key::Minus
#define CK_KEY_PERIOD           ::Cherenkov::Key::Period
#define CK_KEY_SLASH            ::Cherenkov::Key::Slash
#define CK_KEY_0                ::Cherenkov::Key::Zero
#define CK_KEY_1                ::Cherenkov::Key::One
#define CK_KEY_2                ::Cherenkov::Key::Two
#define CK_KEY_3                ::Cherenkov::Key::Three
#define CK_KEY_4                ::Cherenkov::Key::Four
#define CK_KEY_5                ::Cherenkov::Key::Five
#define CK_KEY_6                ::Cherenkov::Key::Six
#define CK_KEY_7                ::Cherenkov::Key::Seven
#define CK_KEY_8                ::Cherenkov::Key::Eight
#define CK_KEY_9                ::Cherenkov::Key::Nine
#define CK_KEY_SEMICOLON        ::Cherenkov::Key::Semicolon
#define CK_KEY_EQUAL            ::Cherenkov::Key::Equal
#define CK_KEY_A                ::Cherenkov::Key::A
#define CK_KEY_B                ::Cherenkov::Key::B 
#define CK_KEY_C                ::Cherenkov::Key::C
#define CK_KEY_D                ::Cherenkov::Key::D 
#define CK_KEY_E                ::Cherenkov::Key::E 
#define CK_KEY_F                ::Cherenkov::Key::F
#define CK_KEY_G                ::Cherenkov::Key::G 
#define CK_KEY_H                ::Cherenkov::Key::H 
#define CK_KEY_I                ::Cherenkov::Key::I 
#define CK_KEY_J                ::Cherenkov::Key::J
#define CK_KEY_K                ::Cherenkov::Key::K
#define CK_KEY_L                ::Cherenkov::Key::L
#define CK_KEY_M                ::Cherenkov::Key::M 
#define CK_KEY_N                ::Cherenkov::Key::N
#define CK_KEY_O                ::Cherenkov::Key::O
#define CK_KEY_P                ::Cherenkov::Key::P 
#define CK_KEY_Q                ::Cherenkov::Key::Q
#define CK_KEY_R                ::Cherenkov::Key::R 
#define CK_KEY_S                ::Cherenkov::Key::S 
#define CK_KEY_T                ::Cherenkov::Key::T 
#define CK_KEY_U                ::Cherenkov::Key::U 
#define CK_KEY_V                ::Cherenkov::Key::V 
#define CK_KEY_W                ::Cherenkov::Key::W 
#define CK_KEY_X                ::Cherenkov::Key::X 
#define CK_KEY_Y                ::Cherenkov::Key::Y 
#define CK_KEY_Z                ::Cherenkov::Key::Z 
#define CK_KEY_LEFT_BRACKET     ::Cherenkov::Key::Left_Bracket 
#define CK_KEY_BACKSLASH        ::Cherenkov::Key::Backslash
#define CK_KEY_RIGHT_BRACKET    ::Cherenkov::Key::Right_Bracket
#define CK_KEY_GRAVE_ACCENT     ::Cherenkov::Key::Grave
#define CK_KEY_WORLD_1          ::Cherenkov::Key::World_1
#define CK_KEY_WORLD_2          ::Cherenkov::Key::World_2
								
/* Function keys */				
#define CK_KEY_ESCAPE           ::Cherenkov::Key::Escape
#define CK_KEY_ENTER            ::Cherenkov::Key::Enter
#define CK_KEY_TAB              ::Cherenkov::Key::Tab
#define CK_KEY_BACKSPACE        ::Cherenkov::Key::Backspace
#define CK_KEY_INSERT           ::Cherenkov::Key::Insert
#define CK_KEY_DELETE           ::Cherenkov::Key::Delete
#define CK_KEY_RIGHT            ::Cherenkov::Key::Right
#define CK_KEY_LEFT             ::Cherenkov::Key::Left
#define CK_KEY_DOWN             ::Cherenkov::Key::Down
#define CK_KEY_UP               ::Cherenkov::Key::Up
#define CK_KEY_PAGE_UP          ::Cherenkov::Key::Page_Up
#define CK_KEY_PAGE_DOWN        ::Cherenkov::Key::Page_Down
#define CK_KEY_HOME             ::Cherenkov::Key::Home
#define CK_KEY_END              ::Cherenkov::Key::End
#define CK_KEY_CAPS_LOCK        ::Cherenkov::Key::Caps_Lock
#define CK_KEY_SCROLL_LOCK      ::Cherenkov::Key::Scroll_Lock
#define CK_KEY_NUM_LOCK         ::Cherenkov::Key::Num_Lock
#define CK_KEY_PRINT_SCREEN     ::Cherenkov::Key::Print_Screen
#define CK_KEY_PAUSE            ::Cherenkov::Key::Pause
#define CK_KEY_F1               ::Cherenkov::Key::F1
#define CK_KEY_F2               ::Cherenkov::Key::F2
#define CK_KEY_F3               ::Cherenkov::Key::F3  
#define CK_KEY_F4               ::Cherenkov::Key::F4  
#define CK_KEY_F5               ::Cherenkov::Key::F5  
#define CK_KEY_F6               ::Cherenkov::Key::F6  
#define CK_KEY_F7               ::Cherenkov::Key::F7  
#define CK_KEY_F8               ::Cherenkov::Key::F8  
#define CK_KEY_F9               ::Cherenkov::Key::F9  
#define CK_KEY_F10              ::Cherenkov::Key::F10  
#define CK_KEY_F11              ::Cherenkov::Key::F11  
#define CK_KEY_F12              ::Cherenkov::Key::F12  
#define CK_KEY_F13              ::Cherenkov::Key::F13  
#define CK_KEY_F14              ::Cherenkov::Key::F14  
#define CK_KEY_F15              ::Cherenkov::Key::F15  
#define CK_KEY_F16              ::Cherenkov::Key::F16  
#define CK_KEY_F17              ::Cherenkov::Key::F17  
#define CK_KEY_F18              ::Cherenkov::Key::F18  
#define CK_KEY_F19              ::Cherenkov::Key::F19  
#define CK_KEY_F20              ::Cherenkov::Key::F20  
#define CK_KEY_F21              ::Cherenkov::Key::F21  
#define CK_KEY_F22              ::Cherenkov::Key::F22  
#define CK_KEY_F23              ::Cherenkov::Key::F23  
#define CK_KEY_F24              ::Cherenkov::Key::F24 
#define CK_KEY_F25              ::Cherenkov::Key::F25 
#define CK_KEY_KP_0             ::Cherenkov::Key::KP_0 
#define CK_KEY_KP_1             ::Cherenkov::Key::KP_1  
#define CK_KEY_KP_2             ::Cherenkov::Key::KP_2  
#define CK_KEY_KP_3             ::Cherenkov::Key::KP_3  
#define CK_KEY_KP_4             ::Cherenkov::Key::KP_4  
#define CK_KEY_KP_5             ::Cherenkov::Key::KP_5  
#define CK_KEY_KP_6             ::Cherenkov::Key::KP_6  
#define CK_KEY_KP_7             ::Cherenkov::Key::KP_7  
#define CK_KEY_KP_8             ::Cherenkov::Key::KP_8  
#define CK_KEY_KP_9             ::Cherenkov::Key::KP_9  
#define CK_KEY_KP_DECIMAL       ::Cherenkov::Key::KP_Decimal  
#define CK_KEY_KP_DIVIDE        ::Cherenkov::Key::KP_Divide  
#define CK_KEY_KP_MULTIPLY      ::Cherenkov::Key::KP_Multiply  
#define CK_KEY_KP_SUBTRACT      ::Cherenkov::Key::KP_Subtract  
#define CK_KEY_KP_ADD           ::Cherenkov::Key::KP_Add  
#define CK_KEY_KP_ENTER         ::Cherenkov::Key::KP_Enter 
#define CK_KEY_KP_EQUAL         ::Cherenkov::Key::KP_Equal  
#define CK_KEY_LEFT_SHIFT       ::Cherenkov::Key::Left_Shift  
#define CK_KEY_LEFT_CONTROL     ::Cherenkov::Key::Left_Control  
#define CK_KEY_LEFT_ALT         ::Cherenkov::Key::Left_Alt  
#define CK_KEY_LEFT_SUPER       ::Cherenkov::Key::Left_Super  
#define CK_KEY_RIGHT_SHIFT      ::Cherenkov::Key::Right_Shift  
#define CK_KEY_RIGHT_CONTROL    ::Cherenkov::Key::Right_Control  
#define CK_KEY_RIGHT_ALT        ::Cherenkov::Key::Right_Alt  
#define CK_KEY_RIGHT_SUPER      ::Cherenkov::Key::Right_Super  
#define CK_KEY_MENU             ::Cherenkov::Key::Menu
