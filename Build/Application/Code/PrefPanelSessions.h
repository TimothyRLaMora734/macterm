/*!	\file PrefPanelSessions.h
	\brief Implements the Sessions panel of Preferences.
*/
/*###############################################################

	MacTerm
		© 1998-2013 by Kevin Grant.
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

#include <UniversalDefines.h>

#ifndef __PREFPANELSESSIONS__
#define __PREFPANELSESSIONS__

// application includes
#include "GenericPanelTabs.h"
#include "Panel.h"
#include "Preferences.h"
#ifdef __OBJC__
#	include "PreferenceValue.objc++.h"
#	include "PrefsContextManager.objc++.h"
#endif



#pragma mark Types

#ifdef __OBJC__

/*!
Loads a NIB file that defines a panel view with tabs
and provides the sub-panels that the tabs contain.

Note that this is only in the header for the sake of
Interface Builder, which will not synchronize with
changes to an interface declared in a ".mm" file.
*/
@interface PrefPanelSessions_ViewManager : GenericPanelTabs_ViewManager
{
}

@end


/*!
Manages bindings for the control-key preferences.
The only valid preference tags are those that store
raw control-key characters, such as
"kPreferences_TagKeyInterruptProcess".
*/
@interface PrefPanelSessions_ControlKeyValue : PreferenceValue_InheritedSingleTag

// designated initializer
- (id)
initWithPreferencesTag:(Preferences_Tag)_
contextManager:(PrefsContextManager_Object*)_;

// accessors

- (NSString*)
stringValue;
- (void)
setStringValue:(NSString*)_; // binding

@end


/*!
Manages bindings for the Emacs-meta-key mapping preference.
*/
@interface PrefPanelSessions_EmacsMetaValue : PreferenceValue_Array

// designated initializer
- (id)
initWithContextManager:(PrefsContextManager_Object*)_;

@end


/*!
Manages bindings for the new-line preference.
*/
@interface PrefPanelSessions_NewLineValue : PreferenceValue_Array

// designated initializer
- (id)
initWithContextManager:(PrefsContextManager_Object*)_;

@end


/*!
Loads a NIB file that defines the Keyboard pane.

Note that this is only in the header for the sake of
Interface Builder, which will not synchronize with
changes to an interface declared in a ".mm" file.
*/
@interface PrefPanelSessions_KeyboardViewManager : Panel_ViewManager< Panel_Delegate, PrefsWindow_PanelInterface >
{
@private
	PrefsContextManager_Object*		prefsMgr;
	NSRect							idealFrame;
	NSMutableDictionary*			byKey;
	BOOL							isEditingKeyInterruptProcess;
	BOOL							isEditingKeyResume;
	BOOL							isEditingKeySuspend;
}

// accessors

- (PreferenceValue_Flag*)
deleteKeySendsBackspace; // binding

- (PreferenceValue_Flag*)
emacsArrowKeys; // binding

- (BOOL)
isEditingKeyInterruptProcess; // binding

- (BOOL)
isEditingKeyResume; // binding

- (BOOL)
isEditingKeySuspend; // binding

- (PrefPanelSessions_ControlKeyValue*)
keyInterruptProcess; // binding

- (PrefPanelSessions_ControlKeyValue*)
keyResume; // binding

- (PrefPanelSessions_ControlKeyValue*)
keySuspend; // binding

- (PrefPanelSessions_EmacsMetaValue*)
mappingForEmacsMeta; // binding

- (PrefPanelSessions_NewLineValue*)
mappingForNewLine; // binding

// actions

- (IBAction)
performChooseInterruptProcessKey:(id)_; // binding

- (IBAction)
performChooseResumeKey:(id)_; // binding

- (IBAction)
performChooseSuspendKey:(id)_; // binding

@end

#endif // __OBJC__



#pragma mark Public Methods

Panel_Ref
	PrefPanelSessions_New						();

Panel_Ref
	PrefPanelSessions_NewDataFlowPane			();

Preferences_TagSetRef
	PrefPanelSessions_NewDataFlowPaneTagSet		();

Panel_Ref
	PrefPanelSessions_NewGraphicsPane			();

Preferences_TagSetRef
	PrefPanelSessions_NewGraphicsPaneTagSet		();

Panel_Ref
	PrefPanelSessions_NewKeyboardPane			();

Preferences_TagSetRef
	PrefPanelSessions_NewKeyboardPaneTagSet		();

Panel_Ref
	PrefPanelSessions_NewResourcePane			();

Preferences_TagSetRef
	PrefPanelSessions_NewResourcePaneTagSet		();

Preferences_TagSetRef
	PrefPanelSessions_NewTagSet					();

#endif

// BELOW IS REQUIRED NEWLINE TO END FILE
