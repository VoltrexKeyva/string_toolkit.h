#define PY_SSIZE_T_CLEAN
#include <Python.h>

#pragma warning(disable: 4244)
#define ST_64
#include "string_toolkit.h"
#pragma warning(default: 4244)

static PyObject * progress_bar(PyObject * self, PyObject * args) {
    double in_total, total;
    Py_ssize_t bar_length;
    char * elapsed_char;
    char * progress_bar;
    char * empty_char;
    
    if (!PyArg_ParseTuple(args, "ddsssn", &in_total, &total, &elapsed_char, &progress_bar, &empty_char, &bar_length))
        return NULL;
    else if (strlen(elapsed_char) != 1 || strlen(progress_bar) != 1 || strlen(empty_char) != 1) {
        PyErr_SetString(PyExc_TypeError, "The string length for the third, fourth, and fifth argument must be 1.");
        return NULL;
    } else if (bar_length < 1) {
        PyErr_SetString(PyExc_ValueError, "The bar length must be higher than 0.");
        return NULL;
    } else if (in_total > total) {
        PyErr_SetString(PyExc_TypeError, "The second argument must be higher than the first argument.");
        return NULL;
    } else if (in_total < 0 || total < 1) {
        PyErr_SetString(PyExc_ValueError, "Invalid in_total and total value.");
        return NULL;
    }
    
    char * output = st_progress_bar(in_total, total, elapsed_char[0], progress_bar[0], empty_char[0], (st_uint)bar_length);
    if (output == NULL)
        return Py_BuildValue("s", "", 0);
    return Py_BuildValue("s", output, strlen(output));
}

static PyObject * get_indexes(PyObject * self, PyObject * args) {
    char * string;
    char * character;

    if (!PyArg_ParseTuple(args, "ss", &string, &character))
        return NULL;
    
    if (strlen(character) != 1) {
        PyErr_SetString(PyExc_TypeError, "The string length for the second argument must be 1.");
        return NULL;
    }

    st_uint_arr array = st_get_indexes(string, character[0]);
    if (!array.size)
        return PyList_New(0);
    
    PyObject * list = PyList_New(array.size);
    for (st_uint i = 0; i < array.size; i++)
        PyList_SET_ITEM(list, i, PyLong_FromUnsignedLongLong(array.data[i]));
    
    return list;
}

static PyObject * to_chunks(PyObject * self, PyObject * args) {
    char * string;
    Py_ssize_t amount;

    if (!PyArg_ParseTuple(args, "sn", &string, &amount))
        return NULL;
    
    if (amount < 0) {
        PyErr_SetString(PyExc_TypeError, "The second argument must not be less than 0.");
        return NULL;
    }

    st_str_arr array = st_to_chunks(string, (st_uint)amount);
    if (!array.size) {
        PyObject * list = PyList_New(1);
        PyList_SET_ITEM(list, 0, Py_BuildValue("s", string, strlen(string)));
        return list;
    }

    PyObject * list = PyList_New(array.size);
    for (st_uint i = 0; i < array.size; i++)
        PyList_SET_ITEM(list, i, Py_BuildValue("s", array.data[i], strlen(array.data[i])));
    
    return list;
}

static PyObject * substr(PyObject * self, PyObject * args) {
    char * string;
    Py_ssize_t a;
    Py_ssize_t b;

    if (!PyArg_ParseTuple(args, "snn", &string, &a, &b))
        return NULL;
    
    if (a < 0 || b < 0) {
        PyErr_SetString(PyExc_TypeError, "The second/third argument must not be less than 0.");
        return NULL;
    }

    char * output = st_substr(string, (st_uint)a, (st_uint)b);
    if (output == NULL)
        return Py_BuildValue("s", string, strlen(string));
    
    return Py_BuildValue("s", output, strlen(output));
}

static PyObject * shorten(PyObject * self, PyObject * args) {
    char * string;
    char * placeholder;
    Py_ssize_t amount;

    if (!PyArg_ParseTuple(args, "sns", &string, &amount, &placeholder))
        return NULL;
    
    if (amount < 1) {
        PyErr_SetString(PyExc_TypeError, "The amount must be higher than 1.");
        return NULL;
    }

    char * output = st_shorten(string, (st_uint)amount, placeholder);
    if (output == NULL)
        return Py_BuildValue("s", string, strlen(string));
    
    return Py_BuildValue("s", output, strlen(output));
}

static PyObject * has_custom_emoji(PyObject * self, PyObject * args) {
    char * string;
    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;
    
    const unsigned char result = st_has_custom_emoji(string);
    return result ? Py_True : Py_False;
}

static PyObject * scramble(PyObject * self, PyObject * args) {
    char * string;
    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;
    
    st_scramble(string);
    return Py_BuildValue("s", string, strlen(string));
}

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
    { "mock",             mock,             METH_VARARGS, "Mock a string" },
    { "to_abbreviation",  to_abbreviation,  METH_VARARGS, "Converts a string to it's abbreviation" },
    { "proper_case",      proper_case,      METH_VARARGS, "Fixes(?) the case of a string." },
    { "scramble",         scramble,         METH_VARARGS, "Scrambles a string." },
    { "has_custom_emoji", has_custom_emoji, METH_VARARGS, "Checks if a string contains a discord custom emoji or not." },
    { "shorten",          shorten,          METH_VARARGS, "Shortens a string." },
    { "substr",           substr,           METH_VARARGS, "Gets a sub-string from a string." },
    { "to_chunks",        to_chunks,        METH_VARARGS, "Converts a string to chunks." },
    { "get_indexes",      get_indexes,      METH_VARARGS, "Gets a list of indexes (matches) from a character." },
    { "progress_bar",     progress_bar,     METH_VARARGS, "Creates a progress bar from a string." },
    { NULL, NULL }
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