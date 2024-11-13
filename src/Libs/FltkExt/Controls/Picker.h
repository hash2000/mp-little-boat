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
	public:
		Picker();

		virtual ~Picker();

	public:
		PickerResult PoolDown(Fl_Widget* owner, int cw, int ch);

		void EndPicker();

		bool IsEventInside();

		void SetPickerResult(PickerResult result);

	protected:

		int handle(int event) override;

	private:

		PickerResult _result = PickerResult::Initialized;

	};
}
