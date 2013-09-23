
#ifdef DEBUG
#define SHOW(x) cout << #x << "= " << x << endl;
#define STATE(x) cout << #x << endl;
#else 
#define SHOW(x)
#define STATE(x)
#endif

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int checklibrary(char* passed)
{
	SHOW(passed);
	try
	{
		ifstream filecheck(passed, ios::binary);
		if (!filecheck)
		{
			throw passed;
		}

		filecheck.close();
	}

	catch (char* &missing)
	{
		STATE(File Missing);
		cout << "Error: OGLbash could not locate: " << missing << endl;
		return 1;
	}

	return 0;
}

int checkheader(char* passed)
{
	SHOW(passed);
	try
	{
		ifstream filecheck(passed);
		if (!filecheck)
		{
			throw passed;
		}

		filecheck.close();
	}

	catch (char* &missing)
	{
		STATE(File Missing);
		cout << "Error: OGLbash could not locate: " << missing << endl;
		return 1;
	}

	return 0;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Invalid input for OGLBG. Please use the following format: OGLBG <source file>" << endl;
		return 1;
	}
	
	char check[25];
	int missing = 0;

	strcpy(check, "libfreeglut_static.a");
	if (checklibrary(check) != 0)
		missing++;

	strcpy(check, "libglew32.a");
	if (checklibrary(check) != 0)
		missing++;

	strcpy(check, "glew.h");
	if (checkheader(check) != 0)
		missing++;

	strcpy(check, "freeglut.h");
	if (checkheader(check) != 0)
		missing++;

	strcpy(check, "freeglut_ext.h");
	if (checkheader(check) != 0)
		missing++;

	strcpy(check, "freeglut_std.h");
	if (checkheader(check) != 0)
		missing++;

	strcpy(check, "glut.h");
	if (checkheader(check) != 0)
		missing++;

	if (missing > 0)
	{
		cout << "Please place these files into the working directory." << endl;
		return 1;
	}

	int stringlength = strlen(argv[1]);

	char ch;
	char filename[stringlength];
	char fullname[stringlength];

	SHOW(argv[1]);
	
	bool filenameEnd = false;

	strcpy(filename, argv[1]);
	strcpy(fullname, argv[1]);

	int dotCount = 0;

	for (int i=0; i<stringlength; i++)
	{
		if (filename[i] == '.')
		{
			filenameEnd = true;
			dotCount++;
		}

		if (filenameEnd == true)
			filename[i] = '\0';

		if (filename[i] == '\n')
			filename[i] = '\0';

		if (fullname[i] == '\n')
			fullname[i] = '\0';
	}

	SHOW(filename);
	SHOW(fullname);

	if (dotCount>1)
	{
		cout << "This filename has too many dots. Rename the source file and try again." << endl;
		return 1;
	}	

	char objectfile[(strlen(filename))+2];
	char exefile[(strlen(filename))+4];
	char bashfile[(strlen(filename))+5];

	strcpy(objectfile, filename);
	strcpy(exefile, filename);
	strcpy(bashfile, filename);

	strcat (objectfile, ".o");
	strcat (exefile, ".exe");
	strcat (bashfile, "_bash");

	SHOW(objectfile);
	SHOW(exefile);
	SHOW(bashfile);

	char bashstring1[50+strlen(objectfile)+strlen(fullname)];

	strcpy(bashstring1, "g++ -D GLEW_STATIC -D FREEGLUT_STATIC -c -o ");
	strcat(bashstring1, objectfile);
	strcat(bashstring1, " ");
	strcat(bashstring1, fullname);
	strcat(bashstring1, " -I.\n");

	SHOW(bashstring1);

	char bashstring2[99+strlen(objectfile)+strlen(exefile)];

	strcpy(bashstring2, "g++ -o ");
	strcat(bashstring2, exefile);
	strcat(bashstring2, " ");
	strcat(bashstring2, objectfile);
	strcat(bashstring2, " -L. -lfreeglut_static -lglew32 -lglu32 ");
	strcat(bashstring2, "-lopengl32 -lwinmm -lgdi32 -Wl,--subsystem,windows\n");

	SHOW(bashstring2);

	ofstream fout(bashfile);
	fout << bashstring1 << bashstring2 << "rm " << objectfile << "\n"; 
	if (bashfile)
	{
		cout << bashfile << " successfully generated.";
		cout << " To run, enter \"sh " << bashfile << "\"" << endl;
	}
	fout.close();

	return 0;
}