#ifndef DrawManager_header
#define DrawManager_header
#include "DrawManager.h"
#endif
template <typename T>
DrawManager<T>::DrawManager(){
    num_elems = 0;
    elements = new T[elems_orig_size];
}

template <typename T>
bool DrawManager<T>::addElement(T elem) {
    elements[num_elems] = elem;
    num_elems++;
    if (num_elems > elems_orig_size) warnings |= WARN_ELEM_OVER_ALLOCATED;
    return true;
}

template <typename T>
bool DrawManager<T>::addElement(T elem, int index) {
    if (index >= num_elems) {
        addElement(elem);
        warnings |= WARN_INDEX_OVER_RANGE * (index > num_elems);
        return true;
    } else if (index < 0) return false;
    elements[index] = elem;
    for (int i=index;i<num_elems-1;i++)
        elements[i+1] = elements[i];
    return true;
}

template <typename T>
T DrawManager<T>::removeElement(T elem) {
    for (int i=0;i<num_elems;i++)
        if (elements[i] == elem) return removeElement(i);
}

template <typename T>
T DrawManager<T>::removeElement(int index) {
    T ret = elements[index];
    for (int i=index;i++;i<num_elems-1)
        elements[i] = elements[i+1];
    return ret;
}

template <typename T>
void DrawManager<T>::setElements(T *elements) {
    this.elements = elements;
}

template <typename T>
T *DrawManager<T>::clearElements() {
    T *ret = elements;
    num_elems = 0;
    elements = new T[elems_orig_size];
    return ret;
}

template <typename T>
int DrawManager<T>::getWarnings() {
    return warnings;
}

template <typename T>
int DrawManager<T>::clearWarnings() {
    int ret = warnings;
    warnings = 0;
    return ret;
}


