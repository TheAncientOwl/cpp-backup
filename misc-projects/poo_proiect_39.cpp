#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// <summary>
/// Obliga clasele care o mostenesc sa implementeze metodele de scriere si citire in/din fisiere
/// *le obliga pt ca metodele sunt virtuale pure
/// </summary>
class FisierInOut
{
public:
	virtual ofstream& output(ofstream& out) = 0; //scriere
	virtual ifstream& input(ifstream& in) = 0;   //citire
};

class Data : public FisierInOut
{
private:
	int zi;
	int luna;
	int an;

private:
	bool eAnBisect(int an)
	{
		return (an % 4 == 0 && (an % 100 == 0 && an % 400 == 0));
	}

public:
	Data() : zi(1), luna(1), an(2000) {}

	Data(int v_zi, int v_luna, int v_an)
	{
		this->setZi(v_zi);
		this->setLuna(v_luna);
		this->setAn(v_an);
	}

	Data(const Data& data) : zi(data.zi), luna(data.luna), an(data.an) {}

	Data& operator=(const Data& data)
	{
		if (this == &data)
			return *this;

		this->zi = data.zi;
		this->luna = data.luna;
		this->an = data.an;

		return *this;
	}

	~Data()
	{
	}

	int getZi() const
	{
		return this->zi;
	}

	int getLuna() const
	{
		return this->luna;
	}

	int getAn() const
	{
		return this->an;
	}

	void setZi(int ziNoua)
	{
		if (ziNoua < 1 || ziNoua > 31)
			throw "Zi invalida.";

		if (luna == 2)
		{
			if (ziNoua > 28)
			{
				if (ziNoua == 29)
				{
					if (!eAnBisect(an))
						throw "Februarie are max 28 zile in anii care nu sunt bisecti.";
				}
				else
					throw "Zi invalida pentru luna februarie.";
			}
		}

		this->zi = ziNoua;
	}

	void setLuna(int lunaNoua)
	{
		if (lunaNoua < 1 || lunaNoua > 12)
			throw "Luna invalida.";

		if (lunaNoua == 2)
		{
			if (zi > 28)
			{
				if (zi == 29)
				{
					if (!eAnBisect(an))
						throw "Februarie are max 28 zile in anii care nu sunt bisecti.";
				}
				else
					throw "Zi invalida pentru luna februarie.";
			}
		}

		this->luna = lunaNoua;
	}

	void setAn(int anNou)
	{
		if (anNou < 1900 || anNou > 3000)
			throw "An invalid";

		if (luna == 2)
		{
			if (zi > 28)
			{
				if (zi == 29)
				{
					if (!eAnBisect(anNou))
						throw "Februarie are max 28 zile in anii care nu sunt bisecti.";
				}
				else
					throw "Zi invalida pentru luna februarie.";
			}
		}

		this->an = anNou;
	}

	friend istream& operator>>(istream& in, Data& data)
	{
		int zi = 0;
		bool dateleIntroduseSuntValide = true;
		do
		{
			dateleIntroduseSuntValide = true;
			std::cout << ">> zi: ";
			in >> zi;
			try
			{
				data.setZi(zi);
			}
			catch (const char* mesaj)
			{
				std::cout << "Eroare: " << mesaj << '\n';
				dateleIntroduseSuntValide = false;
			}
		} while (!dateleIntroduseSuntValide);

		int luna = 0;
		dateleIntroduseSuntValide = true;
		do
		{
			dateleIntroduseSuntValide = true;
			std::cout << ">> luna: ";
			in >> luna;
			try
			{
				data.setLuna(luna);
			}
			catch (const char* mesaj)
			{
				std::cout << "Eroare: " << mesaj << '\n';
				dateleIntroduseSuntValide = false;
			}
		} while (!dateleIntroduseSuntValide);

		int an = 0;
		dateleIntroduseSuntValide = true;
		do
		{
			dateleIntroduseSuntValide = true;
			std::cout << ">> an: ";
			in >> an;
			try
			{
				data.setAn(an);
			}
			catch (const char* mesaj)
			{
				std::cout << "Eroare: " << mesaj << '\n';
				dateleIntroduseSuntValide = false;
			}
		} while (!dateleIntroduseSuntValide);

		return in;
	}

	friend ostream& operator<<(ostream& out, const Data& data)
	{
		out << "zi: " << data.zi << '\n';
		out << "luna: " << data.luna << '\n';
		out << "an: " << data.an;

		return out;
	}

	ofstream& output(ofstream& out)
	{
		out << zi << " " << luna << " " << an;
		return out;
	}

	ifstream& input(ifstream& in)
	{
		in >> zi >> luna >> an;
		return in;
	}

	bool operator<(const Data& data) const
	{
		return (this->an < data.an ||
			(this->an == data.an && (this->luna < data.luna || (this->luna == data.luna && this->zi < data.zi))));
	}
	
	bool operator>(const Data& data) const
	{
		return !this->operator<(data) && !this->operator==(data);
	}

	bool operator==(const Data& data) const
	{
		return (this->an == data.an && this->luna == data.luna && this->zi == data.zi);
	}

	bool operator !=(const Data& data) const
	{
		return !this->operator==(data);
	}
};

class Adresa : public FisierInOut
{
private:
	const int codPostal;
	char* judet;
	string oras;
	string locatie;

public:
	Adresa()
		: codPostal(0), judet(nullptr), oras("UNTITLED"), locatie("UNTITLED")
	{
	}

	Adresa(int codPostal) 
		: codPostal(codPostal), judet(nullptr), oras("UNTITLED"), locatie("UNTITLED")
	{
	}

	Adresa(int codPostal, const char* v_judet, string v_oras, string v_locatie)
		: codPostal(codPostal), judet(nullptr), oras(v_oras), locatie(v_locatie)
	{
		if (v_judet != nullptr)
		{
			this->judet = new char[strlen(v_judet) + 1];
			strcpy(this->judet, v_judet);
		}
		else this->judet = nullptr;
	}

	Adresa(const Adresa& adresa)
		: codPostal(adresa.codPostal), oras(adresa.oras), locatie(adresa.locatie)
	{
		if (adresa.judet != nullptr)
		{
			this->judet = new char[strlen(adresa.judet) + 1];
			strcpy(this->judet, adresa.judet);
		}
		else this->judet = nullptr;
	}

	~Adresa()
	{
		if (this->judet)
			delete[] this->judet;
	}

	Adresa& operator=(const Adresa& adresa)
	{
		if (this == &adresa)
			return *this;

		if (this->judet)
			delete[] this->judet;

		if (adresa.judet != nullptr)
		{
			this->judet = new char[strlen(adresa.judet) + 1];
			strcpy(this->judet, adresa.judet);
		}
		else this->judet = nullptr;

		this->oras = adresa.oras;
		this->locatie = adresa.locatie;

		return *this;
	}

	int getCodPostal() const
	{
		return this->codPostal;
	}

	const char* getJudet() const
	{
		return this->judet;
	}

	const string& getOras() const
	{
		return this->oras;
	}

	const string& getLocatie() const
	{
		return this->locatie;
	}

	void setJudet(const char* judetNou)
	{
		if (!judetNou)
			throw "Numele judetului nu poate fi nul!";

		if (this->judet)
			delete[] this->judet;

		this->judet = new char[strlen(judetNou) + 1];
		strcpy(this->judet, judetNou);
	}

	void setOras(string orasNou)
	{
		this->oras = orasNou;
	}

	void setLocatie(string locatieNoua)
	{
		this->locatie = locatieNoua;
	}

	friend istream& operator>>(istream& in, Adresa& adresa)
	{
		cout << ">> judet: ";
		string judetAux;
		getline(in, judetAux);
		adresa.judet = new char[judetAux.size() + 1];
		strcpy(adresa.judet, judetAux.c_str());

		cout << ">> oras: ";
		getline(in, adresa.oras);
		
		cout << ">> locatie: ";
		getline(in, adresa.locatie);

		return in;
	}

	friend ostream& operator<<(ostream& out, const Adresa& adresa)
	{
		if (adresa.judet)
			out << "judet: " << adresa.judet << " | ";
		out << "oras: " << adresa.oras << " | ";
		out << "locatie: " << adresa.locatie << " | ";

		return out;
	}

	ofstream& output(ofstream& out)
	{
		if (judet)
			out << judet;
		out << '\n';
		out << oras << '\n';
		out << locatie;
		return out;
	}

	ifstream& input(ifstream& in)
	{
		if (judet != NULL)
			delete[] judet;

		string judetAux;
		getline(in, judetAux);
		if (!judetAux.empty())
		{
			this->judet = new char[judetAux.size() + 1];
			strcpy(this->judet, judetAux.c_str());
		}
		else this->judet = NULL;

		getline(in, oras);
		getline(in, locatie);
		return in;
	}

	bool operator==(const Adresa& adresa) const
	{
		return (this->codPostal == adresa.codPostal && strcmp(this->judet, adresa.judet) == 0 &&
			this->oras == adresa.oras && this->locatie == locatie);
	}

	bool operator!=(const Adresa& adresa) const
	{
		return !this->operator==(adresa);
	}

	explicit operator int()
	{
		return this->codPostal;
	}
};

class Persoana : public FisierInOut
{
private:
	string nume;
	string prenume;
	char* telefon = nullptr;
	string email;
	Adresa adresa;

public:
	Persoana() : nume("UNKNOWN"), prenume("UNKNOWN"), telefon(nullptr), email("UNKNOWN"), adresa()
	{
	}

	Persoana(string v_nume, string v_prenume) 
		: nume(v_nume), prenume(v_prenume), telefon(nullptr), email("UNKNOWN"), adresa()
	{
	}

	Persoana(string v_nume, string v_prenume, const char* v_telefon, string v_email, const Adresa& v_adresa)
		: nume(v_nume), prenume(v_prenume), email(v_email), adresa(v_adresa)
	{
		this->setTelefon(v_telefon);
	}

	Persoana(const Persoana& persoana)
		: nume(persoana.nume), prenume(persoana.prenume), email(persoana.email), adresa(persoana.adresa)
	{
		if (persoana.telefon != nullptr)
		{
			this->telefon = new char[strlen(persoana.telefon) + 1];
			strcpy(this->telefon, persoana.telefon);
		}
		else this->telefon = nullptr;
	}

	virtual ~Persoana()
	{
		if (this->telefon)
			delete[] this->telefon;
	}

	Persoana& operator=(const Persoana& persoana)
	{
		if (this == &persoana)
			return *this;

		this->nume = persoana.nume;
		this->prenume = persoana.prenume;
	
		if (this->telefon)
			delete[] this->telefon;

		if (persoana.telefon != nullptr)
		{
			this->telefon = new char[strlen(persoana.telefon) + 1];
			strcpy(this->telefon, persoana.telefon);
		}
		else this->telefon = nullptr;

		this->email = persoana.email;
		this->adresa = persoana.adresa;

		return *this;
	}

	/// <summary>
	/// Referinta ca sa nu se copieze stringul
	/// Const ca sa nu poata fi modificat de afara
	/// </summary>
	const string& getNume() const
	{
		return this->nume;
	}

	const string& getPrenume() const
	{
		return this->prenume;
	}

	const char* getTelefon() const
	{
		return this->telefon;
	}

	const string& getEmail() const
	{
		return this->email;
	}

	const Adresa& getAdresa() const
	{
		return this->adresa;
	}

	void setNume(string numeNou)
	{
		this->nume = numeNou;
	}

	void setPrenume(string prenumeNou)
	{
		this->prenume = prenumeNou;
	}

	void setTelefon(const char* telefonNou)
	{
		if (!telefonNou)
			throw "Telefonul nu poate fi nul!";

		if (this->telefon)
			delete[] this->telefon;

		this->telefon = new char[strlen(telefonNou) + 1];
		strcpy(this->telefon, telefonNou);
	}

	void setEmail(string emailNou)
	{
		this->email = emailNou;
	}

	void setAdresa(const Adresa& adresaNoua)
	{
		this->adresa = adresaNoua;
	}

	friend istream& operator>>(istream& in, Persoana& persoana)
	{
		cout << ">> nume: ";
		getline(in, persoana.nume);

		cout << ">> prenume: ";
		getline(in, persoana.prenume);

		cout << ">> telefon: ";
		string telefonAux;
		getline(in, telefonAux);
		persoana.telefon = new char[telefonAux.size() + 1];
		strcpy(persoana.telefon, telefonAux.c_str());

		cout << ">> email: ";
		getline(in, persoana.email);

		cout << ">> adresa\n";
		in >> persoana.adresa;

		return in;
	}

	friend ostream& operator<<(ostream& out, const Persoana& persoana)
	{
		out << ">> nume: " << persoana.nume << '\n';
		out << ">> prenume: " << persoana.prenume << '\n';
		if (persoana.telefon)
			out << ">> telefon: " << persoana.telefon << '\n';
		out << ">> email: " << persoana.email << '\n';
		out << ">> adresa: " << persoana.adresa;

		return out;
	}

	ofstream& output(ofstream& out)
	{
		out << nume << '\n';
		out << prenume << '\n';
		if (telefon != nullptr)
			out << telefon;
		out << '\n';

		out << email << '\n';
		adresa.output(out);

		return out;
	}

	ifstream& input(ifstream& in)
	{
		if (telefon)
			delete[] telefon;

		getline(in, nume);
		getline(in, prenume);

		string telefonAux;
		getline(in, telefonAux);
		if (!telefonAux.empty())
		{
			this->telefon = new char[telefonAux.size() + 1];
			strcpy(this->telefon, telefonAux.c_str());
		}
		else this->telefon = nullptr;

		getline(in, email);
		adresa.input(in);

		return in;
	}

	bool operator==(const Persoana& persoana) const
	{
		return (this->nume == persoana.nume && this->prenume == persoana.prenume &&
			strcmp(this->telefon, persoana.telefon) == 0 && this->email == persoana.email && this->adresa == persoana.adresa);
	}

	bool operator!=(const Persoana& persoana) const
	{
		return !this->operator==(persoana);
	}

};

class Functie : public FisierInOut
{
private:
	char* denumire;
	float salariuMin;
	float salariuMax;

public:
	Functie() : denumire(nullptr), salariuMin(0), salariuMax(0)
	{
	}

	Functie(float v_salariuMin, float v_salariuMax)
		: denumire(nullptr)
	{
		this->setSalariuMax(v_salariuMax);
		this->setSalariuMin(v_salariuMin);
	}

	Functie(const char* v_denumire, float v_salariuMin, float v_salariuMax)
	{
		this->setSalariuMax(v_salariuMax);
		this->setSalariuMin(v_salariuMin);
		this->setDenumire(v_denumire);
	}

	Functie(const Functie& functie) 
		: salariuMin(functie.salariuMin), salariuMax(functie.salariuMax)
	{
		if (functie.denumire != nullptr)
		{
			this->denumire = new char[strlen(functie.denumire) + 1];
			strcpy(this->denumire, functie.denumire);
		}
		else this->denumire = nullptr;
	}

	Functie& operator=(const Functie& functie)
	{
		if (this == &functie)
			return *this;

		if (functie.denumire != nullptr)
		{
			this->denumire = new char[strlen(functie.denumire) + 1];
			strcpy(this->denumire, functie.denumire);
		}
		else this->denumire = nullptr;

		this->salariuMin = functie.salariuMin;
		this->salariuMax = functie.salariuMax;

		return *this;
	}

	~Functie()
	{
		if (this->denumire)
			delete[] this->denumire;
	}

	const char* getDenumire() const
	{
		return this->denumire;
	}

	float getSalariuMin() const
	{
		return this->salariuMin;
	}

	float getSalariuMax() const
	{
		return this->salariuMax;
	}

	void setDenumire(const char* denumireNoua)
	{
		if (!denumireNoua)
			throw "Denumirea nu poate fi nula!";

		if (this->denumire)
			delete[] this->denumire;

		this->denumire = new char[strlen(denumireNoua) + 1];
		strcpy(this->denumire, denumireNoua);
	}

	void setSalariuMin(float salariuMinNou)
	{
		if (salariuMinNou < 0)
			throw "Salariul nu poate fi negativ!";

		if (salariuMinNou > this->salariuMax)
			throw "Salariul minim nu poate fi mai mare decat salariul maxim!";

		this->salariuMin = salariuMinNou;
	}

	void setSalariuMax(float salariuMaxNou)
	{
		if (salariuMaxNou < 0)
			throw "Salariul nu poate fi negativ!";

		if (salariuMaxNou < this->salariuMin)
			throw "Salariul maxim nu poate fi mai mic decat salariul minim!";

		this->salariuMax = salariuMaxNou;
	}

	friend istream& operator>>(istream& in, Functie& functie)
	{
		cout << ">> denumire: ";
		string denumireAux;
		getline(in, denumireAux);
		functie.denumire = new char[denumireAux.size() + 1];
		strcpy(functie.denumire, denumireAux.c_str());

		float x = 0;
		bool ok = false;
		do
		{
			ok = true;
			cout << ">> salariul max: ";
			in >> x;

			try
			{
				functie.setSalariuMax(x);
			}
			catch (const char* mesaj)
			{
				cout << "Eroare: " << mesaj << '\n';
				ok = false;
			}

		} while (!ok);

		do
		{
			ok = true;
			cout << ">> salariul min: ";
			in >> x;

			try
			{
				functie.setSalariuMin(x);
			}
			catch (const char* mesaj)
			{
				cout << "Eroare: " << mesaj << '\n';
				ok = false;
			}

		} while (!ok);

		return in;
	}

	friend ostream& operator<<(ostream& out, const Functie& functie)
	{
		if (functie.denumire)
			out << ">> denumire functie: " << functie.denumire << '\n';
		out << ">> salariu min: " << functie.salariuMin << '\n';
		out << ">> salariu max: " << functie.salariuMax;

		return out;
	}

	ofstream& output(ofstream& out)
	{
		if (denumire != NULL)
			out << denumire;
		out << '\n';
		out << salariuMin << " " << salariuMax;
		return out;
	}

	ifstream& input(ifstream& in)
	{
		if (denumire != nullptr)
			delete[] denumire;

		string denumireAux;
		getline(in, denumireAux);

		if (denumireAux.empty())
			this->denumire = nullptr;
		else
		{
			this->denumire = new char[denumireAux.size() + 1];
			strcpy(this->denumire, denumireAux.c_str());
		}

		in >> salariuMin >> salariuMax;
		in.get();///citim sfarsitul de linie deoarece urmeaza sa citim un string (data urmatoare cand metoda este apelata)

		return in;
	}

	bool operator==(const Functie& functie) const
	{
		return (strcmp(this->denumire, functie.denumire) == 0 &&
			this->salariuMax == functie.salariuMax && this->salariuMin == functie.salariuMax);
	}

	bool operator!=(const Functie& functie) const
	{
		return !this->operator==(functie);
	}

	explicit operator const char* () const
	{
		return this->denumire;
	}
};

class Angajat : public Persoana //implicit clasa FisierInOut
{
private:
	Data dataAngajare;
	Data dataNastere;
	Functie functie;
	float salariu;
	string departament;

public:
	Angajat() 
		: Persoana(), dataAngajare(), dataNastere(), functie(), salariu(0), departament("") 
	{
	}

	Angajat(const Data& v_dataAngajare, const Data& v_dataNastere, const Persoana& v_persoana)
		: Persoana(v_persoana), dataAngajare(v_dataAngajare), dataNastere(v_dataNastere), functie(), salariu(0), departament("")
	{
		if (v_dataAngajare < v_dataNastere)
			throw "Datele sunt invalide!";
	}

	Angajat(const Data& v_dataAngajare, const Data& v_dataNastere, const Functie& v_functie, float v_salariu, 
		    string v_departament, const Persoana& v_persoana)
		: Persoana(v_persoana), dataAngajare(v_dataAngajare), dataNastere(v_dataNastere), functie(v_functie), departament(v_departament)
	{
		if (v_dataAngajare < v_dataNastere)
			throw "Datele sunt invalide!";

		this->setSalariul(v_salariu);
	}

	Angajat(const Angajat& angajat)
		: Persoana(angajat), dataAngajare(angajat.dataAngajare), dataNastere(angajat.dataNastere), functie(angajat.functie),
		  salariu(angajat.salariu), departament(angajat.departament)
	{
	}

	~Angajat()
	{
	}

	Angajat& operator=(const Angajat& angajat)
	{
		if (this == &angajat)
			return *this;

		Persoana::operator=(angajat);

		this->dataAngajare = angajat.dataAngajare;
		this->dataNastere = angajat.dataNastere;
		this->functie = angajat.functie;
		this->salariu = angajat.salariu;
		this->departament = angajat.departament;

		return *this;
	}

	float getSalariu() const
	{
		return this->salariu;
	}

	const Data& getDataAngajare() const
	{
		return this->dataAngajare;
	}

	const Data& getDataNastere() const
	{
		return this->dataNastere;
	}

	const Functie& getFunctie() const
	{
		return this->functie;
	}

	const string& getDepartament() const
	{
		return this->departament;
	}

	void setSalariul(float salariuNou)
	{
		if (salariuNou < this->functie.getSalariuMin() || salariuNou > this->functie.getSalariuMax())
			throw "Salariul nu se afla in limitele functiei!";

		this->salariu = salariuNou;
	}

	void setFunctie(const Functie& functieNoua)
	{
		this->functie = functieNoua;
	}

	void setDepartament(string departamentNou)
	{
		this->departament = departamentNou;
	}

	friend istream& operator>>(istream& in, Angajat& angajat)
	{
		cout << ">> date personale\n";
		in >> (Persoana&)(angajat);

		cout << ">> date angajat\n";
		cout << ">> data nastere\n";
		in >> angajat.dataNastere;

		cout << ">> data angajare\n";
		in >> angajat.dataAngajare;
		in.get();

		cout << ">> functie\n";
		in >> angajat.functie;

		bool ok = true;
		float salariu = 0;
		do
		{
			ok = true;
			cout << ">> salariu: ";
			in >> salariu;

			try
			{
				angajat.setSalariul(salariu);
			}
			catch (const char* mesaj)
			{
				cout << "Eroare: " << mesaj << '\n';
				ok = false;
			}

		} while (!ok);

		cin.get();
		cout << ">> departament: ";
		getline(in, angajat.departament);

		return in;
	}

	friend ostream& operator<<(ostream& out, const Angajat& angajat)
	{
		out << (const Persoana&)angajat << '\n';

		out << ">> data nastere: " << angajat.dataNastere << '\n';
		out << ">> data angajare: " << angajat.dataAngajare << '\n';
		out << ">> functie: " << angajat.functie << '\n';
		out << ">> salariu: " << angajat.salariu << '\n';
		out << ">> departament: " << angajat.departament << '\n';

		return out;
	}

	ofstream& output(ofstream& out)
	{
		Persoana::output(out) << '\n';

		this->dataAngajare.output(out) << '\n';
		this->dataNastere.output(out) << '\n';
		this->functie.output(out) << '\n';
		out << this->salariu << '\n';
		out << this->departament;
		return out;
	}

	ifstream& input(ifstream& in)
	{
		Persoana::input(in);

		this->dataAngajare.input(in);
		this->dataNastere.input(in);
		in.get();
		this->functie.input(in);
		in >> this->salariu;
		in.get();
		getline(in, this->departament);

		return in;
	}

	bool operator==(const Angajat& angajat) const
	{
		const Persoana& persoana = angajat;
		const Persoana* _this = this;

		return (persoana == *_this && this->functie == angajat.functie && this->dataAngajare == angajat.dataAngajare
			&& this->dataNastere == angajat.dataNastere && this->salariu == angajat.salariu && this->departament == angajat.departament);
	}

	bool operator!=(const Angajat& angajat) const
	{
		return !this->operator==(angajat);
	}

	explicit operator float() const
	{
		return this->salariu;
	}

};

class Colet : public FisierInOut
{
private:
	char* awb = nullptr;
	Persoana client;
	Angajat curier;
	Persoana persoanaContact;
	Adresa adresaLivrare;
	Data dataPlasare;
	Data dataLivrare;
	float valoare;
	float greutate;

public:
	Colet() 
		: awb(nullptr), client(), curier(), persoanaContact(), adresaLivrare(), dataPlasare(), dataLivrare(), valoare(0), greutate(0)
	{
	}

	Colet(const char* AWB, float valoare, float greutate)
		: client(), curier(), persoanaContact(), adresaLivrare(), dataPlasare(), dataLivrare(), valoare(0), greutate(0)
	{
		this->setAWB(AWB);
		this->setValoare(valoare);
		this->setGreutate(greutate);
	}

	Colet(const char* v_awb, const Persoana& v_client, const Angajat& v_curier, const Persoana& v_persoanaContact,
		  const Adresa& v_adresaLivrare, const Data& v_DataLivrare, const Data& v_DataPlasare, float v_valoare, float v_greutate)
		: client(v_client), curier(v_curier), persoanaContact(v_persoanaContact), adresaLivrare(v_adresaLivrare),
		dataLivrare(v_DataLivrare), dataPlasare(v_DataPlasare)
	{
		this->setAWB(v_awb);
		this->setValoare(v_valoare);
		this->setGreutate(v_greutate);
	}

	Colet(const Colet& colet)
		: client(colet.client), curier(colet.curier), persoanaContact(colet.persoanaContact), adresaLivrare(colet.adresaLivrare),
		dataLivrare(colet.dataLivrare), dataPlasare(colet.dataPlasare), valoare(colet.valoare), greutate(colet.greutate)
	{
		if (colet.awb != nullptr)
		{
			this->awb = new char[strlen(colet.awb) + 1];
			strcpy(this->awb, colet.awb);
		}
		else this->awb = nullptr;
	}

	Colet& operator=(const Colet& colet)
	{
		if (this == &colet)
			return *this;

		if (this->awb != nullptr)
			delete[] this->awb;

		if (colet.awb != nullptr)
		{
			this->awb = new char[strlen(colet.awb) + 1];
			strcpy(this->awb, colet.awb);
		}
		else this->awb = nullptr;

		this->client = colet.client;
		this->curier = colet.curier;
		this->persoanaContact = colet.persoanaContact;
		this->adresaLivrare = colet.adresaLivrare;
		this->dataPlasare = colet.dataPlasare;
		this->dataLivrare = colet.dataLivrare;
		this->valoare = colet.valoare;
		this->greutate = colet.greutate;

		return *this;
	}

	~Colet()
	{
		if (this->awb)
			delete[] this->awb;
	}

	const char* getAWB() const
	{
		return this->awb;
	}

	const Persoana& getClient() const
	{
		return this->client;
	}

	const Angajat& getCurier() const
	{
		return this->curier;
	}

	const Persoana& getPersoanaContact() const
	{
		return this->persoanaContact;
	}

	const Adresa& getAdresaLivrare() const
	{
		return this->adresaLivrare;
	}

	const Data& getDataPlasare() const
	{
		return this->dataPlasare;
	}

	const Data& getDataLivrare() const
	{
		return this->dataLivrare;
	}

	float getValoare() const
	{
		return this->valoare;
	}

	float getGreutate() const
	{
		return this->greutate;
	}

	void setAWB(const char* awbNou)
	{
		if (!awbNou)
			throw "AWB-ul nu poate fi nul!";

		if (this->awb)
			delete[] this->awb;

		this->awb = new char[strlen(awbNou) + 1];
		strcpy(this->awb, awbNou);
	}

	void setClient(const Persoana& clientNou)
	{
		this->client = clientNou;
	}

	void setCurier(const Angajat& curierNou)
	{
		this->curier = curierNou;
	}

	void setPersoanaContact(const Persoana& persoanaContactNoua)
	{
		this->persoanaContact = persoanaContactNoua;
	}

	void setAdresaLivrare(const Adresa& adresaLivrareNoua)
	{
		this->adresaLivrare = adresaLivrareNoua;
	}

	void setDataPlasare(const Data& dataPlasareNoua)
	{
		if (dataPlasareNoua > this->dataLivrare)
			throw "Data plasarii nu poate fi mai mare decat data livrarii!";

		this->dataPlasare = dataPlasareNoua;
	}

	void setDataLivrare(const Data& dataLivrareNoua)
	{
		if (dataLivrareNoua < this->dataPlasare)
			throw "Data livrarii nu poate fi mai mica decat data plasarii!";

		this->dataLivrare = dataLivrareNoua;
	}

	void setValoare(float valoareNoua)
	{
		if (valoareNoua < 0)
			throw "Valoarea nu poate fi negativa!";

		this->valoare = valoareNoua;
	}

	void setGreutate(float greutateNoua)
	{
		if (greutateNoua < 0)
			throw "Greutatea nu poate fi negativa!";

		this->greutate = greutateNoua;
	}

	friend istream& operator>>(istream& in, Colet& colet)
	{
		cout << ">> AWB: ";
		string awbAux;
		getline(in, awbAux);
		colet.awb = new char[awbAux.size() + 1];
		strcpy(colet.awb, awbAux.c_str());
		cout << "___________________________________\n";

		cout << ">> client:\n";
		in >> colet.client;
		cout << "___________________________________\n";

		cout << ">> curier:\n";
		in >> colet.curier;
		cout << "___________________________________\n";

		cout << ">> persoana contact:\n";
		in >> colet.persoanaContact;
		cout << "___________________________________\n";

		cout << ">> Adresa livrare:\n";
		in >> colet.adresaLivrare;
		cout << "___________________________________\n";

		cout << ">> Data plasare:\n";
		in >> colet.dataPlasare;
		cout << "___________________________________\n";

		cout << ">> Data livrare:\n";
		in >> colet.dataLivrare;
		cout << "___________________________________\n";

		float x = 0;
		bool ok = false;
		do
		{
			ok = true;
			cout << ">> Valoare: ";
			in >> x;

			try
			{
				colet.setValoare(x);
			}
			catch (const char* mesaj)
			{
				cout << "Eroare: " << mesaj << '\n';
				ok = false;
			}

		} while (!ok);

		do
		{
			ok = true;
			cout << ">> Greutate: ";
			in >> x;

			try
			{
				colet.setGreutate(x);
			}
			catch (const char* mesaj)
			{
				cout << "Eroare: " << mesaj << '\n';
				ok = false;
			}

		} while (!ok);

		return in;
	}

	friend ostream& operator<<(ostream& out, const Colet& colet)
	{
		if (colet.awb)
			out << ">> AWB: " << colet.awb << '\n';
		out << "___________________________________\n";
		out << ">> client:\n" << colet.client << '\n';
		out << "___________________________________\n";
		out << ">> curier:\n" << colet.curier << '\n';
		out << "___________________________________\n";
		out << ">> persoana contact:\n" << colet.persoanaContact << '\n';
		out << "___________________________________\n";
		out << ">> adresa livrare:\n" << colet.adresaLivrare << '\n';
		out << "___________________________________\n";
		out << ">> data plasare\n" << colet.dataPlasare << '\n';
		out << "___________________________________\n";
		out << ">> data livrare\n" << colet.dataLivrare << '\n';
		out << "___________________________________\n";
		out << ">> valoare: " << colet.valoare << '\n';
		out << ">> greutate: " << colet.greutate;

		return out;
	}

	ofstream& output(ofstream& out)
	{
		if (this->awb)
			out << this->awb;
		out << '\n';

		this->client.output(out) << '\n';
		this->curier.output(out) << '\n';
		this->persoanaContact.output(out) << '\n';
		this->adresaLivrare.output(out) << '\n';
		this->dataPlasare.output(out) << '\n';
		this->dataLivrare.output(out) << '\n';
		out << this->valoare << '\n';
		out << this->greutate;

		return out;
	}

	ifstream& input(ifstream& in)
	{
		string awbAux;
		getline(in, awbAux);
		if (awbAux.empty())
			this->awb = nullptr;
		else
		{
			this->awb = new char[awbAux.size() + 1];
			strcpy(this->awb, awbAux.c_str());
		}

		this->client.input(in);
		this->curier.input(in);
		this->persoanaContact.input(in);
		this->adresaLivrare.input(in);
		this->dataLivrare.input(in);
		this->dataLivrare.input(in);
		in >> this->valoare;
		in >> this->greutate;
		in.get();

		return in;
	}

	bool operator==(const Colet& colet) const
	{
		return (strcmp(this->awb, colet.awb) == 0 &&
			this->client == colet.client &&
			this->curier == colet.curier &&
			this->persoanaContact == colet.persoanaContact &&
			this->adresaLivrare == colet.adresaLivrare &&
			this->dataPlasare == colet.dataPlasare &&
			this->dataLivrare == colet.dataLivrare &&
			this->valoare == colet.valoare &&
			this->greutate == colet.greutate);
	}

	bool operator!=(const Colet& colet) const
	{
		return !this->operator==(colet);
	}

	explicit operator float() const
	{
		return this->valoare;
	}

	explicit operator const char* () const
	{
		return this->awb;
	}
};

template<class Obj>
void test()
{
	Obj obj1{};
	cin >> obj1;

	Obj obj2(obj1);

	Obj obj3;
	obj3 = obj2;

	cout << obj1 << '\n' << obj2 << '\n' << obj3 << '\n';

	cout << "--------------\n";

	std::ofstream outputFile("data.txt", ios::out);
	obj1.output(outputFile) << '\n';
	obj2.output(outputFile) << '\n';
	obj3.output(outputFile) << '\n';
	outputFile.close();

	std::ifstream inputFile("data.txt", ios::in);
	Obj obj4{};
	Obj obj5{};
	Obj obj6{};

	obj4.input(inputFile);
	obj5.input(inputFile);
	obj6.input(inputFile);


	cout << obj4 << '\n' << obj5 << '\n' << obj6 << '\n';

	inputFile.close();
}

template<class T>
class Registru
{
private:
	T** inregistrari;
	int numarInregistrari;

public:
	Registru() : inregistrari(nullptr), numarInregistrari(0)
	{
	}

	void stergeInregistrari()
	{
		if (this->inregistrari)
		{
			for (int i = 0; i < this->numarInregistrari; ++i)
				if (this->inregistrari[i])
					delete this->inregistrari[i];
			delete[] this->inregistrari;
		}
	}

	Registru(const Registru& r)
	{
		this->numarInregistrari = r.numarInregistrari;
		if (r.inregistrari != NULL)
		{
			this->inregistrari = new T * [r.numarInregistrari];
			for (int i = 0; i < r.numarInregistrari; ++i)
				this->inregistrari[i] = new T(*r.inregistrari[i]);
		}
		else this->inregistrari = NULL;
	}

	~Registru()
	{
		stergeInregistrari();
	}

	void output(string numeFisier)
	{
		ofstream fisier;
		fisier.open(numeFisier, ios::out);

		fisier << this->numarInregistrari << '\n';

		for (int i = 0; i < this->numarInregistrari; ++i)
			this->inregistrari[i]->output(fisier) << '\n';

		fisier.close();
	}

	void input(string numeFisier)
	{
		ifstream fisier;
		fisier.open(numeFisier, ios::in);

		fisier >> this->numarInregistrari;
		fisier.get();

		this->inregistrari = new T * [this->numarInregistrari];
		for (int i = 0; i < this->numarInregistrari; ++i)
		{
			this->inregistrari[i] = new T();
			this->inregistrari[i]->input(fisier);
		}

		fisier.close();
	}

	void afiseaza(ostream& out)
	{
		for (int i = 0; i < this->numarInregistrari; ++i)
		{
			out << "_______________________[ " << i + 1 << " ]_______________________\n";
			out << *this->inregistrari[i] << '\n';
		}
	}

	Registru& operator=(const Registru& r)
	{
		if (this == &r)
			return *this;

		if (this->inregistrari != NULL)
			delete[] this->inregistrari;

		this->numarInregistrari = r.numarInregistrari;

		if (r.inregistrari != NULL)
		{
			this->inregistrari = new T * [r.numarInregistrari];
			for (int i = 0; i < r.numarInregistrari; ++i)
				this->inregistrari[i] = new T(*r.inregistrari[i]);
		}
		else this->inregistrari = NULL;

		return *this;
	}

	void adaugaInregistrare(const T& inregistrare)
	{
		T** inregistrariNoi = new T * [this->numarInregistrari + 1];
		for (int i = 0; i < this->numarInregistrari; ++i)
			inregistrariNoi[i] = this->inregistrari[i];

		inregistrariNoi[this->numarInregistrari] = new T(inregistrare);
		this->numarInregistrari++;

		if (this->inregistrari)
			delete[] this->inregistrari;

		this->inregistrari = inregistrariNoi;
	}

	int getNumarInregistrari() const
	{
		return this->numarInregistrari;
	}

	T& operator[](int index)
	{
		if (index >= 0 && index < this->numarInregistrari)
			return *(this->inregistrari[index]);

		throw "Index invalid";
	}

};

template<class Obj>
void testRegistru()
{
	Registru<Obj> r1;

	Obj obj{};
	r1.adaugaInregistrare(obj);
	r1.adaugaInregistrare(obj);
	r1.adaugaInregistrare(obj);
	r1.output("data.txt");

	Registru<Obj> r2;
	r2.input("data.txt");

	for (int i = 0; i < r2.getNumarInregistrari(); ++i)
		cout << *r2[i] << '\n';
}

class ManagerRegistrii
{
private:
	Registru<Functie> functii;
	Registru<Angajat> angajati;
	Registru<Colet> colete;

public:
	ManagerRegistrii()
		: functii(), angajati(), colete()
	{

	}

	ManagerRegistrii(const ManagerRegistrii& m)
		: functii(m.functii), angajati(m.angajati), colete(m.colete)
	{
	}

	ManagerRegistrii& operator=(const ManagerRegistrii& m)
	{
		if (this == &m)
			return *this;

		this->functii = m.functii;
		this->angajati = m.angajati;
		this->colete = m.colete;

		return *this;
	}

	~ManagerRegistrii()
	{
	}

	Registru<Functie>& getFunctii()
	{
		return this->functii;
	}

	Registru<Angajat>& getAngajati()
	{
		return this->angajati;
	}

	Registru<Colet>& getColete()
	{
		return this->colete;
	}

	void salveazaDatele()
	{
		this->functii.output("functii.txt");
		this->angajati.output("angajati.txt");
		this->colete.output("colete.txt");
	}

	void incarcaDatele()
	{
		this->functii.input("functii.txt");
		this->angajati.input("angajati.txt");
		this->colete.input("colete.txt");
	}

};

class Meniu
{
private:
	bool eDeschis;

private:
	virtual void afiseaza() = 0;
	virtual void executa(ManagerRegistrii& managerRegistrii) = 0;

public:
	Meniu()
		: eDeschis(true)
	{
	}

	bool esteDeschis()
	{
		return this->eDeschis;
	}

	void inchide()
	{
		this->eDeschis = false;
	}

	void start(ManagerRegistrii& managerRegistrii)
	{
		afiseaza();
		while (esteDeschis())
		{
			executa(managerRegistrii);
		}
	}
};

class MeniuAdaugare : public Meniu
{
	void afiseaza()
	{
		cout << "______________________________________________________\n";
		cout<< "~~~~~~~~~~~~~~~~~~~ Meniu Adaugare ~~~~~~~~~~~~~~~~~~~\n";
		cout << "1: afiseaza meniu\n";
		cout << "2: functie\n";
		cout << "3: angajat\n";
		cout << "4: colet\n";
		cout << "5: inapoi la meniul principal\n";
	}

	void executa(ManagerRegistrii& managerRegistrii)
	{
		short optiune;
		cout << "Alegeti optiunea: ";

		cin >> optiune;

		switch (optiune)
		{
			case 1:
			{
				afiseaza();
				break;
			}
			case 2:
			{
				Functie f;
				cout << "Introduceti datele functiei\n";
				cin.get();
				cin >> f;
				managerRegistrii.getFunctii().adaugaInregistrare(f);
				cout << "Functie adaugata.\n";
				break;
			}
			case 3:
			{
				Angajat a;
				cout << "Introduceti datele angajatului\n";
				cin.get();
				cin >> a;
				managerRegistrii.getAngajati().adaugaInregistrare(a);
				cout << "Angajat adaugat.\n";
				break;
			}
			case 4:
			{
				Colet c;
				cout << "Introduceti datele coletului\n";
				cin.get();
				cin >> c;
				managerRegistrii.getColete().adaugaInregistrare(c);
				cout << "Colet adaugat.\n";
				break;
			}
			case 5:
			{
				inchide();
				break;
			}
			default:
			{
				cout << ">> Optiune invalida!\n";
				break;
			}
		}
	}
};

class MeniuAfisareDate : public Meniu
{
	void afiseaza()
	{
		cout << "______________________________________________________\n";
		cout << "~~~~~~~~~~~~~~~~~~~ Meniu Afisare Date ~~~~~~~~~~~~~~~~~~~\n";
		cout << "1: afiseaza meniu\n";
		cout << "2: functie\n";
		cout << "3: angajat\n";
		cout << "4: colet\n";
		cout << "5: inapoi la meniul principal\n";
	}

	void executa(ManagerRegistrii& managerRegistrii)
	{
		short optiune;
		cout << "Alegeti optiunea: ";

		cin >> optiune;

		switch (optiune)
		{
		case 1:
		{
			afiseaza();
			break;
		}
		case 2:
		{
			managerRegistrii.getFunctii().afiseaza(cout);
			break;
		}
		case 3:
		{
			managerRegistrii.getAngajati().afiseaza(cout);
			break;
		}
		case 4:
		{
			managerRegistrii.getColete().afiseaza(cout);
			break;
		}
		case 5:
		{
			inchide();
			break;
		}
		default:
		{
			cout << ">> Optiune invalida!\n";
			break;
		}
		}
	}
};

class MeniuRapoarte : public Meniu
{
	void afiseaza()
	{
		cout << "______________________________________________________\n";
		cout << "~~~~~~~~~~~~~~~~~~~ Meniu Rapoarte ~~~~~~~~~~~~~~~~~~~\n";
		cout << "1: afiseaza meniu\n";
		cout << "2: functie\n";
		cout << "3: angajat\n";
		cout << "4: colet\n";
		cout << "5: inapoi la meniul principal\n";
	}

	void executa(ManagerRegistrii& managerRegistrii)
	{
		short optiune;
		cout << "Alegeti optiunea: ";

		cin >> optiune;

		switch (optiune)
		{
			case 1:
			{
				afiseaza();
				break;
			}
			case 2:
			{
				std::ofstream g("raport_functii.txt");
				managerRegistrii.getFunctii().afiseaza(g);
				g.close();
				break;
			}
			case 3:
			{
				std::ofstream g("raport_angajati.txt");
				managerRegistrii.getAngajati().afiseaza(g);
				g.close();
				break;
			}
			case 4:
			{
				std::ofstream g("raport_colete.txt");
				managerRegistrii.getColete().afiseaza(g);
				g.close();
				break;
			}
			case 5:
			{
				inchide();
				break;
			}
			default:
			{
				cout << ">> Optiune invalida!\n";
				break;
			}
		}
	}
};

class MeniuActualizare : public Meniu
{
	void afiseaza()
	{
		cout << "_________________________________________________________\n";
		cout << "~~~~~~~~~~~~~~~~~~~ Meniu Actualizare ~~~~~~~~~~~~~~~~~~~\n";
		cout << "1: afiseaza meniu\n";
		cout << "2: functie\n";
		cout << "3: angajat\n";
		cout << "4: colet\n";
		cout << "5: inapoi la meniul principal\n";
	}

	void executa(ManagerRegistrii& managerRegistrii)
	{
		short optiune;
		cout << "Alegeti optiunea: ";

		cin >> optiune;

		switch (optiune)
		{
			case 1:
			{
				afiseaza();
				break;
			}
			case 2:
			{
				cout << "Introduceti denumirea functiei pe care doriti sa o actualizati: ";
				string denumireFunctie;
				cin.get();
				getline(cin, denumireFunctie);

				Registru<Functie>& registru = managerRegistrii.getFunctii();

				bool gasita = false;
				for (int i = 0; i < registru.getNumarInregistrari(); ++i)
					if (registru[i].getDenumire() == denumireFunctie)
					{
						cout << "________ Date curente ________\n";
						cout << registru[i] << '\n';
						cout << "________ Actualizare ________\n";
						cin >> registru[i];
						cout << "Actualizare realizata!\n";
						gasita = true;
						break;
					}
				if (!gasita)
					cout << "Functia nu exista\n";
				break;
			}
			case 3:
			{
				cout << "Introduceti numele angajatului pe care doriti sa il actualizati: ";
				string numeAngajat;
				cin.get();
				getline(cin, numeAngajat);

				Registru<Angajat>& registru = managerRegistrii.getAngajati();

				bool gasita = false;
				for (int i = 0; i < registru.getNumarInregistrari(); ++i)
					if (registru[i].getNume() == numeAngajat)
					{
						cout << "________ Date curente ________\n";
						cout << registru[i] << '\n';
						cout << "________ Actualizare ________\n";
						cin >> registru[i];
						cout << "Actualizare realizata!\n";
						gasita = true;
						break;
					}
				if (!gasita)
					cout << "Angajatul nu exista\n";
				break;
			}
			case 4:
			{
				cout << "Introduceti AWB-ul coletului pe care doriti sa il actualizati: ";
				string awbColet;
				cin.get();
				getline(cin, awbColet);

				Registru<Colet>& registru = managerRegistrii.getColete();

				bool gasita = false;
				for (int i = 0; i < registru.getNumarInregistrari(); ++i)
					if (registru[i].getAWB() == awbColet)
					{
						cout << "________ Date curente ________\n";
						cout << registru[i] << '\n';
						cout << "________ Actualizare ________\n";
						cin >> registru[i];
						cout << "Actualizare realizata!\n";
						gasita = true;
						break;
					}
				if (!gasita)
					cout << "Coletul nu exista\n";
				break;
			}
			case 5:
			{
				inchide();
				break;
			}
			default:
			{
				cout << ">> Optiune invalida!\n";
				break;
			}
		}
	}
};

class MeniuPrincipal : public Meniu
{
private:
	ManagerRegistrii managerRegistrii;

public:
	MeniuPrincipal()
	{
		this->managerRegistrii.incarcaDatele();
	}

	~MeniuPrincipal()
	{
		this->managerRegistrii.salveazaDatele();
	}

private:
	void afiseaza()
	{
		cout << "_______________________________________________________\n";
		cout << "~~~~~~~~~~~~~~~~~~~ Meniu Principal ~~~~~~~~~~~~~~~~~~~\n";
		cout << "1: afisare meniu\n";
		cout << "2: salvare date\n";
		cout << "3: adaugare date\n";
		cout << "4: afisare date\n";
		cout << "5: generare rapoarte\n";
		cout << "6: actualizare date\n";
		cout << "7: exit\n";
	}

	void executa(ManagerRegistrii& managerRegistrii)
	{
		short optiune;
		cout << "Alegeti optiunea: ";

		cin >> optiune;
		
		switch (optiune)
		{
			case 1:
			{
				afiseaza();
				break;
			}
			case 2:
			{
				cout << "Se salveaza datele...\n";
				this->managerRegistrii.salveazaDatele();
				cout << "Datele au fost salvate!\n";
				break;
			}
			case 3:
			{
				MeniuAdaugare m;
				m.start(this->managerRegistrii);
				afiseaza();
				break;
			}
			case 4:
			{
				MeniuAfisareDate m;
				m.start(this->managerRegistrii);
				afiseaza();
				break;
			}
			case 5:
			{
				MeniuRapoarte m;
				m.start(this->managerRegistrii);
				afiseaza();
				break;
			}
			case 6:
			{
				MeniuActualizare m;
				m.start(this->managerRegistrii);
				afiseaza();
				break;
			}
			case 7:
			{
				inchide();
				break;
			}
			default:
			{
				cout << ">> Optiune invalida!\n";
				break;
			}
		}
		
	}

public:
	void go()
	{
		start(managerRegistrii);
	}
};

int main()
{
	MeniuPrincipal m;
	m.go();


	return 0;
}