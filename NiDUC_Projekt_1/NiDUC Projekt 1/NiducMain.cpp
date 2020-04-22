// NiDUC Projekt 1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Python.h"

int main()
{

    Py_Initialize(); 

    PyObject* moduleString = PyUnicode_FromString((char*)"komm");
    PyObject* module = PyImport_Import(moduleString);
    if (module == nullptr) {
        PyErr_Print();
        std::cout << "Fails to import the module.\n";
        return 1;
    }
    Py_DECREF(moduleString);

    PyObject* dict = PyModule_GetDict(module);
    if (dict == nullptr) {
        PyErr_Print();
        std::cout << "Fails to get the dictionary.\n";
        return 1;
    }
    Py_DECREF(module);

    PyObject* python_class = PyDict_GetItemString(dict, "BCHCode");
    if (python_class == nullptr) {
        PyErr_Print();
        std::cerr << "Fails to get the Python class.\n";
        return 1;
    }
    Py_DECREF(dict);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, PyLong_FromLong(15));
    PyTuple_SetItem(args, 1, PyLong_FromLong(2));
    PyObject* object;
    if (PyCallable_Check(python_class)) {
        object = PyObject_CallObject(python_class, args);
        Py_DECREF(python_class);
    }
    else {
        std::cout << "Cannot instantiate the Python class" << std::endl;
        Py_DECREF(python_class);
        return 1;
    }
    int size = PyLong_AsLong(PyObject_GetAttrString(object, "dimension"));
    PyObject* l = PyList_New(size);
    for (size_t i = 0; i != size; i++) {
        PyList_SetItem(l, i, PyLong_FromLong(i));
    }
   PyObject* value = PyObject_CallMethod(object, "encode", "O", l);
    if (value)
        Py_DECREF(value);
    else
        PyErr_Print();

   /* PyObject* value1 = PyObject_CallMethod(object, "decode", "O", value);
    if (value1)
        Py_DECREF(value1);
    else
        PyErr_Print();*/

    PyTypeObject* type = value->ob_type;
    const char* p = type->tp_name;
    
    std::cout<< p;
   

    Py_Finalize();
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
