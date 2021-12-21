#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

#define INPUT_FOLDER "Data\\"
#define OUTPUT_FOLDER "SQL\\"

void genereazaCategorii()
{
	std::ifstream f(INPUT_FOLDER "Categorii.txt");
	std::ofstream g(OUTPUT_FOLDER "Categorii.sql");

	int id = 0;
	std::string s = "";

	do
	{
		id++;
		std::getline(f, s);

		g << "INSERT INTO CATEGORII VALUES ("
			<< id << ", '" << s << "');\n";


	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaProduse()
{
	const int NUMAR_CATEGORII = 10;

	std::ifstream den(INPUT_FOLDER "Produse.txt");
	std::ifstream desc(INPUT_FOLDER "Text random.txt");
	std::ofstream g(OUTPUT_FOLDER "Produse.sql");

	int id = 0;
	std::string denumire = "";
	std::string descriere = "";

	do
	{
		id++;
		std::getline(den, denumire);
		std::getline(desc, descriere);

		g << "INSERT INTO PRODUSE VALUES ("
			<< id << ", " << NUMAR_CATEGORII - id + 1 << ", '" << denumire << "', '" << descriere << "', "
			<<100 + (rand() % (1000 - 100 + 1)) << ");\n";

	} while (!den.eof() && !desc.eof());


	den.close();
	desc.close();
	g.close();
}

std::string genereazaCodPostal()
{
	std::string cod = "";
	for (int i = 0; i < 4; ++i)
		cod.push_back('0' + (rand() % ('9' - '0' + 1)));
	return cod;
}

void genereazaAdrese()
{
	std::ifstream f(INPUT_FOLDER "Adrese.txt");
	std::ofstream g(OUTPUT_FOLDER "Adrese.sql");

	std::vector<std::string> orase{"Bucuresti", "Brasov", "Cluj-Napoca", "Timiș", "Iasi", "Bihor", "Bacau", "Constanta", "Argeș"};

	int id = 0;
	std::string s = "";

	do
	{
		id++;
		std::getline(f, s);

		g << "INSERT INTO ADRESA VALUES ("
			<< id << ", '" << genereazaCodPostal() << "', '" << orase[rand() % orase.size()] << "', '" << s << "');\n";

	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaDepartamente()
{
	std::ifstream f(INPUT_FOLDER "Departamente.txt");
	std::ofstream g(OUTPUT_FOLDER "Departamente.sql");

	const int NUMAR_ADRESE = 10;
	std::set<int> adrese;

	int id = 0;
	std::string denumire = "";

	do
	{
		id++;
		std::getline(f, denumire);

		int idAdresa = 0;
		do
		{
			idAdresa = rand() % NUMAR_ADRESE + 1;

		} while (!adrese.insert(idAdresa).second);

		g << "INSERT INTO DEPARTAMENT VALUES ("
			<< id << ", '" << denumire << "', " << idAdresa << ", NULL);\n";


	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaAngajati()
{
	std::ifstream f(INPUT_FOLDER "Angajati.txt");
	std::ofstream g(OUTPUT_FOLDER "Angajati.sql");

	const int NUMAR_DEPARTAMENTE = 5;

	int id = 0;
	std::string nume = "";
	std::string prenume = "";
	std::string mail = "";
	std::string tel = "";

	do
	{
		id++;
		f >> nume >> prenume >> mail >> tel;

		int ziAngajare = rand() % 28 + 1;
		int lunaAnagajre = rand() % 12 + 1;
		int anAngajare = 2000 + (rand() % (2016 - 2000 + 1));

		g << "INSERT INTO ANGAJATI VALUES ("
			<< id << ", '" << nume << "', '" << prenume << "', '" << mail << "', '" << tel << "', "
			<< "to_date('" << (ziAngajare) << "-" << (lunaAnagajre) << "-" << anAngajare << "', 'dd-mm-yyyy'), "
			<< " NULL, " << rand() % NUMAR_DEPARTAMENTE + 1 << ", " << 3000 + (rand() % (15000 - 3000 + 1)) << ");\n";


	} while (!f.eof());

	f.close();
	g.close();
}

void genereazaAprovizionari()
{
	std::vector<std::string> apr;
	std::ifstream f(INPUT_FOLDER "APROVIZIONARI.txt");
	do
	{
		std::string s;
		std::getline(f, s);
		apr.push_back(s);
	} while (!f.eof());
	f.close();

	const int NUMAR_DEPARTAMENTE = 5;
	std::ofstream g(OUTPUT_FOLDER "Aprovizionari.sql");

	const int NUMAR_APROVIZIONARI = 50;

	for (int idAprovizionare = 1; idAprovizionare <= 50; ++idAprovizionare)
	{
		g << "INSERT INTO APROVIZIONARI VALUES ("
			<< idAprovizionare << ", " << rand() % NUMAR_DEPARTAMENTE + 1 << ", '"
			<< apr[rand() % apr.size()] << "', " << 25 + (rand() % (100 - 25 + 1)) << ", " << 500 + (rand() % 7000 - 500 + 1) << ");\n";
	}

	g.close();
}

void genereazaFacturi()
{
	const int NUMAR_ADRESE = 10;
	std::ofstream g(OUTPUT_FOLDER "Facturi.sql");

	const int NUMAR_FACTURI = 50;

	for (int idFactura = 0; idFactura <= NUMAR_FACTURI; ++idFactura)
	{
		int ziFacturare = rand() % 24 + 1;
		int lunaFacturare = rand() % 12 + 1;
		int anFacturare = 2016 + (rand() % (2020 - 2016 + 1));

		int ziScadenta = ziFacturare + (rand() % 4) + 1;
		int lunaScadenta = lunaFacturare;
		int anScadenta = anFacturare;

		g << "INSERT INTO FACTURI VALUES ("
			<< idFactura << ", " << rand() % NUMAR_ADRESE + 1<<", "
			<< "to_date('" << ziFacturare << "-" << lunaFacturare << "-" << anFacturare << "', 'dd-mm-yyyy'), "
			<< "to_date('" << ziScadenta << "-" << lunaScadenta << "-" << anScadenta << "', 'dd-mm-yyyy'));\n";
	}

	g.close();
}

void genereazaComenzi()
{
	const int NUMAR_ANGAJATI = 10;
	std::ofstream g(OUTPUT_FOLDER "Comenzi.sql");

	const int NUMAR_COMENZI = 50;
	for (int idComanda = 1; idComanda <= NUMAR_COMENZI; ++idComanda)
	{
		int ziFacturare = rand() % 24 + 1;
		int lunaFacturare = rand() % 12 + 1;
		int anFacturare = 2016 + (rand() % (2020 - 2016 + 1));
		g << "INSERT INTO COMENZI VALUES ("
			<< idComanda << ", "
			<< "to_date('" << ziFacturare << "-" << lunaFacturare << "-" << anFacturare << "', 'dd-mm-yyyy'), "
			<< rand() % NUMAR_ANGAJATI + 1 << ", " << idComanda << ");\n";
	}

	g.close();
}

void genereazaProduseComandate()
{
	const int NUMAR_COMENZI = 50;
	std::ofstream g(OUTPUT_FOLDER "ProduseComandate.sql");

	int id = 0;

	for (int idComanda = 1; idComanda <= NUMAR_COMENZI; ++idComanda)
	{
		int numarProduseComandate = rand() % 4 + 1;
		for (int i = 0; i < numarProduseComandate; ++i)
		{
			id++;
			g << "INSERT INTO PRODUS_COMANDAT VALUES ("
				<< id << ", " << idComanda << ", " << 100 + (rand() % (1000 - 100 + 1)) << ", " << 4 + rand() % 10 << ");\n";
		}
	}

	g.close();
}

int main()
{
	genereazaProduseComandate();


	return 0;
}