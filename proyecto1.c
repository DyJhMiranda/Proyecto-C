/*
Valery Carranza Vásquez B91660
Jose Armando León Solano B94249
Dylan Miranda Granados C24857

Este programa utiliza la herramienta de GTK, Glade para crear
la interfaz gráfica del juego tic-tac-toe.
Es posible ejecutar el programa mediante el makefile.

El juego consiste en presionar los botones que se presentan en la ventana,
de manera que el jugador 1 marca sus casillas con una x y
el jugador 2 las marca con una O, gana el jugador que logre 
formar una línea de 3 casillas consecutivas.  

Con la herramienta GKT se contruyen los botones, que al ser preionados 
generan una señal, la cual se registray se guarda en un  tablero, luego se
convierte este tablero en una matriz. Después, se utiliza una función que revisa
las fila, columnsa y diagonales de la matriz, buscando casillas consecutivas
con el mismo simbolo que producen la condición de ganador
*/


#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *Window;
GtkLabel *Mensaje;

// Variable para rastrear el estado actual del botón
int estado_boton = 0; // 0 para "X", 1 para "O"
// Variable para rastrear si el botón ya ha sido clicado
int botonPresionado1 = 0;
int botonPresionado2 = 0;
int botonPresionado3 = 0;
int botonPresionado4 = 0;
int botonPresionado5 = 0;
int botonPresionado6 = 0;
int botonPresionado7 = 0;
int botonPresionado8 = 0;
int botonPresionado9 = 0;

// Matriz para rastrear el estado del tablero
char tablero[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

// Función para convertir el tablero en un array
void tablero_a_array(char array[9]) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            array[k++] = tablero[i][j];
        }
    }
}

// Función para revisar quién es el ganador
char revisar_ganador(char array[9]) {
    // Comprobaciones de filas
    for (int i = 0; i < 3; i++) {
        if (array[i*3] == array[i*3 + 1] && array[i*3 + 1] == array[i*3 + 2] && array[i*3] != ' ') {
            return array[i*3];
        }
    }
    
    // Comprobaciones de columnas
    for (int i = 0; i < 3; i++) {
        if (array[i] == array[i + 3] && array[i + 3] == array[i + 6] && array[i] != ' ') {
            return array[i];
        }
    }
    
    // Comprobaciones de diagonales
    if ((array[0] == array[4] && array[4] == array[8] && array[0] != ' ') ||
        (array[2] == array[4] && array[4] == array[6] && array[2] != ' ')) {
        return array[4];
    }
    
    return ' '; // Si no hay ganador aún
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "in.glade", NULL);

    Window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana"));
    Mensaje = GTK_LABEL(gtk_builder_get_object(builder, "mensaje"));
    
    gtk_builder_connect_signals(builder, NULL); 
    g_object_unref(builder);
    
    gtk_widget_show_all(Window);
    gtk_main();

    return 0;
}

void b_uno(GtkWidget *widget, gpointer data) {
    if (botonPresionado1 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto1 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto1);
        tablero[0][0] = *texto1;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado1 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);

        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}

// Implementa las funciones b_dos(), b_tres(), b_cuatro(), b_cinco(), b_seis(), b_siete(), b_ocho(), b_nueve() de manera similar a b_uno() 
void b_dos(GtkWidget *widget, gpointer data) {
    if (botonPresionado2 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto2 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto2);
        tablero[0][1] = *texto2;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado2 = 1;
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);
       
        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}
void b_tres(GtkWidget *widget, gpointer data) {
    if (botonPresionado3 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto3 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto3);
        tablero[0][2] = *texto3;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado3 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);
           
        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}
void b_cuatro(GtkWidget *widget, gpointer data) {
    if (botonPresionado4 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto4 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto4);
        tablero[1][0] = *texto4;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado4 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);
            exit(EXIT_SUCCESS);
        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}
void b_cinco(GtkWidget *widget, gpointer data) {
    if (botonPresionado5 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto5 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto5);
        tablero[1][1] = *texto5;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado5 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);
            
        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}
void b_seis(GtkWidget *widget, gpointer data) {
    if (botonPresionado6 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto6 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto6);
        tablero[1][2] = *texto6;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado6 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);
           
        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}
void b_siete(GtkWidget *widget, gpointer data) {
    if (botonPresionado7 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto7 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto7);
        tablero[2][0] = *texto7;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado7 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);
            exit(EXIT_SUCCESS);
        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}
void b_ocho(GtkWidget *widget, gpointer data) {
    if (botonPresionado8 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto8= (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto8);
        tablero[2][1] = *texto8;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado8 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);
        } else {
            printf("No hay ganador todavía.\n");
        }
    }
}
void b_nueve(GtkWidget *widget, gpointer data) {
    if (botonPresionado9 == 0) {
        // Alternar entre "X" y "O" dependiendo del estado actual del botón
        char *texto9 = (estado_boton == 0) ? "X" : "O";
        gtk_button_set_label(GTK_BUTTON(widget), texto9);
        tablero[2][2] = *texto9;
        // Actualizar el estado del botón para el próximo clic
        estado_boton = 1 - estado_boton; // Alternar entre 0 y 1
        botonPresionado9 = 1;
                
        // Convertir tablero en array y revisar ganador
        char array[9];
        tablero_a_array(array);
        char ganador = revisar_ganador(array);
        if (ganador != ' ') {
            char mensajes[50];
            sprintf(mensajes, "El ganador es: %c", ganador);
            gtk_label_set_text(Mensaje, mensajes);    
        } else {
            printf("No hay ganador todavía.\n");
 }
    } 
} 