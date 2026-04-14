#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define SIZE_INCREMENT 10
char *dia[7] =  {"domingo", "lunes", "martes", "miercoles", "jueves", "viernes", "sabado"}; //el domingo es 0 ya que es el 7o dia
char *centro[65] = {"Francisco_Fernandez_Ochoa","La_Almudena","La_Fundi","Aluche","Felix_Rubio","Gallur","La_Chopera","Marques_de_Samaranch","Pradillo","Alfredo_Goyeneche","Antonio_Diaz_Miguel","Barajas","Blanca_Fernandez_Ochoa","Centro_Integrado_Arganzuela","Cerro_Almodovar","Cubo_Gym_Chamartin","Cubo_Gym_Las_Tablas","Cubo_Gym_Madrid_Rio","Cubo_Gym_Retiro","El_Espinillo","El_Quijote","Entrevias","Faustina_Valladolid","Fernando_Martin","Fuente_del_Berro","Gimnasio_Moscardo","Hortaleza","Jose_Maria_Cagigal","Juan_de_Dios_Roman","La_Elipa","La_Maso","Orcasitas","Orcasur","Palomeras","Plata_y_Castanar","Playa_Victoria","Pueblo_Nuevo","Raul_Gonzalez","San_Blas","San_Cristobal","Triangulo_de_Oro","Vicente_del_Bosque","Wilfred_Agbonavbare","Las_Cruces","Eva_Duarte","Los_Caprichos","Torrespana","Casa_de_Campo","Circuito_BMX_Madrid_Rio","Daoiz_y_Velarde","Estanque_del_Retiro","Lago_Casa_de_Campo","Luis_Aragones","Margot_Moles","Moratalaz","San_Juan_Bautista","Estadio_Vallehermoso","Concepcion","Escuelas_San_Anton","Antiguo_Canodromo","Maria_Jesus_Rosa","Miguel_Guillen_Prim","Ciudad_de_los_Poetas","La_Bombilla","Tenis_Casa_de_Campo"};
char *modalidad[8] = {"vaso_ensenanza","ninguna","bordillo","central","calles_intermedia","calles_lateral","calles_central","calles_bordillo"};
char *actividades[185] = {"nado_libre","uso_sala_musculacion","uso_sala_multitrabajo","sala_de_musculacion","uso_de","uso","fitness_acuatico","natacion_acondicionamiento","calistenia","uso_libre_de","cubo_gym_cross_training_funcional","sala_multitrabajo_musculacion","boulder","rocodromo","de","carrera_acuatica","pruebas_de_nivel_natacion","entrenamiento_funcional","uso_pista_atletismo","fitness","matronatacion","cubogym_cross_training_funcional","uso_rocodromo","sala_musculacion","uso_musculacion_los_caprichos","ciclo_sala","gimnasia_suave","triatlon_por_madrid","entrenamiento_trx","aletas_acondicionamiento","ciclo_sala_virtual","autoproteccion_para_las_mujeres","uso_libre_sala_de_musculacion_90","uso_circuito_bmx","prueba_de_nivel_de_natacion","barcas_estanque_del_retiro","barcas_lago_casa_campo","sala_multitrabajo","pilates","uso_sauna","gimnasia_acuatica","prueba_de_nivel_natacion","prueba_de_nivel_padel","prueba_de_nivel_tenis","pilates_mesd","piraguismo_por_madrid","matronatacion_1_2_anos","fitness_gap","parkour_por_madrid","estiramientos_relajacion","circuito_fitness","fuerza_gap_mesd","cuerpo_mente","fitness_acuatico_mesd","uso_pista_patinaje","combinada_sala","yoga","reconocimiento_medico_deportivo_especial","water_army_camp","entrenamiento_por_intervalos","fuerza_gap","pilates_basico","entrenamiento_en_suspension_express","pilates_mayores","uso_de_sauna","uso_libre_patinaje","marcha_nordica_por_madrid","uso_libre_de_sala_multitrabajo","entrevista_deportiva_atp_multidisciplinar","fuerza_sala_multitrabajo_mananas_45","pilates_iniciacion","pilates_acuatico","hiit_expres","entrevista_deportiva_atp_con_prescripcion","uso_sala_cardio","pilates_acuatico_sobre_tabla","utilizacion_polideportiva","fuerza_en_sala_multitrabajo_mayores_65","aquaruning","caminar_por_madrid","pilates_mananas","aquagym","entrenamiento_funcional_expres","fuerza_en_sala_multitrabajo","fuerza_g_a_p","fitness_b_combat","correr_por_madrid","cubo_gym_cross_training_funcional_mayores","bodypump","fitness_cross","zumba","fuerza_general","aerofitness","cuerpo_mente_mayores","fitness_acuatico_mayores_de_65_anos","entrevista_sanitaria_cardiovascular","pickleball_acondicionamiento","gimnasia_acuatica_mayores","pickleball","entrenamiento_en_suspension","fuerza_core","fitness_acuatico_en_piscina_profunda","fuerza_core_express","uso_libre_sala_de_musculacion_60","padel_acondicionamiento","padel_acondicionamiento_nivel_1","acondicionamiento_fisico_mayores","uso_libre_cubo_gym","entrevista_deportiva","les_mills_core","acondicionamiento_cardiovascular","tenis_acondicionamiento","tonificacion_gap","funcional","acondicionamiento_fisico","acondicionamiento_fisico_65_anos","fitness_mayores","gimnasia_acuatica_mayores_65","baile","zz_pilates","estiramientos_relajacion_express","cross_training_cubo_gym","pruebas_de_nivel_de_natacion","gimnasias_suaves","padel_acondicionamieno","natacion_adulto_nivel_1","prueba_de_nivel_padel_adultos","padel_acondicionamiento_65","pilates_embarazadas","prueba_de_nivel_de_padel_adulto","prueba_de_nivel_natacion_deporte_adaptado","badminton","fuerza_en_sala_de_musculacion","combinada_sala_piscina","fuerza_sala_multirabajo","pruebas_de_nivel_padel","cuerpo_y_mente","prueba_de_nivel_de_padel","natacion_acondicionamiento_n2","estiramientos","prueba_nivel_de_tenis","combinada_piscina","prueba_de_nivel_de_tenis","hipopresivos_y_estiramientos","funcional_cubo_gym","patinaje_en_familia","actividad_fisica_y_juego_4_5_anos","matronatacion_3_4_anos","baloncesto_acondicionamiento","fuerza_hipopresivos","fuerza_en_sala","atletismo_acondicionamiento","comb_ciclo_entren_funcional","padel_acondicionamiento_nivel_2","pilates_tardes","bodycombat","calistenia_acondicionamiento","combinada_de_sala","cross_training","bodybalance","fitness_acuatico_sobre_tabla","entrenamiento_por_intervalos_expres","core_estiramientos","zz_natacion_acondicionamiento","core","aerofitness_bodystep","ballet_acondicionamiento","streching","acondicionamiento_fisico_mayores_65","fuerza_en_sala_multitrabajo_mayores","esnorquel_acondicionamiento","fitness_acuatico_mayores","prueba_de_nivel_de_padel_mananas","pilates_iniciacion_mesd","gap","total_training","entrenamiento_en_circuito","pilates_65","entrenamiento_por_intervalos_express","aquapilates","acondicionamiento_cardiovascular_atp","natacion_adulto_nivel_2","gimnasia_suave_b_balance","aqua_pump","fuerza_gap_express"};
char *tipo[6] = {"uso_libre","actividad_dirigida","prueba_de_nivel","barca_de_recreo","servicio_sanitario","entrevista_deportiva_sanitaria"};

typedef struct {
  uint32_t year;
  uint32_t mes;
  uint32_t dia;
  uint32_t dia_semana;
  uint32_t t0; //numero de minutos desde las 00:00
  uint32_t tf;
  uint32_t actividad; //guarda el indice en el array actividad
  uint32_t modalidad;
  uint32_t centro;
  uint32_t total;
  uint32_t ocupado;
  uint32_t libre;
  uint32_t tipo;
} actividad;

actividad *read_csv(char *filename, unsigned int *lineas);

actividad *read_csv(char *filename, unsigned int *lineas) {
  FILE *csv = fopen(filename, "r");
  actividad *dataptr = malloc(sizeof(actividad)*SIZE_INCREMENT);
  char linea[2048];
  char temp_str[5][128];
  uint32_t h0, hf, m0, mf; //variables locales intermedias para poder leer el archivo
  unsigned int n = 0; //como el tamaño del archivo es de en torno a 5k lineas, nos vale de sobra con un unsigned int (64k)
  unsigned int capacidad = SIZE_INCREMENT;
  
  if (csv == NULL) {
    printf("no se ha podido abrir el archivo");
    free(dataptr);
    return NULL;
  }

  fgets(linea, sizeof(linea), csv); //quitamos la primera linea que no contiene información
  while(fgets(linea, sizeof(linea), csv)) {
    if (n >= capacidad) {
      capacidad = capacidad * 2; //asi el resizing de memoria se hace en O(log(n)), gastando menos operaciones que una suma O(n)
      actividad *tempptr = realloc(dataptr, capacidad*sizeof(actividad));
      if (tempptr == NULL) {
        printf("problema de resizing del buffer");
        free(dataptr);
        return NULL;
      }
      dataptr = tempptr;
    }
    
    sscanf(linea, "%u %u %u %15[^ ] %u:%u %u:%u %127[^ ] %127[^ ] %127[^ ] %u %u %u %127s[^\n]", 
        &dataptr[n].year, 
        &dataptr[n].mes,
        &dataptr[n].dia,
        temp_str[0],
        &h0, 
        &m0, 
        &hf, 
        &mf, 
        temp_str[1],
        temp_str[2],
        temp_str[3],
        &dataptr[n].total,
        &dataptr[n].ocupado, 
        &dataptr[n].libre,
        temp_str[4]);

    dataptr[n].t0 = h0*60 + m0; //calculamos el tiempo en minutos sumando horas y minutos del dato capturado
    dataptr[n].tf = hf*60 + mf;

    for (int i = 0; i < 7; i++) {
      if(strcmp(temp_str[0], dia[i]) == 0) {
        dataptr[n].dia_semana = i;
      }
    } for (int i = 0; i < 65; i++) {
      if(strcmp(temp_str[1], centro[i]) == 0) {
        dataptr[n].centro = i;
      }
    } for (int i = 0; i < 9; i++) {
      if(strcmp(temp_str[2], modalidad[i]) == 0) {
        dataptr[n].modalidad = i;
      }
    } for (int i = 0; i < 185; i++) {
      if(strcmp(temp_str[3], actividades[i]) == 0) {
        dataptr[n].dia_semana = i;
      }
    } for (int i = 0; i < 6; i++) {
      if(strcmp(temp_str[4], tipo[i]) == 0) {
        dataptr[n].tipo = i;
      }
    }
    
    n++;
    printf("%s", linea);
  }
  *lineas = n; //devolvemos el numero de lineas que se han escrito

  fclose(csv);
  return(dataptr);
}

int main(void) {
  unsigned int l = 0;
  actividad *datavec = read_csv("dataset.csv", &l);
  printf("%lu %i", sizeof(actividad), l);
  return 0;
}
