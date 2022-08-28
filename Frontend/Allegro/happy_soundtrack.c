/*La verdad es que no estoy logrando hacer correr los archivos de prueba desde VS Code.
Me instalé netbeans y ahí sí que funciona, no sé qué onda. 
El tema es que ahora no puedo clonar de nuevo el repositorio desde netbeans, no me deja.
Así que por el momento estoy abriendo manualmente la carpeta en donde clono el repo desde
netbeans para ver si funca o no. Encima se me descuageringó la terminal integrada en VS, 
así que estoy re incómodo, una paja.

Lo de VS Code y allegro creo que es un tema de linker que el netbeans te arregla por 
defecto, pero que acá hay que configurar, así que veremos.
Una vez que salga eso, habrá que limpiar todos los archivos colados de "netbeans proyect"
y eso que están re molestando.

Qué bronca que tengo... Por qué nunca nos explicaron esto lpm */ 

//Los ejemplos de la cátedra no están comentados así que voy a usar mi criterio ingenieril

/*Al final lo que hice fue directamente agarrar el código de la cátedra y "desglozarlo", 
aparte de adaptarlo un cachin para que no sea un main sino un archivo que recibe un parámetro,
siendo dicho parámentro el audio que se quiere reproducir.*/
#include "happy_soundtrack.h"

int al_sound (char *path , float volume , float speed)
{
	/*Esto es muy confuso porque están usando structs pero no dicen cómo están 
	definidos así que voy a tener que escarvar entre los .h de allegro.*/

	ALLEGRO_DISPLAY *display = NULL;	//Evidentemente son todos punteros a lo que intuyo que es el espacio de memoria con 
	ALLEGRO_SAMPLE *sample = NULL;		//la info del display, etc. Supongo que en este caso el display no es un bitmap o 
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;	//algo por el estilo sino la parte de info en donde se dice qué está sonando

	bool display_close = false;		//Flag para informar sobre el estado "prendido/apagado" del display de sonido.

	//A partir de acá hay banda de llamados a funciones que - oh sorpresa - tampoco están documentados.

	/*Mi instinto ingenieril me dice que las funciones son de inicialización y de "recolección" de datos
	y archivos, etc. que evidentemente podrían no funcionar ante cualquier eventualidad (como el malloc)
	entonces seguro devuelven un int 0 o int 1 que se interpretan como un "ok polisha" o "arde troya".
	El if básicamente está para decir "inicialicemos el display" pero si el display no funca, avisamos
	que hubo un error y directamente return -1 al lobby, lo que sería un "se creashea el juego" para el
	usuario. Lo curioso es que evidentemente las funciones devuelven 1 si funcionan y 0 si no, lo cual,
	al menos para mí, es contraintuitivo. O sea, prendés el flag si salió todo ok?? En fin, cuestión,
	los profes hacen el plot twist de negar dicho valor, cosa de que si es cero se interpreta como
	"verdadero" o sea "sí hubo error" y entra al if. Como no hay necesidad de guardar dicho flag en
	ningún lado, solo reciben la devolución y la descartan, por eso no está "igualado" a nada. Creo que
	es una forma muy buena de ir haciendo las validaciones cortitas y al pie, para tomar nota! */


	//Otra cosa que me llama la atención es que no reciban parámetros.
	if (!al_init()) 
	{	//O sea, si veo normal que al_init no reciba parámetros
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_audio()) 
	{	//...pero install audio? Qué está instalando si no le pasamos nada?
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}

	if (!al_init_acodec_addon()) 
	{	//Esta sí es normal, porque también es un inicializador.
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}

	if (!al_reserve_samples(1)) 
	{	/*Entiendo que esta es """parecida""" al malloc en el sentido de que le avisamos cuántos
		soundtracks queremos cargar a la fila de reproducción. En este caso solo es el del ejemplo
		y creo que lo voy a dejar en 1, porque la idea sería ir pasándole de a uno a medida que se
		necesiten, pero bueno, eso de última se modifica y no pasa nada.*/
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

	//El truquito acá va a ser inventarse una forma útil de informar qué audio queremos a partir de
	//un parámetro, que no necesariamente sea un string del nombre. 

	sample = al_load_sample(path);	

	if (!sample)	//Más validaciones
	{
		printf("Audio clip sample not loaded!\n");
		return -1;
	}

	/*Aparentemente proyecta el display gráfico aunque no tiene nada para mostrar.
	Los parámetros calculo que son la resolución.*/
	display = al_create_display(640, 480);	

	if (!display)	//Más validaciones
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	event_queue = al_create_event_queue();	//Supongo que carga de uno en uno y por eso no pide parámetros.

	if (!event_queue)	//Más validaciones
	{
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	//Loop the sample until the display closes.
	al_play_sample(sample, volume, 0.0, speed, ALLEGRO_PLAYMODE_LOOP, NULL);

	while (!display_close) 
	{
		ALLEGRO_EVENT ev;
		if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT (coment de profe)
		{
			/*al_get_next_event va pasando al sig sonido, pero por cómo se estructuró la función,
			nunca va a cargar dos archivos a la cola en el mismo llamado. Para mí que eso es un
			mal diseño. Habrá que ver si después necesitamos cambiarlo o no. Veremos.*/

			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//Entiendo que hay un evento que se usa de terminador
				display_close = true;
		}

	}

	//Esto es como lo de "free memory alloc" 
	al_uninstall_audio();
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_sample(sample);

	return 0;
}
//Y esto es to esto es to esto es todo amigos