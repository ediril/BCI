'''Wrapper for Dragonfly_config.h

Generated with:
C:\Users\emd\Documents\_apps_\ctypesgen\ctypesgen.py --includedir="../include" -a -o C:\Users\emd\Desktop\BCI\message_definitions\Dragonfly_config.py C:\Users\emd\Desktop\BCI\message_definitions\Dragonfly_config.h

Do not modify this file.
'''

__docformat__ =  'restructuredtext'

# Begin preamble

import ctypes, os, sys
from ctypes import *

_int_types = (c_int16, c_int32)
if hasattr(ctypes, 'c_int64'):
    # Some builds of ctypes apparently do not have c_int64
    # defined; it's a pretty good bet that these builds do not
    # have 64-bit pointers.
    _int_types += (c_int64,)
for t in _int_types:
    if sizeof(t) == sizeof(c_size_t):
        c_ptrdiff_t = t
del t
del _int_types

class c_void(Structure):
    # c_void_p is a buggy return type, converting to int, so
    # POINTER(None) == c_void_p is actually written as
    # POINTER(c_void), so it can be treated as a real pointer.
    _fields_ = [('dummy', c_int)]

def POINTER(obj):
    p = ctypes.POINTER(obj)

    # Convert None to a real NULL pointer to work around bugs
    # in how ctypes handles None on 64-bit platforms
    if not isinstance(p.from_param, classmethod):
        def from_param(cls, x):
            if x is None:
                return cls()
            else:
                return x
        p.from_param = classmethod(from_param)

    return p

class UserString:
    def __init__(self, seq):
        if isinstance(seq, basestring):
            self.data = seq
        elif isinstance(seq, UserString):
            self.data = seq.data[:]
        else:
            self.data = str(seq)
    def __str__(self): return str(self.data)
    def __repr__(self): return repr(self.data)
    def __int__(self): return int(self.data)
    def __long__(self): return long(self.data)
    def __float__(self): return float(self.data)
    def __complex__(self): return complex(self.data)
    def __hash__(self): return hash(self.data)

    def __cmp__(self, string):
        if isinstance(string, UserString):
            return cmp(self.data, string.data)
        else:
            return cmp(self.data, string)
    def __contains__(self, char):
        return char in self.data

    def __len__(self): return len(self.data)
    def __getitem__(self, index): return self.__class__(self.data[index])
    def __getslice__(self, start, end):
        start = max(start, 0); end = max(end, 0)
        return self.__class__(self.data[start:end])

    def __add__(self, other):
        if isinstance(other, UserString):
            return self.__class__(self.data + other.data)
        elif isinstance(other, basestring):
            return self.__class__(self.data + other)
        else:
            return self.__class__(self.data + str(other))
    def __radd__(self, other):
        if isinstance(other, basestring):
            return self.__class__(other + self.data)
        else:
            return self.__class__(str(other) + self.data)
    def __mul__(self, n):
        return self.__class__(self.data*n)
    __rmul__ = __mul__
    def __mod__(self, args):
        return self.__class__(self.data % args)

    # the following methods are defined in alphabetical order:
    def capitalize(self): return self.__class__(self.data.capitalize())
    def center(self, width, *args):
        return self.__class__(self.data.center(width, *args))
    def count(self, sub, start=0, end=sys.maxint):
        return self.data.count(sub, start, end)
    def decode(self, encoding=None, errors=None): # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.decode(encoding, errors))
            else:
                return self.__class__(self.data.decode(encoding))
        else:
            return self.__class__(self.data.decode())
    def encode(self, encoding=None, errors=None): # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.encode(encoding, errors))
            else:
                return self.__class__(self.data.encode(encoding))
        else:
            return self.__class__(self.data.encode())
    def endswith(self, suffix, start=0, end=sys.maxint):
        return self.data.endswith(suffix, start, end)
    def expandtabs(self, tabsize=8):
        return self.__class__(self.data.expandtabs(tabsize))
    def find(self, sub, start=0, end=sys.maxint):
        return self.data.find(sub, start, end)
    def index(self, sub, start=0, end=sys.maxint):
        return self.data.index(sub, start, end)
    def isalpha(self): return self.data.isalpha()
    def isalnum(self): return self.data.isalnum()
    def isdecimal(self): return self.data.isdecimal()
    def isdigit(self): return self.data.isdigit()
    def islower(self): return self.data.islower()
    def isnumeric(self): return self.data.isnumeric()
    def isspace(self): return self.data.isspace()
    def istitle(self): return self.data.istitle()
    def isupper(self): return self.data.isupper()
    def join(self, seq): return self.data.join(seq)
    def ljust(self, width, *args):
        return self.__class__(self.data.ljust(width, *args))
    def lower(self): return self.__class__(self.data.lower())
    def lstrip(self, chars=None): return self.__class__(self.data.lstrip(chars))
    def partition(self, sep):
        return self.data.partition(sep)
    def replace(self, old, new, maxsplit=-1):
        return self.__class__(self.data.replace(old, new, maxsplit))
    def rfind(self, sub, start=0, end=sys.maxint):
        return self.data.rfind(sub, start, end)
    def rindex(self, sub, start=0, end=sys.maxint):
        return self.data.rindex(sub, start, end)
    def rjust(self, width, *args):
        return self.__class__(self.data.rjust(width, *args))
    def rpartition(self, sep):
        return self.data.rpartition(sep)
    def rstrip(self, chars=None): return self.__class__(self.data.rstrip(chars))
    def split(self, sep=None, maxsplit=-1):
        return self.data.split(sep, maxsplit)
    def rsplit(self, sep=None, maxsplit=-1):
        return self.data.rsplit(sep, maxsplit)
    def splitlines(self, keepends=0): return self.data.splitlines(keepends)
    def startswith(self, prefix, start=0, end=sys.maxint):
        return self.data.startswith(prefix, start, end)
    def strip(self, chars=None): return self.__class__(self.data.strip(chars))
    def swapcase(self): return self.__class__(self.data.swapcase())
    def title(self): return self.__class__(self.data.title())
    def translate(self, *args):
        return self.__class__(self.data.translate(*args))
    def upper(self): return self.__class__(self.data.upper())
    def zfill(self, width): return self.__class__(self.data.zfill(width))

class MutableString(UserString):
    """mutable string objects

    Python strings are immutable objects.  This has the advantage, that
    strings may be used as dictionary keys.  If this property isn't needed
    and you insist on changing string values in place instead, you may cheat
    and use MutableString.

    But the purpose of this class is an educational one: to prevent
    people from inventing their own mutable string class derived
    from UserString and than forget thereby to remove (override) the
    __hash__ method inherited from UserString.  This would lead to
    errors that would be very hard to track down.

    A faster and better solution is to rewrite your program using lists."""
    def __init__(self, string=""):
        self.data = string
    def __hash__(self):
        raise TypeError("unhashable type (it is mutable)")
    def __setitem__(self, index, sub):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data): raise IndexError
        self.data = self.data[:index] + sub + self.data[index+1:]
    def __delitem__(self, index):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data): raise IndexError
        self.data = self.data[:index] + self.data[index+1:]
    def __setslice__(self, start, end, sub):
        start = max(start, 0); end = max(end, 0)
        if isinstance(sub, UserString):
            self.data = self.data[:start]+sub.data+self.data[end:]
        elif isinstance(sub, basestring):
            self.data = self.data[:start]+sub+self.data[end:]
        else:
            self.data =  self.data[:start]+str(sub)+self.data[end:]
    def __delslice__(self, start, end):
        start = max(start, 0); end = max(end, 0)
        self.data = self.data[:start] + self.data[end:]
    def immutable(self):
        return UserString(self.data)
    def __iadd__(self, other):
        if isinstance(other, UserString):
            self.data += other.data
        elif isinstance(other, basestring):
            self.data += other
        else:
            self.data += str(other)
        return self
    def __imul__(self, n):
        self.data *= n
        return self

class String(MutableString, Union):

    _fields_ = [('raw', POINTER(c_char)),
                ('data', c_char_p)]

    def __init__(self, obj=""):
        if isinstance(obj, (str, unicode, UserString)):
            self.data = str(obj)
        else:
            self.raw = obj

    def __len__(self):
        return self.data and len(self.data) or 0

    def from_param(cls, obj):
        # Convert None or 0
        if obj is None or obj == 0:
            return cls(POINTER(c_char)())

        # Convert from String
        elif isinstance(obj, String):
            return obj

        # Convert from str
        elif isinstance(obj, str):
            return cls(obj)

        # Convert from c_char_p
        elif isinstance(obj, c_char_p):
            return obj

        # Convert from POINTER(c_char)
        elif isinstance(obj, POINTER(c_char)):
            return obj

        # Convert from raw pointer
        elif isinstance(obj, int):
            return cls(cast(obj, POINTER(c_char)))

        # Convert from object
        else:
            return String.from_param(obj._as_parameter_)
    from_param = classmethod(from_param)

def ReturnString(obj, func=None, arguments=None):
    return String.from_param(obj)

# As of ctypes 1.0, ctypes does not support custom error-checking
# functions on callbacks, nor does it support custom datatypes on
# callbacks, so we must ensure that all callbacks return
# primitive datatypes.
#
# Non-primitive return values wrapped with UNCHECKED won't be
# typechecked, and will be converted to c_void_p.
def UNCHECKED(type):
    if (hasattr(type, "_type_") and isinstance(type._type_, str)
        and type._type_ != "P"):
        return type
    else:
        return c_void_p

# ctypes doesn't have direct support for variadic functions, so we have to write
# our own wrapper class
class _variadic_function(object):
    def __init__(self,func,restype,argtypes):
        self.func=func
        self.func.restype=restype
        self.argtypes=argtypes
    def _as_parameter_(self):
        # So we can pass this variadic function as a function pointer
        return self.func
    def __call__(self,*args):
        fixed_args=[]
        i=0
        for argtype in self.argtypes:
            # Typecheck what we can
            fixed_args.append(argtype.from_param(args[i]))
            i+=1
        return self.func(*fixed_args+list(args[i:]))

# End preamble

_libs = {}
_libdirs = []

# Begin loader

# ----------------------------------------------------------------------------
# Copyright (c) 2008 David James
# Copyright (c) 2006-2008 Alex Holkner
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#  * Neither the name of pyglet nor the names of its
#    contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

import os.path, re, sys, glob
import ctypes
import ctypes.util

def _environ_path(name):
    if name in os.environ:
        return os.environ[name].split(":")
    else:
        return []

class LibraryLoader(object):
    def __init__(self):
        self.other_dirs=[]

    def load_library(self,libname):
        """Given the name of a library, load it."""
        paths = self.getpaths(libname)

        for path in paths:
            if os.path.exists(path):
                return self.load(path)

        raise ImportError("%s not found." % libname)

    def load(self,path):
        """Given a path to a library, load it."""
        try:
            # Darwin requires dlopen to be called with mode RTLD_GLOBAL instead
            # of the default RTLD_LOCAL.  Without this, you end up with
            # libraries not being loadable, resulting in "Symbol not found"
            # errors
            if sys.platform == 'darwin':
                return ctypes.CDLL(path, ctypes.RTLD_GLOBAL)
            else:
                return ctypes.cdll.LoadLibrary(path)
        except OSError,e:
            raise ImportError(e)

    def getpaths(self,libname):
        """Return a list of paths where the library might be found."""
        if os.path.isabs(libname):
            yield libname
        else:
            # FIXME / TODO return '.' and os.path.dirname(__file__)
            for path in self.getplatformpaths(libname):
                yield path

            path = ctypes.util.find_library(libname)
            if path: yield path

    def getplatformpaths(self, libname):
        return []

# Darwin (Mac OS X)

class DarwinLibraryLoader(LibraryLoader):
    name_formats = ["lib%s.dylib", "lib%s.so", "lib%s.bundle", "%s.dylib",
                "%s.so", "%s.bundle", "%s"]

    def getplatformpaths(self,libname):
        if os.path.pathsep in libname:
            names = [libname]
        else:
            names = [format % libname for format in self.name_formats]

        for dir in self.getdirs(libname):
            for name in names:
                yield os.path.join(dir,name)

    def getdirs(self,libname):
        '''Implements the dylib search as specified in Apple documentation:

        http://developer.apple.com/documentation/DeveloperTools/Conceptual/
            DynamicLibraries/Articles/DynamicLibraryUsageGuidelines.html

        Before commencing the standard search, the method first checks
        the bundle's ``Frameworks`` directory if the application is running
        within a bundle (OS X .app).
        '''

        dyld_fallback_library_path = _environ_path("DYLD_FALLBACK_LIBRARY_PATH")
        if not dyld_fallback_library_path:
            dyld_fallback_library_path = [os.path.expanduser('~/lib'),
                                          '/usr/local/lib', '/usr/lib']

        dirs = []

        if '/' in libname:
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))
        else:
            dirs.extend(_environ_path("LD_LIBRARY_PATH"))
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))

        dirs.extend(self.other_dirs)
        dirs.append(".")
        dirs.append(os.path.dirname(__file__))

        if hasattr(sys, 'frozen') and sys.frozen == 'macosx_app':
            dirs.append(os.path.join(
                os.environ['RESOURCEPATH'],
                '..',
                'Frameworks'))

        dirs.extend(dyld_fallback_library_path)

        return dirs

# Posix

class PosixLibraryLoader(LibraryLoader):
    _ld_so_cache = None

    def _create_ld_so_cache(self):
        # Recreate search path followed by ld.so.  This is going to be
        # slow to build, and incorrect (ld.so uses ld.so.cache, which may
        # not be up-to-date).  Used only as fallback for distros without
        # /sbin/ldconfig.
        #
        # We assume the DT_RPATH and DT_RUNPATH binary sections are omitted.

        directories = []
        for name in ("LD_LIBRARY_PATH",
                     "SHLIB_PATH", # HPUX
                     "LIBPATH", # OS/2, AIX
                     "LIBRARY_PATH", # BE/OS
                    ):
            if name in os.environ:
                directories.extend(os.environ[name].split(os.pathsep))
        directories.extend(self.other_dirs)
        directories.append(".")
        directories.append(os.path.dirname(__file__))

        try: directories.extend([dir.strip() for dir in open('/etc/ld.so.conf')])
        except IOError: pass

        directories.extend(['/lib', '/usr/lib', '/lib64', '/usr/lib64'])

        cache = {}
        lib_re = re.compile(r'lib(.*)\.s[ol]')
        ext_re = re.compile(r'\.s[ol]$')
        for dir in directories:
            try:
                for path in glob.glob("%s/*.s[ol]*" % dir):
                    file = os.path.basename(path)

                    # Index by filename
                    if file not in cache:
                        cache[file] = path

                    # Index by library name
                    match = lib_re.match(file)
                    if match:
                        library = match.group(1)
                        if library not in cache:
                            cache[library] = path
            except OSError:
                pass

        self._ld_so_cache = cache

    def getplatformpaths(self, libname):
        if self._ld_so_cache is None:
            self._create_ld_so_cache()

        result = self._ld_so_cache.get(libname)
        if result: yield result

        path = ctypes.util.find_library(libname)
        if path: yield os.path.join("/lib",path)

# Windows

class _WindowsLibrary(object):
    def __init__(self, path):
        self.cdll = ctypes.cdll.LoadLibrary(path)
        self.windll = ctypes.windll.LoadLibrary(path)

    def __getattr__(self, name):
        try: return getattr(self.cdll,name)
        except AttributeError:
            try: return getattr(self.windll,name)
            except AttributeError:
                raise

class WindowsLibraryLoader(LibraryLoader):
    name_formats = ["%s.dll", "lib%s.dll", "%slib.dll"]

    def load_library(self, libname):
        try:
            result = LibraryLoader.load_library(self, libname)
        except ImportError:
            result = None
            if os.path.sep not in libname:
                for name in self.name_formats:
                    try:
                        result = getattr(ctypes.cdll, name % libname)
                        if result:
                            break
                    except WindowsError:
                        result = None
            if result is None:
                try:
                    result = getattr(ctypes.cdll, libname)
                except WindowsError:
                    result = None
            if result is None:
                raise ImportError("%s not found." % libname)
        return result

    def load(self, path):
        return _WindowsLibrary(path)

    def getplatformpaths(self, libname):
        if os.path.sep not in libname:
            for name in self.name_formats:
                dll_in_current_dir = os.path.abspath(name % libname)
                if os.path.exists(dll_in_current_dir):
                    yield dll_in_current_dir
                path = ctypes.util.find_library(name % libname)
                if path:
                    yield path

# Platform switching

# If your value of sys.platform does not appear in this dict, please contact
# the Ctypesgen maintainers.

loaderclass = {
    "darwin":   DarwinLibraryLoader,
    "cygwin":   WindowsLibraryLoader,
    "win32":    WindowsLibraryLoader
}

loader = loaderclass.get(sys.platform, PosixLibraryLoader)()

def add_library_search_dirs(other_dirs):
    loader.other_dirs = other_dirs

load_library = loader.load_library

del loaderclass

# End loader

add_library_search_dirs([])

# No libraries

# No modules

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 26
class struct_anon_1(Structure):
    pass

struct_anon_1.__slots__ = [
    'SerialNo',
    'Flags',
    'DeltaTime',
]
struct_anon_1._fields_ = [
    ('SerialNo', c_int),
    ('Flags', c_int),
    ('DeltaTime', c_double),
]

SAMPLE_HEADER = struct_anon_1 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 26

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 52
class struct_anon_2(Structure):
    pass

struct_anon_2.__slots__ = [
    'sample_header',
    'sample_interval',
    'pos',
    'vel',
    'controlledDims',
    'tag',
]
struct_anon_2._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('sample_interval', c_double),
    ('pos', c_double * 18),
    ('vel', c_double * 18),
    ('controlledDims', c_int * 18),
    ('tag', c_char * 64),
]

MOVEMENT_COMMAND_DATA = struct_anon_2 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 52

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 60
class struct_anon_3(Structure):
    pass

struct_anon_3.__slots__ = [
    'sample_header',
    'tag',
    'dof_vals',
]
struct_anon_3._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('tag', c_char * 64),
    ('dof_vals', c_double * 21),
]

INPUT_DOF_DATA = struct_anon_3 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 60

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 67
class struct_anon_4(Structure):
    pass

struct_anon_4.__slots__ = [
    'event_time',
    'event_code',
    'reserved',
]
struct_anon_4._fields_ = [
    ('event_time', c_double),
    ('event_code', c_int),
    ('reserved', c_int),
]

TRIAL_EVENT = struct_anon_4 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 67

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 72
class struct_anon_5(Structure):
    pass

struct_anon_5.__slots__ = [
    'D',
]
struct_anon_5._fields_ = [
    ('D', c_double * (18 * 32)),
]

PLAN_PROCESSOR_STATE = struct_anon_5 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 72

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 86
class struct_anon_6(Structure):
    pass

struct_anon_6.__slots__ = [
    'virtualPadPosition',
    'centralPointPosition',
    'posMin',
    'posMax',
    'velMin',
    'velMax',
    'graspingGraspApertureTarget',
    'graspingOpenApertureTarget',
    'graspingIntermediateApertureTarget',
    'maxApproachSwingAngle',
    'graspTooCloseIfClosedRadius',
]
struct_anon_6._fields_ = [
    ('virtualPadPosition', c_double * 18),
    ('centralPointPosition', c_double * 3),
    ('posMin', c_double * 18),
    ('posMax', c_double * 18),
    ('velMin', c_double * 18),
    ('velMax', c_double * 18),
    ('graspingGraspApertureTarget', c_double),
    ('graspingOpenApertureTarget', c_double),
    ('graspingIntermediateApertureTarget', c_double),
    ('maxApproachSwingAngle', c_double),
    ('graspTooCloseIfClosedRadius', c_double),
]

AUTOMAGIC_CONTROLLER_PARAMS = struct_anon_6 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 86

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 102
class struct_anon_7(Structure):
    pass

struct_anon_7.__slots__ = [
    'target',
    'coriMatrix',
    'trialEvent',
    'autoControlParams',
    'autoPosControlFraction',
    'autoVelControlFraction',
    'orthPosImpedance',
    'orthVelImpedance',
    'extrinsicVelControlled',
    'extrinsicPosControlled',
    'importantDOF',
]
struct_anon_7._fields_ = [
    ('target', c_double * 18),
    ('coriMatrix', c_double * 9),
    ('trialEvent', TRIAL_EVENT),
    ('autoControlParams', AUTOMAGIC_CONTROLLER_PARAMS),
    ('autoPosControlFraction', c_double * 18),
    ('autoVelControlFraction', c_double * 18),
    ('orthPosImpedance', c_double * 18),
    ('orthVelImpedance', c_double * 18),
    ('extrinsicVelControlled', c_int * 18),
    ('extrinsicPosControlled', c_int * 18),
    ('importantDOF', c_int * 18),
]

ROBOT_CONTROL_CONFIG = struct_anon_7 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 102

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 119
class struct_anon_8(Structure):
    pass

struct_anon_8.__slots__ = [
    'sample_header',
    'RTMA_received_time',
    'Jpos',
    'Jvel',
    'Cpos',
    'Cori',
    'Cforce',
    'Ctrq',
    'Cvel',
    'CangVel',
    'Hpos',
    'Hstrain',
    'Jtrq',
]
struct_anon_8._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('RTMA_received_time', c_double),
    ('Jpos', c_double * 7),
    ('Jvel', c_double * 7),
    ('Cpos', c_double * 3),
    ('Cori', c_double * 3),
    ('Cforce', c_double * 3),
    ('Ctrq', c_double * 3),
    ('Cvel', c_double * 3),
    ('CangVel', c_double * 3),
    ('Hpos', c_double * 4),
    ('Hstrain', c_double * 4),
    ('Jtrq', c_double * 3),
]

ROBOT_ACTUAL_STATE = struct_anon_8 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 119

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 127
class struct_anon_9(Structure):
    pass

struct_anon_9.__slots__ = [
    'sample_header',
    'RTMA_received_time',
    'pos',
    'vel',
    'CoriMatrix',
]
struct_anon_9._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('RTMA_received_time', c_double),
    ('pos', c_double * 18),
    ('vel', c_double * 18),
    ('CoriMatrix', c_double * 9),
]

ROBOT_CONTROL_SPACE_ACTUAL_STATE = struct_anon_9 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 127

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 132
class struct_anon_10(Structure):
    pass

struct_anon_10.__slots__ = [
    'sample_header',
    'targetPos',
]
struct_anon_10._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('targetPos', c_double * 18),
]

PLANNER_STATE = struct_anon_10 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 132

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 136
class struct_anon_11(Structure):
    pass

struct_anon_11.__slots__ = [
    'cmd',
]
struct_anon_11._fields_ = [
    ('cmd', c_double * 11),
]

JVEL_COMMAND = struct_anon_11 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 136

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 143
class struct_anon_12(Structure):
    pass

struct_anon_12.__slots__ = [
    'DOFCommand',
    'JposCommand',
    'controllerId',
    'j0nks',
]
struct_anon_12._fields_ = [
    ('DOFCommand', c_double * 18),
    ('JposCommand', c_double * 7),
    ('controllerId', c_int),
    ('j0nks', c_int),
]

OVERRIDE_COMMAND = struct_anon_12 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 143

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 166
class struct_anon_13(Structure):
    pass

struct_anon_13.__slots__ = [
    'sample_header',
    'autoControl',
    'overrideCommand',
    'RTMA_received_time',
    'actualControlPos',
    'actualControlVel',
    'autoControlPos',
    'autoControlVel',
    'autoPosControlFraction',
    'autoVelControlFraction',
    'orthPosImpedance',
    'orthVelImpedance',
    'intrinsicVelControlled',
    'intrinsicPosControlled',
    'extrinsicVelControlled',
    'extrinsicPosControlled',
    'overrideDimensions',
    'actualCommandComposition',
    'blank',
]
struct_anon_13._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('autoControl', PLANNER_STATE),
    ('overrideCommand', OVERRIDE_COMMAND),
    ('RTMA_received_time', c_double),
    ('actualControlPos', c_double * 18),
    ('actualControlVel', c_double * 18),
    ('autoControlPos', c_double * 18),
    ('autoControlVel', c_double * 18),
    ('autoPosControlFraction', c_double * 18),
    ('autoVelControlFraction', c_double * 18),
    ('orthPosImpedance', c_double * 18),
    ('orthVelImpedance', c_double * 18),
    ('intrinsicVelControlled', c_int * 18),
    ('intrinsicPosControlled', c_int * 18),
    ('extrinsicVelControlled', c_int * 18),
    ('extrinsicPosControlled', c_int * 18),
    ('overrideDimensions', c_int * 18),
    ('actualCommandComposition', c_uint),
    ('blank', c_int),
]

ROBOT_CONTROL_STATE = struct_anon_13 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 166

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 72
class struct_anon_14(Structure):
    pass

struct_anon_14.__slots__ = [
    'whichButton',
    'val',
    'controllerId',
    'buttonMask',
    'buttonVal',
    'continuousMask',
    'continuousVal',
    'accelMask',
    'spacer',
    'accelVal',
]
struct_anon_14._fields_ = [
    ('whichButton', c_int),
    ('val', c_int),
    ('controllerId', c_int),
    ('buttonMask', c_int * 21),
    ('buttonVal', c_int * 21),
    ('continuousMask', c_int * 21),
    ('continuousVal', c_int * 21),
    ('accelMask', c_int * 2),
    ('spacer', c_int),
    ('accelVal', c_double * 2),
]

PS3_DATA = struct_anon_14 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 72

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 81
class struct_anon_15(Structure):
    pass

struct_anon_15.__slots__ = [
    'stickCommandDOFMap',
    'stickCommandJointMap',
    'stickScale',
    'stickOffset',
    'use_controller',
    'use_label_controller',
]
struct_anon_15._fields_ = [
    ('stickCommandDOFMap', c_int * 21),
    ('stickCommandJointMap', c_int * 21),
    ('stickScale', c_double * 21),
    ('stickOffset', c_double * 21),
    ('use_controller', c_int),
    ('use_label_controller', c_int),
]

PS3_CONFIG = struct_anon_15 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 81

MDF_PS3_BUTTON_PRESS = PS3_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 83

MDF_PS3_BUTTON_RELEASE = PS3_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 84

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 81
class struct_anon_16(Structure):
    pass

struct_anon_16.__slots__ = [
    'buttonMask',
    'buttonVal',
    'continuousMask',
    'continuousVal',
    'accelMask',
    'accelVal',
    'controllerId',
    'spacer',
]
struct_anon_16._fields_ = [
    ('buttonMask', c_int * 21),
    ('buttonVal', c_int * 21),
    ('continuousMask', c_int * 21),
    ('continuousVal', c_int * 21),
    ('accelMask', c_int * 2),
    ('accelVal', c_double * 2),
    ('controllerId', c_int),
    ('spacer', c_int),
]

PS3_RAW_DATA = struct_anon_16 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 81

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 88
class struct_anon_17(Structure):
    pass

struct_anon_17.__slots__ = [
    'sample_header',
    'controllerId',
    'spacer',
    'dof_vals',
]
struct_anon_17._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('controllerId', c_int),
    ('spacer', c_int),
    ('dof_vals', c_double * 21),
]

PS3_GENERIC_DATA = struct_anon_17 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 88

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 93
class struct_anon_18(Structure):
    pass

struct_anon_18.__slots__ = [
    'whichButton',
    'controllerId',
]
struct_anon_18._fields_ = [
    ('whichButton', c_int),
    ('controllerId', c_int),
]

PS3_BUTTON_DATA = struct_anon_18 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 93

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 108
class struct_anon_19(Structure):
    pass

struct_anon_19.__slots__ = [
    'stickCommandDOFMap',
    'stickCommandJointMap',
    'tag',
    'stickScale',
    'stickOffset',
    'accelScale',
    'accelOffset',
    'DOFscale',
    'accelDOFMap',
    'use_controller',
    'free_run',
    'spacer',
]
struct_anon_19._fields_ = [
    ('stickCommandDOFMap', c_int * 21),
    ('stickCommandJointMap', c_int * 21),
    ('tag', c_char * 64),
    ('stickScale', c_double * 21),
    ('stickOffset', c_double * 21),
    ('accelScale', c_double * 2),
    ('accelOffset', c_double * 2),
    ('DOFscale', c_double * 18),
    ('accelDOFMap', c_int * 2),
    ('use_controller', c_int * 10),
    ('free_run', c_int),
    ('spacer', c_int),
]

PS3_RAW_CONFIG = struct_anon_19 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 108

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 130
class struct_accel_state(Structure):
    pass

struct_accel_state.__slots__ = [
    'controllerId',
    'ax',
    'ay',
    'az',
    'time',
    'ddx',
    'ddy',
    'ddz',
    'dx',
    'dy',
    'dz',
    'x',
    'y',
    'z',
    'roll',
    'pitch',
]
struct_accel_state._fields_ = [
    ('controllerId', c_int),
    ('ax', c_int),
    ('ay', c_int),
    ('az', c_int),
    ('time', c_double),
    ('ddx', c_double),
    ('ddy', c_double),
    ('ddz', c_double),
    ('dx', c_double),
    ('dy', c_double),
    ('dz', c_double),
    ('x', c_double),
    ('y', c_double),
    ('z', c_double),
    ('roll', c_double),
    ('pitch', c_double),
]

PS3_ACCEL_DATA = struct_accel_state # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 130

MDF_PS3_RAW_CONFIG = PS3_RAW_CONFIG # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 133

MDF_PS3_SIMPLE_BUTTON_PRESS = PS3_BUTTON_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 134

MDF_PS3_SIMPLE_BUTTON_RELEASE = PS3_BUTTON_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 135

MDF_PS3_GENERIC_DATA = PS3_GENERIC_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 136

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 63
class struct_anon_20(Structure):
    pass

struct_anon_20.__slots__ = [
    'Dimensions',
]
struct_anon_20._fields_ = [
    ('Dimensions', c_double * 18),
]

EM_PARAMS = struct_anon_20 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 63

MDF_EM_START_SESSION = EM_PARAMS # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 65

MDF_RELOAD_CONFIGURATION = EM_PARAMS # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 69

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 74
class struct_anon_21(Structure):
    pass

struct_anon_21.__slots__ = [
    'regressionGroups',
]
struct_anon_21._fields_ = [
    ('regressionGroups', c_int * 18),
]

EM_PROCEDURE_MESSAGE = struct_anon_21 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 74

MDF_EM_RESET_AGGREGATION = EM_PROCEDURE_MESSAGE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 76

MDF_EM_RESUME_COLLECTION = EM_PROCEDURE_MESSAGE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 77

MDF_EM_AGGREGATE_DATA_NOW = EM_PROCEDURE_MESSAGE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 78

MDF_EM_PAUSE_COLLECTION = EM_PROCEDURE_MESSAGE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 79

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 89
class struct_anon_22(Structure):
    pass

struct_anon_22.__slots__ = [
    'initial_position',
    'initial_velocity',
    'target_position',
    'reset_history',
    'reserved',
]
struct_anon_22._fields_ = [
    ('initial_position', c_double * 18),
    ('initial_velocity', c_double * 18),
    ('target_position', c_double * 18),
    ('reset_history', c_int),
    ('reserved', c_int),
]

MDF_EM_RESET_STATE = struct_anon_22 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 89

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 94
class struct_anon_23(Structure):
    pass

struct_anon_23.__slots__ = [
    'data_index',
    'reserved',
]
struct_anon_23._fields_ = [
    ('data_index', c_int),
    ('reserved', c_int),
]

MDF_EM_START_TRIAL = struct_anon_23 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 94

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 101
class struct_anon_24(Structure):
    pass

struct_anon_24.__slots__ = [
    'first_data_index',
    'last_data_index',
]
struct_anon_24._fields_ = [
    ('first_data_index', c_int),
    ('last_data_index', c_int),
]

MDF_EM_ADAPT_NOW = struct_anon_24 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 101

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 105
class struct_anon_25(Structure):
    pass

struct_anon_25.__slots__ = [
    'drift_correction',
]
struct_anon_25._fields_ = [
    ('drift_correction', c_double * 18),
]

MDF_EM_UPDATE_DRIFT_CORRECTION = struct_anon_25 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 105

MDF_EM_MOD_DEPTH_CUTOFF = c_double # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 117

MDF_EM_SET_PDS = POINTER(c_char) # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 118

MDF_EM_PDS = POINTER(c_char) # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 119

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 138
class struct_anon_26(Structure):
    pass

struct_anon_26.__slots__ = [
    'Norm2RealFactor',
    'ModDepthCutoff',
    'RSquaredCutoff',
    'PredictFRFilter',
    'AdaptFRFilter',
    'TargetFilter',
    'RegressionGroups',
    'tag',
    'ControlledDims',
    'numAdaptReps',
]
struct_anon_26._fields_ = [
    ('Norm2RealFactor', c_double * 18),
    ('ModDepthCutoff', c_double),
    ('RSquaredCutoff', c_double),
    ('PredictFRFilter', c_double * 33),
    ('AdaptFRFilter', c_double * 33),
    ('TargetFilter', c_double * 33),
    ('RegressionGroups', c_double * 18),
    ('tag', c_char * 64),
    ('ControlledDims', c_double * 18),
    ('numAdaptReps', c_double),
]

PVAConfig = struct_anon_26 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 138

MDF_PVA_CONFIG = PVAConfig # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 142

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 151
class struct_anon_27(Structure):
    pass

struct_anon_27.__slots__ = [
    'tag',
    'PV',
    'usedIndices',
]
struct_anon_27._fields_ = [
    ('tag', c_char * 64),
    ('PV', c_double * (200 * 8)),
    ('usedIndices', c_int * 200),
]

PVAState = struct_anon_27 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 151

MDF_PVA_STATE = PVAState # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 155

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 164
class struct_anon_28(Structure):
    pass

struct_anon_28.__slots__ = [
    'targTag',
    'attenuationLevel',
]
struct_anon_28._fields_ = [
    ('targTag', c_char * 64),
    ('attenuationLevel', c_double * 200),
]

PVAAttenuateCommand = struct_anon_28 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 164

MDF_PVA_ATTENUATE_COMMAND = PVAAttenuateCommand # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 172

STRING_DATA = POINTER(c_char) # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 69

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 22
class struct_anon_29(Structure):
    pass

struct_anon_29.__slots__ = [
    'source_index',
    'reserved',
    'source_timestamp',
    'count_interval',
    'counts',
]
struct_anon_29._fields_ = [
    ('source_index', c_int),
    ('reserved', c_int),
    ('source_timestamp', c_double),
    ('count_interval', c_double),
    ('counts', c_ubyte * (96 * 6)),
]

MDF_RAW_SPIKECOUNT = struct_anon_29 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 22

SPIKE_COUNT_DATA_TYPE = c_ubyte # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 24

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 30
class struct_anon_30(Structure):
    pass

struct_anon_30.__slots__ = [
    'sample_header',
    'source_timestamp',
    'count_interval',
    'counts',
]
struct_anon_30._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('source_timestamp', c_double),
    ('count_interval', c_double),
    ('counts', SPIKE_COUNT_DATA_TYPE * (3 * (96 * 6))),
]

MDF_SPM_SPIKECOUNT = struct_anon_30 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 30

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 34
class struct_anon_31(Structure):
    pass

struct_anon_31.__slots__ = [
    'sample_header',
    'source_timestamp',
]
struct_anon_31._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('source_timestamp', c_double),
]

MDF_SAMPLE_GENERATED = struct_anon_31 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 34

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 41
class struct_anon_32(Structure):
    pass

struct_anon_32.__slots__ = [
    'sample_response_timestamp',
    'sample_alignment_timestamp',
    'sample_response_count',
    'sample_alignment_count',
]
struct_anon_32._fields_ = [
    ('sample_response_timestamp', c_double),
    ('sample_alignment_timestamp', c_double),
    ('sample_response_count', c_uint),
    ('sample_alignment_count', c_uint),
]

MDF_SAMPLE_RESPONSE = struct_anon_32 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 41

MDF_INPUT_DOF_DATA = INPUT_DOF_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 87

MDF_OPERATOR_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 90

MDF_FIXTURED_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 93

MDF_SHADOW_COMPOSITE_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 96

MDF_FIXTURED_COMPOSITE_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 99

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 107
class struct_anon_33(Structure):
    pass

struct_anon_33.__slots__ = [
    'sample_header',
    'tool_pos',
    'wrist_pos',
]
struct_anon_33._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('tool_pos', c_double * 7),
    ('wrist_pos', c_double * 7),
]

MDF_PROBOT_FEEDBACK = struct_anon_33 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 107

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 178
class struct_anon_34(Structure):
    pass

struct_anon_34.__slots__ = [
    'sample_header',
    'command',
    'mode',
    'reserved',
]
struct_anon_34._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('command', c_double * 18),
    ('mode', c_int),
    ('reserved', c_int),
]

MDF_GROBOT_COMMAND = struct_anon_34 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 178

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 184
class struct_anon_35(Structure):
    pass

struct_anon_35.__slots__ = [
    'command',
    'mode',
    'reserved',
]
struct_anon_35._fields_ = [
    ('command', c_double * 18),
    ('mode', c_int),
    ('reserved', c_int),
]

MDF_GROBOT_BYPASS = struct_anon_35 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 184

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 188
class struct_anon_36(Structure):
    pass

struct_anon_36.__slots__ = [
    'Cmd',
]
struct_anon_36._fields_ = [
    ('Cmd', c_double * 6),
]

MDF_OPTO_CNTRL_CMD = struct_anon_36 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 188

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 192
class struct_anon_37(Structure):
    pass

struct_anon_37.__slots__ = [
    'Cmd',
]
struct_anon_37._fields_ = [
    ('Cmd', c_double * 4),
]

MDF_OPTO_POS_CMD = struct_anon_37 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 192

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 196
class struct_anon_38(Structure):
    pass

struct_anon_38.__slots__ = [
    'Cmd',
]
struct_anon_38._fields_ = [
    ('Cmd', c_double * 4),
]

MDF_KIN_POS_CMD = struct_anon_38 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 196

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 205
class struct_anon_39(Structure):
    pass

struct_anon_39.__slots__ = [
    'x',
    'y',
    'z',
    'w',
    'Which',
    'Reserved',
]
struct_anon_39._fields_ = [
    ('x', c_double * 20),
    ('y', c_double * 20),
    ('z', c_double * 20),
    ('w', c_double * 20),
    ('Which', c_int),
    ('Reserved', c_int),
]

MDF_KINECT_SKELETON = struct_anon_39 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 205

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 219
class struct_anon_40(Structure):
    pass

struct_anon_40.__slots__ = [
    'ind_force',
    'mid_force',
    'rng_force',
    'lit_force',
    'thb_force',
    'ind_accel',
    'mid_accel',
    'rng_accel',
    'lit_accel',
    'thb_accel',
]
struct_anon_40._fields_ = [
    ('ind_force', c_double * 3),
    ('mid_force', c_double * 3),
    ('rng_force', c_double * 3),
    ('lit_force', c_double * 3),
    ('thb_force', c_double * 3),
    ('ind_accel', c_double * 3),
    ('mid_accel', c_double * 3),
    ('rng_accel', c_double * 3),
    ('lit_accel', c_double * 3),
    ('thb_accel', c_double * 3),
]

MDF_GROBOT_SEGMENT_PERCEPTS = struct_anon_40 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 219

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 231
class struct_anon_41(Structure):
    pass

struct_anon_41.__slots__ = [
    'configID',
    'afcf',
    'pulses',
    'amp1',
    'amp2',
    'width1',
    'width2',
    'frequency',
    'interphase',
]
struct_anon_41._fields_ = [
    ('configID', c_int),
    ('afcf', c_int),
    ('pulses', c_double),
    ('amp1', c_double),
    ('amp2', c_double),
    ('width1', c_double),
    ('width2', c_double),
    ('frequency', c_double),
    ('interphase', c_double),
]

MDF_CERESTIM_CONFIG_MODULE = struct_anon_41 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 231

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 243
class struct_anon_42(Structure):
    pass

struct_anon_42.__slots__ = [
    'stop',
    'group_stimulus',
    'group_numChans',
    'group_channel',
    'group_pattern',
    'manual_stimulus',
    'manual_channel',
    'manual_pattern',
]
struct_anon_42._fields_ = [
    ('stop', c_int),
    ('group_stimulus', c_int),
    ('group_numChans', c_int),
    ('group_channel', c_int * 16),
    ('group_pattern', c_int * 16),
    ('manual_stimulus', c_int),
    ('manual_channel', c_int),
    ('manual_pattern', c_int),
]

MDF_CERESTIM_CONFIG_CHAN = struct_anon_42 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 243

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 249
class struct_anon_43(Structure):
    pass

struct_anon_43.__slots__ = [
    'j_ang',
    'j_vel',
    'j_trq',
]
struct_anon_43._fields_ = [
    ('j_ang', c_double * 28),
    ('j_vel', c_double * 28),
    ('j_trq', c_double * 28),
]

MDF_GROBOT_RAW_FEEDBACK = struct_anon_43 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 249

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 257
class struct_anon_44(Structure):
    pass

struct_anon_44.__slots__ = [
    'sample_header',
    'position',
    'velocity',
    'force',
    'cori_matrix',
]
struct_anon_44._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('position', c_double * 18),
    ('velocity', c_double * 18),
    ('force', c_double * 18),
    ('cori_matrix', c_double * 9),
]

MDF_GROBOT_FEEDBACK = struct_anon_44 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 257

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 263
class struct_anon_45(Structure):
    pass

struct_anon_45.__slots__ = [
    'data_dir',
]
struct_anon_45._fields_ = [
    ('data_dir', c_char * 128),
]

MDF_SESSION_CONFIG = struct_anon_45 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 263

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 270
class struct_anon_46(Structure):
    pass

struct_anon_46.__slots__ = [
    'sample_header',
    'data',
]
struct_anon_46._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('data', c_double * 30),
]

MDF_GLOVE_DATA = struct_anon_46 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 270

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 274
class struct_anon_47(Structure):
    pass

struct_anon_47.__slots__ = [
    'sample_header',
    'data',
]
struct_anon_47._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('data', c_double * 30),
]

MDF_MICROSTRAIN_DATA = struct_anon_47 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 274

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 280
class struct_anon_48(Structure):
    pass

struct_anon_48.__slots__ = [
    'chosen_channel_mask',
]
struct_anon_48._fields_ = [
    ('chosen_channel_mask', c_int * 1728),
]

MDF_EM_OVERRIDE_CONFIG = struct_anon_48 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 280

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 285
class struct_anon_49(Structure):
    pass

struct_anon_49.__slots__ = [
    'next_tool_id',
    'reserved',
]
struct_anon_49._fields_ = [
    ('next_tool_id', c_int),
    ('reserved', c_int),
]

MDF_CHANGE_TOOL = struct_anon_49 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 285

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 290
class struct_anon_50(Structure):
    pass

struct_anon_50.__slots__ = [
    'tool_id',
    'reserved',
]
struct_anon_50._fields_ = [
    ('tool_id', c_int),
    ('reserved', c_int),
]

MDF_CHANGE_TOOL_COMPLETE = struct_anon_50 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 290

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 322
class struct_anon_51(Structure):
    pass

struct_anon_51.__slots__ = [
    'id',
    'rep_num',
    'use_for_calib',
    'target_combo_index',
    'timed_out_conseq',
    'idle_gateable',
    'reach_offset',
    'relax_arm',
    'idle_timeout',
    'ts_time',
    'target',
    'coriMatrix',
    'idle_target',
    'trans_threshold',
    'ori_threshold',
    'trans_threshold_f',
    'ori_threshold_f',
    'finger_threshold',
    'finger_threshold_judging_method',
    'finger_threshold_judging_polarity',
    'trans_threshold_judging_polarity',
    'ori_threshold_judging_polarity',
    'trans_threshold_f_judging_polarity',
    'ori_threshold_f_judging_polarity',
    'timeout',
    'tags',
]
struct_anon_51._fields_ = [
    ('id', c_int),
    ('rep_num', c_int),
    ('use_for_calib', c_int),
    ('target_combo_index', c_int),
    ('timed_out_conseq', c_int),
    ('idle_gateable', c_int),
    ('reach_offset', c_int),
    ('relax_arm', c_int),
    ('idle_timeout', c_double),
    ('ts_time', c_double),
    ('target', c_double * (18 + 15)),
    ('coriMatrix', c_double * 9),
    ('idle_target', c_double * 18),
    ('trans_threshold', c_double),
    ('ori_threshold', c_double),
    ('trans_threshold_f', c_double),
    ('ori_threshold_f', c_double),
    ('finger_threshold', c_double * (10 + 15)),
    ('finger_threshold_judging_method', c_int * (10 + 15)),
    ('finger_threshold_judging_polarity', c_int * (10 + 15)),
    ('trans_threshold_judging_polarity', c_int),
    ('ori_threshold_judging_polarity', c_int),
    ('trans_threshold_f_judging_polarity', c_int),
    ('ori_threshold_f_judging_polarity', c_int),
    ('timeout', c_double),
    ('tags', c_char * 64),
]

MDF_TASK_STATE_CONFIG = struct_anon_51 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 322

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 328
class struct_anon_52(Structure):
    pass

struct_anon_52.__slots__ = [
    'id',
    'reserved',
    'reason',
]
struct_anon_52._fields_ = [
    ('id', c_int),
    ('reserved', c_int),
    ('reason', c_char * 64),
]

MDF_JUDGE_VERDICT = struct_anon_52 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 328

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 334
class struct_anon_53(Structure):
    pass

struct_anon_53.__slots__ = [
    'id',
    'outcome',
    'reason',
]
struct_anon_53._fields_ = [
    ('id', c_int),
    ('outcome', c_int),
    ('reason', c_char * 64),
]

MDF_END_TASK_STATE = struct_anon_53 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 334

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 340
class struct_anon_54(Structure):
    pass

struct_anon_54.__slots__ = [
    'source_index',
    'reserved',
    'source_timestamp',
]
struct_anon_54._fields_ = [
    ('source_index', c_int),
    ('reserved', c_int),
    ('source_timestamp', c_double),
]

MDF_RAW_SAMPLE_RESPONSE = struct_anon_54 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 340

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 345
class struct_anon_55(Structure):
    pass

struct_anon_55.__slots__ = [
    'module_name',
    'version',
]
struct_anon_55._fields_ = [
    ('module_name', c_char * 64),
    ('version', c_char * 64),
]

MDF_CODE_VERSION = struct_anon_55 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 345

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 352
class struct_anon_56(Structure):
    pass

struct_anon_56.__slots__ = [
    'sample_header',
    'source_timestamp',
    'count_interval',
    'rates',
]
struct_anon_56._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('source_timestamp', c_double),
    ('count_interval', c_double),
    ('rates', c_double * (3 * (96 * 6))),
]

MDF_SPM_FIRINGRATE = struct_anon_56 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 352

MDF_EM_DECODER_CONFIGURATION = POINTER(c_ubyte) # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 354

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 358
class struct_anon_57(Structure):
    pass

struct_anon_57.__slots__ = [
    'full_path',
]
struct_anon_57._fields_ = [
    ('full_path', c_char * 128),
]

MDF_LOAD_DECODER_CONFIG = struct_anon_57 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 358

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 366
class struct_anon_58(Structure):
    pass

struct_anon_58.__slots__ = [
    'load_calibration',
    'calib_session_id',
    'num_reps',
    'reserved',
    'subject_name',
]
struct_anon_58._fields_ = [
    ('load_calibration', c_int),
    ('calib_session_id', c_int),
    ('num_reps', c_int),
    ('reserved', c_int),
    ('subject_name', c_char * 64),
]

MDF_XM_START_SESSION = struct_anon_58 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 366

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 370
class struct_anon_59(Structure):
    pass

struct_anon_59.__slots__ = [
    'module_name',
]
struct_anon_59._fields_ = [
    ('module_name', c_char * 64),
]

MDF_PING = struct_anon_59 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 370

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 374
class struct_anon_60(Structure):
    pass

struct_anon_60.__slots__ = [
    'module_name',
]
struct_anon_60._fields_ = [
    ('module_name', c_char * 64),
]

MDF_PING_ACK = struct_anon_60 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 374

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 378
class struct_anon_61(Structure):
    pass

struct_anon_61.__slots__ = [
    'data',
]
struct_anon_61._fields_ = [
    ('data', c_double * 32),
]

MDF_DEBUG_VECTOR = struct_anon_61 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 378

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 382
class struct_anon_62(Structure):
    pass

struct_anon_62.__slots__ = [
    'config',
]
struct_anon_62._fields_ = [
    ('config', c_char * 64),
]

MDF_APP_START = struct_anon_62 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 382

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 386
class struct_anon_63(Structure):
    pass

struct_anon_63.__slots__ = [
    'module',
]
struct_anon_63._fields_ = [
    ('module', c_char * 64),
]

MDF_MODULE_START = struct_anon_63 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 386

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 395
class struct_anon_64(Structure):
    pass

struct_anon_64.__slots__ = [
    'time',
    'chan',
    'unit',
    'box_id',
    'length',
    'snippet',
]
struct_anon_64._fields_ = [
    ('time', c_double),
    ('chan', c_int),
    ('unit', c_int),
    ('box_id', c_int),
    ('length', c_int),
    ('snippet', c_short * 48),
]

MDF_SPM_SPIKE_SNIPPET = struct_anon_64 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 395

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 403
class struct_anon_65(Structure):
    pass

struct_anon_65.__slots__ = [
    'time',
    'chan',
    'unit',
    'box_id',
]
struct_anon_65._fields_ = [
    ('time', c_double * 256),
    ('chan', c_short * 256),
    ('unit', c_char * 256),
    ('box_id', c_char * 256),
]

MDF_SPM_SPIKE_TIMES = struct_anon_65 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 403

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 408
class struct_anon_66(Structure):
    pass

struct_anon_66.__slots__ = [
    'state',
    'reserved',
]
struct_anon_66._fields_ = [
    ('state', c_int),
    ('reserved', c_int),
]

MDF_IDLY_LABELLING = struct_anon_66 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 408

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 413
class struct_anon_67(Structure):
    pass

struct_anon_67.__slots__ = [
    'sample_header',
    'drift_correction',
]
struct_anon_67._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('drift_correction', c_double * 18),
]

MDF_EM_DRIFT_CORRECTION = struct_anon_67 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 413

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 420
class struct_anon_68(Structure):
    pass

struct_anon_68.__slots__ = [
    'movement_id',
    'num_cycles',
    'sequence',
    'amplitude',
]
struct_anon_68._fields_ = [
    ('movement_id', c_int),
    ('num_cycles', c_int),
    ('sequence', c_int * 8),
    ('amplitude', c_double * 3),
]

MDF_DENSO_WIGGLE = struct_anon_68 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 420

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 425
class struct_anon_69(Structure):
    pass

struct_anon_69.__slots__ = [
    'id',
    'reserved',
]
struct_anon_69._fields_ = [
    ('id', c_int),
    ('reserved', c_int),
]

MDF_PLAY_SOUND = struct_anon_69 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 425

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 429
class struct_anon_70(Structure):
    pass

struct_anon_70.__slots__ = [
    'time',
]
struct_anon_70._fields_ = [
    ('time', c_double),
]

MDF_ARTIFACT_REJECTED = struct_anon_70 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 429

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 437
class struct_anon_71(Structure):
    pass

struct_anon_71.__slots__ = [
    'sample_header',
    'score',
    'gain',
    'idle',
    'reserved',
]
struct_anon_71._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('score', c_double),
    ('gain', c_double),
    ('idle', c_int),
    ('reserved', c_int),
]

MDF_IDLE = struct_anon_71 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 437

MDF_WAM_FEEDBACK = ROBOT_CONTROL_SPACE_ACTUAL_STATE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 439

MDF_WAM_HAND_FEEDBACK = ROBOT_CONTROL_SPACE_ACTUAL_STATE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 440

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 445
class struct_anon_72(Structure):
    pass

struct_anon_72.__slots__ = [
    'target',
    'coriMatrix',
]
struct_anon_72._fields_ = [
    ('target', c_double * 18),
    ('coriMatrix', c_double * 9),
]

MDF_PLANNER_CONTROL_CONFIG = struct_anon_72 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 445

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 452
class struct_anon_73(Structure):
    pass

struct_anon_73.__slots__ = [
    'sample_header',
    'pos',
    'controlledDims',
    'overrideDims',
]
struct_anon_73._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('pos', c_double * 8),
    ('controlledDims', c_int * 8),
    ('overrideDims', c_int * 8),
]

MDF_ROBOT_JOINT_COMMAND = struct_anon_73 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 452

MDF_IDLEGATED_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 454

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 102
class struct_anon_74(Structure):
    pass

struct_anon_74.__slots__ = [
    'event_time',
    'event_code',
    'reserved',
]
struct_anon_74._fields_ = [
    ('event_time', c_double),
    ('event_code', c_int),
    ('reserved', c_int),
]

MDF_TRIAL_EVENT = struct_anon_74 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 102

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 110
class struct_anon_75(Structure):
    pass

struct_anon_75.__slots__ = [
    'rep_no',
    'trial_no',
    'num_reward_states',
    'reserved',
]
struct_anon_75._fields_ = [
    ('rep_no', c_int),
    ('trial_no', c_int),
    ('num_reward_states', c_int),
    ('reserved', c_int),
]

MDF_TRIAL_CONFIG = struct_anon_75 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 110

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 116
class struct_anon_76(Structure):
    pass

struct_anon_76.__slots__ = [
    'success',
    'reserved',
]
struct_anon_76._fields_ = [
    ('success', c_int),
    ('reserved', c_int),
]

MDF_TRIAL_STATUS = struct_anon_76 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 116

MDF_ROBOT_ACTUAL_STATE = ROBOT_ACTUAL_STATE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 144

MDF_ROBOT_CONTROL_STATE = ROBOT_CONTROL_STATE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 145

MDF_ROBOT_CONTROL_SPACE_ACTUAL_STATE = ROBOT_CONTROL_SPACE_ACTUAL_STATE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 146

MDF_ROBOT_CONTROL_CONFIG = ROBOT_CONTROL_CONFIG # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 152

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 162
class struct_anon_77(Structure):
    pass

struct_anon_77.__slots__ = [
    'duration_ms',
    'num_clicks',
]
struct_anon_77._fields_ = [
    ('duration_ms', c_double),
    ('num_clicks', c_double),
]

MDF_GIVE_REWARD = struct_anon_77 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 162

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 180
class struct_anon_78(Structure):
    pass

struct_anon_78.__slots__ = [
    'high',
    'low',
]
struct_anon_78._fields_ = [
    ('high', c_double * 12),
    ('low', c_double * 12),
]

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 187
class struct_anon_79(Structure):
    pass

struct_anon_79.__slots__ = [
    'limits',
    'reserved',
    'internal_sampling',
    'sample_interval',
]
struct_anon_79._fields_ = [
    ('limits', struct_anon_78),
    ('reserved', c_int),
    ('internal_sampling', c_int),
    ('sample_interval', c_double),
]

MDF_IO_START_STREAM = struct_anon_79 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 187

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 205
class struct_anon_80(Structure):
    pass

struct_anon_80.__slots__ = [
    'sample_header',
    'sample_interval',
    'data',
]
struct_anon_80._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('sample_interval', c_double),
    ('data', c_double * 12),
]

MDF_ANALOG_STREAM = struct_anon_80 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 205

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 216
class struct_anon_81(Structure):
    pass

struct_anon_81.__slots__ = [
    'source_time',
    'event_time',
    'sample_no',
]
struct_anon_81._fields_ = [
    ('source_time', c_double),
    ('event_time', c_double),
    ('sample_no', c_int),
]

KNOB_EVENT_DATA = struct_anon_81 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 216

MDF_KNOB_TOUCHED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 218

MDF_KNOB_TURNED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 220

MDF_KNOB_ANTI_TURNED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 222

MDF_KNOB_OVER_TURNED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 224

MDF_DOOR_MOVED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 226

MDF_DOOR_OPENED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 228

MDF_DOOR_ANTI_OPENED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 230

MDF_DOOR_OVER_OPENED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 232

MDF_KNOB_MOVED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 234

MDF_DOOR_UN_OPENED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 236

MDF_KNOB_RELEASED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 238

MDF_PAD_PRESSED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 241

MDF_PAD_STEADY = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 243

MDF_PAD_PERTURBED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 245

MDF_PAD_RELEASED = KNOB_EVENT_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 247

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 264
class struct_anon_82(Structure):
    pass

struct_anon_82.__slots__ = [
    'position_no',
    'movement_id',
]
struct_anon_82._fields_ = [
    ('position_no', c_int),
    ('movement_id', c_int),
]

MDF_DENSO_MOVE = struct_anon_82 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 264

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 268
class struct_anon_83(Structure):
    pass

struct_anon_83.__slots__ = [
    'speed',
]
struct_anon_83._fields_ = [
    ('speed', c_double),
]

MDF_DENSO_SET_SPEED = struct_anon_83 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 268

MDF_DENSO_MOVE_CONTINUE = MDF_DENSO_MOVE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 270

MDF_DENSO_NOT_READY = STRING_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 282

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 286
class struct_anon_84(Structure):
    pass

struct_anon_84.__slots__ = [
    'movement_id',
    'reserved',
]
struct_anon_84._fields_ = [
    ('movement_id', c_int),
    ('reserved', c_int),
]

RESPONSE_DATA_TO_DENSO_MOVE = struct_anon_84 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 286

MDF_DENSO_MOVE_COMPLETE = RESPONSE_DATA_TO_DENSO_MOVE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 287

MDF_DENSO_MOVE_FAILED = RESPONSE_DATA_TO_DENSO_MOVE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 288

MDF_DENSO_MOVE_INVALID = RESPONSE_DATA_TO_DENSO_MOVE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 289

MDF_DENSO_HALTED = RESPONSE_DATA_TO_DENSO_MOVE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 290

MDF_EM_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 301

MDF_EM_AUX_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 304

MDF_COMPOSITE_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 307

MDF_ROBOT_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 310

MDF_PLANNER_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 313

MDF_PLANNER_STATE = PLANNER_STATE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 316

MDF_PLAN_PROCESSOR_STATE = PLAN_PROCESSOR_STATE # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 319

MDF_FM_MOVEMENT_COMMAND = MOVEMENT_COMMAND_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 327

MDF_OVERRIDE_COMMAND = OVERRIDE_COMMAND # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 338

MDF_JVEL_COMMAND = JVEL_COMMAND # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 340

MDF_COMPONENT_DELAY_MSG_TYPES = c_int * 6 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 351

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 356
class struct_anon_85(Structure):
    pass

struct_anon_85.__slots__ = [
    'sample_header',
    'Components',
    'Total',
]
struct_anon_85._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('Components', c_double * 6),
    ('Total', c_double),
]

DELAY_DATA = struct_anon_85 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 356

MDF_ESTIMATED_DELAY = DELAY_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 358

MDF_MEASURED_DELAY = DELAY_DATA # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 361

MDF_CLEAR_FUNCTION = POINTER(c_char) # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 368

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 384
class struct_anon_86(Structure):
    pass

struct_anon_86.__slots__ = [
    'sample_header',
    'cloud',
    'nTargs',
    'spacer',
]
struct_anon_86._fields_ = [
    ('sample_header', SAMPLE_HEADER),
    ('cloud', c_double * (18 * 32)),
    ('nTargs', c_int),
    ('spacer', c_int),
]

TARG_CLOUD = struct_anon_86 # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 384

MDF_TARG_CLOUD = TARG_CLOUD # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 386

MDF_ATTENTION = c_double # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 399

__const = c_int # <command-line>: 5

# <command-line>: 8
try:
    CTYPESGEN = 1
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 30
try:
    HID_MAIN_HOST = 1
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 35
try:
    MID_EXEC_MOD = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 37
try:
    MID_SPM_MOD = 20
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 38
try:
    MID_SPM_MOD1 = 21
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 39
try:
    MID_SPM_MOD2 = 22
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 40
try:
    MID_SPM_MOD3 = 23
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 41
try:
    MID_SPM_MOD4 = 24
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 43
try:
    MID_IO_MOD = 60
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 44
try:
    MID_DENSO_MOD = 80
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 45
try:
    MID_DENSO_TRY = 81
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 46
try:
    MID_WATCHDOG = 97
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 47
try:
    MID_SILICON_MONKEY = 72
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 48
try:
    MID_WAM = 73
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 49
try:
    MID_OPTOTRAK = 74
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 50
try:
    MID_SIMPLE_PLANNER = 76
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 52
try:
    MID_EXTRACTION_MOD = 50
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 54
try:
    MID_VIZ = 85
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 55
try:
    MID_HANDY_DANDY = 86
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 56
try:
    MID_DRIFTY = 93
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 57
try:
    MID_THE_DECIDER = 94
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 58
try:
    MID_PS3_COMMAND_MODULE = 95
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 59
try:
    MID_PS3_RAW_MODULE = 96
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 60
try:
    MID_SILICON_MONKEY_BRAIN = 91
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 61
try:
    MID_PS3_MODULE = 92
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 62
try:
    MID_TEST_MOD = 99
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 14
def check_flag_bits(A, bitmask):
    return ((A & bitmask) == bitmask)

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 15
def clear_flag_bits(A, bitmask):
    return (A & (~bitmask))

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 16
def set_flag_bits(A, bitmask):
    return (A | bitmask)

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 28
try:
    SF_ALIGNMENT = 1
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 29
try:
    SF_UNFREEZE = 2
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 30
try:
    SF_IRREGULAR = 4
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 31
try:
    SF_FRACTINT = 8
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 35
try:
    MAX_CONTROL_DIMS = 18
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 37
try:
    MAX_EM_DIMS = MAX_CONTROL_DIMS
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 40
try:
    TAG_LENGTH = 64
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 41
try:
    NUM_D_COLS = 16
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 42
try:
    MAX_D_COLS = 32
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/common_defs.h: 54
try:
    MAX_INPUT_DOFS = 21
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 10
try:
    PS3_B_L1 = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 11
try:
    PS3_B_L2 = 8
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 12
try:
    PS3_B_R1 = 11
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 13
try:
    PS3_B_R2 = 9
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 14
try:
    PS3_B_LDIR = 7
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 15
try:
    PS3_B_RDIR = 5
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 16
try:
    PS3_B_UDIR = 4
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 17
try:
    PS3_B_DDIR = 6
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 18
try:
    PS3_B_TRIANGLE = 12
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 19
try:
    PS3_B_SQUARE = 15
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 20
try:
    PS3_B_CIRCLE = 13
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 21
try:
    PS3_B_X = 14
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 22
try:
    PS3_B_SELECT = 0
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 23
try:
    PS3_B_START = 3
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 24
try:
    PS3_B_L3 = 1
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 25
try:
    PS3_B_R3 = 2
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 28
try:
    PS3_C_LSTICKH = 0
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 29
try:
    PS3_C_LSTICKV = 1
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 30
try:
    PS3_C_RSTICKH = 2
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 31
try:
    PS3_C_RSTICKV = 3
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 33
try:
    PS3_C_L1 = 14
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 34
try:
    PS3_C_L2 = 12
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 35
try:
    PS3_C_R1 = 15
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 36
try:
    PS3_C_R2 = 13
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 37
try:
    PS3_C_LDIR = 11
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 38
try:
    PS3_C_RDIR = 9
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 39
try:
    PS3_C_UDIR = 8
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 40
try:
    PS3_C_DDIR = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 41
try:
    PS3_C_TRIANGLE = 16
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 42
try:
    PS3_C_SQUARE = 19
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 43
try:
    PS3_C_CIRCLE = 17
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 44
try:
    PS3_C_X = 18
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 47
try:
    PS3_N_SENSORS = 21
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 48
try:
    PS3_N_ACCEL = 2
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 49
try:
    BUTTON_PRESS = 2135
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 50
try:
    BUTTON_RELEASE = 2136
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 51
try:
    STICK_READING = 2137
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 53
try:
    MT_PS3_BUTTON_PRESS = BUTTON_PRESS
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 54
try:
    MT_PS3_BUTTON_RELEASE = BUTTON_RELEASE
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3Defines.h: 55
try:
    MT_PS3_STICK_READING = STICK_READING
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 66
try:
    MAX_CONTROLLERS = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 139
try:
    MT_PS3_RAW_CONFIG = 6543
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 140
try:
    MT_PS3_SIMPLE_BUTTON_PRESS = 6544
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 141
try:
    MT_PS3_SIMPLE_BUTTON_RELEASE = 6545
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 142
try:
    MT_PS3_GENERIC_DATA = 6546
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 4
try:
    MAX_REDUCED_SPIKE_CHANS = 200
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 7
try:
    MAX_EM_DIMENSIONS = MAX_CONTROL_DIMS
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 10
try:
    MT_EM_START_SESSION = 1600
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 11
try:
    MT_EM_END_SESSION = 1601
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 12
try:
    MT_EM_FREEZE = 1602
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 13
try:
    MT_EM_RESET_STATE = 1603
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 14
try:
    MT_EM_UNFREEZE = 1604
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 15
try:
    MT_EM_START_TRIAL = 1605
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 16
try:
    MT_EM_END_TRIAL = 1606
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 17
try:
    MT_EM_DISCARD_TRIAL = 1607
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 18
try:
    MT_EM_ADAPT_NOW = 1608
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 19
try:
    MT_EM_FEEDBACK = 1609
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 20
try:
    MT_EM_MOD_DEPTH_CUTOFF = 1610
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 21
try:
    MT_EM_PAUSE_COLLECTION = 1611
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 22
try:
    MT_EM_RESUME_COLLECTION = 1612
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 23
try:
    MT_EM_GET_PDS = 1613
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 24
try:
    MT_EM_SET_PDS = 1614
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 25
try:
    MT_EM_AGGREGATE_DATA_NOW = 1615
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 26
try:
    MT_EM_RESET_AGGREGATION = 1616
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 27
try:
    MT_EM_CORRECT_DRIFT_NOW = 1617
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 28
try:
    MT_EM_UPDATE_DRIFT_CORRECTION = 1618
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 29
try:
    MT_RELOAD_PVA_CONFIG = 1619
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 32
try:
    MT_EM_READY = 1650
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 33
try:
    MT_EM_FROZEN = 1651
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 34
try:
    MT_EM_ADAPT_DONE = 1652
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 35
try:
    MT_EM_ADAPT_FAILED = 1653
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 36
try:
    MT_EM_MOD_DEPTH_FAILED = 1654
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 37
try:
    MT_EM_MOD_DEPTH_SUCCEEDED = 1655
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 38
try:
    MT_EM_PDS = 1656
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 39
try:
    MT_EM_ALREADY_FROZEN = 1657
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 40
try:
    MT_EM_DRIFT_CORRECTED = 1658
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 67
try:
    MT_RELOAD_CONFIGURATION = 1004
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 140
try:
    MT_PVA_CONFIG = 382
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 153
try:
    MT_PVA_STATE = 383
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 166
try:
    MT_DECISION = 384
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 168
try:
    MT_TRAINING_BEGIN = 385
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 170
try:
    MT_DO_IT_DECIDER = 386
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/Extraction/ExtractionConfig.h: 171
try:
    MT_PVA_ATTENUATE_COMMAND = 387
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 71
try:
    MAX_FILENAME_LENGTH = 256
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 6
try:
    MAX_SPIKE_SOURCES = 3
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 7
try:
    MAX_SPIKE_CHANS_PER_SOURCE = 96
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 8
try:
    MAX_UNITS_PER_CHAN = 6
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 9
try:
    MAX_TOTAL_SPIKE_CHANS_PER_SOURCE = (MAX_SPIKE_CHANS_PER_SOURCE * MAX_UNITS_PER_CHAN)
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 10
try:
    MAX_TOTAL_SPIKE_CHANS = (MAX_SPIKE_SOURCES * MAX_TOTAL_SPIKE_CHANS_PER_SOURCE)
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 12
try:
    RAW_COUNTS_PER_SAMPLE = 2
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 13
try:
    MSEC_PER_RAW_SAMPLE = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/spike_types.h: 14
try:
    SAMPLE_DT = ((RAW_COUNTS_PER_SAMPLE * MSEC_PER_RAW_SAMPLE) * 0.001)
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 7
try:
    MID_GROBOT_RAW_FEEDBACK = 19
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 8
try:
    MID_GROBOT_FEEDBACK = 18
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 9
try:
    MID_DIGITAL_IO = 17
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 10
try:
    MID_TASK_JUDGE = 16
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 11
try:
    MID_SI_MOVEMENT = 15
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 12
try:
    MID_INPUT_TRANSFORM = 14
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 13
try:
    MID_SIMPLE_ARBITRATOR = 13
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 14
try:
    MID_OUTPUT_TRANSFORM = 12
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 15
try:
    MID_FEEDBACK_TRANSFORM = 11
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 16
try:
    MID_SAMPLE_GENERATOR = 29
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 17
try:
    MID_VIRTUAL_FIXTURING = 28
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 18
try:
    MID_CANNED_MOVEMENT = 27
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 19
try:
    MID_HAND_VIZ = 30
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 20
try:
    MID_CALIBRATION = 37
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 21
try:
    MID_SSH_CONTROLLER = 35
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 22
try:
    MID_IDLE_DETECTOR = 38
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 23
try:
    MID_ARDUINO_IO = 39
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 24
try:
    MID_POSITION_CONTROLLER = 40
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 25
try:
    MID_JOINT_CONTROLLER = 42
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 27
try:
    MID_WAM_BHAND = 25
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 30
try:
    MID_EM_OVERRIDE_CONFIG = 31
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 32
try:
    MID_OPTO_MPL_CTRL = 32
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 33
try:
    MID_OBSTACLE_COURSE = 33
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 34
try:
    MID_SKELETON_CTRL = 34
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 37
try:
    MID_GROBOT_SEGMENT_PERCEPTS = 56
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 38
try:
    MID_CERESTIM_CONFIG = 57
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 39
try:
    MID_CERESTIM_CONTROL = 58
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 42
try:
    MID_COMMAND_SPACE_FEEDBACK_GUI = 89
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 43
try:
    MID_MESSAGE_WATCHER = 88
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 50
try:
    MT_GROBOT_SEGMENT_PERCEPTS = 1888
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 51
try:
    MT_CERESTIM_CONFIG_MODULE = 1889
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 52
try:
    MT_CERESTIM_CONFIG_CHAN = 1890
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 56
try:
    MT_GROBOT_COMMAND = 1700
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 57
try:
    MT_GROBOT_RAW_FEEDBACK = 1701
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 58
try:
    MT_GROBOT_FEEDBACK = 1702
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 59
try:
    MT_COMMANDSPACE_FEEDBACK = 1703
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 60
try:
    MT_GROBOT_BYPASS = 1704
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 61
try:
    MT_GROBOT_END_BYPASS = 1707
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 63
try:
    MT_MICROSTRAIN_DATA = 1705
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 64
try:
    MT_GLOVE_DATA = 1706
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 68
try:
    MT_EM_OVERRIDE_CONFIG = 1708
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 70
try:
    MT_OPTO_CNTRL_CMD = 1709
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 71
try:
    MT_OPTO_POS_CMD = 1712
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 72
try:
    MT_KIN_POS_CMD = 1713
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 73
try:
    MT_KINECT_SKELETON = 1711
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 74
try:
    MT_SESSION_CONFIG = 1710
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 76
try:
    MT_RAW_SPIKECOUNT = 1750
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 77
try:
    MT_SPM_SPIKECOUNT = 1751
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 78
try:
    MT_SAMPLE_GENERATED = 1752
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 79
try:
    MT_SAMPLE_RESPONSE = 1753
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 80
try:
    MT_RESET_SAMPLE_ALIGNMENT = 1754
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 82
try:
    MT_SYNCH_NOW = 1800
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 83
try:
    MT_SYNCH_START = 1801
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 84
try:
    MT_SYNCH_DONE = 1802
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 86
try:
    MT_INPUT_DOF_DATA = 1850
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 89
try:
    MT_OPERATOR_MOVEMENT_COMMAND = 1900
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 92
try:
    MT_FIXTURED_MOVEMENT_COMMAND = 1910
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 95
try:
    MT_SHADOW_COMPOSITE_MOVEMENT_COMMAND = 1919
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 98
try:
    MT_FIXTURED_COMPOSITE_MOVEMENT_COMMAND = 1920
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 101
try:
    MT_PROBOT_FEEDBACK = 1930
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 102
try:
    MAX_PROBOT_FEEDBACK_DIMS = 7
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 109
try:
    MT_CHANGE_TOOL = 1940
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 110
try:
    MT_CHANGE_TOOL_INVALID = 1941
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 111
try:
    MT_CHANGE_TOOL_COMPLETE = 1942
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 112
try:
    MT_CHANGE_TOOL_FAILED = 1943
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 114
try:
    MT_TASK_STATE_CONFIG = 1950
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 115
try:
    MT_JUDGE_VERDICT = 1960
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 116
try:
    MT_END_TASK_STATE = 1970
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 117
try:
    MT_RAW_SAMPLE_RESPONSE = 1980
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 118
try:
    MT_CODE_VERSION = 1990
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 119
try:
    MT_TRIAL_DATA_SAVED = 2080
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 120
try:
    MT_EM_DECODER_CONFIGURATION = 2090
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 121
try:
    MT_SPM_FIRINGRATE = 2100
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 122
try:
    MT_LOAD_DECODER_CONFIG = 2110
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 123
try:
    MT_APP_START = 2120
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 124
try:
    MT_APP_START_COMPLETE = 2121
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 125
try:
    MT_MODULE_START = 2125
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 126
try:
    MT_MODULE_START_COMPLETE = 2126
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 127
try:
    MT_EXIT_ACK = 2130
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 128
try:
    MT_PING = 2140
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 129
try:
    MT_PING_ACK = 2141
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 130
try:
    MT_XM_START_SESSION = 2150
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 131
try:
    MT_DEBUG_VECTOR = 2160
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 132
try:
    MT_SPM_SPIKE_SNIPPET = 2170
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 133
try:
    MT_SPM_SPIKE_TIMES = 2171
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 134
try:
    MT_XM_END_OF_SESSION = 2180
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 135
try:
    MT_IDLY_LABELLING = 2190
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 136
try:
    MT_IDLY_RESET_LABELLING = 2200
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 137
try:
    MT_EM_DRIFT_CORRECTION = 2210
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 138
try:
    MT_ARTIFACT_REJECTED = 2220
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 139
try:
    MT_PLAY_SOUND = 2230
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 140
try:
    MT_WAM_FEEDBACK = 2240
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 141
try:
    MT_WAM_HAND_FEEDBACK = 2242
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 142
try:
    MT_IDLE = 2250
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 143
try:
    MT_IDLE_DETECTION_ENDED = 2251
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 144
try:
    MT_PLANNER_CONTROL_CONFIG = 2260
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 145
try:
    MT_ROBOT_JOINT_COMMAND = 2270
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 146
try:
    MT_IDLEGATED_MOVEMENT_COMMAND = 2280
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 152
try:
    MAX_GROBOT_JOINTS = 28
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 153
try:
    MAX_GROBOT_COMMAND_DIMS = 18
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 154
try:
    MAX_GROBOT_FEEDBACK_DIMS = 18
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 155
try:
    MAX_OPTO_CTRL_JOINTS = 6
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 156
try:
    MAX_OPTO_POS = 4
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 157
try:
    MAX_KIN_POS = 4
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 158
try:
    NUM_FINGER_DIMS = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 159
try:
    KINECT_JOINTS = 20
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 160
try:
    MAX_JOINT_DIMS = 8
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 166
try:
    MPL_AT_ARM_EPV_FING_JV = 0
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 167
try:
    MPL_AT_ARM_EPV_FING_JP = 1
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 168
try:
    MPL_AT_ARM_JV_FING_JP = 2
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 169
try:
    MPL_AT_ALL_JV = 3
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 170
try:
    MPL_AT_ALL_JP = 4
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 171
try:
    MPL_AT_ARM_EPP_FING_JP = 5
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 259
try:
    MAX_DATA_DIR_LEN = 128
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 266
try:
    MAX_CYBER_GLOVE_DIMS = 30
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 277
try:
    MAX_EM_CHANNELS = 1728
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 292
try:
    MAX_FINGER_DIMS = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 293
try:
    MAX_PERCEPT_DIMS = 15
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 294
try:
    MAX_HAND_DIMS = (MAX_FINGER_DIMS + MAX_PERCEPT_DIMS)
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/config.h: 397
try:
    MAX_SPIKE_TIMES_PER_PACKET = 256
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 85
try:
    MT_XM_ABORT_SESSION = 171
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 87
try:
    MT_PROCEED_TO_Failure = 196
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 88
try:
    MT_PROCEED_TO_NextState = 198
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 90
try:
    MT_PAUSE_EXPERIMENT = 180
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 91
try:
    MT_RESUME_EXPERIMENT = 181
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 96
try:
    MT_TRIAL_EVENT = 100
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 104
try:
    MT_TRIAL_CONFIG = 101
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 112
try:
    MT_TRIAL_STATUS = 102
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 122
try:
    MT_WASHING_WITH_MONKEYS = 133
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 132
try:
    MT_LICKING_BEGIN = 150
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 133
try:
    MT_LICKING_END = 151
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 139
try:
    MT_ROBOT_ACTUAL_STATE = 934
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 140
try:
    MT_ROBOT_CONTROL_STATE = 935
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 141
try:
    MT_ROBOT_CONTROL_SPACE_ACTUAL_STATE = 936
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 142
try:
    MT_GRASP_EVENT = 937
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 151
try:
    MT_ROBOT_CONTROL_CONFIG = 938
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 158
try:
    MT_GIVE_REWARD = 600
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 164
try:
    NUM_ANALOG_STREAM_CHANS = 12
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 165
try:
    ASC_MONKEY_KNOB = 0
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 166
try:
    ASC_MONKEY_DOOR = 1
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 167
try:
    ASC_ROBOT_KNOB = 2
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 168
try:
    ASC_ROBOT_DOOR = 3
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 169
try:
    ASC_ARMREST_LF = 4
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 170
try:
    ASC_ARMREST_LB = 5
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 171
try:
    ASC_ARMREST_RF = 6
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 172
try:
    ASC_ARMREST_RB = 7
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 173
try:
    ASC_JOYPAD_LEFT_UD = 8
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 174
try:
    ASC_JOYPAD_LEFT_LR = 9
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 175
try:
    ASC_JOYPAD_RIGHT_UD = 10
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 176
try:
    ASC_JOYPAD_RIGHT_LR = 11
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 178
try:
    MT_IO_START_STREAM = 601
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 188
try:
    MT_IO_STOP_STREAM = 602
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 193
try:
    MT_JOYPAD_R1 = 610
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 194
try:
    MT_JOYPAD_R2 = 611
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 195
try:
    MT_JOYPAD_X = 612
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 196
try:
    MT_JOYPAD_PAD_BUTTON = 613
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 197
try:
    MT_READY_BUTTON = 614
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 200
try:
    MT_ANALOG_STREAM = 620
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 206
try:
    MT_IO_STREAM_STARTED = 621
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 207
try:
    MT_IO_STREAM_STOPPED = 622
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 217
try:
    MT_KNOB_TOUCHED = 640
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 219
try:
    MT_KNOB_TURNED = 641
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 221
try:
    MT_KNOB_ANTI_TURNED = 642
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 223
try:
    MT_KNOB_OVER_TURNED = 643
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 225
try:
    MT_DOOR_MOVED = 644
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 227
try:
    MT_DOOR_OPENED = 645
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 229
try:
    MT_DOOR_ANTI_OPENED = 646
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 231
try:
    MT_DOOR_OVER_OPENED = 647
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 233
try:
    MT_KNOB_MOVED = 648
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 235
try:
    MT_DOOR_UN_OPENED = 649
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 237
try:
    MT_KNOB_RELEASED = 650
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 240
try:
    MT_PAD_PRESSED = 660
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 242
try:
    MT_PAD_STEADY = 661
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 244
try:
    MT_PAD_PERTURBED = 662
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 246
try:
    MT_PAD_RELEASED = 663
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 253
try:
    MT_DENSO_CONFIG = 800
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 254
try:
    MT_DENSO_INITIALIZE = 801
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 255
try:
    MT_DENSO_MOVE = 802
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 256
try:
    MT_DENSO_HALT = 803
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 257
try:
    MT_DENSO_SET_SPEED = 804
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 258
try:
    MT_DENSO_WIGGLE = 806
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 259
try:
    MT_DENSO_MOVE_CONTINUE = 807
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 276
try:
    MT_DENSO_READY = 850
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 277
try:
    MT_DENSO_NOT_READY = 851
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 278
try:
    MT_DENSO_MOVE_COMPLETE = 852
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 279
try:
    MT_DENSO_MOVE_FAILED = 853
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 280
try:
    MT_DENSO_MOVE_INVALID = 854
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 281
try:
    MT_DENSO_HALTED = 855
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 296
try:
    MT_KILL_KILL_KILL_EM = 300
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 300
try:
    MT_EM_MOVEMENT_COMMAND = 350
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 303
try:
    MT_EM_AUX_MOVEMENT_COMMAND = 355
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 306
try:
    MT_COMPOSITE_MOVEMENT_COMMAND = 366
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 309
try:
    MT_ROBOT_MOVEMENT_COMMAND = 351
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 312
try:
    MT_PLANNER_MOVEMENT_COMMAND = 352
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 315
try:
    MT_PLANNER_STATE = 353
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 318
try:
    MT_PLAN_PROCESSOR_STATE = 354
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 326
try:
    MT_FM_MOVEMENT_COMMAND = 430
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 337
try:
    MT_OVERRIDE_COMMAND = 480
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 339
try:
    MT_JVEL_COMMAND = 481
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 349
try:
    NUM_COMPONENT_DELAYS = 6
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 350
try:
    MT_COMPONENT_DELAY_MSG_TYPES = 200
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 357
try:
    MT_ESTIMATED_DELAY = 201
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 360
try:
    MT_MEASURED_DELAY = 202
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 365
try:
    MT_NOOP = 998
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 366
try:
    MT_KEYBOARD = 1002
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 367
try:
    MT_CLEAR_FUNCTION = 1003
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 371
try:
    MT_LATE_ADAPT_NOW = 1005
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 375
try:
    MT_DUMMY_MESSAGE = 2000
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 377
try:
    MT_TARG_CLOUD = 1006
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 398
try:
    MT_ATTENTION = 1659
except:
    pass

# C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\Dragonfly_config.h: 402
try:
    MT_RELOAD_CONFIGURATION = 1004
except:
    pass

accel_state = struct_accel_state # C:\\Users\\emd\\Desktop\\BCI\\message_definitions\\/../modules/ps3RawModule/ps3RawDefines.h: 130

# No inserted files

