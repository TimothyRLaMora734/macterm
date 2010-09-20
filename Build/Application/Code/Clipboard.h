/*!	\file Clipboard.h
	\brief The clipboard window, and Copy and Paste management.
	
	Based on the implementation of Apple’s SimpleText clipboard.
*/
/*###############################################################

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

#ifndef __CLIPBOARD__
#define __CLIPBOARD__

// Mac includes
#include <Carbon/Carbon.h>
#ifdef __OBJC__
#	import <Cocoa/Cocoa.h>
#endif
#include <CoreServices/CoreServices.h>

// MacTelnet includes
#include "SessionRef.typedef.h"
#include "TerminalViewRef.typedef.h"
#include "VectorInterpreterID.typedef.h"



#pragma mark Constants

typedef UInt16 Clipboard_CopyMethod; // do not redefine
enum
{
	kClipboard_CopyMethodStandard		= 0,		// use this value, or...
	kClipboard_CopyMethodTable			= 1 << 0,	// ...a bitwise OR of one or more of these mask values
	kClipboard_CopyMethodInline			= 1 << 1
};

/*!
A data constraint allows you to take advantage of common
type filtering that the Clipboard module is already
familiar with.  This can avoid an often cumbersome series
of API calls and string comparisons necessary when dealing
with pasteboards.  It can also simplify tasks like iterating
over buffers, if you can ensure the array has elements of a
certain size.
*/
enum Clipboard_DataConstraint
{
	kClipboard_DataConstraintNone				= 0xFFFF,	//!< any type of data
	kClipboard_DataConstraintText8Bit			= 1 << 0,	//!< only text that can be expressed as bytes
	kClipboard_DataConstraintText16BitNative	= 1 << 1	//!< only Unicode text with native byte-ordering
};

typedef UInt16 Clipboard_PasteMethod; // do not redefine
enum
{
	kClipboard_PasteMethodStandard		= 0,
	kClipboard_PasteMethodBlock			= 1
};

/*!
When pasting, you have the option of using a filtered version
of the data actually on the Clipboard, to suit the destination.
*/
enum Clipboard_Modifier
{
	kClipboard_ModifierNone						= 0,		//!< leave data unchanged
	kClipboard_ModifierOneLine					= 1			//!< strip all '\r' and '\n' characters first
};

#pragma mark Types

#ifdef __OBJC__

/*!
Implements the data-rendering part of the Clipboard.

Note that this is only in the header for the sake of
Interface Builder, which will not synchronize with
changes to an interface declared in a ".mm" file.
*/
@interface Clipboard_ContentView : NSControl
{
@private
	BOOL	showDragHighlight;
}

- (void)drawRect:(NSRect)	rect;

- (void)setShowDragHighlight:(BOOL)		flag;

- (BOOL)showDragHighlight;

@end

/*!
Implements the Clipboard window.  See "ClipboardCocoa.xib".

Note that this is only in the header for the sake of
Interface Builder, which will not synchronize with
changes to an interface declared in a ".mm" file.
*/
@interface Clipboard_WindowController : NSWindowController
{
@public
	IBOutlet Clipboard_ContentView*		clipboardContent;
	IBOutlet NSView*					clipboardImageContainer;
	IBOutlet NSImageView*				clipboardImageContent;
	IBOutlet NSView*					clipboardTextContainer;
	IBOutlet NSTextView*				clipboardTextContent;
	IBOutlet NSTextField*				valueKind;
	IBOutlet NSTextField*				valueSize;
	IBOutlet NSTextField*				label1;
	IBOutlet NSTextField*				value1;
	IBOutlet NSTextField*				label2;
	IBOutlet NSTextField*				value2;
}

+ (id)sharedClipboardWindowController;

- (NSFont*)returnNSFontForMonospacedTextOfSize:(unsigned int)	fontSize;

- (void)setDataSize:(size_t)	dataSize;

- (void)setDataWidth:(size_t)	widthInPixels
		andHeight:(size_t)		heightInPixels;

- (void)setNeedsDisplay;

- (void)setKindField:(NSString*)	aString;

- (void)setLabel1:(NSString*)	labelString
		andValue:(NSString*)	valueString;

- (void)setLabel2:(NSString*)	labelString
		andValue:(NSString*)	valueString;

- (void)setShowImage:(BOOL)		flag;

- (void)setShowText:(BOOL)		flag;

- (void)setSizeField:(NSString*)	aString;

@end

#endif // __OBJC__


#pragma mark Public Methods

//!\name Initialization
//@{

void
	Clipboard_Init			();

void
	Clipboard_Done			();

//@}

//!\name Accessing Clipboard Data
//@{

OSStatus
	Clipboard_AddCFStringToPasteboard		(CFStringRef				inStringToCopy,
											 PasteboardRef				inPasteboardOrNullForMainClipboard = nullptr);

OSStatus
	Clipboard_AEDescToScrap					(AEDesc const*				inDescPtr);

Boolean
	Clipboard_Contains						(CFStringRef				inUTI,
											 UInt16						inDesiredItemOrZeroForAll,
											 CFStringRef&				outConformingItemActualType,
											 PasteboardItemID&			outConformingItemID,
											 PasteboardRef				inDataSourceOrNull = nullptr);

Boolean
	Clipboard_ContainsGraphics				(PasteboardRef				inWhatChangedOrNullForPrimaryPasteboard = nullptr);

Boolean
	Clipboard_ContainsText					(PasteboardRef				inWhatChangedOrNullForPrimaryPasteboard = nullptr);

Boolean
	Clipboard_CreateCFStringFromPasteboard	(CFStringRef&				outCFString,
											 CFStringRef&				outUTI,
											 PasteboardRef				inPasteboardOrNull = nullptr);

Boolean
	Clipboard_CreateCGImageFromPasteboard	(CGImageRef&				outImage,
											 CFStringRef&				outUTI,
											 PasteboardRef				inPasteboardOrNull = nullptr);

OSStatus
	Clipboard_CreateContentsAEDesc			(AEDesc*					outDescPtr);

void
	Clipboard_GraphicsToScrap				(VectorInterpreter_ID		inGraphicID);

Boolean
	Clipboard_GetData						(Clipboard_DataConstraint	inConstraint,
											 CFDataRef&					outData,
											 CFStringRef&				outConformingItemActualType,
											 PasteboardItemID&			outConformingItemID,
											 PasteboardRef				inDataSourceOrNull = nullptr);

PasteboardRef
	Clipboard_ReturnPrimaryPasteboard		();

void
	Clipboard_SetPasteboardModified			(PasteboardRef				inWhatChangedOrNullForPrimaryPasteboard = nullptr);

void
	Clipboard_TextFromScrap					(SessionRef					inSession,
											 Clipboard_Modifier			inFilter = kClipboard_ModifierNone,
											 PasteboardRef				inDataSourceOrNull = nullptr);

void
	Clipboard_TextToScrap					(TerminalViewRef			inView,
											 Clipboard_CopyMethod		inHowToCopy,
											 PasteboardRef				inDataTargetOrNull = nullptr);

void
	Clipboard_TextType						(TerminalViewRef			inSource,
											 SessionRef					inTarget);

//@}

//!\name Clipboard User Interface
//@{

void
	Clipboard_SetWindowVisible			(Boolean			inIsVisible);

Boolean
	Clipboard_WindowIsVisible			();

//@}

//!\name Utilities
//@{

Boolean
	Clipboard_IsOneLineInBuffer			(UInt8 const*		inTextPtr,
										 CFIndex			inLength);

Boolean
	Clipboard_IsOneLineInBuffer			(UInt16 const*		inTextPtr,
										 CFIndex			inLength);

//@}

#endif

// BELOW IS REQUIRED NEWLINE TO END FILE
