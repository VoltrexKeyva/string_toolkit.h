#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "string_toolkit.h"

static PyObject * proper_case(PyObject * self, PyObject * args) {
    char * string;
    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;
    
    st_proper_case(string);
    return Py_BuildValue("s", string, strlen(string));
}

static PyObject * mock(PyObject * self, PyObject * args) {
    char * string;
    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;
    
    st_mock(string);
    return Py_BuildValue("s", string, strlen(string));
}

static PyObject * to_abbreviation(PyObject * self, PyObject * args) {
    char * string;
    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;
    
    char * output = st_to_abbreviation(string);
    if (output == NULL) {
        PyErr_SetString(PyExc_TypeError, "The string length must be longer than 1 character.");
        return NULL;
    }
    
    return Py_BuildValue("s", output, strlen(output));
}

static PyMethodDef string_toolkit_methods[] = {
    { "mock",            mock,             METH_VARARGS,   "Mock a string" },
    { "to_abbreviation", to_abbreviation,  METH_VARARGS,   "Converts a string to it's abbreviation" },
    { "proper_case",     proper_case,      METH_VARARGS,   "Fixes(?) the case of a string." },
    { NULL,              NULL,            0,              NULL }
};

static struct PyModuleDef py_module = {
    PyModuleDef_HEAD_INIT,
    "string_toolkit",
    "Python wrapper for the string_toolkit.h C/C++ header",
    -1,
    string_toolkit_methods
};

PyMODINIT_FUNC PyInit_st(void) {
    return PyModule_Create(&py_module);
}