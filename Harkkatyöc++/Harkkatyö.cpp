//Mikko Rajamäki
//Hotelli harkkatyö
//Kolmosen työhön tähtään

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

//Vakioarvot

const int MINIMI_HUONEET = 30;
const int MAKSIMI_HUONEET = 70;
const int MINIMI_HINTA = 80;
const int MAKSIMI_HINTA = 100;

//Aliohjelmien esittely

bool tarkistaHuoneVarattu(const std::vector<bool>& huoneet, int numero);
int laskeHinta(int hintaPerYo, int yot);

int main() {
    std::srand(std::time(nullptr));

    //Arvotaan hotellihuoneiden määrä ja hinta per yö

    int huoneidenMaara = MINIMI_HUONEET + std::rand() % (MAKSIMI_HUONEET - MINIMI_HUONEET + 1);
    int hintaPerYo = MINIMI_HINTA + std::rand() % (MAKSIMI_HINTA - MINIMI_HINTA + 1);

    //Huoneiden varauslista

    std::vector<bool> huoneet(huoneidenMaara, false);

    std::cout << "Tervetuloa hotellihuoneen varausjarjestelmaan!\n";
    std::cout << "Hotellissa on " << huoneidenMaara << " huonetta.\n";
    std::cout << "Hinta per yo: " << hintaPerYo << " euroa.\n";

    bool jatka = true;
    while (jatka) {
        int huoneNumero, yot;

        std::cout << "\nAnna huonenumero (1-" << huoneidenMaara << "): ";
        std::cin >> huoneNumero;

        // Syötteen tarkistus
        if (std::cin.fail() || huoneNumero < 1 || huoneNumero > huoneidenMaara) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Virheellinen syote. Yrita uudelleen.\n";
            continue;
        }

        if (tarkistaHuoneVarattu(huoneet, huoneNumero - 1)) {
            std::cout << "Huone " << huoneNumero << " on jo varattu. Valitse toinen.\n";
            continue;
        }

        std::cout << "Anna oiden maara: ";
        std::cin >> yot;

        if (std::cin.fail() || yot <= 0) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Virheellinen syote. Yrita uudelleen.\n";
            continue;
        }

        //Lasketaan hinta ja merkitään huone varatuksi. Eli sitä ei voi varata enään

        int loppusumma = laskeHinta(hintaPerYo, yot);
        huoneet[huoneNumero - 1] = true;

        std::cout << "Huone " << huoneNumero << " varattu " << yot << " yoksi.\n";
        std::cout << "Loppusumma: " << loppusumma << " euroa.\n";

        //Kysytään käyttäjältä haluaako jatkaa

        char valinta;
        std::cout << "Haluatko jatkaa varaamista? (k/e): ";
        std::cin >> valinta;
        if (valinta == 'e' || valinta == 'E') {
            jatka = false;
        }
    }

    std::cout << "Kiitos kaynnista! Nakemiin.\n";
    return 0;
}

//Tämä aliohjelma tarkastaa onko huone varattu

bool tarkistaHuoneVarattu(const std::vector<bool>& huoneet, int numero) {
    return huoneet[numero];
}

//Tämä aliohjelma laskee loppusumman

int laskeHinta(int hintaPerYo, int yot) {
    return hintaPerYo * yot;
}
