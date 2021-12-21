#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

#define INPUT_FOLDER "Data\\"
#define OUTPUT_FOLDER "SQL\\"

void genereazaModele()
{
	std::ifstream f(INPUT_FOLDER "modele.txt");
	std::ofstream g(OUTPUT_FOLDER "Modele.sql");

	int id = 0;
	std::string s = "";

	do
	{
		id++;
		std::getline(f, s);

		g << "INSERT INTO MODELE VALUES ("
			<< id << ", '" << s << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaCombustibili()
{
	std::ifstream f(INPUT_FOLDER "combustibili.txt");
	std::ofstream g(OUTPUT_FOLDER "Combustibili.sql");

	int id = 0;
	std::string s = "";

	do
	{
		id++;
		std::getline(f, s);

		g << "INSERT INTO COMBUSTIBILI VALUES ("
			<< id << ", '" << s << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaTari()
{
	std::ifstream f(INPUT_FOLDER "Tari.txt");
	std::ofstream g(OUTPUT_FOLDER "Tari.sql");

	std::string id = "";
	std::string denumire = "";

	do
	{
		std::getline(f, id);
		std::getline(f, denumire);

		g << "INSERT INTO TARI VALUES ("
			<< id << ", " << denumire << ");\n";

	} while (!f.eof());


	f.close();
	g.close();
}

void genereazaAdrese()
{
	std::ifstream f(INPUT_FOLDER "locatii.txt");
	std::ofstream g(OUTPUT_FOLDER "Adrese.sql");

	int id = 0;
	std::string s = "";

	std::vector<std::string> tari{
		"AR", "AU", "BE", "BR", "CA", "CH", "CN", 
		"DE", "DK", "EG", "FR", "HK", "IL", "IN", "IT", 
		"JP", "KW", "MX", "NG"
		, "NL", "SG", "UK", "US", "ZM", "ZW" };

	do
	{
		id++;
		std::getline(f, s);

		g << "INSERT INTO ADRESE VALUES ("
			<< id << ", '" << tari[rand() % tari.size()] << "', '" << s << "');\n";


	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaSedii()
{
	std::ofstream g(OUTPUT_FOLDER "Sedii.sql");

	for (int id = 1; id <= 5; ++id)
	{
		g << "INSERT INTO SEDII VALUES ("
			<< id << ", " << 20 + id << ");\n";
	}

	g.close();
}

void genereazaClienti()
{
	std::ifstream f(INPUT_FOLDER "clienti.txt");
	std::ofstream g(OUTPUT_FOLDER "Clienti.sql");

	int id = 0;
	std::string nume = "";
	std::string prenume = "";
	std::string tel = "";
	std::string mail = "";

	int idAdresaInceput = 0;

	do
	{
		id++;
		f >> nume >> prenume >> tel >> mail;

		g << "INSERT INTO CLIENTI VALUES ("
			<< id << ", " << idAdresaInceput + id << ", '" << nume << "', '" << prenume << "', '" << tel << "', '" << mail << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaAngajati()
{
	const int NUMAR_SEDII = 5;

	std::ifstream f(INPUT_FOLDER "angajati.txt");
	std::ofstream g(OUTPUT_FOLDER "Angajati.sql");

	int id = 0;
	std::string nume = "";
	std::string prenume = "";
	std::string tel = "";
	std::string mail = "";

	int idAdresaInceput = 10;

	do
	{
		id++;
		f >> nume >> prenume >> tel >> mail;

		int ziNastere = rand() % 28 + 1;
		int lunaNastere = rand() % 12 + 1;
		int anNastere = 1975 + (rand() % (2001 - 1975 + 1));

		int ziAngajare = rand() % 28 + 1;
		int lunaAngajare = rand() % 12 + 1;
		int anAngajare = std::min(anNastere + (19 + rand() % (50 - 19 + 1)), 2000);

		g << "INSERT INTO ANGAJATI VALUES ("
			<< id << ", "
			<< rand() % 5 + 1 << ", "
			<< idAdresaInceput + id << ", "
			<< "MODIF" << ", '"
			<< nume << "', '"
			<< prenume << "', '"
			<< tel << "', '"
			<< mail << "', "
			<< "to_date('" << (ziAngajare) << "-" << (lunaAngajare) << "-" << anAngajare << "', 'dd-mm-yyyy'), "
			<< "to_date('" << (ziNastere) << "-" << (lunaNastere) << "-" << anNastere << "', 'dd-mm-yyyy'), "
			<< 4000 + (rand() % (15000 - 4000 + 1)) << ");\n";

	} while (!f.eof());


	f.close();
	g.close();
}

void genereazaMasini()
{
	std::ifstream f(INPUT_FOLDER "random.txt");
	std::vector<std::string> random;
	std::string s;
	do
	{
		std::getline(f, s);
		random.push_back(std::move(s));
	} while (!f.eof());

	std::ofstream g(OUTPUT_FOLDER "Masini.sql");

	const int NUMAR_MASINI = 69;
	const int NUMAR_MODELE = 12;
	const int NUMAR_COMBUSTIBILI = 8;
	std::vector<std::string> tari{
		"AR", "AU", "BE", "BR", "CA", "CH", "CN",
		"DE", "DK", "EG", "FR", "HK", "IL", "IN", "IT",
		"JP", "KW", "MX", "NG"
		, "NL", "SG", "UK", "US", "ZM", "ZW" };

	for (int idMasina = 1; idMasina <= NUMAR_MASINI; ++idMasina)
	{
		g << "INSERT INTO MASINI VALUES ("
			<< idMasina << ", "
			<< rand() % NUMAR_MODELE + 1 << ", "
			<< rand() % NUMAR_COMBUSTIBILI + 1 << ", '"
			<< tari[rand() % tari.size()] << "', "
			<< rand() % 100 << ", '"
			<< random[rand() % random.size()] << "');\n";
	}

	f.close();
	g.close();
}

void genereazaGarantii()
{
	std::ofstream g(OUTPUT_FOLDER "Garantii.sql");
	const int NUMAR_GARANTII = 30;

	for (int idGarantie = 1; idGarantie <= NUMAR_GARANTII; ++idGarantie)
	{
		g << "INSERT INTO GARANTII_SERVICE VALUES ("
			<< idGarantie << ", "
			<< rand() % 6 << ", "
			<< rand() % 100000 << ", "
			<< (rand() % 101 > 30 ? "'DA'" : "'NU'") << ");\n";
	}


	g.close();
}

void genereazaVanzari()
{
	std::ofstream g(OUTPUT_FOLDER "Vanzari.sql");

	const int NUMAR_VANZARI = 30;
	const int NUMAR_MASINI = 69;
	const int NUMAR_ANGAJATI = 10;
	const int NUMAR_CLIENTI = 10;

	int zi = rand() % 28 + 1;
	int luna = rand() % 12 + 1;
	int an = 2000 + (rand() % (2019 - 2000 + 1));

	std::set<int> masiniVandute;

	for (int idVanzare = 1; idVanzare <= NUMAR_VANZARI; ++idVanzare)
	{
		int idMasina = 0;
		do
		{
			idMasina = rand() % NUMAR_MASINI + 1;
		} while (!masiniVandute.insert(idMasina).second);

		g << "INSERT INTO VANZARI VALUES ("
			<< idVanzare << ", "
			<< idMasina << ", "
			<< rand() % NUMAR_ANGAJATI + 1 << ", "
			<< rand() % NUMAR_ANGAJATI + 1 << ", "
			<< idVanzare << ", "
			<< "to_date('" << (zi) << "-" << (luna) << "-" << an << "', 'dd-mm-yyyy'), "
			<< 10000 + (rand() % (100000 - 10000 + 1)) << ");\n";
	}

	g.close();
}

void generariCartiService()
{
	std::ifstream f(INPUT_FOLDER "random.txt");
	std::vector<std::string> random;
	std::string s;
	do
	{
		std::getline(f, s);
		random.push_back(std::move(s));
	} while (!f.eof());

	std::ofstream g(OUTPUT_FOLDER "CartiService.sql");

	const int NUMAR_CARTI_SERVICE = 50;
	const int NUMAR_GARANTII = 30;

	for (int idCarteService = 1; idCarteService <= NUMAR_CARTI_SERVICE; ++idCarteService)
	{
		g << "INSERT INTO CARTI_SERVICE VALUES ("
			<< idCarteService << ", "
			<< rand() % NUMAR_GARANTII + 1 << ", "
			<< rand() % 10000 << ", '"
			<< random[rand() % random.size()] << "');\n";
	}

	f.close();
	g.close();
}

int main()
{
	generariCartiService();

	return 0;
}