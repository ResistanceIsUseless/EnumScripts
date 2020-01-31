/*      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 3 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 *      
 *      Author: 
 *      Matias Fontanini
 * 
 */
 
#ifndef PYWRAPPER_H
#define PYWRAPPER_H

#include <string>
#include <stdexcept>
#include <utility>
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <tuple>
#include <python2.7/Python.h>


namespace Python {
    // Deleter that calls Py_XDECREF on the PyObject parameter.
    struct PyObjectDeleter {
        void operator()(PyObject *obj) {
            Py_XDECREF(obj);
        } 
    };
    // unique_ptr that uses Py_XDECREF as the destructor function.
    typedef std::unique_ptr<PyObject, PyObjectDeleter> pyunique_ptr;
    
    // ------------ Conversion functions ------------
    
    // Convert a PyObject to a std::string.
    bool convert(PyObject *obj, std::string &val);
    // Convert a PyObject to a std::vector<char>.
    bool convert(PyObject *obj, std::vector<char> &val);
    // Convert a PyObject to a bool value.
    bool convert(PyObject *obj, bool &value);
    // Convert a PyObject to any integral type.
    template<class T, typename std::enable_if<std::is_integral<T>::value, T>::type = 0>
    bool convert(PyObject *obj, T &val) {
        if(!PyInt_Check(obj))
            return false;
        val = PyInt_AsLong(obj);
        return true;
    }
    // Convert a PyObject to an float.
    bool convert(PyObject *obj, double &val);
    
    template<size_t n, class... Args>
    typename std::enable_if<n == 0, bool>::type 
    add_to_tuple(PyObject *obj, std::tuple<Args...> &tup) {
        return convert(PyTuple_GetItem(obj, n), std::get<n>(tup));
    }
    
    template<size_t n, class... Args>
    typename std::enable_if<n != 0, bool>::type 
    add_to_tuple(PyObject *obj, std::tuple<Args...> &tup) {
        add_to_tuple<n-1, Args...>(obj, tup);
        return convert(PyTuple_GetItem(obj, n), std::get<n>(tup));
    }
    
    template<class... Args>
    bool convert(PyObject *obj, std::tuple<Args...> &tup) {
        if(!PyTuple_Check(obj) || 
            PyTuple_Size(obj) != sizeof...(Args))
            return false;
        return add_to_tuple<sizeof...(Args)-1, Args...>(obj, tup);
    }
    // Convert a PyObject to a std::map
    template<class K, class V>
    bool convert(PyObject *obj, std::map<K, V> &mp) {
        if(!PyDict_Check(obj))
            return false;
        PyObject *py_key, *py_val;
        Py_ssize_t pos(0);
        while (PyDict_Next(obj, &pos, &py_key, &py_val)) {
            K key;
            if(!convert(py_key, key))
                return false;
            V val;
            if(!convert(py_val, val))
                return false;
            mp.insert(std::make_pair(key, val));
        }
        return true;
    }
    // Convert a PyObject to a generic container.
    template<class T, class C>
    bool convert_list(PyObject *obj, C &container) {
        if(!PyList_Check(obj))
            return false;
        for(Py_ssize_t i(0); i < PyList_Size(obj); ++i) {
            T val;
            if(!convert(PyList_GetItem(obj, i), val))
                return false;
            container.push_back(std::move(val));
        }
        return true;
    }
    // Convert a PyObject to a std::list.
    template<class T> bool convert(PyObject *obj, std::list<T> &lst) {
        return convert_list<T, std::list<T>>(obj, lst);
    }
    // Convert a PyObject to a std::vector.
    template<class T> bool convert(PyObject *obj, std::vector<T> &vec) {
       return convert_list<T, std::vector<T>>(obj, vec);
    }
    
    template<class T> bool generic_convert(PyObject *obj, 
      const std::function<bool(PyObject*)> &is_obj,
      const std::function<T(PyObject*)> &converter,
      T &val) {
        if(!is_obj(obj))
            return false;
        val = converter(obj);
        return true;
    }
    
    // -------------- PyObject allocators ----------------
    
    // Generic python list allocation
    template<class T> static PyObject *alloc_list(const T &container) {
        PyObject *lst(PyList_New(container.size()));
            
        Py_ssize_t i(0);
        for(auto it(container.begin()); it != container.end(); ++it)
            PyList_SetItem(lst, i++, alloc_pyobject(*it));
        
        return lst;
    }
    // Creates a PyObject from a std::string
    PyObject *alloc_pyobject(const std::string &str);
    // Creates a PyObject from a std::vector<char>
    PyObject *alloc_pyobject(const std::vector<char> &val, size_t sz);
    // Creates a PyObject from a std::vector<char>
    PyObject *alloc_pyobject(const std::vector<char> &val);
    // Creates a PyObject from a const char*
    PyObject *alloc_pyobject(const char *cstr);
    // Creates a PyObject from any integral type(gets converted to PyInt)
    template<class T, typename std::enable_if<std::is_integral<T>::value, T>::type = 0>
    PyObject *alloc_pyobject(T num) {
        return PyInt_FromLong(num);
    }
    // Creates a PyObject from a bool
    PyObject *alloc_pyobject(bool value);
    // Creates a PyObject from a double
    PyObject *alloc_pyobject(double num);
    // Creates a PyObject from a std::vector
    template<class T> PyObject *alloc_pyobject(const std::vector<T> &container) {
        return alloc_list(container);
    }
    // Creates a PyObject from a std::list
    template<class T> PyObject *alloc_pyobject(const std::list<T> &container) {
        return alloc_list(container);
    }
    // Creates a PyObject from a std::map
    template<class T, class K> PyObject *alloc_pyobject(
      const std::map<T, K> &container) {
        PyObject *dict(PyDict_New());
            
        for(auto it(container.begin()); it != container.end(); ++it)
            PyDict_SetItem(dict, 
                alloc_pyobject(it->first),
                alloc_pyobject(it->second)
            );
        
        return dict;
    }
    
    void initialize();
    void finalize();
    void print_error();
    void clear_error();
    void print_object(PyObject *obj);
    
    /**
     * \class Object
     * \brief This class represents a python object.
     */
    class Object {
    public:
        /**
         * \brief Constructs a default python object
         */
        Object();
        
        /**
         * \brief Constructs a python object from a PyObject pointer.
         * 
         * This Object takes ownership of the PyObject* argument. That 
         * means no Py_INCREF is performed on it. 
         * \param obj The pointer from which to construct this Object.
         */
        Object(PyObject *obj);
        
        /**
         * \brief Calls the callable attribute "name" using the provided
         * arguments.
         * 
         * This function might throw a std::runtime_error if there is
         * an error when calling the function.
         * 
         * \param name The name of the attribute to be called.
         * \param args The arguments which will be used when calling the
         * attribute.
         * \return Python::Object containing the result of the function.
         */
        template<typename... Args>
        Object call_function(const std::string &name, const Args&... args) {
            pyunique_ptr func(load_function(name));
            // Create the tuple argument
            pyunique_ptr tup(PyTuple_New(sizeof...(args)));
            add_tuple_vars(tup, args...);
            // Call our object
            PyObject *ret(PyObject_CallObject(func.get(), tup.get()));
            if(!ret)
                throw std::runtime_error("Failed to call function " + name);
            return {ret};
        }
        
        /**
         * \brief Calls a callable attribute using no arguments.
         * 
         * This function might throw a std::runtime_error if there is
         * an error when calling the function.
         * 
         * \sa Python::Object::call_function.
         * \param name The name of the callable attribute to be executed.
         * \return Python::Object containing the result of the function.
         */
        Object call_function(const std::string &name);
        
        /**
         * \brief Finds and returns the attribute named "name".
         * 
         * This function might throw a std::runtime_error if an error
         * is encountered while fetching the attribute.
         * 
         * \param name The name of the attribute to be returned.
         * \return Python::Object representing the attribute.
         */
        Object get_attr(const std::string &name);
        
        /**
         * \brief Checks whether this object contains a certain attribute.
         * 
         * \param name The name of the attribute to be searched.
         * \return bool indicating whether the attribute is defined.
         */
        bool has_attr(const std::string &name);
          
        /**
         * \brief Returns the internal PyObject*.
         * 
         * No reference increment is performed on the PyObject* before
         * returning it, so any DECREF applied to it without INCREF'ing
         * it will cause undefined behaviour.
         * \return The PyObject* which this Object is representing.
         */
        PyObject *get() const { return py_obj.get(); }
        
        template<class T>
        bool convert(T &param) {
            return Python::convert(py_obj.get(), param);
        }
        
        /**
         * \brief Constructs a Python::Object from a script.
         * 
         * The returned Object will be the representation of the loaded
         * script. If any errors are encountered while loading this 
         * script, a std::runtime_error is thrown.
         * 
         * \param script_path The path of the script to be loaded.
         * \return Object representing the loaded script.
         */
        static Object from_script(const std::string &script_path);
    private:
        typedef std::shared_ptr<PyObject> pyshared_ptr;
    
        PyObject *load_function(const std::string &name);
        
        pyshared_ptr make_pyshared(PyObject *obj);
    
        // Variadic template method to add items to a tuple
        template<typename First, typename... Rest> 
        void add_tuple_vars(pyunique_ptr &tup, const First &head, const Rest&... tail) {
            add_tuple_var(
                tup, 
                PyTuple_Size(tup.get()) - sizeof...(tail) - 1, 
                head
            );
            add_tuple_vars(tup, tail...);
        }
        
        
        void add_tuple_vars(pyunique_ptr &tup, PyObject *arg) {
            add_tuple_var(tup, PyTuple_Size(tup.get()) - 1, arg);
        }
        
        // Base case for add_tuple_vars
        template<typename Arg> 
        void add_tuple_vars(pyunique_ptr &tup, const Arg &arg) {
            add_tuple_var(tup, 
              PyTuple_Size(tup.get()) - 1, alloc_pyobject(arg)
            );
        }
        
        // Adds a PyObject* to the tuple object
        void add_tuple_var(pyunique_ptr &tup, Py_ssize_t i, PyObject *pobj) {
            PyTuple_SetItem(tup.get(), i, pobj);
        }
        
        // Adds a PyObject* to the tuple object
        template<class T> void add_tuple_var(pyunique_ptr &tup, Py_ssize_t i, 
          const T &data) {
            PyTuple_SetItem(tup.get(), i, alloc_pyobject(data));
        }
        
        pyshared_ptr py_obj;
    };
};

#endif // PYWRAPPER_H
