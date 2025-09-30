// ejercicio taller viernes.cpp
// Programa que gestiona las temperaturas promedio mensuales de tres departamentos
// Jader Suarez
#include <iostream>
#include <iomanip>
#include <cmath>    
#include <string>

const int MESES = 12;
const int DEPARTAMENTOS = 3;
const std::string nombresDeptos[DEPARTAMENTOS] = { "Santander", "Guajira", "Nariño" };
const std::string nombresMeses[MESES] = {
    "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
};

// Función para calcular el promedio anual de un departamento
double promedioAnual(const double temp[MESES]) {
    double suma = 0;
    for (int i = 0; i < MESES; ++i)
        suma += temp[i];
    return suma / MESES;
}

// Función para calcular el promedio nacional
double promedioNacional(const double t1[MESES], const double t2[MESES], const double t3[MESES]) {
    double suma = 0;
    for (int i = 0; i < MESES; ++i)
        suma += t1[i] + t2[i] + t3[i];
    return suma / (MESES * DEPARTAMENTOS);
}

// Función para encontrar el mes más caliente de un departamento
int mesMasCaliente(const double temp[MESES]) {
    int idx = 0;
    double max = temp[0];
    for (int i = 1; i < MESES; ++i) {
        if (temp[i] > max) {
            max = temp[i];
            idx = i;
        }
    }
    return idx;
}

// Función para obtener el valor máximo de un departamento
double maximoDepto(const double temp[MESES]) {
    double max = temp[0];
    for (int i = 1; i < MESES; ++i)
        if (temp[i] > max) max = temp[i];
    return max;
}

// Función para calcular el promedio de los picos
double promedioPicos(const double t1[MESES], const double t2[MESES], const double t3[MESES]) {
    double suma = maximoDepto(t1) + maximoDepto(t2) + maximoDepto(t3);
    return suma / DEPARTAMENTOS;
}

// Función para determinar el departamento con mayor promedio anual
int deptoMayorPromedio(const double proms[DEPARTAMENTOS]) {
    int idx = 0;
    double max = proms[0];
    for (int i = 1; i < DEPARTAMENTOS; ++i) {
        if (proms[i] > max) {
            max = proms[i];
            idx = i;
        }
    }
    return idx;
}

// Función para encontrar la temperatura máxima global y su ubicación
void maximoGlobal(const double t1[MESES], const double t2[MESES], const double t3[MESES],
    double& valor, int& depto, int& mes) {
    valor = t1[0];
    depto = 0;
    mes = 0;
    for (int d = 0; d < DEPARTAMENTOS; ++d) {
        const double* temp = (d == 0) ? t1 : (d == 1) ? t2 : t3;
        for (int m = 0; m < MESES; ++m) {
            if (temp[m] > valor) {
                valor = temp[m];
                depto = d;
                mes = m;
            }
        }
    }
}

// Función para calcular la desviación estándar poblacional
double desviacionEstandar(const double temp[MESES]) {
    double media = promedioAnual(temp);
    double suma = 0;
    for (int i = 0; i < MESES; ++i)
        suma += pow(temp[i] - media, 2);
    return sqrt(suma / MESES);
}

int main()
{
    double santander[MESES], guajira[MESES], narino[MESES];

    // Solicitar datos al usuario
    for (int d = 0; d < DEPARTAMENTOS; ++d) {
        double* temp = (d == 0) ? santander : (d == 1) ? guajira : narino;
        std::cout << "Ingrese las 12 temperaturas promedio mensuales para " << nombresDeptos[d] << ":\n";
        for (int m = 0; m < MESES; ++m) {
            std::cout << "  " << nombresMeses[m] << ": ";
            std::cin >> temp[m];
        }
        std::cout << std::endl;
    }

    double proms[DEPARTAMENTOS] = {
        promedioAnual(santander),
        promedioAnual(guajira),
        promedioAnual(narino)
    };

    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);

    // Promedios anuales
    for (int i = 0; i < DEPARTAMENTOS; ++i)
        std::cout << "Promedio anual " << nombresDeptos[i] << ": " << proms[i] << " °C\n";

    std::cout << std::endl;

    // Promedio nacional
    std::cout << "Promedio nacional: " << promedioNacional(santander, guajira, narino) << " °C\n";

    std::cout << std::endl;

    // Mes más caliente de cada departamento
    for (int i = 0; i < DEPARTAMENTOS; ++i) {
        const double* temp = (i == 0) ? santander : (i == 1) ? guajira : narino;
        int mes = mesMasCaliente(temp);
        std::cout << "Mes más caliente en " << nombresDeptos[i] << ": " << nombresMeses[mes]
            << " (" << temp[mes] << " °C)\n";
    }

    std::cout << std::endl;

    // Promedio de los picos
    std::cout << "Promedio de los picos: " << promedioPicos(santander, guajira, narino) << " °C\n";

    std::cout << std::endl;

    // Departamento con mayor promedio anual
    int idxMayor = deptoMayorPromedio(proms);
    std::cout << "Departamento con mayor promedio anual: " << nombresDeptos[idxMayor] << "\n";

    std::cout << std::endl;

    // Temperatura máxima anual global
    double valorMax;
    int deptoMax, mesMax;
    maximoGlobal(santander, guajira, narino, valorMax, deptoMax, mesMax);
    std::cout << "Temperatura máxima anual global: " << valorMax << " °C en "
        << nombresDeptos[deptoMax] << ", mes de " << nombresMeses[mesMax] << "\n";

    std::cout << std::endl;

    // Desviación estándar anual por departamento
    for (int i = 0; i < DEPARTAMENTOS; ++i) {
        const double* temp = (i == 0) ? santander : (i == 1) ? guajira : narino;
        std::cout << "Desviación estándar anual " << nombresDeptos[i] << ": "
            << desviacionEstandar(temp) << " °C\n";
    }

    return 0;

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
