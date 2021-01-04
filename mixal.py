# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _mixal
else:
    import _mixal

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)



__version__ = '1.168.14'

class SwigPyIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _mixal.delete_SwigPyIterator

    def value(self):
        return _mixal.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _mixal.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _mixal.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _mixal.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _mixal.SwigPyIterator_equal(self, x)

    def copy(self):
        return _mixal.SwigPyIterator_copy(self)

    def next(self):
        return _mixal.SwigPyIterator_next(self)

    def __next__(self):
        return _mixal.SwigPyIterator___next__(self)

    def previous(self):
        return _mixal.SwigPyIterator_previous(self)

    def advance(self, n):
        return _mixal.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _mixal.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _mixal.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _mixal.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _mixal.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _mixal.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _mixal.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self

# Register SwigPyIterator in _mixal:
_mixal.SwigPyIterator_swigregister(SwigPyIterator)

class VecInt(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def iterator(self):
        return _mixal.VecInt_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _mixal.VecInt___nonzero__(self)

    def __bool__(self):
        return _mixal.VecInt___bool__(self)

    def __len__(self):
        return _mixal.VecInt___len__(self)

    def __getslice__(self, i, j):
        return _mixal.VecInt___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _mixal.VecInt___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _mixal.VecInt___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _mixal.VecInt___delitem__(self, *args)

    def __getitem__(self, *args):
        return _mixal.VecInt___getitem__(self, *args)

    def __setitem__(self, *args):
        return _mixal.VecInt___setitem__(self, *args)

    def pop(self):
        return _mixal.VecInt_pop(self)

    def append(self, x):
        return _mixal.VecInt_append(self, x)

    def empty(self):
        return _mixal.VecInt_empty(self)

    def size(self):
        return _mixal.VecInt_size(self)

    def swap(self, v):
        return _mixal.VecInt_swap(self, v)

    def begin(self):
        return _mixal.VecInt_begin(self)

    def end(self):
        return _mixal.VecInt_end(self)

    def rbegin(self):
        return _mixal.VecInt_rbegin(self)

    def rend(self):
        return _mixal.VecInt_rend(self)

    def clear(self):
        return _mixal.VecInt_clear(self)

    def get_allocator(self):
        return _mixal.VecInt_get_allocator(self)

    def pop_back(self):
        return _mixal.VecInt_pop_back(self)

    def erase(self, *args):
        return _mixal.VecInt_erase(self, *args)

    def __init__(self, *args):
        _mixal.VecInt_swiginit(self, _mixal.new_VecInt(*args))

    def push_back(self, x):
        return _mixal.VecInt_push_back(self, x)

    def front(self):
        return _mixal.VecInt_front(self)

    def back(self):
        return _mixal.VecInt_back(self)

    def assign(self, n, x):
        return _mixal.VecInt_assign(self, n, x)

    def resize(self, *args):
        return _mixal.VecInt_resize(self, *args)

    def insert(self, *args):
        return _mixal.VecInt_insert(self, *args)

    def reserve(self, n):
        return _mixal.VecInt_reserve(self, n)

    def capacity(self):
        return _mixal.VecInt_capacity(self)
    __swig_destroy__ = _mixal.delete_VecInt

# Register VecInt in _mixal:
_mixal.VecInt_swigregister(VecInt)

class VecStr(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def iterator(self):
        return _mixal.VecStr_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _mixal.VecStr___nonzero__(self)

    def __bool__(self):
        return _mixal.VecStr___bool__(self)

    def __len__(self):
        return _mixal.VecStr___len__(self)

    def __getslice__(self, i, j):
        return _mixal.VecStr___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _mixal.VecStr___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _mixal.VecStr___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _mixal.VecStr___delitem__(self, *args)

    def __getitem__(self, *args):
        return _mixal.VecStr___getitem__(self, *args)

    def __setitem__(self, *args):
        return _mixal.VecStr___setitem__(self, *args)

    def pop(self):
        return _mixal.VecStr_pop(self)

    def append(self, x):
        return _mixal.VecStr_append(self, x)

    def empty(self):
        return _mixal.VecStr_empty(self)

    def size(self):
        return _mixal.VecStr_size(self)

    def swap(self, v):
        return _mixal.VecStr_swap(self, v)

    def begin(self):
        return _mixal.VecStr_begin(self)

    def end(self):
        return _mixal.VecStr_end(self)

    def rbegin(self):
        return _mixal.VecStr_rbegin(self)

    def rend(self):
        return _mixal.VecStr_rend(self)

    def clear(self):
        return _mixal.VecStr_clear(self)

    def get_allocator(self):
        return _mixal.VecStr_get_allocator(self)

    def pop_back(self):
        return _mixal.VecStr_pop_back(self)

    def erase(self, *args):
        return _mixal.VecStr_erase(self, *args)

    def __init__(self, *args):
        _mixal.VecStr_swiginit(self, _mixal.new_VecStr(*args))

    def push_back(self, x):
        return _mixal.VecStr_push_back(self, x)

    def front(self):
        return _mixal.VecStr_front(self)

    def back(self):
        return _mixal.VecStr_back(self)

    def assign(self, n, x):
        return _mixal.VecStr_assign(self, n, x)

    def resize(self, *args):
        return _mixal.VecStr_resize(self, *args)

    def insert(self, *args):
        return _mixal.VecStr_insert(self, *args)

    def reserve(self, n):
        return _mixal.VecStr_reserve(self, n)

    def capacity(self):
        return _mixal.VecStr_capacity(self)
    __swig_destroy__ = _mixal.delete_VecStr

# Register VecStr in _mixal:
_mixal.VecStr_swigregister(VecStr)

class ComputerWord(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    negative = property(_mixal.ComputerWord_negative_get, _mixal.ComputerWord_negative_set)
    byte1 = property(_mixal.ComputerWord_byte1_get, _mixal.ComputerWord_byte1_set)
    byte2 = property(_mixal.ComputerWord_byte2_get, _mixal.ComputerWord_byte2_set)
    byte3 = property(_mixal.ComputerWord_byte3_get, _mixal.ComputerWord_byte3_set)
    byte4 = property(_mixal.ComputerWord_byte4_get, _mixal.ComputerWord_byte4_set)
    byte5 = property(_mixal.ComputerWord_byte5_get, _mixal.ComputerWord_byte5_set)

    def __init__(self, *args):
        _mixal.ComputerWord_swiginit(self, _mixal.new_ComputerWord(*args))

    def reset(self):
        return _mixal.ComputerWord_reset(self)

    def __eq__(self, word):
        return _mixal.ComputerWord___eq__(self, word)

    def getBytesString(self):
        return _mixal.ComputerWord_getBytesString(self)

    def bytes2(self, index1, index2):
        return _mixal.ComputerWord_bytes2(self, index1, index2)

    def bytes12(self):
        return _mixal.ComputerWord_bytes12(self)

    def bytes23(self):
        return _mixal.ComputerWord_bytes23(self)

    def bytes34(self):
        return _mixal.ComputerWord_bytes34(self)

    def bytes45(self):
        return _mixal.ComputerWord_bytes45(self)

    def value(self):
        return _mixal.ComputerWord_value(self)

    def addressValue(self):
        return _mixal.ComputerWord_addressValue(self)

    def address(self):
        return _mixal.ComputerWord_address(self)

    def index(self):
        return _mixal.ComputerWord_index(self)

    def field(self):
        return _mixal.ComputerWord_field(self)

    def operation(self):
        return _mixal.ComputerWord_operation(self)

    def setAddress(self, *args):
        return _mixal.ComputerWord_setAddress(self, *args)

    def setIndex(self, index):
        return _mixal.ComputerWord_setIndex(self, index)

    def setField(self, field):
        return _mixal.ComputerWord_setField(self, field)

    def setOperation(self, operation):
        return _mixal.ComputerWord_setOperation(self, operation)

    def getAt(self, index):
        return _mixal.ComputerWord_getAt(self, index)

    def getCharacters(self):
        return _mixal.ComputerWord_getCharacters(self)

    def set(self, *args):
        return _mixal.ComputerWord_set(self, *args)
    __swig_destroy__ = _mixal.delete_ComputerWord

# Register ComputerWord in _mixal:
_mixal.ComputerWord_swigregister(ComputerWord)
cvar = _mixal.cvar
CHAR_CODES_NUM = cvar.CHAR_CODES_NUM

class Register2(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    negative = property(_mixal.Register2_negative_get, _mixal.Register2_negative_set)
    byte1 = property(_mixal.Register2_byte1_get, _mixal.Register2_byte1_set)
    byte2 = property(_mixal.Register2_byte2_get, _mixal.Register2_byte2_set)

    def __init__(self, *args):
        _mixal.Register2_swiginit(self, _mixal.new_Register2(*args))

    def reset(self):
        return _mixal.Register2_reset(self)

    def bytes12(self):
        return _mixal.Register2_bytes12(self)

    def value(self):
        return _mixal.Register2_value(self)

    def set(self, *args):
        return _mixal.Register2_set(self, *args)
    __swig_destroy__ = _mixal.delete_Register2

# Register Register2 in _mixal:
_mixal.Register2_swigregister(Register2)

class Computer(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    NUM_INDEX_REGISTER = _mixal.Computer_NUM_INDEX_REGISTER
    NUM_MEMORY = _mixal.Computer_NUM_MEMORY
    NUM_IO_DEVICE = _mixal.Computer_NUM_IO_DEVICE
    rA = property(_mixal.Computer_rA_get, _mixal.Computer_rA_set)
    rX = property(_mixal.Computer_rX_get, _mixal.Computer_rX_set)
    rI1 = property(_mixal.Computer_rI1_get, _mixal.Computer_rI1_set)
    rI2 = property(_mixal.Computer_rI2_get, _mixal.Computer_rI2_set)
    rI3 = property(_mixal.Computer_rI3_get, _mixal.Computer_rI3_set)
    rI4 = property(_mixal.Computer_rI4_get, _mixal.Computer_rI4_set)
    rI5 = property(_mixal.Computer_rI5_get, _mixal.Computer_rI5_set)
    rI6 = property(_mixal.Computer_rI6_get, _mixal.Computer_rI6_set)
    rJ = property(_mixal.Computer_rJ_get, _mixal.Computer_rJ_set)
    overflow = property(_mixal.Computer_overflow_get, _mixal.Computer_overflow_set)
    comparison = property(_mixal.Computer_comparison_get, _mixal.Computer_comparison_set)
    memory = property(_mixal.Computer_memory_get, _mixal.Computer_memory_set)
    devices = property(_mixal.Computer_devices_get, _mixal.Computer_devices_set)

    def __init__(self):
        _mixal.Computer_swiginit(self, _mixal.new_Computer())
    __swig_destroy__ = _mixal.delete_Computer

    def rI(self, index):
        return _mixal.Computer_rI(self, index)

    def memoryAt(self, *args):
        return _mixal.Computer_memoryAt(self, *args)

    def getDevice(self, index):
        return _mixal.Computer_getDevice(self, index)

    def waitDevice(self, device):
        return _mixal.Computer_waitDevice(self, device)

    def waitDevices(self):
        return _mixal.Computer_waitDevices(self)

    def getDeviceWordAt(self, device, index):
        return _mixal.Computer_getDeviceWordAt(self, device, index)

    def reset(self):
        return _mixal.Computer_reset(self)

    def line(self):
        return _mixal.Computer_line(self)

    def elapsed(self):
        return _mixal.Computer_elapsed(self)

    def getSingleLineSymbol(self):
        return _mixal.Computer_getSingleLineSymbol(self)

    def executeUntilSelfLoop(self):
        return _mixal.Computer_executeUntilSelfLoop(self)

    def executeUntilHalt(self):
        return _mixal.Computer_executeUntilHalt(self)

    def executeSingle(self, *args):
        return _mixal.Computer_executeSingle(self, *args)

    def executeSinglePesudo(self, instruction):
        return _mixal.Computer_executeSinglePesudo(self, instruction)

    def loadCodes(self, *args):
        return _mixal.Computer_loadCodes(self, *args)

# Register Computer in _mixal:
_mixal.Computer_swigregister(Computer)

IODeviceType_TAPE = _mixal.IODeviceType_TAPE
IODeviceType_DISK = _mixal.IODeviceType_DISK
IODeviceType_CARD_READER = _mixal.IODeviceType_CARD_READER
IODeviceType_CARD_PUNCH = _mixal.IODeviceType_CARD_PUNCH
IODeviceType_LINE_PRINTER = _mixal.IODeviceType_LINE_PRINTER
IODeviceType_TYPEWRITER = _mixal.IODeviceType_TYPEWRITER
IODeviceType_PAPER_TAPE = _mixal.IODeviceType_PAPER_TAPE
IODeviceStatus_READY = _mixal.IODeviceStatus_READY
IODeviceStatus_BUSY_READ = _mixal.IODeviceStatus_BUSY_READ
IODeviceStatus_BUSY_WRITE = _mixal.IODeviceStatus_BUSY_WRITE
class IODevice(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _mixal.delete_IODevice

    def type(self):
        return _mixal.IODevice_type(self)

    def blockSize(self):
        return _mixal.IODevice_blockSize(self)

    def allowRead(self):
        return _mixal.IODevice_allowRead(self)

    def allowWrite(self):
        return _mixal.IODevice_allowWrite(self)

    def ready(self, elapsed):
        return _mixal.IODevice_ready(self, elapsed)

    def control(self, arg2):
        return _mixal.IODevice_control(self, arg2)

    def read(self, memory, address):
        return _mixal.IODevice_read(self, memory, address)

    def write(self, memory, address):
        return _mixal.IODevice_write(self, memory, address)

    def wordAt(self, index):
        return _mixal.IODevice_wordAt(self, index)

# Register IODevice in _mixal:
_mixal.IODevice_swigregister(IODevice)

class IODeviceStorage(IODevice):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _mixal.IODeviceStorage_swiginit(self, _mixal.new_IODeviceStorage(*args))

    def ready(self, elapsed):
        return _mixal.IODeviceStorage_ready(self, elapsed)

    def read(self, memory, address):
        return _mixal.IODeviceStorage_read(self, memory, address)

    def write(self, memory, address):
        return _mixal.IODeviceStorage_write(self, memory, address)

    def wordAt(self, index):
        return _mixal.IODeviceStorage_wordAt(self, index)
    __swig_destroy__ = _mixal.delete_IODeviceStorage

# Register IODeviceStorage in _mixal:
_mixal.IODeviceStorage_swigregister(IODeviceStorage)

class IODeviceTape(IODeviceStorage):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODeviceTape_swiginit(self, _mixal.new_IODeviceTape(storageSize))

    def control(self, operation):
        return _mixal.IODeviceTape_control(self, operation)
    __swig_destroy__ = _mixal.delete_IODeviceTape

# Register IODeviceTape in _mixal:
_mixal.IODeviceTape_swigregister(IODeviceTape)

class IODeviceDisk(IODeviceStorage):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODeviceDisk_swiginit(self, _mixal.new_IODeviceDisk(storageSize))

    def control(self, operation):
        return _mixal.IODeviceDisk_control(self, operation)
    __swig_destroy__ = _mixal.delete_IODeviceDisk

# Register IODeviceDisk in _mixal:
_mixal.IODeviceDisk_swigregister(IODeviceDisk)

class IODeviceSeqReader(IODeviceStorage):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODeviceSeqReader_swiginit(self, _mixal.new_IODeviceSeqReader(storageSize))
    __swig_destroy__ = _mixal.delete_IODeviceSeqReader

# Register IODeviceSeqReader in _mixal:
_mixal.IODeviceSeqReader_swigregister(IODeviceSeqReader)

class IODeviceSeqWriter(IODeviceStorage):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODeviceSeqWriter_swiginit(self, _mixal.new_IODeviceSeqWriter(storageSize))
    __swig_destroy__ = _mixal.delete_IODeviceSeqWriter

# Register IODeviceSeqWriter in _mixal:
_mixal.IODeviceSeqWriter_swigregister(IODeviceSeqWriter)

class IODeviceCardReader(IODeviceSeqReader):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODeviceCardReader_swiginit(self, _mixal.new_IODeviceCardReader(storageSize))
    __swig_destroy__ = _mixal.delete_IODeviceCardReader

# Register IODeviceCardReader in _mixal:
_mixal.IODeviceCardReader_swigregister(IODeviceCardReader)

class IODeviceCardPunch(IODeviceSeqWriter):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODeviceCardPunch_swiginit(self, _mixal.new_IODeviceCardPunch(storageSize))
    __swig_destroy__ = _mixal.delete_IODeviceCardPunch

# Register IODeviceCardPunch in _mixal:
_mixal.IODeviceCardPunch_swigregister(IODeviceCardPunch)

class IODeviceLinePrinter(IODeviceSeqWriter):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096, pageSize=20):
        _mixal.IODeviceLinePrinter_swiginit(self, _mixal.new_IODeviceLinePrinter(storageSize, pageSize))

    def control(self, operation):
        return _mixal.IODeviceLinePrinter_control(self, operation)

    def pageSize(self):
        return _mixal.IODeviceLinePrinter_pageSize(self)

    def pageOffsetAt(self, index):
        return _mixal.IODeviceLinePrinter_pageOffsetAt(self, index)

    def line(self, pageNum, lineNum):
        return _mixal.IODeviceLinePrinter_line(self, pageNum, lineNum)
    __swig_destroy__ = _mixal.delete_IODeviceLinePrinter

# Register IODeviceLinePrinter in _mixal:
_mixal.IODeviceLinePrinter_swigregister(IODeviceLinePrinter)

class IODeviceTypewriter(IODeviceSeqReader):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODeviceTypewriter_swiginit(self, _mixal.new_IODeviceTypewriter(storageSize))
    __swig_destroy__ = _mixal.delete_IODeviceTypewriter

# Register IODeviceTypewriter in _mixal:
_mixal.IODeviceTypewriter_swigregister(IODeviceTypewriter)

class IODevicePaperTape(IODeviceSeqReader):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, storageSize=4096):
        _mixal.IODevicePaperTape_swiginit(self, _mixal.new_IODevicePaperTape(storageSize))

    def control(self, operation):
        return _mixal.IODevicePaperTape_control(self, operation)
    __swig_destroy__ = _mixal.delete_IODevicePaperTape

# Register IODevicePaperTape in _mixal:
_mixal.IODevicePaperTape_swigregister(IODevicePaperTape)



