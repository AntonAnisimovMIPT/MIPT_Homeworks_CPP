

template <typename Object, typename  Argument>
auto to_call(Object& obj, Argument&& arg) {
    return obj(arg);
}


template <typename Object, typename ... Arguments>
auto to_call(Object& obj, Arguments&&... args) {
    return obj(args...);
}



