// Bibliotecas necesarias para entrada/salida y manejo de strings
#include <iostream>
#include <string>

// Para evitar escribir std:: antes de cada funci�n de la biblioteca est�ndar
using namespace std;

// Lista de palabras para las unidades (0-9)
string unidades[] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};

// Lista de palabras para las decenas (10, 20, 30, ..., 90)
string decenas[] = {"", "diez", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};

// Lista de palabras para los n�meros especiales del 11 al 19
string especiales[] = {"", "once", "doce", "trece", "catorce", "quince", "diecis�is", "diecisiete", "dieciocho", "diecinueve"};

// Lista de palabras para las centenas (100, 200, ..., 900)
string centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};

/*
* Funci�n que convierte n�meros menores a 1000 a palabras en espa�ol.
* Recibe un entero (0-999) y devuelve su representaci�n en texto.
*/
string convertirMenorAMil(int numero) {
	// Caso 1: N�meros del 0 al 9
	if (numero < 10) {
		return unidades[numero];  // Ej: 5 ? "cinco"
	}
	// Caso 2: N�meros del 10 al 19 (once, doce, etc.)
	else if (numero >= 10 && numero < 20) {
		return especiales[numero - 10];  // Ej: 13 ? "trece"
	}
	// Caso 3: N�meros del 20 al 99
	else if (numero >= 20 && numero < 100) {
		// Ej: 45 ? "cuarenta" + " y " + "cinco" ? "cuarenta y cinco"
		return decenas[numero / 10] + (numero % 10 != 0 ? " y " + unidades[numero % 10] : "");
	}
	// Caso 4: El n�mero 100 (no es "ciento", es "cien")
	else if (numero == 100) {
		return "cien";
	}
	// Caso 5: N�meros del 101 al 999
	else if (numero > 100 && numero < 1000) {
		// Ej: 345 ? "trescientos" + " " + "cuarenta y cinco" ? "trescientos cuarenta y cinco"
		return centenas[numero / 100] + " " + convertirMenorAMil(numero % 100);
	}
	// Si no cumple ninguna condici�n (no deber�a pasar)
	return "";
}

/*
* Funci�n principal que convierte cualquier n�mero entre 0 y 1 bill�n a palabras.
* Maneja miles, millones y billones.
*/
string convertirNumeroALetras(long long numero) {
	// Caso 1: El n�mero es cero
	if (numero == 0) {
		return "cero";
	}
	// Caso 2: N�meros menores a 1000
	else if (numero < 1000) {
		return convertirMenorAMil(numero);
	}
	// Caso 3: N�meros entre 1,000 y 999,999 (miles)
	else if (numero >= 1000 && numero < 1000000) {
		int miles = numero / 1000;  // Ej: 4500 ? 4 (miles)
		int resto = numero % 1000;  // Ej: 4500 ? 500 (resto)
		string resultado = convertirMenorAMil(miles) + " mil";  // Ej: "cuatro mil"
		if (resto != 0) {
			resultado += " " + convertirMenorAMil(resto);  // Ej: "cuatro mil quinientos"
		}
		return resultado;
	}
	// Caso 4: N�meros entre 1,000,000 y 999,999,999 (millones)
	else if (numero >= 1000000 && numero < 1000000000) {
		int millones = numero / 1000000;  // Ej: 2,500,000 ? 2 (millones)
		int resto = numero % 1000000;     // Ej: 2,500,000 ? 500,000 (resto)
		string resultado = convertirMenorAMil(millones) + " mill�n";  // Ej: "dos mill�n"
		if (millones > 1) {
			resultado += "es";  // Plural: "dos millones"
		}
		if (resto != 0) {
			resultado += " " + convertirNumeroALetras(resto);  // Ej: "dos millones quinientos mil"
		}
		return resultado;
	}
	// Caso 5: N�meros entre 1,000,000,000 y 999,999,999,999 (billones)
	else if (numero >= 1000000000 && numero < 1000000000000LL) {
		long long billones = numero / 1000000000;  // Ej: 3,200,000,000 ? 3 (billones)
		long long resto = numero % 1000000000;     // Ej: 3,200,000,000 ? 200,000,000 (resto)
		string resultado = convertirNumeroALetras(billones) + " bill�n";  // Ej: "tres bill�n"
		if (billones > 1) {
			resultado += "es";  // Plural: "tres billones"
		}
		if (resto != 0) {
			resultado += " " + convertirNumeroALetras(resto);  // Ej: "tres billones doscientos millones"
		}
		return resultado;
	}
	// Si no cumple ninguna condici�n (no deber�a pasar)
	return "";
}

/*
* Funci�n principal del programa.
* Solicita un n�mero al usuario, valida el rango y muestra su equivalente en letras.
*/
int main() {
	long long numero;  // Variable para almacenar el n�mero ingresado (hasta 1 bill�n)
	
	// Solicita al usuario un n�mero
	cout << "Ingrese un n�mero entre 0 y 1 bill�n (1,000,000,000,000): ";
	cin >> numero;
	
	// Verifica si el n�mero est� fuera del rango permitido
	if (numero < 0 || numero > 1000000000000LL) {
		cout << "N�mero fuera de rango." << endl;
	}
	// Si est� dentro del rango, lo convierte a letras y lo muestra
	else {
		cout << "El n�mero " << numero << " en letras es: " << convertirNumeroALetras(numero) << endl;
	}
	
	return 0;  // Fin del programa
}
