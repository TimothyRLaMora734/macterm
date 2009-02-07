#!/usr/bin/python
# vim: set fileencoding=UTF-8 :
"""Main entry point to MacTelnet.

The set of routines available from Python is known as the Quills
API and is declared in the MacTelnet headers of the same name
(like "QuillsBase.h").

Exposure to Python simplifies debugging, and gives you options
for extensibility and configuration that most applications lack!
This file shows just a few examples of what you can do...look for
more information at MacTelnet.com.
"""
__author__ = 'Kevin Grant <kevin@ieee.org>'
__date__ = '24 August 2006'
__version__ = '3.1.0'

import os, string

import pymactelnet.HandleFile as HandleFile
import pymactelnet.HandleURL as HandleURL
try:
	from Quills import Base, Events, Session, Terminal
except ImportError, err:
	import sys, os
	print >>sys.stderr, "Unable to import Quills."
	if "DYLD_LIBRARY_PATH" in os.environ:
		print >>sys.stderr, "Shared library path:", os.environ["DYLD_LIBRARY_PATH"]
	print >>sys.stderr, "Python path:", sys.path
	raise err

# below are examples of things you might want to enable for debugging...

# memory allocation changes - see "man malloc" for more options here
#os.environ['MallocGuardEdges'] = '1'
#os.environ['MallocScribble'] = '1'

# debugging of Carbon Events
#os.environ['EventDebug'] = '1'

# if you want to read documentation on the API, try one of these (and
# run MacTelnet from a shell so you can see the documentation)...
#os.system("pydoc Quills.Base")
#os.system("pydoc Quills.Events")
#os.system("pydoc Quills.Prefs")
#os.system("pydoc Quills.Session")
#os.system("pydoc Quills.Terminal")



# load all required MacTelnet modules
Base.all_init()
#Base.all_init(os.environ['INITIAL_APP_BUNDLE_DIR']) # this variant is no longer needed

# banner
print "MacTelnet: Base initialization complete.  This is MacTelnet version %s." % Base.version()

# If necessary, invoke testcases (each has its own block so that subsets
# can be run more easily).  A _test() call will generate output only for
# problems; therefore, this runner prints its own banner for success.
do_testing = False
def run_module_tests( mod ):
	(failures, test_count) = mod._test()
	if not failures: print "MacTelnet: %s module: SUCCESSFUL unit test (total tests: %d)" % (mod.__name__, test_count)
if do_testing:
	import pymactelnet.Util
	run_module_tests(pymactelnet.Util)
if do_testing:
	import pymactelnet.ParseURL
	run_module_tests(pymactelnet.ParseURL)
if do_testing:
	import pymactelnet.HandleURL
	run_module_tests(pymactelnet.HandleURL)

# register MacTelnet features that are actually implemented in Python!
Session.on_urlopen_call(HandleURL.file, 'file')
Session.on_urlopen_call(HandleURL.ftp, 'ftp')
Session.on_urlopen_call(HandleURL.sftp, 'sftp')
Session.on_urlopen_call(HandleURL.ssh, 'ssh')
Session.on_urlopen_call(HandleURL.telnet, 'telnet')
Session.on_urlopen_call(HandleURL.x_man_page, 'x-man-page')
Session.on_fileopen_call(HandleFile.script, 'bash')
Session.on_fileopen_call(HandleFile.script, 'command')
Session.on_fileopen_call(HandleFile.script, 'csh')
Session.on_fileopen_call(HandleFile.script, 'pl')
Session.on_fileopen_call(HandleFile.script, 'py')
Session.on_fileopen_call(HandleFile.script, 'sh')
Session.on_fileopen_call(HandleFile.script, 'tcl')
Session.on_fileopen_call(HandleFile.script, 'tcsh')
Session.on_fileopen_call(HandleFile.script, 'tool')
Session.on_fileopen_call(HandleFile.script, 'zsh')

# if desired, override what string is sent after keep-alive timers expire
#Session.set_keep_alive_transmission(".")

def get_dumb_rendering( ord_unicode_16 ):
	"""Return the string that dumb terminals should use to
	render the specified character.  The idea is for EVERY
	character to have a visible representation, whereas
	with normal terminals many invisible characters have
	special meaning.
	
	"""
	result = '<?>' # must use UTF-8 encoding
	if ord_unicode_16 < 128:
		as_ascii = ord_unicode_16
		if as_ascii == 27: result = '<ESC>'
		# a "proper" control symbol is preferred, but MacTelnet cannot render
		# higher Unicode characters just yet...
		#elif as_ascii < ord(' '): result = '⌃%c' % chr(ord('@') + as_ascii)
		elif as_ascii < ord(' '): result = '^%c' % chr(ord('@') + as_ascii)
		elif (chr(as_ascii) in string.printable): result = chr(as_ascii)
		else: result = '<%i>' % as_ascii
	else:
		result = '<u%i>' % ord_unicode_16
	return result
for i in range(0, 256):
	try:
		Terminal.set_dumb_string_for_char(i, get_dumb_rendering(i))
	except Exception, e:
		print "warning, exception while setting character code %i:" % i, e
		pass

# banner
print "MacTelnet: Full initialization complete."

# (if desired, insert code at this point to interact with MacTelnet)

# if you want to find out when new sessions are created, you can
# define a Python function and simply register it...
#def my_py_func():
#	print "\n\nI was called by MacTelnet!\n\n"
#Session.on_new_call(my_py_func)

# the following line would run a command every time you start up...
#session_1 = Session("progname -arg1 -arg2 -arg3 val3 -arg4 val4".split())

# start user interaction (WARNING: will not return until quitting time!)
Events.run_loop()

# unload all required MacTelnet modules, performing necessary cleanup
Base.all_done()

