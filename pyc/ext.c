#define PY_SSIZE_T_CLEAN
#include <Python.h>
#ifdef HAVE_OMP
#include <omp.h>
#endif

static PyObject *sum(PyObject *self, PyObject *args) {
  unsigned int sum = 0;
  int i = 0;

#pragma omp parallel for
  for (i = 0; i < 10; i++) {
#pragma omp critical
    sum++;
  }
  return Py_BuildValue("I", sum);
}

static PyMethodDef m_methods[] = {
    {"sum", sum, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef ext_module = {
    PyModuleDef_HEAD_INIT, "ext", NULL, -1, m_methods, NULL, NULL, NULL, NULL};

PyMODINIT_FUNC PyInit_ext(void) { return PyModule_Create(&ext_module); }
