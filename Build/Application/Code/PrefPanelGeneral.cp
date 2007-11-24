/*###############################################################

	PrefPanelGeneral.cp
	
	MacTelnet
		� 1998-2007 by Kevin Grant.
		� 2001-2003 by Ian Anderson.
		� 1986-1994 University of Illinois Board of Trustees
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
#include <cstring>

// Unix includes
#include <strings.h>

// Mac includes
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>

// library includes
#include <AlertMessages.h>
#include <CarbonEventHandlerWrap.template.h>
#include <CarbonEventUtilities.template.h>
#include <ColorUtilities.h>
#include <CommonEventHandlers.h>
#include <Console.h>
#include <DialogAdjust.h>
#include <HIViewWrap.h>
#include <HIViewWrapManip.h>
#include <Localization.h>
#include <MemoryBlocks.h>
#include <NIBLoader.h>
#include <RegionUtilities.h>

// resource includes
#include "ControlResources.h"
#include "DialogResources.h"
#include "GeneralResources.h"
#include "StringResources.h"
#include "SpacingConstants.r"

// MacTelnet includes
#include "AppResources.h"
#include "Commands.h"
#include "Configure.h" // GetApplicationType()
#include "ConstantsRegistry.h"
#include "DialogUtilities.h"
#include "Panel.h"
#include "Preferences.h"
#include "PrefPanelGeneral.h"
#include "SessionFactory.h"
#include "TerminalView.h"
#include "TerminalWindow.h"
#include "UIStrings.h"
#include "UIStrings_PrefsWindow.h"



#pragma mark Constants

#define NUMBER_OF_GENERAL_TABPANES			3
enum
{
	// must match tab order at creation, and be one-based
	kTabIndexGeneralOptions = 1,
	kTabIndexGeneralSpecial = 2,
	kTabIndexGeneralNotification = 3
};

/*!
IMPORTANT

The following values MUST agree with the view IDs in
the NIBs from the package "PrefPanels.nib".

In addition, they MUST be unique across all panels.
*/
static HIViewID const	idMyCheckBoxSimplifiedUI					= { FOUR_CHAR_CODE('SUIM'), 0/* ID */ };
static HIViewID const	idMyCheckBoxDoNotAutoClose					= { FOUR_CHAR_CODE('DACW'), 0/* ID */ };
static HIViewID const	idMyCheckBoxDoNotDimInactive				= { FOUR_CHAR_CODE('DDBW'), 0/* ID */ };
static HIViewID const	idMyCheckBoxUseTabsToArrangeWindows			= { FOUR_CHAR_CODE('UTAW'), 0/* ID */ };
static HIViewID const	idMyCheckBoxInvertSelectedText				= { FOUR_CHAR_CODE('ISel'), 0/* ID */ };
static HIViewID const	idMyCheckBoxAutoCopySelectedText			= { FOUR_CHAR_CODE('ACST'), 0/* ID */ };
static HIViewID const	idMyCheckBoxMoveCursorToDropArea			= { FOUR_CHAR_CODE('MCTD'), 0/* ID */ };
static HIViewID const	idMyCheckBoxMenuKeyEquivalents				= { FOUR_CHAR_CODE('MIKE'), 0/* ID */ };
static HIViewID const	idMyCheckBoxMapBackquoteToEscape			= { FOUR_CHAR_CODE('MBQE'), 0/* ID */ };
static HIViewID const	idMyCheckBoxDoNotAutoCreateWindows			= { FOUR_CHAR_CODE('DCNW'), 0/* ID */ };
static HIViewID const	idMyCheckBoxCursorFlashing					= { FOUR_CHAR_CODE('CurF'), 0/* ID */ };
static HIViewID const	idMyButtonCursorBlock						= { FOUR_CHAR_CODE('CrBl'), 0/* ID */ };
static HIViewID const	idMyButtonCursorVerticalBar					= { FOUR_CHAR_CODE('CrVB'), 0/* ID */ };
static HIViewID const	idMyButtonCursorUnderline					= { FOUR_CHAR_CODE('CrUn'), 0/* ID */ };
static HIViewID const	idMyButtonCursorBoldVerticalBar				= { FOUR_CHAR_CODE('CrBV'), 0/* ID */ };
static HIViewID const	idMyButtonCursorBoldUnderline				= { FOUR_CHAR_CODE('CrBU'), 0/* ID */ };
static HIViewID const	idMyFieldStackingOriginLeft					= { FOUR_CHAR_CODE('WSOL'), 0/* ID */ };
static HIViewID const	idMyFieldStackingOriginTop					= { FOUR_CHAR_CODE('WSOT'), 0/* ID */ };
static HIViewID const	idMyRadioButtonResizeAffectsScreenSize		= { FOUR_CHAR_CODE('WRSS'), 0/* ID */ };
static HIViewID const	idMyRadioButtonResizeAffectsFontSize		= { FOUR_CHAR_CODE('WRFS'), 0/* ID */ };
static HIViewID const	idMyHelpTextResizeEffect					= { FOUR_CHAR_CODE('HTWR'), 0/* ID */ };
static HIViewID const	idMyFieldCopyUsingSpacesForTabs				= { FOUR_CHAR_CODE('CUST'), 0/* ID */ };
static HIViewID const	idMyRadioButtonCommandNDefault				= { FOUR_CHAR_CODE('CNDf'), 0/* ID */ };
static HIViewID const	idMyRadioButtonCommandNLogInShell			= { FOUR_CHAR_CODE('CNSh'), 0/* ID */ };
static HIViewID const	idMyRadioButtonCommandNDialog				= { FOUR_CHAR_CODE('CNDg'), 0/* ID */ };
static HIViewID const	idMyPopUpMenuBellType						= { FOUR_CHAR_CODE('BSnd'), 0/* ID */ };
static HIViewID const	idMyCheckBoxVisualBell						= { FOUR_CHAR_CODE('VisB'), 0/* ID */ };
static HIViewID const	idMyHelpTextBellType						= { FOUR_CHAR_CODE('HTBT'), 0/* ID */ };
static HIViewID const	idMyCheckBoxMarginBell						= { FOUR_CHAR_CODE('MarB'), 0/* ID */ };
static HIViewID const	idMyCheckBoxNotifyTerminalBeeps				= { FOUR_CHAR_CODE('BelN'), 0/* ID */ };
static HIViewID const	idMyRadioButtonNotifyDoNothing				= { FOUR_CHAR_CODE('NotN'), 0/* ID */ };
static HIViewID const	idMyRadioButtonNotifyBadgeDockIcon			= { FOUR_CHAR_CODE('NotD'), 0/* ID */ };
static HIViewID const	idMyRadioButtonNotifyBounceDockIcon			= { FOUR_CHAR_CODE('NotB'), 0/* ID */ };
static HIViewID const	idMyRadioButtonNotifyDisplayMessage			= { FOUR_CHAR_CODE('NotM'), 0/* ID */ };

#pragma mark Types

/*!
Implements the �Notification� tab.
*/
struct MyGeneralTabNotification:
public HIViewWrap
{
public:
	MyGeneralTabNotification	(HIWindowRef);

protected:
	HIViewWrap
	createPaneView	(HIWindowRef) const;
	
	static void
	deltaSize	(HIViewRef, Float32, Float32, void*);
	
	//! you should prefer setCFTypeRef(), which is clearer
	inline CFRetainRelease&
	operator =	(CFRetainRelease const&);

private:
	CommonEventHandlers_HIViewResizer	containerResizer;
};

/*!
Implements the �Options� tab.
*/
struct MyGeneralTabOptions:
public HIViewWrap
{
public:
	MyGeneralTabOptions		(HIWindowRef);

protected:
	HIViewWrap
	createPaneView	(HIWindowRef) const;
	
	static void
	deltaSize	(HIViewRef, Float32, Float32, void*);
	
	//! you should prefer setCFTypeRef(), which is clearer
	inline CFRetainRelease&
	operator =	(CFRetainRelease const&);

private:
	CommonEventHandlers_HIViewResizer	containerResizer;
};

/*!
Implements the �Special� tab.
*/
struct MyGeneralTabSpecial:
public HIViewWrap
{
public:
	MyGeneralTabSpecial		(HIWindowRef);
	
	CarbonEventHandlerWrap		buttonCommandsHandler;		//!< invoked when a button is clicked

protected:
	HIViewWrap
	createPaneView	(HIWindowRef) const;
	
	static void
	deltaSize	(HIViewRef, Float32, Float32, void*);
	
	//! you should prefer setCFTypeRef(), which is clearer
	inline CFRetainRelease&
	operator =	(CFRetainRelease const&);

private:
	CommonEventHandlers_HIViewResizer	containerResizer;
};

/*!
Implements the entire panel user interface.
*/
struct MyGeneralPanelUI
{
public:
	MyGeneralPanelUI	(Panel_Ref, HIWindowRef);
	
	MyGeneralTabOptions					optionsTab;
	MyGeneralTabSpecial					specialTab;
	MyGeneralTabNotification			notificationTab;
	HIViewWrap							tabView;
	HIViewWrap							mainView;
	CommonEventHandlers_HIViewResizer	containerResizer;	//!< invoked when the panel is resized
	CarbonEventHandlerWrap				viewClickHandler;	//!< invoked when a tab is clicked

protected:
	HIViewWrap
	createContainerView		(Panel_Ref, HIWindowRef) const;
	
	HIViewWrap
	createTabsView	(HIWindowRef) const;
};
typedef MyGeneralPanelUI*			MyGeneralPanelUIPtr;
typedef MyGeneralPanelUI const*		MyGeneralPanelUIConstPtr;

/*!
Contains the panel reference and its user interface
(once the UI is constructed).
*/
struct MyGeneralPanelData
{
	MyGeneralPanelData ();
	
	Panel_Ref			panel;			//!< the panel this data is for
	MyGeneralPanelUI*	interfacePtr;	//!< if not nullptr, the panel user interface is active
};
typedef MyGeneralPanelData*		MyGeneralPanelDataPtr;

#pragma mark Internal Method Prototypes

static void				changePreferenceUpdateScreenTerminalWindowOp	(TerminalWindowRef, void*, SInt32, void*);
static void				deltaSizePanelContainerHIView					(HIViewRef, Float32, Float32, void*);
static void				disposePanel									(Panel_Ref, void*);
static SInt32			panelChanged									(Panel_Ref, Panel_Message, void*);
static pascal OSStatus	receiveHICommand								(EventHandlerCallRef, EventRef, void*);
static pascal OSStatus	receiveViewHit									(EventHandlerCallRef, EventRef, void*);
static void				savePreferenceForField							(Panel_Ref, HIViewRef);
static void				showTabPane										(MyGeneralPanelUIPtr, UInt16);
static Boolean			updateCheckBoxPreference						(MyGeneralPanelUIPtr, HIViewRef);

#pragma mark Variables

namespace // an unnamed namespace is the preferred replacement for "static" declarations in C++
{
	Float32		gIdealPanelWidth = 0.0;
	Float32		gIdealPanelHeight = 0.0;
	Float32		gMaximumTabPaneWidth = 0.0;
	Float32		gMaximumTabPaneHeight = 0.0;
}



#pragma mark Public Methods

/*!
Creates a new preference panel for the General
category, initializes it, and returns a reference
to it.  You must destroy the reference using
Panel_Dispose() when you are done with it.

If any problems occur, nullptr is returned.

(3.0)
*/
Panel_Ref
PrefPanelGeneral_New ()
{
	Panel_Ref	result = Panel_New(panelChanged);
	
	
	if (nullptr != result)
	{
		MyGeneralPanelDataPtr	dataPtr = new MyGeneralPanelData();
		CFStringRef				nameCFString = nullptr;
		
		
		Panel_SetKind(result, kConstantsRegistry_PrefPanelDescriptorGeneral);
		Panel_SetShowCommandID(result, kCommandDisplayPrefPanelGeneral);
		if (UIStrings_Copy(kUIStrings_PreferencesWindowGeneralCategoryName, nameCFString).ok())
		{
			Panel_SetName(result, nameCFString);
			CFRelease(nameCFString), nameCFString = nullptr;
		}
		Panel_SetIconRefFromBundleFile(result, AppResources_ReturnPrefPanelGeneralIconFilenameNoExtension(),
										kConstantsRegistry_ApplicationCreatorSignature,
										kConstantsRegistry_IconServicesIconPrefPanelGeneral);
		Panel_SetImplementation(result, dataPtr);
		dataPtr->panel = result;
	}
	return result;
}// New


#pragma mark Internal Methods

/*!
Initializes a MyGeneralPanelData structure.

(3.1)
*/
MyGeneralPanelData::
MyGeneralPanelData ()
:
// IMPORTANT: THESE ARE EXECUTED IN THE ORDER MEMBERS APPEAR IN THE CLASS.
panel(nullptr),
interfacePtr(nullptr)
{
}// MyGeneralPanelData default constructor


/*!
Initializes a MyFormatsPanelUI structure.

(3.1)
*/
MyGeneralPanelUI::
MyGeneralPanelUI	(Panel_Ref		inPanel,
					 HIWindowRef	inOwningWindow)
:
// IMPORTANT: THESE ARE EXECUTED IN THE ORDER MEMBERS APPEAR IN THE CLASS.
optionsTab			(inOwningWindow),
specialTab			(inOwningWindow),
notificationTab		(inOwningWindow),
tabView				(createTabsView(inOwningWindow)
						<< HIViewWrap_AssertExists),
mainView			(createContainerView(inPanel, inOwningWindow)
						<< HIViewWrap_AssertExists),
containerResizer	(mainView, kCommonEventHandlers_ChangedBoundsEdgeSeparationH |
								kCommonEventHandlers_ChangedBoundsEdgeSeparationV,
						deltaSizePanelContainerHIView, this/* context */),
viewClickHandler	(GetControlEventTarget(this->tabView), receiveViewHit,
						CarbonEventSetInClass(CarbonEventClass(kEventClassControl), kEventControlHit),
						this/* user data */)
{
	assert(containerResizer.isInstalled());
	assert(viewClickHandler.isInstalled());
}// MyGeneralPanelUI 2-argument constructor


/*!
Constructs the container for the panel.  Assumes that
the tabs view already exists.

(3.1)
*/
HIViewWrap
MyGeneralPanelUI::
createContainerView		(Panel_Ref		inPanel,
						 HIWindowRef	inOwningWindow)
const
{
	assert(this->tabView.exists());
	assert(0 != gMaximumTabPaneWidth);
	assert(0 != gMaximumTabPaneHeight);
	
	HIViewRef	result = nullptr;
	OSStatus	error = noErr;
	
	
	// create the container
	{
		Rect	containerBounds;
		
		
		SetRect(&containerBounds, 0, 0, 0, 0);
		error = CreateUserPaneControl(inOwningWindow, &containerBounds, kControlSupportsEmbedding, &result);
		assert_noerr(error);
		Panel_SetContainerView(inPanel, result);
		SetControlVisibility(result, false/* visible */, false/* draw */);
	}
	
	// calculate the ideal size
	{
		Point		tabFrameTopLeft;
		Point		tabFrameWidthHeight;
		Point		tabPaneTopLeft;
		Point		tabPaneBottomRight;
		
		
		// calculate initial frame and pane offsets (ignore width/height)
		Panel_CalculateTabFrame(result, &tabFrameTopLeft, &tabFrameWidthHeight);
		Panel_GetTabPaneInsets(&tabPaneTopLeft, &tabPaneBottomRight);
		
		gIdealPanelWidth = tabFrameTopLeft.h + tabPaneTopLeft.h + gMaximumTabPaneWidth +
							tabPaneBottomRight.h + tabFrameTopLeft.h/* right is same as left */;
		gIdealPanelHeight = tabFrameTopLeft.v + tabPaneTopLeft.v + gMaximumTabPaneHeight +
							tabPaneBottomRight.v + tabFrameTopLeft.v/* bottom is same as top */;
		
		// make the container big enough for the tabs
		{
			HIRect		containerFrame = CGRectMake(0, 0, gIdealPanelWidth, gIdealPanelHeight);
			
			
			error = HIViewSetFrame(result, &containerFrame);
			assert_noerr(error);
		}
		
		// recalculate the frame, this time the width and height will be correct
		Panel_CalculateTabFrame(result, &tabFrameTopLeft, &tabFrameWidthHeight);
		
		// make the tabs match the ideal frame, because the size
		// and position of NIB views is used to size subviews
		// and subview resizing deltas are derived directly from
		// changes to the container view size
		{
			HIRect		containerFrame = CGRectMake(tabFrameTopLeft.h, tabFrameTopLeft.v,
													tabFrameWidthHeight.h, tabFrameWidthHeight.v);
			
			
			error = HIViewSetFrame(this->tabView, &containerFrame);
			assert_noerr(error);
		}
	}
	
	// embed the tabs in the content pane; done at this stage
	// (after positioning the tabs) just in case the origin
	// of the container is not (0, 0); this prevents the tabs
	// from having to know where they will end up in the window
	error = HIViewAddSubview(result, this->tabView);
	assert_noerr(error);
	
	return result;
}// MyGeneralPanelUI::createContainerView


/*!
Constructs the container for all panel tab panes.
Assumes that all tabs already exist.

(3.1)
*/
HIViewWrap
MyGeneralPanelUI::
createTabsView	(HIWindowRef	inOwningWindow)
const
{
	assert(this->optionsTab.exists());
	assert(this->specialTab.exists());
	assert(this->notificationTab.exists());
	
	HIViewRef				result = nullptr;
	Rect					containerBounds;
	ControlTabEntry			tabInfo[NUMBER_OF_GENERAL_TABPANES];
	UIStrings_Result		stringResult = kUIStrings_ResultOK;
	OSStatus				error = noErr;
	
	
	// nullify or zero-fill everything, then set only what matters
	bzero(&tabInfo, sizeof(tabInfo));
	tabInfo[0].enabled =
		tabInfo[1].enabled =
		tabInfo[2].enabled = true;
	stringResult = UIStrings_Copy(kUIStrings_PreferencesWindowGeneralOptionsTabName,
									tabInfo[kTabIndexGeneralOptions - 1].name);
	stringResult = UIStrings_Copy(kUIStrings_PreferencesWindowGeneralSpecialTabName,
									tabInfo[kTabIndexGeneralSpecial - 1].name);
	stringResult = UIStrings_Copy(kUIStrings_PreferencesWindowGeneralNotificationTabName,
									tabInfo[kTabIndexGeneralNotification - 1].name);
	SetRect(&containerBounds, 0, 0, 0, 0);
	error = CreateTabsControl(inOwningWindow, &containerBounds, kControlTabSizeLarge, kControlTabDirectionNorth,
								sizeof(tabInfo) / sizeof(ControlTabEntry)/* number of tabs */, tabInfo,
								&result);
	assert_noerr(error);
	for (size_t i = 0; i < sizeof(tabInfo) / sizeof(ControlTabEntry); ++i)
	{
		if (nullptr != tabInfo[i].name) CFRelease(tabInfo[i].name), tabInfo[i].name = nullptr;
	}
	
	// calculate the largest area required for all tabs, and keep this as the ideal size
	{
		Rect		optionsTabSize;
		Rect		specialTabSize;
		Rect		notificationTabSize;
		Point		tabPaneTopLeft;
		Point		tabPaneBottomRight;
		
		
		// determine sizes of tabs from NIBs
		GetControlBounds(this->optionsTab, &optionsTabSize);
		GetControlBounds(this->specialTab, &specialTabSize);
		GetControlBounds(this->notificationTab, &notificationTabSize);
		
		// also include pane margin in panel size
		Panel_GetTabPaneInsets(&tabPaneTopLeft, &tabPaneBottomRight);
		
		// find the widest tab and the highest tab
		gMaximumTabPaneWidth = std::max(optionsTabSize.right - optionsTabSize.left,
										specialTabSize.right - specialTabSize.left);
		gMaximumTabPaneWidth = std::max(notificationTabSize.right - notificationTabSize.left,
										STATIC_CAST(gMaximumTabPaneWidth, int));
		gMaximumTabPaneHeight = std::max(optionsTabSize.bottom - optionsTabSize.top,
											specialTabSize.bottom - specialTabSize.top);
		gMaximumTabPaneHeight = std::max(notificationTabSize.bottom - notificationTabSize.top,
											STATIC_CAST(gMaximumTabPaneHeight, int));
		
		// make every tab pane match the ideal pane size
		{
			HIRect		containerFrame = CGRectMake(tabPaneTopLeft.h, tabPaneTopLeft.v,
													gMaximumTabPaneWidth, gMaximumTabPaneHeight);
			
			
			error = HIViewSetFrame(this->optionsTab, &containerFrame);
			assert_noerr(error);
			error = HIViewSetFrame(this->specialTab, &containerFrame);
			assert_noerr(error);
			error = HIViewSetFrame(this->notificationTab, &containerFrame);
			assert_noerr(error);
		}
		
		// make the tabs big enough for any of the panes
		{
			HIRect		containerFrame = CGRectMake(0, 0,
													tabPaneTopLeft.h + gMaximumTabPaneWidth + tabPaneBottomRight.h,
													tabPaneTopLeft.v + gMaximumTabPaneHeight + tabPaneBottomRight.v);
			
			
			error = HIViewSetFrame(result, &containerFrame);
			assert_noerr(error);
		}
		
		// embed every tab pane in the tabs view; done at this stage
		// so that the subsequent move of the tab frame (later) will
		// also offset the embedded panes; if embedding is done too
		// soon, then the panes have to know too much about where
		// they will physically reside within the window content area
		error = HIViewAddSubview(result, this->optionsTab);
		assert_noerr(error);
		error = HIViewAddSubview(result, this->specialTab);
		assert_noerr(error);
		error = HIViewAddSubview(result, this->notificationTab);
		assert_noerr(error);
	}
	
	return result;
}// MyGeneralPanelUI::createTabsView


/*!
Initializes a MyGeneralTabNotification structure.

(3.1)
*/
MyGeneralTabNotification::
MyGeneralTabNotification	(HIWindowRef	inOwningWindow)
:
// IMPORTANT: THESE ARE EXECUTED IN THE ORDER MEMBERS APPEAR IN THE CLASS.
HIViewWrap			(createPaneView(inOwningWindow)
						<< HIViewWrap_AssertExists),
containerResizer	(*this, kCommonEventHandlers_ChangedBoundsEdgeSeparationH,
						MyGeneralTabNotification::deltaSize, this/* context */)
{
	assert(exists());
	assert(containerResizer.isInstalled());
}// MyGeneralTabNotification 2-argument constructor


/*!
Constructs the HIView that resides within the tab, and
the sub-views that belong in its hierarchy.

(3.1)
*/
HIViewWrap
MyGeneralTabNotification::
createPaneView		(HIWindowRef	inOwningWindow)
const
{
	HIViewRef					result = nullptr;
	std::vector< HIViewRef >	viewList;
	Rect						dummy;
	Rect						idealContainerBounds;
	OSStatus					error = noErr;
	
	
	// create the tab pane
	SetRect(&dummy, 0, 0, 0, 0);
	error = CreateUserPaneControl(inOwningWindow, &dummy, kControlSupportsEmbedding, &result);
	assert_noerr(error);
	
	// create most HIViews for the tab based on the NIB
	error = DialogUtilities_CreateControlsBasedOnWindowNIB
			(CFSTR("PrefPanels"), CFSTR("General/Notification"), inOwningWindow,
					result/* parent */, viewList, idealContainerBounds);
	assert_noerr(error);
	
	// make the container match the ideal size, because the tabs view
	// will need this guideline when deciding its largest size
	{
		HIRect		containerFrame = CGRectMake(0, 0, idealContainerBounds.right - idealContainerBounds.left,
												idealContainerBounds.bottom - idealContainerBounds.top);
		
		
		error = HIViewSetFrame(result, &containerFrame);
		assert_noerr(error);
	}
	
	// initialize values
	{
		size_t		actualSize = 0;
		Boolean		visualBell = false;
		Boolean		marginBell = false;
		Boolean		notifyOfBeeps = false;
		
		
		unless (Preferences_GetData(kPreferences_TagVisualBell, sizeof(visualBell), &visualBell, &actualSize) ==
				kPreferences_ResultOK)
		{
			visualBell = false; // assume default, if preference can�t be found
		}
		unless (Preferences_GetData(kPreferences_TagMarginBell, sizeof(marginBell), &marginBell, &actualSize) ==
				kPreferences_ResultOK)
		{
			marginBell = false; // assume default, if preference can�t be found
		}
		unless (Preferences_GetData(kPreferences_TagNotifyOfBeeps, sizeof(notifyOfBeeps),
									&notifyOfBeeps, &actualSize) ==
				kPreferences_ResultOK)
		{
			notifyOfBeeps = false; // assume default, if preference can�t be found
		}
		
		//if (bell sound)
		//{ set up menu }
		// UNIMPLEMENTED
		
		SetControl32BitValue(HIViewWrap(idMyCheckBoxVisualBell, inOwningWindow), BooleanToCheckBoxValue(visualBell));
		SetControl32BitValue(HIViewWrap(idMyCheckBoxMarginBell, inOwningWindow), BooleanToCheckBoxValue(marginBell));
		SetControl32BitValue(HIViewWrap(idMyCheckBoxNotifyTerminalBeeps, inOwningWindow), BooleanToCheckBoxValue(notifyOfBeeps));
		
		// ...initialize radio buttons using user preferences
		{
			HIViewRef			selectedRadioButton = nullptr;
			HIViewWrap const	radioNotifyNothing(idMyRadioButtonNotifyDoNothing, inOwningWindow);
			HIViewWrap const	radioNotifyBadgeDockIcon(idMyRadioButtonNotifyBadgeDockIcon, inOwningWindow);
			HIViewWrap const	radioNotifyBounceDockIcon(idMyRadioButtonNotifyBounceDockIcon, inOwningWindow);
			HIViewWrap const	radioNotifyDisplayMessage(idMyRadioButtonNotifyDisplayMessage, inOwningWindow);
			UInt16				notificationPreferences = kAlert_NotifyDisplayDiamondMark;
			
			
			unless (Preferences_GetData(kPreferences_TagNotification, sizeof(notificationPreferences),
										&notificationPreferences, &actualSize) ==
					kPreferences_ResultOK)
			{
				notificationPreferences = kAlert_NotifyDisplayDiamondMark; // assume default, if preference can�t be found
			}
			SetControl32BitValue(radioNotifyNothing, kControlRadioButtonUncheckedValue);
			SetControl32BitValue(radioNotifyBadgeDockIcon, kControlRadioButtonUncheckedValue);
			SetControl32BitValue(radioNotifyBounceDockIcon, kControlRadioButtonUncheckedValue);
			SetControl32BitValue(radioNotifyDisplayMessage, kControlRadioButtonUncheckedValue);
			switch (notificationPreferences)
			{
			case kAlert_NotifyDoNothing:
				selectedRadioButton = radioNotifyNothing;
				break;
			
			case kAlert_NotifyDisplayDiamondMark:
				selectedRadioButton = radioNotifyBadgeDockIcon;
				break;
			
			case kAlert_NotifyDisplayIconAndDiamondMark:
				selectedRadioButton = radioNotifyBounceDockIcon;
				break;
			
			case kAlert_NotifyAlsoDisplayAlert:
				selectedRadioButton = radioNotifyDisplayMessage;
				break;
			
			default:
				// ???
				break;
			}
			
			if (nullptr != selectedRadioButton) SetControl32BitValue(selectedRadioButton, kControlRadioButtonCheckedValue);
		}
	}
	
	return result;
}// MyGeneralTabNotification::createPaneView


/*!
Resizes the views in this tab.

(3.1)
*/
void
MyGeneralTabNotification::
deltaSize	(HIViewRef		inContainer,
			 Float32		inDeltaX,
			 Float32		UNUSED_ARGUMENT(inDeltaY),
			 void*			UNUSED_ARGUMENT(inContext))
{
	HIWindowRef const		kPanelWindow = GetControlOwner(inContainer);
	//MyGeneralTabNotification*	dataPtr = REINTERPRET_CAST(inContext, MyGeneralTabNotification*);
	HIViewWrap				viewWrap;
	
	
	viewWrap = HIViewWrap(idMyHelpTextBellType, kPanelWindow);
	viewWrap << HIViewWrap_DeltaSize(inDeltaX, 0/* delta Y */);
}// MyGeneralTabNotification::deltaSize


/*!
Exists so the superclass assignment operator is
not hidden by an implicit assignment operator
definition.

(3.1)
*/
CFRetainRelease&
MyGeneralTabNotification::
operator =	(CFRetainRelease const&		inCopy)
{
	return HIViewWrap::operator =(inCopy);
}// MyGeneralTabNotification::operator =


/*!
Initializes a MyGeneralTabOptions structure.

(3.1)
*/
MyGeneralTabOptions::
MyGeneralTabOptions		(HIWindowRef	inOwningWindow)
:
// IMPORTANT: THESE ARE EXECUTED IN THE ORDER MEMBERS APPEAR IN THE CLASS.
HIViewWrap			(createPaneView(inOwningWindow)
						<< HIViewWrap_AssertExists),
containerResizer	(*this, kCommonEventHandlers_ChangedBoundsEdgeSeparationH,
						MyGeneralTabOptions::deltaSize, this/* context */)
{
	assert(exists());
	assert(containerResizer.isInstalled());
}// MyGeneralTabOptions 2-argument constructor


/*!
Constructs the HIView that resides within the tab, and
the sub-views that belong in its hierarchy.

(3.1)
*/
HIViewWrap
MyGeneralTabOptions::
createPaneView		(HIWindowRef	inOwningWindow)
const
{
	HIViewRef					result = nullptr;
	std::vector< HIViewRef >	viewList;
	Rect						dummy;
	Rect						idealContainerBounds;
	OSStatus					error = noErr;
	size_t						actualSize = 0L;
	Boolean						flag = false;
	
	
	// create the tab pane
	SetRect(&dummy, 0, 0, 0, 0);
	error = CreateUserPaneControl(inOwningWindow, &dummy, kControlSupportsEmbedding, &result);
	assert_noerr(error);
	
	// create most HIViews for the tab based on the NIB
	error = DialogUtilities_CreateControlsBasedOnWindowNIB
			(CFSTR("PrefPanels"), CFSTR("General/Options"), inOwningWindow,
					result/* parent */, viewList, idealContainerBounds);
	assert_noerr(error);
	
	// make the container match the ideal size, because the tabs view
	// will need this guideline when deciding its largest size
	{
		HIRect		containerFrame = CGRectMake(0, 0, idealContainerBounds.right - idealContainerBounds.left,
												idealContainerBounds.bottom - idealContainerBounds.top);
		
		
		error = HIViewSetFrame(result, &containerFrame);
		assert_noerr(error);
	}
	
	//
	// initialize checkboxes using user preferences
	//
	
	{
		HIViewWrap		checkBox(idMyCheckBoxSimplifiedUI, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagSimplifiedUserInterface, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume normal mode, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxDoNotAutoClose, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagDontAutoClose, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume windows automatically close, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxDoNotDimInactive, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagDontDimBackgroundScreens, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume background screens are dimmed, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxUseTabsToArrangeWindows, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagArrangeWindowsUsingTabs, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume background screens are dimmed, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxInvertSelectedText, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagPureInverse, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume text is highlighted according to Mac OS standards, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxAutoCopySelectedText, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagCopySelectedText, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume the clipboard isn�t affected by text highlighting, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxMoveCursorToDropArea, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagCursorMovesPriorToDrops, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume the cursor is not affected by drag and drop, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxMenuKeyEquivalents, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagMenuItemKeys, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = true; // assume menu items have key equivalents, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxMapBackquoteToEscape, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagMapBackquote, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume the backquote key isn�t re-mapped, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	{
		HIViewWrap		checkBox(idMyCheckBoxDoNotAutoCreateWindows, inOwningWindow);
		
		
		assert(checkBox.exists());
		unless (Preferences_GetData(kPreferences_TagDontAutoNewOnApplicationReopen, sizeof(flag), &flag,
									&actualSize) == kPreferences_ResultOK)
		{
			flag = false; // assume new windows are created automatically, if preference can�t be found
		}
		SetControl32BitValue(checkBox, BooleanToCheckBoxValue(flag));
	}
	return result;
}// MyGeneralTabOptions::createPaneView


/*!
Resizes the views in this tab.

(3.1)
*/
void
MyGeneralTabOptions::
deltaSize	(HIViewRef		UNUSED_ARGUMENT(inContainer),
			 Float32		UNUSED_ARGUMENT(inDeltaX),
			 Float32		UNUSED_ARGUMENT(inDeltaY),
			 void*			UNUSED_ARGUMENT(inContext))
{
	// nothing needed
}// MyGeneralTabOptions::deltaSize


/*!
Exists so the superclass assignment operator is
not hidden by an implicit assignment operator
definition.

(3.1)
*/
CFRetainRelease&
MyGeneralTabOptions::
operator =	(CFRetainRelease const&		inCopy)
{
	return HIViewWrap::operator =(inCopy);
}// MyGeneralTabOptions::operator =


/*!
Initializes a MyGeneralTabSpecial structure.

(3.1)
*/
MyGeneralTabSpecial::
MyGeneralTabSpecial		(HIWindowRef	inOwningWindow)
:
// IMPORTANT: THESE ARE EXECUTED IN THE ORDER MEMBERS APPEAR IN THE CLASS.
HIViewWrap				(createPaneView(inOwningWindow)
							<< HIViewWrap_AssertExists),
buttonCommandsHandler	(GetWindowEventTarget(inOwningWindow), receiveHICommand,
							CarbonEventSetInClass(CarbonEventClass(kEventClassCommand), kEventCommandProcess),
							nullptr/* user data */),
containerResizer		(*this, kCommonEventHandlers_ChangedBoundsEdgeSeparationH,
							MyGeneralTabSpecial::deltaSize, this/* context */)
{
	assert(exists());
	assert(buttonCommandsHandler.isInstalled());
	assert(containerResizer.isInstalled());
}// MyGeneralTabSpecial 2-argument constructor


/*!
Constructs the HIView that resides within the tab, and
the sub-views that belong in its hierarchy.

(3.1)
*/
HIViewWrap
MyGeneralTabSpecial::
createPaneView		(HIWindowRef	inOwningWindow)
const
{
	HIViewRef					result = nullptr;
	std::vector< HIViewRef >	viewList;
	Rect						dummy;
	Rect						idealContainerBounds;
	size_t						actualSize = 0L;
	OSStatus					error = noErr;
	
	
	// create the tab pane
	SetRect(&dummy, 0, 0, 0, 0);
	error = CreateUserPaneControl(inOwningWindow, &dummy, kControlSupportsEmbedding, &result);
	assert_noerr(error);
	
	// create most HIViews for the tab based on the NIB
	error = DialogUtilities_CreateControlsBasedOnWindowNIB
			(CFSTR("PrefPanels"), CFSTR("General/Special"), inOwningWindow,
					result/* parent */, viewList, idealContainerBounds);
	assert_noerr(error);
	
	// make the container match the ideal size, because the tabs view
	// will need this guideline when deciding its largest size
	{
		HIRect		containerFrame = CGRectMake(0, 0, idealContainerBounds.right - idealContainerBounds.left,
												idealContainerBounds.bottom - idealContainerBounds.top);
		
		
		error = HIViewSetFrame(result, &containerFrame);
		assert_noerr(error);
	}
	
	// set up the cursor shape bevel buttons
	{
		enum
		{
			kNumberOfButtons = 5
		};
		struct CursorButtonInfo
		{
			HIViewID		buttonID;
			UInt16			cursorType;
			HIViewRef		view;
		};
		TerminalView_CursorType		terminalCursorType = kTerminalView_CursorTypeBlock;
		struct CursorButtonInfo		cursorButtonIDs[kNumberOfButtons] =
									{
										{
											idMyButtonCursorBlock,
											kTerminalView_CursorTypeBlock,
											nullptr
										},
										{
											idMyButtonCursorVerticalBar,
											kTerminalView_CursorTypeVerticalLine,
											nullptr
										},
										{
											idMyButtonCursorBoldVerticalBar,
											kTerminalView_CursorTypeThickVerticalLine,
											nullptr
										},
										{
											idMyButtonCursorUnderline,
											kTerminalView_CursorTypeUnderscore,
											nullptr
										},
										{
											idMyButtonCursorBoldUnderline,
											kTerminalView_CursorTypeThickUnderscore,
											nullptr
										}
									};
		
		
		unless (Preferences_GetData(kPreferences_TagTerminalCursorType, sizeof(terminalCursorType),
									&terminalCursorType, &actualSize) == kPreferences_ResultOK)
		{
			terminalCursorType = kTerminalView_CursorTypeBlock; // assume a block-shaped cursor, if preference can�t be found
		}
		
		for (SInt16 i = 0; i < kNumberOfButtons; ++i)
		{
			cursorButtonIDs[i].view = HIViewWrap(cursorButtonIDs[i].buttonID, inOwningWindow);
			if (terminalCursorType == cursorButtonIDs[i].cursorType) SetControl32BitValue(cursorButtonIDs[i].view, kControlCheckBoxCheckedValue);
		}
	}
	{
		Boolean		cursorBlinks = false;
		
		
		unless (Preferences_GetData(kPreferences_TagCursorBlinks, sizeof(cursorBlinks),
									&cursorBlinks, &actualSize) ==
				kPreferences_ResultOK)
		{
			cursorBlinks = false; // assume the cursor doesn�t flash, if preference can�t be found
		}
		SetControl32BitValue(HIViewWrap(idMyCheckBoxCursorFlashing, inOwningWindow), BooleanToCheckBoxValue(cursorBlinks));
	}
	
	// ...create stacking origin�s controls and initialize using user preferences
	{
		HIViewWrap		fieldViewLeft(idMyFieldStackingOriginLeft, inOwningWindow);
		HIViewWrap		fieldViewTop(idMyFieldStackingOriginTop, inOwningWindow);
		Point			stackingOrigin;
		
		
		unless (Preferences_GetData(kPreferences_TagWindowStackingOrigin, sizeof(stackingOrigin),
									&stackingOrigin, &actualSize) ==
				kPreferences_ResultOK)
		{
			SetPt(&stackingOrigin, 40, 40); // assume a default, if preference can�t be found
		}
		SetControlNumericalText(fieldViewLeft, stackingOrigin.h);
		SetControlNumericalText(fieldViewTop, stackingOrigin.v);
		fieldViewLeft << HIViewWrap_InstallKeyFilter(NumericalLimiterKeyFilterUPP());
		fieldViewTop << HIViewWrap_InstallKeyFilter(NumericalLimiterKeyFilterUPP());
	}
	
	// set window resize preferences
	{
		HIViewWrap	radioButtonScreenSize(idMyRadioButtonResizeAffectsScreenSize, inOwningWindow);
		HIViewWrap	radioButtonFontSize(idMyRadioButtonResizeAffectsFontSize, inOwningWindow);
		Boolean		affectsFontSize = false;
		
		
		unless (Preferences_GetData(kPreferences_TagTerminalResizeAffectsFontSize,
									sizeof(affectsFontSize), &affectsFontSize,
									&actualSize) ==
				kPreferences_ResultOK)
		{
			affectsFontSize = false; // assume default, if preference can�t be found
		}
		SetControl32BitValue(radioButtonScreenSize, (false == affectsFontSize)
													? kControlRadioButtonCheckedValue
													: kControlRadioButtonUncheckedValue);
		SetControl32BitValue(radioButtonFontSize, (affectsFontSize)
													? kControlRadioButtonCheckedValue
													: kControlRadioButtonUncheckedValue);
	}
	
	// ...create �Copy Using Spaces For Tabs� controls and initialize using user preferences
	{
		HIViewWrap	fieldView(idMyFieldCopyUsingSpacesForTabs, inOwningWindow);
		UInt16		copyTableThreshold = 0;
		
		
		unless (Preferences_GetData(kPreferences_TagCopyTableThreshold, sizeof(copyTableThreshold),
									&copyTableThreshold, &actualSize) ==
				kPreferences_ResultOK)
		{
			copyTableThreshold = 4; // assume 4 spaces per tab, if preference can�t be found
		}
		SetControlNumericalText(fieldView, copyTableThreshold);
		fieldView << HIViewWrap_InstallKeyFilter(NumericalLimiterKeyFilterUPP());
	}
	
	// ...initialize command-N radio buttons using user preferences
	{
		HIViewWrap	radioButtonDefault(idMyRadioButtonCommandNDefault, inOwningWindow);
		HIViewWrap	radioButtonLogInShell(idMyRadioButtonCommandNLogInShell, inOwningWindow);
		HIViewWrap	radioButtonDialog(idMyRadioButtonCommandNDialog, inOwningWindow);
		UInt32		newCommandShortcutEffect = kCommandNewSessionShell;
		
		
		unless (Preferences_GetData(kPreferences_TagNewCommandShortcutEffect,
									sizeof(newCommandShortcutEffect), &newCommandShortcutEffect,
									&actualSize) ==
				kPreferences_ResultOK)
		{
			newCommandShortcutEffect = kCommandNewSessionShell; // assume default, if preference can�t be found
		}
		SetControl32BitValue(radioButtonDefault, kControlRadioButtonUncheckedValue);
		SetControl32BitValue(radioButtonLogInShell, kControlRadioButtonUncheckedValue);
		SetControl32BitValue(radioButtonDialog, kControlRadioButtonUncheckedValue);
		switch (newCommandShortcutEffect)
		{
		case kCommandNewSessionDefaultFavorite:
			SetControl32BitValue(radioButtonDefault, kControlRadioButtonCheckedValue);
			break;
		
		case kCommandNewSessionShell:
			SetControl32BitValue(radioButtonLogInShell, kControlRadioButtonCheckedValue);
			break;
		
		case kCommandNewSessionDialog:
			SetControl32BitValue(radioButtonDialog, kControlRadioButtonCheckedValue);
			break;
		
		default:
			// ???
			break;
		}
	}
	
	return result;
}// MyGeneralTabSpecial::createPaneView


/*!
Resizes the views in this tab.

(3.1)
*/
void
MyGeneralTabSpecial::
deltaSize	(HIViewRef		inContainer,
			 Float32		inDeltaX,
			 Float32		UNUSED_ARGUMENT(inDeltaY),
			 void*			UNUSED_ARGUMENT(inContext))
{
	HIWindowRef const		kPanelWindow = GetControlOwner(inContainer);
	//MyGeneralTabSpecial*	dataPtr = REINTERPRET_CAST(inContext, MyGeneralTabSpecial*);
	HIViewWrap				viewWrap;
	
	
	viewWrap = HIViewWrap(idMyHelpTextResizeEffect, kPanelWindow);
	viewWrap << HIViewWrap_DeltaSize(inDeltaX, 0/* delta Y */);
}// MyGeneralTabSpecial::deltaSize


/*!
Exists so the superclass assignment operator is
not hidden by an implicit assignment operator
definition.

(3.1)
*/
CFRetainRelease&
MyGeneralTabSpecial::
operator =	(CFRetainRelease const&		inCopy)
{
	return HIViewWrap::operator =(inCopy);
}// MyGeneralTabSpecial::operator =


/*!
This method, of SessionFactory_TerminalWindowOpProcPtr
form, will update the specified window�s terminal
screens appropriately based on the value of the
preference indicated by the given General preference
tag.

Currently, this method only supports changing of
the �use background picture� or �don�t dim background
session windows� preferences.  If one of these tags
is given, then the specified screen�s port rectangle
is invalidated (which will cause the picture to
appear or disappear).  In the case of a background
picture, the per-screen flag is also updated to
reflect the preference value.

(3.0)
*/
static void
changePreferenceUpdateScreenTerminalWindowOp	(TerminalWindowRef		inTerminalWindow,
												 void*					UNUSED_ARGUMENT(inUnusedData1),
												 SInt32					inDataPreferenceTag,
												 void*					UNUSED_ARGUMENT(inoutUndefinedResultPtr))
{
	switch (inDataPreferenceTag)
	{
	case kPreferences_TagArrangeWindowsUsingTabs:
		// UNIMPLEMENTED - move windows into or out of tabs if necessary
		break;
	
	case kPreferences_TagDontDimBackgroundScreens:
	case kPreferences_TagPureInverse:
		// update the entire terminal window, which will reflect the change
		RegionUtilities_RedrawWindowOnNextUpdate(TerminalWindow_ReturnWindow(inTerminalWindow));
		break;
	
	default:
		// unrecognized tag
		break;
	}
}// changePreferenceUpdateScreenTerminalWindowOp


/*!
Adjusts the controls in the �General� preference panel
to match the specified change in dimensions of its
container. 

(3.1)
*/
static void
deltaSizePanelContainerHIView	(HIViewRef		UNUSED_ARGUMENT(inView),
								 Float32		inDeltaX,
								 Float32		inDeltaY,
								 void*			inContext)
{
	if ((0 != inDeltaX) || (0 != inDeltaY))
	{
		//HIWindowRef				kPanelWindow = GetControlOwner(inView);
		MyGeneralPanelUIPtr		interfacePtr = REINTERPRET_CAST(inContext, MyGeneralPanelUIPtr);
		assert(nullptr != interfacePtr);
		
		
		interfacePtr->tabView << HIViewWrap_DeltaSize(inDeltaX, inDeltaY);
		
		// due to event handlers, this will automatically resize subviews too
		interfacePtr->optionsTab << HIViewWrap_DeltaSize(inDeltaX, inDeltaY);
		interfacePtr->specialTab << HIViewWrap_DeltaSize(inDeltaX, inDeltaY);
		interfacePtr->notificationTab << HIViewWrap_DeltaSize(inDeltaX, inDeltaY);
	}
}// deltaSizePanelContainerHIView


/*!
Cleans up a panel that is about to be destroyed.

(3.0)
*/
static void
disposePanel	(Panel_Ref		UNUSED_ARGUMENT(inPanel),
				 void*			inDataPtr)
{
	MyGeneralPanelDataPtr	dataPtr = REINTERPRET_CAST(inDataPtr, MyGeneralPanelDataPtr);
	
	
	// destroy UI, if present
	if (nullptr != dataPtr->interfacePtr) delete dataPtr->interfacePtr;
	
	delete dataPtr;
}// disposePanel


/*!
This routine, of standard PanelChangedProcPtr form,
is invoked by the Panel module whenever a property
of one of the preferences dialog�s panels changes.

(3.0)
*/
static SInt32
panelChanged	(Panel_Ref			inPanel,
				 Panel_Message		inMessage,
				 void*				inDataPtr)
{
	SInt32		result = 0L;
	assert(kCFCompareEqualTo == CFStringCompare(Panel_ReturnKind(inPanel),
												kConstantsRegistry_PrefPanelDescriptorGeneral, 0/* options */));
	
	
	switch (inMessage)
	{
	case kPanel_MessageCreateViews: // specification of the window containing the panel - create controls using this window
		{
			MyGeneralPanelDataPtr	panelDataPtr = REINTERPRET_CAST(Panel_ReturnImplementation(inPanel),
																	MyGeneralPanelDataPtr);
			WindowRef const*		windowPtr = REINTERPRET_CAST(inDataPtr, WindowRef*);
			
			
			// create the rest of the panel user interface
			panelDataPtr->interfacePtr = new MyGeneralPanelUI(inPanel, *windowPtr);
			assert(nullptr != panelDataPtr->interfacePtr);
			showTabPane(panelDataPtr->interfacePtr, 1/* tab index */);
		}
		break;
	
	case kPanel_MessageDestroyed: // request to dispose of private data structures
		{
			void*	panelAuxiliaryDataPtr = inDataPtr;
			
			
			disposePanel(inPanel, panelAuxiliaryDataPtr);
		}
		break;
	
	case kPanel_MessageFocusGained: // notification that a control is now focused
		{
			//HIViewRef const*	controlPtr = REINTERPRET_CAST(inDataPtr, HIViewRef*);
			
			
			// do nothing
		}
		break;
	
	case kPanel_MessageFocusLost: // notification that a control is no longer focused
		{
			HIViewRef const*	controlPtr = REINTERPRET_CAST(inDataPtr, HIViewRef*);
			
			
			savePreferenceForField(inPanel, *controlPtr);
		}
		break;
	
	case kPanel_MessageGetIdealSize: // request for panel to return its required dimensions in pixels (after control creation)
		{
			HISize&		newLimits = *(REINTERPRET_CAST(inDataPtr, HISize*));
			
			
			if ((0 != gIdealPanelWidth) && (0 != gIdealPanelHeight))
			{
				newLimits.width = gIdealPanelWidth;
				newLimits.height = gIdealPanelHeight;
				result = kPanel_ResponseSizeProvided;
			}
		}
		break;
	
	case kPanel_MessageNewAppearanceTheme: // notification of theme switch, a request to recalculate control sizes
		{
			// this notification is currently ignored, but shouldn�t be...
		}
		break;
	
	case kPanel_MessageNewVisibility: // visible state of the panel�s container has changed to visible (true) or invisible (false)
		{
			//Boolean		isNowVisible = *((Boolean*)inDataPtr);
			
			
			// do nothing
		}
		break;
	
	default:
		break;
	}
	
	return result;
}// panelChanged


/*!
Handles "kEventCommandProcess" of "kEventClassCommand"
for the buttons in this panel.

(3.1)
*/
static pascal OSStatus
receiveHICommand	(EventHandlerCallRef	UNUSED_ARGUMENT(inHandlerCallRef),
					 EventRef				inEvent,
					 void*					UNUSED_ARGUMENT(inContext))
{
	OSStatus		result = eventNotHandledErr;
	UInt32 const	kEventClass = GetEventClass(inEvent);
	UInt32 const	kEventKind = GetEventKind(inEvent);
	
	
	assert(kEventClass == kEventClassCommand);
	assert(kEventKind == kEventCommandProcess);
	{
		HICommandExtended	received;
		
		
		// determine the command in question
		result = CarbonEventUtilities_GetEventParameter(inEvent, kEventParamDirectObject, typeHICommand, received);
		
		// if the command information was found, proceed
		if (noErr == result)
		{
			switch (received.commandID)
			{
			case kCommandPrefCursorBlock:
			case kCommandPrefCursorUnderline:
			case kCommandPrefCursorVerticalBar:
			case kCommandPrefCursorThickUnderline:
			case kCommandPrefCursorThickVerticalBar:
				{
					assert(0 != (received.attributes & kHICommandFromControl));
					HIViewRef					fromView = received.source.control;
					TerminalView_CursorType		cursorType = kTerminalView_CursorTypeBlock;
					
					
					SetControl32BitValue(HIViewWrap(idMyButtonCursorBlock, GetControlOwner(fromView)),
											kControlCheckBoxUncheckedValue);
					SetControl32BitValue(HIViewWrap(idMyButtonCursorVerticalBar, GetControlOwner(fromView)),
											kControlCheckBoxUncheckedValue);
					SetControl32BitValue(HIViewWrap(idMyButtonCursorUnderline, GetControlOwner(fromView)),
											kControlCheckBoxUncheckedValue);
					SetControl32BitValue(HIViewWrap(idMyButtonCursorBoldVerticalBar, GetControlOwner(fromView)),
											kControlCheckBoxUncheckedValue);
					SetControl32BitValue(HIViewWrap(idMyButtonCursorBoldUnderline, GetControlOwner(fromView)),
											kControlCheckBoxUncheckedValue);
					if (kCommandPrefCursorBlock == received.commandID)
					{
						cursorType = kTerminalView_CursorTypeBlock;
						SetControl32BitValue(fromView, kControlCheckBoxCheckedValue);
					}
					if (kCommandPrefCursorUnderline == received.commandID)
					{
						cursorType = kTerminalView_CursorTypeUnderscore;
						SetControl32BitValue(fromView, kControlCheckBoxCheckedValue);
					}
					if (kCommandPrefCursorVerticalBar == received.commandID)
					{
						cursorType = kTerminalView_CursorTypeVerticalLine;
						SetControl32BitValue(fromView, kControlCheckBoxCheckedValue);
					}
					if (kCommandPrefCursorThickUnderline == received.commandID)
					{
						cursorType = kTerminalView_CursorTypeThickUnderscore;
						SetControl32BitValue(fromView, kControlCheckBoxCheckedValue);
					}
					if (kCommandPrefCursorThickVerticalBar == received.commandID)
					{
						cursorType = kTerminalView_CursorTypeThickVerticalLine;
						SetControl32BitValue(fromView, kControlCheckBoxCheckedValue);
					}
					Preferences_SetData(kPreferences_TagTerminalCursorType, sizeof(cursorType), &cursorType);
				}
				break;
			
			default:
				// must return "eventNotHandledErr" here, or (for example) the user
				// wouldn�t be able to select menu commands while the window is open
				result = eventNotHandledErr;
				break;
			}
		}
	}
	
	return result;
}// receiveHICommand


/*!
Handles "kEventControlClick" of "kEventClassControl"
for this preferences panel.  Responds by changing
the currently selected tab, etc.

Also, temporarily, this handles clicks in other
controls.  Eventually, the buttons will simply have
commands associated with them, and a command handler
will be installed instead.

(3.1)
*/
static pascal OSStatus
receiveViewHit	(EventHandlerCallRef	UNUSED_ARGUMENT(inHandlerCallRef),
				 EventRef				inEvent,
				 void*					inMyGeneralPanelUIPtr)
{
	OSStatus				result = eventNotHandledErr;
	MyGeneralPanelUIPtr		interfacePtr = REINTERPRET_CAST(inMyGeneralPanelUIPtr, MyGeneralPanelUIPtr);
	assert(nullptr != interfacePtr);
	UInt32 const			kEventClass = GetEventClass(inEvent);
	UInt32 const			kEventKind = GetEventKind(inEvent);
	
	
	assert(kEventClass == kEventClassControl);
	assert(kEventKind == kEventControlHit);
	{
		HIViewRef	view = nullptr;
		
		
		// determine the control in question
		result = CarbonEventUtilities_GetEventParameter(inEvent, kEventParamDirectObject, typeControlRef, view);
		
		// if the control was found, proceed
		if (noErr == result)
		{
			result = eventNotHandledErr; // unless set otherwise
			
			if (view == interfacePtr->tabView)
			{
				showTabPane(interfacePtr, GetControl32BitValue(view));
				result = noErr; // completely handled
			}
			else
			{
				ControlKind		controlKind;
				OSStatus		error = GetControlKind(view, &controlKind);
				
				
				if ((noErr == error) && (kControlKindSignatureApple == controlKind.signature) &&
					((kControlKindCheckBox == controlKind.kind) || (kControlKindRadioButton == controlKind.kind)))
				{
					(Boolean)updateCheckBoxPreference(interfacePtr, view);
				}
			}
		}
	}
	
	return result;
}// receiveViewHit


/*!
Updates the preferences in memory to reflect the
information in the specified text field.  This
should be done if the focus of the window changes
(by hitting the tab key or clicking in another
text field).

(3.0)
*/
static void
savePreferenceForField	(Panel_Ref	inPanel,
						 HIViewRef	inView)
{
	MyGeneralPanelDataPtr	dataPtr = REINTERPRET_CAST(Panel_ReturnImplementation(inPanel), MyGeneralPanelDataPtr);
	MyGeneralPanelUIPtr		interfacePtr = dataPtr->interfacePtr;
	assert(nullptr != interfacePtr);
	
	
	if ((nullptr != inView) && (nullptr != dataPtr))
	{
		HIViewIDWrap	viewID(HIViewWrap(inView).identifier());
		
		
		if ((HIViewIDWrap(idMyFieldStackingOriginLeft) == viewID) ||
			(HIViewIDWrap(idMyFieldStackingOriginTop) == viewID))
		{
			HIViewWrap	fieldLeft(idMyFieldStackingOriginLeft, GetControlOwner(inView));
			assert(fieldLeft.exists());
			HIViewWrap	fieldTop(idMyFieldStackingOriginTop, GetControlOwner(inView));
			assert(fieldTop.exists());
			SInt32		value1 = 0L;
			SInt32		value2 = 0L;
			Point		prefValue;
			
			
			GetControlNumericalText(fieldLeft, &value1);
			GetControlNumericalText(fieldTop, &value2);
			SetPt(&prefValue, STATIC_CAST(value1, SInt16), STATIC_CAST(value2, SInt16));
			Preferences_SetData(kPreferences_TagWindowStackingOrigin, sizeof(prefValue), &prefValue);
			TerminalWindow_StackWindows(); // re-stack windows so the user can see the effect of the change
		}
		else if (HIViewIDWrap(idMyFieldCopyUsingSpacesForTabs) == viewID)
		{
			SInt32		value = 0L;
			UInt16		threshold = 0;
			
			
			GetControlNumericalText(inView, &value);
			threshold = value;
			Preferences_SetData(kPreferences_TagCopyTableThreshold, sizeof(threshold), &threshold);
		}
		else
		{
			// not a text field - ignore
		}
	}
}// savePreferenceForField


/*!
Displays the specified tab pane and hides the others.

(3.1)
*/
static void
showTabPane		(MyGeneralPanelUIPtr	inUIPtr,
				 UInt16					inTabIndex)
{
	HIViewRef	selectedTabPane = nullptr;
	
	
	if (kTabIndexGeneralOptions == inTabIndex)
	{
		selectedTabPane = inUIPtr->optionsTab;
		assert_noerr(HIViewSetVisible(inUIPtr->specialTab, false/* visible */));
		assert_noerr(HIViewSetVisible(inUIPtr->notificationTab, false/* visible */));
	}
	else if (kTabIndexGeneralSpecial == inTabIndex)
	{
		selectedTabPane = inUIPtr->specialTab;
		assert_noerr(HIViewSetVisible(inUIPtr->optionsTab, false/* visible */));
		assert_noerr(HIViewSetVisible(inUIPtr->notificationTab, false/* visible */));
	}
	else if (kTabIndexGeneralNotification == inTabIndex)
	{
		selectedTabPane = inUIPtr->notificationTab;
		assert_noerr(HIViewSetVisible(inUIPtr->optionsTab, false/* visible */));
		assert_noerr(HIViewSetVisible(inUIPtr->specialTab, false/* visible */));
	}
	else
	{
		assert(false && "not a recognized tab index");
	}
	
	if (nullptr != selectedTabPane)
	{
		assert_noerr(HIViewSetVisible(selectedTabPane, true/* visible */));
	}
}// showTabPane


/*!
Call this method when a click in a checkbox or
radio button has been detected AND the control
value has been toggled to its new value.

The appropriate preference will have been updated
in memory using Preferences_SetData().

If the specified view is �known�, "true" is
returned to indicate that the click was handled.
Otherwise, "false" is returned.

(3.0)
*/
static Boolean
updateCheckBoxPreference	(MyGeneralPanelUIPtr	inInterfacePtr,
							 HIViewRef				inCheckBoxClicked)
{
	Boolean		result = false;
	
	
	if (nullptr != inInterfacePtr)
	{
		WindowRef const		kWindow = GetControlOwner(inCheckBoxClicked);
		assert(IsValidWindowRef(kWindow));
		HIViewIDWrap		viewID(HIViewWrap(inCheckBoxClicked).identifier());
		Boolean				checkBoxFlagValue = (GetControl32BitValue(inCheckBoxClicked) == kControlCheckBoxCheckedValue);
		UInt16				chosenTabIndex = STATIC_CAST(GetControl32BitValue(inInterfacePtr->tabView), UInt16);
		
		
		switch (chosenTabIndex)
		{
		case kTabIndexGeneralOptions:
			if (HIViewIDWrap(idMyCheckBoxSimplifiedUI) == viewID)
			{
				Preferences_SetData(kPreferences_TagSimplifiedUserInterface,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxDoNotAutoClose) == viewID)
			{
				Preferences_SetData(kPreferences_TagDontAutoClose,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxDoNotDimInactive) == viewID)
			{
				Preferences_SetData(kPreferences_TagDontDimBackgroundScreens,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				SessionFactory_ForEveryTerminalWindowDo(changePreferenceUpdateScreenTerminalWindowOp,
														nullptr/* undefined */, kPreferences_TagDontDimBackgroundScreens,
														nullptr/* undefined */);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxUseTabsToArrangeWindows) == viewID)
			{
				Preferences_SetData(kPreferences_TagArrangeWindowsUsingTabs,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				SessionFactory_ForEveryTerminalWindowDo(changePreferenceUpdateScreenTerminalWindowOp,
														nullptr/* undefined */, kPreferences_TagArrangeWindowsUsingTabs,
														nullptr/* undefined */);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxInvertSelectedText) == viewID)
			{
				Preferences_SetData(kPreferences_TagPureInverse,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				// there�s no real reason to do this, since background window text selections will not
				// have an inverted appearance anyway; re-rendering them all wouldn�t change anything
				//SessionFactory_ForEveryTerminalWindowDo(changePreferenceUpdateScreenTerminalWindowOp,
				//										nullptr/* undefined */, kPreferences_TagPureInverse,
				//										nullptr/* undefined */);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxAutoCopySelectedText) == viewID)
			{
				Preferences_SetData(kPreferences_TagCopySelectedText,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxMoveCursorToDropArea) == viewID)
			{
				Preferences_SetData(kPreferences_TagCursorMovesPriorToDrops,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxMenuKeyEquivalents) == viewID)
			{
				Preferences_SetData(kPreferences_TagMenuItemKeys,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxMapBackquoteToEscape) == viewID)
			{
				Preferences_SetData(kPreferences_TagMapBackquote,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			else if (HIViewIDWrap(idMyCheckBoxDoNotAutoCreateWindows) == viewID)
			{
				Preferences_SetData(kPreferences_TagDontAutoNewOnApplicationReopen,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			break;
		
		case kTabIndexGeneralSpecial:
			if (HIViewIDWrap(idMyCheckBoxCursorFlashing) == viewID)
			{
				// save the new value
				Preferences_SetData(kPreferences_TagCursorBlinks,
									sizeof(checkBoxFlagValue), &checkBoxFlagValue);
				result = true;
			}
			else
			{
				// check if any of the radio buttons was hit; if not, check for other control hits
				HIViewWrap		radioButtonCommandNDefault(idMyRadioButtonCommandNDefault, kWindow);
				HIViewWrap		radioButtonCommandNLogInShell(idMyRadioButtonCommandNLogInShell, kWindow);
				HIViewWrap		radioButtonCommandNDialog(idMyRadioButtonCommandNDialog, kWindow);
				UInt32			newCommandShortcutEffect = 0;
				
				
				if (HIViewIDWrap(radioButtonCommandNDefault.identifier()) == viewID)
				{
					newCommandShortcutEffect = kCommandNewSessionDefaultFavorite;
					SetControl32BitValue(radioButtonCommandNLogInShell, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonCommandNDialog, kControlRadioButtonUncheckedValue);
				}
				else if (HIViewIDWrap(radioButtonCommandNLogInShell.identifier()) == viewID)
				{
					newCommandShortcutEffect = kCommandNewSessionShell;
					SetControl32BitValue(radioButtonCommandNDefault, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonCommandNDialog, kControlRadioButtonUncheckedValue);
				}
				else if (HIViewIDWrap(radioButtonCommandNDialog.identifier()) == viewID)
				{
					newCommandShortcutEffect = kCommandNewSessionDialog;
					SetControl32BitValue(radioButtonCommandNDefault, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonCommandNLogInShell, kControlRadioButtonUncheckedValue);
				}
				else
				{
					// unrecognized radio button
					newCommandShortcutEffect = 0;
				}
				
				if (0 != newCommandShortcutEffect)
				{
					Preferences_SetData(kPreferences_TagNewCommandShortcutEffect,
										sizeof(newCommandShortcutEffect), &newCommandShortcutEffect);
					result = true;
				}
				
				HIViewWrap		radioButtonResizeAffectsScreenSize(idMyRadioButtonResizeAffectsScreenSize, kWindow);
				HIViewWrap		radioButtonResizeAffectsFontSize(idMyRadioButtonResizeAffectsFontSize, kWindow);
				Boolean			resizeAffectsFontSize = false;
				
				
				if (HIViewIDWrap(radioButtonResizeAffectsScreenSize.identifier()) == viewID)
				{
					resizeAffectsFontSize = false;
					Preferences_SetData(kPreferences_TagTerminalResizeAffectsFontSize,
										sizeof(resizeAffectsFontSize), &resizeAffectsFontSize);
					SetControl32BitValue(radioButtonResizeAffectsFontSize, kControlRadioButtonUncheckedValue);
					result = true;
				}
				else if (HIViewIDWrap(radioButtonResizeAffectsFontSize.identifier()) == viewID)
				{
					resizeAffectsFontSize = true;
					Preferences_SetData(kPreferences_TagTerminalResizeAffectsFontSize,
										sizeof(resizeAffectsFontSize), &resizeAffectsFontSize);
					SetControl32BitValue(radioButtonResizeAffectsScreenSize, kControlRadioButtonUncheckedValue);
					result = true;
				}
			}
			break;
		
		case kTabIndexGeneralNotification:
			{
				HIViewWrap		radioButtonNotificationNone(idMyRadioButtonNotifyDoNothing, kWindow);
				HIViewWrap		radioButtonNotificationBadge(idMyRadioButtonNotifyBadgeDockIcon, kWindow);
				HIViewWrap		radioButtonNotificationBounce(idMyRadioButtonNotifyBounceDockIcon, kWindow);
				HIViewWrap		radioButtonNotificationDialog(idMyRadioButtonNotifyDisplayMessage, kWindow);
				
				
				if (HIViewIDWrap(radioButtonNotificationNone.identifier()) == viewID)
				{
					SInt16		newNotificationType = kAlert_NotifyDoNothing;
					
					
					Preferences_SetData(kPreferences_TagNotification,
										sizeof(newNotificationType), &newNotificationType);
					SetControl32BitValue(radioButtonNotificationBadge, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationBounce, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationDialog, kControlRadioButtonUncheckedValue);
					result = true;
				}
				else if (HIViewIDWrap(radioButtonNotificationBadge.identifier()) == viewID)
				{
					SInt16		newNotificationType = kAlert_NotifyDisplayDiamondMark;
					
					
					Preferences_SetData(kPreferences_TagNotification,
										sizeof(newNotificationType), &newNotificationType);
					SetControl32BitValue(radioButtonNotificationNone, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationBounce, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationDialog, kControlRadioButtonUncheckedValue);
					result = true;
				}
				else if (HIViewIDWrap(radioButtonNotificationBounce.identifier()) == viewID)
				{
					SInt16		newNotificationType = kAlert_NotifyDisplayIconAndDiamondMark;
					
					
					Preferences_SetData(kPreferences_TagNotification,
										sizeof(newNotificationType), &newNotificationType);
					SetControl32BitValue(radioButtonNotificationNone, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationBadge, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationDialog, kControlRadioButtonUncheckedValue);
					result = true;
				}
				else if (HIViewIDWrap(radioButtonNotificationDialog.identifier()) == viewID)
				{
					SInt16		newNotificationType = kAlert_NotifyAlsoDisplayAlert;
					
					
					Preferences_SetData(kPreferences_TagNotification,
										sizeof(newNotificationType), &newNotificationType);
					SetControl32BitValue(radioButtonNotificationNone, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationBadge, kControlRadioButtonUncheckedValue);
					SetControl32BitValue(radioButtonNotificationBounce, kControlRadioButtonUncheckedValue);
					result = true;
				}
				else if (HIViewWrap(idMyCheckBoxVisualBell, kWindow) == HIViewWrap(inCheckBoxClicked))
				{
					// save the new value
					Preferences_SetData(kPreferences_TagVisualBell,
										sizeof(checkBoxFlagValue), &checkBoxFlagValue);
					result = true;
				}
				else if (HIViewWrap(idMyCheckBoxMarginBell, kWindow) == HIViewWrap(inCheckBoxClicked))
				{
					// save the new value
					Preferences_SetData(kPreferences_TagMarginBell,
										sizeof(checkBoxFlagValue), &checkBoxFlagValue);
					result = true;
				}
				else if (HIViewWrap(idMyCheckBoxNotifyTerminalBeeps, kWindow) == HIViewWrap(inCheckBoxClicked))
				{
					// save the new value
					Preferences_SetData(kPreferences_TagNotifyOfBeeps,
										sizeof(checkBoxFlagValue), &checkBoxFlagValue);
					result = true;
				}
			}
			break;
		
		default:
			break;
		}
	}
	
	return result;
}// updateCheckBoxPreference

// BELOW IS REQUIRED NEWLINE TO END FILE
