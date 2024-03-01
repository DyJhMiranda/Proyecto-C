#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*
Universidad de Costa Rica
Facultad de Ingeniería
Escuela de Ingeniería Eléctrica
IE0117 - Programación Bajo Plataformas Abiertas
Docente: Julian Gairaud
III Ciclo 2023
Proyecto C: Parte 2

El presente proyecto tiene como fin encontrar la o las intersecciones
entre dos funciones cuadráticas en el plano. Estas se mostrarán al usuario
por consola y posteriormente se graficaran usando la librería de gnuplot,
además de mostrar también pues las funciones cuadráticas graficadas
correctamente.

*/
/*
// Función para calcular el valor de una función cuadrática
double cuadratica(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

// Función para buscar el subdominio
void busqueda_subdominio(double a1, double b1, double c1, double a2, double b2, double c2, double porc_error) {
    printf("Subdominio donde se cumple el porcentaje de error:\n");
    for (double x = -100000; x <= 100000; x += 0.1) {
        double fx = cuadratica(a1, b1, c1, x);
        double gx = cuadratica(a2, b2, c2, x);

        double error = 100 * fabs(fx - gx) / fx;

        if (error <= porc_error) {
            printf("Valor de x dentro del porcentaje de error: %.2lf\n", x);
        }
    }
}

// Función para graficar las funciones cuadráticas
void graficar(double a1, double b1, double c1, double a2, double b2, double c2, double porc_error) {
    FILE *gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot == NULL) {
        printf("Error al abrir Gnuplot.\n");
        return;
    }

    fprintf(gnuplot, "set term wxt\n"); // Ventana emergente para la gráfica
    fprintf(gnuplot, "set title 'Funciones Cuadráticas'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");

    // Graficar las funciones cuadráticas
    fprintf(gnuplot, "plot %.2lf * x**2 + %.2lf * x + %.2lf title 'Función 1', ", a1, b1, c1);
    fprintf(gnuplot, "%.2lf * x**2 + %.2lf * x + %.2lf title 'Función 2', ", a2, b2, c2);

    // Calcular y graficar el área sombreada donde se cumple el porcentaje de error
    fprintf(gnuplot, "(x > 100000) ? 1/0 : ");
    fprintf(gnuplot, "((%lf * x*2 + %lf * x + %lf) - (%lf * x2 + %lf * x + %lf) <= (%lf / 100) * (%lf * x2 + %lf * x + %lf)) ? (%lf * x*2 + %lf * x + %lf) : 1/0 ",
            a1, b1, c1, a2, b2, c2, porc_error, a1, b1, c1, a2, b2, c2);

    fprintf(gnuplot, "with filledcurves above y1=0 title 'Porcentaje de error'\n");

    pclose(gnuplot);
}

int main() {
    double a1, b1, c1, a2, b2, c2, porc_error;

    printf("Ingresa el porcentaje de error deseado: ");
    scanf("%lf", &porc_error);

    printf("Ingresa los coeficientes de la primera función cuadrática (a1 b1 c1): ");
    scanf("%lf %lf %lf", &a1, &b1, &c1);

    printf("Ingresa los coeficientes de la segunda función cuadrática (a2 b2 c2): ");
    scanf("%lf %lf %lf", &a2, &b2, &c2);

    busqueda_subdominio(a1, b1, c1, a2, b2, c2, porc_error);
    graficar(a1, b1, c1, a2, b2, c2, porc_error);

    return 0;
}
//[9:10, 27/2/2024] José León IE: #include <stdio.h>
#include <math.h>
*/

// Función para calcular el valor de una función cuadrática

double cuadratica(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

float encontrar_intervalo(double a1, double b1, double c1, double a2,
double b2, double c2, double error, double valorX) {
    float distancia = valorX;
    float limite = 100000.0;
    float evaluacionFx, evaluacionGx, errorActual, intervalo = 0.0;
    while (distancia <= limite) {
        evaluacionFx = cuadratica(a1, b1, c1, distancia);
        evaluacionGx = cuadratica(a2, b2, c2, distancia);
        errorActual = 100.0 * fabs(evaluacionFx - evaluacionGx)
        / evaluacionFx;
        if (errorActual > error || distancia == limite) {
            intervalo = distancia - valorX;
            break;
        }
        distancia = distancia + 0.1;
    }
    return intervalo;
}

// Función para buscar el subdominio
void busqueda_subdominio(double a1, double b1, double c1, double a2, double b2, double c2, double porc_error, bool* interseccion, double* x1, double* x2,
double* primerIntervalo, double* segundoIntervalo) {
    printf("Subdominio donde se cumple el porcentaje de error:\n");
    // Generar una nueva ecuación para obtener las intersecciones.
    float a = a1 - a2;
    float b = b1 - b2;
    float c = c1 - c2;
    float discriminante = pow(b, 2) - 4 * a * c;
    float intervalo1, intervalo2 = 0.0;
    float solucion1, solucion2 = 0.0;
    if (discriminante >= 0) {
        // Existe al menos una solución real.
        if (a == 0.0) {
            // Si a == 0, es una función lineal y solo tiene una
            // intersección entre funciones
            if (b != 0.0) {
                solucion1 = -c / b;
            } else {
                solucion1 = -c;
            }
            // Encontrar intervalo para la intersección:
            intervalo1 = encontrar_intervalo(a1, b1, c1, a2, b2, c2,
            porc_error, solucion1);
            *x1 = solucion1;
            *interseccion = true;
            *primerIntervalo = intervalo1;
            printf("[%f, %f] \n", solucion1 - intervalo1, solucion1 + intervalo1);
        } else {
            // Si no, es cuadrática y se calcula con fórmula general.
            solucion1 = (-b + sqrt(discriminante)) / (2 * a);
            solucion2 = (-b - sqrt(discriminante)) / (2 * a);
            *x1 = solucion1;
            *x2 = solucion2;
            // Encontrar intervalo para las intersecciones
            intervalo1 = encontrar_intervalo(a1, b1, c1, a2, b2, c2,
            porc_error, solucion1);
            intervalo2 = encontrar_intervalo(a1, b1, c1, a2, b2, c2,
            porc_error, solucion2);
            // Asignar valores para usarlos al salir de la función
            *interseccion = true;
            *primerIntervalo = intervalo1;
            *segundoIntervalo = intervalo2;
            // Imprimir resultados
            printf("[%f, %f]\n", solucion1 - intervalo1, solucion1 + intervalo1);
            printf("[%f, %f]\n", solucion2 - intervalo2, solucion2 + intervalo2);
        }
    } else {
        // Imprimir error
        fprintf(stderr, "No se encontró intersección para las funciones. \n");
    }
}


// Función para graficar las funciones cuadráticas con el rango donde se cumple el porcentaje de error
void graficar(double a1, double b1, double c1, double a2, double b2, double c2, double porc_error, bool interseccion, float x1, float x2, float intervalo1,
float intervalo2) {
    FILE *gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot == NULL) {
        printf("Error al abrir Gnuplot.\n");
        return;
    }

    fprintf(gnuplot, "set term wxt\n"); // Ventana emergente para la gráfica
    fprintf(gnuplot, "set title 'Funciones Cuadráticas'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");

    // Graficar las funciones cuadráticas
    fprintf(gnuplot, "plot [-10:10] %.2lf * x**2 + %.2lf * x + %.2lf title 'Función 1',", a1, b1, c1);
    fprintf(gnuplot, "%.2lf * x**2 + %.2lf * x + %.2lf title 'Función 2'", a2, b2, c2);

    // Si hay intersecciones entre las graficas, mostrar los rangos respectivos
    if (interseccion == true) {
        if (intervalo1 != 0.0) {
            float distancia = x1 + intervalo1;
            fprintf(gnuplot, "set parametric \n");
            fprintf(gnuplot, "set arrow from %.2lf, graph 0 to %.2lf, graph 1 nohead lc rgb 'red' \n", distancia, distancia);
            distancia = x1 - intervalo1;
            fprintf(gnuplot, "set arrow from %.2lf, graph 0 to %.2lf, graph 1 nohead lc rgb 'red' \n", distancia, distancia);
        }
        if (intervalo2 != 0.0) {
            float distancia = x2 + intervalo2;
            //fprintf(gnuplot, "set parametric \n");
            fprintf(gnuplot, "set arrow from %.2lf, graph 0 to %.2lf, graph 1 nohead lc rgb 'red' \n", distancia, distancia);
            distancia = x2 - intervalo2;
            fprintf(gnuplot, "set arrow from %.2lf, graph 0 to %.2lf, graph 1 nohead lc rgb 'red' \n", distancia, distancia);
        }
    }
    fprintf(gnuplot, "set object 1 rectangle from screen 0, graph 0 to screen 1, graph %lf behind fillcolor rgb '#89fd0b' fillstyle solid noborder\n", porc_error/100);
    // fprintf(gnuplot, "set arrow 1 from graph 0,first %lf to graph 1,first %lf nohead lc rgb 'blue' lw 2 front\n", porc_error/100, porc_error/100);
    //fprintf(gnuplot, "set arrow 2 from graph 0,last %lf to graph 1,last %lf nohead lc rgb 'blue' lw 2 front\n", porc_error/100, porc_error/100);
    
    pclose(gnuplot);
}


int main() {
    double a1, b1, c1, a2, b2, c2, porc_error, x1, x2,
    intervalo1, intervalo2 = 0.0;

    printf("Ingresa el porcentaje de error deseado: ");
    scanf("%lf", &porc_error);

    printf("Ingresa los coeficientes de la primera función cuadrática (a1 b1 c1): ");
    scanf("%lf %lf %lf", &a1, &b1, &c1);

    printf("Ingresa los coeficientes de la segunda función cuadrática (a2 b2 c2): ");
    scanf("%lf %lf %lf", &a2, &b2, &c2);

    bool interseccion = false;
    busqueda_subdominio(a1, b1, c1, a2, b2, c2, porc_error, &interseccion,
    &x1, &x2, &intervalo1, &intervalo2);
    graficar(a1, b1, c1, a2, b2, c2, porc_error, interseccion, x1,
    x2, intervalo1, intervalo2);

    return 0;
}