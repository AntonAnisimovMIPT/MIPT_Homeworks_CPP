class Example {
public:
    const int& operator[] (int position) const {
        return m_data[position];
    }

    int& operator[] (int position) {
        return
            const_cast<int&>(static_cast<const Example&>(*this)[position]);
    }
private:
    int* m_data;
};