#pragma once
#include "FltkAll.h"
#include <initializer_list>
#include <map>
#include <string>
#include <functional>
#include <optional>

enum class Fl_Scheme_Mode {
	default_mode,
	light,
	dark,
	white,
	black,
	red,
	green,
	blue,
};


using namespace std;

namespace {
	auto original_background_color_ = optional<Fl_Color>{};
	auto original_background2_color_ = optional<Fl_Color>{};
	auto original_foreground_color_ = optional<Fl_Color>{};
	auto original_selection_color_ = optional<Fl_Color>{};
	auto scheme_mode_ = Fl_Scheme_Mode::default_mode;

	void init_original_colors() {
		if (!original_background_color_.has_value())
			original_background_color_ = Fl::get_color(FL_BACKGROUND_COLOR);
		if (!original_background2_color_.has_value())
			original_background2_color_ = Fl::get_color(FL_BACKGROUND2_COLOR);
		if (!original_foreground_color_.has_value())
			original_foreground_color_ = Fl::get_color(FL_FOREGROUND_COLOR);
		if (!original_selection_color_.has_value())
			original_selection_color_ = Fl::get_color(FL_SELECTION_COLOR);
	}

	void set_scheme_light_mode() {
#if _WIN32
		Fl::background(240, 240, 240);
		Fl::background2(255, 255, 255);
		Fl::foreground(0, 0, 0);
		Fl::set_color(FL_SELECTION_COLOR, 0, 120, 215);
#elif __APPLE__
		Fl::background(236, 236, 236);
		Fl::background2(255, 255, 255);
		Fl::foreground(0, 0, 0);
		Fl::set_color(FL_SELECTION_COLOR, 0, 98, 225);
#else
		Fl::background(241, 240, 238);
		Fl::background2(255, 255, 255);
		Fl::foreground(0, 0, 0);
		Fl::set_color(FL_SELECTION_COLOR, 53, 100, 228);
#endif
	}

	void set_scheme_dark_mode() {
#if _WIN32
		Fl::background(25, 25, 25);
		Fl::background2(32, 32, 32);
		Fl::foreground(255, 255, 255);
		Fl::set_color(FL_SELECTION_COLOR, 0, 160, 250);
#elif __APPLE__
		Fl::background(50, 50, 50);
		Fl::background2(23, 23, 23);
		Fl::foreground(223, 223, 223);
		Fl::set_color(FL_SELECTION_COLOR, 0, 87, 207);
#else
		Fl::background(51, 51, 51);
		Fl::background2(45, 45, 45);
		Fl::foreground(255, 255, 255);
		Fl::set_color(FL_SELECTION_COLOR, 21, 83, 158);
#endif
	}

	void set_scheme_default_mode() {
		unsigned char r = 0, g = 0, b = 0;
		Fl::get_color(original_background_color_.value(), r, g, b);
		Fl::background(r, g, b);
		Fl::set_color(FL_BACKGROUND2_COLOR, original_background2_color_.value());
		Fl::set_color(FL_FOREGROUND_COLOR, original_foreground_color_.value());
		Fl::set_color(FL_SELECTION_COLOR, original_selection_color_.value());
	}

	void set_scheme_white_mode() {
		Fl::background(248, 248, 255);
		Fl::background2(255, 255, 255);
		Fl::foreground(80, 80, 80);
#if _WIN32
		Fl::set_color(FL_SELECTION_COLOR, 0, 120, 215);
#elif __APPLE__
		Fl::set_color(FL_SELECTION_COLOR, 0, 98, 225);
#else
		Fl::set_color(FL_SELECTION_COLOR, 53, 100, 228);
#endif
	}

	void set_scheme_black_mode() {
		Fl::background(16, 16, 16);
		Fl::background2(0, 0, 0);
		Fl::foreground(120, 120, 120);
#if _WIN32
		Fl::set_color(FL_SELECTION_COLOR, 0, 160, 250);
#elif __APPLE__
		Fl::set_color(FL_SELECTION_COLOR, 0, 87, 207);
#else
		Fl::set_color(FL_SELECTION_COLOR, 21, 83, 158);
#endif
	}

	void set_scheme_red_mode() {
		Fl::background(36, 0, 0);
		Fl::background2(8, 0, 0);
		Fl::foreground(223, 100, 100);
		Fl::set_color(FL_SELECTION_COLOR, 220, 50, 50);
	}

	void set_scheme_green_mode() {
		Fl::background(0, 36, 0);
		Fl::background2(0, 8, 0);
		Fl::foreground(100, 223, 100);
		Fl::set_color(FL_SELECTION_COLOR, 50, 220, 50);
	}

	void set_scheme_blue_mode() {
		Fl::background(0, 0, 64);
		Fl::background2(0, 0, 16);
		Fl::foreground(90, 90, 255);
		Fl::set_color(FL_SELECTION_COLOR, 80, 80, 255);
	}
}

void fl_scheme_mode(Fl_Scheme_Mode scheme_mode) {
	init_original_colors();
	static auto set_modes = map<Fl_Scheme_Mode, std::function<void()>>{
		{Fl_Scheme_Mode::default_mode, set_scheme_default_mode},
		{Fl_Scheme_Mode::dark, set_scheme_dark_mode},
		{Fl_Scheme_Mode::light, set_scheme_light_mode},
		{Fl_Scheme_Mode::white, set_scheme_white_mode},
		{Fl_Scheme_Mode::black, set_scheme_black_mode},
		{Fl_Scheme_Mode::red, set_scheme_red_mode},
		{Fl_Scheme_Mode::green, set_scheme_green_mode},
		{Fl_Scheme_Mode::blue, set_scheme_blue_mode}
	};
	if (scheme_mode_ != scheme_mode) {
		scheme_mode_ = scheme_mode;
		set_modes[scheme_mode_]();
	}
}

Fl_Scheme_Mode fl_scheme_mode() {
	init_original_colors();
	return scheme_mode_;
}



class MainWindowFltkThemes : public Fl_Window
{
public:
	MainWindowFltkThemes() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		resizable(this);

		button1.callback([](Fl_Widget* sender, void* window) {
			fl_message_icon()->box(FL_ROUND_UP_BOX);
			fl_message_icon()->color(fl_rgb_color(0, 0, 255));
			fl_message_icon()->label("i");
			fl_message_icon()->labelcolor(fl_rgb_color(255, 255, 255));
			fl_choice("This is an example of message...", nullptr, fl_ok, nullptr);
			}, this);

		toggle_button1.value(true);
		// For more consistency
		light_button1.color2(FL_SELECTION_COLOR);
		light_button1.value(true);
		radio1.value(true);
		check_button2.value(true);

		box1.align(FL_ALIGN_LEFT | FL_ALIGN_TOP | FL_ALIGN_CLIP | FL_ALIGN_INSIDE);
		box1.box(Fl_Boxtype::FL_FLAT_BOX);

#pragma warning(disable:4566)
		multiline_input1.value("The quick brown fox jumps over the lazy dog.\n"
			"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.\n"
			"0123456789+-*/%~^&|=<>≤≥±÷≠{{[()]}},;:.?¿!¡\n"
			"àçéèêëïî@@°_#§$ù£€æœøπµ©®∞\\\"'\n"
			"\u0400\u0401\u0402\u0403\u0404\u0405\u0406\u0407\u0408\u0409\u040a\u040b\u040c\u040d\u040e\u040f\n"
			"\u0410\u0411\u0412\u0413\u0414\u0415\u0416\u0417\u0418\u0419\u041a\u041b\u041c\u041d\u041e\u041f\n"
			"\u4ea0\u4ea1\u4ea2\u4ea3\u4ea4\u4ea5\u4ea6\u4ea7\u4ea8\u4ea9\u4eaa\u4eab\u4eac\u4ead\u4eae\u4eaf\n"
			"\u4eb0\u4eb1\u4eb2\u4eb3\u4eb4\u4eb5\u4eb6\u4eb7\u4eb8\u4eb9\u4eba\u4ebb\u4ebc\u4ebd\u4ebe\u4ebf\n"
			"\U0001F428");
#pragma warning(default:4566)

		browser1.type(FL_HOLD_BROWSER);
		for (auto item : { "Light red", "Light green", "Light blue", "Yellow", "White", "Dark gray", "Light cyan", "Light magenta", "Red", "Green", "Blue", "Brown", "Light gray", "Black", "Cyan", "Magenta" }) {
			browser1.add(item);
			check_browser1.add(item);
		}
		browser1.select(1);
		check_browser1.checked(1, true);
		check_browser1.checked(4, true);

		slider1.type(FL_HOR_NICE_SLIDER);
		slider1.maximum(100);
		slider1.value(50);
		//slider1.color2(FL_SELECTION_COLOR);
		slider1.callback([](Fl_Widget* sender, void* window) {
			reinterpret_cast<MainWindowFltkThemes*>(window)->progress1.value(dynamic_cast<Fl_Slider*>(sender)->value());
			reinterpret_cast<MainWindowFltkThemes*>(window)->progress1.copy_label((to_string((static_cast<int>(dynamic_cast<Fl_Slider*>(sender)->value()))) + "%").c_str());
			}, this);
		progress1.value(slider1.value());
		progress1.copy_label((to_string((static_cast<int>(slider1.value()))) + "%").c_str());
		// For more consistency
		progress1.color2(FL_SELECTION_COLOR);

		for (auto item : { "basic", "plastic", "gtk+", "gleam" })
			scheme_choice.add(item);
		scheme_choice.value(0);
		scheme_choice.callback([](Fl_Widget* sender, void* window) {
			reinterpret_cast<MainWindowFltkThemes*>(window)->update_theme_and_mode();
			}, this);

		for (auto item : { "default", "light", "dark", "white", "black", "red", "green", "blue" })
			scheme_mode_choice.add(item);
		scheme_mode_choice.value(0);
		scheme_mode_choice.callback([](Fl_Widget* sender, void* window) {
			reinterpret_cast<MainWindowFltkThemes*>(window)->update_theme_and_mode();
			}, this);
	}

protected:
	void resize(int x, int y, int w, int h) override {
		Fl_Window::resize(x, y, w, h);
		tabs.resize(10, 10, w - 20, h - 65);
		buttons_page.resize(10, 30, w - 20, h - 85);
		texts_page.resize(10, 30, w - 20, h - 85);
		browsers_page.resize(10, 30, w - 20, h - 85);
		slider_page.resize(10, 30, w - 20, h - 85);
		scheme_choice.resize(70, h - 35, 80, 25);
		scheme_mode_choice.resize(210, h - 35, 80, 25);
	}

	void draw() override {
		Fl_Window::draw();
		draw_box(Fl_Boxtype::FL_FLAT_BOX, 10, h() - 45, w() - 20, 1, fl_darker(color()));
		draw_box(Fl_Boxtype::FL_FLAT_BOX, 11, h() - 44, w() - 20, 1, fl_lighter(color()));
	}

private:
	void update_theme_and_mode() {
		if (scheme_choice.value() == 1) fl_scheme_mode(Fl_Scheme_Mode::default_mode); // Workaround : with scheme "plastic", window background was not correctly refresh...
		Fl::scheme(scheme_choice.text(scheme_choice.value()));
		static map<string, Fl_Scheme_Mode> scheme_modes = { {"default", Fl_Scheme_Mode::default_mode}, {"light", Fl_Scheme_Mode::light}, {"dark", Fl_Scheme_Mode::dark}, {"white", Fl_Scheme_Mode::white}, {"black", Fl_Scheme_Mode::black}, {"red", Fl_Scheme_Mode::red}, {"green", Fl_Scheme_Mode::green}, {"blue", Fl_Scheme_Mode::blue} };
		fl_scheme_mode(scheme_modes[scheme_mode_choice.text(scheme_mode_choice.value())]);
	}

	Fl_Tabs tabs{ 10, 10, w() - 20,h() - 70 };

	Fl_Group buttons_page{ tabs.x(), tabs.y() + 20, tabs.w(), tabs.h() - 20, "Buttons" };
	Fl_Scroll buttons_scroll{ tabs.x() + 1, tabs.y() + 21, tabs.w() - 2, tabs.h() - 22 };
	Fl_Button button1{ 20, 40, 75, 25, "Message" };
	Fl_Toggle_Button toggle_button1{ 120, 40, 75, 25, "Toggle" };
	Fl_Light_Button light_button1{ 20, 80, 75, 25, "Light" };
	Fl_Return_Button return_button1{ 120, 80, 75, 25, "Return" };
	Fl_Radio_Round_Button radio1{ 20, 120, 90, 25, "Raddio 1" };
	Fl_Radio_Round_Button radio2{ 120, 120, 90, 25, "Raddio 2" };
	Fl_Check_Button check_button1{ 20, 150, 90, 25, "Check 1" };
	Fl_Check_Button check_button2{ 120, 150, 90, 25, "Check 2" };
	Fl_End end_buttons_scroll;
	Fl_End end_buttons_page;

	Fl_Group texts_page{ tabs.x(), tabs.y() + 20, tabs.w(), tabs.h() - 20, "Texts" };
	Fl_Scroll texts_scroll{ tabs.x() + 1, tabs.y() + 21, tabs.w() - 2, tabs.h() - 22 };
	Fl_Box box1{ 20, 40, 300, 25, "The quick brown fox jumps over the lazy dog." };
	Fl_Multiline_Input multiline_input1{ 20, 70, 400, 200 };
	Fl_End end_texts_scroll;
	Fl_End end_texts_page;

	Fl_Group browsers_page{ tabs.x(), tabs.y() + 20, tabs.w(), tabs.h() - 20, "Browsers" };
	Fl_Scroll browsers_scroll{ tabs.x() + 1, tabs.y() + 21, tabs.w() - 2, tabs.h() - 22 };
	Fl_Browser browser1{ 20, 40, 200, 100 };
	Fl_Check_Browser check_browser1{ 20, 160, 200, 100 };
	Fl_End end_browser_scroll;
	Fl_End end_browser_page;

	Fl_Group slider_page{ tabs.x(), tabs.y() + 20, tabs.w(), tabs.h() - 20, "Slider and progress" };
	Fl_Scroll slider_scroll{ tabs.x() + 1, tabs.y() + 21, tabs.w() - 2, tabs.h() - 22 };
	Fl_Hor_Nice_Slider slider1{ 20, 40, 290, 25 };
	Fl_Progress progress1{ 20, 80, 290, 25 };
	Fl_End end_slider_scroll;
	Fl_End end_slider_page;

	Fl_Group valuators_page{ tabs.x(), tabs.y() + 20, tabs.w(), tabs.h() - 20, "Valuators" };
	Fl_Scroll valuators_scroll{ tabs.x() + 1, tabs.y() + 21, tabs.w() - 2, tabs.h() - 22 };
	Fl_Dial dial1{ 20, 40, 75, 75 };
	Fl_Roller roller1{ 45, 130, 25, 100 };
	Fl_End end_valuators_scroll;
	Fl_End end_valuators_page;

	Fl_End end_tabs;

	Fl_Choice scheme_choice{ 70, h() - 35, 80, 25, "Scheme" };
	Fl_Choice scheme_mode_choice{ 210, h() - 35, 80, 25, "Mode" };
};
