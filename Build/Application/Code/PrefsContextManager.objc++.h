/*!	\file PrefsContextManager.objc++.h
	\brief An Objective-C object for common preferences tasks.
*/
/*###############################################################

	MacTerm
		© 1998-2012 by Kevin Grant.
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

#ifndef __PREFSCONTEXTMANAGER__
#define __PREFSCONTEXTMANAGER__

// application includes
#import "Preferences.h"



#pragma mark Types

/*!
This class simplifies various Preferences tasks in an
Objective-C environment (such as a preferences panel
interface).
*/
@interface PrefsContextManager_Object : NSObject
{
@private
	Preferences_ContextRef		currentContext;
}

// initializers

- (id)
init;

// designated initializer
- (id)
initWithDefaultContextInClass:(Quills::Prefs::Class)_;

// accessors

- (Preferences_ContextRef)
currentContext;
- (void)
setCurrentContext:(Preferences_ContextRef)_;

// new methods

- (BOOL)
deleteDataForPreferenceTag:(Preferences_Tag)_;

- (NSColor*)
readColorForPreferenceTag:(Preferences_Tag)_
isDefault:(BOOL*)_;

- (BOOL)
readFlagForPreferenceTag:(Preferences_Tag)_
defaultValue:(BOOL)_;

- (BOOL)
writeColor:(NSColor*)_
forPreferenceTag:(Preferences_Tag)_;

- (BOOL)
writeFlag:(BOOL)_
forPreferenceTag:(Preferences_Tag)_;

@end

#endif

// BELOW IS REQUIRED NEWLINE TO END FILE