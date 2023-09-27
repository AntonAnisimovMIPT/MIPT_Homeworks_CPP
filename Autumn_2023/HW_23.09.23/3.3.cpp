#include <iostream>

class Electric_Current {
private:
    double SI_unit{};
    static inline const double SI_to_Gaussian = 3000000000;  // 1A = 3*10^9 Gaussian units


public:
    Electric_Current(double current) : SI_unit(current) {}

    ~Electric_Current() {
        std::cout << "Delimiter called!";
    }

    double Get_SI() const {
        return SI_unit;
    }

    double Get_Gaussian() {
        return SI_unit * SI_to_Gaussian;
    };

    void Set_SI(double set_value) {
        SI_unit = set_value;
    }

    void Set_Gaussian(double set_value) {
        SI_unit = set_value / SI_to_Gaussian;
    }

};

int main() {
    Electric_Current elcur(0.001);
    std::cout << "In SI: " << elcur.Get_SI() << "\nIn Gaussian: " << elcur.Get_Gaussian() << "\n\n";

    elcur.Set_SI(0.01);
    std::cout << "New in SI: " << elcur.Get_SI() << "\nNew in Gaussian: " << elcur.Get_Gaussian() << "\n\n";


    elcur.Set_Gaussian(3000000000);
    std::cout << "New new in SI: " << elcur.Get_SI() << "\nNew new in Gaussian: " << elcur.Get_Gaussian() << "\n\n";

}
