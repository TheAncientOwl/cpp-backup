#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <map>
#include <vector>

#include <Windows.h>

using namespace std;

void schimbaCuloarea(int codCuloare) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, codCuloare);
}

class Vin;
class Angajat;
class Client;
class Comanda;

map<int, Vin> date_Vinuri;
map<int, Angajat> date_Angajati;
map<int, Client> date_Clienti;
map<int, Comanda> date_Comenzi;

int genereazaID() {
    ifstream f("id.txt");
    int id = 0;
    f >> id;
    f.close();

    id = id + 1;

    ofstream g("id.txt");
    g << id;
    g.close();

    return id;
}

struct Data {
    int zi;
    int luna;
    int an;

    Data() {
        this->zi = 1;
        this->luna = 1;
        this->an = 1978;
    }

    Data(int zi, int luna, int an) {
        this->zi = zi;
        this->luna = luna;
        this->an = an;
    }

    bool operator<(const Data& data) const {
        if ((this->an < data.an) ||
            (this->an == data.an && this->luna < data.luna) ||
            (this->an == data.an && this->luna == data.luna && this->zi < data.zi))
            return true;

        return false;
    }

    string pentruFisierText() const {
        string str = "" + to_string(this->zi) + " " + to_string(this->luna) + " " + to_string(this->an);

        return str;
    }

    string pentruConsola() const {
        string str = "" + to_string(this->zi) + "/" + to_string(this->luna) + "/" + to_string(this->an);

        return str;
    }

    friend istream& operator>>(istream& in, Data& data) {
        cout << " >> zi: ";
        in >> data.zi;
        cout << " >> luna: ";
        in >> data.luna;
        cout << " >> an: ";
        in >> data.an;

        return in;
    }
};

enum class TipVin {
    Rosu,
    Alb,
    Rose
};

string tipVinCaString(TipVin tip) {
    switch (tip) {
    case TipVin::Rosu:
        return "rosu";
    case TipVin::Alb:
        return "alb";
    default:
        return "rose";
    }
}

TipVin stringCaTipVin(string tip) {
    for (int i = 0; i < tip.length(); i++)
        tip[i] = tolower(tip[i]);

    if (tip == "rosu")
        return TipVin::Rosu;

    if (tip == "alb")
        return TipVin::Alb;

    if (tip == "rose")
        return TipVin::Rose;

    throw "Tip vin invalid";
}

class Vin {
private:
    int id = -1;
    char* nume = NULL;
    string descriere = "";
    TipVin tip = TipVin::Rosu;
    float pretMinim = -1;
    float pret = -1;
    Data dataImbutelierii = Data();

public:
    int getID() const {
        return this->id;
    }

    const char* getNume() const {
        return this->nume;
    }

    string getDescriere() const {
        return this->descriere;
    }

    TipVin getTipVin() const {
        return this->tip;
    }

    float getPretMinim() const {
        return this->pretMinim;
    }

    float getPret() const {
        return this->pret;
    }

    Data getDataImbutelierii() const {
        return this->dataImbutelierii;
    }

    void setNume(const char* numeNou) {
        if (numeNou == NULL)
            throw "Numele nu poate fi null";

        if (this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }

        this->nume = new char[strlen(numeNou) + 1];
        strcpy(this->nume, numeNou);
    }

    void setDescriere(string descriereNoua) {
        if (descriereNoua == "")
            throw "Descrierea nu poate fi goala";

        this->descriere = descriereNoua;
    }

    void setPretMinim(float nouPretMinim) {
        if (nouPretMinim < 0)
            throw "Noul pret minim nu poate fi negativ";

        if (nouPretMinim > this->pret)
            throw "Noul pret minim nu poate fi mai mare decat pretul curent.";

        this->pretMinim = nouPretMinim;
    }

    void setPret(float nouPret) {
        if (nouPret < 0)
            throw "Noul pret nu poate fi negativ.";

        if (nouPret < this->pretMinim)
            throw "Noul pret nu poate fi mai mic decat pretul minim.";

        this->pret = nouPret;
    }

    Vin() {
        this->id = genereazaID();
        this->setNume("lipsa");
        this->setDescriere("lipsa");
        this->tip = TipVin::Rosu;
        this->pretMinim = 0;
        this->pret = 0;
        this->dataImbutelierii = Data();
    }

    Vin(const char* nume, float pretMinim, TipVin tip, Data dataImbutelierii) {
        this->id = genereazaID();
        this->descriere = "Nespecificat";
        this->tip = tip;
        this->setPret(pretMinim);
        this->setPretMinim(pretMinim);
        this->setNume(nume);
        this->dataImbutelierii = dataImbutelierii;
    }

    Vin(const char* nume, float pretMinim, Data dataImbutelierii, string descriere, float pret, TipVin tip) {
        this->id = genereazaID();
        this->setDescriere(descriere);
        this->tip = tip;
        this->setPret(pret);
        this->setPretMinim(pretMinim);
        this->setNume(nume);
        this->dataImbutelierii = dataImbutelierii;
    }

    Vin(const Vin& vin) {
        this->id = vin.id;
        this->setDescriere(vin.descriere);
        this->tip = vin.tip;
        this->setPret(vin.pret);
        this->setPretMinim(vin.pretMinim);
        this->setNume(vin.nume);
        this->dataImbutelierii = vin.dataImbutelierii;
    }

    Vin& operator=(const Vin& vin) {
        if (this == &vin)
            return *this;

        this->id = vin.id;
        this->setDescriere(vin.descriere);
        this->tip = vin.tip;
        this->setPret(vin.pret);
        this->setPretMinim(vin.pretMinim);
        this->setNume(vin.nume);
        this->dataImbutelierii = vin.dataImbutelierii;

        return *this;
    }

    ~Vin() {
        if (this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }
    }

    friend istream& operator>>(istream& in, Vin& vin) {
        string aux;

        cout << "Introduceti numele vinului: ";
        getline(in, aux);
        vin.setNume(aux.c_str());

        cout << "Introduceti descrierea vinului: ";
        getline(in, aux);
        vin.setDescriere(aux);

        cout << "Introduceti tipul vinului (rosu, alb, rose): ";
        getline(in, aux);
        vin.tip = stringCaTipVin(aux);

        float pret = 0;
        cout << "Introduceti pretul: ";
        in >> pret;
        vin.setPret(pret);

        pret = 0;
        cout << "Introduceti pretul minim: ";
        in >> pret;
        vin.setPretMinim(pret);

        cout << "Introduceti data imbutelierii: \n";
        in >> vin.dataImbutelierii;

        cout << "[INFO] ID Vin: " << vin.id << '\n';

        return in;
    }

    friend ostream& operator<<(ostream& out, const Vin& vin) {
        schimbaCuloarea(4);
        out << "ID: " << vin.id << '\n';

        schimbaCuloarea(3);
        out << "Nume: ";
        if (vin.nume != NULL)
            out << vin.nume;
        out << '\n';

        out << "Descriere: " << vin.descriere << '\n';
        out << "Tip: " << tipVinCaString(vin.tip) << '\n';
        out << "Pret Minim: " << vin.pretMinim << "\n";
        out << "Pret: " << vin.pret << '\n';
        out << "Data imbutelierii: " << vin.dataImbutelierii.pentruConsola();

        return out;
    }

    friend ofstream& operator<<(ofstream& out, const Vin& vin) {
        out << vin.id << '\n';

        if (vin.nume != NULL)
            out << vin.nume;
        out << '\n';
        out << vin.descriere << '\n';
        out << tipVinCaString(vin.tip) << '\n';
        out << vin.pretMinim << " " << vin.pret << '\n';
        out << vin.dataImbutelierii.pentruFisierText();

        return out;
    }

    friend ifstream& operator>>(ifstream& in, Vin& vin) {
        in >> vin.id;
        in.get();

        string aux;
        getline(in, aux);
        vin.setNume(aux.c_str());

        getline(in, aux);
        vin.setDescriere(aux);

        getline(in, aux);
        vin.tip = stringCaTipVin(aux);

        in >> vin.pretMinim >> vin.pret;

        Data data;
        in >> data.zi >> data.luna >> data.an;
        vin.dataImbutelierii = data;

        return in;
    }

    bool imbuteliatInainteDe(Data data) const {
        if (this->dataImbutelierii < data)
            return true;

        return false;
    }

    float calculeazaValoareaAdaugata() const {
        return this->pret - this->pretMinim;
    }

    Vin operator+(float pret) const {
        Vin copie = *this;
        copie.pret = copie.pret + pret;

        return copie;
    }

    Vin operator-(float pret) const {
        Vin copie = *this;
        copie.pret = copie.pret - pret;

        return copie;
    }

    explicit operator string() const {
        return this->nume;
    }

    operator TipVin() const {
        return this->tip;
    }

    Vin& operator! () {
        this->pret = this->pretMinim;

        return *this;
    }

    bool operator<=(const Vin& vin) const {
        if (this->pret <= vin.pret)
            return true;
        return false;
    }

    bool operator<=(float pret) const {
        if (this->pret <= pret)
            return true;
        return false;
    }

    bool operator<(const Vin& vin) const {
        if (this->pret < vin.pret)
            return true;
        return false;
    }

    bool operator<(float pret) const {
        if (this->pret < pret)
            return true;
        return false;
    }

    bool operator==(const Vin& vin) const {
        if (this->id == vin.id)
            return true;
        return false;
    }

    bool operator!=(const Vin& vin) const {
        return !this->operator==(vin);
    }
};

enum class Gen {
    Masculin, Feminin, Altul
};

string genCaString(Gen gen) {
    switch (gen) {
    case Gen::Masculin:
        return "masculin";
    case Gen::Feminin:
        return "feminin";
    default:
        return "altul";
    }
}

Gen stringCaGen(string gen) {
    for (int i = 0; i < gen.length(); i++)
        gen[i] = tolower(gen[i]);

    if (gen == "masculin")
        return Gen::Masculin;

    if (gen == "feminin")
        return Gen::Feminin;

    if (gen == "altul")
        return Gen::Altul;

    throw "Gen necunoscut";
}

class Persoana {
private:
    int id = -1;
    char* prenume = NULL;
    char* nume = NULL;
    string email = "";
    string telefon = "";
    Gen gen = Gen::Altul;
    Data dataNasterii = Data();

public:
    int getID() const {
        return this->id;
    }

    const char* getPrenume() const {
        return this->prenume;
    }

    const char* getNume() const {
        return this->nume;
    }

    string getEmail() const {
        return this->email;
    }

    string getTelefon() const {
        return this->telefon;
    }

    Gen getGen() const {
        return this->gen;
    }

    Data getDataNasterii() const {
        return this->dataNasterii;
    }

    void setPrenume(const char* prenumeNou) {
        if (prenumeNou == NULL)
            throw "Prenumele nu poate fi null";

        if (this->prenume != NULL) {
            delete[] this->prenume;
            this->prenume = NULL;
        }

        this->prenume = new char[strlen(prenumeNou) + 1];
        strcpy(this->prenume, prenumeNou);
    }

    void setNume(const char* numeNou) {
        if (numeNou == NULL)
            throw "Numele nu poate fi null";

        if (this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }

        this->nume = new char[strlen(numeNou) + 1];
        strcpy(this->nume, numeNou);
    }

    void setEmail(string emailNou) {
        if (emailNou == "")
            throw "Email-ul nu poate fi gol";

        this->email = emailNou;
    }

    void setTelefon(string telefonNou) {
        if (telefonNou.length() != 10)
            throw "Numar telefon invalid";

        this->telefon = telefonNou;
    }

    Persoana() {
        this->id = genereazaID();
        this->setPrenume("lipsa");
        this->setNume("lipsa");
        this->email = "lipsa";
        this->telefon = "lipsa";
        this->gen = Gen::Altul;
        this->dataNasterii = Data();
    }

    Persoana(const char* prenume, const char* nume, string email, string telefon, Gen gen, Data dataNasterii) {
        this->id = genereazaID();
        this->setPrenume(prenume);
        this->setNume(nume);
        this->setEmail(email);
        this->setTelefon(telefon);
        this->gen = gen;
        this->dataNasterii = dataNasterii;
    }

    Persoana(const Persoana& persoana) {
        this->id = persoana.id;
        this->setPrenume(persoana.prenume);
        this->setNume(persoana.nume);
        this->setEmail(persoana.email);
        this->setTelefon(persoana.telefon);
        this->gen = persoana.gen;
        this->dataNasterii = persoana.dataNasterii;
    }

    Persoana& operator=(const Persoana& persoana) {
        if (this == &persoana)
            return *this;

        this->id = persoana.id;
        this->setPrenume(persoana.prenume);
        this->setNume(persoana.nume);
        this->setEmail(persoana.email);
        this->setTelefon(persoana.telefon);
        this->gen = persoana.gen;
        this->dataNasterii = persoana.dataNasterii;

        return *this;
    }

    virtual ~Persoana() {
        if (this->prenume != NULL) {
            delete[] this->prenume;
            this->prenume = NULL;
        }

        if (this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }
    }

    friend istream& operator>>(istream& in, Persoana& persoana) {
        string aux;

        cout << "Introduceti prenumele: ";
        getline(in, aux);
        persoana.setPrenume(aux.c_str());

        cout << "Introduceti numele: ";
        getline(in, aux);
        persoana.setNume(aux.c_str());

        cout << "Introduceti email-ul: ";
        getline(in, aux);
        persoana.setEmail(aux);

        cout << "Introduceti numarul de telefon (10 cifre): ";
        getline(in, aux);
        persoana.setTelefon(aux);

        cout << "Introduceti genul (masculin, feminin, altul): ";
        getline(in, aux);
        persoana.gen = stringCaGen(aux);

        cout << "Introduceti data nasterii: " << '\n';
        in >> persoana.dataNasterii;

        cout << "[INFO] ID Persoana: " << persoana.id << '\n';

        return in;
    }

    friend ostream& operator<<(ostream& out, const Persoana& persoana) {
        schimbaCuloarea(4);
        out << "ID: " << persoana.id << '\n';

        schimbaCuloarea(6);
        out << "Prenume: " << persoana.prenume << '\n';
        out << "Nume: " << persoana.nume << '\n';
        out << "Email: " << persoana.email << '\n';
        out << "Telefon: " << persoana.telefon << '\n';
        out << "Gen: " << genCaString(persoana.gen) << '\n';
        out << "Data nasterii: " << persoana.dataNasterii.pentruConsola();

        return out;
    }

    friend ofstream& operator<<(ofstream& out, const Persoana& persoana) {
        out << persoana.id << '\n';
        out << persoana.prenume << '\n';
        out << persoana.nume << '\n';
        out << persoana.email << '\n';
        out << persoana.telefon << '\n';
        out << genCaString(persoana.gen) << '\n';
        out << persoana.dataNasterii.pentruFisierText();

        return out;
    }

    friend ifstream& operator>>(ifstream& in, Persoana& persoana) {
        in >> persoana.id;
        in.get();

        string aux;
        getline(in, aux);
        persoana.setPrenume(aux.c_str());

        getline(in, aux);
        persoana.setNume(aux.c_str());

        getline(in, aux);
        persoana.email = aux;

        getline(in, aux);
        persoana.telefon = aux;

        getline(in, aux);
        persoana.gen = stringCaGen(aux);

        in >> persoana.dataNasterii.zi >> persoana.dataNasterii.luna >> persoana.dataNasterii.an;

        return in;
    }

    string getNumeComplet() const {
        string numeComplet = this->nume;
        numeComplet += " ";
        numeComplet += this->prenume;

        return numeComplet;
    }

    bool nascutInainteDe(const Data& data) const {
        if (this->dataNasterii < data)
            return true;

        return false;
    }

    explicit operator string() const {
        return this->getNumeComplet();
    }

    bool operator<=(const Persoana& persoana) {
        if (this->id <= persoana.id)
            return true;
        return false;
    }

    bool operator<(const Persoana& persoana) {
        if (this->id < persoana.id)
            return true;
        return false;
    }

    bool operator==(const Persoana& persoana) const {
        if (this->id == persoana.id)
            return true;
        return false;
    }

    bool operator!=(const Persoana& persoana) const {
        return !this->operator==(persoana);
    }

    virtual string getTipClasa() = 0;

    virtual void citesteDeLaTastatura() = 0;

    virtual void afiseazaLaTastatura() = 0;
};

enum class FunctieAngajat {
    Operator,
    Manager,
    Curier,
    Tehnician
};

string functieAngajatCaString(FunctieAngajat functie) {
    switch (functie) {
    case FunctieAngajat::Operator:
        return "operator";
    case FunctieAngajat::Manager:
        return "manager";
    case FunctieAngajat::Curier:
        return "curier";
    default:
        return "tehnician";
    }
}

FunctieAngajat stringCaFunctieAngajat(string function) {
    for (int i = 0; i < function.length(); i++)
        function[i] = tolower(function[i]);

    if (function == "operator")
        return FunctieAngajat::Operator;

    if (function == "manager")
        return FunctieAngajat::Manager;

    if (function == "curier")
        return FunctieAngajat::Curier;

    if (function == "tehnician")
        return FunctieAngajat::Tehnician;

    throw "Functie angajat necunoscuta";
}

class Angajat : public Persoana {
private:
    float salariu = 0;
    Data dataAngajarii = Data();
    FunctieAngajat functie = FunctieAngajat::Curier;

public:
    float getSalariu() const {
        return this->salariu;
    }

    Data getDataAngajarii() const {
        return this->dataAngajarii;
    }

    FunctieAngajat getFunction() const {
        return this->functie;
    }

    void setSalariu(float salariuNou) {
        if (salariuNou < 0)
            throw "Salariul nu poate fi negativ";

        this->salariu = salariuNou;
    }

    void setFunctie(FunctieAngajat functieNoua) {
        this->functie = functieNoua;
    }

    Angajat() : Persoana() {
        this->salariu = 0;
        this->dataAngajarii = Data();
        this->functie = FunctieAngajat::Curier;
    }

    Angajat(const char* prenume, const char* nume, string email, string telefon, Gen gen, Data dataNasterii,
        float salariu, Data dataAngajarii, FunctieAngajat functie) :
        Persoana(prenume, nume, email, telefon, gen, dataNasterii) {
        this->setSalariu(salariu);
        this->dataAngajarii = dataAngajarii;
        this->functie = functie;
    }

    Angajat(const Angajat& angajat) : Persoana(angajat) {
        this->setSalariu(angajat.salariu);
        this->dataAngajarii = angajat.dataAngajarii;
        this->functie = angajat.functie;
    }

    Angajat& operator=(const Angajat& angajat) {
        if (this == &angajat)
            return *this;

        Persoana::operator=(angajat);
        this->setSalariu(angajat.salariu);
        this->dataAngajarii = angajat.dataAngajarii;
        this->functie = angajat.functie;

        return *this;
    }

    friend istream& operator>>(istream& in, Angajat& angajat) {
        Persoana& angajatCaPersoana = angajat;
        in >> angajatCaPersoana;

        float salariu;
        cout << "Introduceti salariu: ";
        in >> salariu;
        angajat.setSalariu(salariu);

        cout << "Introduceti data angajarii: \n";
        in >> angajat.dataAngajarii;
        in.get();

        string aux;
        cout << "Introduceti functia (operator, manager, curier, tehnician): ";
        getline(in, aux);
        angajat.setFunctie(stringCaFunctieAngajat(aux));

        return in;
    }

    friend ostream& operator<<(ostream& out, const Angajat& angajat) {
        const Persoana& angajatCaPersoana = angajat;
        out << angajatCaPersoana << '\n';

        schimbaCuloarea(9);
        out << "Salariu: " << angajat.salariu << '\n';
        out << "Data angajarii: " << angajat.dataAngajarii.pentruConsola() << '\n';
        out << "Functie: " << functieAngajatCaString(angajat.functie);

        return out;
    }

    friend ofstream& operator<<(ofstream& out, const Angajat& angajat) {
        const Persoana& angajatCaPersoana = angajat;
        out << angajatCaPersoana << '\n';

        out << angajat.salariu << '\n';
        out << angajat.dataAngajarii.pentruFisierText() << '\n';
        out << functieAngajatCaString(angajat.functie);

        return out;
    }

    friend ifstream& operator>>(ifstream& in, Angajat& angajat) {
        Persoana& angajatCaPersoana = angajat;
        in >> angajatCaPersoana;

        in >> angajat.salariu;
        in >> angajat.dataAngajarii.zi >> angajat.dataAngajarii.luna >> angajat.dataAngajarii.an;
        in.get();

        string aux;
        getline(in, aux);
        angajat.functie = stringCaFunctieAngajat(aux);

        return in;
    }

    bool employedBefore(const Data& data) const {
        if (this->dataAngajarii < data)
            return true;

        return false;
    }

    Angajat operator+(float valoare) const {
        Angajat copie = *this;
        copie.salariu = copie.salariu + valoare;

        return copie;
    }

    Angajat operator-(float valoare) const {
        Angajat copie = *this;
        copie.salariu = copie.salariu - valoare;

        return copie;
    }

    string getTipClasa() {
        return "Angajat";
    }

    void citesteDeLaTastatura() {
        cin >> *this;
    }

    void afiseazaLaTastatura() {
        cout << *this << '\n';
    }
};

class Client : public Persoana {
private:
    float venit = 0;

public:
    float getVenit() const {
        return this->venit;
    }

    void setVenit(float venitNou) {
        if (venitNou < 0)
            throw "Venitul nu poate fi negativ";

        this->venit = venitNou;
    }

    Client() : Persoana() {
        this->venit = 0;
    }

    Client(const char* prenume, const char* nume, string email, string telefon, Gen gen, Data dataNasterii,
        float venit) :
        Persoana(prenume, nume, email, telefon, gen, dataNasterii) {
        this->setVenit(venit);
    }

    Client(const Client& client) : Persoana(client) {
        this->setVenit(client.venit);
    }

    Client& operator=(const Client& client) {
        if (this == &client)
            return *this;

        Persoana::operator=(client);
        this->venit = client.venit;

        return *this;
    }

    friend istream& operator>>(istream& in, Client& client) {
        Persoana& clientCaPersoana = client;
        in >> clientCaPersoana;

        float venit;
        cout << "Introduceti venitul: ";
        in >> venit;
        client.setVenit(venit);

        return in;
    }

    friend ostream& operator<<(ostream& out, const Client& client) {
        const Persoana& clientCaPersoana = client;
        out << clientCaPersoana << '\n';

        schimbaCuloarea(5);
        out << "Venit: " << client.venit;

        return out;
    }

    friend ofstream& operator<<(ofstream& out, const Client& client) {
        const Persoana& clientAsPerson = client;
        out << clientAsPerson << '\n';

        out << client.venit;

        return out;
    }

    friend ifstream& operator>>(ifstream& in, Client& client) {
        Persoana& clientCaPersoana = client;
        in >> clientCaPersoana;

        in >> client.venit;

        return in;
    }

    Client operator+(float valoare) const {
        Client copie = *this;
        copie.venit = copie.venit + valoare;

        return copie;
    }

    Client operator-(float valoare) const {
        Client copie = *this;
        copie.venit = copie.venit - valoare;

        return copie;
    }

    string getTipClasa() {
        return "Client";
    }

    void citesteDeLaTastatura() {
        cin >> *this;
    }

    void afiseazaLaTastatura() {
        cout << *this << '\n';
    }
};

class ComandaVin {
private:
    static int NumarComenziVin;
    int idVin = -1;
    float numarSticle = 0;

public:
    static int getNumarComenziVin() {
        return ComandaVin::NumarComenziVin;
    }

    int getIdVin() const {
        return this->idVin;
    }

    float getNumarSticle() const {
        return this->numarSticle;
    }

    void setIdVin(int idVinNou) {
        bool valid = false;
        if (date_Vinuri.find(idVinNou) != date_Vinuri.end())
            valid = true;

        if (!valid)
            throw "ID vin invalid";

        this->idVin = idVinNou;
    }

    void setNumarSticle(float numarSticleNou) {
        if (numarSticleNou <= 0)
            throw "Noul numar de sticle nu poate fi <= 0";

        this->numarSticle = numarSticleNou;
    }

    ComandaVin() {
        ComandaVin::NumarComenziVin++;
        this->idVin = -1;
        this->numarSticle = -1;
    }

    ComandaVin(int idVin, float numarSticle) {
        ComandaVin::NumarComenziVin++;

        this->setIdVin(idVin);
        this->setNumarSticle(numarSticle);
    }

    ComandaVin(const ComandaVin& comandaVin) {
        ComandaVin::NumarComenziVin++;

        this->idVin = comandaVin.idVin;
        this->numarSticle = comandaVin.numarSticle;
    }

    ComandaVin& operator=(const ComandaVin& comandaVin) {
        if (this == &comandaVin)
            return *this;

        this->idVin = comandaVin.idVin;
        this->numarSticle = comandaVin.numarSticle;

        return *this;
    }

    ~ComandaVin() {
        ComandaVin::NumarComenziVin--;
    }

    friend istream& operator>>(istream& in, ComandaVin& comandaVin) {
        int idVin = 0;
        cout << "Introduceti ID-ul vinului: ";
        in >> idVin;
        comandaVin.setIdVin(idVin);

        float numarSticle = 0;
        cout << "Introduceti numarul de sticle: ";
        in >> numarSticle;
        comandaVin.setNumarSticle(numarSticle);

        return in;
    }

    friend ostream& operator<<(ostream& out, const ComandaVin& comandaVin) {
        schimbaCuloarea(2);
        out << "[NumarSticle]: " << comandaVin.numarSticle << '\n';
        out << "[Vin]: \n";
        if (date_Vinuri.find(comandaVin.idVin) != date_Vinuri.end())
            out << date_Vinuri[comandaVin.idVin];

        return out;
    }

    friend ofstream& operator<<(ofstream& out, const ComandaVin& comandaVin) {
        out << comandaVin.idVin << ' ' << comandaVin.numarSticle;

        return out;
    }

    friend ifstream& operator>>(ifstream& in, ComandaVin& comandaVin) {
        in >> comandaVin.idVin;
        in >> comandaVin.numarSticle;

        return in;
    }

    ComandaVin operator+(float valoare) const {
        ComandaVin copie = *this;
        copie.numarSticle = copie.numarSticle + valoare;

        return copie;
    }

    ComandaVin operator-(float valoare) const {
        ComandaVin copie = *this;
        copie.numarSticle = copie.numarSticle - valoare;

        return copie;
    }

    float calculeazaPretulComenzii() const {
        float pretVin = 0;

        if (date_Vinuri.find(this->idVin) != date_Vinuri.end())
            pretVin = date_Vinuri[this->idVin].getPret();

        return pretVin * numarSticle;
    }

    operator float() const {
        return this->numarSticle;
    }

    bool operator<=(const ComandaVin& comandaVin) const {
        if (this->numarSticle <= comandaVin.numarSticle)
            return true;
        return false;
    }

    bool operator<(const ComandaVin& comandaVin) const {
        if (this->numarSticle < comandaVin.numarSticle)
            return true;
        return false;
    }

    bool operator==(const ComandaVin& comandaVin) const {
        if (this->idVin == comandaVin.idVin && this->numarSticle == comandaVin.numarSticle)
            return true;
        return false;
    }

    bool operator!=(const ComandaVin& comandaVin) const {
        return !this->operator==(comandaVin);
    }
};

int ComandaVin::NumarComenziVin = 0;

class Comanda {
private:
    int id = -1;
    int idClient = -1;
    int idAngajat = -1;

    int numarComenziVin = 0;
    ComandaVin* listaComenziVin = NULL;

public:
    int getID() const {
        return this->id;
    }

    int getIdClient() const {
        return this->idClient;
    }

    int getIdAngajat() const {
        return this->idAngajat;
    }

    int getNumarComenziVin() const {
        return this->numarComenziVin;
    }

    ComandaVin getComandaVin(int index) const {
        if (index >= 0 && index < this->numarComenziVin)
            return this->listaComenziVin[index];

        throw "Index in afara limitelor";
    }

    void setIdClient(const int idClientNou) {
        bool valid = false;
        if (date_Clienti.find(idClientNou) != date_Clienti.end())
            valid = true;

        if (!valid)
            throw "ID client invalid";

        this->idClient = idClientNou;
    }

    void setIdAngajat(const int idAngajatNou) {
        bool valid = false;
        if (date_Angajati.find(idAngajatNou) != date_Angajati.end())
            valid = true;

        if (!valid)
            throw "ID angajat invalid";

        this->idAngajat = idAngajatNou;
    }

    void setListaComenziVin(int numarComenziVinNou, const ComandaVin* listaComenziVinNoua) {
        if (listaComenziVinNoua == NULL || numarComenziVinNou <= 0)
            throw "Input invalid";

        if (this->listaComenziVin != NULL) {
            delete[] this->listaComenziVin;
            this->listaComenziVin = NULL;
        }

        this->numarComenziVin = numarComenziVinNou;
        this->listaComenziVin = new ComandaVin[numarComenziVinNou];

        for (int i = 0; i < numarComenziVinNou; i++)
            this->listaComenziVin[i] = listaComenziVinNoua[i];
    }

    Comanda() {
        this->id = genereazaID();
        this->idClient = -1;
        this->idAngajat = -1;
        this->numarComenziVin = 0;
        this->listaComenziVin = NULL;
    }

    Comanda(int idClient, int idAngajat, int numarComenziVin, ComandaVin* listaComenziVin) {
        this->id = genereazaID();
        this->setIdClient(idClient);
        this->setIdAngajat(idAngajat);
        this->setListaComenziVin(numarComenziVin, listaComenziVin);
    }

    Comanda(const Comanda& order) {
        this->id = order.id;
        this->idClient = order.idClient;
        this->idAngajat = order.idAngajat;
        this->setListaComenziVin(order.numarComenziVin, order.listaComenziVin);
    }

    Comanda& operator=(const Comanda& comanda) {
        if (this == &comanda)
            return *this;

        this->id = comanda.id;
        this->idClient = comanda.idClient;
        this->idAngajat = comanda.idAngajat;
        this->setListaComenziVin(comanda.numarComenziVin, comanda.listaComenziVin);

        return *this;
    }

    ~Comanda() {
        if (this->listaComenziVin != NULL) {
            delete[] this->listaComenziVin;
            this->listaComenziVin = NULL;
        }
    }

    friend istream& operator>>(istream& in, Comanda& comanda) {
        int id;

        cout << "Introduceti ID-ul clientului: ";
        in >> id;
        comanda.setIdClient(id);

        cout << "Introduceti ID-ul angajatului: ";
        in >> id;
        comanda.setIdAngajat(id);

        if (comanda.listaComenziVin != NULL) {
            delete[] comanda.listaComenziVin;
            comanda.listaComenziVin = NULL;
        }

        comanda.numarComenziVin = 0;

        int numarComenziVin;
        cout << "Introduceti numarul de comenzi vin: ";
        in >> numarComenziVin;
        if (numarComenziVin <= 0)
            throw "Numarul de comenzi vin nu poate fi <= 0";

        for (int i = 0; i < numarComenziVin; i++) {
            ComandaVin vin;
            cout << ">> Introduceti datele pentru comanda vin nr. " << i + 1 << ": \n";
            in >> vin;

            comanda.adaugaComandaVin(vin);
        }

        return in;
    }

    friend ostream& operator<<(ostream& out, const Comanda& comanda) {
        schimbaCuloarea(4);
        out << "ID Comanda: " << comanda.id << '\n';

        schimbaCuloarea(11);
        out << "[Client]: \n";
        if (date_Clienti.find(comanda.idClient) != date_Clienti.end())
            out << date_Clienti[comanda.idClient] << '\n';

        out << "\n";

        schimbaCuloarea(11);
        out << "[Angajat]: \n";
        if (date_Angajati.find(comanda.idAngajat) != date_Angajati.end())
            out << date_Angajati[comanda.idAngajat] << '\n';

        out << '\n';

        schimbaCuloarea(11);
        out << "[Vinuri]: \n";
        for (int i = 0; i < comanda.numarComenziVin; i++)
            out << ">> Vin " << i + 1 << ":\n" << comanda.listaComenziVin[i] << "\n\n";

        return out;
    }

    friend ofstream& operator<<(ofstream& out, const Comanda& comanda) {
        out << comanda.id << " " << comanda.idClient << ' ' << comanda.idAngajat << ' ' << comanda.numarComenziVin << '\n';
        for (int i = 0; i < comanda.numarComenziVin; i++)
            out << comanda.listaComenziVin[i] << '\n';

        return out;
    }

    friend ifstream& operator>>(ifstream& in, Comanda& comanda) {
        in >> comanda.id >> comanda.idClient >> comanda.idAngajat;

        int length;
        in >> length;
        for (int i = 0; i < length; i++) {
            ComandaVin comandaVin;
            in >> comandaVin;
            comanda.adaugaComandaVin(comandaVin);
        }

        return in;
    }

    float calculeazaPretulComenzii() const {
        float total = 0;
        for (int i = 0; i < this->numarComenziVin; i++)
            total = total + this->listaComenziVin[i].calculeazaPretulComenzii();

        return total;
    }

    void adaugaComandaVin(const ComandaVin& comandaVin) {
        ComandaVin* aux = new ComandaVin[this->numarComenziVin + 1];

        for (int i = 0; i < this->numarComenziVin; i++)
            aux[i] = this->listaComenziVin[i];
        aux[this->numarComenziVin] = comandaVin;

        if (this->listaComenziVin != NULL) {
            delete[] this->listaComenziVin;
            this->listaComenziVin = NULL;
        }

        this->numarComenziVin++;
        this->listaComenziVin = aux;
    }

    void stergeComandaVin(const ComandaVin& comandaVin) {
        if (this->numarComenziVin == 0)
            return;

        int indexComandaVin = -1;
        for (int i = 0; i < this->numarComenziVin; i++)
            if (this->listaComenziVin[i] == comandaVin) {
                indexComandaVin = i;
                break;
            }

        if (indexComandaVin == -1)
            return;

        ComandaVin* aux = new ComandaVin[this->numarComenziVin - 1];
        for (int i = 0; i < indexComandaVin; i++)
            aux[i] = this->listaComenziVin[i];

        for (int i = indexComandaVin + 1; i < this->numarComenziVin; i++)
            aux[i - 1] = this->listaComenziVin[i];

        this->numarComenziVin--;

        if (this->listaComenziVin != NULL) {
            delete[] this->listaComenziVin;
            this->listaComenziVin = NULL;
        }

        this->listaComenziVin = aux;
    }

    Comanda operator+(const ComandaVin& comandaVin) const {
        Comanda copy = *this;
        copy.adaugaComandaVin(comandaVin);

        return copy;
    }

    Comanda operator-(const ComandaVin& comandaVin) const {
        Comanda copy = *this;
        copy.stergeComandaVin(comandaVin);

        return copy;
    }

    ComandaVin operator[](int index) const {
        return this->getComandaVin(index);
    }

    operator int() const {
        return this->numarComenziVin;
    }

    bool operator<=(const Comanda& comanda) const {
        if (this->numarComenziVin <= comanda.numarComenziVin)
            return true;
        return false;
    }

    bool operator<(const Comanda& comanda) const {
        if (this->numarComenziVin < comanda.numarComenziVin)
            return true;
        return false;
    }

    bool operator==(const Comanda& comanda) const {
        if (this->idClient == comanda.idClient && this->idAngajat == comanda.idClient && this->numarComenziVin == comanda.numarComenziVin)
            for (int i = 0; i < this->numarComenziVin; i++)
                if (this->listaComenziVin[i] != comanda.listaComenziVin[i])
                    return false;
        return true;
    }

    bool operator!=(const Comanda& comanda) const {
        return !this->operator==(comanda);
    }
};

void testVin() {
    Vin vin1;
    Vin vin2("Vin2", 100, TipVin::Rosu, Data({ 1, 4, 2001 }));
    Vin vin3("Vin3", 250, Data({ 1, 5, 1997 }), "Vin vechi", 300, TipVin::Rose);
    Vin vin4(vin3);
    Vin vin5;
    vin5 = vin2;

    cout << vin1 << '\n' << vin2 << '\n' << vin3 << '\n' << vin4 << '\n' << vin5 << '\n';

    Vin vin6;
    try {
        cin >> vin6;
        cout << vin6 << '\n';
    }
    catch (const char* mesajEroare) {
        cout << "[Eroare]: " << mesajEroare << '\n';
    }

    ofstream g("test.txt");
    g << vin3 << '\n';
    g << vin2 << '\n';
    cout << vin3 << '\n';
    cout << vin2 << '\n';
    g.close();

    cout << '\n';

    ifstream f("test.txt");
    Vin vin7;
    Vin vin8;
    f >> vin7;
    f >> vin8;
    f.close();
    cout << vin7 << '\n';
    cout << vin8 << '\n';

    if (vin2.imbuteliatInainteDe(Data({ 5, 6, 2005 })))
        cout << "Vinul 2 a fost imbuteliat inainte de 5/6/2005\n";

    cout << "Vinul 3 are " << vin3.calculeazaValoareaAdaugata() << "lei valoare adaugata\n";
}

void testPersoana() {
    // Deoarece clasa Persoana are metode virtuale pure, nu mai putem crea obiecte de acest tip.

    // Persoana p1;
    // Persoana p2("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gen::Masculin, Data({ 5, 2, 1995 }));
    // Persoana p3(p2);
    // Persoana p4;
    // p4 = p2;

    // Persoana p5;
    // try {
    //     cin >> p5;
    //     cout << p5 << '\n';
    // }
    // catch (const char* mesajEroare) {
    //     cout << "[Eroare]: " << mesajEroare << '\n';
    // }

    // ofstream g("test.txt");
    // g << p2 << '\n';
    // g << p3 << '\n';
    // cout << p2 << '\n';
    // cout << p3 << '\n';
    // g.close();

    // cout << '\n';

    // ifstream f("test.txt");
    // Persoana p6;
    // Persoana p7;
    // f >> p6;
    // f >> p7;
    // f.close();
    // cout << p6 << '\n';
    // cout << p7 << '\n';

    // cout << "Numele complet al celei de-a doua persoana este: " << p2.getNumeComplet() << '\n';
}

void testAngajat() {
    Angajat a1;
    Angajat a2("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gen::Masculin, Data({ 5, 2, 1995 }), 3000, Data({ 5, 3, 2019 }), FunctieAngajat::Curier);
    Angajat a3(a2);
    Angajat a4;
    a4 = a2;

    Angajat a5;
    try {
        cin >> a5;
        cout << a5 << '\n';
    }
    catch (const char* mesajEroare) {
        cout << "[Eroare]: " << mesajEroare << '\n';
    }

    ofstream g("test.txt");
    g << a2 << '\n';
    g << a3 << '\n';
    cout << a2 << '\n';
    cout << a3 << '\n';
    g.close();

    cout << '\n';

    ifstream f("test.txt");
    Angajat a6;
    Angajat a7;
    f >> a6;
    f >> a7;
    f.close();
    cout << a6 << '\n';
    cout << a7 << '\n';

    cout << "Numele complet al celui de-al doilea angajat este: " << a2.getNumeComplet() << '\n';
}

void testClient() {
    Client c1;
    Client c2("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gen::Masculin, Data({ 5, 2, 1995 }), 4500);
    Client c3(c2);
    Client c4;
    c4 = c2;

    Client c5;
    try {
        cin >> c5;
        cout << c5 << '\n';
    }
    catch (const char* mesajEroare) {
        cout << "[Eroare]: " << mesajEroare << '\n';
    }

    ofstream g("test.txt");
    g << c2 << '\n';
    g << c3 << '\n';
    cout << c2 << '\n';
    cout << c3 << '\n';
    g.close();

    cout << '\n';

    ifstream f("test.txt");
    Client c6;
    Client c7;
    f >> c6;
    f >> c7;
    f.close();
    cout << c6 << '\n';
    cout << c7 << '\n';

    cout << "Numele complet al celui de-al doilea client este: " << c2.getNumeComplet() << '\n';
}

void testComandaVin() {
    Vin vin("Vin", 250, Data({ 1, 5, 1997 }), "Vin vechi", 300, TipVin::Rose);
    date_Vinuri.insert(make_pair(vin.getID(), vin));

    ComandaVin o1;
    ComandaVin o2(vin.getID(), 20);

    cout << "Total comanda 2: " << o2.calculeazaPretulComenzii() << '\n';
}

void testComanda() {
    Client client("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gen::Masculin, Data({ 5, 2, 1995 }), 4500);
    int clientID = client.getID();
    cout << "ID Client: " << clientID << '\n';
    date_Clienti.insert(make_pair(clientID, client));

    Angajat angajat("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gen::Masculin, Data({ 5, 2, 1995 }), 3000, Data({ 5, 3, 2019 }), FunctieAngajat::Curier);
    int idAngajat = angajat.getID();
    cout << "ID Angajat: " << idAngajat << '\n';
    date_Angajati.insert(make_pair(idAngajat, angajat));

    Vin vin("Vin", 250, Data({ 1, 5, 1997 }), "Vin vechi", 300, TipVin::Rose);
    int idVin = vin.getID();
    cout << "ID Vin: " << idVin << '\n';
    date_Vinuri.insert(make_pair(idVin, vin));

    ComandaVin comenziVin[] = { ComandaVin(idVin, 20) , ComandaVin(idVin, 40) };
    Comanda comanda(clientID, idAngajat, 2, comenziVin);

    cout << comanda << '\n';

    Comanda comanda2;
    comanda2.setIdClient(clientID);
    comanda2.setIdAngajat(idAngajat);
    comanda2.adaugaComandaVin(comenziVin[0]);
    comanda2.adaugaComandaVin(comenziVin[1]);

    cout << comanda2 << '\n';

    Comanda comanda3;
    try {
        cin >> comanda3;
        cout << comanda3 << '\n';
    }
    catch (const char* mesajEroare) {
        cout << "[Eroare]: " << mesajEroare << '\n';
    }
}

void incarcaDateleAplicatiei() {
    schimbaCuloarea(11);

    cout << "[Info] Se incarca datele aplicatiei...\n";
    ifstream fisierVinuri("vinuri.txt");
    int numarVinuri = 0;
    fisierVinuri >> numarVinuri;

    for (int i = 0; i < numarVinuri; i++) {
        Vin vin;
        fisierVinuri >> vin;
        date_Vinuri.insert(make_pair(vin.getID(), vin));
    }

    ifstream fisierClienti("clienti.txt");
    int numarClienti = 0;
    fisierClienti >> numarClienti;

    for (int i = 0; i < numarClienti; i++) {
        Client client;
        fisierClienti >> client;
        date_Clienti.insert(make_pair(client.getID(), client));
    }

    ifstream fisierAngajati("angajati.txt");
    int numarAngajati = 0;
    fisierAngajati >> numarAngajati;

    for (int i = 0; i < numarAngajati; i++) {
        Angajat angajat;
        fisierAngajati >> angajat;
        date_Angajati.insert(make_pair(angajat.getID(), angajat));
    }

    ifstream fisierComenzi("comenzi.txt");
    int numarComenzi = 0;
    fisierComenzi >> numarComenzi;

    for (int i = 0; i < numarComenzi; i++) {
        Comanda comanda;
        fisierComenzi >> comanda;
        date_Comenzi.insert(make_pair(comanda.getID(), comanda));
    }

    cout << "[Info] Datele aplicatiei s-au incarcat!\n";
}

void salveazaDateleAplicatiei() {
    ofstream fisierVinuri("vinuri.txt");

    fisierVinuri << date_Vinuri.size() << '\n';

    for (map<int, Vin>::iterator it = date_Vinuri.begin(); it != date_Vinuri.end(); it++)
        fisierVinuri << it->second << '\n';

    fisierVinuri.close();

    ofstream fisierClienti("clienti.txt");

    fisierClienti << date_Clienti.size() << '\n';

    for (map<int, Client>::iterator it = date_Clienti.begin(); it != date_Clienti.end(); it++)
        fisierClienti << it->second << '\n';

    fisierClienti.close();

    ofstream fisierAngajati("angajati.txt");

    fisierAngajati << date_Angajati.size() << '\n';

    for (map<int, Angajat>::iterator it = date_Angajati.begin(); it != date_Angajati.end(); it++)
        fisierAngajati << it->second << '\n';

    fisierAngajati.close();

    ofstream fisierComenzi("comenzi.txt");

    fisierComenzi << date_Comenzi.size() << '\n';

    for (map<int, Comanda>::iterator it = date_Comenzi.begin(); it != date_Comenzi.end(); it++)
        fisierComenzi << it->second << '\n';

    fisierComenzi.close();
}

class Meniu {
private:
    void arataMeniu() {
        schimbaCuloarea(3);
        cout << "\nMeniu\n";
        cout << "Alegeti optiunea: \n";
        cout << "-1) Testeaza clase\n";
        cout << '\n';
        cout << "1) Adauga Vin\n";
        cout << "2) Adauga Client\n";
        cout << "3) Adauga Angajat\n";
        cout << "4) Adauga Comanda\n";
        cout << '\n';
        cout << "5) Listeaza Vinuri\n";
        cout << "6) Listeaza Clienti\n";
        cout << "7) Listeaza Angajati\n";
        cout << "8) Listeaza Comenzi\n";
        cout << '\n';
        cout << "9)  Sterge Vin\n";
        cout << "10) Sterge Client\n";
        cout << "11) Sterge Angajat\n";
        cout << "12) Sterge Comanda\n";
        cout << '\n';
        cout << "13) Listeaza vinurile cu pretul intr-un interval\n";
        cout << "14) Listeaza vinurile imbuteliate inainte de o data\n";
        cout << "15) Listeaza angajatii cu salariul intr-un interval\n";
        cout << "16) Listeaza comenzile cu pretul intr-un interval\n";
        cout << '\n';
        cout << "17) Salveaza datele\n";
        cout << "18) Opreste programul\n";
        cout << "19) Listeaza toate persoanele\n";
        cout << "20) Goleste ecranul\n";
        cout << "\n";
    }
public:
    void run() {
        this->arataMeniu();

        while (true) {

            int optiune = 0;
            schimbaCuloarea(10);
            cout << "\nIntroduceti optiunea (0 arata meniul): ";
            cin >> optiune;
            cout << "\n";
            schimbaCuloarea(9);

            try {
                switch (optiune) {
                case -1: { // testeaza clasele
                    cin.get();
                    testVin();

                    cin.get();
                    testClient();

                    cin.get();
                    testAngajat();
                    testComanda();
                    testComandaVin();
                    break;
                }
                case 0: { // arata meniu
                    this->arataMeniu();
                    break;
                }
                case 1: { // adauga vin
                    cin.get();

                    Vin vin;
                    cout << ">> Introduceti datele vinului:\n";
                    cin >> vin;

                    date_Vinuri.insert(make_pair(vin.getID(), vin));
                    schimbaCuloarea(2);  cout << "[Succes]\n";

                    break;
                }
                case 2: { // adauga client
                    cin.get();

                    Client client;
                    cout << ">> Introduceti datele clientului:\n";
                    client.citesteDeLaTastatura();
                    // cin >> client;

                    date_Clienti.insert(make_pair(client.getID(), client));
                    schimbaCuloarea(2);  cout << "[Succes]\n";

                    break;
                }
                case 3: { // adauga angajat
                    cin.get();

                    Angajat angajat;
                    cout << ">> Introduceti datele angajatului:\n";
                    angajat.citesteDeLaTastatura();
                    // cin >> angajat;

                    date_Angajati.insert(make_pair(angajat.getID(), angajat));
                    schimbaCuloarea(2);  cout << "[Succes]\n";

                    break;
                }
                case 4: { // adauga comanda
                    Comanda comanda;
                    cout << ">> Introduceti datele comenzii:\n";
                    cin >> comanda;

                    date_Comenzi.insert(make_pair(comanda.getID(), comanda));
                    schimbaCuloarea(2);  cout << "[Succes]\n";

                    break;
                }
                case 5: { // listeaza vinuri
                    if (date_Vinuri.empty()) {
                        cout << "[Info] Nu exista vinuri in baza de date.\n";
                        break;
                    }

                    cout << "---------------------- Vinuri ----------------------\n";
                    for (map<int, Vin>::iterator it = date_Vinuri.begin(); it != date_Vinuri.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 6: { // listeaza clienti
                    if (date_Clienti.empty()) {
                        cout << "[Info] Nu exista clienti in baza de date.\n";
                        break;
                    }

                    cout << "---------------------- Clienti ----------------------\n";
                    for (map<int, Client>::iterator it = date_Clienti.begin(); it != date_Clienti.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 7: { // listeaza angajati
                    if (date_Angajati.empty()) {
                        cout << "[Info] Nu exista angajati in baza de date.\n";
                        break;
                    }

                    cout << "---------------------- Angajati ----------------------\n";
                    for (map<int, Angajat>::iterator it = date_Angajati.begin(); it != date_Angajati.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 8: { // listeaza comenzi
                    if (date_Comenzi.empty()) {
                        cout << "[Info] Nu exista comenzi in baza de date.\n";
                        break;
                    }

                    cout << "---------------------- Comenzi ----------------------\n";
                    for (map<int, Comanda>::iterator it = date_Comenzi.begin(); it != date_Comenzi.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 9: { // sterge vin
                    int idVin = 0;
                    cout << ">> Introduceti ID-ul vinului pe care doriti sa il stergeti: ";
                    cin >> idVin;

                    date_Vinuri.erase(idVin);
                    cout << "[Succes] Vin sters\n";

                    break;
                }
                case 10: { // sterge client
                    int idClient = 0;
                    cout << ">> Introduceti ID-ul clientului pe care doriti sa il stergeti: ";
                    cin >> idClient;

                    date_Clienti.erase(idClient);
                    cout << "[Succes] Client sters\n";

                    break;
                }
                case 11: { // sterge angajat
                    int idAngajat = 0;
                    cout << ">> Introduceti ID-ul clientului pe care doriti sa il stergeti: ";
                    cin >> idAngajat;

                    date_Angajati.erase(idAngajat);
                    cout << "[Succes] Angajat sters\n";

                    break;
                }
                case 12: { // sterge comanda
                    int idComanda = 0;
                    cout << ">> Introduceti ID-ul comenzii pe care doriti sa o stergeti: ";
                    cin >> idComanda;

                    date_Comenzi.erase(idComanda);
                    cout << "[Succes] Comanda stearsa\n";

                    break;
                }
                case 13: { // Listeaza vinurile cu pretul intr-un interval
                    int pretMinim = 0;
                    cout << ">> Introduceti pretul minim: ";
                    cin >> pretMinim;

                    int pretMaxim = 0;
                    cout << ">> Introduceti pretul maxim: ";
                    cin >> pretMaxim;

                    ofstream fisierRaport("raport.txt");

                    int numarVinuri = 0;
                    for (map<int, Vin>::iterator it = date_Vinuri.begin(); it != date_Vinuri.end(); it++) {
                        Vin& vin = it->second;

                        if (vin.getPret() >= pretMinim && vin.getPret() <= pretMaxim) {
                            numarVinuri = numarVinuri + 1;
                            fisierRaport << "----------- " << numarVinuri << " -----------\n";

                            fisierRaport << "ID: " << vin.getID() << '\n';
                            fisierRaport << "Nume: " << vin.getNume() << '\n';
                            fisierRaport << "Descriere: " << vin.getDescriere() << '\n';
                            fisierRaport << "Tip: " << tipVinCaString(vin.getTipVin()) << '\n';
                            fisierRaport << "Pret minim: " << vin.getPretMinim() << '\n';
                            fisierRaport << "Pret: " << vin.getPret() << '\n';
                            fisierRaport << "Valoare adaugata: " << vin.calculeazaValoareaAdaugata() << '\n';
                            Data dataImbutelierii = vin.getDataImbutelierii();
                            fisierRaport << "Imbuteliat la data " << dataImbutelierii.zi << '/' << dataImbutelierii.luna << '/' << dataImbutelierii.an << '\n';

                            fisierRaport << "\n";
                        }
                    }

                    fisierRaport.close();

                    cout << "[Succes] Raport generat!\n";

                    break;
                }
                case 14: { // Listeaza vinurile imbuteliate inainte de o data
                    Data data;
                    cout << ">> Introduceti data:\n";
                    cin >> data;

                    ofstream fisierRaport("raport.txt");

                    int numarVinuri = 0;
                    for (map<int, Vin>::iterator it = date_Vinuri.begin(); it != date_Vinuri.end(); it++) {
                        Vin& vin = it->second;

                        if (vin.imbuteliatInainteDe(data)) {
                            numarVinuri = numarVinuri + 1;
                            fisierRaport << "----------- " << numarVinuri << " -----------\n";

                            fisierRaport << "ID: " << vin.getID() << '\n';
                            fisierRaport << "Nume: " << vin.getNume() << '\n';
                            fisierRaport << "Descriere: " << vin.getDescriere() << '\n';
                            fisierRaport << "Tip: " << tipVinCaString(vin.getTipVin()) << '\n';
                            fisierRaport << "Pret minim: " << vin.getPretMinim() << '\n';
                            fisierRaport << "Pret: " << vin.getPret() << '\n';
                            fisierRaport << "Valoare adaugata: " << vin.calculeazaValoareaAdaugata() << '\n';
                            Data dataImbutelierii = vin.getDataImbutelierii();
                            fisierRaport << "Imbuteliat la data " << dataImbutelierii.zi << '/' << dataImbutelierii.luna << '/' << dataImbutelierii.an << '\n';

                            fisierRaport << "\n";
                        }
                    }

                    fisierRaport.close();

                    cout << "[Succes] Raport generat!\n";

                    break;
                }
                case 15: { // Listeaza angajatii cu salariul intr-un interval
                    int salariuMinim = 0;
                    cout << ">> Introduceti salariulMinim: ";
                    cin >> salariuMinim;

                    int salariuMaxim = 0;
                    cout << ">> Introduceti salariulMaxim: ";
                    cin >> salariuMaxim;

                    ofstream fisierRaport("raport.txt");

                    int numarAngajati = 0;
                    for (map<int, Angajat>::iterator it = date_Angajati.begin(); it != date_Angajati.end(); it++) {
                        Angajat& angajat = it->second;

                        if (angajat.getSalariu() >= salariuMinim && angajat.getSalariu() <= salariuMaxim) {
                            numarAngajati = numarAngajati + 1;
                            fisierRaport << "----------- " << numarAngajati << " -----------\n";

                            fisierRaport << "ID: " << angajat.getID() << '\n';
                            fisierRaport << "Nume: " << angajat.getNumeComplet() << '\n';
                            fisierRaport << "Email: " << angajat.getEmail() << '\n';
                            fisierRaport << "Telefon: " << angajat.getTelefon() << '\n';
                            fisierRaport << "Gen: " << genCaString(angajat.getGen()) << '\n';

                            Data dataNasterii = angajat.getDataNasterii();
                            fisierRaport << "Nascut la data " << dataNasterii.zi << '/' << dataNasterii.luna << '/' << dataNasterii.an << '\n';

                            Data dataAngajarii = angajat.getDataAngajarii();
                            fisierRaport << "Angajat la data " << dataAngajarii.zi << '/' << dataAngajarii.luna << '/' << dataAngajarii.an << '\n';

                            fisierRaport << "\n";
                        }
                    }

                    fisierRaport.close();

                    cout << "[Succes] Raport generat!\n";

                    break;
                }
                case 16: { // Listeaza comenzile cu pretul intr-un interval
                    int pretMinim = 0;
                    cout << ">> Introduceti pretul minim: ";
                    cin >> pretMinim;

                    int pretMaxim = 0;
                    cout << ">> Introduceti pretul maxim: ";
                    cin >> pretMaxim;

                    ofstream fisierRaport("raport.txt");

                    int numarComenzi = 0;
                    for (map<int, Comanda>::iterator it = date_Comenzi.begin(); it != date_Comenzi.end(); it++) {
                        Comanda& comanda = it->second;
                        float pretComanda = comanda.calculeazaPretulComenzii();

                        if (pretComanda >= pretMinim && pretComanda <= pretMaxim) {
                            numarComenzi = numarComenzi + 1;
                            fisierRaport << "----------- " << numarComenzi << " -----------\n";
                            fisierRaport << "ID Comanda: " << comanda.getID() << '\n';
                            fisierRaport << "Pret: " << pretComanda << "lei\n";

                            if (date_Clienti.find(comanda.getIdClient()) != date_Clienti.end()) {
                                Client& client = date_Clienti[comanda.getIdClient()];
                                fisierRaport << "ID Client: " << client.getID() << '\n';
                                fisierRaport << "Nume client: " << client.getNumeComplet() << '\n';
                            }
                            else {
                                fisierRaport << "Clientul a fost sters din baza de date.\n";
                            }

                            if (date_Angajati.find(comanda.getIdAngajat()) != date_Angajati.end()) {
                                Angajat& employee = date_Angajati[comanda.getIdAngajat()];
                                fisierRaport << "ID Angajat: " << employee.getID() << '\n';
                                fisierRaport << "Nume angajat: " << employee.getNumeComplet() << '\n';
                            }
                            else {
                                fisierRaport << "Angajatul a fost sters din baza de date.\n";
                            }

                            for (int i = 0; i < comanda.getNumarComenziVin(); i++) {
                                ComandaVin comandaVin = comanda[i];

                                fisierRaport << "Vin" << i << ": ";

                                if (date_Vinuri.find(comandaVin.getIdVin()) != date_Vinuri.end()) {
                                    Vin& vin = date_Vinuri[comandaVin.getIdVin()];
                                    fisierRaport << "ID(" << vin.getID() << ") ~ Nume(" << vin.getNume() << ") ~ NumarSticle(" << comandaVin.getNumarSticle() << ")\n";
                                }
                                else {
                                    fisierRaport << "Vinul a fost sters din baza de date.\n";
                                }

                            }

                            fisierRaport << "\n";
                        }
                    }

                    fisierRaport.close();

                    cout << "[Succes] Raport generat!\n";

                    break;
                }
                case 17: { // Salveaza datele
                    salveazaDateleAplicatiei();

                    cout << "[Succes] Datele au fost salvate!\n";

                    break;
                }
                case 18: { // Opreste programul
                    return;
                }
                case 19: { // Listeaza toate persoanele
                    vector<Persoana*> persoane;

                    for (map<int, Client>::iterator it = date_Clienti.begin(); it != date_Clienti.end(); it++) {
                        persoane.push_back(&(it->second));
                    }

                    for (map<int, Angajat>::iterator it = date_Angajati.begin(); it != date_Angajati.end(); it++) {
                        persoane.push_back(&(it->second));
                    }

                    for (std::vector<Persoana*>::iterator it = persoane.begin(); it != persoane.end(); it++) {
                        Persoana* persoana = *it;

                        cout << "--------------------------------------\n";
                        cout << persoana->getTipClasa() << '\n';
                        persoana->afiseazaLaTastatura();
                        cout << '\n';
                    }

                    break;
                }
                case 20: { // Goleste ecranul
                    system("cls");
                    break;
                }
                default: {
                    throw "Optiune invalida";
                }
                }
            }
            catch (const char* mesajEroare) {
                schimbaCuloarea(4);
                cout << "\n[Eroare]: " << mesajEroare << "\n\n";
            }
        }
    }
};

int main() {
    incarcaDateleAplicatiei();

    Meniu meniu;
    meniu.run();

    salveazaDateleAplicatiei();

    return 0;
}

/**
 * Pentru partea a doua am transformat clasa Persoana intr-o clasa abstracta adaugand doua metode virtuale pure:
 *  virtual string getTipClasa() = 0; -> returneaza tipul clasei ca string. (avem "Client" sau "Angajat")
 *  virtual void citesteDeLaTastatura() = 0; -> citeste obiectul de la tastatura.
 *  virtual void afiseazaLaTastatura() = 0; -> afiseaza obiectul la tastatura.
 *
 * Am adaugat o noua optiune in meniu care listeaza toate persoanele din baza de date.
 *  Pentru implementare am folosit un vector de pointeri la clasa de baza Persoana in care am adaugat toti clientii
 *  si angajatii, apoi i-am listat.
*/
