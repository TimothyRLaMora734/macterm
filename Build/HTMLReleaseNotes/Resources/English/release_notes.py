#!/usr/bin/python
"""Notes on changes in each MacTelnet release.

Import this module to access its variables, or run it as a script to see the
sorted, formatted release notes as text (see to_rst()).
"""
__author__ = "Kevin Grant <kevin@ieee.org>"
__date__ = "28 September 2006"

# IMPORTANT: Released versions of MacTelnet will always point to
# a specific version page, so don't ever remove old versions from
# this list (that is, even ancient versions pages should be
# generated).  Also, the order of this list matters; the newest
# release should be inserted at the beginning.
version_lineage = [
    '3.1.0',
    '3.0.1',
]

daily_build_lineage = [
    '20071019',
    '20071015',
    '20071013',
    '20071011',
    '20071010',
    '20071006',
    '20070929',
    '20070918',
    '20070908',
    '20070906',
    '20070827',
    '20070424',
    '20070224',
    '20070220',
    '20070212',
    '20070207',
    '20070124',
    '20070109',
    '20070108',
    '20070107',
    '20070103',
    '20061227',
    '20061224',
    '20061127',
    '20061113',
    '20061110',
    '20061107',
    '20061105',
    '20061101',
    '20061030',
    '20061029',
    '20061028',
    '20061027',
    '20061026',
    '20061025',
    '20061024',
    '20061023',
    '20061022',
]

notes_by_version = {
	'20071019': [
		'Terminal window toolbars now have a Bell item option.  Clicking it will enable *or* disable the terminal bell.',
		'Renamed the "Disable Bell" command to simply "Bell", which also inverts the state of its checkmark.',
		'Preferences window collections drawer further tweaked to align in an aesthetically pleasing way with tabs.',
		'Custom Screen Size dialog arrows now increment and decrement by 4 for columns, and 10 for rows.',
	],
	'20071015': [
		'Fixed the Interrupt Process command to send the interrupt character to the active session.',
		'Preferences window General pane now correctly displays cursor shapes.',
		'Preferences window General pane now uses Unicode text for cursor shapes instead of icon images.',
	],
	'20071013': [
		'Changed the artwork for the main application icon and other icons showing terminals.',
	],
	'20071011': [
		'Added an icon for the Translations preference category.',
	],
	'20071010': [
		'Fixed line truncation during operations such as Copy and drag-and-drop.',
		'Fixed word and line highlighting for double-clicks and triple-clicks.',
	],
	'20071006': [
		'Internal improvements to the code (removing some compile warnings, etc.).',
	],
	'20070929': [
		'Fixed cases where size-change commands were ineffective in one terminal resize mode but not the other.',
	],
	'20070918': [
		'Terminal view backgrounds now have a user interface for changing the color, via menu or contextual menu.',
		'Session Info window toolbar items rearranged in customization sheet, so that Customize is not hidden.',
	],
	'20070908': [
		'Fixed a few possible crash conditions.',
		'Redesigned the Find icon on the VT220 keypad.',
		'Key palettes now have a 5 pixel padding between buttons and the window edge.',
	],
	'20070906': [
		'Preferences window collections drawer is now below the toolbar to show that it affects only one category.',
		'Preferences window General pane now has correctly sized tab content.',
		'Preferences window Sessions pane now has correctly sized tab content.',
		'Terminal views and backgrounds now support a more complete set of accessibility attributes.',
		'Terminal view backgrounds now have an accessibility role of "matte".',
		'Terminal view drag highlight now uses Core Graphics for a smoother display.',
	],
	'20070827': [
		'Added tabbed-windows feature, accessible through a new General preference.',
		'Added Move to New Workspace command (available only when using tabs) to move tabs into separate groups.',
	],
	'20070424': [
		'Session Info window list selections can now be the target of session-related menu bar commands.',
	],
	'20070224': [
		'New, high-quality icons for the VT220 keypad window.',
	],
	'20070220': [
		'Keys menu renamed to Map, which is more accurate; also renamed some of the items in the menu.',
		'Session Info window toolbars may now have "Arrange All Windows in Front".',
	],
	'20070212': [
		'Added placeholder Fix Character command.',
	],
	'20070207': [
		'A new, simpler look for MacTelnet Help.',
		'Internal changes to improve the MacTelnet Help build system.',
	],
	'20070124': [
		'Fixed a case where terminal windows could open with toolbar focus instead of terminal keyboard focus.',
	],
	'20070109': [
		'Fixed VT52-mode cursor positioning.',
	],
	'20070108': [
		'Preferences window resizes now remembered per category, so choosing a panel will restore its window size.',
		'Interrupt now correctly resets the Suspend Network flag.',
		'Interrupt now displays a help tag above the cursor instead of writing text into the terminal.',
		'Suspend now displays a help tag above the cursor instead of writing text into the terminal.',
		'Resume now hides the Interrupt or Suspend help tag instead of writing text into the terminal.',
		'Internal changes to old QuickDraw code based on Apple recommendations for Intel compatibility.',
	],
	'20070107': [
		'Compiled as a Universal Application (for Intel Macs).  The Intel version has NOT been tested yet!',
	],
	'20070103': [
		'Identified a possible crash when switching the Window Resize Affects preference.  No fix is available yet.',
		'Corrected possible parsing problem when entering URLs containing whitespace into the command line.',
		'Internal changes to separate URL parsing code from handling code, which also simplifies tests.',
		'Internal changes to make MacTelnet Python files have very unique names, avoiding risk of import collisions.',
		'Internal changes to unit testing code in RunMacTelnet.py, to make it cleaner and easier to filter modules.',
	],
	'20061227': [
		'Updated color box buttons to use Core Graphics natively.',
		'Drag-and-drop highlight now respects the Graphite appearance setting, if applicable.',
	],
	'20061224': [
		'Open Session dialog no longer crashes if Cancel is chosen.',
		'Open Session dialog now supports more than one file at the same time.',
		'Tall (80 x 48) pre-defined size added to the View menu.',
		'Color boxes in the Format preferences panel now properly display a color.',
		'Color boxes in the Format preferences panel (ANSI Colors tab) can now change the color when clicked.',
		'Internal changes to avoid some memory copies in a few instances, for efficiency.',
	],
	'20061127': [
		'Internally, removed a lot of legacy and transitional cruft for handling the menu bar.',
		'Menus are now implemented in the normal way as a single NIB file.',
		'The Network menu has been removed; various menu items moved to different menus.',
		'New "Action" menu, a redundant menu interface to make commands easy to find by task!',
	],
	'20061113': [
		'Terminal is now properly focused for text input when opened via the New Session sheet.',
		'Fixed a possible crash condition when selecting text.',
		'Internal changes to prevent needless reconstruction of the Python interface during builds.',
	],
	'20061110': [
		'Fixed visual synchronization of changes in New Session dialog with the command line field.',
		'More section names in Preferences window now use a bold font (like Keynote and Pages do).',
		'Redesigned the Format preferences panel.',
		'Minor renaming of items in the Full Screen preferences panel.',
		'Arbitrarily reduced the default window size of Session Info.',
	],
	'20061107': [
		'Terminal view cursor blinking works once again.',
		'Fixed a problem with the mouse cursor changing when pointing just outside a selection.',
		'Internal changes to allow ANSI-BBS terminal type to be supported in the future.',
	],
	'20061105': [
		'Terminal views now hide the cursor whenever scrollback lines are displayed.',
		'Window hiding no longer fails for windows that were redisplayed under certain conditions.',
		'Window hiding animation has been sped up, because it is still synchronous.',
		'Window hiding seems to cause a session to be ignored during quitting time reviews; there is no fix yet.',
		'Preferences panel for Sessions now has functional DNS lookup on the Resource tab.',
	],
	'20061101': [
		'Some problems with scrollback function and display are now fixed.',
		'Section names in dialogs and in the Preferences window now use a bold font (like Keynote and Pages do).',
		'Various bits of internal code cleanup.',
	],
	'20061030': [
		'Fixed problems with renaming items in the collections drawer of the Preferences window.',
		'Fixed problems with adding and removing items in the collections drawer of the Preferences window.',
	],
	'20061029': [
		'Once again supporting rlogin URLs.',
		'Updated property list so the Finder, etc. realizes MacTelnet can handle a number of different types of URLs.',
		'Once again printing random biline text on the splash screen.  However, it is now localizable.',
		'Internal changes to put the MacTelnet core and generated Python API into a framework called Quills.framework.',
		'Internal changes to put Python-based portions of MacTelnet into a framework called PyMacTelnet.framework.',
		'Minor corrections to MacTelnet Help.',
	],
	'20061028': [
		'More than any other release so far, this build shows off the true power of the new Quills interface in Python!',
		'Added Session.on_urlopen_call(func, schema) to Quills, allowing Python functions to respond to URL requests.',
		'Added Session.stop_urlopen_call(func, schema) to Quills, to mirror Session.on_urlopen_call().',
		'Reimplemented every URL handler as Python code, greatly simplifying both implementation and maintenance.',
		'Added a series of doctest testcases to validate all URL handling code.',
		'Renamed Quills API Session.on_new_ignore() to Session.stop_new_call().',
	],
	'20061027': [
		'Added support for the x-man-page URL type.  For example, "x-man-page://ls" or "x-man-page://3/printf".',
		'Cursor shape preferences are once again respected.',
		'Corrected glitch in rendering lower right edges of inactive selection outlines.',
	],
	'20061026': [
		'Fixed position of inactive text selection outlines in terminal views.',
		'Internal change to fix to cursor positioning code in renderer.',
	],
	'20061025': [
		'MacTelnet Help has received several minor corrections and other edits.',
		'Jump Scrolling menu item now has a help tag.',
		'Internal changes to add icon identifiers to a central registry.',
		'Internal changes to allow a terminal view to not render a focus ring, if a special flag is set.',
	],
	'20061024': [
		'Terminal window toolbars now have a Full Screen item option.  Clicking it will start *or* end Full Screen.',
		'Zoom effect for hiding windows now more accurately approximates the location of the Window menu title.',
	],
	'20061023': [
		'Added keys for the 5 Full Screen preferences to DefaultPreferences.plist.',
		'Updated the Preferences window interface to properly save and restore the Full Screen checkboxes.',
		'Full Screen now respects the menu bar visibility preference.',
		'Full Screen menu bar checkbox label changed to more accurately show its effect.',
		'Full Screen now respects the scroll bar visibility preference.',
		'Full Screen now respects the Force Quit availability preference.',
		'Full Screen now respects the off-switch visibility preference.',
		'Full Screen is now usually disabled automatically if the terminal window closes (some quirks remain here).',
	],
	'20061022': [
		'Most of the Preferences window is broken due to recent internal changes.  Please do not submit bugs on it.',
		'Terminal window text selections do not work properly.  Please do not submit bugs on this.',
		'Terminal scrollback cannot be displayed.  Please do not submit bugs on this.',
	],
    '3.1.0': [
        'Decision was made to require Mac OS X 10.3 minimum.',
        'IPv6 addresses can now be used anywhere hosts are normally used.',
        'Get IP Address command now returns IPv6 format if possible.',
        'New Session sheet now supports SSH-1, SSH-2, SFTP, FTP and TELNET.',
        'All user interface elements reimplemented as NIBs.',
        'Full Keyboard Access now works throughout (because of NIBs change).',
        'VoiceOver now works throughout (because of NIBs change).',
        'Minor accessibility additions to allow VoiceOver to work with custom interfaces.',
        'User interface style (layout, etc.) revamped based on Mac OS X guidelines.',
        'Session Info window now fully functional.',
        'Session Info window allows you to select a window by double-clicking its list item.',
        'Session Info window allows you to change window titles simply by clicking and typing.',
        "Session Info window displays icon and text version of each session's status.",
        'Session Info window now has a customizable toolbar, with the "unified" appearance.',
        'Session Info window columns can be moved or resized, ordering is implicitly saved.',
        'Terminal emulation core rewritten from scratch!',
		'Terminal maximum width increased to 256 columns.',
        'Terminal window toolbars now use the standard Mac OS X implementation.',
        'Terminal window toolbar LED icon artwork has been significantly improved.',
        'Terminal window toolbars now have Suspend (Scroll Lock), Hide, Full Screen, and Print.',
        'Terminal windows now support live feedback during resize.',
        'Terminal window resizes can now change font *or* dimensions.',
        'Terminal window resize behavior can be inverted with the Option key.',
        'Terminal window resize behavior can now be set in Preferences.',
        'Terminal views are now implemented as HIViews, which simplifies some code.',
        'Terminal views now automatically switch to a contrasting color if an ANSI color would make text invisible.',
        'Terminal text with blinking style now animates, with a gentle pulse.',
        'Floating command line window now has a pop-up menu for history as well.',
        'Floating command line window now recognizes up-arrow for history rotation.',
        'Floating command line window now properly respects tab focusing.',
        'Key palettes have been reimplemented as Aqua windows with regular buttons.',
        'Key palette buttons that are entirely iconic now have Help Tags to describe them.',
        'Key palettes now have keyboard equivalents to show and hide their windows.',
        'TEK graphics windows now support live resize.',
        'TEK graphics can once again be copied to the clipboard.',
        'Clipboard window once again updates itself when the clipboard contents are changed.',
        'Clipboard window can now display Unicode text.',
        'Drag highlight effect is much improved (similar to Apple Mail on Tiger).',
        'Windows can now be given titles containing Unicode characters.',
        'Most file interfaces now support Unicode names.',
        'Most file interfaces now use sheets.',
        'Printing dialogs now use sheets.',
        'Preferences have been reimplemented as com.mactelnet.MacTelnet.plist.',
        'New preferences are now initialized exclusively from DefaultPreferences.plist.',
        'Converter utility now automatically imports older preferences files.',
        'Preferences window now has a toolbar like in other Mac OS X applications.',
        'Preferences window now supports live editing of settings in collections!',
        'Preferences window now displays a drawer with a list of Favorites when appropriate.',
        'Preferences window now fully integrates macro editing.',
        'Preferences for fonts and colors are now separate, in Format Favorites.',
        'Preferences for sessions now properly support local Unix command lines.',
        'Preferences for Full Screen are now a panel instead of a modal dialog.',
        "Preferences for Scripts no longer offer event mapping (which didn't work anyway).",
        'Significant AppleScript interfaces are broken.  They will be removed in the future.',
        'MacTelnet core reimplemented as a framework loaded into the Python interpreter!!!',
        'Python API called "Quills" is now available, allowing Python scripts to call MacTelnet!',
        'Python functions can also be called *by* MacTelnet, allowing simple extensibility!',
        'Python API is very minimal right now, the plan is for this to become much bigger.',
        'Text translation is currently broken.  However, Quills will make this much easier.',
        'Apple ".command" files can now be opened by MacTelnet.',
        'Apple ".term" files can now be opened by MacTelnet, but some settings are ignored.',
        'Several new application menu commands, including Check for Updates.',
        'The Special Characters command is now available in the Edit menu.',
        'Help tags do not appear automatically; turn them on with the Help menu.',
    ],
    '3.0.1': [
        'Fixes for dialog boxes that stopped accepting input in Mac OS X 10.3.',
    ],
}

def to_basic_html(lineage=version_lineage):
    """to_basic_html(lineage) -> list of string
    
    Return lines rendering the release notes as basic HTML.
    
    No fancy formatting is applied, nor is the document complete
    (e.g. it doesn't start with <html>).
    
    By default all versions are returned; you can override lineage.
    """
    result = []
    for version in lineage:
        result.append("<h1>%s</h1>" % version)
        result.append("<ul>")
        for note in notes_by_version[version]:
            result.append("<li>%s</li>" % note)
        result.append("</ul>")
    return result

def to_plain_text(lineage=version_lineage):
    """to_plain_text(lineage) -> string
    
    Return lines rendering the release notes as a continuous string,
    with minimal formatting delimiting each note.  This is necessary
    for a MacPAD file, among other things.
    
    By default all versions are returned; you can override lineage.
    """
    result = ''
    for version in lineage:
        result += ('[%s] ' % version)
        for note in notes_by_version[version]:
            result += ("* %s   " % note)
    return result

def to_rst(lineage=version_lineage):
    """to_rst(lineage) -> list of string
    
    Return lines rendering the release notes as reStructuredText.
    
    By default all versions are returned; you can override lineage.
    """
    result = []
    for version in lineage:
        result.append(''.join(['-' for x in version]))
        result.append(version)
        result.append(''.join(['-' for x in version]))
        result.append('')
        for note in notes_by_version[version]:
            result.append("- %s" % note)
        result.append('')
    return result

if __name__ == '__main__':
    import sys
    # by default, all versions are returned; or, specify which ones
    format = sys.argv[1]
    if len(sys.argv) > 2: lineage = sys.argv[2:]
    else: lineage = version_lineage
    if format == "plain_text": print to_plain_text(lineage)
    elif format == "rst": print "\n".join(to_rst(lineage))
    else: print "\n".join(to_basic_html(lineage))

