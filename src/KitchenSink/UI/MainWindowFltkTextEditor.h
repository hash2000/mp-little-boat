#pragma once
#include "FltkAll.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Editor.H>

namespace
{

	// Custom class to demonstrate a specialized text editor
	class MyEditor : public Fl_Text_Editor {

		Fl_Text_Buffer* tbuff;      // text buffer
		Fl_Text_Buffer* sbuff;      // style buffer

		// Modify callback handler
		void ModifyCallback(int pos,        // position of update
			int nInserted,  // number of inserted chars
			int nDeleted,   // number of deleted chars
			int,            // number of restyled chars (unused here)
			const char*) {  // text deleted (unused here)

			// Nothing inserted or deleted?
			if (nInserted == 0 && nDeleted == 0) return;

			// Characters inserted into tbuff?
			//     Insert same number of chars into style buffer..
			//
			if (nInserted > 0) {
				char* style = new char[nInserted + 1];  // temp buffer
				memset(style, 'A', nInserted);          // init style to "A"s
				style[nInserted] = '\0';                // terminate string
				sbuff->insert(pos, style);              // insert "A"s into style buffer
				delete[] style;                         // done with temp buffer..
			}

			// Characters deleted from tbuff?
			//    Delete same number of chars from style buffer..
			//
			if (nDeleted > 0) {
				sbuff->remove(pos, pos + nDeleted);
				return;     // nothing more to do; deleting won't affect our single char coloring
			}

			// Focus on characters inserted
			int start = pos;
			int end = pos + nInserted;
			//DEBUG fprintf(stderr, "add_modify_callback(): start/end=%d/%d, text='%.*s'\n", start, end, (end-start), tbuff->address(start));

			// SIMPLE EXAMPLE:
			//     Color the digits 0-4 in green, 5-9 in red.
			//
			for (int i = start; i < end; i++) {
				unsigned int c = tbuff->char_at(i);
				if (strchr("01234", c)) sbuff->replace(i, i + 1, "B");   // style 'B' (green)
				else if (strchr("56789", c)) sbuff->replace(i, i + 1, "C");   // style 'C' (red)
				else                           sbuff->replace(i, i + 1, "A");   // style 'A' (black)
			}
		}

		static void ModifyCallback_STATIC(int pos,                 // position of update
			int nInserted,           // number of inserted chars
			int nDeleted,            // number of deleted chars
			int nRestyled,           // number of restyled chars
			const char* deletedText, // text deleted
			void* cbarg) {           // callback data
			MyEditor* med = (MyEditor*)cbarg;
			med->ModifyCallback(pos, nInserted, nDeleted, nRestyled, deletedText);
		}

	public:
		MyEditor(int X, int Y, int W, int H) : Fl_Text_Editor(X, Y, W, H) {
			// Style table for the respective styles
			static const Fl_Text_Editor::Style_Table_Entry stable[] = {
				// FONT COLOR      FONT FACE   FONT SIZE
				// --------------- ----------- --------------
				{  FL_BLACK,       FL_COURIER, 14 }, // A - Black
				{  FL_DARK_GREEN,  FL_COURIER, 14 }, // B - Green
				{  FL_RED,         FL_COURIER, 14 }, // C - Red
			};
			tbuff = new Fl_Text_Buffer();    // text buffer
			sbuff = new Fl_Text_Buffer();    // style buffer
			buffer(tbuff);
			int stable_size = sizeof(stable) / sizeof(stable[0]);
			highlight_data(sbuff, stable, stable_size, 'A', 0, 0);
			tbuff->add_modify_callback(ModifyCallback_STATIC, (void*)this);
		}

		void text(const char* val) {
			tbuff->text(val);
		}
	};

}

class MainWindowFltkTextEditor : public Fl_Window
{
public:
	MainWindowFltkTextEditor(const char* label) : Fl_Window(100, 100, 800, 600, label)
	{
		auto editor = new MyEditor{ 10, 10, w() - 20, h() - 20 };
		editor->text("In this editor, digits 0-4 are shown in green, 5-9 shown in red.\n"
			"So here's some numbers 0123456789.\n"
			"Coloring is handled automatically by the add_modify_callback().\n"
			"\n"
			"You can type here to test. ");

		resizable(editor);
	}
};
