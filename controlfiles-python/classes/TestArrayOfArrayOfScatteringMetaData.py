import pyarts.arts as cxx
import test_functions as test

x = cxx.ArrayOfArrayOfScatteringMetaData()
test.io(x, delete=True)