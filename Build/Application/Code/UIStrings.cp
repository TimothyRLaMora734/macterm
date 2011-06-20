/*###############################################################

	UIStrings.cp
	
	MacTelnet
		© 1998-2010 by Kevin Grant.
		© 2001-2003 by Ian Anderson.
		© 1986-1994 University of Illinois Board of Trustees
		(see About box for full list of U of I contributors).
	
	This program is free software; you can redistribute it or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version
	2 of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be
	useful, but WITHOUT ANY WARRANTY; without even the implied
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	PURPOSE.  See the GNU General Public License for more
	details.
	
	You should have received a copy of the GNU General Public
	License along with this program; if not, write to:
	
		Free Software Foundation, Inc.
		59 Temple Place, Suite 330
		Boston, MA  02111-1307
		USA

###############################################################*/

#include "UniversalDefines.h"

// standard-C includes
#include <cstdlib>

// standard-C++ includes
#include <algorithm>
#include <functional>
#include <vector>

// GNU extension includes
#include <ext/numeric>

// Mac includes
#include <CoreServices/CoreServices.h>

// library includes
#include <RandomWrap.h>

// resource includes
#include "CFRetainRelease.h"

// MacTelnet includes
#include "UIStrings.h"
#include "UIStrings_PrefsWindow.h"



#pragma mark Internal Methods

#define createCFStringWithPascalString (s)		CFStringCreateWithPascalString(kCFAllocatorDefault, s, CFStringGetSystemEncoding())



#pragma mark Public Methods

/*!
Locates the specified alert window string and returns
a reference to a Core Foundation string.  Since a copy
is made, you must call CFRelease() on the returned
string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_AlertWindowCFString	inWhichString,
				 CFStringRef&					outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_AlertWindowANSIColorsResetPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Reset to the 16 standard ANSI colors?"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowANSIColorsResetPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowCloseName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Close"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowCloseName"));
		break;
	
	case kUIStrings_AlertWindowCloseHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("You will lose any unsaved changes."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowCloseHelpText"));
		break;
	
	case kUIStrings_AlertWindowClosePrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("The processes in this window will be forced to quit.  Close anyway?"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowClosePrimaryText"));
		break;
	
	case kUIStrings_AlertWindowCommandFailedHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Click Quit to shut down this program instantly.  Click Continue to ignore the error (not recommended for some types of errors)."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowCommandFailedHelpText"));
		break;
	
	case kUIStrings_AlertWindowCommandFailedPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("The command could not be completed, because an error of type %1$d occurred."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowCommandFailedPrimaryText; %1$d will be an error code"));
		break;
	
	case kUIStrings_AlertWindowExcessiveErrorsPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("A significant number of data errors are occurring.  For stability reasons, MacTelnet has avoided trying to render some of the text."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowExcessiveErrorsPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowExcessiveErrorsHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("It is possible that the current Text Translation (set in the Map menu) is inaccurate."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowExcessiveErrorsHelpText"));
		break;
	
	case kUIStrings_AlertWindowGenericCannotUndoHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("This cannot be undone."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowGenericCannotUndoHelpText"));
		break;
	
	case kUIStrings_AlertWindowMacroExportNothingPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("No macros are active."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowMacroExportNothingPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowMacroExportNothingHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("To change the active macro set or define macros, use the Preferences window."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowMacroExportNothingHelpText"));
		break;
	
	case kUIStrings_AlertWindowMacroImportWarningPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Your active macro set will be modified.  Import anyway?"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowMacroImportWarningPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowMacroImportWarningHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("The active macro set is whichever one is selected in the Map menu."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowMacroImportWarningHelpText"));
		break;
	
	case kUIStrings_AlertWindowNotifyActivityPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Data has arrived in a monitored window."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyActivityPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowNotifyActivityTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Session Active"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyActivityTitle"));
		break;
	
	case kUIStrings_AlertWindowNotifyInactivityPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("A monitored window is no longer transmitting data."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyActivityPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowNotifyInactivityTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Session Idle"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyInactivityTitle"));
		break;
	
	case kUIStrings_AlertWindowNotifyProcessDieTemplate:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Process exited unsuccessfully (code %1$d)."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyProcessDieTemplate; %1$d is the nonzero exit status code"));
		break;
	
	case kUIStrings_AlertWindowNotifyProcessDieTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Session Failed"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyProcessDieTitle"));
		break;
	
	case kUIStrings_AlertWindowNotifyProcessExitPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Process exited successfully."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyProcessExitPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowNotifyProcessExitTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Session Ended"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyProcessExitTitle"));
		break;
	
	case kUIStrings_AlertWindowNotifyProcessSignalTemplate:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Process unexpectedly quit (exited with signal %1$d)."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowNotifyProcessSignalTemplate; %1$d is the signal number"));
		break;
	
	case kUIStrings_AlertWindowPasteLinesWarningName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Multi-Line Paste"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowPasteLinesWarningName"));
		break;
	
	case kUIStrings_AlertWindowPasteLinesWarningPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Join into a single line before pasting?"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowPasteLinesWarningPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowPasteLinesWarningHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("In terminal applications such as shells, entering multiple lines may produce unexpected results."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowPasteLinesWarningHelpText"));
		break;
	
	case kUIStrings_AlertWindowScriptErrorName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Script Error"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowScriptErrorName"));
		break;
	
	case kUIStrings_AlertWindowScriptErrorHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("An error of type %1$d occurred."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowScriptErrorHelpText; %1$d will be an error code"));
		break;
	
	case kUIStrings_AlertWindowShowIPAddressesPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Your computer has at least the following IP addresses:"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowShowIPAddressesPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowUpdateCheckHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("A new version may be available on the web!"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowUpdateCheckHelpText"));
		break;
	
	case kUIStrings_AlertWindowUpdateCheckPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("It has been some time since this copy of MacTelnet was updated."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowUpdateCheckPrimaryText"));
		break;
	
	case kUIStrings_AlertWindowUpdateCheckTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("MacTelnet Update"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowUpdateCheckTitle"));
		break;
	
	case kUIStrings_AlertWindowQuitName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Quit"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowQuitName"));
		break;
	
	case kUIStrings_AlertWindowQuitHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Any recently-opened windows will be closed automatically."), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowQuitHelpText"));
		break;
	
	case kUIStrings_AlertWindowQuitPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Review running sessions?"), CFSTR("Alerts"),
													CFSTR("kUIStrings_AlertWindowQuitPrimaryText"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (alert window strings)


/*!
Locates the specified button title string and returns
a reference to a Core Foundation string.  Since a copy
is made, you must call CFRelease() on the returned
string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_ButtonCFString	inWhichString,
				 CFStringRef&				outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_ButtonOK:
		outString = CFCopyLocalizedStringFromTable(CFSTR("OK"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonOK"));
		break;
	
	case kUIStrings_ButtonCancel:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Cancel"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonCancel"));
		break;
	
	case kUIStrings_ButtonSave:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Save"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonSave"));
		break;
	
	case kUIStrings_ButtonStartSession:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Start Session"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonStartSession"));
		break;
	
	case kUIStrings_ButtonDontSave:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Don't Save"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonDontSave"));
		break;
	
	case kUIStrings_ButtonYes:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Yes"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonYes"));
		break;
	
	case kUIStrings_ButtonNo:
		outString = CFCopyLocalizedStringFromTable(CFSTR("No"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonNo"));
		break;
	
	case kUIStrings_ButtonClose:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Close"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonClose"));
		break;
	
	case kUIStrings_ButtonQuit:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Quit"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonQuit"));
		break;
	
	case kUIStrings_ButtonContinue:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Continue"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonContinue"));
		break;
	
	case kUIStrings_ButtonIgnore:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Ignore"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonIgnore"));
		break;
	
	case kUIStrings_ButtonCheckForUpdatesWithEllipsis:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Check for Updates..."), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonCheckForUpdatesWithEllipsis"));
		break;
	
	case kUIStrings_ButtonReviewWithEllipsis:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Review..."), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonReviewWithEllipsis"));
		break;
	
	case kUIStrings_ButtonDiscardAll:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Discard All"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonDiscardAll"));
		break;
	
	case kUIStrings_ButtonPasteNormally:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Paste Normally"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonPasteNormally"));
		break;
	
	case kUIStrings_ButtonMakeOneLine:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Join"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonMakeOneLine"));
		break;
	
	case kUIStrings_ButtonHelpAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("help"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonHelpAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonAddAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("add"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonAddAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonRemoveAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("remove"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonRemoveAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonMoveUpAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("move up"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonMoveUpAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonMoveDownAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("move down"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonMoveDownAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonColorBoxAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("color"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonColorBoxAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonEditTextArrowsAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("edit text numerical value"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonEditTextArrowsAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonEditTextHistoryAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("recent edit text values"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonEditTextHistoryAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	case kUIStrings_ButtonPopUpMenuArrowsAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("pop up menu selection"), CFSTR("Buttons"),
													CFSTR("kUIStrings_ButtonPopUpMenuArrowsAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (button strings)


/*!
Locates the specified string used by the clipboard window.
Returns a reference to a Core Foundation string.  Since a
copy is made, you must call CFRelease() on the returned
string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_ClipboardWindowCFString	inWhichString,
				 CFStringRef&						outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_ClipboardWindowIconName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Clipboard"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowIconName"));
		break;
	
	case kUIStrings_ClipboardWindowLabelWidth:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Width:"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowLabelWidth; used to label the width property of a copied image"));
		break;
	
	case kUIStrings_ClipboardWindowLabelHeight:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Height:"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowLabelHeight; used to label the height property of a copied image"));
		break;
	
	case kUIStrings_ClipboardWindowPixelDimensionTemplate:
		outString = CFCopyLocalizedStringFromTable(CFSTR("%1$d pixels"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowPixelDimensionTemplate; %1$d is a numeric pixel value"));
		break;
	
	case kUIStrings_ClipboardWindowOnePixel:
		outString = CFCopyLocalizedStringFromTable(CFSTR("one pixel"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowOnePixel; used to represent a size of exactly one pixel"));
		break;
	
	case kUIStrings_ClipboardWindowGenericKindText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("text"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowGenericKindText"));
		break;
	
	case kUIStrings_ClipboardWindowGenericKindImage:
		outString = CFCopyLocalizedStringFromTable(CFSTR("image"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowGenericKindImage"));
		break;
	
	case kUIStrings_ClipboardWindowDataSizeTemplate:
		outString = CFCopyLocalizedStringFromTable(CFSTR("%1$@%2$d %3$@"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowDataSizeTemplate; %1$@ is used if the value is approximate, and should have trailing whitespace; %2$d is a numeric size value; %3$@ is a units string, like MB"));
		break;
	
	case kUIStrings_ClipboardWindowDataSizeApproximately:
		outString = CFCopyLocalizedStringFromTable(CFSTR("about "), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowDataSizeApproximately; substituted into the data size string whenever the size value is not exact, e.g. about 3 MB; must have a trailing space!!!"));
		break;
	
	case kUIStrings_ClipboardWindowUnitsByte:
		outString = CFCopyLocalizedStringFromTable(CFSTR("byte"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowUnitsByte; a single byte"));
		break;
	
	case kUIStrings_ClipboardWindowUnitsBytes:
		outString = CFCopyLocalizedStringFromTable(CFSTR("bytes"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowUnitsBytes; units of bytes"));
		break;
	
	case kUIStrings_ClipboardWindowUnitsK:
		outString = CFCopyLocalizedStringFromTable(CFSTR("K"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowUnitsK; units of kilobytes"));
		break;
	
	case kUIStrings_ClipboardWindowUnitsMB:
		outString = CFCopyLocalizedStringFromTable(CFSTR("MB"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowUnitsMB; units of megabytes"));
		break;
	
	case kUIStrings_ClipboardWindowValueUnknown:
		outString = CFCopyLocalizedStringFromTable(CFSTR("unknown"), CFSTR("ClipboardWindow"),
													CFSTR("kUIStrings_ClipboardWindowValueUnknown; used to represent any unknown property"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (clipboard strings)


/*!
Locates the specified string used by the command line
floating window.  Returns a reference to a Core Foundation
string.  Since a copy is made, you must call CFRelease()
on the returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_CommandLineCFString	inWhichString,
				 CFStringRef&					outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_CommandLineHelpTextCommandArgumentTemplate:
		outString = CFCopyLocalizedStringFromTable(CFSTR("%1$@ %2$@ - %3$@"), CFSTR("CommandLine"),
													CFSTR("kUIStrings_CommandLineHelpTextCommandArgumentTemplate; %1$@ will be a command name; %2$@ will be an argument to that command; %3$@ will be a description of the argument"));
		break;
	
	case kUIStrings_CommandLineHelpTextCommandTemplate:
		outString = CFCopyLocalizedStringFromTable(CFSTR("%1$@ - %2$@"), CFSTR("CommandLine"),
													CFSTR("kUIStrings_CommandLineHelpTextCommandTemplate; %1$@ will be a command name; %2$@ will be a description of the command"));
		break;
	
	case kUIStrings_CommandLineHelpTextDefault:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Text is sent to the terminal window."), CFSTR("CommandLine"),
													CFSTR("kUIStrings_CommandLineHelpTextDefault"));
		break;
	
	case kUIStrings_CommandLineHelpTextFreeInput:
		outString = CFCopyLocalizedStringFromTable(CFSTR("This text will be sent to the frontmost session window."), CFSTR("CommandLine"),
													CFSTR("kUIStrings_CommandLineHelpTextFreeInput"));
		break;
	
	case kUIStrings_CommandLineHistoryMenuAccessibilityDesc:
		outString = CFCopyLocalizedStringFromTable(CFSTR("recent command lines"), CFSTR("CommandLine"),
													CFSTR("kUIStrings_CommandLineHistoryMenuAccessibilityDesc; lowercase with minimal punctuation"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (command line strings)


/*!
Locates the specified string used by a context-sensitive
pop-up menu.  Returns a reference to a Core Foundation
string.  Since a copy is made, you must call CFRelease()
on the returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_ContextualMenuCFString	inWhichString,
				 CFStringRef&						outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_ContextualMenuArrangeAllInFront:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Arrange All Windows in Front"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuArrangeAllInFront"));
		break;
	
	case kUIStrings_ContextualMenuChangeBackground:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Change Background..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuChangeBackground"));
		break;
	
	case kUIStrings_ContextualMenuCloseThisWindow:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Close This Window"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuCloseThisWindow"));
		break;
	
	case kUIStrings_ContextualMenuCopyToClipboard:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Copy"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuCopyToClipboard"));
		break;
	
	case kUIStrings_ContextualMenuCopyUsingTabsForSpaces:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Copy with Tab Substitution"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuCopyUsingTabsForSpaces"));
		break;
	
	case kUIStrings_ContextualMenuCustomFormat:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Custom Format..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuCustomFormat"));
		break;
	
	case kUIStrings_ContextualMenuCustomScreenDimensions:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Custom Screen Size..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuCustomScreenDimensions"));
		break;
	
	case kUIStrings_ContextualMenuFindInThisWindow:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Find..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuFindInThisWindow"));
		break;
	
	case kUIStrings_ContextualMenuFixCharacterTranslation:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Fix Character Translation..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuFixCharacterTranslation"));
		break;
	
	case kUIStrings_ContextualMenuHideThisWindow:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Hide This Window"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuHideThisWindow"));
		break;
	
	case kUIStrings_ContextualMenuMoveToNewWorkspace:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Move to New Workspace"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuMoveToNewWorkspace"));
		break;
	
	case kUIStrings_ContextualMenuOpenThisResource:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Open URL"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuOpenThisResource"));
		break;
	
	case kUIStrings_ContextualMenuPasteText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Paste"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuPasteText"));
		break;
	
	case kUIStrings_ContextualMenuPrintSelectedText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Print Selected Text..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuPrintSelectedText"));
		break;
	
	case kUIStrings_ContextualMenuRenameThisWindow:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Rename..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuRenameThisWindow"));
		break;
	
	case kUIStrings_ContextualMenuSaveSelectedText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Save Selection..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuSaveSelectedText"));
		break;
	
	case kUIStrings_ContextualMenuSpeakSelectedText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Start Speaking Text"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuSpeakSelectedText"));
		break;
	
	case kUIStrings_ContextualMenuStopSpeaking:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Stop Speaking"), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuStopSpeaking"));
		break;
	
	case kUIStrings_ContextualMenuSpecialKeySequences:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Custom Key Sequences..."), CFSTR("ContextualMenus"),
													CFSTR("kUIStrings_ContextualMenuSpecialKeySequences"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (contextual menu item strings)


/*!
Locates the specified string used for a file or folder
name, and returns a reference to a Core Foundation
string.  Since a copy is made, you must call CFRelease()
on the returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_FileOrFolderCFString		inWhichString,
				 CFStringRef&						outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_FileDefaultCaptureFile:
		outString = CFCopyLocalizedStringFromTable(CFSTR("untitled.txt"), CFSTR("FileOrFolderNames"),
													CFSTR("kUIStrings_FileDefaultCaptureFile; please localize the name but keep the .txt suffix"));
		break;
	
	case kUIStrings_FileDefaultMacroSet:
		outString = CFCopyLocalizedStringFromTable(CFSTR("untitled.macros"), CFSTR("FileOrFolderNames"),
													CFSTR("kUIStrings_FileDefaultMacroSet; please localize the name but keep the .macros suffix"));
		break;
	
	case kUIStrings_FileDefaultSession:
		outString = CFCopyLocalizedStringFromTable(CFSTR("untitled.session"), CFSTR("FileOrFolderNames"),
													CFSTR("kUIStrings_FileDefaultSession; please localize the name but keep the .session suffix"));
		break;
	
	case kUIStrings_FileNameDockTileAttentionPicture:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("DockTileAttention.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameDockTileAttentionMask:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("DockTileAttentionMask.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame1Picture:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof1.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame1Mask:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof1Mask.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame2Picture:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof2.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame2Mask:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof2Mask.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame3Picture:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof3.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame3Mask:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof3Mask.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame4Picture:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof4.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame4Mask:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof4Mask.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame5Picture:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof5.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FileNameToolbarPoofFrame5Mask:
		// localization of this string is unnecessary; however an explicit retain is now
		// needed because the caller is required to release the string later on
		outString = CFSTR("ToolbarItemPoof5Mask.pict");
		CFRetain(outString);
		break;
	
	case kUIStrings_FolderNameApplicationPreferences:
		outString = CFCopyLocalizedStringFromTable(CFSTR("MacTelnet Preferences"), CFSTR("FileOrFolderNames"),
													CFSTR("kUIStrings_FolderNameApplicationPreferences; warning, this should be consistent with previous strings of this type because it is used to find existing preferences"));
		break;
	
	case kUIStrings_FolderNameApplicationRecentSessions:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Recent Sessions"), CFSTR("FileOrFolderNames"),
													CFSTR("kUIStrings_FolderNameApplicationRecentSessions; warning, this should be consistent with previous strings of this type because it is used to find existing preferences"));
		break;
	
	case kUIStrings_FolderNameApplicationScriptsMenuItems:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Scripts Menu Items"), CFSTR("FileOrFolderNames"),
													CFSTR("kUIStrings_FolderNameApplicationScriptsMenuItems; warning, this should be consistent with previous strings of this type because it is used to find existing scripts"));
		break;
	
	case kUIStrings_FolderNameHomeLibraryLogs:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Logs"), CFSTR("FileOrFolderNames"),
													CFSTR("kUIStrings_FolderNameHomeLibraryLogs; should EXACTLY MATCH what Mac OS X uses to name this folder (we would ask the system for this name if we could)"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (file or folder strings)


/*!
Locates the specified string used by the help system,
either for display in a menu item or as a search string.
Returns a reference to a Core Foundation string.  Since
a copy is made, you must call CFRelease() on the
returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_HelpSystemCFString	inWhichString,
				 CFStringRef&					outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_HelpSystemName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("MacTelnet Help"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemName; must match AppleTitle in HTML"));
		break;
	
	case kUIStrings_HelpSystemContextualHelpCommandName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Contextual Help"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemContextualHelpCommandName"));
		break;
	
	case kUIStrings_HelpSystemShowTagsCommandName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Show Help Tags"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemShowTagsCommandName"));
		break;
	
	case kUIStrings_HelpSystemHideTagsCommandName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Hide Help Tags"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemHideTagsCommandName"));
		break;
	
	case kUIStrings_HelpSystemTopicHelpCreatingSessions:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Help Creating Sessions"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemTopicHelpCreatingSessions; should match topic title"));
		break;
	
	case kUIStrings_HelpSystemTopicHelpSearchingForText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Help Searching For Text"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemTopicHelpSearchingForText; should match topic title"));
		break;
	
	case kUIStrings_HelpSystemTopicHelpSettingTheScreenSize:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Help Setting The Screen Size"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemTopicHelpSettingTheScreenSize; should match topic title"));
		break;
	
	case kUIStrings_HelpSystemTopicHelpUsingTheCommandLine:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Help Using The Floating Command Line"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemTopicHelpUsingTheCommandLine; should match topic title"));
		break;
	
	case kUIStrings_HelpSystemTopicHelpWithPreferences:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Help With Preferences"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemTopicHelpWithPreferences; should match topic title"));
		break;
	
	case kUIStrings_HelpSystemTopicHelpWithScreenFormatting:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Help With Screen Formatting"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemTopicHelpWithScreenFormatting; should match topic title"));
		break;
	
	case kUIStrings_HelpSystemTopicHelpWithTerminalSettings:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Help With Terminal Settings"), CFSTR("HelpSystem"),
													CFSTR("kUIStrings_HelpSystemTopicHelpWithTerminalSettings; should match topic title"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (help system strings)


/*!
Locates the specified string used by the Preferences
window and returns a reference to a Core Foundation
string.  Since a copy is made, you must call
CFRelease() on the returned string when you are
finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_PreferencesWindowCFString	inWhichString,
				 CFStringRef&							outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_PreferencesWindowAddToFavoritesButton:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Add to Preferences"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowAddToFavoritesButton"));
		break;
	
	case kUIStrings_PreferencesWindowCollectionsDrawerDescription:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Shows or hides a customizable list of collections for the displayed preference category."), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowCollectionsDrawerDescription"));
		break;
	
	case kUIStrings_PreferencesWindowCollectionsDrawerShowHideName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Collections"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowCollectionsDrawerShowHideName"));
		break;
	
	case kUIStrings_PreferencesWindowDefaultFavoriteName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Default"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowDefaultFavoriteName"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesDuplicateButtonName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Duplicate"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesDuplicateButtonName"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesDuplicateNameTemplate:
		outString = CFCopyLocalizedStringFromTable(CFSTR("%1$@ copy"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesDuplicateNameTemplate; %1$@ will be the old item name"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesEditButtonName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Edit..."), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesEditButtonName"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesNewButtonName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("New..."), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesNewButtonName"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesNewGroupButtonName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("New Group..."), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesNewGroupButtonName"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesRemoveButtonName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Remove"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesRemoveButtonName"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesCannotRemoveDefault:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Sorry, you cannot remove the default item in this list."), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesCannotRemoveDefault"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesRemoveWarning:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Remove item \"%1$@\" from the list?"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesRemoveWarning; %1$@ will be a Favorite name from the list"));
		break;
	
	case kUIStrings_PreferencesWindowFavoritesRemoveWarningHelpText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("This cannot be undone."), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFavoritesRemoveWarningHelpText"));
		break;
	
	case kUIStrings_PreferencesWindowFormatsCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Formats"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFormatsCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowFormatsNormalTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Normal"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFormatsNormalTabName"));
		break;
	
	case kUIStrings_PreferencesWindowFormatsANSIColorsTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("ANSI Colors"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowFormatsANSIColorsTabName"));
		break;
	
	case kUIStrings_PreferencesWindowGeneralCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("General"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowGeneralCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowGeneralNotificationTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Notification"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowGeneralNotificationTabName"));
		break;
	
	case kUIStrings_PreferencesWindowGeneralOptionsTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Options"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowGeneralOptionsTabName"));
		break;
	
	case kUIStrings_PreferencesWindowGeneralSpecialTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Special"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowGeneralSpecialTabName"));
		break;
	
	case kUIStrings_PreferencesWindowIconName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Preferences"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowIconName"));
		break;
	
	case kUIStrings_PreferencesWindowKioskCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Full Screen"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowKioskCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowListHeaderNumber:
		outString = CFCopyLocalizedStringFromTable(CFSTR("#"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesListHeaderNumber"));
		break;
	
	case kUIStrings_PreferencesWindowMacrosCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Macros"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowMacrosCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowMacrosListHeaderName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Macro Name"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowMacrosListHeaderName"));
		break;
	
	case kUIStrings_PreferencesWindowScriptsCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Scripts"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowScriptsCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowScriptsListHeaderEvent:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Event"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowScriptsListHeaderEvent"));
		break;
	
	case kUIStrings_PreferencesWindowScriptsListHeaderScriptToRun:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Script To Run"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowScriptsListHeaderScriptToRun"));
		break;
	
	case kUIStrings_PreferencesWindowSessionsCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Sessions"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowSessionsCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowSessionsDataFlowTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Data Flow"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowSessionsDataFlowTabName"));
		break;
	
	case kUIStrings_PreferencesWindowSessionsGraphicsTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Graphics"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowSessionsVectorGraphicsTabName"));
		break;
	
	case kUIStrings_PreferencesWindowSessionsKeyboardTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Keyboard"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowSessionsControlKeysTabName"));
		break;
	
	case kUIStrings_PreferencesWindowSessionsResourceTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Resource"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowSessionsHostTabName"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Terminals"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsEmulationTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Emulation"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsEmulationTabName"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsVT100FixLineWrapBug:
		outString = CFCopyLocalizedStringFromTable(CFSTR("VT100 Fix Line Wrapping Bug"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsVT100FixLineWrapBug"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsXTerm256ColorsEnabled:
		outString = CFCopyLocalizedStringFromTable(CFSTR("XTerm 256 Colors"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsXTerm256ColorsEnabled"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsXTermBackColorErase:
		outString = CFCopyLocalizedStringFromTable(CFSTR("XTerm Background Color Erase"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsXTermBackColorErase"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsXTermColorEnabled:
		outString = CFCopyLocalizedStringFromTable(CFSTR("XTerm Color"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsXTermColorEnabled"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsXTermGraphicsEnabled:
		outString = CFCopyLocalizedStringFromTable(CFSTR("XTerm Graphics Characters"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsXTermGraphicsEnabled"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsXTermWindowAltEnabled:
		outString = CFCopyLocalizedStringFromTable(CFSTR("XTerm Window Alteration"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsXTermWindowAltEnabled"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsListHeaderTweakName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Terminal Feature"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsListHeaderTweakName"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsOptionsTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Options"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsOptionsTabName"));
		break;
	
	case kUIStrings_PreferencesWindowTerminalsScreenTabName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Screen"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTerminalsScreenTabName"));
		break;
	
	case kUIStrings_PreferencesWindowTranslationsCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Translations"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTranslationsCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowTranslationsListHeaderBaseTable:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Available Encodings"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowTranslationsListHeaderBaseTable"));
		break;
	
	case kUIStrings_PreferencesWindowWorkspacesCategoryName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Workspaces"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowWorkspacesCategoryName"));
		break;
	
	case kUIStrings_PreferencesWindowWindowsListHeaderName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Window Name"), CFSTR("PreferencesWindow"),
													CFSTR("kUIStrings_PreferencesWindowWindowsListHeaderName"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (preferences window strings)


/*!
Locates the specified string used by a progress window,
and returns a reference to a Core Foundation string.
Since a copy is made, you must call CFRelease() on the
returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_ProgressWindowCFString	inWhichString,
				 CFStringRef&						outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_ProgressWindowFontListIconName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Font List Rebuilding Progress"), CFSTR("ProgressWindows"),
													CFSTR("kUIStrings_ProgressWindowFontListIconName"));
		break;
	
	case kUIStrings_ProgressWindowPrintingPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Printing..."), CFSTR("ProgressWindows"),
													CFSTR("kUIStrings_ProgressWindowPrintingPrimaryText"));
		break;
	
	case kUIStrings_ProgressWindowScriptsMenuIconName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Scripts Menu Rebuilding Progress"), CFSTR("ProgressWindows"),
													CFSTR("kUIStrings_ProgressWindowScriptsMenuIconName"));
		break;
	
	case kUIStrings_ProgressWindowScriptsMenuPrimaryText:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Searching for Scripts menu items..."), CFSTR("ProgressWindows"),
													CFSTR("kUIStrings_ProgressWindowScriptsMenuPrimaryText"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (progress window strings)


/*!
Locates the specified string used by the “session info”
window, and returns a reference to a Core Foundation
string.  Since a copy is made, you must call CFRelease()
on the returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_SessionInfoWindowCFString	inWhichString,
				 CFStringRef&							outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_SessionInfoWindowIconName:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Session Info"), CFSTR("SessionInfoWindow"),
													CFSTR("kUIStrings_SessionInfoWindowIconName"));
		break;
	
	case kUIStrings_SessionInfoWindowStatusProcessNewborn:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Running (just opened)"), CFSTR("SessionInfoWindow"),
													CFSTR("kUIStrings_SessionInfoWindowStatusProcessNewborn"));
		break;
	
	case kUIStrings_SessionInfoWindowStatusProcessRunning:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Running"), CFSTR("SessionInfoWindow"),
													CFSTR("kUIStrings_SessionInfoWindowStatusProcessRunning"));
		break;
	
	case kUIStrings_SessionInfoWindowStatusProcessTerminated:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Not Running"), CFSTR("SessionInfoWindow"),
													CFSTR("kUIStrings_SessionInfoWindowStatusProcessTerminated"));
		break;
	
	case kUIStrings_SessionInfoWindowStatusTerminatedAtTime:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Not Running, Since %1$@"), CFSTR("SessionInfoWindow"),
													CFSTR("kUIStrings_SessionInfoWindowStatusProcessTerminated; %1$@ is the time of termination"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (session info window strings)


/*!
Locates the specified string used for a system-provided
UI element (like a file chooser or color picker), and
returns a reference to a Core Foundation string.  Since
a copy is made, you must call CFRelease() on the returned
string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_SystemDialogCFString		inWhichString,
				 CFStringRef&						outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_SystemDialogPromptCaptureToFile:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Enter a name for the file to contain captured text."),
													CFSTR("SystemDialogs"),
													CFSTR("kUIStrings_SystemDialogPromptCaptureToFile"));
		break;
	
	case kUIStrings_SystemDialogPromptOpenMacroSet:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Choose one or more macro files to open."),
													CFSTR("SystemDialogs"),
													CFSTR("kUIStrings_SystemDialogPromptOpenMacroSet"));
		break;
	
	case kUIStrings_SystemDialogPromptOpenSession:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Choose one or more settings files to open."),
													CFSTR("SystemDialogs"),
													CFSTR("kUIStrings_SystemDialogPromptOpenSession"));
		break;
	
	case kUIStrings_SystemDialogPromptSaveSession:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Enter a name for the file to contain your settings."),
													CFSTR("SystemDialogs"),
													CFSTR("kUIStrings_SystemDialogPromptSaveSession"));
		break;
	
	case kUIStrings_SystemDialogPromptPickColor:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Please choose a color."),
													CFSTR("SystemDialogs"),
													CFSTR("kUIStrings_SystemDialogPromptPickColor"));
		break;
	
	case kUIStrings_SystemDialogTitleOpenMacroSet:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Open Macro Set"),
													CFSTR("SystemDialogs"),
													CFSTR("kUIStrings_SystemDialogTitleOpenMacroSet"));
		break;
	
	case kUIStrings_SystemDialogTitleOpenSession:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Open Session"),
													CFSTR("SystemDialogs"),
													CFSTR("kUIStrings_SystemDialogTitleOpenSession"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (system dialog strings)


/*!
Locates the specified string used by a terminal window,
and returns a reference to a Core Foundation string.
Since a copy is made, you must call CFRelease() on the
returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_TerminalCFString		inWhichString,
				 CFStringRef&					outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_TerminalAccessibilityDescription:
		outString = CFCopyLocalizedStringFromTable(CFSTR("terminal screen"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalAccessibilityDescription; must be all-lowercase without punctuation"));
		break;
	
	case kUIStrings_TerminalBackgroundAccessibilityDescription:
		outString = CFCopyLocalizedStringFromTable(CFSTR("terminal background"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalBackgroundAccessibilityDescription; must be all-lowercase without punctuation"));
		break;
	
	case kUIStrings_TerminalInterruptProcess:
		outString = CFCopyLocalizedStringFromTable(CFSTR("[Interrupted]"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalInterruptProcess"));
		break;
	
	case kUIStrings_TerminalNewCommandsKeyCharacter:
		outString = CFCopyLocalizedStringFromTable(CFSTR("n"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalNewCommandsKeyCharacter; used for some menu command keys, this should be only one lowercase Unicode character"));
		break;
	
	case kUIStrings_TerminalPrintFromTerminalJobTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Print From Terminal: MacTelnet"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalPrintFromTerminalJobTitle"));
		break;
	
	case kUIStrings_TerminalPrintScreenJobTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Print Screen: MacTelnet"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalPrintScreenJobTitle"));
		break;
	
	case kUIStrings_TerminalPrintSelectionJobTitle:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Print Selection: MacTelnet"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalPrintSelectionJobTitle"));
		break;
	
	case kUIStrings_TerminalResumeOutput:
		outString = CFCopyLocalizedStringFromTable(CFSTR("[Resumed]"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalResumeOutput"));
		break;
	
	case kUIStrings_TerminalSuspendOutput:
		outString = CFCopyLocalizedStringFromTable(CFSTR("[Suspended]"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalSuspendOutput"));
		break;
	
	case kUIStrings_TerminalSearchNothingFound:
		outString = CFCopyLocalizedStringFromTable(CFSTR("The text was not found."), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalSearchNothingFound"));
		break;
	
	case kUIStrings_TerminalSearchNumberOfMatches:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Matches: %1$u"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalSearchNumberOfMatches; %1$u will be the number of times the query found a match"));
		break;
	
	case kUIStrings_TerminalVectorGraphicsRedirect:
		outString = CFCopyLocalizedStringFromTable(CFSTR("[Output in Canvas Window]"), CFSTR("Terminal"),
													CFSTR("kUIStrings_TerminalVectorGraphicsRedirect"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (terminal strings)


/*!
Locates the specified string used by a toolbar item
label, and returns a reference to a Core Foundation
string.  Since a copy is made, you must call CFRelease()
on the returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_ToolbarItemCFString	inWhichString,
				 CFStringRef&					outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_ToolbarItemArrangeAllInFront:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Arrange All Windows in Front"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemArrangeAllInFront"));
		break;
	
	case kUIStrings_ToolbarItemBell:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Bell"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemBell"));
		break;
	
	case kUIStrings_ToolbarItemCustomizeToolbar:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Customize"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemCustomizeToolbar"));
		break;
	
	case kUIStrings_ToolbarItemFullScreen:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Full Screen"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarFullScreen"));
		break;
	
	case kUIStrings_ToolbarItemHideFrontWindow:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Hide"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemHideFrontWindow"));
		break;
	
	case kUIStrings_ToolbarItemNewSessionDefault:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Default"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemNewSessionDefault"));
		break;
	
	case kUIStrings_ToolbarItemNewSessionLoginShell:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Log-In Shell"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemNewSessionLoginShell"));
		break;
	
	case kUIStrings_ToolbarItemNewSessionShell:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Shell"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemNewSessionShell"));
		break;
	
	case kUIStrings_ToolbarItemPrint:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Print"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemPrint"));
		break;
	
	case kUIStrings_ToolbarItemSearch:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Search"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemSearch"));
		break;
	
	case kUIStrings_ToolbarItemSuspendNetwork:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Suspend (Scroll Lock)"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemSuspendNetwork"));
		break;
	
	case kUIStrings_ToolbarItemTerminalLED1:
		outString = CFCopyLocalizedStringFromTable(CFSTR("L1"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemTerminalLED1"));
		break;
	
	case kUIStrings_ToolbarItemTerminalLED2:
		outString = CFCopyLocalizedStringFromTable(CFSTR("L2"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemTerminalLED2"));
		break;
	
	case kUIStrings_ToolbarItemTerminalLED3:
		outString = CFCopyLocalizedStringFromTable(CFSTR("L3"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemTerminalLED3"));
		break;
	
	case kUIStrings_ToolbarItemTerminalLED4:
		outString = CFCopyLocalizedStringFromTable(CFSTR("L4"), CFSTR("ToolbarItems"),
													CFSTR("kUIStrings_ToolbarItemTerminalLED4"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (toolbar item strings)


/*!
Locates the specified string used for an Undo or Redo
command, and returns a reference to a Core Foundation string.
Since a copy is made, you must call CFRelease() on the
returned string when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given tag is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_Copy	(UIStrings_UndoCFString		inWhichString,
				 CFStringRef&				outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichString)
	{
	case kUIStrings_UndoDefault:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Undo"),
													CFSTR("Undo"), CFSTR("kUIStrings_UndoDefault"));
		break;
	
	case kUIStrings_RedoDefault:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Redo"),
													CFSTR("Undo"), CFSTR("kUIStrings_RedoDefault"));
		break;
	
	case kUIStrings_UndoDimensionChanges:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Undo Dimension Changes"),
													CFSTR("Undo"), CFSTR("kUIStrings_UndoDimensionChanges"));
		break;
	
	case kUIStrings_RedoDimensionChanges:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Redo Dimension Changes"),
													CFSTR("Undo"), CFSTR("kUIStrings_RedoDimensionChanges"));
		break;
	
	case kUIStrings_UndoFormatChanges:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Undo Format Changes"),
													CFSTR("Undo"), CFSTR("kUIStrings_UndoFormatChanges"));
		break;
	
	case kUIStrings_RedoFormatChanges:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Redo Format Changes"),
													CFSTR("Undo"), CFSTR("kUIStrings_RedoFormatChanges"));
		break;
	
	case kUIStrings_UndoFullScreen:
		outString = CFCopyLocalizedStringFromTable(CFSTR("Undo Full Screen"),
													CFSTR("Undo"), CFSTR("kUIStrings_UndoFullScreen"));
		break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// Copy (undo/redo strings)


/*!
Locates the specified string table and returns a random
entry from it as a Core Foundation string.  Since a copy
is made, you must call CFRelease() on the returned string
when you are finished with it.

\retval kUIStrings_ResultOK
if the string is copied successfully

\retval kUIStrings_ResultNoSuchString
if the given class is invalid

\retval kUIStrings_ResultCannotGetString
if an OS error occurred

(3.0)
*/
UIStrings_Result
UIStrings_CopyRandom	(UIStrings_StringClass		inWhichStringClass,
						 CFStringRef&				outString)
{
	UIStrings_Result	result = kUIStrings_ResultOK;
	
	
	// IMPORTANT: The external utility program "genstrings" is not smart enough to
	//            figure out the proper string table name if you do not inline it.
	//            If you replace the CFSTR() calls with string constants, they will
	//            NOT BE PARSED CORRECTLY and consequently you won’t be able to
	//            automatically generate localizable ".strings" files.
	switch (inWhichStringClass)
	{
	//case kUIStrings_StringClassXYZ:
		//{
			//std::vector< UInt16 >	numberList(10/* number of available strings below */);
			//RandomWrap				generator;
			
			
			//__gnu_cxx::iota(numberList.begin(), numberList.end(), 0/* starting value */);
			//std::random_shuffle(numberList.begin(), numberList.end(), generator);
			//switch (numberList[0])
			//{
			//case 0:
			//default:
			//	outString = CFCopyLocalizedStringFromTable(CFSTR("whatever the string is"),
			//												CFSTR("StringTableName"), CFSTR("comment"));
			//	break;
			//}
		//}
		//break;
	
	default:
		// ???
		result = kUIStrings_ResultNoSuchString;
		break;
	}
	return result;
}// CopyRandom


/*!
Locates the specified file or folder name and calls
FSMakeFSRefUnicode() with the given parent directory.  The
result is an FSRef with a copy of the given file name string.

\retval noErr
if the FSRef is created successfully

\retval paramErr
if no file name with the given ID exists

\retval (other)
if an OS error occurred (for example, the file/folder does not
actually exist on disk)

(3.1)
*/
OSStatus
UIStrings_CreateFileOrDirectory		(FSRef const&						inParentRef,
									 UIStrings_FileOrFolderCFString		inWhichString,
									 FSRef&								outFSRef,
									 UInt32*							outNewDirIDOrNullForFile,
									 FSCatalogInfoBitmap				inWhichInfo,
									 FSCatalogInfo const*				inInfoOrNull)
{
	CFStringRef			nameCFString = nullptr;
	UIStrings_Result	stringResult = kUIStrings_ResultOK;
	OSStatus			result = noErr;
	
	
	stringResult = UIStrings_Copy(inWhichString, nameCFString);
	
	// if the string was obtained, find the file
	if (stringResult.ok())
	{
		UniCharCount const	kBufferSize = CFStringGetLength(nameCFString);
		UniChar*			buffer = new UniChar[kBufferSize];
		
		
		CFStringGetCharacters(nameCFString, CFRangeMake(0, kBufferSize), buffer);
		
		// does it already exist?
		result = FSMakeFSRefUnicode(&inParentRef, kBufferSize, buffer,
									CFStringGetSmallestEncoding(nameCFString), &outFSRef);
		if (noErr != result)
		{
			if (nullptr != outNewDirIDOrNullForFile)
			{
				// create a directory
				result = FSCreateDirectoryUnicode(&inParentRef, kBufferSize, buffer, inWhichInfo, inInfoOrNull,
													&outFSRef, nullptr/* old-style specification record */,
													outNewDirIDOrNullForFile);
			}
			else
			{
				// create a file
				result = FSCreateFileUnicode(&inParentRef, kBufferSize, buffer, inWhichInfo, inInfoOrNull,
												&outFSRef, nullptr/* old-style specification record */);
			}
		}
		
		delete [] buffer, buffer = nullptr;
		CFRelease(nameCFString), nameCFString = nullptr;
	}
	else
	{
		result = paramErr;
	}
	
	return result;
}// CreateFileOrDirectory


/*!
Locates the specified file or folder name and calls
FSMakeFSRefUnicode() with the given parent directory.  The result
is an FSRef with a copy of the given file name string.

If the file does not exist, UIStrings_CreateFileOrDirectory() can
be used to create the object and return a valid record.

\retval noErr
if the FSRef is created successfully

\retval paramErr
if no file name with the given ID exists

\retval (other)
if an OS error occurred (for example, the file/folder does not
actually exist on disk)

(3.1)
*/
OSStatus
UIStrings_MakeFSRef		(FSRef const&						inParentRef,
						 UIStrings_FileOrFolderCFString		inWhichString,
						 FSRef&								outFSRef)
{
	CFStringRef			nameCFString = nullptr;
	UIStrings_Result	stringResult = kUIStrings_ResultOK;
	OSStatus			result = noErr;
	
	
	stringResult = UIStrings_Copy(inWhichString, nameCFString);
	
	// if the string was obtained, find the file
	if (stringResult.ok())
	{
		UniCharCount const	kBufferSize = CFStringGetLength(nameCFString);
		UniChar*			buffer = new UniChar[kBufferSize];
		
		
		CFStringGetCharacters(nameCFString, CFRangeMake(0, kBufferSize), buffer);
		result = FSMakeFSRefUnicode(&inParentRef, kBufferSize, buffer,
									CFStringGetSmallestEncoding(nameCFString), &outFSRef);
		
		delete [] buffer, buffer = nullptr;
		CFRelease(nameCFString), nameCFString = nullptr;
	}
	else
	{
		result = paramErr;
	}
	
	return result;
}// MakeFSRef

// BELOW IS REQUIRED NEWLINE TO END FILE
