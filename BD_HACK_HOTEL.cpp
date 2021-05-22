#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

#define INPUT_FOLDER "Data\\"
#define OUTPUT_FOLDER "SQL\\"

std::string genereazaCodPostal()
{
	std::string cod = "";
	for (int i = 0; i < 20; ++i)
		cod.push_back('0' + (rand() % ('9' - '0' + 1)));
	return cod;
}

void genereazaHoteluri()
{
	std::ifstream f(INPUT_FOLDER "tabela hoteluri.txt");
	std::ofstream g(OUTPUT_FOLDER "Hoteluri.sql");

	std::vector<std::string> tari{
		"AR", "AU", "BE", "BR", "CA", "CH", "CN",
		"DE", "DK", "EG", "FR", "HK", "IL", "IN", "IT",
		"JP", "KW", "MX", "NG"
		, "NL", "SG", "UK", "US", "ZM", "ZW" };

	int id = 0;
	std::string adresa = "";
	std::string oras = "";

	do
	{
		id++;
		std::getline(f, oras);
		std::getline(f, adresa);

		g << "INSERT INTO HOTELURI VALUES ("
			<< id << ", '"
			<< adresa << "', '"
			<< genereazaCodPostal() << "', '"
			<< oras << "', '"
			<< tari[rand() % tari.size()] << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaClienti()
{
	std::ifstream f(INPUT_FOLDER "tabela clienti.txt");
	std::ofstream g(OUTPUT_FOLDER "Clienti.sql");

	int id = 0;
	std::string nume = "";
	std::string prenume = "";
	std::string telefon = "";
	std::string email = "";
	std::string sex = "";

	do
	{
		id++;
		f >> nume >> prenume >> telefon >> email >> sex;

		int ziNastere = rand() % 28 + 1;
		int lunaNastere = rand() % 12 + 1;
		int anNastere = 1975 + (rand() % (2001 - 1975 + 1));

		std::cout << nume << " " << prenume << " " << telefon << " " << email << " " << sex << '\n';

		g << "INSERT INTO CLIENTI VALUES ("
			<< id << ", '"
			<< nume << "', '"
			<< prenume << "', '"
			<< telefon << "', '"
			<< email << "', "
			<< "to_date('" << (ziNastere) << "-" << (lunaNastere) << "-" << anNastere << "', 'dd-mm-yyyy'), '"
			<< (char)toupper(sex.front()) << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaAngajati()
{
	std::ifstream f(INPUT_FOLDER "tabela angajati.txt");
	std::ofstream g(OUTPUT_FOLDER "Angajati.sql");

	int id = 0;
	std::string nume = "";
	std::string prenume = "";
	std::string email = "";
	std::string telefon = "";
	
	do
	{
		id++;
		f >> prenume >> nume >> email >> telefon;

		int ziAngajare = rand() % 28 + 1;
		int lunaAngajare = rand() % 12 + 1;
		int anAngajare = 1975 + (rand() % (2001 - 1975 + 1));

		g << "INSERT INTO ANGAJATI VALUES ("
			<< id << ", '"
			<< nume << "', '"
			<< prenume << "', '"
			<< email << "', '"
			<< telefon << "', "
			<< "to_date('" << (ziAngajare) << "-" << (lunaAngajare) << "-" << anAngajare << "', 'dd-mm-yyyy'), "
			<< 2500 + (rand() % (12000 - 2500 + 1)) << ");\n";

	} while (!f.eof());

	f.close();
	g.close();
}

std::string getModalitatePlata()
{
	return (rand() % 2 == 0 ? "cash" : "card");
}

int getNumarZileCazare()
{
	return 1 + rand() % 14;
}

struct Data
{
	int zi = 0;
	int luna = 0;
	int an = 0;

	Data()
	{
		zi = rand() % 28 + 1;
		luna = rand() % 12 + 1;
		an = 2000 + (rand() % (2018 - 2000 + 1));
	}

	bool operator<(const Data& other)
	{
		return (an < other.an || (an == other.an && (luna < other.luna || (luna == other.luna && zi < other.zi))));
	}

	friend std::ostream& operator<<(std::ostream& out, const Data& data)
	{
		out << "to_date('" << data.zi << "-" << data.luna << "-" << data.an << "', 'dd-mm-yyyy')";
		return out;
	}

	void setNext()
	{
		int chance = rand() % 100 + 1;

		if (chance < 30)
		{
			zi = zi + rand() % 3;
			luna = luna + rand() % 3;
			an = an + rand() % 1;

			if (zi > 30)
			{
				zi -= 30;
				luna++;
			}

			if (luna > 12)
			{
				luna -= 12;
				an++;
			}
		}
		else if (chance < 50)
		{
			luna = luna + 3;
			if (luna > 12)
			{
				luna -= 12;
				an++;
			}
		}
		else
		{
			an++;
		}
	}
};

void genereazaRestu()
{
	const int NUMAR_HOTELURI = 20;
	const int NUMAR_CLIENTI = 20;
	const int NUMAR_ANGAJATI = 20;

	const int NUMAR_DATE_CAZARE = 60;
	const int NUMAR_REZERVARI = 50;
	const int NUMAR_CAZARI_CU_REZERVARE = 40;
	const int NUMAR_CAZARI_FARA_REZERVARE = 10; 
	const int ID_FARA_CAZARE = 50;

	std::ofstream dateCazari(OUTPUT_FOLDER "DateCazari.sql");
	std::ofstream camereRezervate(OUTPUT_FOLDER "CamereRezervate.sql");
	std::ofstream rezervari(OUTPUT_FOLDER "Rezervari.sql");
	std::ofstream cazari(OUTPUT_FOLDER "Cazari.sql");

	for (int idDateCazare = 1; idDateCazare <= NUMAR_DATE_CAZARE; ++idDateCazare)
	{
		dateCazari << "INSERT INTO DATE_CAZARI VALUES ("
			<< idDateCazare << ", '"
			<< getModalitatePlata() << "', "
			<< rand() % NUMAR_HOTELURI + 1 << ", "
			<< getNumarZileCazare() << ", "
			<< rand() % NUMAR_CLIENTI + 1 << ");\n";
	}

	int numarCameraRezervata = 58;
	for (int idDateCazare = 1; idDateCazare <= NUMAR_DATE_CAZARE; ++idDateCazare)
	{
		int nrCamere = rand() % 4 + 1;
		for (int i = 0; i < nrCamere; ++i)
		{
			camereRezervate << "INSERT INTO CAMERE_REZERVATE VALUES ("
				<< idDateCazare << ", " << numarCameraRezervata << ");\n";
			numarCameraRezervata++;
		}
	}

	std::vector<Data> dateRezervari;

	int idDateCazare = 0;
	for (int idRezervare = 1; idRezervare <= NUMAR_REZERVARI; ++idRezervare)
	{
		idDateCazare++;

		dateRezervari.emplace_back();

		rezervari << "INSERT INTO REZERVARI VALUES ("
			<< idRezervare << ", "
			<< idDateCazare << ", "
			<< dateRezervari.back() << ");\n";
	}

	idDateCazare = 0;
	for (int idCazare = 1; idCazare <= NUMAR_CAZARI_CU_REZERVARE; ++idCazare)
	{
		dateRezervari[idCazare].setNext();
		idDateCazare++;
		cazari << "INSERT INTO CAZARI VALUES ("
			<< idCazare << ", " << idDateCazare << ", " << dateRezervari[idCazare] << ", " << rand() % NUMAR_ANGAJATI + 1 << ");\n";
	}

	idDateCazare = ID_FARA_CAZARE;
	for (int idCazare = NUMAR_CAZARI_CU_REZERVARE + 1; idCazare <= NUMAR_CAZARI_CU_REZERVARE + NUMAR_CAZARI_FARA_REZERVARE; ++idCazare)
	{
		idDateCazare++;
		Data data;
		cazari << "INSERT INTO CAZARI VALUES ("
			<< idCazare << ", " << idDateCazare << ", " << data << ", " << rand() % NUMAR_ANGAJATI + 1 << ");\n";
	}

	dateCazari.close();
	camereRezervate.close();
	rezervari.close();
	cazari.close();
}


int main()
{
	genereazaRestu();


	return 0;
}