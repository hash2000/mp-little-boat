#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Menu_Window.H>
#include <memory>

namespace FltkExt::Controls
{
	enum class PickerResult
	{
		Initialized,
		OnOk,
		OnCancel,
	};

	class Picker : public Fl_Menu_Window
	{
	private:
		Picker();

	public:

		static Picker* GetInstance();

	public:
		PickerResult Do(Fl_Widget* owner, int cx, int cy);

		void EndPicker();

	protected:

		int handle(int event) override;

	private:

		PickerResult _result = PickerResult::Initialized;

	};
}
