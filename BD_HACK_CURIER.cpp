#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

#define INPUT_FOLDER "Data\\"
#define OUTPUT_FOLDER "SQL\\"

void genereazaDepartamente()
{
	std::ifstream f(INPUT_FOLDER "Departamente.txt");
	std::ofstream g(OUTPUT_FOLDER "Departamente.sql");

	int id = 0;
	std::string s = "";

	do
	{
		id++;
		std::getline(f, s);

		g << "INSERT INTO DEPARTAMENT VALUES ("
			<< id << ", '" << s << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaAdrese()
{
	const int NUMAR_JUDETE = 41;
	const int NUMAR_ORASE = 123;

	std::ifstream f(INPUT_FOLDER "LOCATII.txt");
	std::ofstream g(OUTPUT_FOLDER "Adrese.sql");

	int id = 0;
	std::string locatie = "";

	do
	{
		id++;
		std::getline(f, locatie);

		g << "INSERT INTO ADRESE VALUES ("
			<< id << ", "
			<< rand() % 41 + 1 << ", "
			<< rand() % 123 + 1 << ", '"
			<< locatie << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaFunctii()
{
	std::ifstream f(INPUT_FOLDER "FUNCTII.txt");
	std::ofstream g(OUTPUT_FOLDER "Functii.sql");

	int id = 0;
	std::string denumireFunctie = "";

	do
	{
		id++;
		std::getline(f, denumireFunctie);

		int salariuMinim = 2000 + (rand() % (10000 - 2000 + 1));
		int salariuMaxim = salariuMinim + (rand() % (10000 - salariuMinim + 1));

		g << "INSERT INTO FUNCTII VALUES ("
			<< id << ", '" << denumireFunctie << "', " << salariuMinim << ", " << salariuMaxim << ");\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaPersoane()
{
	const int NUMAR_ADRESE = 105;

	std::ifstream f(INPUT_FOLDER "DATE_PERSONALE.txt");
	std::ofstream g(OUTPUT_FOLDER "Persoane.sql");

	int id = 0;
	std::string nume = "";
	std::string prenume = "";
	std::string tel = "";
	std::string mail = "";

	do
	{
		id++;
		f >> nume >> prenume >> mail >> tel;

		g << "INSERT INTO PERSOANE VALUES ("
			<< id << ", " << NUMAR_ADRESE - id + 1 << ", '" << nume << "', '" << prenume << "', '" << tel << "', '" << mail << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaAngajati()
{
	const int NUMAR_ADRESE = 20;
	const int NUMAR_FUNCTII = 20;
	const int NUMAR_DEPARTAMENTE = 6;
	std::ifstream f(INPUT_FOLDER "SALARIU_NUME_PRENUME.txt");
	std::ofstream g(OUTPUT_FOLDER "Angajati.sql");

	int id = 0;
	int salariu = 0;
	std::string nume = "";
	std::string prenume = "";

	do
	{
		id++;
		f >> salariu >> nume >> prenume;

		int ziNastere = rand() % 28 + 1;
		int lunaNastere = rand() % 12 + 1;
		int anNastere = 1975 + (rand() % (2001 - 1975 + 1));

		int ziAngajare = rand() % 28 + 1;
		int lunaAngajare = rand() % 12 + 1;
		int anAngajare = std::min(anNastere + (19 + rand() % (50 - 19 + 1)), 2000);

		g << "INSERT INTO ANGAJATI VALUES ("
			<< id << ", "
			<< rand() % NUMAR_FUNCTII + 1 << ", "
			<< rand() % NUMAR_ADRESE + 1 << ", "
			<< rand() % NUMAR_DEPARTAMENTE + 1 << ", "
			<< "to_date('" << (ziAngajare) << "-" << (lunaAngajare) << "-" << anAngajare << "', 'dd-mm-yyyy'), "
			<< salariu << ", '"
			<< nume << "', '"
			<< prenume << "', "
			<< "to_date('" << (ziNastere) << "-" << (lunaNastere) << "-" << anNastere << "', 'dd-mm-yyyy')" << ");\n";

	} while (!f.eof());

	f.close();
	g.close();
}

std::string tipMasina()
{
	int x = rand() % 100;

	if (x < 40) return "medie";
	if (x < 25)return "mare";
	
	return "mica";
}

void genereazaMasini()
{
	const int NUMAR_ANGAJATI = 20;
	std::ifstream f(INPUT_FOLDER "numere.txt");
	std::ofstream g(OUTPUT_FOLDER "MasiniFirma.sql");

	int id = 0;
	std::string numar = "";

	do
	{
		id++;
		std::getline(f, numar);

		g << "INSERT INTO MASINILE_FIRMEI VALUES ("
			<< id << ", " << rand() % NUMAR_ANGAJATI + 1 << ", '" << numar << "', '" << tipMasina() << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

std::string genereazaAWB()
{
	std::string s;
	s.reserve(13);

	for (int i = 0; i < 13; ++i)
	{
		char c = '0' + (rand() % ('9' - '0' + 1));
		s.push_back(c);
	}

	return s;
}

void genereazaColeteSiComenzi()
{
	const int NUMAR_MASINI = 10;
	const int NUMAR_PERSOANE = 50;
	const int NUMAR_ANGAJATI = 20;

	const int NUMAR_COLETE = 50;
	
	std::ofstream colete(OUTPUT_FOLDER "Colete.sql");
	std::ofstream comenzi(OUTPUT_FOLDER "Comenzi.sql");

	for (int id = 1; id <= NUMAR_COLETE; ++id)
	{
		int ziComanda = rand() % 24 + 1;
		int lunaComanda = rand() % 12 + 1;
		int anComanda = 2016 + (rand() % (2020 - 2016 + 1));

		int ziLivrare = ziComanda + (rand() % 4) + 1;
		int lunaLivrare = lunaComanda;
		int anLivrare = anComanda;

		colete << "INSERT INTO COLETE VALUES ("
			<< id << ", "
			<< rand() % NUMAR_PERSOANE + 1 << ", "
			<< rand() % NUMAR_MASINI + 1 << ", '"
			<< genereazaAWB() << "', "
			<< rand() % 100 + 1
			<< ", to_date('" << ziLivrare << "-" << lunaLivrare << "-" << anLivrare << "', 'dd-mm-yyyy')" << ");\n";

		comenzi << "INSERT INTO COMENZI VALUES ("
			<< id << ", "
			<< rand() % NUMAR_PERSOANE + 1 << ", "
			<< id << ", "
			<< rand() % NUMAR_ANGAJATI + 1
			<< ", to_date('" << ziComanda << "-" << lunaComanda << "-" << anComanda << "', 'dd-mm-yyyy'), "
			<< ((rand() % 2 == 0) ? "'card'" : "'ramburs'") << ");\n";
	}

	colete.close();
	comenzi.close();
}

int main()
{
	genereazaPersoane();

	return 0;
}