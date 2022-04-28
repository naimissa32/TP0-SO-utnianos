#include "client.h"
#include<stdbool.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger,"Hola, soy un log");



	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
    valor = string_duplicate(config_get_string_value(config, "CLAVE"));
    log_info(logger,valor);


	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)

{
	t_log* nuevo_logger;

	nuevo_logger = log_create("tp0.log", "tp0", true ,  LOG_LEVEL_INFO);

	return nuevo_logger;
}



t_config* iniciar_config(void)

{
	t_config* nuevo_config;
//nuevo_config nos va  a traer infor del archivo cliente.config
	nuevo_config = config_create("cliente.config");

	return nuevo_config;
}


void leer_consola(t_log* logger)
{
char* leido;

// La primera te la dejo de yapa
leido = readline("> ");

// El resto, las vamos leyendo y logueando hasta recibir un string vacío

//si leido es igual a la cadena vacia
//strcmp compara dos cadenas si las dos son iguales da 0, si es mayor es 1, si es menor -1

while(strcmp(leido,"")!=0){
	log_info(logger,leido);
	free(leido);
	leido= readline("> ");
}

	  free(leido);

// ¡No te olvides de liberar las lineas antes de regresar!

}


void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete
	paquete = crear_paquete();

	leido = readline(">");
		while(strcmp(leido, "") != 0)
		{
			agregar_a_paquete(paquete, leido, strlen(leido) + 1);
			free(leido);
			leido = readline(">");
		}

		free(leido);
	//enviar paquete Preguntar porque no toma a socket_cliente

	enviar_paquete(paquete, conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	liberar_conexion(conexion);
}
