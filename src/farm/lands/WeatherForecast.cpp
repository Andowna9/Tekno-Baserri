extern "C" {
#include <console_config.h>
}

#include "WeatherForecast.h"
#include <curl/curl.h>


WeatherForecast::WeatherForecast() {

}

// TODO Configurar código postal para cambiar de localidad cuando se necesite

void WeatherForecast::update() {

    CURL *curl;
    FILE* fp;
    CURLcode res;

    // Iniciamos la interfaz síncrona de curl

    curl = curl_easy_init();

    if(curl) {

        fp = fopen("weather.xml", "w");

        // Opciones de transferencia

        curl_easy_setopt(curl, CURLOPT_URL, "http://www.aemet.es/xml/municipios/localidad_01006.xml"); // URL de descarga (imprescindible)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Deshabilitamos certificados de conexión segura
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirección habilitada
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // Puntero a fichero donde se ecriben los datos -> fwrite como callback por defecto


        res = curl_easy_perform(curl); //

        if(res != CURLE_OK) {

            printf_c(LIGHT_RED_TXT, "Error de red al actualizar pronóstico del tiempo!\n");

        }

        else {

            printf_c(LIGHT_GREEN_TXT, "Pronóstico de tiempo actualizado correctamente!\n");
        }


        curl_easy_cleanup(curl); //  Finalizamos la sesión

        fclose(fp);


    }

}
